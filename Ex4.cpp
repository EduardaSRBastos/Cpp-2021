#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define MAX_NAME 50
#define STAGES 15

typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;

typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;


typedef BTREE_NODE* BTREE;
typedef enum _BTREE_LOCATION { BTREE_LEFT, BTREE_RIGHT } BTREE_LOCATION;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)
#define EMPTY NULL
#define NO_LINK NULL

void printJogos_Second(BTREE Btree);
void GetWinnerHistory(BTREE Btree);
void SearchWinnerGames(char* winnerName, BTREE Btree);
int GetHeight(BTREE Btree);
void DadosJogosDisputados(BTREE Btree);
void printJogos(BTREE, int, int*, int*);
void DadosJogosDisputados(BTREE Btree);
void PrintTreeInOrder(BTREE Btree);
void GetQualifiersNumber(BTREE, int*);
void PrintNamesInOrder(BTREE);
STATUS ReadPlayersFromFile(void**, char*);
BTREE_NODE* NewBtreeNode(void* data);
BTREE_NODE* InitNode(void*, BTREE_NODE*, BTREE_NODE*);
BTREE_NODE* CreateBtree(void**, int, int);
void BtreeFree(BTREE);


int main(void)
{
	BTREE Btree;
	void* players[STAGES];
	char file_name[MAX_NAME] = "tournament.txt";
	
	if (ReadPlayersFromFile(players, file_name))
	{
		Btree = CreateBtree(players, 0, STAGES);
	setlocale(LC_ALL, "");	
int op=0;

		while (op != 11) 
		{
			puts("1 - Listar Paticipantes");
			puts("2 - Número de Eliminatórias");
			puts("3 - Jogos Disputados");
			puts("4 - Vencedor e os seus jogos");
			puts("11 - Sair");

			scanf("%d", &op);

			switch (op) 
			{
			case 1:
				PrintNamesInOrder(Btree);
   				printf("\n");
				break;
			
			case 2:
				{
				int qualifiersNumber = 0;
				GetQualifiersNumber(Btree, &qualifiersNumber);
				qualifiersNumber = qualifiersNumber / 2;
				printf("\nNúmero de eliminatórias: %d\n", qualifiersNumber);
   				 printf("\n");
				}
				
				break;	
			
			case 3:
				DadosJogosDisputados(Btree);
   				printf("\n");
				break;
				
			case 4:
				{
				GetWinnerHistory(Btree);
				}
				break;
			}
		}
	printf("\nA sair...\n");
    return 0;	
	system("pause");
	BtreeFree(Btree);
	}
	else
		printf("ERRO na leitura do ficheiro\n"); system("pause");
	return 0;
}

void GetWinnerHistory(BTREE Btree)
{

	char winnerName[30]; 
	strcpy(winnerName, ((PLAYER*)DATA(Btree))->name);
	printf("\nVencedor: %s\n\n", winnerName);

	SearchWinnerGames(winnerName, Btree);
}

void SearchWinnerGames(char* winnerName, BTREE Btree) {

	if (Btree != NULL) {
		if (RIGHT(Btree) != NULL && LEFT(Btree) != NULL) {

			if (!(strcmp(winnerName, ((PLAYER*)DATA(Btree))->name))) {
				printf("\n\nJogo: \n");
				printf("Nome: %s\t Sets: %d\n", ((PLAYER*)DATA(RIGHT(Btree)))->name, ((PLAYER*)DATA(RIGHT(Btree)))->sets);
				printf("Nome: %s\t Sets: %d\n", ((PLAYER*)DATA(LEFT(Btree)))->name, ((PLAYER*)DATA(LEFT(Btree)))->sets);
			}

			SearchWinnerGames(winnerName, LEFT(Btree));
			SearchWinnerGames(winnerName, RIGHT(Btree));
		}
	}
}

void DadosJogosDisputados(BTREE Btree)
{
	/*int height = GetHeight(Btree);
	int i = 0;
	int numJogadorDoJogoAtual = 0;
	int numJogo = 0;

	for (i = 1; i < height; i++) {
		printJogos(Btree, i, &numJogo, &numJogadorDoJogoAtual);
	}*/

	if (Btree != NULL) {
		printJogos_Second(Btree);
	}
}

