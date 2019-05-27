/****************************************************************
    Nome: Lucy Anne de Omena Evangelista
    NUSP: 11221776

    Fonte e comentários: 
    O programa utiliza uma matriz para armazenar os valores do arquivo, fazendo um tratamento nos dados recebidos do arquivo
    de tal forma que fique mais fácil processá-los. O tempo padrão é em minutos, sendo convertido em horas quando necessário.
    Cada uma das funcoes foram pensadas para funcionar com qualquer matriz de três colunas, com a pessoa indicando qual coluna
    deseja levar em consideração para cada processo. As funções estão descritas possuem nome auto-descritivo. A função ordena()
    retorna um vetor de correção da ordem dos itens, não modificando a estrutura inicial dos dados e facilitando na manipulação
    da matriz.
    A funcao distribuicao_por_tempo_diario() mostra as estatísticas considerando a quantidade de pessoas ao final do período.
    
****************************************************************/
#include <stdio.h>
#include <math.h>
#define MAX 100
#define cols_data 3

int nusp_unicos(int nusp[cols_data][MAX], int tamn, int unicos[MAX], int col);
float tempo_medio(int dados[cols_data][MAX], int tamn, int col);
float desvio_padrao(int dados[cols_data][MAX], int tamn, int col);
void histograma_de_uso(int dados[cols_data][MAX], int tamn);
void distribuicao_por_tempo_diario(int dados[3][MAX], int tamn, int unicos[MAX], int tamun);
void ordena(int dados[cols_data][MAX], int tamn, int col, int ordena[], int ascdesc);

