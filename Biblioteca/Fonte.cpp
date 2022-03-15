// lixo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>

typedef struct _LIST_NODE
{
	void* data;
	struct _LIST_NODE* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
typedef enum _STATUS { OK, ERROR } STATUS;

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)
#define EMPTY NULL
#define NO_LINK NULL

typedef struct _LIVRO
{
	char autor[30], titulo[30];
	BOOLEAN estado;
}LIVRO;

typedef struct _SOCIO
{
	char nome[30];
	int num;
	LIVRO* req;
}SOCIO;

void initList(LIST* list);
BOOLEAN emptyList(LIST list);
LIST_NODE* NewNode(void* data);

STATUS InsertIni(LIST* list, void* data);
STATUS InsertEnd(LIST* list, void* data);

int ListSize(LIST list);

void ShowSocios(LIST list);
void ShowLivros(LIST list);

STATUS ReadSocios(LIST* list, LIST livros, const char* filename);
STATUS ReadLivros(LIST* list, const char* filename);

LIVRO* ProcuraLivro(LIST list, char* titulo);
SOCIO* ProcuraSocio(LIST list, int num);


void FreeList(LIST* list);
void RemoveFirstNode(LIST* list);
STATUS RemoveChoosedNode(LIST list, LIST* node);


STATUS SaveLivros(LIST list, const char* filename);
STATUS SaveSocios(LIST list, const char* filename);

STATUS AddLivro(LIST* list, const char* filename);
STATUS AddSocio(LIST* list, const char* filename);

STATUS RemoveSocio(LIST list_socios);
STATUS RemoveLivro(LIST list_livros);

STATUS RequisitarLivro(LIST list_socios,LIST list_livros);
STATUS EntregarLivro(LIST list_socios, LIST list_livros);

//-----------------------------EXTRA--------------------------------

STATUS Somar(LIST* list, LIST livros, const char* filename);


/****************************************************************
* Programa principal
***************************************************************/
int main()
{
	LIST socios = NULL;
	LIST livros = NULL;
	
	setlocale(LC_ALL, "");

	if (ReadLivros(&livros, "livros.txt") == OK && ReadSocios(&socios, livros, "socios.txt") == OK)
	{
		int op=0;

		while (op != 11) {

			puts("");
			puts("1 - Adicionar livro");
			puts("2 - Mostrar livros");
			puts("3 - Adicionar sócio");
			puts("4 - Mostrar sócios + Soma nr");
			puts("5 - Remover livro");
			puts("6 - Remover sócio");
			puts("7 - Procurar estado do sócio");
			puts("8 - Procurar estado do livro");
			puts("9 - Requisitar um livro");
			puts("10 - Entregar um livro");
			puts("11 - Sair");

			scanf("%d", &op);

			switch (op) {
			case 1:
				if ((AddLivro(&livros, "livros.txt")) == OK)
					puts("Adicionado com sucesso.");
				else
					puts("Erro a adicionar.");

				break;
			
			case 2:
				ShowLivros(livros);	
				break;
			case 3:
				if ((AddSocio(&socios, "socios.txt")) == OK)
					puts("Adicionado com sucesso.");
				else
					puts("Erro a adicionar.");

				break;
			case 4:
				ShowSocios(socios);
				Somar(&socios, livros, "socios.txt");
				break;
			case 5:
				if ((RemoveLivro(livros) == OK))
					puts("Livro removido com sucesso.");
				else
					puts("Erro a remover o livro.");
				break;
			case 6:
				if ((RemoveSocio(socios) == OK))
					puts("Sócio removido com sucesso.");
				else
					puts("Erro a remover o sócio.");

				break;
			case 7:
				int tempNum;
				SOCIO* tempSocio;

				puts("Qual o número do sócio?");
				scanf("%d", &tempNum);

				tempSocio = ProcuraSocio(socios, tempNum);

				

				if ( tempSocio == NULL)
					puts("Erro a encontrar o sócio.");
				else
					if(tempSocio->req == NULL)
						printf("Sócio nao tem livro requisitado.");
					else
						printf("Sócio tem livro requisitado.");


				break;
			case 8:
				char titulo[100];
				LIVRO* tempLivro;

				puts("Qual o título do livro?");
				scanf("%s", titulo);

				tempLivro = ProcuraLivro(livros, titulo);



				if (tempLivro == NULL)
					puts("Erro a encontrar o livro");
				else
					if (tempLivro->estado == NULL)
						printf("Livro disponível.");
					else
						printf("Livro requisitado.");

				break;
			case 9:
				if(RequisitarLivro(socios, livros) == OK)
					puts("Livro requisitado com sucesso.");
				else
					puts("Erro ao requisitar o livro.");

				break;
			case 10:
				if(EntregarLivro(socios, livros) == OK)
					puts("Livro entregue com sucesso.");
				else
					puts("Erro ao entregar o livro.");
				break;
			}

		}

		if (SaveLivros(livros, "livros.txt") == OK && SaveSocios(socios,"socios.txt") == OK) {
			printf("OK");
		}
		else
			printf("Erro");

		FreeList(&socios);
		FreeList(&livros);

	}
	else
		printf("ERRO na abertura do ficheiro\n");
	return 1;
}

