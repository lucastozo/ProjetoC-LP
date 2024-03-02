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

/*
    Gravando os dados de um cliente no final do arquivo. Caso o arquivo
    não exista, gera um novo arquivo com as colunas que são o cabeçalho
    @param c Cliente que será salvo no final do arquivo Clientes.csv
*/
int gravarClienteCSV(CLIENTE c);

/*
    Rotina que lê os dados de um cliente através do teclado
    os dados serão salvos no arquivo final do arquivo Clientes.csv
*/
void cadastroNovoCliente();

/*
    Retorna a quantidade de clientes que estão salvos no arquivo CSV
    @return Quantidade de clientes salvos
*/
int quantidadeClientesCSV();

/*
    Leitura de dados do CSV para registros
    @param lista Ponteiro para um vetor de registros
    com os dados que estão no arquivo
*/
void lerClientesCSV(CLIENTE* lista);

/*
    Adiciona pontos a um determinado cliente
    @param CPF em formato string do cliente
    @param Pontos a serem adicionados ao cliente
    @return retorna 0 se teve sucesso em encontrar o CPF do cliente e adicionar os pontos, 1 se não teve.
*/
int adicionarPontosClienteCPF(char* CPF, int pontos);

/*
    Adiciona Manualmente pontos a um cliente
    Pede ao usuário o CPF do cliente e a quantidade de pontos
*/
void adicionarManualPontosCliente();

/*
    Atualiza o arquivo CSV conforme necessidade do usuário, copiando o arquivo original
    modificando a parte a ser atualizada e por fim criando um novo arquivo com o mesmo nome
*/
void atualizarCliente();

/*
    Exibe os campos contidos em um registro do tipo CLIENTE
    @param p Registro que será exibido
*/
void exibirCliente(CLIENTE c);

/*
    lista todos os clientes com idades entre 18 e 25 anos
*/
void listarClientes18a25anos();

/*
    lista todos os clientes com 1000 ou mais pontos
*/
void listarClientesAcima1000Pontos();

/*
    Retorna se verdadeiro se o cliente ja está cadastrado e falso caso o contrário
*/
bool verificaCadastroCliente();
#endif