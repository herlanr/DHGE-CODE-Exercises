//NULL überprufen : fopen, malloc
//EOF uberprufen: fgetc, fgets, fclose, fread

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

// Nome do programa (argv[0]), utilizado para exibir mensagens de erro
const char *progName;

// Função para exibir mensagens de erro e encerrar o programa
void errMsg(const char *operation, const char *fileName);

void errMsg(const char *operation, const char *fileName)
{
  // Exibe uma mensagem de erro com detalhes da operação e o nome do arquivo
  fprintf(stderr, "%s: error %s %s: %s\n",
          progName, operation, fileName, strerror(errno));
  exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[])
{
  FILE *inFile, *outFile;
  const char *inFileName, *outFileName;

  // Guarda o nome do programa para exibição em erros
  progName = argv[0];
  
  // Verifica se o número de argumentos está correto
  if (argc != 3) {
    fprintf(stderr, "Uso: %s infile outfile\n", progName);
    exit(EXIT_FAILURE);
  }
  
  // Abre o arquivo de entrada para leitura
  inFileName = argv[1];
  if ((inFile = fopen(inFileName, "r")) == NULL) {
    errMsg("abrindo para leitura", inFileName);
  }
  
  // Abre o arquivo de saída para escrita
  outFileName = argv[2];
  if ((outFile = fopen(outFileName, "w")) == NULL) {
    errMsg("abrindo para escrita", outFileName);
  }

  int c; // Caractere atual lido do arquivo
  int len = 0;   // Contador de espaços consecutivos
  int max = 0;   // Maior número de espaços consecutivos encontrados
  int del = 0;   // Contador de espaços removidos

  // Lê o arquivo caractere por caractere
  while ((c = fgetc(inFile)) != EOF) {
    if (isspace(c)) { // Se for um espaço ou caractere de espaço
      if (len == 0) { // Se for o primeiro espaço após um texto, escreve no arquivo
        if (fputc(c, outFile) == EOF) {
          errMsg("escrevendo", outFileName);
        }
      } else { // Se for um segundo ou mais espaços consecutivos, ignora
        ++del;
      }
      ++len; // Incrementa o contador de espaços consecutivos
      if (len > max) { // Atualiza o maior número de espaços consecutivos
        max = len;
      }
    } else { // Se for um caractere normal (não espaço)
      if (fputc(c, outFile) == EOF) {
        errMsg("escrevendo", outFileName);
      }
      len = 0; // Reinicia o contador de espaços consecutivos
    }
  }

  // Se o arquivo terminou com espaços, atualiza o máximo
  if (len > max) {
    max = len;
  }

  // Verifica se houve erro na leitura do arquivo
  if (ferror(inFile)) {
    errMsg("lendo", inFileName);
  }
  
  // Fecha o arquivo de entrada
  if (fclose(inFile) == EOF) {
    errMsg("fechando", inFileName);
  }
  
  // Fecha o arquivo de saída
  if (fclose(outFile) == EOF) {
    errMsg("fechando", outFileName);
  }

  // Exibe o número total de caracteres removidos e o maior número de espaços consecutivos
  fprintf(stderr, "%s: %d caracteres removidos, maior sequência %d\n",
          inFileName, del, max - 1);
  
  exit(EXIT_SUCCESS);
}