//-----------------------------------------------------EXTRA-----------------------------------------------------------

STATUS Somar(LIST* list, LIST livros, const char* filename)
{
	SOCIO* ptr_data;
	FILE* fp;
	char aux[20];
	setlocale(LC_ALL, "");
	
	int soma=0;

	if ((fp = fopen(filename, "r")) == NULL)
		return(ERROR);

	while (!feof(fp))
	{
		if (((ptr_data = (SOCIO*)malloc(sizeof(SOCIO))) != NULL) && (InsertEnd(list, ptr_data) == OK))
		{
			fscanf(fp, "%[^;];%d;%[^;];\n", ptr_data->nome, &(ptr_data->num), aux);
			soma+=ptr_data->num;
			if (!strcmp(aux, "NULL"))
				ptr_data->req = NULL;
			else
				ptr_data->req = ProcuraLivro(livros, aux);
		}
		else
			return ERROR;
	}
	fclose(fp);
	printf("\n\nSOMA = %d",soma);
	return(OK);
}

//-----------------------------------------------------FIM EXTRA-----------------------------------------------------------

STATUS EntregarLivro(LIST list_socios, LIST list_livros) {

	int tempNum;
	SOCIO* tempSocio;
	setlocale(LC_ALL, "");

	puts("Qual o número do sócio?");
	scanf("%d", &tempNum);

	tempSocio = ProcuraSocio(list_socios, tempNum);

	if (tempSocio == NULL) {
		puts("Erro a encontrar o sócio.");
		return ERROR;
	}
	else if (tempSocio->req == NULL) {
		puts("Sócio não requisitou livros.");
		return ERROR;
	}
	else
		if (tempSocio->req != NULL) {
			char titulo[100];
			LIVRO* tempLivro;

			puts("Qual o título do livro?");
			scanf("%s", titulo);

			tempLivro = ProcuraLivro(list_livros, titulo);

			if (tempLivro == NULL) {
				puts("Erro a encontrar o livro.");
				return ERROR;
			}
			else
				if (tempLivro->estado != NULL) {
					tempSocio->req = NULL;
					tempLivro->estado = FALSE;
					return OK;
				}
				else {
					puts("Livro não requisitado.");
					return ERROR;
				}

		}
		else{
			puts("Sócio não tem livro requisitado.");
			return ERROR;
		}
}

