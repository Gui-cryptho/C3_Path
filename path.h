#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

// ============================================================
//  DEFINIÇÕES DE TIPOS
// ============================================================
#define TIPO_PASTA  0
#define TIPO_ARQUIVO 1

// ============================================================
//  ESTRUTURAS
// ============================================================

// Estrutura do Nó da Árvore
typedef struct NO {
    char nome[100];          // Nome da pasta ou arquivo
    int tipo;                // TIPO_PASTA ou TIPO_ARQUIVO
    struct NO *filho;        // Primeiro filho
    struct NO *irmao;        // Próximo irmão
} NO;

// Estrutura da Árvore Principal
typedef struct {
    NO *raiz;                // Ponteiro para a raiz "/"
} Arvore;



// ============================================================
//  FASE 1 — CRIAÇÃO E LIBERAÇÃO DA ÁRVORE
// ============================================================

// Criar árvore com raiz "/"
Arvore* cria_Arvore();

// Criar nó individual
NO* cria_NO(const char* nome, int tipo);

// Liberar nó recursivamente
void libera_NO(NO* no);

// Liberar toda a árvore
void libera_Arvore(Arvore* arv);



// ============================================================
//  FASE 2 — CARREGAR ARQUIVO in.txt E MONTAR A ÁRVORE
// ============================================================

// Criar "in.txt" com dados padrão, caso não exista
void criar_arquivo_in_txt();

// Ler arquivo e montar os diretórios/arquivos
void carregar_arquivo(Arvore* arv, const char* nomeArquivo);

// Inserir caminho completo (ex.: "Meus Documentos/fontes/main.c")
void inserir_caminho(Arvore* arv, const char* caminho);

// Inserir um filho (arquivo ou pasta) no nó pai
NO* inserir_filho(NO* pai, const char* nome, int tipo);

// Encontrar filho com nome exato
NO* encontrar_filho(NO* pai, const char* nome);



// ============================================================
//  FASE 3 — COMANDOS DA INTERFACE
// ============================================================

// list — listar conteúdo da pasta atual
void listar(NO* atual);

// mkdir — criar diretório dentro da pasta atual
void mkdir(NO* atual, const char* nome);

// cd — entrar em um diretório
NO* cd(NO* atual, const char* nome);

// Sugerir nomes parecidos quando cd falhar
void sugerir(NO* atual, const char* prefixo);

// search — busca recursiva por nome
void search(NO* atual, const char* nome, char* caminho);

// rm — remove diretório ou arquivo recursivamente
int rm(NO* pai, const char* nome);

// clear — limpar tela
void clear();

// help — mostrar lista de comandos
void help();

#endif // PATH_H_INCLUDED
