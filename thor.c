/* * * * * * * * * * * * * *docstrings* * * * * * * * * * * * * * *
*     THOR - simulador de consumo de energia | Versão 2021.1      *
*                                                                 *
* O módulo common.c contém algumas funções, métodos e constantes  *
* utilizadas nesse modulo, o principal.                           *
*                                                                 *
* Programador: Anaxímeno Brito, EIC 1º Ano                        *
* System Design e Roteiro: Vitor Sancha, EIC 1º Ano               *
* Licensa: MIT License                                            *
*                                                                 *
* Cadeira: Introdução à Programação                               *
* Docente: Artemisa Moreno                                        *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.c"


int main()
{
	// define a estrutura setor com um máx. de elemento STRUCTMAX,
	// definido no módulo common.c
	SETOR ArraySetor[STRUCTMAX];

	// inicializa os campos do setor com seus respectivos valores iniciais
	ArraySetor->counter = 0;
	ArraySetor->consumo = 0;
	ArraySetor->cve_gasto = 0;
	ArraySetor->aparelho->counter = 0;
	ArraySetor->aparelho->cve_gasto = 0;
	ArraySetor->aparelho->consumo = 0;

	int index, again, i;
	float unit_val, cve_gasto, val_taxado, total_a_pagar;

	printf("\n# SEJA BEMVINDO(A) ao Simulador de Consumo de Energia: TH0R\n");

	while (TRUE) 
	{

		switch (menu()) 
		{

			case 1:
				add_setor(ArraySetor);
				break;

			case 2:

				if (show_setores_disponiveis(ArraySetor)) {

					printf("\nNúmero do setor a adicionar aparelho: ");
					scanf(" %d", &index);
					cleanBuf();

					if (ArraySetor->counter > 0 && index >= 0 && index < ArraySetor->counter) {	

						do 
						{

							printf("\n\t* %s *\n", ArraySetor[index].nome);

							add_aparelho(ArraySetor, index);

							printf("\n* Quer adicionar outro aparelho ao setor %s? [1 - sim | 0 - não]: ", 
							    ArraySetor[index].nome);
							scanf("%d", &again);
							cleanBuf();

						} while(again);

					} else
						printf("\n* Setor inválido, escolha um dos setores disponíveis\n");

				} else
					printf("Nenhum setor disponível! Adiciona setores na opção 1 e depois volta para cá.\n");
				
				break;

			case 3:
			
				printf("Escreva o atual valor unitário da Tarifa Residêncial de Baixa Tensão: ");
				scanf("%f", &unit_val);

				cve_gasto = calcular_cve_gasto(ArraySetor, unit_val);
				val_taxado = cve_gasto + TAXA_RTC + IP_CONTRIB + ALUGER;
				total_a_pagar =  val_taxado + (val_taxado * IVA);

				for(i = 0 ; i < ArraySetor->counter ; i++)
					show_dados_setor(ArraySetor, i);

				putchar('\n');
				printf("Total a Pagar:\n");
				printf("    -> Energia Consumida: %.2fKwh\n", gConsumo_eletrico_total);
				printf("    -> Valor Unitário:    *%.2f\n", unit_val);
				printf("    -> Gasto em escudos:  %.2fCVE\n", cve_gasto);
				printf("    -> IP_CONTRIB:        +%3dCVE\n", IP_CONTRIB);
				printf("    -> TAXA_RTC:          +%3dCVE\n", TAXA_RTC);
				printf("    -> ALUGER:            +%3dCVE\n", ALUGER);
				printf("    -> IVA:               +%3d%%\n", (int)(IVA*100));
				printf("## TOTAL A PAGAR: %.2fCVE\n", total_a_pagar);
				
				exit(0);

				break;

			default:

				printf("\n* Opção desconhecida!\n");

		}

	}
	
	return 0;

}
