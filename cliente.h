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
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param c Cliente que será salvo no registro
*/
int gravarCliente(CLIENTE c);

/**
*Rotina que lê os dados de um cliente através do teclado
* @param c Ponteiro para um registro do tipo CLIENTE,
* onde os dados lidos serão armazenados
*/
void lerCliente(CLIENTE * c);

/**
 * Exibe os campos contidos em um registro do tipo PRODUTO
 * @param p Registro que será exibido
*/
void exibirCliente(CLIENTE c);

/**
 * Adiciona pontos a um determinado cliente
 * @param c Ponteiro para o cliente que será adicionado
 * @param pontos Pontos a serem adicionados ao cliente c *
*/
void adicionarPontosCliente(CLIENTE* c, int pontos);

/**
* Leitura de dados do CSV para registros
* @param lista Ponteiro para um vetor de registros
* com os dados que estão no arquivo
* @return Retorna a quantidade de clientes cadastrados
*/
int lerClientesCSV(CLIENTE * lista);

/**
 * Retorna a quantidade de clientes que estão salvos no arquivo CSV
 * @return Quantidade de clientes salvos
*/
int quantidadeClientesCSV();

/**
* Atualiza o arquivo CSV conforme necessidade do usuário, copiando o arquivo original
* modificando a parte a ser atualizada e por fim criando um novo arquivo com o mesmo nome 
*/
void atualizarCliente(CLIENTE* listaClientes);
#endif