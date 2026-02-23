#include <stdio.h>
#include <stdlib.h>
#include "build/helpers/vector.h"
#include "build/helpers/buffer.h"
#include "compiler.h"

void test_vector() {
    // Criando um vetor de inteiros
    struct vector* vec = vector_create(sizeof(int));

    printf("Vector criado com sucesso!\n");


    // Inserindo elementos no vetor
    for (int i = 0; i < 5; i++) {
        printf("Inserindo: %d\n", i);
        vector_push(vec, &i);
    }

    // Pegando o último elemento sem remover
    int* peek_val = vector_peek(vec);
    if (peek_val)
        printf("Peek: %d\n", *peek_val);

    // Ajustando ponteiro de leitura para posição 2
    vector_set_peek_pointer(vec, 2);
    peek_val = vector_peek(vec);
    if (peek_val)
        printf("Peek na posição 2: %d\n", *peek_val);

    // Removendo o último elemento
    vector_pop(vec);
    printf("Último elemento removido\n");

    // Liberando a memória do vetor
    vector_free(vec);
}

int main() {
    printf("Compiladores  TURMA A GRUPO 8 \n");
    //test_vector();

    int res = compile_file("./teste.c","./outtest",0);
    if (res == COMPILER_FILE_COMPILED_OK){
        printf("Todos os arquivos foram compilados com sucesso!\n");
    } else if (res == COMPILER_FAILED_WITH_ERRORS){
        printf("Erro de compilacao!\n");
    } else {
        printf("Erro desconhecido!\n");
    }

    return 0;
}
