#ifdef __WIN32
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif
#include "professor.h"
#include "disciplina.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

char menu_professor();
char menu_disciplina();
char menu1();
char menu2();

// main para menu

int main()
{
    char op;


    printf("\n------------------------------ SISTEMA IFCE ------------------------------\n");
    printf("\n\n1 - Ir para aba professor\n");
    printf("2 - Ir para aba disciplina\n");
    printf("Digite o numero da opcao: \n");
    scanf("%c", &op);
    system(limpar_tela);

    while (op != 0){
        switch (op) {
            case '1':
            {
                menu1();
                break;
            }
            case '2':
            {
                menu2();
                break;
            }
            default:{
                printf("\nOpcao invalida! Pressione <Enter> para continuar...");
                scanf("%*c");
                fseek(stdin, 0, SEEK_END);
                main();
            }
        }
    }

    printf("\nFim do programa\n");
    return 0;
}

// função que exibe o menu
char menu_professor()
{
    char respo[2];

    printf("------------------------------ SISTEMA IFCE ------------------------------");
    printf("\n\n1 - Cadastrar um professor\n");
    printf("2 - Listar todos os professores\n");
    printf("3 - Pesquisar professor\n");
    printf("4 - Alterar professor\n");
    printf("5 - Excluir professor\n");
    printf("6 - Listar disciplinas de um professor\n");
    printf("7 - Voltar para menu\n");
    printf("0 - Sair do programa\n");
    printf("Digite o numero da opcao: ");
    scanf("%1s%*c", respo);

    fseek(stdin, 0, SEEK_END);
    return respo[0];
}

// função que exibe o menu
char menu_disciplina()
{
    char resp[2];

    printf("------------------------------ SISTEMA IFCE ------------------------------");
    printf("\n\n1 - Cadastrar uma disciplina\n");
    printf("2 - Ligar professor a disciplina\n");
    printf("3 - Listar todas as disciplinas\n");
    printf("4 - Pesquisar disciplina\n");
    printf("5 - Alterar disciplina\n");
    printf("6 - Excluir disciplina\n");
    printf("7 - Voltar para menu\n");
    printf("0 - Sair do programa\n");
    printf("Digite o numero da opcao: ");
    scanf("%1s%*c", resp);

    fseek(stdin, 0, SEEK_END);

    return resp[0];
}

// função que retorna a opção escolhida pelo usuário
char menu1(){

    char respo;

    while(1)
    {
        respo = menu_professor();

        if(respo == '1')
            cadastrar_professor();
        else if(respo == '2')
            listar_professor();
        else if(respo == '3')
            pesquisar_professor();
        else if(respo == '4')
            alterar_professor();
        else if(respo == '5')
            excluir_professor();
        else if(respo == '6')
            disciplinas_de_um_professor();
        else if(respo == '7')
            main();
        else if(respo == '0')
            exit(1);
        else
        {
            printf("\nOpcao invalida! Pressione <Enter> para continuar...");
            scanf("%*c");
            fseek(stdin, 0, SEEK_END);
        }
        system(limpar_tela);
    }
}

// função que retorna a opção escolhida pelo usuário
char menu2(){

    char resp;

    while(1)
    {
        resp = menu_disciplina();

        if(resp == '1')
            cadastrar_disciplina();
        else if(resp == '2')
            professor_da_disciplina();
        else if(resp == '3')
            listar_disciplina();
        else if(resp == '4')
            pesquisar_disciplina();
        else if(resp == '5')
            alterar_disciplina();
        else if(resp == '6')
            excluir_disciplina();
        else if(resp == '7')
            main();
        else if(resp == '0')
            exit(1);
        else
        {
            printf("\nOpcao invalida! Pressione <Enter> para continuar...");
            scanf("%*c");
            fseek(stdin, 0, SEEK_END);
        }
        system(limpar_tela);
    }
}