#include "vendas.h"
#include "apresentacao.h"
#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Verifica a quantidade de vendas registradas 
 * @return Retorna a quantidade de vendas registradas
*/
int quantidadeVendasCSV()
{
    char nomeArquivo[] = "Vendas.csv";
    FILE *csv;
    char linha[1000];
    csv = fopen(nomeArquivo, "r");
    if (csv != NULL)
    {
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        int contadorLinha = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            contadorLinha++;
        }
        fclose(csv);
        return contadorLinha;
    }
    else
    {
        // arquivo não existe
        return 0;
    }
}

/**
 * Faz a leitura do arquivo vendas.csv e carrega 
 * as informações na lista utilizada como parâmetro
 * @param lista Ponteiro para o vetor que armazena a lista de VENDAS realizadas
*/
int lerVendasCSV(VENDA *lista )
{
    char nomeArquivo[] = "Vendas.csv";
    FILE *csv;
    char linha[1000];
    char *campos;
    const char s[2] = ";";
    int contadorLinha = 0;
    csv = fopen(nomeArquivo, "r");
    if (csv != NULL)
    {
        // fim dos registros, reabrindo para ler os dados
        fseek(csv, 0, SEEK_SET);
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        // alocando memoria para os registros lidos

        int i = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            // separando os dados de uma linha
            campos = strtok(linha, s);
            int campoAtual = 0;
            while (campos != NULL)
            {
                switch (campoAtual)
                {
                case ID_VENDA:
                    lista[i].id = atoi(campos);
                    break;
                case CPF_VENDA:
                    strcpy(lista[i].CPF, campos);
                    break;
                case DATA_VENDA:
                    StringToData(campos, &lista[i].dataCompra);
                    break;
                case TOTAL_VENDA:
                    lista[i].valorTotal = atof(campos);
                    break;
                case ITENS_VENDA:
                    lista[i].quantidadeItens = atoi(campos);
                    break;
                default:
                    break;
                }
                campos = strtok(NULL, s);
                campoAtual++;
            }
            i++;
            // dados do setor;
        }
        contadorLinha = i;
        return contadorLinha;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivo);
        return -1;
    }

}

/**
 * Exibe os campos contidos em um registro do tipo VENDA
 * @param venda Registro que será exibido
*/
void exibirVenda(VENDA venda)
{
    char data[50];
    printf("\n");
    separador();
    DataToString(venda.dataCompra, data, false);
    printf("Data da compra: %s\n", data);
    printf("Valor: R$");
    printf("%.2f\n", venda.valorTotal);
    printf("Quantidade de itens: ");
    printf("%u\n", venda.quantidadeItens);
}

/**
 * Encontra o CPF de um cliente dado o nome dele
 * @param nomeCliente Nome do cliente
 * @return Retorna o CPF do cliente
*/
char encontraCpfCliente(char nomeCliente[])
{
    char cpf[15];
    int quantidade = quantidadeClientesCSV();
    CLIENTE* lista;
    lista = (CLIENTE*)malloc(sizeof(VENDA) * quantidade);
    lerClientesCSV(lista);

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(lista[i].nome, nomeCliente) == 0)
        {
            strcpy(cpf, lista[i].CPF);
            free(lista);
            return cpf;
        }
    }
    free(lista);
    printf("Nenhum cliente encontrado com o nome fornecido.\n");
    return cpf;
}

/**
Procedimento que lista todas as compras de um determinado cliente
*/
void listarComprasDeCliente()
{
    char buscador[] = "default"; // cpf ou nome completo, entrada do usuario
    printf("Escolha a forma de busca: \n1. CPF \n2. Nome Completo");
    printf("\nOpcao -> ");
    int opcaoBusca = 0;
    scanf("%d", &opcaoBusca);

    if (opcaoBusca == 1) {
        printf("Insira o CPF do cliente (xxx.xxx.xxx-xx): ");
    }
    else {
        printf("Insira o nome completo do cliente: ");
    }
    scanf(" %[^\n]s", buscador);

    if (opcaoBusca == 2)
    {
        strcpy(buscador, encontraCpfCliente(buscador)); // ESTÁ DANDO ERRO NA EXECUÇÃO DA FUNÇÃO ENCONTRACPFCLIENTE
    }

    int quantidade = quantidadeVendasCSV();
    VENDA* lista;
    lista = (VENDA*)malloc(sizeof(VENDA) * quantidade);
    lerVendasCSV(lista);

    bool encontrou = false;
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(lista[i].CPF, buscador) == 0)
        {
            exibirVenda(lista[i]);
            encontrou = true;
        }
    }
    free(lista);

    if (!encontrou)
    {
        printf("Nenhuma compra encontrada para o cliente fornecido.\n");
    }
    system("pause");
}