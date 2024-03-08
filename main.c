#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
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
    /*
    Code Page para arrumar o input e output do console
    mudar SetConsoleOutputCP para 1252 e depois para 65001 
    sempre que quiser exibir (print) os dados dos registros que contém caracteres com acento, por exemplo: 'listaclientes.nome' : João
    */
    unsigned int cpin = GetConsoleCP();
    unsigned int cpout = GetConsoleOutputCP();
    SetConsoleCP(1252);
    SetConsoleOutputCP(65001);

    int opcao, opcaoVendas, opcaoClientes, opcaoProdutos;
    char msg[50];
    DATA d1, d2;
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
                    Nova_Venda(); 
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
                switch (opcaoClientes)
                {
                case 1:
                    cadastroNovoCliente();
                    break;
                case 2:
                    adicionarManualPontosCliente();
                    break;
                case 3:
                    atualizarCliente();
                    break;
                case 4:
                    listarClientes18a25anos();
                    break;
                case 5:
                    listarClientesAcima1000Pontos();
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
    SetConsoleCP(cpin);
    SetConsoleOutputCP(cpout);
}
