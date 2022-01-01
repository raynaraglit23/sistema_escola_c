#ifndef DISCIPLINA_H  
#define DISCIPLINA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professor.h"

#define MAX 100

//struct definida da disciplina
typedef struct disciplina
{
	int id;
	int id_professor;
    char nome[MAX];
	char descricao[500];
	char num_creditos[5];
    char carga_hora[5];
} t_disciplina;

t_disciplina *obter_disciplina(FILE *arq_disciplina, int id_disciplina);
int existe_disciplina(FILE *arq_disciplina, int id_disciplina);
void atualizar_disciplina(FILE *arq_disciplina, t_disciplina *arqd_atualizar);


int str_somente_numeros(char str[]);

//funções
void cadastrar_disciplina();
void listar_disciplina();
void pesquisar_disciplina();
void alterar_disciplina();
void excluir_disciplina();
void professor_da_disciplina();


#endif