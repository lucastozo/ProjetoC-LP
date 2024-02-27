#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "tempo.h"

typedef struct CLIENTE
{
    char CPF[15];
    char nome[51];
    DATA dataNascimento;
    int idade;
    char endereco[101];
    char cidade[101];
    char estado[3];
    unsigned int pontos;
} CLIENTE;


/**
 * Gravando os dados de um cliente no final do arquivo. Caso o arquivo
 * n�o exista, gera um novo arquivo com as colunas que s�o o cabe�alho
 * @param c Cliente que ser� salvo no registro
*/
int gravarCliente(CLIENTE c);

/**
*Rotina que l� os dados de um cliente atrav�s do teclado
* @param c Ponteiro para um registro do tipo CLIENTE,
* onde os dados lidos ser�o armazenados
*/
void lerCliente(CLIENTE * c);

/**
 * Exibe os campos contidos em um registro do tipo PRODUTO
 * @param p Registro que ser� exibido
*/
void exibirCliente(CLIENTE c);

/**
 * Adiciona pontos a um determinado cliente
 * @param c Ponteiro para o cliente que ser� adicionado
 * @param pontos Pontos a serem adicionados ao cliente c *
*/
void adicionarPontosCliente(CLIENTE* c, int pontos);

/**
* Leitura de dados do CSV para registros
* @param lista Ponteiro para um vetor de registros
* com os dados que est�o no arquivo
* @return Retorna a quantidade de clientes cadastrados
*/
int lerClientesCSV(CLIENTE * lista);

/**
 * Retorna a quantidade de clientes que est�o salvos no arquivo CSV
 * @return Quantidade de clientes salvos
*/
int quantidadeClientesCSV();

/**
* Atualiza o arquivo CSV conforme necessidade do usu�rio, copiando o arquivo original
* modificando a parte a ser atualizada e por fim criando um novo arquivo com o mesmo nome 
*/
void atualizarCliente(CLIENTE* listaClientes);
#endif