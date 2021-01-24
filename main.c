#include <stdio.h>
#include <stdlib.h>

/*                    docstring
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

	while(1){
		switch (menu()) {
			case 1:
				add_setor(setor);
				break;
			case 2:
				// TODO: precisa ver se tem setores disponíveis
				show_setores(setor);
				printf("\nNúmero do setor a adicionar aparelho: ");
				scanf("%d", &index);
				setbuf(stdin, NULL);
				do{
					printf("\n\t* %s *\n", setor[index].nome);
					add_aparelho(setor, index);
					printf("\n* Quer adicionar outro aparelho ao setor %s? (1 - sim | 0 - não): ", setor[index].nome);
					scanf("%d", &again);
					setbuf(stdin, NULL);
				} while(again);
				break;
			case 3:
				// TODO: show stats and out exit!
				// TODO: mostrar comsumo por setor em ESCUDOS CVE
				exit(0);
				break;
			default:
				printf("\nOpção desconhecida!\n");
		}
	}
	return 0;
}
