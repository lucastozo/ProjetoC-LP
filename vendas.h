#ifndef __VENDAS_H__
#define __VENDAS_H__

#include <stdio.h>
#include "tempo.h"

enum CAMPOS_VENDA {ID_VENDA=0, CPF_VENDA, DATA_VENDA, TOTAL_VENDA, ITENS_VENDA};

typedef struct VENDA
{
    /* Identificação da venda */
    unsigned int id;
    /* CPF do cliente que realizou a compra */
    char CPF[14];
    /* Data de realização da compra*/
    DATA dataCompra;
    /* Valor total da compra */
    float valorTotal;
    /* Quantidade de itens comprados, sem considerar a quantidade */
    unsigned int quantidadeItens;
} VENDA;

typedef struct ITEM_COMPRADO
{
    IdVenda; CPF; IdProduto; Quantidade; Unitario; Total
    unsigned int IdVenda;
    char CPF[14];
    unsigned int IdProduto;
    int Quantidade;
    float Unitario;
    float Total;
} ITEM_COMPRADO;

/**
 * Verifica a quantidade de vendas registradas 
 * @return Retorna a quantidade de vendas registradas
*/
int quantidadeVendasCSV();

/**
 * Faz a leitura do arquivo vendas.csv e carrega 
 * as informações na lista utilizada como parâmetro
 * @param lista Ponteiro para o vetor que armazena a lista de VENDAS realizadas
 * @return Retorna a quantidade de vendas lidas
*/
int lerVendasCSV(VENDA *lista );

/**
 * Exibe os campos contidos em um registro do tipo VENDA
 * @param venda Registro que será exibido
*/
void exibirVenda(VENDA venda);

/**
Procedimento que lista todas as compras de um determinado cliente
*/
void listarComprasDeCliente();

int encontraEstoque();

int diminuiEstoque();

int encontraPreco();

int Nova_Venda();
#endif