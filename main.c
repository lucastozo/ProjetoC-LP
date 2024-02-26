#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "apresentacao.h"
#include "tempo.h"
#include "cliente.h"
#include "vendas.h"

/*************************************************************************************/

/*************************************************************************************/
/**
 * Main para teste das funções
 */
int main(int argc, char const *argv[])
{
    /* code */
    PRODUTO *lista;
    CLIENTE *pListaClientes;
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
                {
                    printf("Vai abrir função nova venda");
                    break;
                }
                case 2:
                    listarComprasDeCliente();
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
                CLIENTE novoCliente;
                int quantidade = quantidadeClientesCSV;
                switch (opcaoClientes)
                {
                case 1:
                    // Cadastro de novo cliente
                    lerCliente(&novoCliente);
                    gravarCliente(novoCliente);
                    break;
                case 2:
                    // Atualização da pontuação
                    break;
                case 3:
                    quantidade = quantidadeClientesCSV();
                    pListaClientes = (CLIENTE*)malloc(sizeof(CLIENTE) * quantidade);
                    lerClientesCSV(pListaClientes);
                    atualizarCliente(pListaClientes);
                    free(pListaClientes);
                    // Atualização dos dados do cliente
                case 4:
                    // listar clientes de 18 a 25 anos
                    break;
                case 5:
                    // listar clientes com mais de 1000 pontos
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
                char setor[50];
                switch (opcaoProdutos)
                {
                //Cadastrar produto
                case 1:
                    cadastrarProduto();
                    break;
                //Atualizar produto
                case 2:
                    atualizarProduto();
                    break;
                //mostrar uma listagem de produtos por Setor
                case 3:
                    produtosPorSetor();
					break;
                //Produtos com estoque abaixo de 5
                case 4:
                    produtosEstoqueAbaixoDe5();
                    break;
                default:
                    break;
                }
            } while (opcaoProdutos != 9);
            break;
        default:
            break;
        }
    } while (opcao != 9);
}
