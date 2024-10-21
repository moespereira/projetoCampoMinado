#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define FACIL 10
#define MEDIO 20
#define DIFICIL 30

//aqui é criado cada célula da matriz para facilitar a identificação de acordo com o preenchimento do jogo.
typedef struct{
	int temMina; //flag de mina - verifica se a jogada x,y do jogador tem uma mina;
	int abertura; //flag de jogada já realizada - verifica se a jogada x,y do jogador já foi realizada
	int vizinho; //contador de minas - identifica a quantidade de minas ao redor da jogada x,y do jogador
}Coordenada;

Coordenada** preencheCampo(int); 				//inicia o campo com todos os elementos = 0
void minarCampo(int, int, Coordenada**); 		//insere as minas no campo
void preencheVizinhos(int, Coordenada**);   	//preenche a área ao redor da mina (contador de minas)
int vizinhanca(int, int, int, Coordenada**); 	//realiza a contagem das de células vizinhas às minas
int validaCoordenada(int, int, int); 			//verifica se a coordenada x,y do jogador é valida
void jogada(int, Coordenada**); 				//início da jogada com a entrada das coordenadas x,y do jogador no teclado
void abrirCampo(int, int, int, Coordenada**);   //mostra as células com ao redor das minas
int vencedor(int, Coordenada**);				//identifica se o jogador venceu ou perdeu a partida
void imprimeCampo(int, Coordenada**); 			//imprime o campo no decorrer da partida ou ao vencer a apartida
void imprimeCampoFinal(int, Coordenada**); 		//imprime o campo ao perder a partida


int main(){
	char dificuldade, novojogo, alterar;
	printf("Escolha a dificuldade do jogo:\n"); //primeira impressão da tela, mostra as opções de dificuldade
	printf("F = FACIL\n");						// 3 minas
	printf("M = MEDIUN\n"); 					// 6 minas
	printf("D = DIFÍCIL\n"); 					// 9 minas
	printf("S = SAIR\n");
	
	int qtdminas, nivel;						//variáveis da main
	Coordenada **jogo = NULL;					//minha matriz do jogo. Iniciada com o NULL pois ainda será selecionada a dificuldade
	while(1){									//loop para seleção de dificuldade VÁLIDA ou sair do jogo 
		if (scanf(" %c", &dificuldade) != 1 || !isalpha(dificuldade)) {		//verifica se a entrada é uma letra do alfabeto
            printf("\n\tEntrada inválida, tente novamente.\n");
            while (getchar() != '\n'); 										// Limpa o buffer de entrada
            continue;
		}
		dificuldade = toupper(dificuldade);									//modifica para MAIUSCULO
		if(dificuldade == 'F' || dificuldade == 'M' || dificuldade == 'D' || dificuldade == 'S') break; //comparador de entrada válida
		else{
			 printf("\n\tEntrada inválida, tente novamente.\n");
            while (getchar() != '\n'); 										// Limpa o buffer de entrada
		}
	}

	if(dificuldade == 'S') return 0;										//finaliza o jogo
	else if(dificuldade == 'F'){
		nivel = FACIL;
		qtdminas = 3;
	}else if(dificuldade == 'M'){
		nivel = MEDIO;
		qtdminas = 6;
	}else if(dificuldade == 'D'){ 
		nivel = DIFICIL;
		qtdminas = 9;
	}

	jogo = preencheCampo(nivel); 											//chamada de função para iniciar a matriz do jogo
	minarCampo(nivel, qtdminas, jogo); 										//implanta as minas na matriz
	preencheVizinhos(nivel, jogo);											//preenche células vizinhas das minas
	jogada(nivel, jogo);													//inicia o jogo
		
	//limpador / desalocador de memória
	//primeiro desaloca o vetor interno
	//depois desaloca o vetor principal
	for(int i = 0; i < nivel; i++){
		free(jogo[i]);
		}
	free(jogo);
	
	return 0;
}

	/*Iniciação da matriz do jogo*/
Coordenada** preencheCampo(int tamanho){
	Coordenada **jogo = (Coordenada**) malloc(tamanho * sizeof(Coordenada*)); //alocação do vetor de vetor
	
	if (jogo == NULL) return NULL;
	for(int i = 0; i < tamanho; i++){
		jogo[i] = (Coordenada*) malloc(tamanho * sizeof(Coordenada)); //alocação do vetor de cada elemento do vetor acima
		if(jogo[i] == NULL){
			for(int j = 0; j < tamanho; j++){
				free(jogo[j]);
			}
			return NULL;
		}
	}
	// inicia o vetor com todas as coordenadas do jogo zeradas
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			jogo[i][j].abertura = 0;
			jogo[i][j].vizinho = 0;
			jogo[i][j].temMina = 0;
		}
	}
	return jogo;
}
	//implanta as minas na matriz

