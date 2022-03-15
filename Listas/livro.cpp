#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct _LIST_NODE
{
void * data;
struct _LIST_NODE * next;
} LIST_NODE;
typedef LIST_NODE * LIST;

typedef struct _Livro
{
char Titulo[60];
char Autor[30];
int Estado;
}
Livro;

typedef struct _Socio 
{
	char Nome[80];
	int Numero;
	Livro *Requisitado;
}Socio;
	
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
typedef enum _STATUS { OK, ERROR } STATUS;
#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)
#define EMPTY NULL
#define NO_LINK NULL
void initList(LIST *list);
BOOLEAN emptyList(LIST list);
void RemoveFirstNode(LIST *list);
LIST_NODE * NewNode(void * data);
STATUS InsertIni(LIST *list, void *data);
STATUS InsertEnd(LIST *list, void *data);
int ListSize(LIST list);
void ShowValues(LIST list);
void FreeList(LIST* list);

STATUS ReadLivros(LIST* list, const char* filename);
STATUS WriteLivros(LIST* list, const char* filename);
void ShowLivros(LIST list);
STATUS ReadSocios(LIST* list, const char* filename);
void ShowSocios(LIST list);
void ReservarLivro(LIST list);
void EntregarLivro(LIST listLivro, LIST listSocio);
void AcrescentarLivro(LIST list);
void RemoverLivro(LIST list);
void AcrescentarSocio(LIST list);
void RemoverSocio(LIST list);
void EstadoLivro(LIST list);
void EstadoSocio(LIST listLivro, LIST listSocio);

int main()
{
LIST Livro_list = NULL;
LIST Socio_list = NULL;

while(true)
	{
		setlocale(LC_ALL, "");
		system("cls");
		printf("\nAlgoritmia Exercício 1");
		printf("\n\t------------------------------");
		printf("\n\t 1. Carregar Dados");
		printf("\n\t 2. Reservar Livro");
		printf("\n\t 3. Entregar Livro");
		printf("\n\t 4. Acrescentar Livro");
		printf("\n\t 5. Remover Livro");
		printf("\n\t 6. Acrescentar Sócio");
		printf("\n\t 7. Remover Sócio");
		printf("\n\t 8. Estado Livro");
		printf("\n\t 9. Estado Sócio");
		
		printf("\n\n Opção Número: ");
			
		switch(getch())
		{
			case '1' :system("cls");
					  	if (ReadLivros(&Livro_list, "livros.txt") == OK)
						{	
							ShowLivros(Livro_list);
						}
						else printf("Erro na abertura do ficheiro de Livros\n");
							
						if (ReadSocios(&Socio_list, "socios.txt") == OK)
						{	
							ShowSocios(Socio_list);
						}
						else printf("Erro na abertura do ficheiro de Socios\n");
					  system("pause");
					  break;
					  
			case '2' :system("cls");
					  ReservarLivro(Livro_list);
					  system("pause");
					  break;
			case '3' :system("cls");
					  EntregarLivro(Livro_list, Socio_list);
					  system("pause");
					  break;	
			case '4' :system("cls");
					  AcrescentarLivro(Livro_list);
					  system("pause");
					  break;
			case '5' :system("cls");
					  RemoverLivro(Livro_list);
					  system("pause");
					  break;
			case '6' :system("cls");
					  AcrescentarSocio(Socio_list);
					  system("pause");
					  break;
			case '7' :system("cls");
					  RemoverSocio(Socio_list);
					  system("pause");
					  break;
			case '8' :system("cls");
					  EstadoLivro(Livro_list);
					  system("pause");
					  break;	
			case '9' :system("cls");
					  EstadoSocio(Livro_list, Socio_list);
					  system("pause");
					  break;		  	  		  		  
			
		}
	}
	FreeList(&Socio_list);			
	FreeList(&Livro_list);			
	system("pause");
	return 0;
}

void EstadoSocio(LIST listLivro, LIST listSocio)
{
	setlocale(LC_ALL, "");
	int reserva = 1;
		system("cls");
		ShowSocios(listSocio);
		
		char NomeTemp[80];
		do{
	    		printf("\n\tNome do Sócio: ('sair' para Voltar) ");
				scanf (" %[^\n]%*c", NomeTemp);
				if(strcmp("sair", NomeTemp) ==  0)
				break;
	    		while (listSocio)
	  			{ 
	    		if(strcmp(((Socio*)DATA(listSocio))->Nome, NomeTemp) ==  0)
	    		{
	    			if(((Livro*)DATA(listLivro))->Estado != 0)  
	    			{		
		    			printf("Esse Sócio tem livro reservado!\n");
		    			system("PAUSE");
		    			break;
		    			reserva = 0;
		    			
	    			}
	    			else
	    			{
	    				printf("Esse Sócio não tem livro reservado!\n");
	    				system("PAUSE");
	    				break;
	    				reserva = 0;
	    				
	    			}
				}	    				    		
	    		else if(reserva == 1)	
				{
					printf("Sócio Não Encontrado! Tente Novamente!\n");
					system("PAUSE");
					break;
				}   
				listSocio = NEXT(listSocio);
				}	
	}while(reserva == 0);			
}

