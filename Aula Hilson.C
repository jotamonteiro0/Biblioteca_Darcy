#include <stdio.h>
#include <stdlib.h>

FILE *ARQUIVO;

char nome[50], curso[50], disciplina[50], periodo[50];
int operacao;

void CadastrarAluno(){
    printf("Digite seu nome\n");
    scanf(" %[^\n]", nome);

    printf("Digite seu curso\n");
    scanf(" %[^\n]", curso);

    printf("Digite sua disciplina\n");
    scanf(" %[^\n]", disciplina);

    printf("Informe o período\n");
    scanf(" %[^\n]", periodo);
}

void GravarArquivo(){
    ARQUIVO = fopen("DadosAluno.txt", "a");

    if (ARQUIVO == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }

    fprintf(ARQUIVO, "Aluno........:%s\n",nome);
    fprintf(ARQUIVO, "Curso........:%s\n",curso);
    fprintf(ARQUIVO, "Disciplina...:%s\n",disciplina);
    fprintf(ARQUIVO, "Período......:%s\n\n",periodo);

    fclose(ARQUIVO);
}

int main(){
    do {
        CadastrarAluno();
        GravarArquivo();

        printf("Digite 0 para sair ou qualquer outro valor para continuar\n");
        scanf("%d", &operacao);

    } while(operacao != 0);

    return 0;
}