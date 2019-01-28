//Definicao da estrutura aluno
typedef struct aluno {
	int id;
	char nome[20];
	char email[40];
	int idade;
	char status;
} aluno;

//Definicao dos prototipos das funcoes
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

	//Variaveis auxiliares de leitura
	int Linha=0, linha=0, id=0, x=0, idade;
	char nome[100], email[100], status;

	//Abrindo arquivo em questão
	FILE * Arquivo;

	Arquivo = fopen("bd.txt", "a+");
	if(Arquivo != NULL){

		rewind(Arquivo);
		while(!feof(Arquivo)){
			x = fscanf(Arquivo, "%d %d %s %d %s %c\n", &Linha, &id, nome, &idade, email, &status);
			if(x > 0){
				linha++;
			}
		}
		linha++;
		x = fprintf(Arquivo, "%d %d %s %d %s %c\n", linha, aux->id, aux->nome, aux->idade, aux->email, 'A');

		if(x < 0){
			puts("+====================================+");
			puts("|  !! ERROR: Dados nao registrado !! |");
			puts("+====================================+");
		}
		else{
			puts("\n> DADOS REGISTRADOS COM SUCESSO!");
		}
		fclose(Arquivo);
	}
	else{
		puts("+====================================+");
		puts("| !! ERROR: Arquivo nao encontrado ! |");
		puts("+====================================+");
	}

	return linha;
	return 0;
}

//Funcao que inativa uma linha do arquivo
void inativaRegistro(int rid){
	char oldname[] = "bd.txt";
	char newname[] = "temp.txt";

 //Abre o arquivo atual de registros
 FILE *Ler = fopen("db.txt","r");
 //Abre o arquivo auxiliar de registros
 FILE *Novo = fopen("temp.txt","w+");

 //Variaveis auxiliares de leitura
 int Linha=0, linha=0, id=0, x=0, idade, Status;
 char nome[100], email[100], status;

 //Se o arquivo existir
 if(Ler != NULL){
	 rewind(Ler);

	 //laço para percorrer todo o arquivo
	 while(!feof(Ler)){
		 //leitura dos dados do  arquivo atual de registros
		 x = fscanf(Ler, "%d %d %s %d %s %c\n", &Linha, &id, nome, &idade, email, &status);

		 //Verifica se a leitura foi bem sucedida
		 if(x > 0){

			 //verifica se a linha lida é a desejada
			 if(Linha == rid){
				 Status = 1;
				 //Imprime o registro atualizado no novo arquivo
				 fprintf(Novo,"%d %d %s %d %s %c\n",linha, id, nome, idade, email, 'I');
			 }
			 else{
				 //Copia o registro para o novo arquivo
				 fprintf(Novo,"%d %d %s %d %s %c\n",linha, id, nome, idade, email, 'I');
			 }
		 }
	 }

	 int status;
 }

 else{
	 //caso o arquivo não exista
	 puts("ERRO: Não foi possível abrir os registros!\n");
	 return;
 }

 //fecha os arquivos abertos
 fclose(Ler);
 fclose(Novo);


 //remoção dos registros antigos
 Status = remove("temp.txt");
 //renomeia o registro auxiliar para o nome padrão
 Status = rename(oldname, newname);

 //caso a remoção seja bem sucedida
 if(Status == 0)
	 return;

 else{
	 //caso ocorra algum erro na remoção dos registros antigos
	 puts("\nNão foi possível remover o registro no arquivo!\n");
	 return;
 }

}

//Funcao que exibe o registro de um aluno
void exibirRegistro(int rid){
	printf("(%d", rid);
}
