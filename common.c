/* * * * * * * * * * * * * * * * * *docstrings* * * * * * * * * * * * * * * * * * * * 
* Este modulo esta a ser utilizado para guardar funções que serao utilizadas        *
* no modulo principal thor.c                                                        *
*                                                                                   *
* No que se refere a explicacoes dos codicos, a maioria encontra-se aqui em baixo,  *
* entao, so comentários realmente necessários serao adicionados aos codicos.        *
* Tambem foram usados nomes bastantes sugestivos o que facilita o entendimento do   *
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
*   float calcular_cve_gasto() -> calcula e retorna o consumo em escudos;           *
*   void show_dados_setor() -> mostra dados de cada setor;                          *
*   void analisar_dados() -> Analisa se todos os dados foram colocados;             *
*                                                                                   *
* Estruturas:                                                                       *
*   struct aparelhos -> "define" um aparelho                                        *
*   struct setores   -> "define" um setor                                           *
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


// var global para guardar o total de comsumo eletrico
float gConsumo_eletrico_total = 0;


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
    float consumo;
    float cve_gasto;
    // conta # de elementos introduzidos
    int counter;

} APARELHO;


typedef struct setores {

    char nome[NOMEMAX];
    APARELHO aparelho[STRUCTMAX];
    float consumo;
    float cve_gasto;
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

    putchar('\n');
    
    return opt;

}


void add_setor(SETOR ArraySetor[]) {

    while (TRUE) 
    {
        char input[NOMEMAX];

        printf("Escreva o nome de um setor(ou escreva -> sair, para terminar): ");
        gets(input);
        cleanBuf();

        if (strcmp(input, "sair") != 0) {

            strcpy(ArraySetor[ArraySetor->counter].nome, input);
            ArraySetor->counter++;

        } else break;

    }

}


int show_setores_disponiveis(SETOR ArraySetor[]) {

    if (ArraySetor->counter > 0) {

        int i;

        printf("Setores disponíveis:");

        for(i = 0 ; i < ArraySetor->counter ; i++)
            printf("\n%d -> %s", i, ArraySetor[i].nome);

        putchar('\n');

        return 1;

    } else return 0;

}


float consumo(float potencia, float hrs_dia, int dia_mes, int quantidade) {

    return ((hrs_dia * dia_mes) * potencia) * quantidade;

}


void add_aparelho(SETOR ArraySetor[], int index) {

    SETOR *setor = &ArraySetor[index];
    int *count = &setor->aparelho->counter;
    APARELHO *aparelho = &setor->aparelho[*count];

    cleanBuf();

    float watts, horas;
    int dias, qtdade;

    printf("Nome do aparelho: ");
    gets(aparelho->nome);
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
    aparelho->potencia = watts * 0.001;

    aparelho->hrs_dia = horas;
    aparelho->dia_mes = dias;
    aparelho->quantidade = qtdade;

    float consu = consumo(aparelho->potencia, horas, dias, qtdade);
    
    aparelho->consumo = consu;
    setor->consumo += consu;
    gConsumo_eletrico_total += consu;
    (*count)++;
}


float calcular_cve_gasto(SETOR ArraySetor[], float valor_unitario) {

    float valor_total = 0;
    int i, j;
    APARELHO *aparelho;

    for (i = 0 ; i < (ArraySetor->counter) ; i++) {
		
        for (j = 0 ; j < (ArraySetor[i].aparelho->counter) ; j++) {
            aparelho = &ArraySetor[i].aparelho[j];

            aparelho->cve_gasto =  aparelho->consumo * valor_unitario;
            ArraySetor[i].cve_gasto += aparelho->cve_gasto;
        
        } valor_total += ArraySetor[i].cve_gasto;

    } return valor_total;

}


void show_dados_setor(SETOR ArraySetor[], int index) {

    SETOR *setor = &ArraySetor[index];
    int i;

    printf("\n#### %s\n", setor->nome);
    printf("  Nome do aparelho:\t\t\tEnergia Consumida:\n");

    for(i = 0; i < setor->aparelho->counter ; i++) {

        printf("   * %s\t\t\t\t %.2fKwh\n", 
            setor->aparelho[i].nome, setor->aparelho[i].consumo);

    }

    printf("\n  Total Aparelhos: %d    |    Energia Total Consumida: %.2fKwh    |    Total Gasto: %.2fCVE\n", 
        setor->aparelho->counter, setor->consumo, setor->cve_gasto);
    printf("#### Fim do setor %s\n", setor->nome);

}
