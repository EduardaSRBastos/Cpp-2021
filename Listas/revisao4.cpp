#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef enum _BOOLEAN {FALSE=0, TRUE=1} BOOLEAN;

typedef struct _CLIENT{
int code;
char name[100];
}CLIENT;
int ReadClients(CLIENT **, char *);


int main(void)
{
int num_clients,i;
CLIENT *clients=NULL;
char str[100];
printf("\nNome do ficheiro : ");
scanf("%s",str);
switch (num_clients=ReadClients(&clients,str))
{
case -2 : printf("\a\nErro na aloca��o de mem�ria...\n");
break;
case -1 : printf("\a\nErro de leitura do ficheiro...\n");
break;
case 0 : printf("\a\nFicheiro vazio...\n");
break;
default: printf("\nFicheiro lido com sucesso...\n");
printf("\nConteudo do ficheiro:\n");
for (i=0; i<num_clients; i++)
printf("%d ; %s\n",clients[i].code,clients[i].name);
}
free(clients);

system("PAUSE");

return 0;
}


int ReadClients(CLIENT **p_v, char *filename)
{
FILE *fp;
int size=0;

if((fp = fopen(filename,"rt"))==NULL)
return(-1);
while(!feof(fp))
{
if((*p_v = (CLIENT*)realloc(*p_v,sizeof(CLIENT)*(size+1))) == NULL)
return(-2);
fscanf(fp,"%d;%[^\n]\n",&(((*p_v)[size]).code),(*p_v+size)->name);
size++;
}
fclose(fp);
return(size);
}
