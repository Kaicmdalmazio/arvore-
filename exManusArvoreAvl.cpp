#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <algorithm> // Para std::max

//Exemplo do arquivo CSV que será lido
//Matricula,CPF,Nome,Nota,Idade,Curso,Cidade
//A0000000,915.216.859-08,Wallace Sampaio,20.35,23,Direito,Rio de Janeiro


struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    //atributos da estrutura arvore
    Aluno* esq;
    Aluno* dir;
    int altura;
};


struct Alunos{
    Aluno *raiz;
    int quantidade;
    //int tamanhoAtual; // Não é necessário se 'quantidade' já representa o tamanho
};

Alunos a;

// Função auxiliar para obter a altura de um nó
int getAltura(Aluno *no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Função auxiliar para obter o maior de dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

void inicializa(){
    a.raiz = NULL;
    a.quantidade = 0;
}

void atualizaAltura(Aluno *no){
    if (no != NULL) {
        no->altura = 1 + max(getAltura(no->esq), getAltura(no->dir));
    }
}

Aluno* rotacaoSimplesDireita(Aluno *y) {
    Aluno *x = y->esq;
    Aluno *T2 = x->dir;

    // Executa a rotação
    x->dir = y;
    y->esq = T2;

    // Atualiza alturas
    atualizaAltura(y);
    atualizaAltura(x);

    // Novo nó raiz
    return x;
}

Aluno* rotacaoSimplesEsquerda(Aluno *x) {
    Aluno *y = x->dir;
    Aluno *T2 = y->esq;

    // Executa a rotação
    y->esq  = x;
    x->dir = T2;

    // Atualiza alturas
    atualizaAltura(x);
    atualizaAltura(y);

    // Novo nó raiz
    return y;
}

Aluno* rotacaoDuplaDireita(Aluno *z) { //Esquerda-Direita
    // Primeiro uma rotação simples à esquerda em z->esq
    z->esq = rotacaoSimplesEsquerda(z->esq);
    // Depois rotação simples à direita em z
    return rotacaoSimplesDireita(z);
}

Aluno* rotacaoDuplaEsquerda(Aluno *z) { //Direita-Esquerda
    // Primeiro uma rotação simples à direita em z->dir
    z->dir = rotacaoSimplesDireita(z->dir);
    // Depois rotação simples à esquerda em z
    return rotacaoSimplesEsquerda(z);
}

// Função para calcular o fator de balanceamento de um nó
int getBalanceamento(Aluno *no) {
    if (no == NULL)
        return 0;
    return getAltura(no->esq) - getAltura(no->dir);
}

// A função de adicionar aluno na arvore já faz o balancemanento e retorna o novo nó se mudou o mo mesmo nó se nao teve mudança
Aluno* adicionarAluno(Aluno *no, Aluno *novoAluno){
    if(no == NULL)
        return novoAluno;

    // Comparação de ordenação baseada na matrícula
    if(strcmp(novoAluno->matricula, no->matricula) < 0){
        no->esq = adicionarAluno(no->esq, novoAluno);
    }
    else if (strcmp(novoAluno->matricula, no->matricula) > 0){
        no->dir = adicionarAluno(no->dir, novoAluno);
    }
    else { // Matrícula já existe, não adiciona duplicados
        return no;
    }

    atualizaAltura(no);

    int balanceamento = getBalanceamento(no);

    // Aplica rotações conforme o caso
    // Caso Esquerda-Esquerda (LL)
    if(balanceamento > 1 && strcmp(novoAluno->matricula, no->esq->matricula) < 0) {
        return rotacaoSimplesDireita(no);
    }
    // Caso Direita-Direita (RR)
    if(balanceamento < -1 && strcmp(novoAluno->matricula, no->dir->matricula) > 0) {
        return rotacaoSimplesEsquerda(no);
    }
    // Caso Esquerda-Direita (LR)
    if(balanceamento > 1 && strcmp(novoAluno->matricula, no->esq->matricula) > 0) {
        return rotacaoDuplaDireita(no);
    }
    // Caso Direita-Esquerda (RL)
    if(balanceamento < -1 && strcmp(novoAluno->matricula, no->dir->matricula) < 0) {
        return rotacaoDuplaEsquerda(no);
    }

    // Retorna nó (já possivelmente rotacionado)
    return no;
}

// Função para ler arquivo CSV
void lerArquivoCSV(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    char linha[300];
    
    printf("Iniciando leitura do arquivo CSV...\n");
    
    // Pular a primeira linha (cabeçalho)
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        printf("Arquivo vazio ou erro na leitura\n");
        fclose(arquivo);
        return;
    }
    // Ler cada linha usando fscanf diretamente na struct
    Aluno* novo;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) { // Ler linha por linha
        novo = new Aluno; // Alocar novo Aluno para cada linha
        if (novo == NULL) {
            printf("Erro de alocação de memória!\n");
            break;
        }
        // Inicializar altura do novo nó
        novo->altura = 1;
        novo->esq = NULL;
        novo->dir = NULL;

        // Usar sscanf para parsear a linha lida
        if (sscanf(linha, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
            
            a.raiz = adicionarAluno(a.raiz, novo);
            a.quantidade++;
            //printf("Aluno adicionado: %s - %s\n", novo->matricula, novo->nome);
        } else {
            printf("Erro ao ler linha: %s\n", linha);
            delete novo; // Liberar memória se a leitura falhar
        }
    }
    
    fclose(arquivo);
    printf("Leitura concluida. Total de alunos: %d\n", a.quantidade);
}

// Função para exibir alunos em ordem (percurso em-ordem)
void exibirAlunosEmOrdem(Aluno* no) {
    if (no != NULL) {
        exibirAlunosEmOrdem(no->esq);
        printf("  Matricula: %s\n", no->matricula);
        printf("  CPF: %s\n", no->cpf);
        printf("  Nome: %s\n", no->nome);
        printf("  Nota: %.2f\n", no->nota);
        printf("  Idade: %d\n", no->idade);
        printf("  Curso: %s\n", no->curso);
        printf("  Cidade: %s\n", no->cidade);
        printf("  ---\n");
        exibirAlunosEmOrdem(no->dir);
    }
}

// Função para exibir todos os alunos
void exibirAlunos() {
    printf("\n=== LISTA DE ALUNOS ===\n");
    if (a.raiz == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    exibirAlunosEmOrdem(a.raiz);
    printf("Total: %d alunos\n\n", a.quantidade);
}


int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    //.....
    time_t inicio, fim;
    inicio = clock();
    // Ler arquivo CSV (você pode alterar o nome do arquivo) Essa função já cria a lista dinâmica com os alunos
    lerArquivoCSV("..//alunos_completosV2.csv");
    fim = clock();
    //se eu quiser pegar como inteiro o valor do tempo

    printf("Tempo de leitura: %d milissegundos\n", (int)fim - inicio);

    exibirAlunos(); // Adicionado para exibir os alunos após a leitura

    //system("pause"); // Comentado para compatibilidade com sistemas Linux
    return 0;
}