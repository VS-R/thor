/* * * * * * * * * * * * * *docstrings* * * * * * * * * * * * * * *
*     THOR - simulador de consumo de energia | Versao 2021.1      *
*                                                                 *
* O modulo common.c contem algumas funcoes, metodos e constantes  *
* utilizadas nesse modulo, o principal.                           *
*                                                                 *
* Programador: Anaximeno Brito, EIC Primeiro Ano                  *
* System Design e Documentacao: Victor Sancha, EIC Primeiro Ano   *
* Licensa: MIT License                                            *
*                                                                 *
* Cadeira: Introducao A  Programacao                              *
* Docente: Artemisa Moreno                                        *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.c"


int main()
{
	// define a estrutura setor com um max. de elemento STRUCTMAX,
	// definido no modulo common.c
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

					printf("\nNumero do setor a adicionar aparelho: ");
					scanf(" %d", &index);
					cleanBuf();

					if (ArraySetor->counter > 0 && index >= 0 && index < ArraySetor->counter) {	

						do 
						{

							printf("\n\t* %s *\n", ArraySetor[index].nome);

							add_aparelho(ArraySetor, index);

							printf("\n* Quer adicionar outro aparelho ao setor %s? [1 - sim | 0 - nao]: ", 
							    ArraySetor[index].nome);
							scanf("%d", &again);
							cleanBuf();

						} while(again);

					} else
						printf("\n* Setor invalido, escolha um dos setores disponiveis\n");

				} else
					printf("Nenhum setor disponivel! Adiciona setores na opcao 1 e depois volta para ca.\n");
				
				break;

			case 3:
			
				printf("Escreva o atual valor unitario da Tarifa Residencial de Baixa Tensao: ");
				scanf("%f", &unit_val);

				cve_gasto = calcular_cve_gasto(ArraySetor, unit_val);
				val_taxado = cve_gasto + TAXA_RTC + IP_CONTRIB + ALUGER;
				total_a_pagar =  val_taxado + (val_taxado * IVA);

				for(i = 0 ; i < ArraySetor->counter ; i++)
					show_dados_setor(ArraySetor, i);

				putchar('\n');
				printf("Total a Pagar:\n");
				printf("    -> Energia Consumida: %.2fKwh\n", gConsumo_eletrico_total);
				printf("    -> Valor Unitario:    *%.2f\n", unit_val);
				printf("    -> Gasto em escudos:  %.2fCVE\n", cve_gasto);
				printf("    -> IP_CONTRIB:        +%3dCVE\n", IP_CONTRIB);
				printf("    -> TAXA_RTC:          +%3dCVE\n", TAXA_RTC);
				printf("    -> ALUGER:            +%3dCVE\n", ALUGER);
				printf("    -> IVA:               +%3d%%\n", (int)(IVA*100));
				printf("## TOTAL A PAGAR: %.2fCVE\n", total_a_pagar);
				
				exit(0);

				break;

			default:

				printf("\n* Opcao desconhecida!\n");

		}

	}
	
	return 0;

}