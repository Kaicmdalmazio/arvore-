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

void adicionarAluno(){

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
    while ((novo = new Aluno) != NULL) {
        //%N significa que fará a leitura de até N caracteres, evitando overflow
        //O [^caractere] é uma classe de caracteres negativa - significa "qualquer caractere EXCETO o especificado".
        //É muito útil para parar a leitura quando encontrar um delimitador específico (como vírgula ou quebra de linha).
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
            
            // Inicializar ponteiros da lista
            novo->direita= NULL;
            novo->esquerda = NULL;

            adicionarAluno(novo);
            //printf("Aluno adicionado: %s - %s\n", novo->matricula, novo->nome);
            // Consumir a quebra de linha restante
            //fgetc(arquivo);
        } else {
            // Se não conseguiu ler todos os campos, liberar memória e sair
            delete novo;
            break;
        }
    }
    
    fclose(arquivo);
    printf("Leitura concluida. Total de alunos: %d\n", a.quantidade);
}


int main(){
    inicializa();
    printf("------Sistema de leitura de alunos-------");

    time_t inicio, fim;
    inicio = time(NULL);
    // Ler arquivo CSV (você pode alterar o nome do arquivo) Essa função já cria a lista dinâmica com os alunos
    lerArquivoCSV("alunos_completosV2");
    fim = time(NULL);
    //se eu quiser pegar como inteiro o valor do tempo
    // time_t tempo;
    // tempo = fim - inicio;
    // printf("Tempo de leitura: %d segundos\n", (int)tempo);
    //se eu quiser pegar como double o valor do tempo
    double tempo = difftime(fim, inicio);
    printf("Tempo de leitura: %.2f segundos\n", tempo);
    // Exibir todos os alunos carregados
    //exibirAlunos();
    
    system("pause");
    
}