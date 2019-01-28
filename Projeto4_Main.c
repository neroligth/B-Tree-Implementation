//Importa as bibliotecas da linguagem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#ifdef _WIN32
#define bool char
#define false 0
#define true 1
#endif

//Importa a biblioteca com a implementacao de Arvore B+
#include "AmittaiAviram.h"

//Importa as bibliotecas criadas pelo grupo
#include "Projeto4_Aluno.h"

//Define clear e cls para funcionar tanto em windows como em unix
#ifdef _unix_ 
#define clear "clear"
#else
#define clear "cls"
#endif

//Funcao menu para decisao do que sera realizado
int menu(){
	int op;
	system(clear);
	puts("+====================================+");
	puts("|               MENU                 |");
	puts("+====================================+");
	puts("[1] - Cadastrar Aluno");
	puts("[2] - Remover Aluno");
	puts("[3] - Exibir Lista de Alunos");
	puts("[4] - Resumo");
	puts("\n[0] - Encerrar o Programa\n");
	printf("Digite sua escolha: ");
	scanf("%d", &op);
	puts("");

	return op;
}

int main(void) {

	//Exibicao da licenca do uso do codigo da arvore
	license_notice();
	system("pause");

	//Declaracao de variaveis
	int op;
	int id = 1;
	node *raiz = NULL;

	//Inicio do programa propriamente dito;
	do{
		op = menu();
		switch(op){
			case 1:
				puts("+====================================+");
				puts("|          CADASTRAR ALUNO           |");
				puts("+====================================+");
				raiz = cadastrarAluno(raiz, &id);
				puts("");
				system("pause");
				break;
			case 2:
				puts("+====================================+");
				puts("|           REMOVER ALUNO            |");
				puts("+====================================+");
				raiz = removerAluno(raiz);
				puts("");
				system("pause");
				break;
			case 3:
				puts("+====================================+");
				puts("|      EXIBIR LISTA DE ALUNOS        |");
				puts("+====================================+");
				exibirListaAlunos(raiz);
				puts("");
				system("pause");
				break;
			case 4:
				puts("+====================================+");
				puts("|              RESUMO                |");
				puts("+====================================+");
				exibirResumo();
				puts("");
				system("pause");
				break;
			case 0:
				puts("+====================================+");
				puts("|            ENCERRAMENTO            |");
				puts("+====================================+");
				puts("O programa foi encerrado pelo usuario.");
				puts("");
				system("pause");
				getchar();
				break;
			default:
				puts("Comando invalido");
				break;
		}
	}while(op!=0);

	return 0;
}
