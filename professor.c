#ifdef __WIN32
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif

#include "disciplina.h"
#include "professor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// função que verifica se uma string contém somente números
int str_somente_numeros(char str[])
{
    int len_str = strlen(str);

    for(int i = 0; i < len_str; i++)
    {
        if(str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

// função que obtém um professor pelo ID
t_professor *obter_professor(FILE *arq_professor, int id_professor){

    rewind(arq_professor);

    t_professor *professor;

    professor = (t_professor *)malloc(sizeof(t_professor));
    while(1)
    {

        size_t result = fread(professor, sizeof(t_professor), 1, arq_professor);

        if(result == 0)
        {
            free(professor);
            return NULL;
        }

        if(professor->id == id_professor)
            break;
    }
    return professor;
}

// função para atualizar um professor
void atualizar_professor(FILE *arq_professor, t_professor *arqp_atualizar)
{
    rewind(arq_professor);

    t_professor professor;
    while(1){

        size_t result = fread(&professor, sizeof(t_professor), 1, arq_professor);

        if(result == 0)
            break;

        if(professor.id == arqp_atualizar->id)
        {
            fseek(arq_professor, - sizeof(t_professor), SEEK_CUR);
            fwrite(arqp_atualizar, sizeof(t_professor), 1, arq_professor);
            break;
        }
    }
}
//função que verifica se o professor existe
int existe_professor(FILE *arq_professor, int id_professor){

    rewind(arq_professor);

    t_professor professor;

    while(1){

        size_t result = fread(&professor, sizeof(t_professor), 1, arq_professor);

        if(result == 0)
            break;

        if(professor.id == id_professor)
            return 1;
    }

    return 0;
}

//função cadastrar professor
void cadastrar_professor()
{
    FILE *arq_professor = fopen("professor.bin", "a+b");

    if(arq_professor == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)!\n");
        exit(1);
    }
    int cont_bytes = 0;

    fseek(arq_professor, 0, SEEK_END);
    cont_bytes = ftell(arq_professor);

    t_professor professor;

    if(cont_bytes == 0)
    {
        professor.id = 1;
    }
    else
    {
        t_professor ultimo_professor;

        fseek(arq_professor, cont_bytes - sizeof(t_professor), SEEK_SET);

        fread(&ultimo_professor, sizeof(t_professor), 1, arq_professor);

        professor.id = ultimo_professor.id + 1;
    }

        printf("\nDigite o nome do professor: ");
        gets(professor.nome);
        printf("\nDigite o rg do professor: ");
        scanf("%50s%*c", professor.rg);
        printf("\nDigite o cpf do professor: ");
        scanf("%50s%*c", professor.cpf);
        printf("\nDigite o endereco do professor: ");
        gets(professor.endereco);
        printf("\nDigite o salario do professor: ");
        scanf("%50s%*c", professor.salario);
        printf("\nDigite a data de nascimento do professor: ");
        scanf("%50s%*c", professor.data_nasc);

    fseek(stdin, 0, SEEK_END);
    fseek(arq_professor, 0, SEEK_END);
    fwrite(&professor, sizeof(t_professor), 1, arq_professor);

    fclose(arq_professor);
    system(limpar_tela);

    printf("\nProfessor \"%s\" cadastrado com sucesso!\n", professor.nome);
    printf("\nRg:\"%s\"\n", professor.rg);
    printf("\nCpf:\"%s\"\n", professor.cpf);
    printf("\nEndereco:\"%s\"\n", professor.endereco);
    printf("\nSalario:\"%s\"\n", professor.salario);
    printf("\nData de nascimento: \"%s\"\n", professor.data_nasc);
    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}

//função listar professor
void listar_professor()
{
    FILE *arq_professor = fopen("professor.bin", "rb");

    if(arq_professor == NULL)
    {
        printf("\nFalha ao abrir arquivo(s) ou ");
        printf("Nenhum professor cadastrado.\n");
        printf("\nPressione <Enter> para continuar...");
        scanf("%*c");

        fseek(stdin, 0, SEEK_END);
        return;
    }

    int encontrou_professor = 0;
    t_professor professor;

    printf("\nListando todos os professores...\n");
    while(1)
    {
        size_t result = fread(&professor, sizeof(t_professor), 1, arq_professor);

        if(result == 0)
            break;

        encontrou_professor = 1;

        printf("\nID do professor: %d\n", professor.id);
        printf("Nome do professor: %s\n", professor.nome);
        printf("Rg do professor: %s\n", professor.rg);
        printf("Cpf do professor: %s\n", professor.cpf);
        printf("endereco do professor: %s\n", professor.endereco);
        printf("salario do professor: %s\n", professor.salario);
        printf("data de nascimento do professor: %s\n", professor.data_nasc);

    }

    if(encontrou_professor == 0)
        printf("\nNenhum professor cadastrado.\n");

    fclose(arq_professor);

    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}

//função pesquisar professor
void pesquisar_professor(){

    char nome[MAX];

    int encontrou_professor = 0;

    FILE *arq_professor = fopen("professor.bin", "rb");

    if(arq_professor == NULL)
    {
        printf("\nFalha ao abrir arquivo(s)!\n");
        exit(1);
    }

    printf("\nDigite o nome do professor: ");
    gets(nome);

    printf("\n Professores com o nome \"%s\":\n\n", nome);

    t_professor professor;
    while(1)
    {
        size_t result = fread(&professor, sizeof(t_professor), 1, arq_professor);

        if(result == 0)
            break;

        char nome_aux[MAX];
        strcpy(nome_aux, professor.nome);

        if(strcmp(strupr(nome_aux), strupr(nome)) == 0){

            printf("ID do professor: %d\n\n", professor.id);
            printf("Rg do professor: %s\n", professor.rg);
            printf("Cpf do professor: %s\n", professor.cpf);
            printf("endereco do professor: %s\n", professor.endereco);
            printf("salario do professor: %s\n", professor.salario);
            printf("data de nascimento do professor: %s\n", professor.data_nasc);
            encontrou_professor = 1;
        }
    }

    if(encontrou_professor == 0)
        printf("Nenhum professor encontrado.\n\n");

    fclose(arq_professor);
    printf("Pressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}

//função alterar professor
void alterar_professor()
{
    char str_id_professor[10];
    int id_professor;

    FILE *arq_professor = fopen("professor.bin", "rb+");

    if(arq_professor == NULL)
    {
        arq_professor = fopen("professor.bin", "wb+");
        if(arq_professor == NULL)
        {
            printf("\nFalha ao criar arquivo(s)!\n");
            exit(1);
        }
    }

    printf("\nDigite o ID do professor: ");
    scanf("%10s%*c", str_id_professor);

    fseek(stdin, 0, SEEK_END);

    if(str_somente_numeros(str_id_professor) == 1){

        sscanf(str_id_professor, "%d", &id_professor);

        if(existe_professor(arq_professor, id_professor))
        {

            if(str_somente_numeros(str_id_professor) == 1){

                sscanf(str_id_professor, "%d", &id_professor);

                t_professor *professor = obter_professor(arq_professor, id_professor);

                if(professor != NULL)
                {
                    printf("\nDigite o novo nome do professor: ");
                    gets(professor->nome);
                    printf("\nDigite o novo rg do professor: ");
                    scanf("%99[^\n]%*c", professor->rg);
                    printf("\nDigite o novo cpf do professor: ");
                    scanf("%10s%*c", professor->cpf);
                    printf("\nDigite o novo endereco do professor: ");
                    scanf("%99[^\n]%*c", professor->endereco);
                    printf("\nDigite o salario do professor: ");
                    scanf("%99[^\n]%*c", professor->salario);
                    printf("\nDigite a data de nascimento do professor: ");
                    scanf("%10s%*c", professor->data_nasc);
                    atualizar_professor(arq_professor, professor);

                    free(professor);
                }
                else
                    printf("\nNao existe disciplina com o ID \"%d\".\n", id_professor);
            }
            else
                printf("\nO ID so pode conter numeros!\n");
        }
    }
    fclose(arq_professor);

    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}
//função excluir professor
void excluir_professor(){

    char str_id_professor[10];
    int id_professor;

    printf("\nDigite o ID do professor: ");
    scanf("%10s%*c", str_id_professor);

    fseek(stdin, 0, SEEK_END);

    if(str_somente_numeros(str_id_professor) == 1){

        sscanf(str_id_professor, "%d", &id_professor);

        FILE *arq_professor = fopen("professor.bin", "rb");

        if(arq_professor == NULL)
        {
            printf("\nFalha ao abrir arquivo(s)!\n");
            exit(1);
        }

        if(existe_professor(arq_professor, id_professor) == 1)
        {
            char nome_professor[MAX];
            FILE *arq_temp = fopen("temp_professor.bin", "a+b");
            if(arq_temp == NULL)
            {
                printf("\nFalha ao criar arquivo temporario!\n");
                fclose(arq_professor);
                exit(1);
            }
            rewind(arq_professor);

            t_professor professor;
            while(1){

                size_t result = fread(&professor, sizeof(t_professor), 1, arq_professor);

                if(result == 0)
                    break;

                if(professor.id != id_professor)
                {
                    fwrite(&professor, sizeof(t_professor), 1, arq_temp);
                }
                else
                    strcpy(nome_professor, professor.nome);
            }

            fclose(arq_professor);
            fclose(arq_temp);

            if(remove("professor.bin") != 0)
                printf("\nErro ao deletar o arquivo \"professor.bin\"\n");
            else
            {
                int r = rename("temp_professor.bin", "professor.bin");
                if(r != 0)
                {
                    printf("\nPermissao negada para renomear o arquivo!\n");
                    printf("Feche esse programa bem como o arquivo \"temp_professor.bin\" e renomeie manualmente para \"professor.bin\"\n");
                }
                else
                    printf("\nProfessor \"%s\" removido com sucesso!\n", nome_professor);
            }
        }
        else
        {
            fclose(arq_professor);
            printf("\nNao existe professor com o ID \"%d\".\n", id_professor);
        }
    }
    else
        printf("\nO ID so pode conter numeros!\n");

    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");
    fseek(stdin, 0, SEEK_END);
}

//lista todas as disciplinas lecionadas por um professor
void disciplinas_de_um_professor(){

    char str_id_professor[10];
    int id_professor;

    FILE *arq_disciplina = fopen("disciplina.bin", "rb");
    FILE *arq_professor = fopen("professor.bin", "rb");

    if(arq_disciplina == NULL){
        arq_disciplina = fopen("disciplina.bin", "wb+");
        if(arq_disciplina == NULL){
            printf("\nFalha ao criar arquivo(s)!\n");
            exit(1);
        }
    }

    if(arq_professor == NULL){
        arq_professor = fopen("professor.bin", "wb+");
        if(arq_professor == NULL)
        {
            printf("\nFalha ao criar arquivo(s)!\n");
            exit(1);
        }
    }

    printf("\nDigite o ID do professor: ");
    scanf("%10s%*c", str_id_professor);

    if(str_somente_numeros(str_id_professor) == 1){

        sscanf(str_id_professor, "%d", &id_professor);

        if(existe_professor(arq_professor, id_professor))
        {
            int encontrou_disciplina = 0;
            t_disciplina disciplina;


                while(1)
                {
                    size_t result = fread(&disciplina, sizeof(t_disciplina), 1, arq_disciplina);

                    if(result == 0)
                        break;

                    encontrou_disciplina= 1;

                    printf("\nID da disciplina: %d\n", disciplina.id);
                    printf("Nome da disciplina: %s\n", disciplina.nome);
                    printf("Descricao da disciplina: %s\n", disciplina.descricao);
                    printf("Numero de creditos da disciplina %s\n", disciplina.num_creditos);
                    printf("Carga horaria da disciplina: %s\n", disciplina.carga_hora);
                }
            printf("\nListando todas as disciplinas de um professor...\n");

            if(encontrou_disciplina == 0)
                printf("\nNenhuma disciplina cadastrada.\n");
        }else
            printf("\nNao existe professor com o ID \"%d\".\n", id_professor);
    }else
        printf("\nO ID so pode conter numeros!\n");

    fclose(arq_professor);
    fclose(arq_disciplina);

    printf("\nPressione <Enter> para continuar...");
    scanf("%*c");

    fseek(stdin, 0, SEEK_END);
}