/****************************************************************
    Nome: Lucy Anne de Omena Evangelista
    NUSP: 11221776

    Fonte e coment�rios: 
jogador: define se a jogada � do usuario ou do computador
jogada: se a jogada � S ou O
linha/coluna: entradas do jogador, estaveis
i/j: variaveis de intera��o
espacos_livres: condicao para o jogo continuar, de valor inicial 9
sos: quantidade de sos's no tabuleiro
score_usu/score_comp: variaveis para as pontua��es
config: configura��o do tabuleiro, em sua codifica��o em numero inteiro
****************************************************************/
// I can use a unique char variable

#include <stdio.h>

int potencia(int base, int potencia);
int tabuleiro(int codificacao);
int retorna_numero(int codificacao, int linha, int coluna);
int calcula_sos(int config);

int main(){
	int jogador, jogada, linha, coluna, i, j, espacos_livres, sos, score_usu, 
	score_comp, config, aux_config, dif, ok, jogada_comp;
	config = 0;		// variavel que armazena a configuracao do tabuleiro
	espacos_livres = 9;	
	jogada_comp = 0;	//variavel auxiliar para identificar a jogada do computador como valida
	score_comp = 0;
	score_usu = 0;
	sos = 0;		// variavel que conta a quantidade total de sos no tabuleiro
	i = 0;
	j = 0;
	ok = 0;			// variavel auxiliar para identificar a jogada do usuario como valida

printf("\n*** Bem-vindo ao Jogo do SOS! ***");
printf("\n\nDigite 1 se voce deseja comecar, ou 2 caso contrario:");
scanf("%d", &jogador);

printf("\nConfiguracao inicial:\n");
tabuleiro(config);
printf("\n\nO tabuleiro tem %d SOS(s)\nPlacar: Usuario %d x %d Computador", sos, score_usu, score_comp);

// O ciclo do jogo se inicia
while (espacos_livres != 0) {
	if (jogador % 2){ //jogador � o usu�rio caso o resto seja 1
		while(ok == 0){
			// Captando a jogada do usuario		
			printf("\n\nDigite sua jogada:\nDigite 1 para S, 2 para O: ");
			scanf("%d", &jogada);
			printf("\nDigite a linha: ");
			scanf("%d", &linha);
			printf("\nDigite a coluna: ");
			scanf("%d", &coluna);
			printf("\nTabuleiro apos sua jogada:\n");
			
			// Verificando se a jogada eh valida
			if (jogada <= 0 || jogada > 2) {
				printf("\n\nValor de posicao invalido. Refaca sua jogada.\n");
			} else {
				if (coluna < 1 || coluna > 3) { 
					printf("\n\nValor de coluna invalido. Refaca sua jogada.\n");
			} else {
				if (linha < 1 || linha > 3) { 
					printf("\n\nValor de linha invalido. Refaca sua jogada.\n");
			} else {
				if (retorna_numero(config, linha, coluna) != 0){
					printf("\n\nEssa posicao ja esta ocupada! Refaca sua jogada.\n posicao: %d\n", retorna_numero(config,linha,coluna));
			} else {
				ok = 1;
			}	
			}
			}
			}
		}
		
		} else {
			// inser��o de valor pelo pc		
			for(i = 1; i<=3;i++){
				for(j = 3; j > 0;j--){
					if (retorna_numero(config, i, j) == 0 && jogada_comp == 0){
						linha = i;
						coluna = j;
						jogada = ((3*(linha-1)+(coluna-1)) % 2) + 1;
						jogada_comp = 1;
					}
				}
			}
		printf("\nTabuleiro apos minha jogada:\n");	
		}
	// Calculando o novo valor de configuracao do tabuleiro
	config = config + jogada*potencia(3, 3*(linha-1)+(coluna-1)); 
	
	// Comparando o registro de sos, para verificar se algum ponto foi feito
	dif = calcula_sos(config) - sos;
	if (dif != 0){ 		// pontuando
		if (jogador % 2) {
			score_usu = score_usu + dif;
			printf("Voce marcou %d pontos. Jogue novamente.\n", dif);
			jogador++; //adiciona +1 para continuar com o mesmo jogador
			ok = 0;
		} else {
			score_comp = score_comp + dif;
			printf("Marquei %d pontos. Vou jogar novamente.\n", dif);
			jogador++;
			jogada_comp = 0;
		}
	}
	tabuleiro(config);	// Mostra o tabuleiro na nova configuracao
	sos = dif + sos;	// Atualiza o valor total de sos no tabuleiro
	printf("\n\nO tabuleiro tem %d SOS(s)\nPlacar: Usuario %d x %d Computador", sos, score_usu, score_comp);
	if (espacos_livres == 0){
		if (score_usu == score_comp){
			printf("\n\nEmpatamos!");
		} else {
			if(score_usu > score_comp){
				printf("\n\nVoc� ganhou!");
			} else {
				printf("\n\nEu ganhei!");
			}
		}
	}
	espacos_livres--;
	jogador++;
	ok = 0;
}

return 0;
}

int potencia(int base, int potencia){
	int i, produto;	
	produto = 1;	
	for (i = 0;i < potencia;i++){
		produto	= produto*base;
	}
	return(produto);
}

int retorna_numero(int codificacao, int linha, int coluna){
	// Funcao para retornar o numero na posicao, dado a linha e coluna
	int i, j,aux_cod;
	for (i = 0; i<linha; i++){
		for (j = 0; j<coluna; j++){
		aux_cod = codificacao % 3;
		codificacao = codificacao/3;
		}
	}
	return (aux_cod);
}

int tabuleiro(int codificacao){
	// Fun��o para tra�ar o tabuleiro
	int aux_cod, i, j, sos;
	char carac;
	for(i = 0; i<3;i++){
		for(j = 0; j<3;j++){
			// Captando o valor de cada posicao e retornando um novo valor para a config do tabuleiro
			aux_cod = codificacao % 3;
			codificacao = codificacao/3;
			if (aux_cod == 0) {
				carac = ' ';
			} else {
				if (aux_cod == 1) {
					carac = 'S';
				} else {
					carac = 'O';
				}
			}	
			printf("  %c  ", carac);
			if(j != 2) { printf("|"); }
		}
	printf("\n");
	if (i != 2) { printf("-----+-----+-----\n");}
	}
	sos = 0;
	return (sos);
}

int calcula_sos(int config){
	// Fun��o para varrer o tabuleiro e calcular a quantidade de SOS
	int sos, i, j, aux;
	sos = 0;
	
	for (i = 1; i<3;i++){
	// Verificando as colunas
		if ((retorna_numero(config, 1, i)==1 && retorna_numero(config, 2, i)==2 && retorna_numero(config, 3, i)==1)){
		printf("linha - i: %d - %d - %d - %d\n", i, retorna_numero(config, 1, i),retorna_numero(config, 2, i),retorna_numero(config, 3, i) );
		sos++;
		}
	//Verificando as linhas
		if ((retorna_numero(config, i, 1)==1 && retorna_numero(config, i, 2)==2 && retorna_numero(config, i, 3)==1)){
		printf("coluna- i: %d - %d - %d - %d\n", i, retorna_numero(config, i, 1),retorna_numero(config, i, 2),retorna_numero(config, i, 3) );
		sos++;
		}
	}
	//Verificando as diagonais
	if (retorna_numero(config, 2,2) == 2){
		if (retorna_numero(config, 1,1)==1 && retorna_numero(config, 3, 3)==1)
			{ sos++; }
		if (retorna_numero(config, 1,3)==1 && retorna_numero(config, 3, 1)==1)
			{ sos++; }
	}
	return (sos);
}

