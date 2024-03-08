#ifndef __APRESENTACAO_H__
#define __APRESENTACAO_H__

/**
 * Limpa o terminal
*/
void LimparTela();

/**
 * Cria um separador de linhas para exibição
*/
void separador();

/**
 * Gera o menu principal e retorna a opção desejada pelo usuário
 * @return Retorna o item escolhido pelo o usuário
*/
int MenuPrincipal();

/**
 * Gera o menu de vendas e retorna a opção desejada pelo usuário
 * @return Retorna o item escolhido pelo o usuário
*/
int MenuVendas();

/**
 * Gera o menu de clientes e retorna a opção desejada pelo usuário
 * @return Retorna o item escolhido pelo o usuário
*/
int MenuClientes();

/**
 * Gera o menu de produtos e retorna a opção desejada pelo usuário
 * @return Retorna o item escolhido pelo o usuário
*/
int MenuProdutos();

#endif