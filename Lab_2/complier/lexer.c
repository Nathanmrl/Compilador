/* BEGIN - LAB 2 ---------------------------------------------*/
#include "compiler.h"
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "helpers/vector.h"
#include "helpers/buffer.h"

#define LEX_GETC_IF(buffer, c, exp)     \
    for (c = peekc(); exp; c = peekc()) \
    {                                   \
        buffer_write(buffer, c);        \
        nextc();                        \
    }

#define S_EQ(a, b) (strcmp((a), (b)) == 0)

// TODO o compilador esta lendo o token de comentario como um token de new line
bool is_keyword(const char *str)
{
    return S_EQ(str, "unsigned") ||
           S_EQ(str, "signed") ||
           S_EQ(str, "char") ||
           S_EQ(str, "short") ||
           S_EQ(str, "int") ||
           S_EQ(str, "long") ||
           S_EQ(str, "float") ||
           S_EQ(str, "double") ||
           S_EQ(str, "void") ||
           S_EQ(str, "struct") ||
           S_EQ(str, "union") ||
           S_EQ(str, "static") ||
           S_EQ(str, "__ignore_typecheck") ||
           S_EQ(str, "return") ||
           S_EQ(str, "include") ||
           S_EQ(str, "sizeof") ||
           S_EQ(str, "if") ||
           S_EQ(str, "else") ||
           S_EQ(str, "while") ||
           S_EQ(str, "for") ||
           S_EQ(str, "do") ||
           S_EQ(str, "break") ||
           S_EQ(str, "continue") ||
           S_EQ(str, "switch") ||
           S_EQ(str, "case") ||
           S_EQ(str, "default") ||
           S_EQ(str, "goto") ||
           S_EQ(str, "typedef") ||
           S_EQ(str, "const") ||
           S_EQ(str, "extern") ||
           S_EQ(str, "retrict");
}

struct token *read_next_token();
static struct lex_process *lex_process;
static struct token tmp_token;


// Pegar um caracter do arquivo, sem mudar a posição de leitura
static char peekc()
{
    return lex_process->function->peek_char(lex_process);
}

static char nextc()
{
    char c = lex_process->function->next_char(lex_process);
    lex_process->pos.col += 1;
    if (c == '\n')
    {
        lex_process->pos.line += 1;
        lex_process->pos.col = 1;
    }
    return c;
}

// Adicionar um caracter no arquivo
static void pushc(char c)
{
    lex_process->function->push_char(lex_process, c);
}

static struct pos lex_file_position()
{
    return lex_process->pos;
}

struct token *token_create(struct token *_token)
{
    memcpy(&tmp_token, _token, sizeof(struct token));
    tmp_token.pos = lex_file_position();

    return &tmp_token;
}

static struct token *lexer_last_token()
{
    return vector_back_or_null(lex_process->token_vec);
}

static struct token *handle_whitespace()
{
    struct token *last_token = lexer_last_token();
    if (last_token)
    {
        last_token->whitespace = true;
    }

    nextc();
    return read_next_token();
}