STATUS SaveSocios(LIST list, const char* filename)
{
	FILE* fp;
	setlocale(LC_ALL, "");

	if ((fp = fopen(filename, "w")) == NULL)
		return(ERROR);

	while (list != NULL)
	{
		fprintf(fp, "%s;%d;", ((SOCIO*)DATA(list))->nome, ((SOCIO*)DATA(list))->num);
		if (((SOCIO*)DATA(list))->req == NULL)
			fprintf(fp, "NULL;\n");
		else
			fprintf(fp, "%s;\n", ((SOCIO*)DATA(list))->req->titulo);
		list = NEXT(list);
	}

	fclose(fp);
	return(OK);

}

STATUS SaveLivros(LIST list, const char* filename)
{
	FILE* fp;
	setlocale(LC_ALL, "");

	if ((fp = fopen(filename, "w")) == NULL)
		return(ERROR);

	while (list != NULL)
	{
		fprintf(fp, "%s;%s;", ((LIVRO*)(list)->data)->autor, ((LIVRO*)DATA(list))->titulo);
		if (((LIVRO*)DATA(list))->estado == TRUE)
			fprintf(fp, "1;\n");
		else
			fprintf(fp, "0;\n");
		list = NEXT(list);
	}

	fclose(fp);
	return(OK);

}

void FreeList(LIST* list) {
	while (*list != NULL)
		RemoveFirstNode(list);
}

void RemoveFirstNode(LIST* list) {

	LIST_NODE* node;

	node = NEXT(*list);
	free(DATA(*list));
	free(*list);
	*list = node;

}


STATUS RemoveChoosedNode(LIST list, LIST* node) {

	LIST* temp = &list;

	while (temp != NULL)
	{
		if (NEXT(*temp)->data == node) {
			NEXT(*temp) = NEXT(*temp)->next;
			free(node); 
			return OK;

		}
		*temp = NEXT(*temp);
		
	}

	return ERROR;
}

STATUS AddLivro(LIST* list, const char* filename) {

	LIVRO* ptr_data;
	setlocale(LC_ALL, "");

	if (((ptr_data = (LIVRO*)malloc(sizeof(LIVRO))) != NULL) && (InsertEnd(list, ptr_data) == OK))
	{
		puts("Qual o nome do autor?");
		scanf("%s", ptr_data->autor);

		puts("Qual o título do livro?");
		scanf("%s", ptr_data->titulo);

		ptr_data->estado = FALSE;

		if (SaveLivros(*list, "livros.txt") == OK) {
			return(OK);
		}
		else
			return(ERROR);

	}
	else
		return(ERROR);


}

STATUS AddSocio(LIST* list, const char* filename) {

	SOCIO* ptr_data;
	setlocale(LC_ALL, "");

	if (((ptr_data = (SOCIO*)malloc(sizeof(SOCIO))) != NULL) && (InsertEnd(list, ptr_data) == OK))
	{
		puts("Qual o nome?");
		scanf("%s", ptr_data->nome);

		puts("Qual o número?");
		scanf("%d", &ptr_data->num);

		ptr_data->req = NULL;

		if (SaveSocios(*list, "socios.txt") == OK) {
			return(OK);
		}
		else
			return(ERROR);

	}
	else
		return(ERROR);


}

STATUS RemoveSocio(LIST list_socios) {

	int num;
	LIST* ptr_socio;
	setlocale(LC_ALL, "");

		puts("Qual o número do sócio?");
		scanf("%d", &num);

		ptr_socio = (LIST*)ProcuraSocio(list_socios, num);


		if (RemoveChoosedNode(list_socios, ptr_socio) == OK) {
			if (SaveSocios(list_socios, "socios.txt") == OK) {
				return(OK);
			}
		}
			
		return ERROR;

}

STATUS RemoveLivro(LIST list_livros) {

	char titulo[100];
	LIST* ptr_livro;
	setlocale(LC_ALL, "");


	puts("Qual o título do livro?");
	scanf("%s", titulo);

	ptr_livro = (LIST*)ProcuraLivro(list_livros, titulo);


	if (RemoveChoosedNode(list_livros, ptr_livro) == OK) {
		if (SaveLivros(list_livros, "livros.txt") == OK) {
			return(OK);
		}
	}

	return ERROR;

}

