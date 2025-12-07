#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"

int main() {

    // ================================
    // Inicialização da Árvore
    // ================================
    criar_arquivo_in_txt();          // cria in.txt caso não exista

    Arvore* arv = cria_Arvore();     // cria árvore com raiz "/"
    carregar_arquivo(arv, "in.txt"); // carrega o sistema de arquivos

    NO* atual = arv->raiz;           // diretório onde o usuário está

    char comando[100];

    printf("=======================================\n");
    printf("   SISTEMA DE ARQUIVOS & ARVORE        \n");
    printf("=======================================\n");
    printf("Digite 'help' para ver os comandos.\n\n");

    while (1) {

        printf("%s> ", atual->nome);   // prompt com nome da pasta atual

        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = 0;  // remover \n

        if (strlen(comando) == 0)
            continue;

        // Pegar o comando (primeira palavra)
        char *cmd = strtok(comando, " ");

        // ================================
        // Comando: exit
        // ================================
        if (strcmp(cmd, "exit") == 0) {
            printf("Encerrando programa...\n");
            break;
        }

        // ================================
        // Comando: help
        // ================================
        else if (strcmp(cmd, "help") == 0) {
            help();
        }

        // ================================
        // Comando: clear
        // ================================
        else if (strcmp(cmd, "clear") == 0) {
            clear();
        }

        // ================================
        // Comando: list
        // ================================
        else if (strcmp(cmd, "list") == 0) {
            listar(atual);
        }

        // ================================
        // Comando: mkdir <nome>
        // ================================
        else if (strcmp(cmd, "mkdir") == 0) {

            // Obtém tudo após "mkdir"
            char *resto = comando + 6;
            while (*resto == ' ') resto++;

            if (strlen(resto) == 0)
                printf("Uso: mkdir <nome>\n");
            else
                mkdir(atual, resto);
        }

        // ================================
        // Comando: cd <nome> (com suporte a espaços)
        // ================================
        else if (strcmp(cmd, "cd") == 0) {

            // Pega tudo após "cd"
            char *resto = comando + 3;
            while (*resto == ' ') resto++;

            if (strlen(resto) == 0) {
                printf("Uso: cd <diretorio>\n");
                continue;
            }

            // cd ..
            if (strcmp(resto, "..") == 0) {

                if (atual == arv->raiz) {
                    printf("Voce ja esta na raiz.\n");
                } else {

                    NO* fila[500];
                    int inicio = 0, fim = 0;

                    fila[fim++] = arv->raiz;

                    while (inicio < fim) {
                        NO* n = fila[inicio++];

                        NO* filho = n->filho;
                        while (filho != NULL) {
                            if (filho == atual) {
                                atual = n;
                                goto cd_fim;
                            }
                            fila[fim++] = filho;
                            filho = filho->irmao;
                        }
                    }
                }

                cd_fim:;
            }
            else {
                atual = cd(atual, resto);
            }
        }

        // ================================
        // Comando: rm <nome>
        // ================================
        else if (strcmp(cmd, "rm") == 0) {

            char *resto = comando + 3;
            while (*resto == ' ') resto++;

            if (strlen(resto) == 0)
                printf("Uso: rm <nome>\n");
            else if (rm(atual, resto))
                printf("'%s' removido com sucesso!\n", resto);
            else
                printf("Item '%s' nao encontrado.\n", resto);
        }

        // ================================
        // Comando: search <nome>
        // ================================
        else if (strcmp(cmd, "search") == 0) {

            char *resto = comando + 7;
            while (*resto == ' ') resto++;

            if (strlen(resto) == 0)
                printf("Uso: search <nome>\n");
            else {
                char base[10] = "";
                search(arv->raiz, resto, base);
            }
        }

        // ================================
        // Comando inválido
        // ================================
        else {
            printf("Comando '%s' nao reconhecido. Use 'help'.\n", cmd);
        }
    }

    libera_Arvore(arv);

    return 0;
}
