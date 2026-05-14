#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int codigoProduto, quantidade, operacao;
char descricao[80], tipoProduto[45];
float valorUnitario, valorTotal;

void RealizarVenda() {
    printf("Informe o código do produto\n");
    scanf("%i", &codigoProduto);             

    printf("Descrição do Produto\n");
    scanf(" %[^\n]", descricao);             

    printf("Digite a quantidade desejada\n");
    scanf("%i", &quantidade);                 

    printf("Digite o valor unitário do produto\n");
    scanf("%f", &valorUnitario);              

    printf("Informe o tipo do produto (importado/nacional)\n");
    scanf("%s", tipoProduto);                 

    valorTotal = quantidade * valorUnitario;
}

void ImprimirCupom() {
    printf("\n+==============================+\n");
    printf("+         CUPOM FISCAL         +\n");
    printf("+------------------------------+\n");
    printf("| Código:        %i\n",            codigoProduto);
    printf("| Descrição:     %s\n",            descricao);
    printf("| Tipo:          %s\n",            tipoProduto);  
    printf("| Quantidade:    %i\n",            quantidade);
    printf("| Valor Unit.:   R$ %.2f\n",       valorUnitario);
    printf("+------------------------------+\n");
    printf("| Valor Total:   R$ %.2f\n",       valorTotal);
    printf("+==============================+\n");
}

void MenuVenda() {
    printf("\n+==============================+\n");
    printf("+      SISTEMA DE VENDA        +\n");
    printf("+==============================+\n");
    printf("+ 1 - Realizar Venda           +\n");
    printf("+ 2 - Imprimir Cupom           +\n");
    printf("+ 0 - Sair                     +\n");
    printf("+==============================+\n");
    printf("Digite a operação desejada:\n"); 
    scanf("%i", &operacao);
}

int main() {
    do {
        MenuVenda();                           
        switch (operacao) {
        case 1:
            RealizarVenda();
            break;
        case 2:
            ImprimirCupom();
            break;
        }

    } while (operacao != 0);                 

    return 0;
}