#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cliente.h"
#include "apresentacao.h"


void limpabuffer()
{
    int limpa_buffer;
    while ((limpa_buffer = getchar()) != EOF && limpa_buffer != '\n');
}

int gravarClienteCSV(CLIENTE c)
{
    char nomeArquivo[] = "Clientes.csv";
    FILE* csv;
    csv = fopen(nomeArquivo, "r");
    if (csv == NULL)
    {
        csv = fopen(nomeArquivo, "a");

        fprintf(csv, "CPF;Nome;Data de Nascimento;Idade;Endereco;Cidade;Estado;Pontos\n");
        fflush(csv);
    }
    fclose(csv);
    fopen(nomeArquivo, "a");
    fprintf(csv, "%s;%s;%d/%d/%d;%d;%s;%s;%s;%d\n",
        c.CPF, c.nome,
        c.dataNascimento.dia, c.dataNascimento.mes, c.dataNascimento.ano, c.idade,
        c.endereco, c.cidade, c.estado,
        c.pontos);
    fflush(csv);
    fclose(csv);
    return 0;
}

void cadastroNovoCliente()
{
    CLIENTE c;
    separador();
    printf("Insira os dados do cliente \n");
    printf("CPF do cliente: ");
    scanf(" %[^\n]s", c.CPF);
    printf("Nome do cliente: ");
    scanf(" %[^\n]s", c.nome);
    printf("Data de Nascimento do Cliente: ");
    printf("\tDia ->");
    scanf(" %d", &c.dataNascimento.dia);
    printf("\tMês ->");
    scanf(" %d", &c.dataNascimento.mes);
    printf("\tAno ->");
    scanf(" %d", &c.dataNascimento.ano);
    printf("Idade do cliente: ");
    scanf(" %d", &c.idade);
    printf("Endereço do cliente: ");
    scanf(" %[^\n]s", &c.endereco);
    printf("Cidade do cliente: ");
    scanf(" %[^\n]s", &c.cidade);
    printf("Estado do cliente: ");
    scanf(" %[^\n]s", &c.estado);
    c.pontos = 0;
    gravarClienteCSV(c);
}

int quantidadeClientesCSV()
{
    char nomeArquivo[] = "Clientes.csv";
    FILE* csv;
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

void lerClientesCSV(CLIENTE* listaClientes)
{
    char nomeArquivo[] = "Clientes.csv";
    FILE* csv;
    char linha[1000];
    char* pCampos;
    const char separador[2] = ";";
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
            pCampos = strtok(linha, separador);
            int campoAtual = 0;
            while (pCampos != NULL)
            {
                switch (campoAtual)
                {
                case 0:
                    strcpy(listaClientes[i].CPF, pCampos);
                    break;
                case 1:
                    strcpy(listaClientes[i].nome, pCampos);
                    break;
                case 2:
                    StringToData(pCampos, &listaClientes[i].dataNascimento);
                    break;
                case 3:
                    listaClientes[i].idade = atoi(pCampos);
                    break;
                case 4:
                    strcpy(listaClientes[i].endereco, pCampos);
                    break;
                case 5:
                    strcpy(listaClientes[i].cidade, pCampos);
                    break;
                case 6:
                    strcpy(listaClientes[i].estado, pCampos);
                    break;
                case 7:
                    listaClientes[i].pontos = atoi(pCampos);
                    break;
                default:
                    break;
                }
                pCampos = strtok(NULL, separador);
                campoAtual++;
            }
            i++;
        }
        fclose(csv);
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivo);
        system("pause");
    }
}

int adicionarPontosClienteCPF(char* CPF, int pontos)
{
    int quantidadeClientes = quantidadeClientesCSV();
    bool clienteEncontrado = false;
    CLIENTE* pListaClientes;
    pListaClientes = (CLIENTE*)malloc(sizeof(CLIENTE) * quantidadeClientes);
    lerClientesCSV(pListaClientes);
    for (int i = 0; i < quantidadeClientes; i++)
    {
        if (strcmp(pListaClientes[i].CPF, CPF) == 0)
        {
            pListaClientes[i].pontos += pontos;
            clienteEncontrado = true;
        }
    }
    if (clienteEncontrado)
    {
        remove("Clientes.csv");
        for (int i = 0; i < quantidadeClientes; i++)
        {
            gravarClienteCSV(pListaClientes[i]);
        }
        free(pListaClientes);
        return 0;
    }
    else
    {
        free(pListaClientes);
        return 1;
    }
}

void adicionarManualPontosCliente()
{
    char CPFBusca[15];
    printf("Digite o CPF do cliente que deseja adicionar pontos: \n");
    scanf(" %[^\n]s", CPFBusca);
    int pontos = 0;
    printf("Digite a quantidade de pontos que deseja adicionar ao cliente\n");
    scanf(" %d", &pontos);
    if ((adicionarPontosClienteCPF(CPFBusca, pontos)) != 0)
    {
        printf("Cliente não encontrado com o CPF digitado\n");
        system("pause");
    }
}

