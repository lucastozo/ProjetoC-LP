#include <stdio.h>
#include <stdlib.h>
#include "apresentacao.h"

const int TAM_SEPARADOR = 40;

void separador()
{
    for (int i = 0 ; i< TAM_SEPARADOR; i++ )
        printf("#");
    printf("\n");
}


int MenuPrincipal()
{
    int opcao;
    //system("clear"); // <- opcao caso Linux 
    system("cls"); // <- opcao caso Windows
    separador();
    printf("1. Venda\n2. Clientes\n3. Produtos\n9. Sair\n");
    separador();
    separador();
    printf("\nOpcao -> ");
    
    scanf(" %d", &opcao );
    return opcao;
}

int MenuVendas()
{
    int opcao;
    system("cls");
    separador();
    printf("1. Nova Venda\n2. Listar Venda do Clientes\n9. Sair\n");
    separador();
    separador();
    printf("\nOpcao -> ");
    scanf(" %d", &opcao );
    return opcao;
}


int MenuClientes()
{
    int opcao;
    system("cls");
    separador();
    printf("1. Cadastrar Novo Cliente\n2. Atualizar Pontuação\n3. Atualizar Cliente\n4. Listar Clientes entre 18 e 25 anos\n5. Listar clientes com mais de 1000 pontos\n9. Sair\n");
    separador();
    separador();
    printf("\nOpcao -> ");
    scanf(" %d", &opcao);
    return opcao;
}

int MenuProdutos()
{
    int opcao;
    system("cls");
    separador();
    printf("1. Cadastrar novo produto\n2. Atualizar informacoes do produto\n3. Estoque por setor\n4. Produtos com estoque baixo\n9. Sair\n");
    separador();
    separador();
    printf("\nOpcao -> ");
    scanf(" %d", &opcao);
    return opcao;
}
int MenuAtualizarCliente()
{
    int opcao;
    system("cls");
    separador();
    printf("Deseja atualizar qual dado do cliente?\n");
    printf("1. CPF\n2. Nome\n3. Data de Nascimento\n4. Idade\n5. Endereco\n6. Cidade\n7. Estado\n9. Sair do menu de atualização de dados do cliente\n");
    separador();
    separador();
    printf("\nOpcao -> ");
    scanf(" %d", &opcao);
    return opcao;
}