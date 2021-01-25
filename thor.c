/* * * * * * * * * * * * * *docstrings* * * * * * * * * * * * * * *
*       THOR - simulador de consumo de energia                    *
*                                                                 *
* O módulo common.c contém algumas funções, métodos e constantes  *
* utilizadas nesse modulo, o principal.                           *
*                                                                 *
* Programador: Anaxímeno Brito                                    *
* Recolha de dados e Roteiro: Vitor Sancha                        *
* Licensa: Undefined TODO: Colocar licensa aqui                   *
*                                                                 *
* Docente: Artemisa Moreno                                        *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.c"


int main()
{
	// define a estrutura setor com uma máx. de elemento STRUCTMAX,
	// definido no módulo common.c
	struct setores setor[STRUCTMAX];
	// inicializa metodos do setor com seus respectivos valores iniciais
	setor->counter = 0;
	setor->consumo_eletrico = 0;
	setor->escudos_consumidos = 0;
	setor->aparelho->counter = 0;
	setor->aparelho->escudos_consumidos = 0;

	int index, again, i;
	float valor_unitario, escudos_consumidos, consumo_e_taxas, total_a_pagar;

	printf("\n# SEJA BEMVINDO(A) ao Simulador de Consumo de Energia: TH0R\n");
	while(1){
		switch(menu()) {
			case 1:
				add_setor(setor);
				break;
			case 2:
				if (show_setores_disponiveis(setor)) {
					printf("\nNúmero do setor a adicionar aparelho: ");
					scanf(" %d", &index);
					cleanBuf();

					if (setor->counter > 0 && index >= 0 && index < setor->counter){	
						do {
							printf("\n\t* %s *\n", setor[index].nome);
							add_aparelho(setor, index);

							printf("\n* Quer adicionar outro aparelho ao setor %s? (1 - sim | 0 - não): ", setor[index].nome);
							scanf("%d", &again);
							cleanBuf();
						} while(again);
					} else
						printf("\n* Setor inválido, escolha um dos setores disponíveis\n");

				} else
					printf("Nenhum setor disponível! Adiciona setores na opção 1 e depois volta para cá.\n");
				break;
			case 3:
				printf("Escreva o valor unitário atual da Tarifa Residêncial de Baixa Tensão: ");
				scanf("%f", &valor_unitario);

				escudos_consumidos = calcular_escudos_consumidos(setor, valor_unitario);
				consumo_e_taxas = escudos_consumidos + TAXA_RTC + IP_CONTRIB + ALUGER;
				total_a_pagar =  consumo_e_taxas + (consumo_e_taxas * IVA);

				for(i = 0 ; i < setor->counter ; ++i)
					show_dados_setor(setor, i);

				printf("\n** O valor total de escudos a pagar é %.2fCVE\n", total_a_pagar);
				exit(0);
				break;
			default:
				printf("\n* Opção desconhecida!\n");
		}
	}
	return 0;
}
