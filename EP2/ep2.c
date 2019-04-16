/****************************************************************
    Nome: Lucy Anne de Omena Evangelista
    NUSP: 11221776

    Fonte e comentários: Usei uma função a mais (chamada carta) para calcular quantos pontos uma determinada carta dá.
    Estou com problemas para parar o cálculo de seno (a condição de parada não é cumprida).
    A função seno foi calculada com base nas aulas 9 e 10, da professora substituta do Carlos.
    	Variáveis:
    	x = recebe a semente do numero pseudo-randomico, e é atualizado ao longo do programa;
    	partidas = armazena a quantidade de simulacoes para cada limiar;
    	par = variável auxiliar que tem como objetivo atingir o valor de "partidas";
    	mao_usu / mao_mesa = Armazenam a pontuação do jogador e da mesa, para comparação futura;
   		score_usu / score_mesa = Variáveis para calcular a pontuação do jogador e da mesa, para cada limiar, dados os valores das mãos;
    	perc = com base em score_usu e score_mesa, calcula o percentual de sucesso para o jogador ganhar;
    	i = variável auxiliar para exibição dos asteríscos representativos do programa;
    
****************************************************************/
#include <stdio.h>
#define c1 9.10938356	// massa do eletron
#define c2 1.618033989	// numero de ouro

double modulo (double n);
double frac (double n);
double seno (double n);
double pseudorand (double x);
int carta (double x);

int main(){
	double x, perc;	
	int lim, partidas, par, score_usu, score_mesa, mao_usu, mao_mesa, i;
	
	printf("Digite a semente (0 < x < 1): ");
	scanf("%f", &x);
	printf("\nDigite o numero de simulacoes para cada limiar: ");
	scanf("%d", &partidas);

	for(lim = 12;lim <= 20;lim++){
		
		for(par = 0; par < partidas; par++){
			while (mao_usu < lim){
				mao_usu+= carta(x);
				x = pseudorand(x);
			}
			
			while (mao_mesa <= mao_usu){
				mao_mesa += carta(x);
				x = pseudorand(x);
			}
			
			if (mao_usu <= 21 && (mao_usu > mao_mesa || mao_mesa > 21))
				score_usu++;
			else
				score_mesa++;
				
			mao_mesa = 0;
			mao_usu = 0;
		}
		
		perc = (float) score_usu/ (score_mesa + score_usu);
		printf("\n%d ( %2.1f%%) : ", lim, perc*100);
		
		for(i = 0; i < (100*perc); i++){
			printf("*");
		}
		
		score_usu = 0;
		score_mesa = 0;
		mao_usu = 0;
		mao_mesa = 0;
	}
	
return (0);
}

double modulo(double n){
	if (n < 0 )
		n = -n;
	return (n);
}

double frac(double n){
	int integer;
	double frac;
	integer = n; // verificar isso = funciona!
	frac = n - integer;
	return (frac);
}

double seno(double n){
	int k, fat, um;
	double sen, termo, elevado;
	sen = 0;
	elevado = n;
	termo = 0.;
	fat = 1;
	um = 1;
	
	for(k = 0;k < 10;k++){
		termo = elevado/fat;
		//printf("\n%f %d %d %d %f %f %f", n, k, fat, um, sen, termo, elevado);
		sen += um*termo;
		fat = fat * (2*k+2) * (2*k+3);
		elevado *= n * n;
		//if (termo <= 1e-8) printf("\nTRUE\n");
		um = -um;		
	}
	
	return (sen);
}

double pseudorand(double x){
	double x1;
	x1 = frac(c1 * modulo(seno(x)) + c2);
	return (x1);
}

int carta(double x){
	int carta;
	carta = 13 * x + 1;
	if (carta == 11 || carta == 12 || carta == 13)
		carta = 10;
	return (carta);
}
