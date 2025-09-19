//Exemplo da estrutura de arvore
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>

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
    int tamanhoAtual;
};

Alunos a;

void inicializa(){
    ////.....
    ;
}

void atualizaAltura(Aluno *no){
    ///.....
    ;
}

Aluno* rotacaoSimplesDireita(Aluno *x) {
    ;
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

Aluno* rotacaoDuplaEsquerda(Aluno *z) { //Direita-Esquerda
    // Primeiro uma rotação simples à direita em z->dir
    z->dir = rotacaoSimplesDireita(z->dir);
    // Depois rotação simples à esquerda em z
    return rotacaoSimplesEsquerda(z);
}


// A função de adicionar aluno na arvore já faz o balancemanento e retorna o novo nó se mudou o mo mesmo nó se nao teve mudança
Aluno* adicionarAluno(Aluno *no, Aluno *novoAluno){
    if(no == NULL)
        return no = novoAluno;

    if(/*faço a comparação de ordenação*/){
        no->dir = adicionarAluno(no->dir, novoAluno);
    }
    else{
        no->esq = adicionarAluno(no->esq, novoAluno);
    }

    atualizaAltura(no);

    int balanceamento = /*calculo o balanceamento*/0;


    //Como aplicar as rotações?
    //Aplica rotações conforme o caso
    if(balanceamento > 1 && /*condicao para rotação SimplesDireita*/0) {
        ///....
    }
    if(balanceamento < -1 && /*condição para rotação SimplesEsquerda*/0) {
        return rotacaoSimplesEsquerda(no);            // RR
    }
    if(balanceamento > 1 && /*condicao para rotação DuplaDireita*/0) {
        ///....
    }
    if(balanceamento < -1 && /*condição para rotação DuplaEsquerda*/0) {
        ///....
    }

    //Retorna nó (já possivelmente rotacionado)
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
    while ((novo = new Aluno) != NULL) {
        //%N significa que fará a leitura de até N caracteres, evitando overflow
        //O [^caractere] é uma classe de caracteres negativa - significa "qualquer caractere EXCETO o especificado".
        //É muito útil para parar a leitura quando encontrar um delimitador específico (como vírgula ou quebra de linha).
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
            
            // Inicializar ponteiros da lista
            novo->dir = NULL;
            novo->esq = NULL;
            //pega o endereço que deve ser inserido no vetor de alunos
            adicionarAluno(a.raiz,novo);
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
    printf("Leitura concluida. Total de alunos: %d\n", a[0].quantidade);
}

// Função para exibir todos os alunos
void exibirAlunos() {
    printf("\n=== LISTA DE ALUNOS ===\n");
    Aluno* atual = a[0].inicio;
    int contador = 1;
    
    while (atual != NULL) {
        printf("Aluno %d:\n", contador);
        printf("  Matricula: %s\n", atual->matricula);
        printf("  CPF: %s\n", atual->cpf);
        printf("  Nome: %s\n", atual->nome);
        printf("  Nota: %.2f\n", atual->nota);
        printf("  Idade: %d\n", atual->idade);
        printf("  Curso: %s\n", atual->curso);
        printf("  Cidade: %s\n", atual->cidade);
        printf("  ---\n");
        
        //..falta codigo..//
        contador++;
    }
    printf("Total: %d alunos\n\n", a.quantidade);
}


int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    //.....
    time_t inicio, fim;
    inicio = clock();
    // Ler arquivo CSV (você pode alterar o nome do arquivo) Essa função já cria a lista dinâmica com os alunos
    lerArquivoCSV("alunos_completosV2.csv");
    fim = clock();
    //se eu quiser pegar como inteiro o valor do tempo

    printf("Tempo de leitura: %d milissegundos\n", (int)fim - inicio);

    system("pause");
    return 0;
}