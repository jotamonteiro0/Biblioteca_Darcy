#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

typedef enum {
    PERFIL_GERENTE,
    PERFIL_USUARIO
} Perfil;

typedef struct {
    char login[32];
    char senha[32];
    Perfil perfil;
} Conta;

typedef struct {
    int  id;
    char nome[100];
    char dataNasc[15];
} Usuario;

typedef struct {
    int  id;
    char nome[100];
    char autor[100];
    char dataPublicacao[15];
    int  quantidade;
} Exemplar;

const Conta contas[] = {
    { "admin01", "0000", PERFIL_GERENTE },
    { "user01",  "0000", PERFIL_USUARIO },
};

const int NUM_CONTAS = 2;

void pausar(void) {
    system("read -p 'Pressione ENTER para continuar...' _tmp");
}

void limpar(void) {
    system("clear");
}

void substituirArquivo(const char *original, const char *tmp) {
    remove(original);
    rename(tmp, original);
}

void lerSenha(char *buf, int tamanho) {
    struct termios old, novo;

    tcgetattr(STDIN_FILENO, &old);

    novo = old;
    novo.c_lflag &= ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &novo);

    scanf("%31s", buf);

    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    printf("\n");
}

Perfil realizarLogin(void) {
    char login[32];
    char senha[32];

    while (1) {

        limpar();

        printf("\n+------------------------------+\n");
        printf("|     BIBLIOTECA DARCY         |\n");
        printf("|          LOGIN               |\n");
        printf("+------------------------------+\n");

        printf("Login: ");
        scanf("%31s", login);

        printf("Senha: ");
        lerSenha(senha, 32);

        for (int i = 0; i < NUM_CONTAS; i++) {

            if (strcmp(contas[i].login, login) == 0 &&
                strcmp(contas[i].senha, senha) == 0) {

                printf("\nBem-vindo, %s!\n", login);

                pausar();

                return contas[i].perfil;
            }
        }

        printf("\nLogin ou senha invalidos.\n");

        pausar();
    }
}

int menuPrincipal(Perfil perfil) {

    int operacao;

    limpar();

    printf("\n+------------------------------+\n");
    printf("|     BIBLIOTECA DARCY         |\n");

    if (perfil == PERFIL_GERENTE)
        printf("|        [GERENTE]             |\n");
    else
        printf("|        [USUARIO]             |\n");

    printf("+------------------------------+\n");

    if (perfil == PERFIL_GERENTE) {

        printf("| 1 - Cadastrar Usuario        |\n");
        printf("| 2 - Listar Usuarios          |\n");
        printf("| 3 - Cadastrar Exemplar       |\n");
        printf("| 4 - Listar Exemplares        |\n");
        printf("| 5 - Emprestimo               |\n");
        printf("| 6 - Devolucao                |\n");
        printf("| 7 - Sair                     |\n");

    } else {

        printf("| 4 - Listar Exemplares        |\n");
        printf("| 5 - Emprestimo               |\n");
        printf("| 7 - Sair                     |\n");
    }

    printf("+------------------------------+\n");

    printf("Digite a operacao: ");
    scanf("%d", &operacao);

    return operacao;
}

void cadastrarUsuario(void) {

    FILE *f = fopen("Usuarios.txt", "a");

    if (!f) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Usuario u;

    printf("ID: ");
    scanf("%d", &u.id);

    printf("Nome: ");
    scanf(" %99[^\n]", u.nome);

    printf("Nascimento (DD/MM/AAAA): ");
    scanf("%14s", u.dataNasc);

    fprintf(f,
            "%d;%s;%s\n",
            u.id,
            u.nome,
            u.dataNasc);

    fclose(f);

    printf("Usuario cadastrado com sucesso.\n");

    pausar();
}

void listarUsuarios(void) {

    FILE *f = fopen("Usuarios.txt", "r");

    if (!f) {
        printf("Nenhum usuario cadastrado.\n");
        pausar();
        return;
    }

    Usuario u;

    printf("\n===== USUARIOS =====\n");

    while (fscanf(f,
                  "%d;%99[^;];%14[^\n]",
                  &u.id,
                  u.nome,
                  u.dataNasc) == 3) {

        printf("\nID: %d\n", u.id);
        printf("Nome: %s\n", u.nome);
        printf("Nascimento: %s\n", u.dataNasc);
    }

    fclose(f);

    pausar();
}

void cadastrarExemplar(void) {

    FILE *f = fopen("Exemplares.txt", "a");

    if (!f) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Exemplar e;

    printf("ID: ");
    scanf("%d", &e.id);

    printf("Nome: ");
    scanf(" %99[^\n]", e.nome);

    printf("Autor: ");
    scanf(" %99[^\n]", e.autor);

    printf("Data de Publicacao (DD/MM/AAAA): ");
    scanf("%14s", e.dataPublicacao);

    printf("Quantidade: ");
    scanf("%d", &e.quantidade);

    fprintf(f,
            "%d;%s;%s;%s;%d\n",
            e.id,
            e.nome,
            e.autor,
            e.dataPublicacao,
            e.quantidade);

    fclose(f);

    printf("Exemplar cadastrado com sucesso.\n");

    pausar();
}