void atualizarCliente()
{
    char CPFBusca[15];
    int quantidadeClientes = quantidadeClientesCSV();
    CLIENTE* pListaClientes;
    pListaClientes = (CLIENTE*)malloc(sizeof(CLIENTE) * quantidadeClientes);
    lerClientesCSV(pListaClientes);
    bool clienteNaoEncontrado = true;
    bool atualizouCliente = false;
    printf("Digite o CPF do cliente que deseja atualizar: \n");
    scanf(" %[^\n]s", CPFBusca);
    for (int i = 0; i < quantidadeClientes; i++)
    {
        if (strcmp(pListaClientes[i].CPF, CPFBusca) == 0)
        {
            clienteNaoEncontrado = false;
            int opcao;
            do
            {
                opcao = MenuAtualizarCliente();
                switch (opcao)
                {
                case 1:
                    printf("\nAtualizar CPF -> ");
                    scanf(" %[^\n]s", &pListaClientes[i].CPF);
                    atualizouCliente = true;
                    break;
                case 2:
                    printf("\nAtualizar Nome -> ");
                    scanf(" %[^\n]s", &pListaClientes[i].nome);
                    atualizouCliente = true;
                    break;
                case 3:
                    printf("\Atualizar Data de Nascimento do Cliente: ");
                    printf("\tDia ->");
                    scanf(" %d", &pListaClientes[i].dataNascimento.dia);
                    printf("\tMês ->");
                    scanf(" %d", &pListaClientes[i].dataNascimento.mes);
                    printf("\tAno ->");
                    scanf(" %d", &pListaClientes[i].dataNascimento.ano);
                    atualizouCliente = true;
                    break;
                case 4:
                    printf("\nAtualizar idade -> ");
                    scanf(" %d", &pListaClientes[i].idade);
                    atualizouCliente = true;
                    break;
                case 5:
                    printf("\nAtualizar Endereço -> ");
                    scanf(" %[^\n]s", &pListaClientes[i].endereco);
                    atualizouCliente = true;
                    break;
                case 6:
                    printf("\nAtualizar Cidade -> ");
                    scanf(" %[^\n]s", &pListaClientes[i].cidade);
                    atualizouCliente = true;
                    break;
                case 7:
                    printf("\nAtualizar Estado -> ");
                    scanf(" %[^\n]s", &pListaClientes[i].estado);
                    atualizouCliente = true;
                    break;
                default:
                    break;
                }
            } while (opcao != 9);
        }
    }
    if (clienteNaoEncontrado)
    {
        printf("Cliente não encontrado com o CPF digitado\n");
        system("pause");
    }
    else if (atualizouCliente)
    {
        remove("Clientes.csv");
        for (int i = 0; i < quantidadeClientes; i++)
        {
            gravarClienteCSV(pListaClientes[i]);
        }
    }
    free(pListaClientes);
}

void exibirCliente(CLIENTE c)
{
    SetConsoleOutputCP(1252);
    char data[50];
    printf("\n");
    separador();
    printf("Exibindo um cliente: \n");
    printf("CPF: %s\n", c.CPF);
    printf("Nome: %s\n", c.nome);
    DataToString(c.dataNascimento, data, false);
    printf("Data de Nascimento: %s\n", data);
    printf("Idade: %d\n", c.idade);
    printf("Endereco: %s\n", c.endereco);
    printf("Cidade: %s\n", c.cidade);
    printf("Estado: %s\n", c.estado);
    printf("Pontos: %d\n", c.pontos);
    separador();
    SetConsoleOutputCP(65001);
}

void listarClientes18a25anos()
{
    int quantidadeClientes = quantidadeClientesCSV();
    CLIENTE* pListaClientes;
    pListaClientes = (CLIENTE*)malloc(sizeof(CLIENTE) * quantidadeClientes);
    lerClientesCSV(pListaClientes);
    for (int i = 0; i < quantidadeClientes; i++)
    {
        if (pListaClientes[i].idade >= 18 & pListaClientes[i].idade <= 25)
        {
            exibirCliente(pListaClientes[i]);
        }
    }
    system("pause");
    free(pListaClientes);
}

void listarClientesAcima1000Pontos()
{
    int quantidadeClientes = quantidadeClientesCSV();
    CLIENTE* pListaClientes;
    pListaClientes = (CLIENTE*)malloc(sizeof(CLIENTE) * quantidadeClientes);
    lerClientesCSV(pListaClientes);
    for (int i = 0; i < quantidadeClientes; i++)
    {
        if (pListaClientes[i].pontos >= 1000)
        {
            exibirCliente(pListaClientes[i]);
        }
    }
    system("pause");
    free(pListaClientes);
}
