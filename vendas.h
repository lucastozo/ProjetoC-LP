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
    unsigned int IdVenda;
    char CPF[15];
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
 * Encontra o CPF de um cliente dado o nome dele
 * @param nomeCliente Nome do cliente
 * @param cpf CPF a ser atribuido, passado por referência
*/
void encontraCpfCliente(char* nomeCliente, char* cpf);

/**
Procedimento que lista todas as compras de um determinado cliente
*/
void listarComprasDeCliente();

/* Função retorna o estoque do produto*/
int encontraEstoque();

/* Função diminui o estoque do produto*/
int diminuiEstoque();

/* Função retorna o preço do produto*/
float encontraPreco();

/**
Procedimento que grava em Itens_Compra.csv o item de uma venda
@param ic Item comprado na venda
*/
void GravaItemComprado_CSV(ITEM_COMPRADO ic);

/**
Procedimento que grava em Vendas.csv uma venda realizada
@param vnd Struct VENDA que terá seus campos preenchidos e gravados no csv
*/
void GravaVendas_CSV(VENDA vnd);

/*Função de venda*/
int Nova_Venda();
#endif