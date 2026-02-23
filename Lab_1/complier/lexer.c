/* BEGIN - LAB 2 ---------------------------------------------*/
#include "compiler.h"
#include <string.h>
#include "helpers/vector.h"
#include "helpers/buffer.h"

#define LEX_GETC_IF(buffer, c, exp) \
  for (c = peekc(); exp; c = peekc()) { \
    buffer_write(buffer, c); \
    nextc(); \
  } 
//Mexido
bool is_operator_char(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
           c == '=' || c == '<' || c == '>' || c == '!' || c == '&' ||
           c == '|' || c == '^' || c == '~' || c == '?';
  }
  


struct token* read_next_token();
static struct lex_process* lex_process;
static struct token tmp_token;

// Pegar um caractere do arquivo, sem mudar a posição de leitura
static char peekc() {
  return lex_process->function->peek_char(lex_process);
}

static char nextc() {
  char c = lex_process->function->next_char(lex_process);
  lex_process->pos.col += 1;

  if (c == '\n') {
    lex_process->pos.line += 1;
    lex_process->pos.col = 1;
  }
  return c;
}

// Adicionar novo caractere no arquivo
static void pushc(char c) {
  lex_process->function->push_char(lex_process, c);
}

static struct pos lex_file_position() {
  return lex_process->pos;
}

struct token* token_create(struct token* _token) {
  memcpy(&tmp_token, _token, sizeof(struct token));
  tmp_token.pos = lex_file_position();

  return &tmp_token;
}

static struct token* lexer_last_token() {
  return vector_back_or_null(lex_process->token_vec);
}

static struct token* handle_whitespace() {
  struct token* last_token = lexer_last_token();
  if (last_token) {
    last_token->whitespace = true;
  }

  nextc();
  return read_next_token();
}

// Funções para NUMERIC_CASE
const char* read_number_str() {
  const char* num = NULL;
  struct buffer* buffer = buffer_create();
  char c = peekc();
  bool has_decimal_point = false;
  
    // Lê os dígitos e o ponto decimal (se houver)
    LEX_GETC_IF(buffer, c, ((c >= '0' && c <= '9') || (c == '.' && !has_decimal_point && (has_decimal_point = true))));

  // Finaliza a string
  buffer_write(buffer, 0x00);

  printf("Token: %s (NUMBER)\n", buffer->data);
  // Retorna o ponteiro para o buffer
  return buffer_ptr(buffer);
}

unsigned long long read_number() {
  const char* s = read_number_str();
  return atoll(s);
}

struct token* token_make_number_for_value(unsigned long number){
  return token_create(&(struct token){.type=TOKEN_TYPE_NUMBER, .llnum=number});
}

struct token* token_make_number(){
  return token_make_number_for_value(read_number());
}



// Funções para STRING_CASE
const char* read_string() {
    struct buffer* buffer = buffer_create();
    char c = peekc();
  
    // Verifica se começa com aspas
    if (c != '"') {
      printf("Erro: String deve começar com aspas!\n");
      return NULL;
    }
  
    nextc(); // Consome a primeira aspas
  
    while ((c = peekc()) != '"' && c != EOF) {
      // Trata escape de aspas: \" dentro da string
      if (c == '\\') {
        nextc(); // consome '\'
        char next = peekc();
        switch (next) {
          case '"': buffer_write(buffer, '"'); nextc(); break;
          case 'n': buffer_write(buffer, '\n'); nextc(); break;
          case 't': buffer_write(buffer, '\t'); nextc(); break;
          case '\\': buffer_write(buffer, '\\'); nextc(); break;
          default: buffer_write(buffer, '\\'); break;
        }
      } else {
        buffer_write(buffer, c);
        nextc();
      }
    }
  
    // Verifica se terminou com aspas
    if (peekc() == '"') {
      nextc(); // Consome a aspas final
    } else {
      printf("Erro: String não fechada!\n");
    }
  
    // Finaliza string com null terminator
    buffer_write(buffer, 0x00);
  
    printf("Token: %s (STRING)\n", buffer->data);
    return buffer_ptr(buffer);
  }
  
  struct token* token_make_string() {
    const char* str = read_string();
    return token_create(&(struct token){
        .type = TOKEN_TYPE_STRING,
        .sval = strdup(str)
    });
}



// Funções para KEYWORD_CASE
bool is_keyword(const char* str) {
  const char* keywords[] = {
    "unsigned", "signed", "char", "short", "int", "long", "float", "double",
    "void", "struct", "union", "static", "return", "include", "sizeof", "if",
    "else", "while", "for", "do", "break", "continue", "switch", "case",
    "default", "goto", "typedef", "const", "extern", "restrict", NULL
  };

  for (int i = 0; keywords[i]; i++) {
    if (strcmp(str, keywords[i]) == 0) {
      return true;
    }
  }
  return false;
}

const char* read_identifier() {
  struct buffer* buffer = buffer_create();
  char c = peekc();

      // Lê caracteres válidos para identificadores (letras, números, '_', '.')
      LEX_GETC_IF(buffer, c, ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
      (c >= '0' && c <= '9') || c == '_' || c == '.'));

  // Finaliza a string
  buffer_write(buffer, 0x00);

  // Retorna o ponteiro para o buffer
  return buffer_ptr(buffer);
}

