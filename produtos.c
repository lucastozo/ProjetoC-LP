#include "produtos.h"
#include "apresentacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char separadorCSV = ';';
// char SETOR[6][] = {"Higiene", "Limpeza", "Bebidas", "Frios", "Padaria", "Açougue"};

void lerProduto(PRODUTO *p)
{
    printf("Lendo um produto \n");
    printf("Setor: ");
    scanf(" %[^\n]s", p->setor);
    printf("Nome: ");
    scanf(" %[^\n]s", p->nome);
    printf("Preco: ");
    scanf(" %f", &p->preco);
    printf("Data de validade\n");
    printf("\tDia ->");
    scanf(" %d", &p->dataValidade.dia);
    printf("\tMês ->");
    scanf(" %d", &p->dataValidade.mes);
    printf("\tAno ->");
    scanf(" %d", &p->dataValidade.ano);
    printf("Estoque: ");
    scanf(" %i", &p->estoque);
}

void exibirProduto(PRODUTO p)
{
    char data[50];
    separador();
    printf("Exibindo um produto \n");
    printf("ID: ");
    printf("%u\n", p.id);
    printf("Setor: ");
    printf("%s\n", p.setor);
    printf("Nome: ");
    printf("%s\n", p.nome);
    printf("Preco: ");
    printf("%.2f\n", p.preco);
    DataToString(p.dataValidade, data, false);
    printf("Data de validade: %s\n", data);
    printf("Estoque: ");
    printf("%i\n", p.estoque);
    separador();
    printf("\n");
}

int gravarProdutoCSV(PRODUTO p)
{
    char nomeArquivo[] = "Produtos.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "r");
    if (csv == NULL)
    {
        csv = fopen(nomeArquivo, "a");
        fprintf(csv, "id;setor;nome;preço;data de validade;estoque\n");
        fflush(csv);
    }
    fclose(csv);
    csv = fopen(nomeArquivo, "a");
     
    // arquivo ja existe, insere apenas o dado no final do arquivo
    fprintf(csv, "%d;%s;%s;%.2f;%d/%d/%d;%d\n",
            p.id, p.setor, p.nome, p.preco,
            p.dataValidade.dia, p.dataValidade.mes, p.dataValidade.ano,
            p.estoque);
    fflush(csv);
    fclose(csv);
    return 0;
}

int quantidadeProdutosCSV()
{
    char nomeArquivo[] = "Produtos.csv";
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

int lerProdutosCSV(PRODUTO *lista)
{
    char nomeArquivo[] = "Produtos.csv";
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
                case 0:
                    lista[i].id = atoi(campos);
                    break;
                case 1:
                    strcpy(lista[i].setor, campos);
                    break;
                case 2:
                    strcpy(lista[i].nome, campos);
                    break;
                case 3:
                    lista[i].preco = atof(campos);
                    break;
                case 4:
                    StringToData(campos, &lista[i].dataValidade);
                    break;
                case 5:
                    lista[i].estoque = atoi(campos);
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
        fclose(csv);
        return contadorLinha;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivo);
        return -1;
    }
}

unsigned int obterProximoIdProduto()
{
    char nomeArquivo[] = "idProduto.dat";
    FILE *f = fopen(nomeArquivo, "r+b");
    unsigned  id=1;
    unsigned int v;
    int size;
    if (f != NULL)
    {
        size = fread(&v,sizeof(unsigned int),1, f);
        if (size > 0)
        {
            v++;
            id = v;
        }
        fseek(f,0,SEEK_SET);
        fwrite(&v, sizeof(unsigned int), 1, f);    
        fflush(f);
        fclose(f);
    }
    else
    {
        f = fopen(nomeArquivo,"wb");
        fwrite(&id, sizeof(unsigned int), 1, f);
        fclose(f);
    }
    return id;
}

void cadastrarProduto()
{
    LimparTela();
    PRODUTO p;
    lerProduto(&p);
    p.id = obterProximoIdProduto();
    gravarProdutoCSV(p);
}