void minarCampo(int tamanho, int minas, Coordenada **jogo){
	int linha, coluna;
	srand(time(NULL)); //semente
	
	for(int i = 1; i <= minas; i++){ //tem que iniciar de 1 pois se iniciar de 0, sempre terá uma mina nas bordas
		linha = rand() % tamanho;		//seleceiona uma linha aleattória de entre 1 e 'minas' (definida pela dificuldade)
		coluna = rand() % tamanho;		//seleceiona uma coluna aleattória de entre 1 e 'minas' (definida pela dificuldade)
		if(jogo[linha][coluna].temMina == 0) jogo[linha][coluna].temMina = 1;
		else i--; 
	}
}
	//validador de linha e coluna

int validaCoordenada(int lin, int col, int tamanho){ //retorna 1 para uma coordenada válida ou 0 para uma não válida
	return (lin >= 0 && lin < tamanho && col >= 0  && col < tamanho); //para retornar 1, a coordenada tem que estar dentro da matriz
}
	//preenche as células vizinhas das minas

void preencheVizinhos(int tamanho, Coordenada **jogo){
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			jogo[i][j].vizinho = vizinhanca(i, j, tamanho, jogo);
		}
	}
}

	//conta e retorna a quantidade de minas existentes ao redor posição x, y fornecida pelo usuário

int vizinhanca(int lin, int col, int tamanho, Coordenada **jogo){
	int quantidade = 0;
	if(validaCoordenada(lin - 1, col, tamanho) && jogo[lin - 1][col].temMina) quantidade++;
	if(validaCoordenada(lin + 1, col, tamanho) && jogo[lin + 1][col].temMina) quantidade++;	
	if(validaCoordenada(lin, col + 1, tamanho) && jogo[lin][col + 1].temMina) quantidade++;	
	if(validaCoordenada(lin, col - 1, tamanho) && jogo[lin][col - 1].temMina) quantidade++;	
	if(validaCoordenada(lin - 1, col - 1, tamanho) && jogo[lin - 1][col - 1].temMina) quantidade++;	
	if(validaCoordenada(lin - 1, col + 1, tamanho) && jogo[lin - 1][col + 1].temMina) quantidade++;	
	if(validaCoordenada(lin + 1, col - 1, tamanho) && jogo[lin + 1][col - 1].temMina) quantidade++;	
	if(validaCoordenada(lin + 1, col + 1, tamanho) && jogo[lin + 1][col + 1].temMina) quantidade++;

	return quantidade;
}
	//caso a posição x, y selecionada seja = 0, esta função abre a matriz até que ache uma posição com flag de abertura != 0
	//caso ela ache uma posição x, y com o flag de vizinho != 0, ela para a abertura da matriz
	//o flag de vizinho é calculado na função preencheVizinhos()

void abrirCampo(int l, int c, int tamanho, Coordenada** jogo){
	if(validaCoordenada(l, c, tamanho) == 1 && jogo[l][c].abertura == 0){
		jogo[l][c].abertura = 1;
		if(jogo[l][c].vizinho == 0){
			abrirCampo(l-1, c, tamanho, jogo);
			abrirCampo(l+1, c, tamanho, jogo);
			abrirCampo(l, c-1, tamanho, jogo);
			abrirCampo(l, c+1, tamanho, jogo);
			abrirCampo(l-1, c-1, tamanho, jogo);
			abrirCampo(l-1, c+1, tamanho, jogo);
			abrirCampo(l+1, c-1, tamanho, jogo);
			abrirCampo(l+1, c+1, tamanho, jogo);
		}
	} 
}
	/*verifica a quantidade de jogadas do usuário e se cada jogada está livre de mina
	caso tenha um flag de mina ou de abertura, ele para a contagem e retorna a quantidade e o jogo continua
	esse loop pode rodar até a quantidade de  posições x, y seja tamanho * tamanho - minas */

int vencedor(int tamanho, Coordenada** jogo){
	int quantidade = 0;
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			if(jogo[i][j].abertura == 0 && jogo[i][j].temMina == 0) quantidade++;
		}
	}
	return quantidade;
}
	//inicia a jogada do usuário

