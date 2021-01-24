#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*                    docstrings
 * O módulo common.c contém as funções que realizam a
 * maioria dos processos deste módulo.
 * */

#include "common.c"


int main()
{
	struct setores setor[STRUCTMAX];
	setor->counter = 0;
	setor->consumo = 0;
	setor->aparelho->counter = 0;

	int index, again, i;

	/* TODO: verify this;
	int tarifa_Residencial_electra;

	printf("Escreva o valor da Tarifa Residencial Cobrado pela ELECTRA: ");
	scanf("%lf", &tarifa_Residencial_electra); */

	printf("\n# SEJA BEMVINDO(A) ao Simulador de Consumo de Energia: TH0R\n");
	while(1){
		switch (menu()) {
			case 1:
				add_setor(setor);
				break;
			case 2:
				if (show_setores_disponiveis(setor)) {
					printf("\nNúmero do setor a adicionar aparelho: ");
					scanf("%d", &index);
					setbuf(stdin, NULL);

					if (setor->counter > 0 && index >= 0 && index < setor->counter){	
						do{
							printf("\n\t* %s *\n", setor[index].nome);
							add_aparelho(setor, index);

							printf("\n* Quer adicionar outro aparelho ao setor %s? (1 - sim | 0 - não): ", setor[index].nome);
							scanf("%d", &again);
							setbuf(stdin, NULL);
						} while(again);
					} else
						printf("\n* Setor inválido, escolha um dos setores disponíveis\n");

				} else
					printf("Nenhum setor disponível! Adiciona setores na opção 1 e depois volta para cá.\n");
				break;
			case 3:
				// TODO: show stats and out exit!
				// TODO: mostrar comsumo por setor em ESCUDOS CVE
				// printf("O consumo do primeiro setor %s é %fkwh\n", setor[0].nome, setor[0].consumo);
				exit(0);
				break;
			default:
				printf("\n* Opção desconhecida!\n");
		}
	}
	return 0;
}
