#ifdef __WIN32
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif

#include "professor.h"
#include "disciplina.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

//função criar disciplina
    void cadastrar_disciplina() {
        FILE *arq_disciplina = fopen("disciplina.bin", "a+b");

        if (arq_disciplina == NULL) {
            printf("\nFalha ao abrir arquivo(s)!\n");
            exit(1);
        }
        t_disciplina disciplina;

        int cont_bytes = 0;

        fseek(arq_disciplina, 0, SEEK_END);

        cont_bytes = ftell(arq_disciplina);

        if (cont_bytes == 0) {
            disciplina.id = 1;
        } else {
            t_disciplina ultimo_disciplina;

            fseek(arq_disciplina, cont_bytes - sizeof(t_disciplina), SEEK_SET);

            fread(&ultimo_disciplina, sizeof(t_disciplina), 1, arq_disciplina);

            disciplina.id = ultimo_disciplina.id + 1;
        }

        printf("\nDigite o nome da disciplina: ");
        gets(disciplina.nome);
        printf("\nDigite a descricao da disciplina: ");
        gets(disciplina.descricao);
        printf("\nDigite o numero de creditos da disciplina: ");
        scanf("%10s%*c", disciplina.num_creditos);
        printf("\nDigite a carga horaria semanal da disciplina (2h, 4h,6h): ");
        scanf("%10s%*c", disciplina.carga_hora);
        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");

        fseek(stdin, 0, SEEK_END);
        disciplina.id_professor = -1;
        fseek(arq_disciplina, 0, SEEK_END);

        fwrite(&disciplina, sizeof(t_disciplina), 1, arq_disciplina);

        fclose(arq_disciplina);
        system(limpar_tela);

        printf("\nDisciplina \"%s\" cadastrado com sucesso!\n", disciplina.nome);
        printf("\nDescricao:\"%s\"\n", disciplina.descricao);
        printf("\nNumero de creditos:\"%s\"\n", disciplina.num_creditos);
        printf("\nCarga horaria:\"%s\"\n", disciplina.carga_hora);
        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");

        fseek(stdin, 0, SEEK_END);
    }

// função que ligar professor à disciplina
    void professor_da_disciplina() {
        char str_id_professor[10];
        int id_professor;

        FILE *arq_disciplina = fopen("disciplina.bin", "rb+");
        FILE *arq_professor = fopen("professor.bin", "rb+");

        if (arq_disciplina == NULL) {
            arq_disciplina = fopen("disciplina.bin", "wb+");
            if (arq_disciplina == NULL) {
                printf("\nFalha ao criar arquivo(s)!\n");
                exit(1);
            }
        }

        if (arq_professor == NULL) {
            arq_professor = fopen("professor.bin", "wb+");
            if (arq_professor == NULL) {
                printf("\nFalha ao criar arquivo(s)!\n");
                exit(1);
            }
        }

        printf("\nDigite o ID do professor: ");
        scanf("%10s%*c", str_id_professor);

        fseek(stdin, 0, SEEK_END);

        if (str_somente_numeros(str_id_professor) == 1) {
            sscanf(str_id_professor, "%d", &id_professor);

            if (existe_professor(arq_professor, id_professor)) {
                char str_id_disciplina[10];
                int id_disciplina;

                printf("\nDigite o ID da disciplina: ");
                scanf("%10s%*c", str_id_disciplina);

                fseek(stdin, 0, SEEK_END);

                if (str_somente_numeros(str_id_disciplina) == 1) {
                    sscanf(str_id_disciplina, "%d", &id_disciplina);

                    t_disciplina *disciplina = obter_disciplina(arq_disciplina, id_disciplina);

                    if (disciplina != NULL) {
                        if (disciplina->id_professor != -1)
                            printf("\nA disciplina \"%s\" ja e lecionada pelo professor de id %d\n", disciplina->nome,disciplina->id_professor);
                        else {
                            disciplina->id_professor = id_professor;
                            atualizar_disciplina(arq_disciplina, disciplina);
                            printf("\nDisciplina \"%s\" associada com sucesso com professor de id %d\n",
                                   disciplina->nome, disciplina->id_professor);
                        }
                        free(disciplina);
                    } else
                        printf("\nNao existe disciplina com o ID \"%d\".\n", id_disciplina);
                } else
                    printf("\nO ID so pode conter numeros!\n");
            } else
                printf("\nNao existe professor com o ID \"%d\".\n", id_professor);
        } else
            printf("\nO ID so pode conter numeros!\n");

        fclose(arq_professor);
        fclose(arq_disciplina);

        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");

        fseek(stdin, 0, SEEK_END);
    }