void jogada(int tamanho, Coordenada** jogo){
    int linha, coluna;
    do {
        imprimeCampo(tamanho, jogo); //primeira impressão do Campo Minado com todas as posições mostrando a letra X
        do {
            if(scanf("%d %d", &linha, &coluna) != 2){ //verifica se a entrada x, y são um par de inteiros
				printf("\nEntrada inválida. Por favor, insira dois números inteiros.\n");
            	while (getchar() != '\n'); // Limpa o buffer de entrada
            	continue;
			}
            linha--; // Ajuste para índice zero
        	coluna--; // Ajuste para índice zero
			
			//este if verifica se a posição está dentro da matriz do jogo e se essa posição já foi jogada anteriormente
			if(validaCoordenada(linha, coluna, tamanho) == 0 || jogo[linha][coluna].abertura == 1){
            	printf("\nJogada inválida ou já jogada\n");
            }
		//loop parecido com o if acima, ele vai continuar solicitando a entrada de x, y até acabar o jogo
    	}while(validaCoordenada(linha, coluna, tamanho) == 0 || jogo[linha][coluna].abertura == 1);
        
		/*função de abrir a matriz do jogo caso o flag de vizinho seja 0, ele vai abrir o jogo até achar uma
		 posição x, y com flag de vizinho != 0, ou seja, 2 posições antes de uma mina*/
		abrirCampo(linha, coluna, tamanho, jogo);

		/*chama a função vencedor explicada acima, com a adição de que verifica se a posição x, y tem mina
		caso tenha, o loop é encerado e caso não tenha, ele vai rodar até que a função vencedor() retorne 0
		se tiver mina, o loop é encerrado*/
	}while(vencedor(tamanho, jogo) != 0 && jogo[linha][coluna].temMina == 0);
    
	/*impressão final*/
	if(jogo[linha][coluna].temMina == 1) {
        printf("Game Over\n");
		imprimeCampoFinal(tamanho, jogo);
    }else{
        printf("Parabéns, vc eh fera\n");
		imprimeCampo(tamanho, jogo);
    }
}
	/*impressção do vencedor
	imprime toda a matriz e a posição da mina fica marcada com um X*/

void imprimeCampo(int tamanho, Coordenada** jogo){
	printf("\n\n\t   ");
	for(int i = 0; i < tamanho; i++) printf("  %02d", i+1); //POSIÇÃO DAS LINHAS
	printf("\n\t    ");
	for(int i = 0; i < tamanho / 10; i++) printf("----------------------------------------");
	printf("\n");
	int mina = -1;
	for(int i = 0; i < tamanho; i++){
		printf("\t%02d |", i+1); //POSIÇÃO DAS COLUNAS
		for(int j = 0; j < tamanho; j++){
			if(jogo[i][j].abertura){
				if(jogo[i][j].temMina){printf(" %d ", mina);}
				else {printf(" %d ", jogo[i][j].vizinho);}
			}else printf(" X ");

			printf("|");
		}
		//printf("\n\t  -------------------------------------------\n");
		printf("\n\t");
		printf("   ");
		for(int i = 0; i < tamanho / 10; i++) printf("----------------------------------------");
		printf("\n");
	}
}
	/*impressão do perdedor
	imprime toda a matriz e a posição com minha fica marcada com -1*/

void imprimeCampoFinal(int tamanho, Coordenada** jogo){
	//tabulaçao da matriz
	printf("\n\n\t   ");
	for(int i = 0; i < tamanho; i++) printf("  %02d", i+1); //POSIÇÃO DAS LINHAS
	printf("\n\t    ");
	for(int i = 0; i < tamanho / 10; i++) printf("----------------------------------------");
	printf("\n");
	
	for (int i = 0; i < tamanho; i++){
		printf("\t%02d  |", i+1); //posição das clunas
        for (int j = 0; j < tamanho; j++){
			//printf("\t  ");
            if (jogo[i][j].temMina == 1) printf("-1 ");
			else if (jogo[i][j].vizinho > 0) printf(" %d ", jogo[i][j].vizinho);
            else printf(" 0 ");
            
			printf("|");
        }
		printf("\n\t");
		printf("   ");
		for(int i = 0; i < tamanho / 10; i++) printf("-----------------------------------------");
		printf("\n");
	}
}
