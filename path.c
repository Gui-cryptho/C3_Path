#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"

/* ============================================================
   FASE 1 — ESTRUTURA BÁSICA DA ÁRVORE
   ------------------------------------------------------------
   • cria_Arvore()
   • cria_NO()
   • libera_NO()
   • libera_Arvore()
   ============================================================ */

// -------------------------------
// 1.1 Criar Árvore (com raiz "/")
// -------------------------------
Arvore* cria_Arvore() {
    Arvore* arv = (Arvore*) malloc(sizeof(Arvore));
    if (arv != NULL)
        arv->raiz = cria_NO("/", TIPO_PASTA);
    return arv;
}

// -------------------------------
// 1.2 Criar Nó
// -------------------------------
NO* cria_NO(const char* nome, int tipo) {
    NO* novo = (NO*) malloc(sizeof(NO));
    if (novo == NULL)
        return NULL;

    strcpy(novo->nome, nome);
    novo->tipo = tipo;
    novo->filho = NULL;
    novo->irmao = NULL;

    return novo;
}

// -------------------------------
// 1.3 Liberar Nó (recursivo)
// -------------------------------
void libera_NO(NO* no) {
    if (no == NULL)
        return;

    NO* filho = no->filho;
    while (filho != NULL) {
        NO* proximo = filho->irmao;
        libera_NO(filho);
        filho = proximo;
    }

    free(no);
}

// -------------------------------
// 1.4 Liberar Árvore inteira
// -------------------------------
void libera_Arvore(Arvore* arv) {
    if (arv == NULL) return;

    libera_NO(arv->raiz);
    free(arv);
}


/* ============================================================
   FASE 2 — CARREGAR ARQUIVO E MONTAR ÁRVORE
   ------------------------------------------------------------
   • criar_arquivo_in_txt()
   • carregar_arquivo()
   • inserir_caminho()
   • inserir_filho()
   • encontrar_filho()
   ============================================================ */

// -------------------------------------------
// 2.1 Criar arquivo in.txt se não existir
// -------------------------------------------
void criar_arquivo_in_txt() {
    FILE *f = fopen("in.txt", "r");

    if (f != NULL) {
        printf("Arquivo in.txt ja existe. Nenhuma acao realizada.\n");
        fclose(f);
        return;
    }

    f = fopen("in.txt", "w");
    if (f == NULL) {
        printf("Erro ao criar arquivo in.txt!\n");
        return;
    }

    const char *conteudo =
        "Arquivos e Programas/Firefox\n"
        "Arquivos e Programas/Chrome\n"
        "Arquivos e Programas/Opera\n"
        "Meus Documentos/apresentacao.ppt\n"
        "Meus Documentos/relatorio.doc\n"
        "Meus Documentos/fontes\n"
        "Meus Documentos/fontes/main.c\n"
        "Meus Documentos/fontes/main.h\n"
        "Meus Documentos/imagens\n"
        "Meus Downloads/7zip.exe\n"
        "Meus Downloads/t2.rar\n";

    fputs(conteudo, f);
    fclose(f);

    printf("Arquivo in.txt criado com sucesso!\n");
}

// -------------------------------------------
// 2.2 Ler arquivo linha a linha
// -------------------------------------------
void carregar_arquivo(Arvore* arv, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char linha[300];

    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        if (strlen(linha) == 0) continue;

        inserir_caminho(arv, linha);
    }

    fclose(f);
}

// -------------------------------------------
// 2.3 Inserir caminho completo na árvore
// -------------------------------------------
void inserir_caminho(Arvore* arv, const char* caminho) {
    char temp[300];
    strcpy(temp, caminho);

    char* token = strtok(temp, "/");
    NO* atual = arv->raiz;

    while (token != NULL) {
        int tipo = strchr(token, '.') ? TIPO_ARQUIVO : TIPO_PASTA;
        atual = inserir_filho(atual, token, tipo);
        token = strtok(NULL, "/");
    }
}

// -------------------------------------------
// 2.4 Encontrar filho com nome específico
// -------------------------------------------
NO* encontrar_filho(NO* pai, const char* nome) {
    NO* atual = pai->filho;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0)
            return atual;
        atual = atual->irmao;
    }
    return NULL;
}

