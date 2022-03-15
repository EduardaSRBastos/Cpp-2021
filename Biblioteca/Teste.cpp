#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>

typedef enum _STATUS {ERROR,OK} STATUS;

typedef enum _BOOLEAN {FALSE,TRUE} BOOLEAN;

#define MAX 20

typedef struct _LIVRO{

   char     autor[MAX], titulo[MAX];

   int      stock, iva, paginas;

   float    preco;

}LIVRO;

typedef struct _LIST_NODE

{

  void * data;

  struct _LIST_NODE * next;

} LIST_NODE;

typedef LIST_NODE * LIST;
#define DATA(node) ((node)->data)

#define NEXT(node) ((node)->next)

STATUS RemoveLivro(LIST list_livros);
STATUS InsertEnd(LIST* list, void* data);


void ShowLivros(LIST list);

STATUS ReadLivros(LIST* list, const char* filename);

LIVRO* ProcuraLivro(LIST list, char* titulo);


void FreeList(LIST* list);
void RemoveFirstNode(LIST* list);
STATUS RemoveChoosedNode(LIST list, LIST* node);


STATUS SaveLivros(LIST list, const char* filename);

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

STATUS RemoveEnd(LIST* list, void* data)
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

STATUS ReadLivros(LIST* list, const char* filename);
void ShowLivros(LIST list);
int main()
{
   LIST lista = NULL;

   if (ReadLivros(&lista, "bd.txt") == OK)
	{
	if ((RemoveLivro(lista) == OK))
					puts("Livro removido com sucesso.");
				else
					puts("Erro a remover o livro.");
}
   return 1;
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
		
		if (((ptr_data = (LIVRO*)malloc(sizeof(LIVRO))) != NULL) && (InsertEnd(list, ptr_data) == OK))
		{
			fscanf(fp, "%[^;];%[^;];%d;%d;%d;%f;\n", ptr_data->autor, ptr_data->titulo, &(ptr_data->stock),&(ptr_data->iva), &(ptr_data->paginas), &(ptr_data->preco));
		
		}
		else
			return ERROR;
	}
	fclose(fp);

	return(OK);
}

void ShowLivros(LIST list)
{
	setlocale(LC_ALL, "");
	float aux = 0;
	int pos=0;
	printf("LIVROS ->\n");
	while (list != NULL)
	{
		printf(" %s;%s;%d;%d;%d;%f \n", ((LIVRO*)DATA(list))->autor,((LIVRO*)DATA(list))->titulo,((LIVRO*)DATA(list))->stock,((LIVRO*)DATA(list))->iva,((LIVRO*)DATA(list))->paginas,((LIVRO*)DATA(list))->preco);
		if(((LIVRO*)DATA(list))->preco > aux)
			{
			aux=((LIVRO*)DATA(list))->preco;
			pos++;
		}
			
		list = NEXT(list);
	}
	printf(" Preco maior: %f na posicao %d.", aux, pos);
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


STATUS SaveLivros(LIST list, const char* filename)
{
    FILE* fp;
    setlocale(LC_ALL, "");

    if ((fp = fopen(filename, "w")) == NULL)
        return(ERROR);

    while (list != NULL)
    {
        fprintf(" %s;%s;%d;%d;%d;%f \n", ((LIVRO*)DATA(list))->autor,((LIVRO*)DATA(list))->titulo,((LIVRO*)DATA(list))->stock,((LIVRO*)DATA(list))->iva,((LIVRO*)DATA(list))->paginas,((LIVRO*)DATA(list))->preco);
        list = NEXT(list);
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

STATUS RemoveLivro(LIST list_livros) {

    char titulo[100];
    LIST* ptr_livro;
    setlocale(LC_ALL, "");


    puts("Qual o título do livro?");
    scanf("%s", titulo);

    ptr_livro = (LIST*)ProcuraLivro(list_livros, titulo);


    if (RemoveChoosedNode(list_livros, ptr_livro) == OK) {
        if (SaveLivros(list_livros, "bd.txt") == OK) {
            return(OK);
        }
    }

    return ERROR;

}