STATUS ReadLivros(LIST* list, const char* filename)
{
	LIVRO* ptr_data;
	FILE* fp;
	int aux;
	setlocale(LC_ALL, "");

	if ((fp = fopen(filename, "r")) == NULL)
		return(ERROR);

	while (!feof(fp))
	{
		// aloca se um quadrado do tipo livro e adiciona se ao fim da lista que ainda está vazia na primeira iteração
		// na segunda faz se o mesmo e vai se adicionando à lista até acabar o ficheiro
		if (((ptr_data = (LIVRO*)malloc(sizeof(LIVRO))) != NULL) && (InsertEnd(list, ptr_data) == OK))
		{
			// guarda se os dados no quadrado
			fscanf(fp, "%[^;];%[^;];%d;\n", ptr_data->autor, ptr_data->titulo, &aux);
			if (aux == 0)
				ptr_data->estado = FALSE;
			else
				ptr_data->estado = TRUE;
		}
		else
			return ERROR;
	}
	fclose(fp);

	return(OK);
}

STATUS ReadSocios(LIST* list, LIST livros, const char* filename)
{
	SOCIO* ptr_data;
	FILE* fp;
	char aux[20];
	setlocale(LC_ALL, "");

	if ((fp = fopen(filename, "r")) == NULL)
		return(ERROR);

	while (!feof(fp))
	{
		if (((ptr_data = (SOCIO*)malloc(sizeof(SOCIO))) != NULL) && (InsertEnd(list, ptr_data) == OK))
		{
			fscanf(fp, "%[^;];%d;%[^;];\n", ptr_data->nome, &(ptr_data->num), aux);
			if (!strcmp(aux, "NULL"))
				ptr_data->req = NULL;
			else
				ptr_data->req = ProcuraLivro(livros, aux);
		}
		else
			return ERROR;
	}
	fclose(fp);

	return(OK);
}

LIVRO* ProcuraLivro(LIST list, char* titulo)
{
	while (list != NULL)
	{

		if (!strcmp(((LIVRO*)DATA(list))->titulo, titulo))
			return (LIVRO*)DATA(list);
		list = NEXT(list);
	}
	return NULL;
}

SOCIO* ProcuraSocio(LIST list, int num)
{
	while (list != NULL)
	{
		if (((SOCIO*)DATA(list))->num == num)
			return (SOCIO*)DATA(list);
		list = NEXT(list);
	}
	return NULL;
}

STATUS RequisitarLivro(LIST list_socios, LIST list_livros) {

	int tempNum;
	SOCIO* tempSocio;
	setlocale(LC_ALL, "");

	puts("Qual o número do sócio?");
	scanf("%d", &tempNum);

	tempSocio = ProcuraSocio(list_socios, tempNum);

	if (tempSocio == NULL) {
		puts("Erro a encontrar o sócio.");
		return ERROR;
	}
	else if (tempSocio->req != NULL) {
		puts("Sócio tem requisição ativa.");
		return ERROR;
	}
	else
		if (tempSocio->req == NULL) {
			char titulo[100];
			LIVRO* tempLivro;

			puts("Qual o título do livro?");
			scanf("%s", titulo);

			tempLivro = ProcuraLivro(list_livros, titulo);


			if (tempLivro == NULL) {
				puts("Erro a encontrar o livro.");
				return ERROR;
			}
			else
				if (tempLivro->estado == NULL) {
					tempSocio->req = tempLivro;
					tempLivro->estado = TRUE;
					return OK;
				}
				else {
					puts("Livro requisitado");
					return ERROR;
				}

		}
		else{
			puts("Sócio tem livro requisitado");
			return ERROR;
		}
}