// -------------------------------------------
// 2.5 Inserir filho (se não existir)
// -------------------------------------------
NO* inserir_filho(NO* pai, const char* nome, int tipo) {
    NO* existente = encontrar_filho(pai, nome);
    if (existente != NULL)
        return existente;

    NO* novo = cria_NO(nome, tipo);

    if (pai->filho == NULL) {
        pai->filho = novo;
        return novo;
    }

    NO* aux = pai->filho;
    while (aux->irmao != NULL)
        aux = aux->irmao;

    aux->irmao = novo;

    return novo;
}


/* ============================================================
   FASE 3 — COMANDOS DA INTERFACE (cd, list, mkdir, rm, search…)
   ------------------------------------------------------------
   • list
   • mkdir
   • cd + sugestão
   • search
   • rm
   • clear
   • help
   ============================================================ */

// -------------------------------------------
// 3.1 list — listar conteúdo da pasta atual
// -------------------------------------------
void listar(NO* atual) {
    if (atual == NULL) return;

    NO* filho = atual->filho;

    while (filho != NULL) {
        printf("[%s] %s\n",
               filho->tipo == TIPO_PASTA ? "DIR" : "ARQ",
               filho->nome);
        filho = filho->irmao;
    }
}

// -------------------------------------------
// 3.2 mkdir — criar diretório
// -------------------------------------------
void mkdir(NO* atual, const char* nome) {
    inserir_filho(atual, nome, TIPO_PASTA);
}

// -------------------------------------------
// 3.3 cd — navegar entre pastas
// -------------------------------------------
void sugerir(NO* atual, const char* prefixo);

NO* cd(NO* atual, const char* nome) {
    NO* alvo = encontrar_filho(atual, nome);

    if (alvo != NULL && alvo->tipo == TIPO_PASTA)
        return alvo;

    printf("Diretório '%s' nao encontrado! Sugestoes:\n", nome);
    sugerir(atual, nome);

    return atual;
}

// -------------------------------------------
// 3.4 sugerir — mostrar nomes parecidos
// -------------------------------------------
void sugerir(NO* atual, const char* prefixo) {
    NO* filho = atual->filho;

    while (filho != NULL) {
        if (strncmp(filho->nome, prefixo, strlen(prefixo)) == 0)
            printf(" - %s\n", filho->nome);

        filho = filho->irmao;
    }
}

// -------------------------------------------
// 3.5 search — busca recursiva
// -------------------------------------------
void search(NO* atual, const char* nome, char* caminho) {
    if (atual == NULL) return;

    char novoCaminho[300];
    sprintf(novoCaminho, "%s/%s", caminho, atual->nome);

    if (strcmp(atual->nome, nome) == 0)
        printf("Encontrado em: %s\n", novoCaminho);

    NO* filho = atual->filho;
    while (filho != NULL) {
        search(filho, nome, novoCaminho);
        filho = filho->irmao;
    }
}

// -------------------------------------------
// 3.6 rm — remover diretório ou arquivo
// -------------------------------------------
int rm(NO* pai, const char* nome) {
    if (pai == NULL) return 0;

    NO* atual = pai->filho;
    NO* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL)
                pai->filho = atual->irmao;
            else
                anterior->irmao = atual->irmao;

            libera_NO(atual);
            return 1;
        }

        anterior = atual;
        atual = atual->irmao;
    }
    return 0;
}

// -------------------------------------------
// 3.7 clear — limpar tela
// -------------------------------------------
void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// -------------------------------------------
// 3.8 help — lista comandos
// -------------------------------------------
void help() {
    printf("Comandos disponiveis:\n");
    printf("cd <dir>    - entrar em diretorio\n");
    printf("list        - listar itens\n");
    printf("mkdir <dir> - criar pasta\n");
    printf("rm <dir>    - remover pasta\n");
    printf("search <x>  - buscar arquivo/pasta\n");
    printf("clear       - limpar tela\n");
    printf("help        - listar comandos\n");
    printf("exit        - sair do programa\n");
}
