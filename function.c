#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "catalogo.h"

// Variáveis globais
Produto* produtos[MAX_PRODUTOS];
int code = 0;

// Função para validar nome do produto
int validar_nome_produto(const char* nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && !isspace(nome[i])) {
            return 0;
        }
    }
    return 1;
}

// Função para exibir texto com atraso
void print_with_delay(const char *str, int delay) {
    printf("%s", str);
    fflush(stdout);
    usleep(delay);
}

// Função para exibir o menu animado
void exibir_menu_animado() {
    const char* menu[] = {
        "*********************************************************************************\n",
        "*                                                                               *\n",
        "*                                Seja Bem-Vindo                                 *\n",
        "*                                                                               *\n",
        "*********************************************************************************\n",
        "*                                                                               *\n",
        "*                                                                               *\n",
        "*                                                                               *\n",
        "*                               Cadastre seu produto                            *\n",
        "*                                                                               *\n",
        "*                               Escolha uma Opção:                              *\n",
        "*                                                                               *\n",
        "*                               1- Cadastrar Produto...                         *\n",
        "*                               2- Buscar Produto Por ID...                     *\n",
        "*                               3- Listar Produtos Por Nome...                  *\n",
        "*                               4- Sair do Sistema...                           *\n",
        "*                                                                               *\n",
        "*********************************************************************************\n"
    };

    int num_lines = sizeof(menu) / sizeof(menu[0]);
    for (int i = 0; i < num_lines; i++) {
        print_with_delay(menu[i], 200000);  // Pausa de 100000 microssegundos (0.1 segundo) entre cada linha
    }
}

// Função para limpar a tela
void limpar_tela() {
    #ifdef _WIN32
        system("cls");  // Para Windows
    #else
        system("clear");  // Para Unix/Linux
    #endif
}

// Função para cadastrar produto
void cadastrar_produto() {
    int continuar = 1;

    while (continuar) {
        limpar_tela();  // Limpa a tela antes de mostrar o menu

        if (code >= MAX_PRODUTOS) {
            printf("Sistema cheio! Não é possível cadastrar mais produtos.\n");
            return;
        }

        // Alocando memória para o novo produto
        produtos[code] = (Produto*)malloc(sizeof(Produto));
        if (produtos[code] == NULL) {
            printf("Erro de alocação de memória.\n");
            return;
        }

        // Alocando memória para o nome do produto
        produtos[code]->nome = (char*)malloc(50 * sizeof(char));
        if (produtos[code]->nome == NULL) {
            printf("Erro de alocação de memória.\n");
            free(produtos[code]);
            return;
        }

        produtos[code]->id = code + 1;

        do {
            printf("Digite o nome do produto: ");
            scanf(" %49[^\n]", produtos[code]->nome);
            if (!validar_nome_produto(produtos[code]->nome)) {
                printf("Nome inválido! Use apenas letras e espaços.\n");
            }
        } while (!validar_nome_produto(produtos[code]->nome));

        printf("Digite o preço do produto: ");
        scanf("%f", &produtos[code]->preco);

        printf("Produto cadastrado com sucesso! ID: %d | Nome: %s | Preço: %.2f\n", produtos[code]->id, produtos[code]->nome, produtos[code]->preco);
        code++;

        // Perguntar se o usuário deseja cadastrar outro produto ou sair
        printf("Deseja cadastrar outro produto? (1 - Sim, 0 - Não): ");
        scanf("%d", &continuar);
    }
}

// Função para buscar produto por ID
void buscar_produto_por_id() {
    int continuar = 1;

    while (continuar) {
        limpar_tela();  // Limpa a tela antes de mostrar o menu

        int id;
        printf("Digite o ID do produto que deseja buscar: ");
        scanf("%d", &id);

        if (id < 1 || id > code) {
            printf("Produto não encontrado.\n");
        } else {
            Produto* produto = produtos[id - 1];
            printf("Produto encontrado: ID: %d | Nome: %s | Preço: %.2f\n", produto->id, produto->nome, produto->preco);
        }

        // Perguntar se o usuário deseja buscar outro produto ou sair
        printf("Deseja buscar outro produto? (1 - Sim, 0 - Não): ");
        scanf("%d", &continuar);
    }
}

// Função para buscar produto por nome
void buscar_produto_por_nome() {
    int continuar = 1;

    while (continuar) {
        limpar_tela();  // Limpa a tela antes de mostrar o menu

        char nome[50];
        printf("Digite o nome do produto que deseja buscar: ");
        scanf(" %49[^\n]", nome);

        int encontrado = 0;
        for (int i = 0; i < code; i++) {
            if (strcasecmp(produtos[i]->nome, nome) == 0) {
                printf("Produto encontrado: ID: %d | Nome: %s | Preço: %.2f\n", produtos[i]->id, produtos[i]->nome, produtos[i]->preco);
                encontrado = 1;
                // Não sair do loop, continue a procurar outros produtos com o mesmo nome
            }
        }

        if (!encontrado) {
            printf("Produto não encontrado.\n");
        }

        // Perguntar se o usuário deseja buscar outro produto ou sair
        printf("Deseja buscar outro produto? (1 - Sim, 0 - Não): ");
        scanf("%d", &continuar);
    }
}

// Função para listar todos os produtos
void listar_produtos() {
    limpar_tela();  // Limpa a tela antes de mostrar o menu

    if (code == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Lista de Produtos:\n");
    for (int i = 0; i < code; i++) {
        printf("ID: %d | Nome: %s | Preço: %.2f\n", produtos[i]->id, produtos[i]->nome, produtos[i]->preco);
    }
}

// Função intermediária para processar a escolha do usuário
void processar_escolha(int escolha) {
    switch (escolha) {
        case 1:
            cadastrar_produto();
            break;
        case 2:
            buscar_produto_por_id();
            break;
        case 3:
            buscar_produto_por_nome();
            break;
        case 4:
            listar_produtos();
            break;
        case 5:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
    }
}
