/****************************************************************
    Nome: Lucy Anne de Omena Evangelista
    NUSP: 11221776

    Fonte e comentários: O computador joga dando prioridade a executar as jogadas de menos 
	pontos no centro do tabuleiro até não haver mais opções. Depois disso ele opta por completar os cantos e bordas,
	a não ser que haja outra posição com um diferença de dois pontos para mais. Em ultimo caso, ele opta pela opção 
	que tem o máximo de pontos (note que algumas vezes o máximo pode ser igual ao mínimo de pontos).
	Meu console de simulação é preto, logo peço que caso o seu seja branco, mude os caracteres de cores na linha indicada.

    
****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define max 8

void inicializaTabuleiro(int tabuleiro[max][max]);
void FazTabu(int tabuleiro[max][max]);
int jogadadisponivel(int tabuleiro[max][max], int cor);
int podejogar(int tabuleiro[max][max], int cor, int l, int c);
void joga(int tabuleiro[max][max], int cor, int l, int c);  
void escolhejogada(int tabuleiro[max][max], int cor, int *linha, int *coluna);
int calcula(int tabuleiro[max][max], int cor);

int main(){
	int i, j, k, ok = 0, naofim = 1, carac;	// auxiliares
	int l, c, jogador, jogini, tabuleiro[max][max], disponivel, ppreto, pbranco;	// var. que recebem valores
	int *lc, *cc;
	
	inicializaTabuleiro(tabuleiro);
	
	printf("======================================================================\n");
	printf("\t\t\t OTHELLO, O JOGO\n\n");
	while (!ok){
		printf("Deseja iniciar o jogo e ser a peca de cor preta? [1] - Sim; [0] - Nao.\n");
		scanf("%d", &jogador);
		if (jogador == 1 || jogador == 0) ok = 1;
		else printf("\n\t Opção inválida! Tente novamente.\n");
	}
	
	// Definindo parametro para saber se quem joga é o comp ou a pessoa
	if (jogador == 1) {
		jogini = -1;
	} 
	if (jogador == 0){
		jogini = 1;
	}
	
	// Inicializando com jogador de cor preta
	jogador = -1;
	
	while (naofim){
		system("cls");
		printf("======================================================================\n");
		printf("\t\t\t OTHELLO, O JOGO\n\n");
		FazTabu(tabuleiro);
		
		if (jogador == -1) carac = 1;	// Ajuste para exibição
		else carac = 2;					// Se o seu console for branco, mude o que é 1 para 2; e o que é 2 para 1.
		printf("\n\n\tCOR : %c", carac);
		
		// Verificando se existe jogada disponível
		disponivel = jogadadisponivel(tabuleiro, jogador);
		if (disponivel){
			l = 0; c = 0;
			// Caso a jogada seja do usuario
			if (jogador == jogini){
				printf("\n\n  Faca sua jogada!\n\n Digite 1o a linha e depois a coluna em que quer jogar: ");
				scanf("%d %d", &l, &c);
				ok = podejogar(tabuleiro, jogador, l, c); // verificando se jogada é válida
			} 
			
			// Caso a jogada seja do computador
			else {
				printf("\n\n  Computador fez a sua jogada! ");
				escolhejogada(tabuleiro, jogador, &l, &c);
				printf("\n\n A posição escolhida para jogar foi: %d %d ", l, c);
				ok = podejogar(tabuleiro, jogador, l, c);
			}
		
			// Verificando a jogada e realizando-a ou parando o jogo caso seja inválida.
			if (ok) joga(tabuleiro, jogador, l, c);
			else {
				printf("\n\t\tJOGADA INVÁLIDA!\n\t VOCE PERDEU O JOGO.");
				getch();	
				break;
			}
		} else {
			if (!jogadadisponivel(tabuleiro, jogador) && !jogadadisponivel(tabuleiro, -jogador)){
				printf("\n\n Não há jogadas disponíveis no tabuleiro.\n\n\t Fim do jogo.");
				naofim = 0;
			} 
			else			
			if (jogador == jogini)
			printf("\n\n Não há jogadas disponíveis para voce. Passe a vez.  :D");
			else 
			printf("\n\n Não há jogadas disponíveis para mim. Passo a vez.  D:");
		}
		
		jogador = -(jogador);
		printf("\n\nAperte alguma tecla para continuar...");
		getch();
	}
	
	
	system("cls");
		printf("======================================================================\n");
		printf("\t\t\t OTHELLO, O JOGO\n\n");
		ppreto = calcula(tabuleiro, -1);
		pbranco = calcula(tabuleiro, 1);
		printf("\n\n O jogador preto (%c) fez %d pontos.", 1, ppreto); 
		printf("\n O jogador branco (%c) fez %d pontos.", 2, pbranco);
		if (ppreto > pbranco)
			printf("\n\n \t O JOGADOR PRETO GANHOU!\n\n");
		else
		if (ppreto < pbranco)
			printf("\n\n \t O JOGADOR BRANCO GANHOU!\n\n");
		else
			printf("\n\n \t DEU EMPATE!\n\n");
		FazTabu(tabuleiro);
	}
	
void inicializaTabuleiro(int tabuleiro[max][max]){
	int i, j;
		
	for(i = 0; i < max; i++)
		for(j = 0; j < max; j++)
			tabuleiro[i][j] = 0;
			
	tabuleiro[3][3] = 1;
	tabuleiro[4][4] = 1;
	tabuleiro[3][4] = -1;
	tabuleiro[4][3] = -1;
	
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

int jogadadisponivel(int tabuleiro[max][max], int cor){
	int a, b, ok = 0;
	
	for(a = 0; a < max && !ok; a++)
		for(b = 0; b < max && !ok; b++)
			if (podejogar(tabuleiro, cor, a, b) == 1)
				ok = 1;	
							
	return(ok);			
}

int podejogar(int tabuleiro[max][max], int cor, int l, int c){
	//Funcao para verificar se a escolha de posição é válida
	int a, b, k, m, ok = 0, outracor, passou = 0;
	
	outracor = -(cor);
	
	if(tabuleiro[l][c] == 0)
		for(a = -1; a < 2 && !ok; a++)
			for(b = -1; b < 2 && !ok; b++){
				k = l + a; m = c + b;
				if (k >= 0 && m>=0){
					while(tabuleiro[k][m] == outracor){
						k = k + a; m = m + b;
						passou = 1;
					}
					if((tabuleiro[k][m] == cor) && (passou)) ok = 1;
					else passou = 0;
				}	
			}
	
	return (ok);
}

void joga(int tabuleiro[max][max], int cor, int l, int c){
	//Esta funcao altera o conteudo do tabuleiro com a jogada da cor na posicao (l,c).
	int a, b, k, m, outracor, passei = 0;
	
	outracor = -(cor);
	
	for(a = -1; a < 2; a++)
		for(b = -1; b < 2; b++){
			passei = 0;
			
			if(b == 0 && a == 0) b++;
			k = l + a; m = c + b;
			if (k >= 0 && m>=0 && m<8 && k<8){
			while(tabuleiro[k][m] == outracor ){
				k = k + a; m = m + b; passei = 1;
			}
			if (tabuleiro[k][m] == cor && passei){
				//printf("oi?");
				while( k!=l || m!=c){
					
					k = k - a;
					m = m - b;
					tabuleiro[k][m] = cor;
				} 
			}
			}
		}
	
}

void escolhejogada(int tabuleiro[max][max], int cor, int *linha, int *coluna){
	// Função para o computador escolher uma jogada
	int a, b, l, c, k, m, li = -1, co = -1, outracor, passou = 0, passei = 0;
	int posicoes[20][3], n = 0, pontos;
	int min = 50, mx = 0, mxl;
	
	outracor = -cor;
	
	// zerando matriz de posicoes que armazenara as posicoes possiveis e os pontos ganhos
	for(l = 0; l < 20; l++)
		for(c = 0; c < 3; c++)
			posicoes[l][c] = 0;

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
							if(k >= 0 && m>=0 && m<8 && k<8)
							if((tabuleiro[k][m] == cor) && passou){
								pontos++;
								if(posicoes[n-1][0] == l && posicoes[n-1][1] == c){
									posicoes[n-1][2] += pontos - 1;
								} else {
									posicoes[n][0] = l;
									posicoes[n][1] = c;
									posicoes[n][2] = pontos;
									n++;
								}
							} else	passou = 0;
						}
				}
			} 
	
	// encontrando mínimo e máximo de pontos
	for(n = 0; n < 20 && posicoes[n][2] != 0; n++){
		if(posicoes[n][2] < min) min = posicoes[n][2];
		if(posicoes[n][2] > mx)  { 	mx = posicoes[n][2];	mxl = n;}
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

int calcula(int tabuleiro[max][max], int cor){
	int i, j, soma = 0;
	
	for(i = 0; i < max; i++)
		for(j = 0; j < max; j++)
			if (tabuleiro[i][j] == cor) soma++;

	return (soma);
}

