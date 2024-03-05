#include "vendas.h"
#include "apresentacao.h"
#include "cliente.h"
#include "produtos.h"
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
void encontraCpfCliente(char* nomeCliente, char* cpf)
{
    int quantidade = quantidadeClientesCSV();
    CLIENTE* lista;
    lista = (CLIENTE*)malloc(sizeof(CLIENTE) * quantidade);
    lerClientesCSV(lista);

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(lista[i].nome, nomeCliente) == 0)
        {
            strcpy(cpf, lista[i].CPF);
            break;
        }
    }
    free(lista);
}

/**
Procedimento que lista todas as compras de um determinado cliente
*/
void listarComprasDeCliente()
{
    char buscador[50]; // cpf ou nome completo, entrada do usuario
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
        char* cpf[15];
        encontraCpfCliente(buscador, cpf);
        strcpy(buscador, cpf);
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

int encontraEstoque(int idProduto)
{
    int estoque = 0;
    int quantidade = quantidadeProdutosCSV();
    PRODUTO* lista;
    lista = (PRODUTO*)malloc(sizeof(PRODUTO) * quantidade);
    lerProdutosCSV(lista);

    for (int i = 0; i < quantidade; i++)
    {
        if (lista[i].id == idProduto)
        {
            estoque = lista[i].estoque;
            free(lista);
            return estoque;
        }
    }
    free(lista);
    printf("Esse produto não foi cadastrado\n");
    return estoque;
}

int diminuiEstoque(int idProduto, int quantidade_itens)
{
    int quantidade = quantidadeProdutosCSV();
    PRODUTO* lista;
    lista = (PRODUTO*)malloc(sizeof(PRODUTO) * quantidade);
    lerProdutosCSV(lista);

    for (int i = 0; i < quantidade; i++)
    {
        if (lista[i].id == idProduto)
        {
            lista[i].estoque = (lista[i].estoque - quantidade_itens);
            free(lista);
            return 0;
        }
    }
    free(lista);
    printf("Esse produto não foi cadastrado\n");
    return 0;
}

float encontraPreco(int idProduto)
{
    float preco = 0;
    int quantidade = quantidadeProdutosCSV();
    PRODUTO* lista;
    lista = (PRODUTO*)malloc(sizeof(PRODUTO) * quantidade);
    lerProdutosCSV(lista);

    for (int i = 0; i < quantidade; i++)
    {
        if (lista[i].id == idProduto)
        {
            preco = lista[i].preco;
            free(lista);
            return preco;
        }
    }
    free(lista);
    printf("Esse produto não foi cadastrado\n");
    return preco;
}
void GravaItemComprado_CSV(ITEM_COMPRADO ic)
{
    char nomeArquivo[] = "ItensCompras.csv";
    FILE* csv;
    csv = fopen(nomeArquivo, "r");
    if (csv == NULL)
    {
        csv = fopen(nomeArquivo, "a");
        fprintf(csv, "IdVenda;CPF;IdProduto;Quantidade;Unitario;Total\n");
        fflush(csv);
    }
    fclose(csv);
    csv = fopen(nomeArquivo, "a");

    // fseek(csv, 0, SEEK_END);

 // arquivo ja existe, insere apenas o dado no final do arquivo
    fprintf(csv, "%d;%s;%d;%d;%.2f;%.2f\n",
        ic.IdVenda, ic.CPF, ic.IdProduto, ic.Quantidade, ic.Unitario, ic.Total);
    fflush(csv);
    fclose(csv);
    // salvando o cabeçalho do arquivo

}

int Nova_Venda()
{   
    VENDA novaVenda;
    ITEM_COMPRADO novoItem;
    int quantidade_itens, id_produto;
    char cpf_venda[15];
    novaVenda.quantidadeItens = 0;  
    novaVenda.valorTotal = 0;
    novaVenda.id = quantidadeVendasCSV() + 1;
    system("cls");
    separador();
    printf("Digite o CPF do cliente:\n");
    scanf(" %s", &cpf_venda);
    if (!(verificaCadastroCliente(cpf_venda))) 
    {
        system("cls");
        printf("Cliente não encontrado!\n");
        printf("Cadastrando novo cliente...\n");
        cadastroNovoCliente();
    }
    do 
    {
        printf("Digite o código do produto (digite 0 para finalizar a venda):\n");
        scanf(" %d", &id_produto);
        if (id_produto != 0) 
        {
            printf("Quantas unidades do produto?\n");
            scanf(" %d", &quantidade_itens);
            if (encontraEstoque(id_produto) >= quantidade_itens)
            {
                diminuiEstoque(id_produto, quantidade_itens);
                novaVenda.quantidadeItens += 1;
                novaVenda.valorTotal += encontraPreco(id_produto) * quantidade_itens;
                novoItem.IdVenda = novaVenda.id;
                strcpy(novoItem.CPF, cpf_venda);
                novoItem.IdProduto = id_produto;
                novoItem.Quantidade = quantidade_itens;
                novoItem.Unitario = (encontraPreco(id_produto));
                novoItem.Total = novaVenda.valorTotal;
                GravaItemComprado_CSV(novoItem);
            }
            else {
                printf("Não há quantidade disponível de produtos\n");
            }
        }
        else {
            printf("Compra finalizada\n");
            return 0;
        }
    } while (id_produto != 0);
    printf("Compra finalizada\n");
    return 0;
}