/****************************************************************
* Funcao: Inicializa a lista
*
* Parametros: list - apontador para lista
* (duplo apontador para o primeiro no')
* Saida: void
***************************************************************/
void initList(LIST* list)
{
	*list = NULL;
}
/****************************************************************
* Funcao: verifica se a lista é vazia
*
* Parametros: list - apontador para lista
* Saida: TRUE se a lista for vazia, ERROR caso contrário
***************************************************************/
BOOLEAN emptyList(LIST list)
{
	return (list == NULL) ? TRUE : FALSE;
}
/****************************************************************
* Funcao: Cria um no'
*
* Parametros: data - apontador generico para os dados a inserir no no' criado
* Saida: apontador para o no' criado ou NULL em caso de erro
***************************************************************/
LIST_NODE* NewNode(void* data)
{
	LIST_NODE* new_node;
	if ((new_node = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL)
	{
		DATA(new_node) = data;
		NEXT(new_node) = NULL;
	}
	return(new_node);
}

/****************************************************************
* Funcao: Insere um no' no inicio da lista
*
* Parametros: list - apontador para lista
* (duplo apontador para o primeiro no')
* data - apontador generico para os dados a inserir no no' criado
* Saida: OK se o nó foi inserido na LISTA e ERROR caso contrário
***************************************************************/
STATUS InsertIni(LIST* list, void* data)
{
	LIST_NODE* new_node;
	if ((new_node = NewNode(data)) != NULL)
	{
		NEXT(new_node) = *list;
		*list = new_node;
		return OK;
	}
	return ERROR;
}
/****************************************************************
* Funcao: Insere um no' no fim da lista
*
* Parametros: list - apontador para lista
* (duplo apontador para o primeiro no')
* data - apontador generico para os dados a inserir no no' criado
* Saida: OK se o nó foi inserido na LISTA e ERROR caso contrário
***************************************************************/
STATUS InsertEnd(LIST* list, void* data)
{
	LIST_NODE* new_node, * temp;
	if ((new_node = NewNode(data)) != NULL)
	{
		if (*list == NULL)
			*list = new_node;
		else
		{
			temp = *list;
			while (NEXT(temp) != NULL)
				temp = NEXT(temp);
			NEXT(temp) = new_node;
		}
		return(OK);
	}
	return(ERROR);
}

/***************************************************************************
* Funcao: calcula quantos elementos contem a lista
*
* Parametros: list - apontador para uma lista
* Saida: numero de elementos da lista
***************************************************************************/
int ListSize(LIST list)
{
	int count = 0;
	while (list != NULL)
	{
		count++;
		list = NEXT(list);
	}
	return count;
}
/****************************************************************
* Funcao: Escreve no ecra o conteudo da lista
*
* Parametros: list - apontador para o primeiro no'
* Saida: void
***************************************************************/
void ShowLivros(LIST list)
{
	setlocale(LC_ALL, "");

	printf("LIVROS ->\n");
	while (list != NULL)
	{
		printf(" %s;%s -> ", ((LIVRO*)DATA(list))->autor, ((LIVRO*)DATA(list))->titulo);
		if (((LIVRO*)DATA(list))->estado == TRUE)
			printf("Requisitado\n");
		else
			printf("Disponível\n");
		list = NEXT(list);
	}
	printf(" FIM");
}

void ShowSocios(LIST list)
{
	setlocale(LC_ALL, "");
	
	printf("SÓCIOS ->\n");
	while (list != NULL)
	{
		printf(" %s;%d -> ", ((SOCIO*)DATA(list))->nome, ((SOCIO*)DATA(list))->num);
		if (((SOCIO*)DATA(list))->req == NULL)
			printf("Não tem livro requisitado.\n");
		else
			printf("%s\n", ((SOCIO*)DATA(list))->req->titulo);
		list = NEXT(list);
	}
	printf(" FIM");
}