//função pesquisar disciplina
    void pesquisar_disciplina() {
        char nome[MAX];
        int encontrou_disciplina = 0;

        FILE *arq_disciplina = fopen("disciplina.bin", "rb");
        FILE *arq_professor = fopen("professor.bin", "rb");

        if (arq_disciplina == NULL) {
            printf("\nFalha ao abrir arquivo(s)!\n");
            exit(1);
        }

        printf("\nDigite o nome da disciplina: ");
        scanf("%99[^\n]%*c", nome);

        printf("\nDisciplina com o nome \"%s\":\n\n", nome);
        t_disciplina disciplina;
        while (1) {
            size_t result = fread(&disciplina, sizeof(t_disciplina), 1, arq_disciplina);

            if (result == 0)
                break;

            char nome_aux[MAX];
            strcpy(nome_aux, disciplina.nome);

            if (strcmp(strupr(nome_aux), strupr(nome)) == 0) {
                printf("\nDisciplina:\"%s\"", disciplina.nome);
                printf("\nDescricao:\"%s\"", disciplina.descricao);
                printf("\nNumero de creditos:\"%s\"", disciplina.num_creditos);
                printf("\nCarga horaria:\"%s\"", disciplina.carga_hora);

                if (disciplina.id_professor != -1) {
                    if (arq_professor == NULL) {
                        printf("\nFalha ao abrir arquivo!\n");
                        fclose(arq_professor);
                        exit(1);
                    }
                    t_professor *professor = obter_professor(arq_professor, disciplina.id_professor);
                    printf("Disciplina tem professor? Sim, professor: %s\n", professor->nome);
                    free(professor);
                } else {
                    printf("Disciplina tem professor? Nao\n");
                }
                encontrou_disciplina = 1;
                printf("\n");
            }
        }

        if (encontrou_disciplina == 0){
            printf("Nenhuma disciplina encontrada.\n\n");
        }
        fclose(arq_disciplina);

        printf("Pressione <Enter> para continuar...");
        scanf("%*c");

        fseek(stdin, 0, SEEK_END);
    }

//função alterar disciplina
    void alterar_disciplina() {
        char str_id_professor[10];
        int id_professor;

        FILE *arq_disciplina = fopen("disciplina.bin", "rb+");
        FILE *arq_professor = fopen("professor.bin", "rb+");

        if (arq_disciplina == NULL) {
            arq_disciplina = fopen("disciplina.bin", "wb+");
            if (arq_disciplina == NULL) {
                printf("\nFalha ao criar arquivo(s)!\n");
                exit(1);
            }
        }

        if (arq_professor == NULL) {
            arq_professor = fopen("professor.bin", "wb+");
            if (arq_professor == NULL) {
                printf("\nFalha ao criar arquivo(s)!\n");
                exit(1);
            }
        }

        printf("\nDigite o ID do professor: ");
        scanf("%10s%*c", str_id_professor);

        fseek(stdin, 0, SEEK_END);

        if (str_somente_numeros(str_id_professor) == 1) {
            sscanf(str_id_professor, "%d", &id_professor);

            if (existe_professor(arq_professor, id_professor)) {
                char str_id_disciplina[10];
                int id_disciplina;

                printf("\nDigite o ID da disciplina: ");
                scanf("%10s%*c", str_id_disciplina);

                fseek(stdin, 0, SEEK_END);

                if (str_somente_numeros(str_id_disciplina) == 1) {
                    sscanf(str_id_disciplina, "%d", &id_disciplina);

                    t_disciplina *disciplina = obter_disciplina(arq_disciplina, id_disciplina);

                    if (disciplina != NULL) {
                        printf("\nDigite o novo nome da disciplina: ");
                        scanf("%99[^\n]%*c", disciplina->nome);
                        printf("\nDigite a nova descricao da disciplina: ");
                        scanf("%99[^\n]%*c", disciplina->descricao);
                        printf("\nDigite o novo numero de creditos da disciplina: ");
                        scanf("%99[^\n]%*c", disciplina->num_creditos);
                        printf("\nDigite a nova carga horaria da disciplina: ");
                        scanf("%99[^\n]%*c", disciplina->carga_hora);
                        atualizar_disciplina(arq_disciplina, disciplina);

                        free(disciplina);
                    } else
                        printf("\nNao existe disciplina com o ID \"%d\".\n", id_disciplina);
                } else
                    printf("\nO ID so pode conter numeros!\n");
            } else
                printf("\nNao existe professor com o ID \"%d\".\n", id_professor);
        } else
            printf("\nO ID so pode conter numeros!\n");

        fclose(arq_professor);
        fclose(arq_disciplina);

        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");

        fseek(stdin, 0, SEEK_END);
    }

