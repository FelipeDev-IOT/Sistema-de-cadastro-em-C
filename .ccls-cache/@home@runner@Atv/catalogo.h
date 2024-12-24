#ifndef CATALOGO_H
#define CATALOGO_H

#define MAX_PRODUTOS 100

typedef struct {
    int id;
    char *nome;
    float preco;
} Produto;

void exibir_menu_animado(); 
void print_with_delay(const char *str, int delay);
void processar_escolha(int escolha);
void cadastrar_produto();
void buscar_produto_por_id();
void buscar_produto_por_nome();

#endif // CATALOGO_H