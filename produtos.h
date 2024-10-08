#ifndef __PRODUTOS_H__
#define __PRODUTOS_H__

#include <stdio.h>
#include "tempo.h"



typedef  struct PRODUTO {
    /* Identificação do produto */
    unsigned int id;
    /* Setor do produto */
    char setor[11];
    /* Nome do produto */
    char nome[51];
    /* Preço atual do produto */
    float preco;
    /* Data de validade do produto */
    DATA dataValidade;
    /* Quantidade de itens do produto em estoque */
    int estoque;
} PRODUTO;



/**
 * Rotina que lê os dados de um produto através do teclado
 * @param p Ponteiro para um registro do tipo PRODUTO, 
 * onde os dados lidos serão armazenados 
*/
void lerProduto( PRODUTO *p );

/**
 * Exibe os campos contidos em um registro do tipo PRODUTO
 * @param p Registro que será exibido
*/
void exibirProduto(PRODUTO p);

/**
 * Gravando os dados de um produto no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param p Produto que será salvo no registro
*/
int gravarProdutoCSV( PRODUTO p);

/**
 * Retorna a quantidade de produtos que estão salvos no arquivo CSV
 * @return Quantidade de produtos salvos
*/
int quantidadeProdutosCSV( );

/**
 * Leitura de dados do CSV para registros 
 * @param lista Ponteiro para um vetor de registros 
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de produtos cadastrados
*/
int lerProdutosCSV( PRODUTO *lista );

/**
 * Rotina que devolve o id a ser utilizado no próximo cadastro
 * @param formato Define se é para o tipo de arquivo csv ou para o tipo dat
 * @return Retorna o próximo ID a ser utilizado. Se o formato não for definido para 
 * um dos dois válidos ("CSV" ou "DAT"), a função retorna -1.
*/
unsigned int obterProximoIdProduto();

//procedimentos de produto
/*
Procedimento que insere um novo produto no CSV
*/
void cadastrarProduto();

/*
    Exibe o menu de atualização de produto
    @return retorna a escolha do usuário
*/
int MenuAtualizarProduto(PRODUTO p);

/*
Procedimento que atualiza os dados de um produto no CSV
*/
void atualizarProduto();

/*
Procedimento que mostra todos os produtos de um dado setor
*/
void produtosPorSetor();

/*
Procedimento que mostra todos os produtos com estoque abaixo de 5
*/
void produtosEstoqueAbaixoDe5();

#endif