int main(){
	int achou, achouvalor = 0;
	int i, j, k = 0, tempo, hrs, min;
	int registro[cols_data][MAX], aux[MAX], tamn = 0;
	int sis[cols_data][MAX], unicos[MAX], tamun = 0;
	char nome_arquivo[80];
	FILE * arquivo;

	// Inicializando matrizes e vetores
	for (j =0; j < MAX; j++){
		aux[j] = 0;
		unicos[i] = 0;
		for (i = 0; i < cols_data; i++)
			registro[i][j] = 0;
	}

	// Iniciando o programa
	printf("Benvindo ao Sistema Estatistico de Uso do Salao de Estudos");
	printf("\nBiblioteca \"Carlos Benjamim de Lyra\"  -  IME-USP");
	printf("\n\nDigite o nome do arquivo de dados: ");
	//scanf("%s", nome_arquivo);
	arquivo = fopen("arq20190425.txt", "r");

	// Armazenando os dados do arquivo de dados, numa estrutura de sequencia [nusp, entrada/saida, tempo(min)]
	// Essa parte do programa precisa ser ajustada caso a estrutura do arquivo seja mudada
	while (!feof(arquivo)){		
		if (fscanf(arquivo,"%d %d %d:%d", &sis[1][tamn], &sis[0][tamn], &hrs , &min) != 4){
			continue;
		}
			
		tempo = hrs*60 + min;
		sis[2][tamn] = tempo;
		//printf("\n%d %d %d", sis[0][tamn], sis[1][tamn], sis[2][tamn]);
		tamn++;
	}
	
	// Iniciando o DataPrep. Tratando a tabela sis para possuir os dados na estrutura [nusp, tempo de entrada(min), permanencia]
	for (i = 0; i < tamn; i++){
		achou = 0;
		for (j = i + 1; j < tamn; j++){
			if (sis[0][i] == sis[0][j] && sis[1][i] == 0 && sis[1][j] == 1 && achou !=1){
				achou = 1;
				achouvalor = j;
			}
		}
		// Para o caso de entrada e saída sem problemas
		if(achou){
			registro[0][k] = sis[0][i]; //nusp
			registro[1][k] = sis[2][i]; //minutos de entrada
			registro[2][k] = sis[2][achouvalor] - sis[2][i]; //permanencia
			sis[0][achouvalor] = 0; //zerando o nusp, para não considerar
			//printf("\n %d \t %d \t %d \t %d", k, registro[0][k], registro[1][k], registro[2][k]);
			k++;
		} else {
			// se só identificou a entrada da pessoa considera ela saindo as 23:59
			if(!sis[1][i]){
				registro[0][k] = sis[0][i]; //nusp
				registro[1][k] = sis[2][i]; //minutos de entrada
				registro[2][k] = 1439 - sis[2][i]; //permanencia, descontando a entrada do total de minutos de um dia
			//	printf("\n %d \t %d \t %d \t %d", k, registro[0][k], registro[1][k], registro[2][k]);
				k++;
			} else {
				// se só identificou a saída da pessoa, considera como ela entrando a meia noite (00:00)
				if(sis[1][i] && sis[0][i] != 0){
				registro[0][k] = sis[0][i]; //nusp
				registro[1][k] = 0; //minutos de entrada
				registro[2][k] = sis[2][i]; //permanencia
			//	printf("\n %d \t %d \t %d \t %d", k, registro[0][k], registro[1][k], registro[2][k]);
				k++;
				}
			}
		}	
	}
	// Fim do DataPrep
	// Agora a variável k representa a quantidade de visitas diárias à biblioteca!
	
	
	// Calculando status
	tamun = nusp_unicos(registro, k, unicos, 0);
	printf("\n\nNO PERIODO TIVEMOS %3d USUARIOS DIFERENTES E %3d VISITAS", tamun, k);
	printf("\nA MEDIA DE PERMANENCIA NO SALAO FOI DE %5.2f MINUTOS", tempo_medio(registro, k, 2));
	printf("\nO DESVIO PADRAO DA PERMANENCIA E DE %5.2f MINUTOS", desvio_padrao(registro, k, 2));
	
	printf("\n\nLISTA DE USUARIOS DO SALAO DE LEITURA\n");
    printf("\nNUSP\tHora de entrada\tTempo de permanencia (minutos)");
    
    //ordenando a tabela pelo NUSP. Coloca em aux os indices de correção das variáveis ordenadas
    ordena(registro, k, 0, aux, 0);  
    for (i = 0; i < k; i++)
   		printf("\n%d \t    %d:%02d \t  %4d", registro[0][aux[i]], (registro[1][aux[i]] / 60), (registro[1][aux[i]] % 60), registro[2][aux[i]]);
   		
    printf("\n\nVISITAS ORDENADAS PELO TEMPO DE PERMANENCIA\n");
	printf("\nNUSP\tHora de entrada\tTempo de permanencia (minutos)");
	
	//ordenando a tabela pelo tempo de permanencia
	ordena(registro, k, 2, aux, 1);
    for (i = 0; i < k; i++)
   		printf("\n%d \t    %d:%02d \t  %4d", registro[0][aux[i]], (registro[1][aux[i]] / 60), (registro[1][aux[i]] % 60), registro[2][aux[i]]);
	
	printf("\n\nVISITAS ORDENADAS PELO HORARIO DE ENTRADA\n");
	printf("\nNUSP\tHora de entrada\tTempo de permanencia (minutos)");
	
	//ordenando a tabela pelo horário de entrada
	ordena(registro, k, 1, aux, 0);
    for (i = 0; i < k; i++)
   		printf("\n%d \t    %d:%02d \t  %4d", registro[0][aux[i]], (registro[1][aux[i]] / 60), (registro[1][aux[i]] % 60), registro[2][aux[i]]);
	
	//Exibindo informações de uso
	histograma_de_uso(registro, k);
	distribuicao_por_tempo_diario(registro, k, unicos, tamun);
}



int nusp_unicos(int nusp[3][MAX], int tamn, int unicos[MAX], int col){
	int possui = 0, i, j, tamun = 0;

	for (i = 0; i < tamn; i++){
		for (j = 0; j < tamn; j++){
			if (nusp[col][i] == unicos[j])
				possui++;
		}

		if (possui == 0){
		//	printf("\nnusp: %d tam: %d", nusp[0][i], tamun);
			unicos[tamun] = nusp[col][i];
			tamun++;
		}
		possui = 0;
	}
	return(tamun);

}

float tempo_medio(int dados[3][MAX], int tamn, int col){
	int i, soma = 0;

	for (i = 0; i < tamn; i++)
		soma += dados[col][i];
	
	return((float) soma / tamn);
}