int MenuAtualizarProduto(PRODUTO p)
{
    int opcao;
    LimparTela();
    exibirProduto(p);
    separador();
    printf("Deseja atualizar qual dado do produto?\n");
    printf("1. ID\n2. Setor\n3. Nome\n4. Preço\n5. Data de Validade\n6. Estoque\n9. Sair\n");
    separador();
    printf("\nOpção -> ");
    scanf(" %d", &opcao);
    return opcao;
}

void atualizarProduto()
{
    LimparTela();
    printf("Digite o ID do produto que deseja buscar: ");
    int idBusca;
    scanf("%d", &idBusca);

    int quantidade = quantidadeProdutosCSV();
    PRODUTO* lista;
    lista = (PRODUTO*)malloc(sizeof(PRODUTO) * quantidade);
    lerProdutosCSV(lista);

    bool encontrou = false;
    bool produtoAtualizado = false;
    PRODUTO p;
    for (int i = 0; i < quantidade; i++)
    {
        if (lista[i].id == idBusca)
        {
            p = lista[i];
            encontrou = true;
            int opcao;
            do
            {
                opcao = MenuAtualizarProduto(p);
                if (opcao == 9)
                {
                    break;
                }
                produtoAtualizado = true;
                switch (opcao)
                {
                    case 1:
                        printf("\nAtualizar ID -> ");
                        scanf(" %d", &p.id);
                        break;

                    case 2:
                        printf("\nAtualizar Setor -> ");
                        scanf(" %[^\n]s", &p.setor);
                        break;

                    case 3:
                        printf("\nAtualizar Nome -> ");
                        scanf(" %[^\n]s", &p.nome);
                        break;

                    case 4:
                        printf("\nAtualizar Preço -> ");
                        scanf(" %f", &p.preco);
                        break;

                    case 5:
                        printf("\nAtualizar Data de validade -> ");
                        printf("\nDia -> ");
                        scanf(" %d", &p.dataValidade.dia);
                        printf("\nMês -> ");
                        scanf(" %d", &p.dataValidade.mes);
                        printf("\nAno -> ");
                        scanf(" %d", &p.dataValidade.ano);
                        break;

                    case 6:
                        printf("\nAtualizar Estoque -> ");
                        scanf(" %d", &p.estoque);
                        break;
                }
            } while (opcao != 9);

            lista[i] = p;
        }
    }

    if (!encontrou)
    {
        printf("Nenhum produto encontrado com este ID.");
        system("pause");
    }
    else if (produtoAtualizado)
    {
        remove("Produtos.csv");
        for (int i = 0; i < quantidade; i++)
        {
            gravarProdutoCSV(lista[i]);
        }
    }
    free(lista);
}

void produtosPorSetor()
{
    LimparTela();
    char setor[50];
    printf("Digite o setor que deseja buscar: ");
    scanf(" %[^\n]s", setor);

    int quantidade = quantidadeProdutosCSV();
    PRODUTO* lista;
    lista = (PRODUTO*)malloc(sizeof(PRODUTO) * quantidade);
    lerProdutosCSV(lista);

    bool encontrou = false;
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(lista[i].setor, setor) == 0)
        {
            exibirProduto(lista[i]);
            encontrou = true;
        }
    }
    free(lista);

    if (!encontrou)
    {
        printf("Nenhum produto encontrado no setor %s\n", setor);
    }
    system("pause");
}

void produtosEstoqueAbaixoDe5()
{
    LimparTela();
    int quantidade = quantidadeProdutosCSV();
    PRODUTO* lista;
    lista = (PRODUTO*)malloc(sizeof(PRODUTO) * quantidade);
    lerProdutosCSV(lista);

    bool encontrou = false;
    for (int i = 0; i < quantidade; i++)
    {
        if (lista[i].estoque < 5)
        {
            exibirProduto(lista[i]);
            encontrou = true;
        }
    }
    free(lista);

    if (!encontrou)
    {
        printf("Nenhum produto com estoque abaixo de 5\n");
    }
    system("pause");
}