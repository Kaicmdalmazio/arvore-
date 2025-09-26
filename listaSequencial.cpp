

//atividade de Lista sequencial
/*Faça a atividade de inserção de aluno utilizando Lista Sequencial (Vetores). Crie um vetor de 2^20 de tamanho e vá inserindo alunos 
na árvore de forma ordenada como feito na atividade anterior. Como a árvore não está balanceada, esse tamanho de vetor não é suficiente. 
Assim quando a inserção tentar inserir em uma posição que não caiba mais no vetor. Interrompa o programa e exiba quantos alunos foram inseridos*/


#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string.h>

#define MAX 1048576

//struct aluno
struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[50];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
};


struct ListaAlunos{
    Aluno* vetorAlunos;
    int quantidadeInserida;
};

 
ListaAlunos lista;

//ja vou alocar aqui pra n ter que botar no main achei melhor
void inicializa(){
    lista.vetorAlunos = (Aluno*)malloc(MAX * sizeof(Aluno));
    lista.quantidadeInserida = 0;
}


void adicionarAluno(Aluno novoAluno) {
    if (lista.quantidadeInserida >= MAX) {
        printf("Vetor cheio! Não foi possível inserir mais alunos.\n");
        printf("Total de alunos inseridos: %d\n", lista.quantidadeInserida);
        free(lista.vetorAlunos);
        exit(0);
    }

    int i;
    for (i = lista.quantidadeInserida - 1; i >= 0 && strcmp(novoAluno.nome, lista.vetorAlunos[i].nome) < 0; i--) {
        lista.vetorAlunos[i + 1] = lista.vetorAlunos[i];
    }

    lista.vetorAlunos[i + 1] = novoAluno;
    lista.quantidadeInserida++;
}




void lerArquivoCSV(const char* nomeArquivo) {
    int contador = 0;
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    char linha[300];
    
    printf("Iniciando insercao ordenada no vetor...\n");
    
    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho

    Aluno alunoLido; 
    
    while (fscanf(arquivo, "%8[^,],%14[^,],%49[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   alunoLido.matricula, alunoLido.cpf, alunoLido.nome, &alunoLido.nota, 
                   &alunoLido.idade, alunoLido.curso, alunoLido.cidade) == 7) {
        
        adicionarAluno(alunoLido);
        
        contador++;

        if (contador % 50000 == 0) {
            std::cout << contador << " registros processados para insercao...\n";
        }
    }
    
    fclose(arquivo);
    printf("\nLeitura e insercao finalizadas.\n");
}


int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    //.....
    time_t inicio, fim;
    inicio = clock();
    lerArquivoCSV("..\\alunos_completosV2.csv");
    fim = clock();
    printf("Tempo de leitura: %d milissegundos\n", (int)fim - inicio);
    printf("Total de alunos inseridos no vetor: %d\n", lista.quantidadeInserida);
    system("pause");
    return 0;

}

