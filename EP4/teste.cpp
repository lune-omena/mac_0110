/********************************************************************************
    Nome: Lucy Anne de Omena Evangelista
    NUSP: 11221776

    Fonte e comentários: 
    Programa para teste individual de funções e de posições do tabuleiro, quando o oficial
	dava algum tipo de problema de difícil visualização. Há funções em comum, mas a estrutura
	de exibição e proposta são diferentes da original. Programa dispensável.
	
*********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define max 8

int podejogar(int tabuleiro[max][max], int cor, int l, int c);
void inicializaTabuleiro(int tabuleiro[max][max]);
void FazTabu(int tabuleiro[max][max]);
void escolhejogada(int tabuleiro[max][max], int cor, int *linha, int *coluna);

int main(){
	int i, j, k, ok = 0, okk, naofim = 1;	// auxiliares
	int l, c, jogador, jogini, tabuleiro[max][max], possibilidades[max][max], disponivel;		// var. que recebem valores
	int *lc, *cc;
	
	inicializaTabuleiro(tabuleiro);
	
	for (i = 0; i < max; i++){
		for(j = 0; j < max; j++){
			okk = podejogar(tabuleiro, 1, i, j);
			possibilidades[i][j] = okk;
		}
	}
	
	FazTabu(tabuleiro);
	printf("\n");
	for (i = 0; i < max; i++){
		for(j = 0; j < max; j++){
			printf(" %d |", possibilidades[i][j]);
			
		}
		printf("\n----------------------------\n");
	}
	
	escolhejogada(tabuleiro, 1, &l, &c);
	printf("JOGADA ESCOLHIDA: %d %d", l, c);
}

void escolhejogada(int tabuleiro[max][max], int cor, int *linha, int *coluna){
	// Função para o computador escolher uma jogada
	int a, b, i, j, l, c, k, m, li = -1, co = -1, outracor, passou = 0, passei = 0;
	int posicoes[20][3], n = 0, pontos;
	int min = 50, mx = 0, mxl;
	
	outracor = -cor;
	// zerando matriz de posicoes que armazenara as posicoes possiveis e os pontos ganhos
	for(i = 0; i < 20; i++)
		for(j = 0; j < 3; j++)
			posicoes[i][j] = 0;

	// varrendo o tabuleiro
	for(l = 0; l < max; l++)
			for(c = 0; c < max; c++)
			if(tabuleiro[l][c] == 0){
				for(a = -1; a < 2; a++)
					for(b = -1; b < 2; b++){
						if(b == 0 && a == 0) b++;
						k = l + a; m = c + b; pontos = 0;
						if (k >= 0 && m>=0){
						while(tabuleiro[k][m] == outracor){
							k = k + a; m = m + b;
							passou = 1;
							pontos++;
						}
						if((tabuleiro[k][m] == cor) && passou){
							//ok = 1;
							pontos++;
							if(posicoes[n-1][0] == l && posicoes[n-1][1] == c){
								posicoes[n-1][2] += pontos - 1;
							} else {
								posicoes[n][0] = l;
								posicoes[n][1] = c;
								posicoes[n][2] = pontos;
								n++;
							}
							
						} else {
							passou = 0;
						}
					
						}
				
				}
			} 
			
	// mostrando a tabela
	for(i = 0; i < 20; i++)
		printf("\n l: %d c: %d p: %d", posicoes[i][0],posicoes[i][1],posicoes[i][2]);
	
	// encontrando mínimo e máximo de pontos
	for(i = 0; i < 20 && posicoes[i][2] != 0; i++){
		if(posicoes[i][2] < min) min = posicoes[i][2];
		if(posicoes[i][2] > mx)  { 	mx = posicoes[i][2];	mxl = i;}
		
	}
			
	// estratégia da posicão com mínimo de pontos dentro do centro
	n = 0;
	for (n = 0; n < 20; n++){
		if((posicoes [n][0] >= 2 && posicoes [n][0] <= 5) 
		&& (posicoes [n][1] >= 2 && posicoes [n][1] <= 5)){
			if(posicoes[n][2] == min){
				li = posicoes [n][0];
				co = posicoes [n][1];
				break;
			}
			passei = 1;
			printf("passei");
		}
	}
			
	// caso não encontre uma jogada minima no centro	
	if (li == -1){
				
	// caso haja outra jogada qualquer no centro
		if (passei = 1){
			for (n = 0; n < 20 && posicoes [n][2] != 0; n++)
				if((posicoes [n][0] >= 2 && posicoes [n][0] <= 5) 
				&& (posicoes [n][1] >= 2 && posicoes [n][1] <= 5)){
						li = posicoes [n][0];
						co = posicoes [n][1];
						break;
					}
		}
	}
	
	// Verificando se há jogada nos cantos com diferença de até 2 pontos ou menos de jogadas de máximos pontos
	if (li == -1){
		
		for (n = 0; n < 20 && posicoes [n][2] != 0; n++){
			if((posicoes [n][0] == 0  && posicoes [n][1] == 0) 
				|| (posicoes [n][0] == 0 && posicoes [n][1] == 7)
				|| (posicoes [n][0] == 7 && posicoes [n][1] == 7)
				|| (posicoes [n][0] == 7 && posicoes [n][1] == 0)){
						if(posicoes[n][2] >= (posicoes[mxl][2] - 2)){
							li = posicoes [n][0];
							co = posicoes [n][1];
							break;
						}		
					}
		}
	}
	
	// Verificando se ha jogadas nas bordas ou outras jogadas máximas com diferença de 2 pontos ou mais
	if (li == -1){
		
		for (n = 0; n < 20 && posicoes [n][2] != 0; n++){
			if((posicoes [n][0] == 0  || posicoes [n][0] == 7) 
				|| (posicoes [n][1] == 0 || posicoes [n][1] == 7)){
						if(posicoes[n][2] >= (posicoes[mxl][2] - 2)){
							li = posicoes [n][0];
							co = posicoes [n][1];
							break;
						}		
					}
		}
	}
	
	// verificando outra jogada com o máximo de pontos
	
	if (li == -1){
		li = posicoes [mxl][0];
		co = posicoes [mxl][1];
	}	
		
			
			*linha = li;
			*coluna = co;		
		
		
}

void inicializaTabuleiro(int tabuleiro[max][max]){
	int i, j;
		
	for(i = 0; i < max; i++)
		for(j = 0; j < max; j++)
			tabuleiro[i][j] = 0;
			
	tabuleiro[0][7] = -1;
	tabuleiro[1][6] = -1;
	tabuleiro[2][2] = 1;
	tabuleiro[2][3] = 1;
	tabuleiro[2][4] = 1;
	tabuleiro[2][5] = -1;
	tabuleiro[3][2] = 1;
	tabuleiro[3][3] = 1;
	tabuleiro[3][4] = -1;
	tabuleiro[3][5] = -1;
	tabuleiro[4][2] = 1;
	tabuleiro[4][3] = -1;
	tabuleiro[4][4] = 1;
	tabuleiro[4][5] = -1;
	tabuleiro[5][1] = 1;
	tabuleiro[5][2] = 1;
	tabuleiro[5][3] = 1;
	tabuleiro[5][4] = 1;
	tabuleiro[5][5] = -1;
	tabuleiro[6][5] = -1;
	tabuleiro[7][5] = -1;


}
	
void FazTabu(int tabuleiro[max][max]){
	// função para montar o tabuleiro. hehe
	int i, j, k, carac;
	
	printf("   ");
	for(i = 0; i < max; i++) printf("  %d ", i);
	printf("\n   %c", 201);
	for (k = 0; k <= 30; k ++) printf("%c", 205);
	printf("%c", 187);
	
	for(i = 0; i < max; i++){
		printf("\n %d %c", i, 186);
		
		for(j = 0; j < max; j++){
			if (tabuleiro[i][j] == 1) carac = 2;
			else
			if (tabuleiro[i][j] == -1) carac = 1;
			else carac = 0;
			if (j != max - 1) printf(" %c |", carac); else printf(" %c ", carac);
			
		}
					
		
		printf("%c\n", 186);
		
		if (i != max - 1) printf("   %c", 204); else printf("   %c", 200);
		for (k = 0; k <= 30; k ++) printf("%c", 205);
		if (i != max - 1) printf("%c", 185); else printf("%c", 188);
	}
	
	
}

int podejogar(int tabuleiro[max][max], int cor, int l, int c){
	
//Esta funcao devolve (1) se a posicao (l,c) do tabuleiro for uma jogada valida para a cor, e false (0) caso contr´ario.
	int a, b, k, m, ok = 0, outracor, passou = 0;
	
	outracor = -(cor);
	
	if(tabuleiro[l][c] == 0){
		for(a = -1; a < 2 && !ok; a++)
			for(b = -1; b < 2 && !ok; b++){
				if(b == 0 && a == 0) b++;
				k = l + a; m = c + b;
				if (k >= 0 && m>=0){
					while(tabuleiro[k][m] == outracor){
					k = k + a; m = m + b;
					passou = 1;
					}
					if((tabuleiro[k][m] == cor) && passou){
						ok = 1;
					} else {
						passou = 0;
					}
					
				}
				
			}
	}
	
	return (ok);
}
