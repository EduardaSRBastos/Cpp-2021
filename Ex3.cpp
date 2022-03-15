#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>

//----GENERAL--------------------------
//-------------------------------------------
#define DATA_LENGTH 7
#define DATA(node) ((node)->pData)
#define LEFT(node) ((node)->pLeft)
#define RIGHT(node) ((node)->pRight)
#define EMPTY NULL
#define NO_LINK NULL
//-------------------------------------------
typedef enum _STATUS { OK, ERROR } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;


typedef struct _NO_DUPLO {
    void* idade;
}NO_DUPLO;


typedef struct _BTREE_NODE {
    void* pData;
    struct _BTREE_NODE* pLeft;
    struct _BTREE_NODE* pRight;
} BTREE_NODE;

typedef BTREE_NODE* BTREE;


//----FUNCTIONS------------------------------
//----BASE-----------------------------------
void freeLeftTree(BTREE_NODE* bt);
void freeRightTree(BTREE_NODE* bt);
void freeBTree(BTREE* bt);
int GetTreeDepth(BTREE bt);
void GetNodeNivel(BTREE bt, int nodeValue, int* nivel);
void CountLeafNumbers(BTREE bt, int* numLeafs);
void CountNodeNumberInOrder(BTREE bt, int *number);
void SearchByAgeInOrder(BTREE bt, int age);
void SearchByAgePostOrder(BTREE bt, int age);
void SearchByAgePreOrder(BTREE bt, int age);
void PrintTreePostOrder(BTREE bt);
void PrintTreePreOrder(BTREE bt);
void PrintTreeInOrder(BTREE bt);
void InsertValuesNoDuplo(int* values, void** idades);
BTREE_NODE* CreateBtree(void** idades, int i, int tamanho);
BTREE_NODE* InitNode(void* idade, BTREE_NODE* no_1, BTREE_NODE* no_2);
BTREE_NODE* NewBTreeNode(void* idade);

//-----------------------------------------//
STATUS initBTree(BTREE *);
BOOLEAN emptyBTree(BTREE);
BOOLEAN isLeaf(BTREE_NODE *);
STATUS createNewBTNode(BTREE_NODE **, void *);
void printIntBTree(BTREE);
STATUS insertIntBST(BTREE *, void *);
STATUS insertBT(BTREE *, void *, void *, void *);
//-----------------------------------------//


int main() {

    BTREE bt = NULL;
    int values[DATA_LENGTH] = { 10, 5, 25, 3, 8, 15, 30};
    void* idades[DATA_LENGTH];                           //Será preenchida com NO_DUPLO

	setlocale(LC_ALL, "");
    //Exercicio B
    InsertValuesNoDuplo(values, idades);   //Inserir valores no idades 
    bt = CreateBtree(idades, 0, DATA_LENGTH);
	
	int op=0;

		while (op != 11) 
		{
			puts("");
			puts("1 - Em Ordem");
			puts("2 - Pré Ordem");
			puts("3 - Pós Ordem");
			puts("4 - Pesquisar elemento (idade)");
			puts("5 - Contar número Nós");
			puts("6 - Contar número Folhas");
			puts("7 - Nível Nó");
			puts("8 - Profundidade Árvore");
			puts("11 - Sair");

			scanf("%d", &op);

			switch (op) 
			{
			case 1:
				PrintTreeInOrder(bt);
   				 printf("\n\n");
				break;
			
			case 2:
				PrintTreePreOrder(bt);
   				 printf("\n\n");
				break;	
			
			case 3:
				PrintTreePostOrder(bt);
   				 printf("\n\n");
				break;
				
			case 4:
				{
				printf("\nPesquisar idade:\n");
				int flag=3, ent=0;
				int nodeValue = 0;
    			int nivel = 0;
    			PrintTreeInOrder(bt);
   				printf("\n\n");
   				while(flag!=0)
   				{
					printf("Digite o elemento: ");
					scanf("%d", &nodeValue);
					for(int i =0;i<=DATA_LENGTH;i++)
					{
						if(nodeValue==values[i])
						{
	    					ent=2;
	    					flag=1;
						}
						else
							flag=0;
					}
					if(flag==0 && ent==0)
						printf("O valor não existe.\n");
				}
				if(ent==2)
				{
					SearchByAgeInOrder(bt, nodeValue);
	  				SearchByAgePostOrder(bt, nodeValue);
	   				SearchByAgePreOrder(bt, nodeValue);
				}
				}
				
				break;
				
			case 5:
				{
				int numNodes = 0;
  				CountNodeNumberInOrder(bt, &numNodes);
    			printf("\nNúmero de nós: %d\n", numNodes);
				}
				break;
				
			case 6:
				{
				int numLeafs = 0;
    			CountLeafNumbers(bt, &numLeafs);
    			printf("\nNúmero de folhas: %d\n", numLeafs);	
				}
				break;
				
			case 7:
				{
				int flag=3, ent=0;
				int nodeValue = 0;
    			int nivel = 0;
    			PrintTreeInOrder(bt);
   				printf("\n\n");
   				while(flag!=0)
   				{
					printf("Digite o elemento: ");
					scanf("%d", &nodeValue);
					for(int i =0;i<=DATA_LENGTH;i++)
					{
						if(nodeValue==values[i])
						{
	    					ent=2;
	    					flag=1;
						}
						else
							flag=0;
					}
					if(flag==0 && ent==0)
						printf("O valor não existe.\n");
				}
				if(ent==2)
	    			GetNodeNivel(bt, nodeValue, &nivel);
				}
				break;
				
			case 8:
				{
				int depth = GetTreeDepth(bt);
    			printf("\nProfundidade: %d\n", depth);	
				}
    			break;
			}
		}
	printf("\nA sair...\n");
    return 0;	
}