void EstadoLivro(LIST listLivro)
{
	setlocale(LC_ALL, "");
	int reserva = 1;
		system("cls");
		ShowLivros(listLivro);
		
		char NomeTemp[80];
		do{
	    		printf("\n\tTítulo do Livro: ('sair' para Voltar) ");
				scanf (" %[^\n]%*c", NomeTemp);
				if(strcmp("sair", NomeTemp) ==  0)
				break;
	    		while (listLivro)
	  			{ 
	    		if(strcmp(((Livro*)DATA(listLivro))->Titulo, NomeTemp) ==  0)
	    		{
	    			if(((Livro*)DATA(listLivro))->Estado != 0)  
	    			{		
		    			printf("Esse Livro está reservado!\n");
		    			system("PAUSE");
		    			break;
		    			reserva = 0;
		    			
	    			}
	    			else
	    			{
	    				printf("Esse Livro não está reservado!\n");
	    				system("PAUSE");
	    				break;
	    				reserva = 0;
	    				
	    			}
				}	    				    		
	    		else if(reserva == 1)	
				{
					printf("Livro Não Encontrado! Tente Novamente!\n");
					system("PAUSE");
					break;
				}   
				listLivro = NEXT(listLivro);
				}	
	}while(reserva == 0);			
}

void RemoverSocio(LIST list)
{
	setlocale(LC_ALL, "");
	int reserva = 0;
	
		system("cls");
		ShowSocios(list);
		char NomeTemp[80];
		printf("\n\tNome: ('sair' para Voltar) ");
		scanf ("%[^\n]%*c", NomeTemp);
		if(strcmp("sair", NomeTemp) ==  0)
			break;	
    do{
			
				if(strcmp(((Socio*)DATA(list))->Nome, NomeTemp) ==  0)
		    	{
				while (list)
			    {   	
			    	FILE* fp;
					Socio* pt;
					fpos_t pos;
		    string line;
		
		    ifstream fin;
		    fin.open("socios.txt");
		    ofstream temp;
		    temp.open("temp.txt");
		
		    while (getline(fin, line))
		    {
		        string id(line.begin(), line.begin() + line.find(";"));
				if (id != NomeTemp)
		   		temp << line << endl;
		    }
		
		    temp.close();
		    fin.close();
		    remove("socios.txt");
		    rename("temp.txt", "socios.txt");
					ShowLivros(list);
						printf("Sócio Encontrado!\n");
					break;
				reserva=1;
					}		    				    		
	    		else if(reserva == 0)	
				{
					break;
				
				}
			else printf("Erro na abertura do ficheiro de Sócios\n");
	          
		list = NEXT(list);	
		}   
	}while(reserva == 0);
}

void AcrescentarSocio(LIST list)
{
	setlocale(LC_ALL, "");
	int reserva = 0;
	do{
		system("cls");
		ShowSocios(list);
		char NomeTemp[60];
		int flag=0;
		int num=1;
		printf("\n\tNome: ('sair' para Voltar) ");
		scanf ("%[^\n]%*c", NomeTemp);
		printf("\n\tNúmero: ('0' para Voltar) ");
		scanf ("%d", &num);
		if(strcmp("sair", NomeTemp) ==  0 || num ==  0)
			break;
		printf("\n\t'%s' e '%d' está correto? ('1' para sim, '0' para não) ", NomeTemp, num);
		scanf("%d",&flag);
		if(flag==1)
		{
			strcpy(((Socio*)DATA(list))->Nome, NomeTemp);
			((Socio*)DATA(list))->Numero= num;
			FILE* fp;
			Socio* pt;
			if ((fp = fopen("socios.txt", "a")) != NULL)
			{
	
				fprintf(fp, "\n%s;%d", ((Socio*)DATA(list))->Nome, ((Socio*)DATA(list))->Numero);	
					fclose(fp);
					ShowSocios(list);
			}
			else printf("Erro na abertura do ficheiro de Sócios\n");
			
			break;	
			reserva=1;		
		}
		else if(flag==0)
		{
			printf("Tente Novamente!\n");
					system("PAUSE");
					break;
		}
		
	}
	while(reserva==0);			
}

