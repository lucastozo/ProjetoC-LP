#include "produtos.h"
#include "apresentacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char separadorCSV = ';';
// char SETOR[6][] = {"Higiene", "Limpeza", "Bebidas", "Frios", "Padaria", "Açougue"};

/**
 * Rotina que lê os dados de um produto através do teclado
 * @param p Ponteiro para um registro do tipo PRODUTO,
 * onde os dados lidos serão armazenados
 */
void lerProduto(PRODUTO *p)
{
    separador();
    printf("Lendo um produto \n");
    printf("Setor:  ");
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

/**
 * Exibe os campos contidos em um registro do tipo PRODUTO
 * @param p Registro que será exibido
 */
void exibirProduto(PRODUTO p)
{
    char data[50];
    printf("\n");
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
}
/**
 * Gravando os dados de um produto no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param p Produto que será salvo no registro
 */
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
        
       // fseek(csv, 0, SEEK_END);
     
    // arquivo ja existe, insere apenas o dado no final do arquivo
    fprintf(csv, "%d;%s;%s;%.2f;%d/%d/%d;%d\n",
            p.id, p.setor, p.nome, p.preco,
            p.dataValidade.dia, p.dataValidade.mes, p.dataValidade.ano,
            p.estoque);
    fflush(csv);
    fclose(csv);
    // salvando o cabeçalho do arquivo
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
/**
 * Leitura de dados do CSV para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de produtos cadastrados
 */
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

/**
 * Grava um registro de PRODUTO em um arquivo binário
 * @param p Produto que será salvo no arquivo
 */
int gravarProdutoDAT(PRODUTO p)
{
    char nomeArquivo[] = "Produtos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "a+b");
    if (dat == NULL)
    {
        dat = fopen(nomeArquivo, "ab");
    }
    fwrite(&p, sizeof(PRODUTO), 1, dat);
    fflush(dat);
    fclose(dat);
    return 0;
}

int quantidadeProdutosDAT()
{
    int qtde = 0;
    PRODUTO dummy;
    char nomeArquivo[] = "Produtos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    if (dat != NULL)
    {
        while (fread(&dummy, sizeof(PRODUTO), 1, dat) > 0)
            qtde++;

        return qtde;
    }
    else
    {
        return 0;
    }
}

/**
 * Leitura de dados do arquivo binário para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de produtos cadastrados
 */
int lerProdutosDAT(PRODUTO *lista)
{
    int qtde = 0;
    char nomeArquivo[] = "Produtos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    if (dat != NULL)
    {
        while (fread(&lista[qtde], sizeof(PRODUTO), 1, dat) > 0)
        {
            // exibirProduto(lista[qtde]);
            qtde++;
        }
        return qtde;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivo);
        return -1;
    }
}


/**
 * Rotina que devolve o id a ser utilizado no próximo cadastro
 * @param formato Define se é para o tipo de arquivo csv ou para o tipo dat
 * @return Retorna o próximo ID a ser utilizado. Se o formato não for definido para 
 * um dos dois válidos ("CSV" ou "DAT"), a função retorna -1.
*/
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

//procedimentos de produto
/*
Procedimento que insere um novo produto no CSV
*/
void cadastrarProduto()
{
    PRODUTO p;
    lerProduto(&p);
    p.id = obterProximoIdProduto();
    gravarProdutoCSV(p);
}

/*
Procedimento que atualiza os dados de um produto no CSV
*/
void atualizarProduto()
{
    PRODUTO p;
    printf("Digite o ID do produto que deseja buscar: ");
    int idBusca;
    scanf("%d", &idBusca);

    int quantidade = quantidadeProdutosCSV();
    PRODUTO* lista;
    lista = (PRODUTO*)malloc(sizeof(PRODUTO) * quantidade);

    lerProdutosCSV(lista);
    remove("Produtos.csv");
    for (int i = 0; i < quantidade; i++)
    {
        if (lista[i].id == idBusca)
        {
            exibirProduto(lista[i]);
            PRODUTO p = lista[i];
            printf("Deseja atualizar o produto? (S/N): ");
            char resp;
            scanf(" %c", &resp);
            if (resp == 'S' || resp == 's')
            {
                lerProduto(&p);
                p.id = idBusca;
                lista[i] = p;
            }
        }
        gravarProdutoCSV(lista[i]);
    }
    free(lista);
}

/*
Procedimento que mostra todos os produtos de um dado setor
*/
void produtosPorSetor()
{
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

/*
Procedimento que mostra todos os produtos com estoque abaixo de 5
*/
void produtosEstoqueAbaixoDe5()
{
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