//Exercício de Eliminar Nós
//    freeBTree(&bt);
//    PrintTreeInOrder(bt);
void freeBTree(BTREE* bt) {
    
    if (bt != NULL) {
        freeLeftTree(LEFT(*bt));
        freeRightTree(RIGHT(*bt));
        
        //Elimina Raiz
        free((*bt)->pData);
        free(*bt);
    }

}

void freeRightTree(BTREE_NODE* bt) {
    
    if (bt != NULL) {
        freeRightTree(LEFT(bt));
        freeRightTree(RIGHT(bt));
        free(bt->pData);
        free(bt);
    }

}

void freeLeftTree(BTREE_NODE* bt) {
    
    if (bt != NULL) {
        freeLeftTree(LEFT(bt));
        freeLeftTree(RIGHT(bt));
        free(bt->pData);
        free(bt);
    }
}

int GetTreeDepth(BTREE bt) {
    
    int depth = 0;
    int left = 0, right = 0;

    if (bt != NULL) {
        left = GetTreeDepth(LEFT(bt));
        right = GetTreeDepth(RIGHT(bt));
        depth = 1 + ((left > right) ? left : right);
    }

    return depth;
}

void GetNodeNivel(BTREE bt, int nodeValue, int *nivel) {

    if (bt != NULL) {
       // if (LEFT(bt) != NULL || RIGHT(bt) != NULL) {
           // (*nivel)++;
        //}

        if (*(int*)((NO_DUPLO*)bt)->idade == nodeValue) {
            printf("Encontrado no nivel %d.\n", *nivel);
        }
         (*nivel)++;
		 GetNodeNivel(LEFT(bt), nodeValue, nivel);
		  (*nivel)++;
        GetNodeNivel(RIGHT(bt), nodeValue, nivel);
        (*nivel)--;
    }
    else
     (*nivel)--;
}

void CountLeafNumbers(BTREE bt, int* numLeafs) {

    if (bt != NULL) {

        if (LEFT(bt) == NULL && RIGHT(bt) == NULL) {
            (*numLeafs)++;
        }
        CountLeafNumbers(LEFT(bt), numLeafs);
        CountLeafNumbers(RIGHT(bt), numLeafs);
    }
}

void CountNodeNumberInOrder(BTREE bt, int *number) {

    if (bt != NULL) {
        (*number)++;
        CountNodeNumberInOrder(LEFT(bt), number);
        CountNodeNumberInOrder(RIGHT(bt), number);
    }
}

void SearchByAgePostOrder(BTREE bt, int age) {

    int i = 0;

    if (bt != NULL && i != 1) {
        SearchByAgePostOrder(LEFT(bt), age);
        SearchByAgePostOrder(RIGHT(bt), age);

        if (*(int*)((NO_DUPLO*)bt)->idade == age) {
            printf("Encontrado com PostOrder\n\n");
            i = 1;  //Flag que permite parar de procurar
        }
    }

    return;
}

void SearchByAgePreOrder(BTREE bt, int age) {

    int i = 0;

    if (bt != NULL && i != 1) {

        if (*(int*)((NO_DUPLO*)bt)->idade == age) {
            printf("Encontrado com PreOrder\n\n");
            i = 1;  //Flag que permite parar de procurar
        }

        SearchByAgePreOrder(LEFT(bt), age);
        SearchByAgePreOrder(RIGHT(bt), age);
    }

    return;
}

