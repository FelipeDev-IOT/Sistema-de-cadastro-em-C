#include <stdio.h>
#include <stdio.h>
#include "catalogo.h"

int main() {
    int escolha = 0;

    while (escolha != 5) {  
        exibir_menu_animado();

        printf("Digite a sua escolha: ");
        scanf("%d", &escolha);

        processar_escolha(escolha);
    }

    return 0;
}