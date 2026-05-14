#include <stdio.h>

typedef struct {
    char nome[50];
    int matricula;
    float nota[3];
    float media;
} Aluno;

typedef struct {
    char nome[50];
    int quantidade;
    float preco;
} Produto;

typedef struct {
    char nome[50];
    float salario;
} Funcionario;

typedef struct {
    char modelo[50];
    float consumo;
} Carro;

typedef struct {
    char titulo[60];
    char autor[50];
    int paginas;
} Livro;

typedef struct {
    char nome[50];
    float total_vendas;
} Vendedor;

typedef struct {
    char nome[50];
    int idade;
} Paciente;

typedef struct {
    char nome[50];
    float preco;
    int quantidade;
} Item;

typedef struct {
    char nome[50];
    float tempo;
} Atleta;

typedef struct {
    char local[50];
    float temperatura;
} Sensor;

void ex1() {
    Aluno a;
    printf("\n=== Exercicio 1: Desempenho de Alunos ===\n");
    printf("Nome: ");
    scanf("%49s", a.nome);
    printf("Matricula: ");
    scanf("%d", &a.matricula);
    for (int i = 0; i < 3; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &a.nota[i]);
    }
    a.media = (a.nota[0] + a.nota[1] + a.nota[2]) / 3.0f;
    printf("Aluno: %s | Matricula: %d | Media: %.2f\n", a.nome, a.matricula, a.media);
    printf("Situacao: %s\n", a.media >= 7.0f ? "Aprovado" : "Reprovado");
}

void ex2() {
    Produto produtos[5];
    printf("\n=== Exercicio 2: Estoque Baixo ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Produto %d - Nome: ", i + 1);
        scanf("%49s", produtos[i].nome);
        printf("Quantidade: ");
        scanf("%d", &produtos[i].quantidade);
        printf("Preco: ");
        scanf("%f", &produtos[i].preco);
    }
    FILE *arq = fopen("estoque_baixo.txt", "w");
    printf("Produtos com estoque baixo (< 10):\n");
    for (int i = 0; i < 5; i++) {
        if (produtos[i].quantidade < 10) {
            printf("- %s | Qtd: %d\n", produtos[i].nome, produtos[i].quantidade);
            if (arq) fprintf(arq, "%s | Qtd: %d\n", produtos[i].nome, produtos[i].quantidade);
        }
    }
    if (arq) fclose(arq);
}

void ex3() {
    Funcionario func[4];
    printf("\n=== Exercicio 3: Bonus Salarial ===\n");
    for (int i = 0; i < 4; i++) {
        printf("Funcionario %d - Nome: ", i + 1);
        scanf("%49s", func[i].nome);
        printf("Salario: ");
        scanf("%f", &func[i].salario);
    }
    for (int i = 0; i < 4; i++)
        if (func[i].salario < 2000.0f)
            func[i].salario *= 1.10f;
    FILE *arq = fopen("funcionarios.txt", "w");
    printf("Funcionarios apos ajuste:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s | Salario: R$ %.2f\n", func[i].nome, func[i].salario);
        if (arq) fprintf(arq, "%s | Salario: R$ %.2f\n", func[i].nome, func[i].salario);
    }
    if (arq) fclose(arq);
}

void ex4() {
    Carro carros[3];
    printf("\n=== Exercicio 4: Carro Mais Economico ===\n");
    for (int i = 0; i < 3; i++) {
        printf("Carro %d - Modelo: ", i + 1);
        scanf("%49s", carros[i].modelo);
        printf("Consumo (km/l): ");
        scanf("%f", &carros[i].consumo);
    }
    int melhor = 0;
    for (int i = 1; i < 3; i++)
        if (carros[i].consumo > carros[melhor].consumo)
            melhor = i;
    printf("Carro mais economico: %s | %.2f km/l\n", carros[melhor].modelo, carros[melhor].consumo);
    FILE *arq = fopen("carros.txt", "w");
    if (arq) {
        for (int i = 0; i < 3; i++)
            fprintf(arq, "%s | %.2f km/l\n", carros[i].modelo, carros[i].consumo);
        fprintf(arq, "Mais economico: %s\n", carros[melhor].modelo);
        fclose(arq);
    }
}

