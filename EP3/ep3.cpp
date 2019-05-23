#include <stdio.h>
/*

> lista ordenada pelo NUSP dos usuários do salão, com quanto tempo ficaram em cada visita
> lista ordenada pelo tempo total de visita do dia dos usuários
> histograma de uso do salão para cada hora de funcionamento
> numero total de usuários diferentes do salão OKAAY
> tempo médio diário de uso do salão de leitura e desvio padrão
> distribuição do numero de usuários por tempo de uso diário em minutos.

*/

void nusp_unicos(int nusp[4][100], int tamn, int unicos[], int *tamun);

int visitas(int nusp[4][100], int tamn);

void ordena(int nusp[4][100], int tamn, int col, int ordena[]);

int main(){
	int i, j, es, hrs, min;
	int aux[100], tamn = 0, unicos[100], tamun = 0;
	int sis[4][100];
	char nome_arquivo[50];
	FILE * arquivo;

	// Inicializando matrizes auxiliares
	for (j =0; j<tamn; j++){
		unicos[j] = 0;
		aux[j] = 0;
	}

	// Iniciando o programa
	printf("Benvindo ao Sistema Estatístico de Uso do Salão de Estudos");
	printf("\nBiblioteca \"Carlos Benjamim de Lyra\"  -  IME-USP");
	printf("\n\nDigite o nome do arquivo de dados: ");
	//scanf("%s", nome_arquivo);
	arquivo = fopen("arq20190425.txt", "r");

	// Armazenando os dados do arquivo de dados
	while (!feof(arquivo)){
		//if (fscanf(arquivo,"%d %d %d:%d", &es, &nusp[tamn], &hrs , &min) != 4)
		if (fscanf(arquivo,"%d %d %d:%d", &sis[1][tamn], &sis[0][tamn], &sis[2][tamn], &sis[3][tamn]) != 4)
			continue;
		printf("%d %d %d %d\n", sis[1][tamn], sis[0][tamn], sis[2][tamn], sis[3][tamn]);
		tamn++;
	}
	/*
	nusp =  sis[0][tamn]
    es  =   sis[1][tamn]
    hr  =   sis[2][tamn]
    min =   sis[3][tamn]
	*/

	for (i = 0; i < tamn; i++){
        aux[i] = sis[0][i];
		printf(" %d \n", aux[i]);

	}
	// Calculando status

	nusp_unicos(sis, tamn, unicos, &tamun);



	printf("\nExistem %d visitantes unicos, de %d visitas no total.", tamun, tamn);

	printf("\nNO PERÍODO TIVEMOS %3d USUÁRIOS DIFERENTES E %3d VISITAS", tamun,visitas(sis, tamn));

    ordena(sis, tamn, 0, aux);

    printf("\nNUSP\tHora entrada\tMinutos entrada");
   for (i = 0; i < tamn;i++)

   printf("\n %d \t %d \t %d ", sis[0][i], aux[i], i, sis[2][i], sis[3][i]);

    //}
}



void nusp_unicos(int nusp[4][100], int tamn, int unicos[], int *tamun){
	int possui = 0, i, j;

	for (i = 0; i < tamn; i++){
		for (j = 0; j < tamn; j++){
			if (nusp[0][i] == unicos[j])
				possui++;
		}

		if (possui == 0){
			printf("\nnusp: %d tam: %d", nusp[0][i], *tamun);
			unicos[*tamun] = nusp[0][i];
			*tamun = *tamun + 1;
		}
		possui = 0;
	}

}

int visitas(int es[4][100], int tamn){
    int visita = 0, i;

    for (i = 0; i < tamn; i++){
        if (es[1][i] == 0) // Caso seja entrada
        visita++;
    }
    return(visita);
}

void ordena (int dados[4][100], int tamn, int col, int ordena[]){
    int i, j, aux = 0;

    // atribuindo valores para a matriz auxiliar
    for(i = 0; i < tamn; i++){
        ordena[i] = dados[col][i];
    }

    //Bubblesort <3
    for(i = 0; i < tamn; i++)
        for (j = i + 1; j < tamn; j++)
            if (dados[col][i] > dados[col][j]){
                aux = dados[col][j];
                dados[col][j] = dados[col][i];
                dados[col][i] = aux;
            }

    // atribuindo à ordena[] os indices ordenados pela coluna da matriz
    for(i = 0; i < tamn; i++)
        for(j = 0; j < tamn; j++){
            if(ordena[i] == dados[col][j]){
            if (ordena[i] == j){
                break;
            }
            ordena[i] = j;
            //dados[col][j] = 0;
            }


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
