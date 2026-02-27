# Projeto de Compiladores - Grupo 8

## Visão Geral

Este repositório contém os trabalhos realizados pelo **Grupo 8** na disciplina de **Compiladores**. O objetivo principal é desenvolver um compilador funcional, passando por todas as etapas do processo de compilação, desde a análise léxica até a geração de código. Cada laboratório aborda um aspecto específico do desenvolvimento de compiladores, com atividades práticas e teóricas.

## Integrantes do Grupo

- **Nathan Mauricio Rodrigeus Lopes**
- **Paulo Vinicius Isidro**
- **João Victor Azevedo dos Santos**
- **Yago Péres dos Santos**

## Estrutura do Repositório

O repositório está organizado em pastas, cada uma representando um laboratório (LAB). Abaixo, segue uma breve descrição de cada LAB:

---

### **LAB01 - Fundamentos e Estruturas de Suporte**
- **Objetivo**: Desenvolver as estruturas base necessárias para o compilador, incluindo vetores dinâmicos e buffers.
- **Atividades**:
  - Implementação das estruturas `vector` e `buffer`.
  - Criação de funções para manipulação dinâmica de memória.
  - Desenvolvimento de testes unitários.
  - Configuração de `Makefile` para automação da compilação.
- **Resultados**:
  - Estruturas auxiliares estáveis e testadas.
  - Base sólida para evolução do compilador.

### **LAB02 - Ponteiros e Implementação da Análise Léxica**
- **Objetivo**: Aplicar conceitos de ponteiros e iniciar o desenvolvimento do analisador léxico.
- **Atividades**:
  - Manipulação de tipos utilizando `union`.
  - Uso de ponteiros para operações matemáticas e arrays de funções.
  - Implementação inicial do lexer.
  - Identificação de tokens em arquivos fonte.
- **Resultados**:
  - Analisador léxico funcional.
  - Reconhecimento de números, strings, palavras-chave, operadores e símbolos.

### **LAB03 - Aprimoramento da Análise Léxica e Início do Parser**
- **Objetivo**: Refinar o analisador léxico e iniciar a implementação da análise sintática.
- **Atividades**:
  - Suporte completo a tokens, incluindo números hexadecimais e binários.
  - Implementação inicial do parser.
  - Criação das estruturas da AST (`FUNCTION_NODE`, `VARIABLE_NODE`, `EXPRESSION_NODE`).
  - Atualização do `Makefile` com novos módulos.
- **Resultados**:
  - Lexer aprimorado e estável.
  - Parser inicial capaz de construir a AST básica.

### **LAB04 - Análise Sintática Completa e Processamento de Expressões**
- **Objetivo**: Consolidar a análise sintática e implementar o processamento completo de expressões.
- **Atividades**:
  - Integração total entre lexer e parser.
  - Construção completa da AST.
  - Implementação de precedência de operadores.
  - Geração de código intermediário.
  - Criação de testes unitários e de integração.
- **Resultados**:
  - Compilador com análise léxica e sintática integradas.
  - Processamento correto de expressões.
  - Estruturas auxiliares robustas.

### **LAB05 - Gerenciamento de Escopo e Resolução de Símbolos**
- **Objetivo**: Implementar controle de escopo e validação semântica.
- **Atividades**:
  - Desenvolvimento do sistema de escopo para variáveis e funções.
  - Implementação de múltiplos níveis de escopo.
  - Criação do resolvedor de símbolos.
  - Implementação de verificação de tipos.
- **Resultados**:
  - Sistema de escopo funcional.
  - Resolução e validação de declarações implementadas.
  - Análise semântica integrada ao compilador.

### **LAB06 - Extensões de Sintaxe e Funcionalidades Avançadas**
- **Objetivo**: Expandir o compilador com novas variações sintáticas e recursos avançados.
- **Atividades**:
  - Implementação da sintaxe `A igual int;`.
  - Implementação alternativa de `struct`.
  - Implementação alternativa de `if/else` com `?`.
  - Suporte a arrays multidimensionais e ponteiros.
  - Tratamento avançado de erros.
- **Resultados**:
  - Novas sintaxes alternativas totalmente funcionais.
  - Suporte ampliado a tipos complexos.
  - Compilador expandido e robusto.

## Como Executar

1. Navegue até a pasta do laboratório desejado.
2. Compile o projeto utilizando o `Makefile`:

   ```bash
   make
   ```

3. Execute o programa gerado:

   ```bash
   ./main
   ```

### Exemplo para LAB06

```bash
cd LAB06/src
make
./main test.c
```

## Testes e Resultados

Cada laboratório inclui testes específicos para validar as funcionalidades implementadas. Os testes podem ser executados compilando o projeto e rodando o executável gerado. Consulte os arquivos `README.md` de cada laboratório para mais detalhes sobre os testes realizados e seus resultados.

### Funcionalidades Implementadas

- **Estruturas Auxiliares**: Vetores dinâmicos e buffers
- **Análise Léxica**: Reconhecimento de tokens, números, strings, operadores
- **Análise Sintática**: Parser e construção de AST
- **Manipulação de Expressões**: Precedência de operadores e avaliação
- **Gerenciamento de Escopo**: Controle de variáveis e funções
- **Resolução de Símbolos**: Validação de declarações e tipos
- **Sintaxes Alternativas**: Novas formas de declarar variáveis, structs e condicionais

---

## Status do Projeto

✅ **LAB01** - Concluído  
✅ **LAB02** - Concluído  
✅ **LAB03** - Concluído  
✅ **LAB04** - Concluído  
✅ **LAB05** - Concluído  
✅ **LAB06** - Concluído  

O projeto está **100% completo** com todas as funcionalidades implementadas e testadas.

---
