//Definicao da estrutura aluno
typedef struct aluno {
	int id;
	char nome[20];
	char email[40];
	int idade;
	char status;
} aluno;

//Definicao dos prototipos dasfuncoes
aluno * recebeInfoAluno(int id);
node * cadastrarAluno(node *raiz, int *id);
node * removerAluno(node *raiz);
void exibirListaAlunos(node *raiz);
void exibirResumo();
int insereRegistro(aluno *aux);
void inativaRegistro(int rid);
void exibirRegistro(int rid);

//Funcao que recebe as informacoes do aluno
aluno * recebeInfoAluno(int id){
	aluno *novo;

	novo = (aluno *) malloc(sizeof(aluno));

	//Limpa o buffer
	getchar();

	printf("Digite o nome do aluno: ");
	scanf("%[^\n]", novo->nome);

	//Limpa o buffer
	getchar();

	printf("Digite o email do aluno: ");
	scanf("%[^\n]", novo->email);

	printf("Digite a idade do aluno: ");
	scanf("%d", &novo->idade);

	novo->id = id;
	novo->status = 'A';

	return novo;
}

//Funcao principal de cadastro de aluno
node * cadastrarAluno(node *raiz, int *id){
	//Declaracao de variaveis
	aluno *novo;
	int rid;

	//Envia o valor do id do novo registro que sera inserido
	novo = recebeInfoAluno(*id);

	//Exibe o ID do aluno ao usuario
	printf("ID do Aluno: %d\n", novo->id);

	//Avanca o valor do id
	*id = *id + 1;

	//Insere no arquivo do banco de dados (TXT)
	rid = insereRegistro(novo);

	//Insere o registro na arvore
	raiz = insert(raiz, novo->id, rid);

	return raiz;
}

//Funcao principal de remocao de aluno
node * removerAluno(node *raiz){
	//Declaracao de variaveis
	int id;
	record *registro = NULL;
	node *noFolha = NULL;

	//Recebendo o ID do aluno
	printf("Digite o ID do aluno que deseja remover: ");
	scanf("%d", &id);

	//Buscando o ID e recebendo a linha que se encontra o registro
	//Envia raiz, id do Aluno, false e a posicao de um ponteiro do node da folha que sera apagado
	registro = find(raiz, id, false, &noFolha);

	//Verifica se o registro existe
	if (registro == NULL){
		printf("Nenhum aluno com o ID digitado.\n");
	}
	else {
		//Inativa o registro no arquivo
		inativaRegistro(registro->value);

		//Deleta o registro na arvore
		raiz = delete_entry(raiz, noFolha, id, registro);
	}

	return raiz;
}

//Funcao que exibe os registros ativos dos alunos
void exibirListaAlunos(node *raiz){
	//Declaracao de variaveis
	node *aux = raiz;
	int i;
	record *registro = NULL;

	//Verifica se a arvore esta vazia
	if (raiz == NULL) {
        printf("Nenhum aluno registrado.\n");
    }
    else{
    	//Percorrendo a arvore para chegar na primeira folha
    	while(!aux->is_leaf){
    		aux = aux->pointers[0];
    	}

    	while(true){

    		for(i=0; i < aux->num_keys; i++){
    			//Exibe o registro do aluno
    			registro = (record *) aux->pointers[i];
    			exibirRegistro(registro->value);
    		
    			//Exibindo o ID para teste
    			printf(" %d) ", aux->keys[i]);
    		}

    		if (aux->pointers[order - 1] != NULL) {
		        printf(" | ");
		        aux = aux->pointers[order - 1];
		    }
	        else
	            break;
    	}

    	printf("\n");
    }
}

//Funcao que exibe o resumo
void exibirResumo(){
	puts("Funcionalidade nao implementada.");
}

//Funcao que insere um registro no arquivo
int insereRegistro(aluno *aux){
	return 0;
}

//Funcao que inativa uma linha do arquivo
void inativaRegistro(int rid){
	return;
}

//Funcao que exibe o registro de um aluno
void exibirRegistro(int rid){
	printf("(%d", rid);
}