//função excluir disciplina
    void excluir_disciplina() {

        char str_id_disciplina[10];
        int id_disciplina;

        printf("\nDigite o ID da disciplina: ");
        scanf("%10s%*c", str_id_disciplina);

        fseek(stdin, 0, SEEK_END);

        if (str_somente_numeros(str_id_disciplina) == 1) {
            sscanf(str_id_disciplina, "%d", &id_disciplina);

            FILE *arq_disciplina = fopen("disciplina.bin", "rb");

            if (arq_disciplina == NULL) {
                printf("\nFalha ao abrir arquivo(s)!\n");
                exit(1);
            }

            if (existe_disciplina(arq_disciplina, id_disciplina) == 1) {
                char nome_disciplina[MAX];

                FILE *arq_temp = fopen("temp_disciplina.bin", "a+b");
                if (arq_temp == NULL) {
                    printf("\nFalha ao criar arquivo temporario!\n");
                    fclose(arq_disciplina);
                    exit(1);
                }
                rewind(arq_disciplina);

                t_disciplina disciplina;
                while (1){

                    size_t result = fread(&disciplina, sizeof(t_disciplina), 1, arq_disciplina);

                    if (result == 0)
                        break;

                    if (disciplina.id != id_disciplina) {
                        fwrite(&disciplina, sizeof(t_disciplina), 1, arq_temp);
                    } else
                        strcpy(nome_disciplina, disciplina.nome);
                }

                fclose(arq_disciplina);
                fclose(arq_temp);

                if (remove("disciplina.bin") != 0)
                    printf("\nErro ao deletar o arquivo \"disciplina.bin\"\n");
                else {
                    int r = rename("temp_disciplina.bin", "disciplina.bin");
                    if (r != 0) {
                        printf("\nPermissao negada para renomear o arquivo!\n");
                        printf("Feche esse programa bem como o arquivo \"temp_disciplinabin\" e renomeie manualmente para \"disciplina.bin\"\n");
                    } else
                        printf("\nDisciplina \"%s\" removido com sucesso!\n", nome_disciplina);
                }
            } else {
                fclose(arq_disciplina);
                printf("\nNao existe disciplina com o ID \"%d\".\n", id_disciplina);
            }
        } else
            printf("\nO ID so pode conter numeros!\n");

        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");
        fseek(stdin, 0, SEEK_END);
    }
// função para listar todos as disciplinas
    void listar_disciplina() {
        FILE *arq_disciplina = fopen("disciplina.bin", "rb");
        FILE *arq_professor = fopen("professor.bin", "rb");

        if (arq_disciplina == NULL) {
            printf("\nFalha ao abrir arquivo ou ");
            printf("Nenhuma disciplina cadastrado.\n");
            printf("\nPressione <Enter> para continuar...");
            scanf("%*c");

            fseek(stdin, 0, SEEK_END);
            return;
        }

        int encontrou_disciplina = 0;
        printf("\nListando todas as disciplinas...\n");
        t_disciplina disciplina;
        while (1) {

            size_t result = fread(&disciplina, sizeof(t_disciplina), 1, arq_disciplina);

            if (result == 0)
                break;

            encontrou_disciplina = 1;

            printf("\nDisciplina: \"%s\"", disciplina.nome);
            printf("\nDescricao:\"%s\"", disciplina.descricao);
            printf("\nNumero de creditos:\"%s\"", disciplina.num_creditos);
            printf("\nCarga horaria:\"%s\"", disciplina.carga_hora);

            if (disciplina.id_professor != -1) {

                if (arq_professor == NULL) {
                    printf("\nFalha ao abrir arquivo!\n");
                    fclose(arq_disciplina);
                    exit(1);
                }
                t_professor *professor = obter_professor(arq_professor, disciplina.id_professor);
                printf("Disciplina tem professor? Sim, professor: %s\n", professor->nome);
                free(professor);
            } else {
                printf("Disciplina tem professor? Nao\n");
            }
        }

        if (encontrou_disciplina == 0)
            printf("\nNenhuma disciplina cadastrada.\n");

        if (arq_professor != NULL)
            fclose(arq_professor);
        fclose(arq_disciplina);

        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");

        fseek(stdin, 0, SEEK_END);
    }

// função que obtém disciplina pelo ID
t_disciplina *obter_disciplina(FILE *arq_disciplina, int id_disciplina){

    rewind(arq_disciplina);

    t_disciplina *disciplina;

    disciplina = (t_disciplina*)malloc(sizeof(t_disciplina));
    while(1)
    {

        size_t result = fread(disciplina, sizeof(t_disciplina), 1, arq_disciplina);

        if(result == 0)
        {
            free(disciplina);
            return NULL;
        }
        if(disciplina->id == id_disciplina)
            break;
    }
    return disciplina;
}

// função para atualizar um professor recebe o ponteiro para o arquivo e o professor
void atualizar_disciplina(FILE *arq_disciplina, t_disciplina *arqd_atualizar){

    rewind(arq_disciplina);

    t_disciplina disciplina;
    while(1){

        size_t result = fread(&disciplina, sizeof(t_disciplina), 1, arq_disciplina);

        if(result == 0)
            break;

        if(disciplina.id == arqd_atualizar->id)
        {
            fseek(arq_disciplina, - sizeof(t_disciplina), SEEK_CUR);
            fwrite(arqd_atualizar, sizeof(t_disciplina), 1, arq_disciplina);
            break;
        }
    }
}
//função que verifica se o professor existe
int existe_disciplina(FILE *arq_disciplina, int id_disciplina) {
    rewind(arq_disciplina);

    t_disciplina disciplina;

    while (1) {
        size_t result = fread(&disciplina, sizeof(t_disciplina), 1, arq_disciplina);

        if (result == 0)
            break;

        if (disciplina.id == id_disciplina)
            return 1;
    }
}