#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*                    docstrings
 * Este módulo esta a ser utilizado para guardar 
 * funções que serão utilizadas no modulo principal 
 * main.c
 *
 * No que se refere a explicações dos códicos,
 * a maioria encontra-se aqui abaixo, pelo que,
 * só comentários realmente necessários serão
 * adicionados aos códicos. Também foram usados
 * nomes bastantes sugestivos o que facilita o
 * entendimento do processo.
 * 
 * Funções principais:
 * TODO: coloca funções principais ali
 * */

// constantes pré-definidas pelo roteiro
#define IVA 0.15
#define TAXA_RTC 508
#define IP_CONTRIB 100
#define ALUGER 105
// máx. de elementos do vetor de tipo estrutura, e string de nomes
#define STRUCTMAX 100
#define NOMEMAX 100



// A variável counter nas estruturas abaixo serve
// para contar a quantidade de elementos introduzidos
struct aparelhagem {
    char nome[NOMEMAX];
    float potencia;
    int quantidade;
    float hrs_dia;
    unsigned int dia_mes;
    float consumo;
    int counter;
};


struct setores {
    char nome[NOMEMAX];
    struct aparelhagem aparelho[STRUCTMAX];
    float consumo;
    int counter;
};


int menu(void)
{
    int opt;
    printf("\n ** Escolha uma das opções abaixo **\n");
    /*
    * printf(" 1 - Ler o Valor da Tarifa Residêncial de Baixa tensão cobrado pela ELECTRA;\n");
    * printf(" 2 - Calcular o consumo de energia elétrica por setor da universidade;\n");
    */
    printf("1 -> Adicionar Setores;\n");
    printf("2 -> Adicionar aparelhos para setores\n");
    printf("3 -> Terminar e Estatísticas;\n");

    printf("\nSua opção: ");
    scanf("%d", &opt);
    setbuf(stdin, NULL);
    printf("\n");
    return opt;
}


void add_setor(struct setores setor[]) {
    while (1) {
        char input[NOMEMAX];
        printf("Escreva o nome de um setor(ou escreva -> sair, para terminar): ");
        gets(input);
        setbuf(stdin, NULL);
        if (strcmp(input, "sair") != 0) {
            strcpy(setor[setor->counter].nome, input);
            setor->counter++;
        } else break;
    }
}


int show_setores_disponiveis(struct setores setor[]) {
    if (setor->counter > 0) {
        int i;
        printf("Setores disponíveis:");
        for(i = 0 ; i < setor->counter ; ++i)
        printf("\n%d -> %s", i, setor[i].nome);
        printf("\n");
        return 1;
    } else return 0;
}


float consumo(float potencia, float hrs_dia, int dia_mes, int quantidade){
    return ((hrs_dia * dia_mes) * potencia) * quantidade;
}


void add_aparelho(struct setores setor[], int index) {
    int * count = &setor->aparelho->counter;
    float potencia_watts, hrs_dia;
    int dia_mes, quantidade;

    printf("Nome do aparelho: ");
    gets(setor[index].aparelho[*count].nome);
    printf("Quantidade: ");
    scanf("%d", &quantidade);
    printf("Potências em watts do aparelho: ");
    scanf("%f", &potencia_watts);
    printf("Horas de uso por dia: ");
    scanf("%f", &hrs_dia);
    printf("Uso em dias por mes: ");
    scanf("%d", &dia_mes);
    setbuf(stdin, NULL);

    // transforma potência em kilowatts
    setor[index].aparelho[*count].potencia = potencia_watts * 0.001;
    
    setor[index].aparelho[*count].hrs_dia = hrs_dia;
    setor[index].aparelho[*count].dia_mes = dia_mes;
    setor[index].aparelho[*count].quantidade = quantidade;
    
    float consu = consumo(setor[index].aparelho[*count].potencia, hrs_dia, dia_mes, quantidade);
    setor[index].aparelho[*count].consumo = consu;
    setor[index].consumo += consu;

    (*count)++;
}