void RemoverLivro(LIST list)
{
	setlocale(LC_ALL, "");
	int reserva = 0;
	do{
		system("cls");
		ShowLivros(list);
		char NomeTemp[80];
		printf("\n\tTítulo do Livro: ('sair' para Voltar) ");
		scanf ("%[^\n]%*c", NomeTemp);
		if(strcmp("sair", NomeTemp) ==  0)
			break;
	
		while (list)
	    {   	
	    	FILE* fp;
			Livro* pt;
			fpos_t pos;
				if ((fp = fopen("livros.txt", "a")) != NULL)
				{
				if(strcmp(((Livro*)DATA(list))->Titulo, NomeTemp) ==  0)
		    		{
					fseek ( fp , 0 , SEEK_SET );
					printf("agf");
  					fprintf ( fp,"AHHH");
					fclose(fp);
					ShowLivros(list);
					
					break;
				reserva=1;
					}		    				    		
	    		else if(reserva == 0)	
				{
					printf("Livro Não Encontrado! Tente Novamente!\n");
					system("PAUSE");
					break;
				}
			}
			else printf("Erro na abertura do ficheiro de Livros\n");
	          
		list = NEXT(list);	
		}   
	}while(reserva == 0);
}

void AcrescentarLivro(LIST list)
{
	setlocale(LC_ALL, "");
	int reserva = 0;
	do{
		system("cls");
		ShowLivros(list);
		char NomeTemp[60], NomeTemp2[30];
		int flag=0;
		printf("\n\tTítulo do Livro: ('sair' para Voltar) ");
		scanf ("%[^\n]%*c", NomeTemp);
		printf("\n\tAutor do Livro: ('sair' para Voltar) ");
		scanf ("%[^\n]%*c", NomeTemp2);
		if(strcmp("sair", NomeTemp) ==  0 || strcmp("sair", NomeTemp2) ==  0)
			break;
		printf("\n\t'%s' e '%s' está correto? ('1' para sim, '0' para não) ", NomeTemp, NomeTemp2);
		scanf("%d",&flag);
		if(flag==1)
		{
			strcpy(((Livro*)DATA(list))->Titulo, NomeTemp);
			strcpy(((Livro*)DATA(list))->Autor, NomeTemp2);
			((Livro*)DATA(list))->Estado = 0;
			FILE* fp;
			Livro* pt;
			if ((fp = fopen("livros.txt", "a")) != NULL)
			{
	
				fprintf(fp, "\n%s;%s;%d", ((Livro*)DATA(list))->Autor, ((Livro*)DATA(list))->Titulo, ((Livro*)DATA(list))->Estado);	
					fclose(fp);
					ShowLivros(list);
			}
			else printf("Erro na abertura do ficheiro de Livros\n");
			
			break;	
			reserva=1;		
		}
		else if(flag==0)
		{
			printf("Tente Novamente!\n");
					system("PAUSE");
					break;
		}
		
	}
	while(reserva==0);			
}

void ReservarLivro(LIST list)
{
	setlocale(LC_ALL, "");
	int reserva = 0;
	do{
		system("cls");
		ShowLivros(list);
		char NomeTemp[80];
		printf("\n\tTítulo do Livro: ('sair' para Voltar) ");
		scanf ("%[^\n]%*c", NomeTemp);
		if(strcmp("sair", NomeTemp) ==  0)
			break;
	
		while (list)
	    {   
	    		if(strcmp(((Livro*)DATA(list))->Titulo, NomeTemp) ==  0)
	    		{
	    			if(((Livro*)DATA(list))->Estado != 1)
	    			{		
		    			printf("Estado Alterado!\n");
		    			((Livro*)DATA(list))->Estado = 1;
		    			
		    			system("PAUSE");
		    			break;
		    			reserva = 1;
		    			
	    			}
	    			else
	    			{
	    				printf("Esse Livro já se encontra reservado!\n");
	    				system("PAUSE");
	    				break;
	    				reserva = 1;
	    				
	    			}
				}	    				    		
	    		else if(reserva == 0)	
				{
					printf("Livro Não Encontrado! Tente Novamente!\n");
					system("PAUSE");
					break;
					}    
				
	        list = NEXT(list);     
	    }
	}while(reserva == 0);
}

