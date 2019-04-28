/****************************************************************
    Nome: Lucy Anne de Omena Evangelista
    NUSP: 11221776

    Fonte e comentários: Usei uma função a mais (chamada carta) para calcular quantos pontos uma determinada carta dá.
    A função seno foi calculada com base nas aulas 9 e 10, da professora substituta do Carlos.
    Para as constantes selecionei constantes físicas com muitas casas decimais diferentes, contendo o número 9, que
    muda em pelo menos um fator cada casa decimal. Testando-se algumas, consegui uma boa variedade e para qualquer semente,
    quando os ensaios são muitos(>100000), o resultado da curva é praticamente igual para sementes !=. Para uma amostra de
    média 46192.7 jogadas se teve um desvio padrão de 138.8461 (0,3% da média), considerando-se 10000 ensaios para cada limite,
	semente 0.3267962, e que as cartas maiores ou iguais a 10 como equivalentes, por valerem 10 no jogo de 21.
    
****************************************************************/
#include <stdio.h>
#define c1 910.93835671	// massa do eletron (x10^-24)
#define c2 0.898755179	// constante de coulomb

double modulo (double n);
double frac (double n);
double seno (double n);
double pseudorand (double x);
int carta (double x);

int main(){
	double x, perc;	
	int lim, partidas, par, score_usu, mao_usu, mao_mesa, ok, i;
//	int cartas[10];
	ok = 1;
	
//	for (lim = 0; lim < 10; lim++){
//		cartas[lim] = 0;
//	}
	
	while (ok){
		printf("Digite a semente (0 < x < 1): ");
		scanf("%lf", &x);
		
		if (x>=1 || x<=0)
			prinft("\n\t Semente invalida!\n\tTente novamente.\n\n");
		else
			ok = 0;
	}
	
	while(ok == 0){
		printf("\nDigite o numero de simulacoes para cada limiar: ");
		scanf("%d", &partidas);
		
		if(partidas < 0)
			printf("\n\t Numero invalido!\n\tTente novamente.\n\n");
	}


	for(lim = 12;lim <= 20;lim++){
		
		for(par = 0; par < partidas; par++){
			// Jogada do usuario/jogador
			while (mao_usu < lim){
				mao_usu+= carta(x);
//				cartas[carta(x)-1]++;
				x = pseudorand(x);
			}
			
			// Jogada da canca
			while (mao_mesa <= mao_usu){
				mao_mesa += carta(x);
//				cartas[carta(x)-1]++;
				x = pseudorand(x);
			}
			
			// Atribuição de pontos
			if (mao_usu <= 21 && (mao_mesa > 21))
				score_usu++;
				
			mao_mesa = 0;
			mao_usu = 0;
		}
		
		// Mostrando a linha de percentual de jogos ganhos, para cada percentual
		perc = 100.0 * score_usu/ partidas;
		printf("\n%d ( %2.1f%%) : ", lim, perc);
		
		for(i = 0; i < perc; i++){
			printf("*");
		}
		
		score_usu = 0;
		mao_usu = 0;
		mao_mesa = 0;
	}
	
//	for(lim = 0; lim < 13; lim++){
//		printf("\nCarta %2d foi jogada %d vezes.", lim+1, cartas[lim]);
//	}
	
return (0);
}

double modulo(double n){
	if (n < 0 )
		n = -n;
	return (n);
}

double frac(double n){
	return (n - (int)n);
}

double seno(double n){
	int k, fat, um;
	double sen, termo, elevado;
	sen = 0;
	elevado = n;
	fat = 1;
	um = 1;
	
	for(k = 0, termo = 1; termo>1e-8; k++){
		termo = elevado/fat;
		sen += um*termo;
		fat = fat * (2*k+2) * (2*k+3);
		elevado *= n * n;
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
	//Função para retornar uma pontuação, dado uma carta encotrada a partir de x
	int carta;
	carta = 13 * x + 1;
	
	if (carta > 10)
		carta = 10;
	return (carta);
}