struct token* token_make_keyword_or_identifier() {
  const char* str = read_identifier();
  if (is_keyword(str)) {
    printf("Token: %s (KEYWORD)\n", str); // Imprime o token como KEYWORD
    return token_create(&(struct token){.type = TOKEN_TYPE_KEYWORD, .sval = strdup(str)});
  }
  printf("Token: %s (IDENTIFIER)\n", str); // Imprime o token como IDENTIFIER
  return token_create(&(struct token){.type = TOKEN_TYPE_IDENTIFIER, .sval = strdup(str)});
}



// Funções para OPERATOR_CASE
const char* read_operator() {
  struct buffer* buffer = buffer_create();
  char c = nextc(); // Consome o operador atual

  // Adiciona o operador ao buffer
  buffer_write(buffer, c);

  // Finaliza a string
  buffer_write(buffer, 0x00);

  printf("Token: %s (OPERATOR)\n", buffer->data); // Imprime o token
  return buffer_ptr(buffer);
}

struct token* token_make_operator() {
  const char* op = read_operator();
  return token_create(&(struct token){.type = TOKEN_TYPE_OPERATOR, .sval = strdup(op)});
}


// Funções para SYMBOL_CASE
const char* read_symbol() {
  struct buffer* buffer = buffer_create();
  char c = nextc(); // Consome o símbolo atual

  // Adiciona o símbolo ao buffer
  buffer_write(buffer, c);

  // Finaliza a string
  buffer_write(buffer, 0x00); 
  
  printf("Token: %s (SYMBOL)\n", buffer->data);
  // Retorna o ponteiro para o buffer
  return buffer_ptr(buffer);
}

struct token* token_make_symbol() {
  const char* sym = read_symbol();
  return token_create(&(struct token){.type = TOKEN_TYPE_SYMBOL, .sval = strdup(sym)});
}



// Funções para COMMENT_CASE
const char* read_comment() {
    struct buffer* buffer = buffer_create();
    char c = nextc(); // Consome o primeiro '/'

    // Para comentários de linha "//"
    if (peekc() == '/') {
        nextc(); // Consome o segundo '/'
        // Lê até o final da linha ou EOF
        LEX_GETC_IF(buffer, c, (c != '\n' && c != EOF));

    // Para comentários de múltiplas linhas "/* ... */"
    } else if (peekc() == '*') {
      nextc(); // Consome o '*'

      // Busca o fechamento do comentário
      while ((c = peekc()) != EOF) {
          if (c == '*') {
              nextc(); // Consome o '*'
              if (peekc() == '/') {
                  nextc(); // Consome o '/'
                  break; // Fim do comentário
              }
              buffer_write(buffer, '*'); // Adiciona o '*' ao buffer se não for seguido por '/'
          } else {
              buffer_write(buffer, c); // Adiciona o caractere ao buffer
              nextc();
          }
      }

      // Verifica se o comentário foi fechado corretamente
      if (c == EOF) {
          printf("Erro: Comentário de múltiplas linhas não fechado!\n");
      }
    } else {
        // Não é um comentário válido, apenas retorna o caractere '/'
        buffer_write(buffer, '/');
    }

    // Finaliza a string
    buffer_write(buffer, 0x00); 

    printf("Token: %s (COMMENT)\n", buffer->data);
    // Retorna o ponteiro para o buffer
    return buffer_ptr(buffer);
}

struct token* token_make_comment() {
  const char* comment = read_comment();
  return token_create(&(struct token){.type = TOKEN_TYPE_COMMENT, .sval = strdup(comment)});
}



struct token* read_next_token() {
    struct token* token = NULL;
    char c = peekc();
    
    switch (c) {
    case EOF:
      break;
  
      NUMERIC_CASE:
          token = token_make_number();
          break;
  
      KEYWORD_CASE:
          token = token_make_keyword_or_identifier();
          break;
  
      OPERATOR_CASE:
          token = token_make_operator();
        break;
  
      case '/':
        token = token_make_comment();
      break;
  
      case '\n':
          token = token_create(&(struct token){.type = TOKEN_TYPE_NEWLINE});
          nextc();
      break;
      case '"':
          token = token_make_string('"','"');
          break;
  
      case ' ':
          token = handle_whitespace();
          break;
      case '\t':
          token = handle_whitespace();
      break;
  
      default:
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
            token = token_make_keyword_or_identifier();
        } else if (is_operator_char(c)) {
            token = token_make_operator();
        } else {
            printf("Caractere inválido ignorado: %c\n", c); // Depuração
            nextc();
        }
      break;
    }
  
    return token;
  }
  

int lex(struct lex_process* process) {
  process->current_expression_count = 0;
  process->parentheses_buffer = NULL;
  lex_process = process;
  process->pos.filename = process->compiler->cfile.abs_path;

  struct token* token = read_next_token();

  while (token) {
    vector_push(process->token_vec, token);
    token = read_next_token();
  }

  return LEXICAL_ANALYSIS_ALL_OK;
}

/* END - LAB 2 -----------------------------------------------*/
