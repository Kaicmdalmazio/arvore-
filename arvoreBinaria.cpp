/*Utilizando a estrutura que já fizemos de leitura de alunos e o que foi visto na disciplina de estrutura de dados faça:
-Implemente uma estrutura de árvore binária ordenada
-Utilize o nome do aluno para fazer a ordenação.
-Na estrutura principal (onde tem a raiz) guarde o nível da árvore. Imprima no final o tempo gasto para inserir todos os alunos, e também a altura da árvore (nível máximo).
-Faça a função de buscar o aluno por Nome.*/


#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
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

//temp e tamanho para poder calcular o tamanho da arvore vi o vendra falando 

Alunos a; // variavel global que é usada para pegar as informações da struct


void inicializa(){
    a.raiz = NULL;
    a.temp = 0;
    a.tamanho = 0;    
}



Aluno* adicionarAluno(Aluno *raiz, Aluno *novo) {
    novo->esquerda = NULL;
    novo->direita = NULL;
    
    if (raiz == NULL){
        raiz = novo;
        a.temp++;
        if(a.temp > a.tamanho){
            a.tamanho = a.temp;
        }
    } else {
        a.temp++;
        if (strcmp(novo->nome, raiz->nome) >= 0){
            raiz->direita = adicionarAluno(raiz->direita, novo);
        } else {
            raiz->esquerda = adicionarAluno(raiz->esquerda, novo);
        }
    }

    return raiz;
}




void lerArquivoCSV(const char* nomeArquivo) {
    int contador = 0;
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    char linha[300];
    
    printf("Iniciando leitura do arquivo CSV...\n");
    
    //Tirando a primeira linha
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        printf("Arquivo vazio ou erro na leitura\n");
        fclose(arquivo);
        return;
    }

    
    while (!feof(arquivo)) {
        Aluno* novo = new Aluno;
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {

            a.temp = 0;
            a.raiz = adicionarAluno(a.raiz, novo);
            contador++;

            // Mostrar a cada 50 mil registros
            if (contador % 50000 == 0) {
                std::cout << contador << " registros lidos...\n";
            }

        } else {
            printf("Erro ao ler linha: %s\n", linha);
            delete novo;
            continue;
        }
    }
    
    fclose(arquivo);
}

//breve explicação 
//Esta função receberá a raiz da árvore e o nome a ser buscado. Ela retornará um ponteiro para o Aluno encontrado ou NULL se não encontrar.

Aluno *buscar(Aluno *raiz, const char* nome){
    int comparando;

    // 1. CONDIÇÃO DE PARADA (CASO BASE):
    // Se o nó atual é NULL, significa que chegamos ao fim de um galho
    // e não encontramos o aluno. Retornamos NULL para sinalizar isso.
    //acho que n precisa pq ela nesse caso nunca vai ta vazia mas vou deixar ela ai 
    if(raiz == NULL){
        return NULL;
    }
    
    // 2. COMPARAÇÃO:
    // Comparamos o nome buscado com o nome do NÓ ATUAL (raiz->nome).
    comparando = strcmp(nome, raiz->nome); //aqui eutou comparando se o nome que estou buscando é igual o nome do nó atual

     // 3. DECISÃO:
    if (comparando == 0) {
        // Encontramos! O nome é igual ao do nó atual.
        return raiz;  // Retorna o ponteiro para o nó encontrado.
    } else if (comparando > 0) {
        // O nome buscado é "maior" (vem depois na ordem alfabética).
        // Portanto, ele só pode estar na sub-árvore da DIREITA.
        return buscar(raiz->direita, nome);
    } else {
        // O nome buscado é "menor".
        // Portanto, ele só pode estar na sub-árvore da ESQUERDA.
        return buscar(raiz->esquerda, nome);
    }
}


void buscarNome(){
    char nomeBusca[50];
    printf("\n--- Busca de Aluno por Nome ---\n");
    printf("Digite o nome do aluno a ser buscado: ");

    // Limpa o buffer de entrada antes de ler a string
    // Isso evita que um "Enter" anterior atrapalhe a leitura
    fflush(stdin); 

    // Lê o nome com espaços
    fgets(nomeBusca, 50, stdin);

    // Remove o '\n' do final, se houver 
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    printf("Buscando por '%s'...\n", nomeBusca);

    // Chama a função de busca começando pela raiz da árvore
    Aluno* encontrado = buscar(a.raiz, nomeBusca);


    if (encontrado != NULL) {
        printf("\n=== Aluno Encontrado! ===\n");
        printf("Matricula: %s\n", encontrado->matricula);
        printf("Nome: %s\n", encontrado->nome);
        printf("CPF: %s\n", encontrado->cpf);
        printf("Curso: %s\n", encontrado->curso);
        printf("Nota: %.2f\n", encontrado->nota);
        printf("Idade: %d\n", encontrado->idade);
        printf("Cidade: %s\n", encontrado->cidade);
        printf("=========================\n");
    } else {
        printf("\nAluno com o nome '%s' nao foi encontrado na arvore.\n", nomeBusca);
    }
}


int main(){
     inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    //.....
    time_t inicio, fim;
    inicio = clock();
    // Ler arquivo CSV (você pode alterar o nome do arquivo) Essa função já cria a lista dinâmica com os alunos
    lerArquivoCSV("..\\alunos_completosV2.csv");
    fim = clock();
    //se eu quiser pegar como inteiro o valor do tempo

    printf("Tempo de leitura: %d milissegundos\n", (int)fim - inicio);
    printf("Tamanho da arvore %d\n", a.tamanho);
    printf("Buscando pelo nome\n");
    buscarNome();
    system("pause");
    return 0;

}
