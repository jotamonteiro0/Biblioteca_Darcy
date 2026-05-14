#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    char nascimento[15];
} Usuario;

typedef struct {
    int id;
    char nome[100];
    char autor[100];
    int quantidade;
} Exemplar;

typedef struct {
    int idUsuario;
    int idExemplar;
    char dataRetirada[15];
} Emprestimo;

FILE *f, *temp;

void LimparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

void MenuPrincipal(int *operacao) {
    LimparTela();

    const char *lista[] = {
        "Cadastrar Usuario",
        "Listar Usuarios",
        "Cadastrar Exemplar",
        "Listar Exemplares",
        "Emprestimo",
        "Devolucao",
        "Sair"
    };

    int tamanho = sizeof(lista) / sizeof(lista[0]);

    printf("\n+------------------------------+\n");
    printf("|     BIBLIOTECA DARCY         |\n");
    printf("+------------------------------+\n");

    for (int i = 0; i < tamanho; i++) {
        printf("| %-2d - %-22s |\n", i + 1, lista[i]);
    }

    printf("+------------------------------+\n");
    printf("Digite a operacao: ");
    scanf("%d", operacao);
}

void CadastrarUsuario() {
    Usuario u;

    f = fopen("Usuarios.txt", "a");

    if (!f) {
        printf("Erro ao abrir Usuarios.txt\n");
        return;
    }

    printf("ID: ");
    scanf("%d", &u.id);

    printf("Nome: ");
    scanf(" %[^\n]", u.nome);

    printf("Nascimento: ");
    scanf("%14s", u.nascimento);

    fprintf(f, "%d;%s;%s\n",
            u.id,
            u.nome,
            u.nascimento);

    fclose(f);

    printf("\nUsuario cadastrado com sucesso.\n");
    Pausar();
}

void ListarUsuarios() {
    Usuario u;

    f = fopen("Usuarios.txt", "r");

    if (!f) {
        printf("Erro ao abrir Usuarios.txt\n");
        return;
    }

    printf("\n===== USUARIOS =====\n");

    while (fscanf(f, "%d;%99[^;];%14[^\n]\n",
                  &u.id,
                  u.nome,
                  u.nascimento) == 3) {

        printf("\nID: %d\n", u.id);
        printf("Nome: %s\n", u.nome);
        printf("Nascimento: %s\n", u.nascimento);
    }

    fclose(f);

    Pausar();
}

void CadastrarExemplar() {
    Exemplar e;

    f = fopen("Exemplares.txt", "a");

    if (!f) {
        printf("Erro ao abrir Exemplares.txt\n");
        return;
    }

    printf("ID: ");
    scanf("%d", &e.id);

    printf("Nome: ");
    scanf(" %[^\n]", e.nome);

    printf("Autor: ");
    scanf(" %[^\n]", e.autor);

    printf("Quantidade: ");
    scanf("%d", &e.quantidade);

    fprintf(f, "%d;%s;%s;%d\n",
            e.id,
            e.nome,
            e.autor,
            e.quantidade);

    fclose(f);

    printf("\nExemplar cadastrado com sucesso.\n");
    Pausar();
}

void ListarExemplares() {
    Exemplar e;

    f = fopen("Exemplares.txt", "r");

    if (!f) {
        printf("Erro ao abrir Exemplares.txt\n");
        return;
    }

    printf("\n===== EXEMPLARES =====\n");

    while (fscanf(f, "%d;%99[^;];%99[^;];%d\n",
                  &e.id,
                  e.nome,
                  e.autor,
                  &e.quantidade) == 4) {

        printf("\nID: %d\n", e.id);
        printf("Nome: %s\n", e.nome);
        printf("Autor: %s\n", e.autor);
        printf("Quantidade: %d\n", e.quantidade);
    }

    fclose(f);

    Pausar();
}

void EmprestimoLivro() {
    Exemplar e;
    Emprestimo emp;

    int encontrado = 0;

    f = fopen("Exemplares.txt", "r");
    temp = fopen("temp.txt", "w");

    if (!f || !temp) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    printf("ID do usuario: ");
    scanf("%d", &emp.idUsuario);

    printf("ID do exemplar: ");
    scanf("%d", &emp.idExemplar);

    printf("Data de retirada (DD/MM/AAAA): ");
    scanf("%14s", emp.dataRetirada);

    while (fscanf(f, "%d;%99[^;];%99[^;];%d\n",
                  &e.id,
                  e.nome,
                  e.autor,
                  &e.quantidade) == 4) {

        if (e.id == emp.idExemplar) {
            encontrado = 1;

            if (e.quantidade > 0) {

                e.quantidade--;

                FILE *fe = fopen("Emprestimos.txt", "a");

                if (fe) {
                    fprintf(fe,
                            "%d;%d;%s\n",
                            emp.idUsuario,
                            emp.idExemplar,
                            emp.dataRetirada);

                    fclose(fe);
                }

                printf("\nEmprestimo realizado.\n");

            } else {
                printf("\nExemplar indisponivel.\n");
            }
        }

        fprintf(temp,
                "%d;%s;%s;%d\n",
                e.id,
                e.nome,
                e.autor,
                e.quantidade);
    }

    fclose(f);
    fclose(temp);

    remove("Exemplares.txt");
    rename("temp.txt", "Exemplares.txt");

    if (!encontrado)
        printf("\nExemplar nao encontrado.\n");

    Pausar();
}

void DevolucaoLivro() {
    Exemplar e;

    int idBusca;
    int encontrado = 0;

    f = fopen("Exemplares.txt", "r");
    temp = fopen("temp.txt", "w");

    if (!f || !temp) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    printf("ID do exemplar: ");
    scanf("%d", &idBusca);

    while (fscanf(f, "%d;%99[^;];%99[^;];%d\n",
                  &e.id,
                  e.nome,
                  e.autor,
                  &e.quantidade) == 4) {

        if (e.id == idBusca) {
            encontrado = 1;
            e.quantidade++;
        }

        fprintf(temp,
                "%d;%s;%s;%d\n",
                e.id,
                e.nome,
                e.autor,
                e.quantidade);
    }

    fclose(f);
    fclose(temp);

    remove("Exemplares.txt");
    rename("temp.txt", "Exemplares.txt");

    if (encontrado)
        printf("\nDevolucao realizada.\n");
    else
        printf("\nExemplar nao encontrado.\n");

    Pausar();
}

int main() {

    int operacao;

    do {

        MenuPrincipal(&operacao);

        switch (operacao) {

            case 1:
                CadastrarUsuario();
                break;

            case 2:
                ListarUsuarios();
                break;

            case 3:
                CadastrarExemplar();
                break;

            case 4:
                ListarExemplares();
                break;

            case 5:
                EmprestimoLivro();
                break;

            case 6:
                DevolucaoLivro();
                break;

            case 7:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                Pausar();
        }

    } while (operacao != 7);

    return 0;
}