/**
 * Implemente aqui as funções dos sistema de arquivos que simula EXT3
 */

#include "fs.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

using namespace std;

/**
 * @brief Inicializa um sistema de arquivos que simula EXT3
 * @param fsFileName nome do arquivo que contém sistema de arquivos que simula EXT3 (caminho do arquivo no sistema de arquivos local)
 * @param blockSize tamanho em bytes do bloco
 * @param numBlocks quantidade de blocos
 * @param numInodes quantidade de inodes
 */
void initFs(std::string fsFileName, int blockSize, int numBlocks, int numInodes){

    std::fstream file{fsFileName, std::ios::out | std::ios::trunc};
    if(!file.is_open()){
        cout<<"erro ao abrir"<<endl;
    }

    int tamMapaBits=ceil(numBlocks/8.0);
    char mapaBits[tamMapaBits]{};
    mapaBits[0]=0x01;

    INODE slash{};
    slash.IS_DIR=0x01;
    slash.IS_USED=0x01;
    slash.NAME[0]='/';

    file.write((const char *) &blockSize, 1);
    file.write((const char *) &numBlocks, 1);
    file.write((const char *) &numInodes, 1);
    file.write((const char *) mapaBits, tamMapaBits);
    file.write((const char *) &slash, sizeof(INODE));

    const char zero{0x00};

    int tam=(numInodes-1)*sizeof(INODE)+1+blockSize*numBlocks;

    for(int i=0;i<tam;i++)
        file.write(&zero,1);


    file.close();

}

/**
 * @brief Adiciona um novo arquivo dentro do sistema de arquivos que simula EXT3. O sistema já deve ter sido inicializado.
 * @param fsFileName arquivo que contém um sistema sistema de arquivos que simula EXT3.
 * @param filePath caminho completo novo arquivo dentro sistema de arquivos que simula EXT3.
 * @param fileContent conteúdo do novo arquivo
 */
void addFile(std::string fsFileName, std::string filePath, std::string fileContent){};

/**
 * @brief Adiciona um novo diretório dentro do sistema de arquivos que simula EXT3. O sistema já deve ter sido inicializado.
 * @param fsFileName arquivo que contém um sistema sistema de arquivos que simula EXT3.
 * @param dirPath caminho completo novo diretório dentro sistema de arquivos que simula EXT3.
 */
void addDir(std::string fsFileName, std::string dirPath){};

/**
 * @brief Remove um arquivo ou diretório (recursivamente) de um sistema de arquivos que simula EXT3. O sistema já deve ter sido inicializado.
 * @param fsFileName arquivo que contém um sistema sistema de arquivos que simula EXT3.
 * @param path caminho completo do arquivo ou diretório a ser removido.
 */
void remove(std::string fsFileName, std::string path){};

/**
 * @brief Move um arquivo ou diretório em um sistema de arquivos que simula EXT3. O sistema já deve ter sido inicializado.
 * @param fsFileName arquivo que contém um sistema sistema de arquivos que simula EXT3.
 * @param oldPath caminho completo do arquivo ou diretório a ser movido.
 * @param newPath novo caminho completo do arquivo ou diretório.
 */
void move(std::string fsFileName, std::string oldPath, std::string newPath){};