void SearchByAgeInOrder(BTREE bt, int age) {

    int i = 0;

    if (bt != NULL && i != 1) {
        SearchByAgeInOrder(LEFT(bt), age);

        if (*(int*)((NO_DUPLO*)bt)->idade == age) {
            printf("Encontrado com InOrder\n\n");
            i = 1;  //Flag que permite parar de procurar
        }
        
        SearchByAgeInOrder(RIGHT(bt), age);
    }

    return;
}

void PrintTreePostOrder(BTREE bt) {
    if (bt != NULL) {
        PrintTreePostOrder(LEFT(bt));
        PrintTreePostOrder(RIGHT(bt));
        printf("%d ", *(int*)((NO_DUPLO*)bt)->idade);
    }
}

void PrintTreePreOrder(BTREE bt) {
    if (bt != NULL) {
        printf("%d ", *(int*)((NO_DUPLO*)bt)->idade);
        PrintTreePreOrder(LEFT(bt));
        PrintTreePreOrder(RIGHT(bt));
    }
}

void PrintTreeInOrder(BTREE bt) {

    if (bt != NULL) {
        PrintTreeInOrder(LEFT(bt));
        printf("%d ", *(int*)((NO_DUPLO*)bt)->idade);
        PrintTreeInOrder(RIGHT(bt));
    }
}

void InsertValuesNoDuplo(int* values, void **idades) {

    int i = 0;
    void* ptr_data;

    for (i = 0; i < DATA_LENGTH; i++) {
        if ((ptr_data = malloc(sizeof(NO_DUPLO))) != NULL) {
            ((NO_DUPLO*)ptr_data)->idade = (void*)values[i];

            idades[i] = ptr_data;
        }
    }
}

BTREE_NODE* CreateBtree(void** idades, int i, int tamanho) {

    if (i >= tamanho) {
        return NULL;
    }
    else {
        return (InitNode(*(idades + i), CreateBtree(idades, 2 * i + 1, tamanho), CreateBtree(idades, 2 * i + 2, tamanho)));
    }
}

BTREE_NODE* InitNode(void* idade, BTREE_NODE *no_1, BTREE_NODE *no_2) {

    BTREE_NODE* node = NULL;

    node = NewBTreeNode(idade);
    node->pLeft = no_1;
    node->pRight = no_2;

    return node;
}

BTREE_NODE* NewBTreeNode(void* idade) {

    BTREE_NODE* node;

    if ((node = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL) {
        ((BTREE_NODE*)node)->pData = idade;
        ((BTREE_NODE*)node)->pLeft = NULL;
        ((BTREE_NODE*)node)->pRight = NULL;

        return node;
    }

    return NULL;
}

//-----------------------------------------//
STATUS initBTree(BTREE *pBT)
{
*pBT=NULL;
return OK;
}

BOOLEAN emptyBTree(BTREE BT)
{
return (BT==NULL)? TRUE : FALSE;
}

BOOLEAN isLeaf(BTREE_NODE *pBT)
{
return ((LEFT(pBT)==NULL) && (RIGHT(pBT)==NULL))? TRUE : FALSE;
}

STATUS createNewBTNode(BTREE_NODE **pNew, void *pData)
{
BTREE_NODE *pTemp;
if((pTemp=(BTREE_NODE *)malloc(sizeof(BTREE_NODE)))==NULL)
return ERROR;
*pNew=pTemp;
DATA(pTemp)=pData;
LEFT(pTemp)=NULL;
RIGHT(pTemp)=NULL;
return OK;
}

void printIntBTree(BTREE BT)
{
if(emptyBTree(BT)==TRUE) return;
printIntBTree(LEFT(BT));
printf("%d, ",*(int *)DATA(BT));
printIntBTree(RIGHT(BT));
return;
}

STATUS insertIntBST(BTREE *pBT, void *pData)
{
if(emptyBTree(*pBT))
{
BTREE_NODE *pNew;
if(createNewBTNode(&pNew,pData)==ERROR)
return ERROR;
*pBT=pNew;
return OK;
}
else if(*(int *)(pData) < *(int *)(DATA(*pBT)))
insertIntBST(&(LEFT(*pBT)),pData);
else insertIntBST(&(RIGHT(*pBT)),pData);
return OK;
}
