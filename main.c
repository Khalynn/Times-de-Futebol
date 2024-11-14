#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Macros dos limites de valores
#define times_quant 6
#define rodadas_quant 5

// Struct do time, aqui é onde armazena os detalhes dos times.  
typedef struct {
	char nome[50];
	int vitorias, derrotas, empates, gols_marc, gols_sorf, pontos;  
} Time; 

// Função para selecionar o nome dos times com sua estrutura em questão.
void selecionarTimes(Time times[times_quant], char nomes[times_quant][50]) {
	// Cria um time com seus valores de acordo com o número limite de times possíveis (max: 6).
	for (int i = 0; i < times_quant; i++) {
		strcpy(times[i].nome, nomes[i]);
		times[i].vitorias = 0;
		times[i].derrotas = 0;
		times[i].empates = 0;
		times[i].gols_marc = 0;
		times[i].gols_sorf = 0;
		times[i].pontos = 0;
	}
}

// Função para randomizar os valores dos gols e mostrar o resultado geral da rodada.
void colocarResultado(Time *time1, Time *time2) {
	int gols1, gols2;
	int escolha = rand() % 3;

	// Randomiza os valores dos gols entre 0 e 3 ou 2 e 1 ou 2 e 2.
	if (rand() % 2 == 0) {
		// Time 1 com vantagem
		 if (escolha == 0) {
            gols1 = 3;
            gols2 = 1;
        } 

        else if (escolha == 1) { // Empate
        	gols1 = 2;
        	gols2 = 2;
        }

        else {
            gols1 = 3;
            gols2 = 0;
        }
	}

	else {
		// Time 2 com vantagem
		if (escolha == 0) {
            gols1 = 1;
            gols2 = 3;
        }

        else if (escolha == 1) { // Empate
        	gols1 = 2;
        	gols2 = 2;
        }

        else {
            gols1 = 0;
            gols2 = 3; 
        }
	}

	printf("Resultado: %s - %d x %d - %s\n", time1->nome, gols1, gols2, time2->nome);

	// Distribuição de gols marcados e sofridos com base nos gols.
	time1->gols_marc += gols1;
	time1->gols_sorf += gols2;
	time2->gols_marc += gols2;
	time2->gols_sorf += gols1;

	// Distribuição de pontos, vitórias e derrotas
	if (gols1 > gols2) {
		time1->pontos += 3;
		time1->vitorias++;
		time2->derrotas++;
	} 

	else if (gols1 < gols2) {
		time2->pontos += 3;
		time2->vitorias++;
		time1->derrotas++;
	} 

	else {
		time1->pontos += 1;
		time2->pontos += 1;
		time1->empates++;
		time2->empates++;
	}
}

// Função que realiza as rodadas, tanto com quem será feito as mesmas quanto para mostrar seu resultado.
void realizarRodadas(Time times[times_quant]) {
	// Times que irão se enfrentar, de maneira que não haja repetição.
	// Combinação de jogos, total 15 combinações para 6 times.
	int rodadas[rodadas_quant][3][2] = {
		{{0, 1}, {2, 3}, {4, 5}},
        {{0, 2}, {1, 4}, {3, 5}},
        {{0, 3}, {1, 5}, {2, 4}},
        {{0, 4}, {1, 3}, {2, 5}},
        {{0, 5}, {1, 2}, {3, 4}}
	};

	// Mostra o resultado da rodada específica, em seguida inseri as variáveis do resultado.
	for (int i = 0; i < rodadas_quant; i++) {
		printf("\nRodada %d:\n", i + 1);

		for (int j = 0; j < 3; j++) {
			colocarResultado(&times[rodadas[i][j][0]], &times[rodadas[i][j][1]]);
		}
	}
}

// Função para comparar os times de acordo com gols marcados e sofridos.
int compararTimes(const void *a, const void *b) {
	Time *time1 = (Time *)a;
	Time *time2 = (Time *)b;

	if (time1->pontos != time2->pontos) {return time2->pontos - time1->pontos;}

	int comparacao1 = time1->gols_marc - time1->gols_sorf;
	int comparacao2 = time2->gols_marc - time2->gols_sorf;

	if (comparacao1 != comparacao2) {return comparacao2 - comparacao1;}

	if (time1->gols_marc != time2->gols_marc) {return time2->gols_marc - time1->gols_marc;}

	return time2->vitorias - time1->vitorias;
}

// Função que organiza as informações do resultado.
void ordenarClassificacao(Time times[times_quant]) {
	qsort(times, times_quant, sizeof(Time), compararTimes);
}

// Função que mostra a classificação dos times em ordem crescente e os resultados específicos de cada um.
void mostrarClassific(Time times[times_quant]) {
	printf("\nClassificacao: \n");
	printf("%-21s %4s %4s %4s %4s %4s %4s\n", "Times", "Vit", "Der", "Emp", "G.M", "G.S", "Pts");

	for (int i = 0; i < times_quant; i++) {
		printf("%-20s %4d %4d %4d %4d %4d %4d\n", 
			times[i].nome, times[i].vitorias, times[i].derrotas, times[i].empates,
			times[i].gols_marc, times[i].gols_sorf, times[i].pontos);
	}
}

int main() {
	srand(time(NULL)); // Função que faz os resultados serem os mais aleatórios possíveis.

	Time times[times_quant];
	char nomes[times_quant][50] = {"Time A", "Time B", "Time C", "Time D", "Time E", "Time F"};

	// Invoca as funções já citadas anteriormente
	selecionarTimes(times, nomes);
	realizarRodadas(times);

	ordenarClassificacao(times);
	mostrarClassific(times);

	scanf(".");
	return 0;
}