void listarExemplares(void) {

    FILE *f = fopen("Exemplares.txt", "r");

    if (!f) {
        printf("Nenhum exemplar cadastrado.\n");
        pausar();
        return;
    }

    Exemplar e;

    printf("\n===== EXEMPLARES =====\n");

    while (fscanf(f,
                  "%d;%99[^;];%99[^;];%14[^;];%d",
                  &e.id,
                  e.nome,
                  e.autor,
                  e.dataPublicacao,
                  &e.quantidade) == 5) {

        printf("\nID: %d\n", e.id);
        printf("Nome: %s\n", e.nome);
        printf("Autor: %s\n", e.autor);
        printf("Data Publicacao: %s\n", e.dataPublicacao);
        printf("Quantidade: %d\n", e.quantidade);
    }

    fclose(f);

    pausar();
}

void emprestimo(void) {

    FILE *f = fopen("Exemplares.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!f || !temp) {

        printf("Erro ao manipular arquivos.\n");

        if (f) fclose(f);
        if (temp) fclose(temp);

        return;
    }

    int idBusca;

    printf("ID do exemplar: ");
    scanf("%d", &idBusca);

    int encontrado = 0;

    Exemplar e;

    while (fscanf(f,
                  "%d;%99[^;];%99[^;];%14[^;];%d",
                  &e.id,
                  e.nome,
                  e.autor,
                  e.dataPublicacao,
                  &e.quantidade) == 5) {

        if (e.id == idBusca) {

            encontrado = 1;

            if (e.quantidade > 0) {

                e.quantidade--;

                printf("Emprestimo realizado com sucesso.\n");

            } else {

                printf("Exemplar indisponivel.\n");
            }
        }

        fprintf(temp,
                "%d;%s;%s;%s;%d\n",
                e.id,
                e.nome,
                e.autor,
                e.dataPublicacao,
                e.quantidade);
    }

    fclose(f);
    fclose(temp);

    substituirArquivo("Exemplares.txt", "temp.txt");

    if (!encontrado)
        printf("Exemplar nao encontrado.\n");

    pausar();
}

void devolucao(void) {

    FILE *f = fopen("Exemplares.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!f || !temp) {

        printf("Erro ao manipular arquivos.\n");

        if (f) fclose(f);
        if (temp) fclose(temp);

        return;
    }

    int idBusca;

    printf("ID do exemplar: ");
    scanf("%d", &idBusca);

    char dataRetirada[15];
    char dataDevolucao[15];

    printf("Data retirada (DD/MM/AAAA): ");
    scanf("%14s", dataRetirada);

    printf("Data devolucao (DD/MM/AAAA): ");
    scanf("%14s", dataDevolucao);

    int diaR, mesR, anoR;
    int diaD, mesD, anoD;

    sscanf(dataRetirada,
           "%d/%d/%d",
           &diaR,
           &mesR,
           &anoR);

    sscanf(dataDevolucao,
           "%d/%d/%d",
           &diaD,
           &mesD,
           &anoD);

    int totalR = anoR * 365 + mesR * 30 + diaR;
    int totalD = anoD * 365 + mesD * 30 + diaD;

    int diasUsados = totalD - totalR;

    int diasAtraso =
        (diasUsados > 7)
        ? diasUsados - 7
        : 0;

    float multa = diasAtraso * 1.0f;

    int encontrado = 0;

    Exemplar e;

    while (fscanf(f,
                  "%d;%99[^;];%99[^;];%14[^;];%d",
                  &e.id,
                  e.nome,
                  e.autor,
                  e.dataPublicacao,
                  &e.quantidade) == 5) {

        if (e.id == idBusca) {

            encontrado = 1;

            e.quantidade++;
        }

        fprintf(temp,
                "%d;%s;%s;%s;%d\n",
                e.id,
                e.nome,
                e.autor,
                e.dataPublicacao,
                e.quantidade);
    }

    fclose(f);
    fclose(temp);

    substituirArquivo("Exemplares.txt", "temp.txt");

    if (!encontrado) {

        printf("Exemplar nao encontrado.\n");

        pausar();

        return;
    }

    printf("\nDias utilizados: %d\n", diasUsados);

    if (diasAtraso > 0) {

        printf("Atraso: %d dia(s)\n", diasAtraso);
        printf("Multa: R$ %.2f\n", multa);

    } else {

        printf("Devolucao no prazo.\n");
    }

    pausar();
}

int main(void) {

    int operacao;

    Perfil perfil;

    while (1) {

        perfil = realizarLogin();

        do {

            operacao = menuPrincipal(perfil);

            if (perfil == PERFIL_USUARIO &&
                operacao != 4 &&
                operacao != 5 &&
                operacao != 7) {

                printf("\nAcesso negado.\n");

                pausar();

                continue;
            }

            switch (operacao) {

                case 1:
                    cadastrarUsuario();
                    break;

                case 2:
                    listarUsuarios();
                    break;

                case 3:
                    cadastrarExemplar();
                    break;

                case 4:
                    listarExemplares();
                    break;

                case 5:
                    emprestimo();
                    break;

                case 6:
                    devolucao();
                    break;

                case 7:
                    printf("Saindo...\n");
                    pausar();
                    break;

                default:
                    printf("Opcao invalida.\n");
                    pausar();
            }

        } while (operacao != 7);
    }

    return 0;
}