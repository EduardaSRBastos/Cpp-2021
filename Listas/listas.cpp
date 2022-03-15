#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef struct _LIST_NODE
{
void * data;
struct _LIST_NODE * next;
} LIST_NODE;
typedef LIST_NODE * LIST;
typedef struct Livro
{
char titulo[60];
char autor[30];
bool emprestimo;
}
Livro;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
typedef enum _STATUS { OK, ERROR } STATUS;
#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)
#define EMPTY NULL
#define NO_LINK NULL
void initList(LIST *list);
BOOLEAN emptyList(LIST list);
LIST_NODE * NewNode(void * data);
STATUS InsertIni(LIST *list, void *data);
STATUS InsertEnd(LIST *list, void *data);
int ListSize(LIST list);
void ShowValues(LIST list);


int main()
{
LIST list = NULL;
Livro *ptr_livro;
Livro livro1, livro2;
char titulo_aux[90];
char autor_aux[90];
int emprest_aux=0;
strcpy(livro1.titulo, "Os Meninos de Ouro");
strcpy(livro1.autor, "Agustina Bessa-Luis");
livro1.emprestimo=true;
strcpy(livro2.titulo, "Os Sonhos de Einstein");
strcpy(livro2.autor, "Alan Lightman");
livro2.emprestimo=true;
if (InsertIni(&list, &livro1) == ERROR)
{
printf("\nErro na alocacao de memoria\n");
printf("\n<Prima qualquer tecla>\n");
getch();
exit(1);
}
if (InsertIni(&list, &livro2) == ERROR)
{
printf("\nErro na alocacao de memoria\n");
printf("\n<Prima qualquer tecla>\n");
getch();
exit(1);
}
printf("\n");
printf("\nTamanho = %d\n", ListSize(list));
printf("Livros:\n");
ShowValues(list);
printf("\n");
ptr_livro = (Livro *)malloc(sizeof(Livro));
printf("Introduza o titulo do livro: ");
fflush(stdout);
scanf("%s", &(ptr_livro->titulo));
printf("Introduza o autor do livro: ");
fflush(stdout);
scanf("%s", &(ptr_livro->autor));
printf("O livro foi requisitado? 1=Sim; 2=Nao: ");
scanf("%d", &(emprest_aux));
if(emprest_aux==1)
{
	(ptr_livro->emprestimo=true);
}
else
{
	(ptr_livro->emprestimo=false);
}
if (InsertEnd(&list, ptr_livro) == ERROR)
{
printf("\nErro na alocacao de memoria\n");
printf("\n<Prima qualquer tecla>\n");
getch();
exit(1);
}
printf("\n");
printf("\nTamanho = %d\n", ListSize(list));
printf("Livros:\n");
ShowValues(list);
printf("\n");
strcpy(((Livro *)DATA(list))->titulo, "Desconhecido 1");
strcpy(((Livro *)DATA(list))->autor, "Desconhecido 2");
((Livro *)DATA(list))->emprestimo=true;
printf("\n");
printf("\nTamanho = %d\n", ListSize(list));
printf("Livro:\n");
ShowValues(list);
printf("\n");

return 0;
}


void initList(LIST *list)
{
*list = NULL;
}


BOOLEAN emptyList(LIST list)
{
return (list == NULL) ? TRUE : FALSE;
}


LIST_NODE *NewNode(void *data)
{
LIST_NODE *new_node;
if ((new_node = (LIST_NODE *)malloc(sizeof(LIST_NODE))) != NULL)
{
DATA(new_node) = data;
NEXT(new_node) = NULL;
}
return(new_node);
}


STATUS InsertIni(LIST *list, void *data)
{
LIST_NODE *new_node;
if ((new_node = NewNode(data)) != NULL)
{
NEXT(new_node) = *list;
*list = new_node;
return OK;
}
return ERROR;
}


STATUS InsertEnd(LIST *list, void *data)
{
LIST_NODE *new_node, *temp;
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


void ShowValues(LIST list)
{
if (emptyList(list) == TRUE)
{
printf("\nLista vazia.\n");
return;
}
printf("LISTA ->");
while (list != NULL)
{
printf(" %s; %s; %d ->", ((Livro *)DATA(list))->titulo, ((Livro *)DATA(list))->autor, ((Livro *)DATA(list))->emprestimo);
list = NEXT(list);
}
printf(" FIM\n");
}

