/* * * * * * * * * * * * * * * * * *docstrings* * * * * * * * * * * * * * * * * * * * 
* Este módulo esta a ser utilizado para guardar funções que serão utilizadas        *
* no modulo principal thor.c                                                        *
*                                                                                   *
* No que se refere a explicações dos códicos, a maioria encontra-se aqui em baixo,  *
* então, só comentários realmente necessários serão adicionados aos códicos.        *
* Também foram usados nomes bastantes sugestivos o que facilita o entendimento do   *
* processo.                                                                         *
*                                                                                   *
* Funções principais:                                                               *
*   void cleanBuf() -> Limpar Buffer;                                               *
*   int menu() -> Mostra o menu e retorna a opção escolhida;                        *
*   void add_setor() -> adiciona um setor ao vetor de setores;                      *
*   int show_setores_disponiveis() -> mostra setores caso diponíveis e retorna 1,   *
*      caso não existam disponíveis retorna 0;                                      *
*   float consumo() -> calcula o consumo e retorna o resultado;                     *
*   void add_aparelho() -> adiciona um aparlho a um setor;                          *
*   float calcular_escudos_consumidos() -> calcula e retorna o consumo em escudos;  *
*   void show_dados_setor() -> mostra dados de cada setor;                          *
*   void analisar_dados() -> Analisa se todos os dados foram colocados;             *                                                      *
*                                                                                   *
* Estruturas:                                                                       *
*   struct aparelhos -> "define" um aparelho                                        *
*   struct setores -> "define" um setor                                             *
*                                                                                   *
*                                                                                   *
* Programador: Anaxímeno Brito, EIC 1º ano                                          *
* System Design e Roteiro: Vitor Sancha, EIC 1º ano                                 *
* Licensa: MIT License                                                              *
*                                                                                   *
* Cadeira: Introdução à Programação                                                 *
* Docente: Artemisa Moreno                                                          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes pré-definidas pelo roteiro do trabalho
#define IVA 0.15
#define TAXA_RTC 508
#define IP_CONTRIB 100
#define ALUGER 105
// máx. de elementos do vetor de tipo estrutura e strings de nomes,
// pode ser alterado para aceitar mais valores
#define STRUCTMAX 100
#define NOMEMAX 100

#define TRUE 1
#define False 0


// Tenta limpar o buffer
void cleanBuf(void) { 
    setbuf(stdin, NULL);
    fflush(stdin);
}


// typedef foi usado para criar um tipo simbólico
// para representar as estruturas abaixo.
typedef struct aparelhos {
    char nome[NOMEMAX];
    float potencia;
    int quantidade;
    float hrs_dia;
    int dia_mes;
    float consumo_eletrico;
    float escudos_consumidos;
    // conta # de elementos introduzidos
    int counter;
} APARELHO;


typedef struct setores {
    char nome[NOMEMAX];
    APARELHO aparelho[STRUCTMAX];
    float consumo_eletrico;
    float escudos_consumidos;
    // conta # de elementos introduzidos
    int counter;
} SETOR;


int menu(void) {
    int opt;
    printf("\n ** Escolha uma das opções abaixo **\n");
    printf("1 -> Adicionar Setores;\n");
    printf("2 -> Adicionar aparelhos para setores;\n");
    printf("3 -> Terminar e Estatísticas.\n");

    printf("\nSua opção: ");
    scanf("%d", &opt);
    cleanBuf();
    printf("\n");
    return opt;
}


void add_setor(SETOR setor[]) {
    while (TRUE) 
    {
        char input[NOMEMAX];
        printf("Escreva o nome de um setor(ou escreva -> sair, para terminar): ");
        gets(input);
        cleanBuf();
        if (strcmp(input, "sair") != 0) {
            strcpy(setor[setor->counter].nome, input);
            setor->counter++;
        } else break;
    }
}


int show_setores_disponiveis(SETOR setor[]) {
    if (setor->counter > 0) {
        int i;
        printf("Setores disponíveis:");
        for(i = 0 ; i < setor->counter ; ++i)
        printf("\n%d -> %s", i, setor[i].nome);
        printf("\n");
        return 1;
    } else return 0;
}


float consumo(float potencia, float hrs_dia, int dia_mes, int quantidade) {
    return ((hrs_dia * dia_mes) * potencia) * quantidade;
}


void add_aparelho(SETOR setor[], int index) {
    int * count = &setor[index].aparelho->counter;
    cleanBuf();
    float watts, horas;
    int dias, qtdade;

    printf("Nome do aparelho: ");
    gets(setor[index].aparelho[*count].nome);
    cleanBuf();
    printf("Quantidade: ");
    scanf(" %d", &qtdade);
    printf("Potência em watts do aparelho: ");
    scanf(" %f", &watts);
    printf("Horas de uso por dia: ");
    scanf(" %f", &horas);
    printf("Dias de uso por mes: ");
    scanf(" %d", &dias);
    cleanBuf();

    // transforma potência de watts para kilowatts
    setor[index].aparelho[*count].potencia = watts * 0.001;

    setor[index].aparelho[*count].hrs_dia = horas;
    setor[index].aparelho[*count].dia_mes = dias;
    setor[index].aparelho[*count].quantidade = qtdade;

    float consu = consumo(setor[index].aparelho[*count].potencia, horas, dias, qtdade);
    
    setor[index].aparelho[*count].consumo_eletrico = consu;
    setor[index].consumo_eletrico += consu;

    ++(*count);
}


float calcular_escudos_consumidos(SETOR setor[], float valor_unitario) {
    float valor_total = 0;
    int i, j;

    for (i = 0 ; i < setor->counter ; ++i) {
        for (j = 0 ; j < setor[i].aparelho->counter ; ++j) {
            setor[i].aparelho[j].escudos_consumidos =  setor[i].aparelho[j].consumo_eletrico * valor_unitario;
            setor[i].escudos_consumidos += setor[i].aparelho[j].escudos_consumidos;
        } valor_total += setor[i].escudos_consumidos;
    } return valor_total;
}


void show_dados_setor(SETOR setor[], int index){
    int i;
    printf("\n#### %s\n", setor[index].nome);
    printf("  Nome do aparelho:\t\t\tEnergia Consumida:\n");
    for(i = 0; i < setor[index].aparelho->counter ; ++i) {
        printf("   * %s\t\t\t\t %.2fKwh\n", 
        setor[index].aparelho[i].nome, setor[index].aparelho[i].consumo_eletrico);
    }
    printf("\n  Total Aparelhos: %d    |    Energia Total Consumida: %.2fKwh    |    Total Gasto: %.2fCVE\n", 
        setor[index].aparelho->counter, setor[index].consumo_eletrico, setor[index].escudos_consumidos);
    printf("#### Fim do setor %s\n", setor[index].nome);
}

/* IN DECISION
int analisar_dados(SETOR setor[]) {
	int opt = 0, i, j;
	if (setor->counter == 0) {
		printf("Nenhum setor foi introduzido, logo não será apresentado nenhum dado!\n");
		printf("Sair mesmo assim? [1 - sim | 0 - não]: ");
		scanf("%d", &opt);
		cleanBuf();
		if(opt) exit(0);
	} else {
		for(i = 0 ; i < setor->counter ; ++i)
			if (setor[i].aparelho->counter == 0) {
				printf("Nenhum aparelho foi introduzido ao setor %s!\n", setor[i].nome);
				printf("Sair mesmo assim? [1 - sim | 0 - não]: ");
				scanf("%d", &opt);
				cleanBuf();
				if (opt) exit(0);
			}
	}
	return 1;
}*/