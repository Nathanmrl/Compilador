# Grupo 7 - Relatório do Laboratório

## Integrantes

- Isabela Garcia Godinho
- João Victor Azevedo dos Santos
- Luiz Eduardo Campos Dias
- Yago Péres dos Santos

### Laboratório 04

Sala: 1002 - Turma A - 0225

---

## Lista de Arquivos Enviados

- **src/**
  - [`compiler.c`](src/compiler.c)
  - [`compiler.h`](src/compiler.h)
  - [`cprocess.c`](src/cprocess.c)
  - [`expressionable.c`](src/expressionable.c)
  - [`lex_process.c`](src/lex_process.c)
  - [`lexer.c`](src/lexer.c)
  - [`main`](src/main)
  - [`main.c`](src/main.c)
  - [`Makefile`](src/Makefile)
  - [`node.c`](src/node.c)
  - [`output.c`](src/output.c)
  - [`parser.c`](src/parser.c)
  - [`parser.h`](src/parser.h)
  - [`test.c`](src/test.c)
  - [`test`](src/test)
  - [`test_precedence1.c`](src/test_precedence1.c)
  - [`test_precedence2.c`](src/test_precedence2.c)
  - [`test_precedence3.c`](src/test_precedence3.c)
  - [`token.c`](src/token.c)
  - **build/**
    - `compiler.o`
    - `cprocess.o`
    - `expressionable.o`
    - `lex_process.o`
    - `lexer.o`
    - `node.o`
    - `parser.o`
    - `token.o`
    - **helpers/**
      - `buffer.o`
      - `vector.o`
  - **helpers/**
    - [`buffer.c`](src/helpers/buffer.c)
    - [`buffer.h`](src/helpers/buffer.h)
    - [`vector.c`](src/helpers/vector.c)
    - [`vector.h`](src/helpers/vector.h)

---

## Descrição do Trabalho Realizado

Neste laboratório, o foco foi a evolução do compilador com a implementação e integração de novos módulos para análise sintática e manipulação de expressões, além do refinamento do analisador léxico. As principais atividades desenvolvidas incluem:

### Estruturas Auxiliares

- **Vetores Dinâmicos (`vector`)**: Funções para criação e manipulação de vetores dinâmicos, localizadas em [`vector.c`](src/helpers/vector.c) e [`vector.h`](src/helpers/vector.h).
- **Buffers (`buffer`)**: Manipulação de buffers dinâmicos, em [`buffer.c`](src/helpers/buffer.c) e [`buffer.h`](src/helpers/buffer.h).

### Núcleo do Compilador

- **Processamento de Compilação**: [`compiler.c`](src/compiler.c), [`compiler.h`](src/compiler.h) e [`cprocess.c`](src/cprocess.c) implementam a lógica principal do compilador, incluindo controle de arquivos, flags e integração com o analisador léxico e sintático.
- **Função Principal**: [`main.c`](src/main.c) contém o ponto de entrada do programa, lidando com argumentos de linha de comando e inicialização do processo de compilação.

### Análise Léxica

- **Analisador Léxico**: [`lexer.c`](src/lexer.c) e [`lex_process.c`](src/lex_process.c) implementam a leitura e classificação de tokens, com suporte a números, operadores, palavras-chave, símbolos, strings e comentários.
- **Tokens**: [`token.c`](src/token.c) define e manipula as estruturas de tokens reconhecidas pelo lexer.

### Análise Sintática

- **Parser**: [`parser.c`](src/parser.c) e [`parser.h`](src/parser.h) implementam o parser responsável por construir a árvore de sintaxe abstrata (AST) a partir dos tokens.
- **Nós da AST**: [`node.c`](src/node.c) define as estruturas dos nós da AST, como funções, variáveis e expressões.
- **Manipulação de Expressões**: [`expressionable.c`](src/expressionable.c) trata a análise e avaliação de expressões, incluindo precedência de operadores.

### Saída e Utilitários

- **Geração de Saída**: [`output.c`](src/output.c) é responsável pela geração de código ou saída intermediária do compilador.

### Testes

- **Testes de Unidade e Integração**: [`test.c`](src/test.c), [`test_precedence1.c`](src/test_precedence1.c), [`test_precedence2.c`](src/test_precedence2.c), [`test_precedence3.c`](src/test_precedence3.c) validam o funcionamento dos módulos do compilador, especialmente análise léxica, sintática e precedência de operadores.

### Automação

- **Makefile**: [`Makefile`](src/Makefile) automatiza a compilação de todos os módulos e geração do executável principal.

---

## Entregas Solicitadas

- Código-fonte completo do compilador, incluindo análise léxica, sintática e manipulação de expressões.
- Arquivo `Makefile` configurado para compilar todos os módulos e gerar o executável.
- Arquivos de teste para validação das funcionalidades implementadas.
- Estruturas auxiliares para vetores e buffers.
- Relatório detalhado das atividades realizadas.

---
