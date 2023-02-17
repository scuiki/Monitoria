/*
Exercício) Montar, utilizando as structs disponibilizadas e ponteiros, um sistema de agendamento para consultórios médicos (lembrando que um doutor pode ter diversas consultas em um mesmo dia). 
Fazer a conclusão da consulta através do CPF do cliente e retornar para o usuário o médico e valor a pagar (Exibir, no início do programa, quais médicos e valores estão cadastrados). 

typedef struct	cliente {

	char CPF[13];	// CPF do cliente

    char nome[80];	// nome do cliente

    char ndoutor[80];	// nome do doutor
    
    char data[8];	//data da consulta	
    
    int k;

}cliente;

typedef struct	doutor {

	char ndoutor[80];	//nome do doutor

	float valor;	//valor da consulta

}doutor;
*/

//1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//2
typedef struct	cliente {

	char CPF[13];	// CPF do cliente

    char nome[80];	// nome do cliente

    char ndoutor[80];	// nome do doutor
    
    char data[8];	//data da consulta	
    
    int k;

}cliente;

typedef struct	doutor {

	char ndoutor[80];	//nome do doutor

	float valor;	//valor da consulta

}doutor;

//3

void aloca_cliente (cliente **c, int qtd);
void aloca_doutor (doutor **d, int qtd);
void cadastra_doutor (doutor *d, int qtd);
void cadastra_cliente (cliente *c, doutor *d, int cont);
void concluir_consulta (cliente *c, int qtd, doutor *d);
int busca_vago (cliente *c, int qtd, int q);

//4
void main () {

//5	
cliente *pc = NULL;
doutor *pd = NULL;
//8
int op, cont = 0, pos, i;
//6.5
	aloca_doutor (&pd, 3);
//7.5
	cadastra_doutor (pd, 3);
	
	for (i = 0; i < 3; i++)
		printf ("Doutor: %s\nValor: %.2f\n\n", (pd + i)->ndoutor, (pd + i)->valor); 
	system ("pause");
//9	
	do {
		system ("cls");
		printf ("[1]Agendar consulta\n[2]Concluir consulta\n[3]Sair\n\n");
		fflush (stdin);
		scanf ("\n%i", &op);
			
		switch (op) {
			case 1: pos = busca_vago (pc, cont, -1);
				if (pos == -1) {
					aloca_cliente (&pc, cont + 1);
					pos = cont;
					cont++;
				}
				cadastra_cliente (pc + pos, pd, cont);
					break;
			//15
			case 2: concluir_consulta (pc, cont, pd);
					break;
		}
	} while (op != 3);
	
}
//6
void aloca_cliente (cliente **c, int qtd) {
	if((*c=(cliente*)realloc(*c, qtd*sizeof(cliente)))==NULL)
		exit (1);
}

void aloca_doutor (doutor **d, int qtd) {
	if((*d=(doutor*)realloc(*d,qtd*sizeof(doutor)))==NULL)
		exit (1);
}
//7
void cadastra_doutor (doutor *d, int qtd) {
int i;
char n1[80] = "Doutor1", n2[80] = "Doutor2", n3[80] = "Doutor3";

	for (i = 0; i < qtd; i++, d++) {
		
		if (i == 0) {
			strcpy (d->ndoutor, n1);
			d->valor = 150.0;
		}
		
		if (i == 1) {
			strcpy (d->ndoutor, n2);
			d->valor = 175.0;
		}
		
		if (i == 2) {
			strcpy (d->ndoutor, n3);
			d->valor = 200.0;	
		}
	}
}

//10
int busca_vago (cliente *c, int qtd, int q) {
int i;
	for (i = 0; i < qtd; i++, c++)
		if (c->k == q)
			return i;
return -1;
}

//11
void cadastra_cliente (cliente *c, doutor *d, int cont) {
char nd[80], dt[8];	
int numdoutor;

//12
do {
	system ("cls");
	printf ("\nDoutor (Doutor1, Doutor2, Doutor3): ");
	fflush (stdin);
	gets (nd);
} while (strcmp(nd, d->ndoutor) != 0 && strcmp(nd, (d + 1)->ndoutor) != 0 && strcmp(nd, (d + 2)->ndoutor) != 0);

	printf ("\nData (xx/xx/xx): ");
	fflush (stdin);
	gets (dt);
	
//13	
	printf ("\nCPF: ");
	fflush (stdin);
	gets (c->CPF);
	printf ("\nNome: ");
	fflush (stdin);
	gets (c->nome);
	strcpy (c->data, dt);
	strcpy (c->ndoutor, nd);
	c->k = 0;

	printf ("\nCadastro efetuado com sucesso. Data: %s\n\n", c->data);
	system ("pause");
}

//14
void concluir_consulta (cliente *c, int qtd, doutor *d) {
int i;	
char CPF[13];
	
	system ("cls");
	printf ("\nCPF: ");
	fflush (stdin);
	gets (CPF);
	
	for (i = 0; i < qtd; i++, c++) {
		if (strcmp (c->CPF, CPF) == 0) {
			printf ("\n\nNome: %s\nDoutor: %s\n", c->nome, c->ndoutor);
			
			for (i = 0; i < 3; i++, d++) {
				if ((strcmp(c->ndoutor, d->ndoutor) == 0))
					printf ("Valor: %.2f\n\n", d->valor);
			}
			c->k = -1;
			memset(c->CPF, -1, 13);//Essa linha não é necessária, nem se preocupem com ela
		}
	}
	system ("pause");
}