float desvio_padrao(int dados[3][MAX], int tamn, int col){
	int i;
	float desvio, media, soma = 0;
	media = tempo_medio(dados, tamn, col);
	
	for (i = 0; i < tamn; i++){
		soma += pow(dados[2][i] - media, 2); 
	}
	
	desvio = sqrt(soma/tamn);
	
	return (desvio);
}

void histograma_de_uso(int dados[3][MAX], int tamn){
	int i, j, nusp = 0, hora[24], inicio, fim;
	
	//zerando a matriz de horas
	for(i = 0; i < 24; i++){
		hora[i] = 0;
	}
	
	// Para cada registro, contabiliza as horas em que o estudante esteve na biblioteca
	for (i = 0; i < tamn; i++){
		inicio = dados[1][i] / 60;
		fim = (dados[1][i] + dados[2][i])/ 60;
		//printf("\ninicio: %d fim: %d\t%d\t%d", inicio, fim, dados[1][i], dados[2][i]);
		while(inicio <= fim){
		 	hora[inicio]++;
		 //	printf ("\n hora: %d inicio: %d fim: %d", hora[inicio], inicio, fim);
		 	inicio++;
	 	}	
	}
	
	printf("\n\nHISTOGRAMA DE USO DO SALAO POR HORA DO DIA\n");
	printf("\nHora");
	for (i = 0; i < 24; i++){
		printf("\n %02d | ", i, hora[i]);
		
		for(j = 0; j < hora[i]; j++){
			printf("*");
		}
	}
}



void distribuicao_por_tempo_diario(int dados[3][MAX], int tamn, int unicos[MAX], int tamun){
	int i, j, permanencia[tamun], distribuicao[48], fim;

	for (i = 0; i < tamun; i++)
		permanencia[i] = 0;
		
	for (i = 0; i < 48; i++)
		distribuicao[i] = 0;
		
	for (i = 0; i < tamun; i++)
		for(j = 0; j < tamn; j++)
			if(unicos[i] == dados[0][j])
				permanencia[i] += dados[2][j];
		
	for (i = 0; i < tamun; i++){
		fim = permanencia[i]/ 30;
		for(j = 0; j < fim; j++)
			distribuicao[j] += 1;	
	}
	
	printf("\n\nDISTRIBUICAO DE USUARIOS POR TEMPO DE USO DIARIO (min)\n");
	printf("\n    PERIODO");
	for (i = 0; i < 48; i++){
		printf("\n %02d:%02d - %02d:%02d | ", ((i * 30) / 60), ((i * 30) % 60) + 1, (((i+1) * 30) / 60) % 24, (((i+1) * 30) % 60) + 1);
		
		for(j = 0; j < distribuicao[i]; j++){
			printf("*");
		}
	}
}

void ordena(int dados[3][MAX], int tamn, int col, int ordena[], int ascdesc){
    int i, j, aux = 0, vaux[tamn], dado[MAX];

    // atribuindo valores para o vetor auxiliar e ordena[]
    for(i = 0; i < tamn; i++){
        vaux[i] = dados[col][i];
        dado[i] = dados[col][i];
        ordena[i] = -1;
    }

    //Bubblesort <3
    for(i = 0; i < tamn; i++)
        for (j = i + 1; j < tamn; j++)
        if (ascdesc == 0){
			if (dado[i] > dado[j]){
                aux = dado[j];
                dado[j] = dado[i];
                dado[i] = aux;
            }
		} else {
		if (ascdesc == 1)
			if (dado[i] < dado[j]){
                aux = dado[j];
                dado[j] = dado[i];
                dado[i] = aux;
			}
		}
            

    // atribuindo a ordena[] os indices  de correcao da posicao dos itens, a partir da comparacao com o vetor auxiliar
    for(i = 0; i < tamn; i++)
        for(j = 0; j < tamn; j++){
        	// Para garantir que nao havera problemas com multiplas entradas de estudantes, ha a condicao ordena[j] == -1 e um break
            if(vaux[i] == dado[j] && ordena[j] == -1){
            	// printf("\n %d %d %d %d %d", vaux[i], dados[col][j], i, j, ordena[j]);
            	ordena[j] = i;
            	break; // barrando a continuação das comparações
            }
        }
}


