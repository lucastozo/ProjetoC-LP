#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "apresentacao.h"
#include "tempo.h"

/*************************************************************************************/

/*************************************************************************************/
/**
 * Main para teste das funções
 */
int main(int argc, char const *argv[])
{
    /* code */
    PRODUTO *lista;
    PRODUTO produto;
    int opcao, opcaoVendas, opcaoClientes, opcaoProdutos;
    char msg[50];
    DATA d1, d2;
    /*
    printf("Data 1\n");
    printf("\tDia ->");
    scanf(" %d", &d1.dia);
    printf("\tMês ->");
    scanf(" %d", &d1.mes);
    printf("\tAno ->");
    scanf(" %d", &d1.ano);

    printf("Data 2\n");
    printf("\tDia ->");
    scanf(" %d", &d2.dia);
    printf("\tMês ->");
    scanf(" %d", &d2.mes);
    printf("\tAno ->");
    scanf(" %d", &d2.ano);

    int resp = DataCmp(d1,d2);
    switch (resp)    
    {
    case 0: printf("Datas iguais\n");            
        break;
    
    case -1: printf("Data 1 menos recente que Data 2\n");            
        break;
    
    case 1: printf("Data 1 mais recente que Data 2\n");            
        break;
    default:
        break;
    }
    getchar();
        
    lerProduto(&produto);
    produto.id = obterProximoIdProduto();
    exibirProduto(produto);
    //gravarProdutoCSV(produto);
    getchar();
    */
    do
    {
        opcao = MenuPrincipal();
        switch (opcao)
        {
        case 1:
            do
            {
                opcaoVendas = MenuVendas();
                switch (opcaoVendas)
                {
                case 1:
                    printf("Vai abrir função nova venda");
                    break;
                case 2:
                    printf("Vai abrir função lista de vendas do cliente");
                    break;
                default:
                    break;
                }
            } while (opcaoVendas !=9);
            break;
        case 2:
            do
            {
                opcaoClientes = MenuClientes();
                switch (opcaoClientes)
                {
                case 1:
                    printf("Vai abrir função castrar novo cliente");
                    break;
                case 2:
                    printf("Vai abrir função atualizar pontuação");
                    break;
                case 3:
                    printf("Vai abrir função atualizar cliente");
                case 4:
                    printf("Vai abrir função listar clientes de 18 a 25");
                    break;
                case 5:
                    printf("Vai abrir função listar clientes acima de 1000 pontos");
                    break;
                default:
                    break;
                }
            } while (opcaoClientes != 9);
            break;
        case 3:
            do
            {
                opcaoProdutos = MenuProdutos();
                PRODUTO p;
                switch (opcaoProdutos)
                {
                case 1:
                    do
                    {
                        system("cls");
                        printf("1. CSV\n2. DAT\nEscolha o formato: ");
                        int formato;
                        scanf(" %d", &formato);
                    } while (opcaoProdutos != 1 && opcaoProdutos != 2);
                    lerProduto(&p);
                    p.id = obterProximoIdProduto();
                    if (opcaoProdutos == 1)
                    {
                        gravarProdutoCSV(p);
					}
					else
					{
						gravarProdutoDAT(p);
					}
                    break;
                case 2:
                    do
                    {
                        system("cls");
                        printf("1. CSV\n2. DAT\nEscolha o formato: ");
                        int formato;
                        scanf(" %d", &formato);
                    } while (opcaoProdutos != 1 && opcaoProdutos != 2);
                    int idBusca;
                    printf("Informe o ID do produto que deseja atualizar: ");
                    scanf(" %d", &idBusca);
                    int id;
                    if (opcaoProdutos == 1)
					{
                        printf("Vai abrir função atualizar produto em CSV");
                    }
                    else
                    {
						printf("Vai abrir função atualizar produto em DAT");
					}
                    break;
                case 3:
                    printf("Vai abrir função estoque por setor");
                case 4:
                    printf("Vai abrir função produtos com estoque baixo");
                    break;
                default:
                    break;
                }
            } while (opcaoProdutos != 9);
            break;
            /*lista = (PRODUTO *)malloc(sizeof(PRODUTO) * 10);
            int qtdeProdutos = lerProdutosCSV(lista);
            printf("Quantidade de registros: %d\n", qtdeProdutos);
            for (int i = 0; i < qtdeProdutos; i++)
            {
                separador();
                printf("Produto %d\n", i + 1);
                separador();
                exibirProduto(lista[i]);
                gravarProdutoDAT(lista[i]);
                separador();
            }
            free(lista);
            lista = (PRODUTO *)malloc(sizeof(PRODUTO) * 10);
            int qtdeBin;
            qtdeBin = lerProdutosDAT(lista);
            printf("Quantidade de registros (binário): %d\n", qtdeBin);     
            getchar();  
            getchar();*/    
            break;
        default:
            break;
        }
    } while (opcao != 9);
}