const char *read_number_str()
{
    struct buffer *buffer = buffer_create();
    char c = peekc();

    // Verifica prefixos para hexadecimal ou binário
    if (c == '0')
    {
        buffer_write(buffer, nextc()); // Consome o '0'
        c = peekc();
        if (c == 'x' || c == 'X') // Hexadecimal
        {
            buffer_write(buffer, nextc()); // Consome o 'x'
            LEX_GETC_IF(buffer, c, (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
        }
        else if (c == 'b' || c == 'B') // Binário
        {
            buffer_write(buffer, nextc()); // Consome o 'b'
            LEX_GETC_IF(buffer, c, (c == '0' || c == '1'));
        }
        else
        {
            // Não é hexadecimal ou binário, continua como número normal
            LEX_GETC_IF(buffer, c, (c >= '0' && c <= '9'));
        }
    }
    else
    {
        // Número decimal normal
        LEX_GETC_IF(buffer, c, (c >= '0' && c <= '9'));
    }

    // Finaliza a string
    buffer_write(buffer, 0x00);
    return buffer_ptr(buffer);
}

unsigned long long read_number()
{
    const char *s = read_number_str();

    // Detecta o prefixo e converte para decimal
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    {
        return strtoull(s, NULL, 16); // Hexadecimal
    }
    else if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B'))
    {
        return strtoull(s + 2, NULL, 2); // Binário (ignora o "0b")
    }
    else
    {
        return atoll(s); // Decimal
    }
}

struct token *token_make_number_for_value(unsigned long number)
{
    return token_create(&(struct token){.type = TOKEN_TYPE_NUMBER, .llnum = number});
}

struct token *token_make_number()
{
    unsigned long long number = read_number();
    printf("TOKEN\tNU: %llu\n", number); // Imprime apenas o número convertido
    return token_make_number_for_value(number);
}

static struct token *make_identifier_or_keyword()
{
    struct buffer *buffer = buffer_create();
    char c;
    LEX_GETC_IF(buffer, c, (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_'));

    buffer_write(buffer, 0x00);

    if (is_keyword(buffer_ptr(buffer)))
    {
        printf("TOKEN\tKW: %s\n", buffer->data); // Adicionado para exibir keywords
        return token_create(&(struct token){.type = TOKEN_TYPE_KEYWORD, .sval = buffer_ptr(buffer)});
    }

    printf("TOKEN\tID: %s\n", buffer->data); // Mantido para identificadores
    return token_create(&(struct token){.type = TOKEN_TYPE_IDENTIFIER, .sval = buffer_ptr(buffer)});
}

struct token *read_special_token()
{
    char c = peekc();
    if (isalpha(c) || c == '_')
    {
        return make_identifier_or_keyword();
    }

    return NULL;
}

static struct token *token_make_string(char start_delim, char end_delim)
{
    struct buffer *buf = buffer_create();
    assert(nextc() == start_delim); // Verifica se o caractere inicial é aspas duplas
    char c = nextc();

    for (; c != end_delim && c != EOF; c = nextc())
    {
        if (c == '\\')
        {
            // Retira o enter do final da string (se tiver)
            continue;
        }
        buffer_write(buf, c);
    }
    buffer_write(buf, 0x00);
    printf("TOKEN\tST: %s\n", buf->data);

    struct token *token = token_create(&(struct token){.type = TOKEN_TYPE_STRING, .sval = buffer_ptr(buf)});
    return token;
};

int token_is_keyword(struct token *token, const char *keyword)
{
    return strcmp(token->sval, keyword) == 0;
}

int is_operator_char(char c)
{
    switch (c)
    {
    OPERATOR_CASE:
        return 1;
    default:
        return 0;
    }
}

char *read_op()
{
    char op[2] = {0}; // Temporary buffer
    int len = 0;

    char current = nextc();
    op[len++] = current;

    while (len < 2 - 1)
    {
        char next = peekc();

        if (is_operator_char(next))
        {
            op[len++] = nextc();
        }
        else
        {
            break;
        }
    }

    op[len] = '\0';

    // Copy to heap and return (caller should free)
    char *result = malloc(len + 1);
    strcpy(result, op);
    return result;
}

static void lex_new_expression()
{
    lex_process->current_expression_count++;
    if (lex_process->current_expression_count == 1)
    {
        lex_process->parentheses_buffer = buffer_create();
    }
}

static struct token *token_make_operator_or_string()
{
    char op = peekc();
    // Tratar o caso do #include <abc.h>
    if (op == '<')
    {
        struct token *last_token = lexer_last_token();
        if (token_is_keyword(last_token, "include"))
        {
            return token_make_string('<', '>');
        }
    }

    struct token *token = token_create(&(struct token){.type = TOKEN_TYPE_STRING, .sval = read_op()});
    printf("TOKEN\tOP: %s\n", token->sval); // Adicionado para exibir operadores
    if (op == '(')
    {
        lex_new_expression();
    }

    return token;
}

static void lex_finish_expression()
{
    lex_process->current_expression_count--;

    if (lex_process->current_expression_count < 0)
    {
        compiler_error(lex_process->compiler, "Você fechou uma expressão nunca iniciada!\n");
    }
}

bool lex_is_in_expression()
{
    return lex_process->current_expression_count > 0;
}

static struct token *token_make_symbol()
{
    char c = nextc();
    if (c == ')')
    {
        lex_finish_expression();
    }

    struct token *token = token_create(&(struct token){.type = TOKEN_TYPE_SYMBOL, .cval = c});
    printf("TOKEN\tSY: %c\n", c);
    return token;
}

struct token *token_make_one_line_comment()
{
    struct buffer *buffer = buffer_create();
    char c = 0;
    LEX_GETC_IF(buffer, c, c != '\n' && c != EOF);

    return token_create(&(struct token){.type = TOKEN_TYPE_COMMENT, .sval = buffer_ptr(buffer)});
}

struct token *token_make_multiline_comment()
{
    struct buffer *buffer = buffer_create();
    char c = 0;
    while (1)
    {
        LEX_GETC_IF(buffer, c, c != '*' && c != EOF);

        if (c == EOF)
        {
            compiler_error(lex_process->compiler, "O comentário não foi fechado!\n");
        }
        else if (c == '*')
        {
            nextc(); // Pula para o próximo caractere do arquivo

            if (peekc() == '/')
            {
                // Finaliza o comentário
                nextc();
                break;
            }
        }
    }

    return token_create(&(struct token){.type = TOKEN_TYPE_COMMENT, .sval = buffer_ptr(buffer)});
}

struct token *handle_comment()
{
    char c = peekc();
    if (c == '/')
    {
        nextc();
        if (peekc() == '/')
        {
            nextc();
            return token_make_one_line_comment();
        }
        else if (peekc() == '*')
        {
            nextc();
            return token_make_multiline_comment();
        }

        pushc('/');
        return token_make_operator_or_string();
    }

    return NULL;
}

struct token *token_make_newline()
{
    nextc();
    printf("TOKEN\tNL \n");
    return token_create(&(struct token){.type = TOKEN_TYPE_NEWLINE});
}

// Função responsável por ler o próximo token do arquivo de entrada
// Retorna NULL se não houver mais tokens
// Retorna um ponteiro para o token lido
// O token lido é armazenado em um vetor de tokens
// O vetor de tokens é alocado dinamicamente e deve ser liberado pelo chamador
// O vetor de tokens é redimensionado automaticamente conforme necessário
// O vetor de tokens é inicializado com tamanho 0 e é redimensionado para o tamanho necessário
// O vetor de tokens é liberado automaticamente quando o processo de lexing é finalizado
struct token *read_next_token()
{
    struct token *token = NULL;
    char c = peekc();

    token = handle_comment();
    if (token)
        return token;

    switch (c)
    {
    case EOF: /**/
        break;

    NUMERIC_CASE:
        token = token_make_number();
        break;

    SYMBOL_CASE:
        token = token_make_symbol();
        break;
    OPERATOR_CASE:
        token = token_make_operator_or_string();
        break;
    case '"':
        token = token_make_string('"', '"');
        break;
    case '\t':
    case ' ':
        token = handle_whitespace();
        break;

    case '\n':
        token = token_make_newline();
        break;

    default:
        token = read_special_token();
        if (!token)
        {
            compiler_error(lex_process->compiler, "Token invalido!\n");
        }
        break;
    }
    return token;
}

int lex(struct lex_process *process)
{
    process->current_expression_count = 0;
    process->parentheses_buffer = NULL;
    lex_process = process;
    process->pos.filename = process->compiler->cfile.abs_path;

    struct token *token = read_next_token();

    // Ler todos os tokens do arquivo de input
    while (token)
    {
        vector_push(process->token_vec, token);
        token = read_next_token();
    }

    return LEXICAL_ANALYSIS_ALL_OK;
}

/* END - LAB 2 -----------------------------------------------*/