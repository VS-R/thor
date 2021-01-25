/* * * * * * * * * docstrings * * * * * * * * * 
* Este módulo esta a ser utilizado para guardar 
* funções que serão utilizadas no modulo principal 
* main.c
*
* No que se refere a explicações dos códicos,
* a maioria encontra-se aqui abaixo, então,
* só comentários realmente necessários serão
* adicionados aos códicos. Também foram usados
* nomes bastantes sugestivos o que facilita o
* entendimento do processo.
* 
* Funções principais:
* TODO: coloca funções principais ali
* * * * * * * * * * * * * * * * * * * * * * * */

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


struct aparelhagem {
    char nome[NOMEMAX];
    float potencia;
    int quantidade;
    float hrs_dia;
    unsigned int dia_mes;
    float consumo_eletrico;
    float escudos_consumidos;
    // conta elementos introduzidos
    int counter;
};


struct setores {
    char nome[NOMEMAX];
    struct aparelhagem aparelho[STRUCTMAX];
    float consumo_eletrico;
    float escudos_consumidos;
    // conta elementos introduzidos
    int counter;
};


int menu(void) {
    int opt;
    printf("\n ** Escolha uma das opções abaixo **\n");
    printf("1 -> Adicionar Setores;\n");
    printf("2 -> Adicionar aparelhos para setores;\n");
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


float consumo(float potencia, float hrs_dia, int dia_mes, int quantidade) {
    return ((hrs_dia * dia_mes) * potencia) * quantidade;
}


void add_aparelho(struct setores setor[], int index) {
    int * count = &setor[index].aparelho->counter;
    setbuf(stdin, NULL);
    float watts, horas;
    int dias, qtdade;

    printf("Nome do aparelho: ");
    gets(setor[index].aparelho[*count].nome);
    printf("Quantidade: ");
    scanf("%d", &qtdade);
    printf("Potência em watts do aparelho: ");
    scanf("%f", &watts);
    printf("Horas de uso por dia: ");
    scanf("%f", &horas);
    printf("Dias de uso por mes: ");
    scanf("%d", &dias);
    setbuf(stdin, NULL);

    // transforma potência de watts para kilowatts
    setor[index].aparelho[*count].potencia = watts * 0.001;
    
    setor[index].aparelho[*count].hrs_dia = horas;
    setor[index].aparelho[*count].dia_mes = dias;
    setor[index].aparelho[*count].quantidade = qtdade;

    float consu = consumo(setor[index].aparelho[*count].potencia, horas, dias, qtdade);
    setor[index].aparelho[*count].consumo_eletrico = consu;
    setor[index].consumo_eletrico += consu;

    (*count)++;
}


float calcular_escudos_consumidos(struct setores setor[], float valor_unitario) {
    float valor_total = 0;
    int i, j;

    for (i = 0 ; i < setor->counter ; ++i) {
        for (j = 0 ; j < setor[i].aparelho->counter ; ++j) {
            setor[i].aparelho[j].escudos_consumidos =  setor[i].aparelho[j].consumo_eletrico * valor_unitario;
            setor[i].escudos_consumidos += setor[i].aparelho[j].escudos_consumidos;
        }
        valor_total += setor[i].escudos_consumidos;
    }

    return valor_total;
}

void show_dados_setor(struct setores setor[], int index){
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