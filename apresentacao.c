#include <stdio.h>
#include <stdlib.h>
#include "apresentacao.h"

const int TAM_SEPARADOR = 40;

void LimparTela()
{
    system("cls");
}

void separador()
{
    for (int i = 0 ; i< TAM_SEPARADOR; i++ )
        printf("#");
    printf("\n");
}


int MenuPrincipal()
{
    int opcao;
    LimparTela();
    separador();
    printf("1. Venda\n2. Clientes\n3. Produtos\n9. Sair\n");
    separador();
    printf("\nOpção -> ");
    scanf(" %d", &opcao );
    return opcao;
}

int MenuVendas()
{
    int opcao;
    LimparTela();
    separador();
    printf("1. Nova Venda\n2. Listar vendas de um cliente\n9. Sair\n");
    separador();
    printf("\nOpção -> ");
    scanf(" %d", &opcao );
    return opcao;
}


int MenuClientes()
{
    int opcao;
    LimparTela();
    separador();
    printf("1. Cadastrar novo cliente\n2. Atualizar pontuação\n3. Atualizar cliente\n4. Listar clientes entre 18 e 25 anos\n5. Listar clientes com mais de 1000 pontos\n9. Sair\n");
    separador();
    printf("\nOpção -> ");
    scanf(" %d", &opcao);
    return opcao;
}

int MenuProdutos()
{
    int opcao;
    LimparTela();
    separador();
    printf("1. Cadastrar novo produto\n2. Atualizar produto\n3. Estoque por setor\n4. Produtos com estoque abaixo de 5\n9. Sair\n");
    separador();
    printf("\nOpção -> ");
    scanf(" %d", &opcao);
    return opcao;
}