void printJogos_Second(BTREE Btree) {

	if (RIGHT(Btree) != NULL && LEFT(Btree) != NULL) {
		printf("\n\nJogo: \n");
		printf("Nome: %s\t Sets: %d\n", ((PLAYER*)DATA(RIGHT(Btree)))->name, ((PLAYER*)DATA(RIGHT(Btree)))->sets);
		printf("Nome: %s\t Sets: %d\n", ((PLAYER*)DATA(LEFT(Btree)))->name, ((PLAYER*)DATA(LEFT(Btree)))->sets);

		printJogos_Second(RIGHT(Btree));
		printJogos_Second(LEFT(Btree));
	}
}

void printJogos(BTREE Btree, int nivel, int *numJogo, int * numJogadorDoJogoAtual) {

	if (Btree != NULL) {

		if (nivel == 1) {

			if ((*numJogo) == 0) {
				(*numJogo)++;
			}
			else {
				if ((*numJogadorDoJogoAtual) == 1) {
					(*numJogo)++;
					(*numJogadorDoJogoAtual)--;
				}
				else
				{
					printf("\n\nJogo %d", (*numJogo));
					(*numJogadorDoJogoAtual)++;
				}

				printf("\n%s vence %d sets.", ((PLAYER*)DATA(Btree))->name, ((PLAYER*)DATA(Btree))->sets);
			}

		}
		else if (nivel > 1) {
			printJogos(RIGHT(Btree), nivel - 1, numJogo, numJogadorDoJogoAtual);
			printJogos(LEFT(Btree), nivel - 1, numJogo, numJogadorDoJogoAtual);
		}
	}
}

int GetHeight(BTREE Btree) {

	int left = 0;
	int right = 0;

	if (Btree != NULL) {
		left = GetHeight(LEFT(Btree));
		right = GetHeight(RIGHT(Btree));
	}

	int tamanho = 0;

	if (left > right) {
		tamanho = left + 1;
	}
	else {
		tamanho = right + 1;
	}

	return tamanho;
}

void PrintTreeInOrder(BTREE Btree) {

	if (Btree != NULL) {
		PrintTreeInOrder(LEFT(Btree));
		printf("Name: %s\tSets: %d\n\n\n", ((PLAYER*)DATA(Btree))->name, ((PLAYER*)DATA(Btree))->sets);
		PrintTreeInOrder(RIGHT(Btree));
	}
}

void GetQualifiersNumber(BTREE Btree, int *qualifiersNumber) {

	if (Btree != NULL) {

		if (RIGHT(Btree) == NULL && LEFT(Btree) == NULL) {
			(*qualifiersNumber)++;
		}
		GetQualifiersNumber(LEFT(Btree), qualifiersNumber);
		GetQualifiersNumber(RIGHT(Btree), qualifiersNumber);
	}
}

void PrintNamesInOrder(BTREE Btree)
{
	if (Btree != NULL) {
		
		if (RIGHT(Btree) == NULL && LEFT(Btree) == NULL) {
			printf("Nome: %s\n", ((PLAYER*)DATA(Btree))->name);
		}
		PrintNamesInOrder(LEFT(Btree));
		PrintNamesInOrder(RIGHT(Btree));
	}
}

STATUS ReadPlayersFromFile(void** players, char* file_name)
{
	FILE* fp;
	int j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = malloc(sizeof(PLAYER))) != NULL)
			{
				fscanf(fp, "%[^;];", ((PLAYER*)ptr_data)->name);
				fscanf(fp, "%d\n", &(((PLAYER*)ptr_data)->sets));
				players[i] = ptr_data;
				i++;
			}
			else
			{
				for (j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}

BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}

BTREE_NODE* CreateBtree(void** v, int i, int size) {
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size),
			CreateBtree(v, 2 * i + 2, size)));
}

void BtreeFree(BTREE btree)
{
	if (btree != NULL)
	{
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(DATA(btree));
		free(btree);
	}
}