void EntregarLivro(LIST listLivro, LIST listSocio)
{
	setlocale(LC_ALL, "");
	int reserva = 1;
	do{
		system("cls");
		ShowLivros(listLivro);
		ShowSocios(listSocio);
		char NomeTemp[80];
		int numTemp=0;
		printf("\n\tNúmero Sócio: ('999' para Voltar) ");
		scanf ("%d", &numTemp);
		if(numTemp==999)
			break;
	
		while (listSocio)
	    {   
	    	if(((Socio*)DATA(listSocio))->Numero == numTemp)
	    	{
	    		printf("\tBem-vindo %s!", ((Socio*)DATA(listSocio))->Nome);
	    		printf("\n\tTítulo do Livro: ('sair' para Voltar) ");
				scanf (" %[^\n]%*c", NomeTemp);
				if(strcmp("sair", NomeTemp) ==  0)
				break;
	    		while (listLivro)
	  			{ 
	    		if(strcmp(((Livro*)DATA(listLivro))->Titulo, NomeTemp) ==  0)
	    		{
	    			if(((Livro*)DATA(listLivro))->Estado != 0)  
	    			{		
		    			printf("Estado Alterado!\n");
		    			((Livro*)DATA(listLivro))->Estado = 0;
		    			system("PAUSE");
		    			break;
		    			reserva = 0;
		    			
	    			}
	    			else
	    			{
	    				printf("Esse Livro não está reservado!\n");
	    				system("PAUSE");
	    				break;
	    				reserva = 0;
	    				
	    			}
				}	    				    		
	    		else if(reserva == 1)	
				{
					printf("Livro Não Encontrado! Tente Novamente!\n");
					system("PAUSE");
					break;
				}   
				listLivro = NEXT(listLivro);
				}			    
			}
			else if(((Socio*)DATA(listSocio))->Numero != numTemp)
			{
				printf("Sócio Não Encontrado! Tente Novamente!\n");
					system("PAUSE");
					break; 
			}
	    	listSocio = NEXT(listSocio);	
	    }
	}while(reserva == 1);
}

void ShowLivros(LIST list)
{
	setlocale(LC_ALL, "");
	printf("\n                    --->  Livros Registados  <--- \n\n");
	printf("_____Autor_________________Título________________Estado___\n");
	while (list != NULL)
	{
		printf("|  %s   \t|  %s  \t\t|     %d    | \n", ((Livro*)DATA(list))->Autor, ((Livro*)DATA(list))->Titulo, ((Livro*)DATA(list))->Estado);
		list = NEXT(list);
		printf("|-----------------|---------------------------|----------|\n");	
	}
	printf("|_________________|___________________________|__________|\n");
}

void ShowSocios(LIST list)
{
	setlocale(LC_ALL, "");
	printf("\n                     --->  Sócios Registados  <---\n\n");
	printf("\t\t___Nome______Número__\n");
	while (list != NULL)
	{
	printf("\t\t|  %s |     %d | \n", ((Socio*)DATA(list))->Nome,  ((Socio*)DATA(list))->Numero);
	list = NEXT(list);
	printf("\t\t|--------|----------|\n");	}
	printf("\t\t|________|__________|\n\n\n\n");
}

STATUS ReadLivros(LIST* list, const char* filename)
{
	setlocale(LC_ALL, "");
	FILE* fp;
	Livro* pt;
	if ((fp = fopen(filename, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((pt = (Livro*)malloc(sizeof(Livro))) != NULL && (InsertIni(list, pt) != ERROR))
			{
				fscanf(fp, "%[^;];%[^;];%d\n", pt->Autor, pt->Titulo, &(pt->Estado));		
			}
			else
			{
				FreeList(list);
				return ERROR;
			}
		}
		fclose(fp);
		return OK;
	}
	else
		return ERROR;
}

STATUS ReadSocios(LIST* list, const char* filename)
{
	setlocale(LC_ALL, "");
	FILE* fp;
	Socio* pt;
	if ((fp = fopen(filename, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((pt = (Socio*)malloc(sizeof(Socio))) != NULL && (InsertIni(list, pt) != ERROR))
			{
				fscanf(fp, "%[^;];%d\n", pt->Nome, &(pt->Numero));				
			}
			else
			{
				FreeList(list);
				return ERROR;
			}
		}
		fclose(fp);
		return OK;
	}
	else
		return ERROR;
}

STATUS WriteLivros(LIST* list, const char* filename)
{
	setlocale(LC_ALL, "");
	FILE* fp;
	Livro* pt;
	if ((fp = fopen(filename, "a")) != NULL)
	{
	
				fprintf(fp, "\n%s;%s;%d\n", pt->Autor, pt->Titulo, pt->Estado);	
					fclose(fp);
		return OK;	
	}
	else
		return ERROR;
}

//-----------------------------------------------------------------------------------


void initList(LIST *list)
{
*list = NULL;
}

void FreeList(LIST* list)
{
	while (*list != NULL)
	RemoveFirstNode(list);
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
printf(" %s; %s; %d ->", ((Livro *)DATA(list))->Titulo, ((Livro *)DATA(list))->Autor, ((Livro *)DATA(list))->Estado);
list = NEXT(list);
}
printf(" FIM\n");
}

void RemoveFirstNode(LIST *list)
{
LIST_NODE* node;
node = NEXT(*list);
free(DATA(*list));
free(list);
*list = node;
}

