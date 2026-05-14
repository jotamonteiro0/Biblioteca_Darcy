#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char usuario[50], senha[15], descricao[50];
int codigoProduto, operacao = 1, loginAtivo = 0, opMenu, quantidade = 0;
float ValorProduto = 0, ValorTotal = 0;

void EfetuarLogin(){
    printf("=========================\n");
    printf("|    Acesso ao Sistema  |\n");
    printf("=========================\n");

    printf("Usuário: ");
    scanf("%s", usuario);

    printf("Senha: ");
    scanf("%s", senha);

    if (strcmp(usuario, "admin") == 0 && strcmp(senha, "admin") == 0){
        loginAtivo = 1;
        printf("Login realizado com sucesso!\n");
    } else {
        printf("Usuário ou senha inválidos.\n");
    }
}

void MenuOperacao(){
    printf("\n==========================================\n");
    printf("|            SISTEMA DE VENDA            |\n");
    printf("==========================================\n");
    printf("1 - Gerar Pedido\n");
    printf("2 - Emitir Cupom\n");
    printf("==========================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opMenu);
}

void GerarPedido(){
    printf("\nDigite o código do produto: ");
    scanf("%d", &codigoProduto);

    printf("Digite a descrição do produto: ");
    scanf(" %[^\n]", descricao);

    printf("Informe a quantidade: ");
    scanf("%d", &quantidade);

    printf("Informe o valor do produto: ");
    scanf("%f", &ValorProduto);

    ValorTotal = quantidade * ValorProduto;

    printf("Pedido gerado com sucesso!\n");
}

void ImprimirCupom() {
    if (quantidade == 0) {
        printf("\nNenhum pedido foi gerado ainda.\n");
        return;
    }

    printf("\n+==============================+\n");
    printf("|         CUPOM FISCAL         |\n");
    printf("+==============================+\n");
    printf("| Código:        %d\n", codigoProduto);
    printf("| Produto:       %s\n", descricao);
    printf("| Quantidade:    %d\n", quantidade);
    printf("| Valor Unit.:   R$ %.2f\n", ValorProduto);
    printf("+------------------------------+\n");
    printf("| Total Venda:   R$ %.2f\n", ValorTotal);
    printf("+==============================+\n");
}

int main(void){

    while (operacao != 0){

        if (!loginAtivo){
            EfetuarLogin();
            if (!loginAtivo) continue;
        }

        MenuOperacao();

        switch (opMenu){
            case 1:
                GerarPedido();
                break;
            case 2:
                ImprimirCupom();
                break;
            default:
                printf("Opção inválida.\n");
        }

        printf("\nDigite 0 para sair ou qualquer outro valor para continuar: ");
        scanf("%d", &operacao);
    }

    return 0;
}