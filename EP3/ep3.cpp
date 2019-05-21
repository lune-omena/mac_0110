#include <stdio.h>

int main(){
	int i, j;
	char nome_arquivo[50];
	FILE * arquivo;
	
	printf("Benvindo ao Sistema Estatístico de Uso do Salão de Estudos");
	printf("\nBiblioteca \"Carlos Benjamim de Lyra\"  -  IME-USP");
	printf("\n\nDigite o nome do arquivo de dados: ");
	scanf("%s", nome_arquivo);
	
	printf("%s", nome_arquivo);
	
	
	arquivo = fopen(nome_arquivo, "r");
	
	
	
	
	
}