void ex5() {
    Livro livros[3];
    printf("\n=== Exercicio 5: Livros Extensos ===\n");
    for (int i = 0; i < 3; i++) {
        printf("Livro %d - Titulo: ", i + 1);
        scanf("%59s", livros[i].titulo);
        printf("Autor: ");
        scanf("%49s", livros[i].autor);
        printf("Paginas: ");
        scanf("%d", &livros[i].paginas);
    }
    FILE *arq = fopen("livros_extensos.txt", "w");
    printf("Livros com mais de 300 paginas:\n");
    for (int i = 0; i < 3; i++) {
        if (livros[i].paginas > 300) {
            printf("%s (%s) - %d pags\n", livros[i].titulo, livros[i].autor, livros[i].paginas);
            if (arq) fprintf(arq, "%s (%s) - %d pags\n", livros[i].titulo, livros[i].autor, livros[i].paginas);
        }
    }
    if (arq) fclose(arq);
}

void ex6() {
    Vendedor v[5];
    printf("\n=== Exercicio 6: Melhor Vendedor ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Vendedor %d - Nome: ", i + 1);
        scanf("%49s", v[i].nome);
        printf("Total de vendas: R$ ");
        scanf("%f", &v[i].total_vendas);
    }
    int melhor = 0;
    for (int i = 1; i < 5; i++)
        if (v[i].total_vendas > v[melhor].total_vendas)
            melhor = i;
    printf("Melhor vendedor: %s | R$ %.2f\n", v[melhor].nome, v[melhor].total_vendas);
}

void ex7() {
    Paciente p[5];
    printf("\n=== Exercicio 7: Pacientes Prioritarios ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Paciente %d - Nome: ", i + 1);
        scanf("%49s", p[i].nome);
        printf("Idade: ");
        scanf("%d", &p[i].idade);
    }
    printf("Pacientes prioritarios (idade >= 60):\n");
    for (int i = 0; i < 5; i++)
        if (p[i].idade >= 60)
            printf("%s | %d anos\n", p[i].nome, p[i].idade);
}

void ex8() {
    Item itens[5];
    float total = 0.0f;
    printf("\n=== Exercicio 8: Desconto em Compras ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Produto %d - Nome: ", i + 1);
        scanf("%49s", itens[i].nome);
        printf("Preco: ");
        scanf("%f", &itens[i].preco);
        printf("Quantidade: ");
        scanf("%d", &itens[i].quantidade);
        total += itens[i].preco * itens[i].quantidade;
    }
    printf("Total bruto: R$ %.2f\n", total);
    if (total > 500.0f) {
        float desconto = total * 0.05f;
        total -= desconto;
        printf("Desconto de 5%% aplicado: -R$ %.2f\n", desconto);
    }
    printf("Total final: R$ %.2f\n", total);
}

void ex9() {
    Atleta atletas[4];
    printf("\n=== Exercicio 9: Vencedor ===\n");
    for (int i = 0; i < 4; i++) {
        printf("Atleta %d - Nome: ", i + 1);
        scanf("%49s", atletas[i].nome);
        printf("Tempo (s): ");
        scanf("%f", &atletas[i].tempo);
    }
    int vencedor = 0;
    for (int i = 1; i < 4; i++)
        if (atletas[i].tempo < atletas[vencedor].tempo)
            vencedor = i;
    printf("Vencedor: %s | %.2fs\n", atletas[vencedor].nome, atletas[vencedor].tempo);
}

void ex10() {
    Sensor sensores[5];
    printf("\n=== Exercicio 10: Maior Temperatura ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Sensor %d - Local: ", i + 1);
        scanf("%49s", sensores[i].local);
        printf("Temperatura (C): ");
        scanf("%f", &sensores[i].temperatura);
    }
    int maior = 0;
    for (int i = 1; i < 5; i++)
        if (sensores[i].temperatura > sensores[maior].temperatura)
            maior = i;
    printf("Maior temperatura: %s | %.1f C\n", sensores[maior].local, sensores[maior].temperatura);
}

int main() {
    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Desempenho de alunos\n");
        printf("2. Estoque baixo\n");
        printf("3. Bonus salarial\n");
        printf("4. Carro mais economico\n");
        printf("5. Livros extensos\n");
        printf("6. Melhor vendedor\n");
        printf("7. Pacientes prioritarios\n");
        printf("8. Desconto em compras\n");
        printf("9. Vencedor\n");
        printf("10. Maior temperatura\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:  ex1();  break;
            case 2:  ex2();  break;
            case 3:  ex3();  break;
            case 4:  ex4();  break;
            case 5:  ex5();  break;
            case 6:  ex6();  break;
            case 7:  ex7();  break;
            case 8:  ex8();  break;
            case 9:  ex9();  break;
            case 10: ex10(); break;
            case 0:  printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}