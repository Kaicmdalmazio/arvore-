/*Utilizando a estrutura que já fizemos de leitura de alunos e o que foi visto na disciplina de estrutura de dados faça:
-Implemente uma estrutura de árvore binária ordenada
-Utilize o nome do aluno para fazer a ordenação.
-Na estrutura principal (onde tem a raiz) guarde o nível da árvore. Imprima no final o tempo gasto para inserir todos os alunos, e também a altura da árvore (nível máximo).
-Faça a função de buscar o aluno por Nome.*/


#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>



//struct aluno
struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[50];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    Aluno *direita;
    Aluno *esquerda;
};


struct Alunos{
    Aluno *raiz;
    int temp;
    int tamanho;
};

void inicializa(){
    a.raiz = NULL;
    a.temp = 0;
    a.tamanho = 0;    
}

Alunos a;



int main(){
    inicializa();
    printf("------Sistema de leitura de alunos-------");
    
}