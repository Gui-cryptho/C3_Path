# 🌲 Trabalho 2 – Árvores

Este repositório contém a implementação do **Trabalho Prático 2** da disciplina **Algoritmos e Estrutura de Dados III**, da Universidade Tecnológica Federal do Paraná (UTFPR).  
O objetivo é criar um programa em **C** capaz de manipular diretórios e arquivos utilizando **árvores genéricas**.

---

## 🎯 Objetivo

Desenvolver uma árvore genérica de diretórios para simular uma linha de comando.  
O programa deve ler um arquivo `in.txt` contendo uma lista de pastas e arquivos e montar uma árvore para armazenar essas informações.  
Deve ser possível navegar pelos diretórios através da árvore.

---

## 📂 Escopo

O arquivo `in.txt` segue a sintaxe:

Arquivos e Programas/Firefox  
Arquivos e Programas/Chrome  
Arquivos e Programas/Opera  
Meus Documentos/apresentacao.ppt  
Meus Documentos/relatorio.doc  
Meus Documentos/fontes  
Meus Documentos/fontes/main.c  
Meus Documentos/fontes/main.h  
Meus Documentos/imagens  
Meus Downloads/7zip.exe  
Meus Downloads/t2.rar  

- O caractere `/` separa diretórios.  
- Arquivos sempre possuem extensão (`.doc`, `.c`, `.ppt`, etc).  



## 💻 Comandos Implementados

O programa oferece uma interface de linha de comando com os seguintes comandos:

- `cd <diretório>` → entra no diretório especificado (ou sugere alternativas se não existir).  
- `search <arg>` → busca um arquivo ou pasta pelo nome e informa sua localização.  
- `rm <diretório>` → remove uma pasta e seus arquivos (liberação recursiva).  
- `list` → lista todos os componentes dentro da pasta atual.  
- `mkdir <arg>` → cria uma nova pasta na pasta atual.  
- `clear` → limpa o conteúdo da tela.  
- `help` → exibe a relação completa dos comandos e suas finalidades.  
- `exit` → encerra o programa liberando o espaço alocado.  

---

## 📑 Estrutura do Projeto

O trabalho deve conter três arquivos principais:

- `matriz.h` → Estrutura e declaração das funções.  
- `matriz.c` → Implementação das funções.  
- `main.c` → Função principal que chama os métodos implementados.  

Além disso, deve ser entregue um **documento explicativo** descrevendo o funcionamento dos métodos e os desafios enfrentados.

---

## ✅ Requisitos

- Ler o arquivo `in.txt` com a lista de pastas e arquivos.  
- Implementar todos os comandos especificados.  
- Liberar corretamente a memória alocada.  
- Criar documentação explicativa do trabalho.  

---

## 📊 Avaliação

- Atendimento aos requisitos especificados.  
- Correção das funções e organização dos arquivos.  
- Documento explicativo com resumo dos desafios.  
- Pontos extras para funcionalidades adicionais (novos comandos, uso de arquivos, interface, etc).  

---

## ✍️ Autor

**Guilherme Brito**  
Disciplina: *Algoritmos e Estrutura de Dados III*  
Professor: *Thiago França Naves*  
UTFPR - Campus Santa Helena
