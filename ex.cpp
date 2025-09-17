#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------- STRUCTS ----------------
typedef struct Aluno {
    char matricula[9];
    char cpf[15];
    char nome[50];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    struct Aluno *direita;
    struct Aluno *esquerda;
} Aluno;

typedef struct {
    Aluno *raiz;
    int temp;      // pode ser usado para medir tempo ou auxiliar
    int tamanho;   // quantidade de alunos
} Alunos;

Alunos a; // variável global

// ---------------- FUNÇÕES ----------------

// Inicializa árvore
void inicializa() {
    a.raiz = NULL;
    a.temp = 0;
    a.tamanho = 0;
}

// Cria novo nó (Aluno)
Aluno* criarAluno(char matricula[], char cpf[], char nome[],
                  double nota, int idade, char curso[], char cidade[]) {
    Aluno *novo = (Aluno*) malloc(sizeof(Aluno));
    strcpy(novo->matricula, matricula);
    strcpy(novo->cpf, cpf);
    strcpy(novo->nome, nome);
    novo->nota = nota;
    novo->idade = idade;
    strcpy(novo->curso, curso);
    strcpy(novo->cidade, cidade);
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Inserir aluno ordenado pelo nome
Aluno* inserir(Aluno *raiz, Aluno *novo) {
    if (raiz == NULL) return novo;

    if (strcmp(novo->nome, raiz->nome) < 0)
        raiz->esquerda = inserir(raiz->esquerda, novo);
    else
        raiz->direita = inserir(raiz->direita, novo);

    return raiz;
}

// Carregar alunos de um arquivo
void carregarDeArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "..//alunos_completosV2.csv");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char matricula[9], cpf[15], nome[50], curso[40], cidade[40];
    double nota;
    int idade;

    while (fscanf(arquivo, "%s %s %s %lf %d %s %s",
                  matricula, cpf, nome, &nota, &idade, curso, cidade) == 7) {
        Aluno *novo = criarAluno(matricula, cpf, nome, nota, idade, curso, cidade);
        a.raiz = inserir(a.raiz, novo);
        a.tamanho++;
    }

    fclose(arquivo);
}

// Impressão em ordem
void imprimirEmOrdem(Aluno *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("Nome: %s | Matrícula: %s | CPF: %s | Nota: %.2f | Idade: %d | Curso: %s | Cidade: %s\n",
               raiz->nome, raiz->matricula, raiz->cpf,
               raiz->nota, raiz->idade, raiz->curso, raiz->cidade);
        imprimirEmOrdem(raiz->direita);
    }
}

// ---------------- MAIN ----------------
int main() {
    inicializa();

    carregarDeArquivo("..//alunos_completosV2.csv");

    printf("\n--- Alunos em ordem alfabética ---\n");
    imprimirEmOrdem(a.raiz);

    printf("\nTotal de alunos: %d\n", a.tamanho);

    return 0;
}
