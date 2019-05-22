#include <stdio.h>
/*

> lista ordenada pelo NUSP dos usuários do salão, com quanto tempo ficaram em cada visita
> lista ordenada pelo tempo total de visita do dia dos usuários
> histograma de uso do salão para cada hora de funcionamento
> numero total de usuários diferentes do salão OKAAY
> tempo médio diário de uso do salão de leitura e desvio padrão
> distribuição do numero de usuários por tempo de uso diário em minutos.

*/

void nusp_unicos(int nusp[], int tamn, int unicos[], int *tamun);


int main(){
	int i, j, es, hrs, min;
	int nusp[100], tamn = 0, unicos[100], tamun = 0;
	char nome_arquivo[50];
	FILE * arquivo;
	
	// Inicializando matrizes auxiliares
	for (j =0; j<tamn; j++){
		unicos[j] = 0;
	}
	
	// Iniciando o programa
	printf("Benvindo ao Sistema Estatístico de Uso do Salão de Estudos");
	printf("\nBiblioteca \"Carlos Benjamim de Lyra\"  -  IME-USP");
	printf("\n\nDigite o nome do arquivo de dados: ");
	//scanf("%s", nome_arquivo);
	arquivo = fopen("arq20190425.txt", "r");	
	
	// Armazenando os dados do arquivo de dados
	while (!feof(arquivo)){
		if (fscanf(arquivo,"%d %d %d:%d", &es, &nusp[tamn], &hrs , &min) != 4)
			continue;		
		printf("%d %d %d %d\n", es, nusp[tamn], hrs , min);
		tamn++;
	}
	
	
	for (j =0; j<tamn; j++){
		printf(" %d \n", nusp[j]);
	}
	// Calculando status
	
	nusp_unicos(nusp, tamn, unicos, &tamun);
	
	printf("\nExistem %d visitantes unicos, de %d visitas no total.", tamun, tamn);
	

}
	
	
	
void nusp_unicos(int nusp[], int tamn, int unicos[], int *tamun){
	int possui = 0, i, j;
	
	for (i = 0; i < tamn; i++){
		for (j = 0; j < tamn; j++){
			if (nusp[i] == unicos[j])
				possui++;
		}
		
		if (possui == 0){
			printf("\nnusp: %d tam: %d", nusp[i], *tamun);
			unicos[*tamun] = nusp[i];	
			*tamun = *tamun + 1;
		}
		
		possui = 0;
	}
	
	
	
}




// Para identificar quem são os usuários que não são contadas as entradas e saídas
/*
int nusp_unicos(int nusp[], int tamn){
	int repete = 0, tamun = 0, i, j;
	
	for (i = 0; i < tamn; i++){
		for (j = 0; j < tamn; j++){
			if (i == j) j++;
			if (nusp[i] == nusp[j])
			repete = 1;
		}
		if (repete ==  0)
		tamun++;
		repete = 0;
	}
	
	return(tamun);
}
*/
