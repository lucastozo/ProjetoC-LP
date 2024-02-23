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
                int idBusca;
                bool encontrou;
                switch (opcaoProdutos)
                {
                //Cadastrar produto
                case 1:
                    lerProduto(&p);
                    p.id = obterProximoIdProduto();
                    gravarProdutoCSV(p);
                    break;

                //Atualizar produto
                case 2:
                    printf("Digite o ID do produto que deseja buscar: ");
                    scanf("%d", &idBusca);

                    int quantidade = quantidadeProdutosCSV();
                    lista = (PRODUTO *)malloc(sizeof(PRODUTO) * quantidade);
                    lerProdutosCSV(lista);
                    encontrou = false;
                    remove("Produtos.csv");
                    for (int i = 0; i < quantidade; i++)
					{
                        if (lista[i].id == idBusca)
                        {
                            encontrou = true;
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
                    if (!encontrou)
					{
						printf("Nenhum produto encontrado com o ID %d\n", idBusca);
					}
                    free(lista);
                    break;

                //mostrar uma listagem de produtos por Setor
                case 3:
                    char setor[50];
                    printf("Digite o setor que deseja buscar: ");
                    scanf(" %[^\n]s", setor);
                    quantidade = quantidadeProdutosCSV();
                    lista = (PRODUTO *)malloc(sizeof(PRODUTO) * quantidade);
                    lerProdutosCSV(lista);
                    encontrou = false;
                    for (int i = 0; i < quantidade; i++)
                    {
                        if (strcmp(lista[i].setor, setor) == 0)
						{
							exibirProduto(lista[i]);
                            encontrou = true;
						}
					}
                    free(lista);
                    if(!encontrou)
					{
						printf("Nenhum produto encontrado no setor %s\n", setor);
					}
					system("pause");
					break;
                //Produtos com estoque abaixo de 5
                case 4:
                    quantidade = quantidadeProdutosCSV();
                    lista = (PRODUTO *)malloc(sizeof(PRODUTO) * quantidade);
                    lerProdutosCSV(lista);
                    encontrou = false;
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
