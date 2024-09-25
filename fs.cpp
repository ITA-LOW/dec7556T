#ifndef fs_h
#define fs_h
#include <string>
#include "fs.h"
#include <iostream>
#include <fstream>
#include <cstring>

/**
 * @param arquivoDaLista nome do arquivo em disco que contem a lista encadeada
 * @param novoNome nome a ser adicionado apos depoisDesteNome
 * @param depoisDesteNome um nome presente na lista
 */

struct Nodo {
    int esta_na_lista;       // 1 para sim, 0 para não (4 bytes)
    char nome[20];           // Nome com até 20 caracteres (20 bytes)
    int proximo_nodo;        // Posição do próximo nodo (4 bytes)
};

void adiciona(std::string arquivoDaLista, std::string novoNome, std::string depoisDesteNome)
{
    //implemente aqui
    std::fstream file(arquivoDaLista, std::ios::in | std::ios::out | std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    int primeiro_nodo_pos;
    file.read((char*)(&primeiro_nodo_pos), sizeof(int));  // Ler posição do primeiro nodo
    
    Nodo nodo_atual;
    int pos_atual = primeiro_nodo_pos;
    int pos_nodo_Z = -1;

    // Percorrer a lista para encontrar o nodo com nome depoisDesteNome
    while (1) {
        file.seekg(pos_atual);
        file.read((char*)(&nodo_atual), sizeof(Nodo));

        if (std::string(nodo_atual.nome) == depoisDesteNome) {
            pos_nodo_Z = pos_atual;  // Encontramos o nodo Z
            break;
        }

        pos_atual = nodo_atual.proximo_nodo;
    }

    if (pos_nodo_Z == -1) {
        std::cerr << "Nodo com nome '" << depoisDesteNome << "' não encontrado." << std::endl;
        file.close();
        return;
    }

    // Procurar um bloco livre (onde esta_na_lista == 0)
    int pos_livre = -1;
    for (int i = 4; i < 284; i += sizeof(Nodo)) {  // Pular os primeiros 4 bytes (cabeçalho)
        file.seekg(i);
        file.read((char*)(&nodo_atual), sizeof(int));  // Ler se o nodo está na lista
        if (nodo_atual.esta_na_lista == 0) {  // Encontrou um bloco livre
            pos_livre = i;
            break;
        }
    }

    if (pos_livre == -1) {
        std::cerr << "Não há blocos livres disponíveis." << std::endl;
        file.close();
        return;
    }

    // Criar e preencher o novo nodo
    Nodo novo_nodo;
    novo_nodo.esta_na_lista = 1;
    std::strncpy(novo_nodo.nome, novoNome.c_str(), 20);
    novo_nodo.proximo_nodo = nodo_atual.proximo_nodo;  // O novo nodo apontará para o mesmo que Z

    // Escrever o novo nodo no bloco livre
    file.seekp(pos_livre);
    file.write((char*)(&novo_nodo), sizeof(Nodo));

    // Atualizar o nodo Z para apontar para o novo nodo
    file.seekp(pos_nodo_Z + 24);  // A posição 24 do nodo é onde está o ponteiro para o próximo nodo
    file.write((char*)(&pos_livre), sizeof(int));

    file.close();

}

#endif /* fs_h */