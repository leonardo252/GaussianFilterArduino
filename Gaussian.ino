/**
Apresentação Geral do Algoritmo: Filtro Gaussiano - Algotitmo de suavização em imagens pgm.
* O Algoritmo de Filtro Gaussiano é comumente aplicado em obter, através de uma imagem que carregam informações numéricas de 0 até 255, de forma a suavisar os pixels a partir de da aplicação de uma matrtiz da função de Gauss, com o objetivo de gerar uma imagem "Borrada".
*
* Estratégia do Algoritmo: Realizar a multiplicação da matriz gaussiana com  os pixels da imagem em questao
*
*
* Copyright 2021 por Leonardo Gomes e Rennan Rebouças
* Instituto Federal de Educação, Ciéncia e Tecnologia do Ceara. - IFCE
* Todos os Direitos Reservados.
*
*
*
* Modo de uso da aplicação:
* Realizar a entrada da matriz da imagem e sera externado na serial. Imprimindo os pixels na serial 

* Entradas e Saídas: Uma imagem de extensão pgm, com valores entre 0 e 255. Saída sera o valor de cada pixel sendo necessario só colar em um arquivo .pgm
*
* Validação e Testes: Comparação entre a imagem de entrada e saida
*
* Estudantes:
* Leonardo Gomes Fernandes e Rennan Rebouças Melo
*
* Data:
* 3 de Dezembro de 2021.
*
* Contexto:
* Desenvolvimento de código exclusivo para fins acadêmicos.
*
* Plataforma alvo:
* Arduino
*
*/

/*
* Includes para bibliotecas externas
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <EEPROM.h>

/* Variaveis que contem o tamanho da imagem */
const uint8_t numLines = 37;
const uint8_t numCollums = 45;

/* Struct que Representa uma imagem */
typedef struct image_t
{
    uint8_t buf[numLines][numCollums];
    uint8_t ncols;
    uint8_t nrows; 
} image_t;


/* Vetor que contem a imagem */
const static uint8_t imagePixels[] PROGMEM = {49,49,49,50,50,50,51,51,51,52,52,52,52,52,52,53,52,54,57,32,28,77,82,53
,25,51,60,57,58,57,57,57,57,57,56,56,56,58,57,56,57,57,57,57,56
,49,49,50,50,50,50,54,58,58,58,55,52,53,53,53,53,56,60,28,92,172,197,187,166
,125,56,49,64,58,59,59,58,57,58,57,57,57,58,57,57,58,58,57,57,57
,49,49,50,50,51,56,47,18,0,25,52,59,53,55,54,55,64,25,95,188,201,184,183,186
,196,157,41,55,66,57,58,58,57,58,58,58,58,59,58,58,57,57,59,58,58
,50,50,50,51,56,34,25,95,108,87,11,43,60,54,54,63,49,44,164,194,170,172,168,166
,182,188,111,16,68,60,59,61,62,61,60,59,59,58,58,58,58,59,60,59,60
,50,51,51,57,35,67,159,193,198,195,150,50,50,60,55,65,35,88,177,196,192,186,178,170
,172,185,140,31,59,67,66,62,58,61,66,62,59,60,59,60,61,60,60,60,61
,52,51,56,46,47,162,208,190,183,196,208,151,0,67,56,64,37,95,171,186,190,195,191,177
,171,187,140,29,63,67,23,24,40,16,22,62,64,60,60,61,61,61,61,62,62
,52,53,59,9,110,188,186,193,183,178,189,185,71,42,67,66,42,84,172,182,178,189,190,185
,189,181,110,42,66,45,105,142,160,155,111,42,59,64,61,62,62,62,62,62,61
,52,54,56,23,127,182,187,204,200,195,191,179,97,27,71,60,55,38,144,185,178,178,180,191
,191,143,60,64,44,129,193,191,190,203,194,129,46,64,64,62,63,63,62,61,62
,54,55,60,24,109,182,184,192,205,196,200,169,64,52,59,59,75,59,51,128,161,168,167,164
,132,62,64,48,101,192,204,187,174,175,190,180,105,45,65,62,62,61,62,63,64
,56,55,60,53,66,154,186,185,188,196,188,117,23,67,87,106,105,116,102,40,73,96,97,77
,43,65,66,52,153,196,197,191,183,176,182,185,142,52,71,73,70,69,64,63,64
,57,58,65,60,18,52,123,147,151,150,106,33,60,98,125,126,124,114,136,122,42,48,50,55
,66,75,51,77,167,181,191,198,190,192,192,188,155,70,38,30,34,55,70,66,64
,59,62,30,50,96,101,86,62,46,42,38,59,77,119,132,141,148,142,136,142,87,58,74,70
,70,77,53,85,167,180,178,203,204,187,179,198,159,0,78,116,107,64,30,67,66
,61,43,93,155,180,190,193,177,111,41,71,56,95,123,130,141,140,150,159,148,91,50,72,67
,51,49,42,34,152,189,179,192,207,203,199,193,109,139,217,234,216,186,116,40,67
,48,74,191,214,190,209,212,201,191,108,35,58,100,132,114,142,139,131,147,143,82,58,68,44
,79,110,117,83,81,159,186,184,192,205,193,127,133,241,236,220,223,231,215,94,48
,42,143,202,213,212,202,191,175,197,167,43,53,82,142,127,127,140,119,132,115,61,64,60,117
,166,183,181,180,143,86,119,137,134,135,98,34,203,230,194,204,214,207,219,149,25
,67,167,182,187,199,187,190,196,193,178,72,59,64,101,136,120,117,120,106,69,67,50,124,182
,187,185,179,176,187,145,26,43,63,50,43,80,206,220,221,232,219,200,203,150,38
,78,168,180,177,168,181,191,195,193,169,66,63,54,14,65,84,78,88,65,68,60,79,169,187
,166,169,169,162,171,172,112,55,72,78,79,62,193,231,222,204,211,232,209,113,50
,60,165,181,201,195,184,185,185,190,145,37,53,86,120,119,113,80,25,67,79,44,108,170,167
,167,174,177,185,183,178,130,58,71,73,73,49,138,200,214,220,227,226,156,54,67
,41,122,179,192,205,195,205,195,163,85,41,120,163,167,167,167,163,118,51,75,56,106,168,183
,183,183,188,183,175,184,133,47,68,72,72,70,55,115,162,183,179,135,60,64,71
,60,50,118,152,185,188,170,145,88,32,110,168,175,175,175,163,175,178,102,54,65,86,170,190
,167,171,183,169,177,176,108,49,73,68,71,76,73,45,49,62,53,36,67,73,68
,64,62,39,74,99,104,78,48,46,75,153,173,176,186,186,182,171,184,152,52,68,64,132,168
,164,169,174,176,180,135,61,66,73,86,83,72,84,88,71,66,68,78,75,68,70
,60,66,67,55,41,38,55,70,64,89,162,171,179,187,187,189,181,183,163,72,63,70,65,118
,152,162,165,157,126,70,62,73,80,34,0,57,39,59,86,78,78,73,71,71,71
,62,62,65,69,71,72,72,74,58,91,159,178,181,182,178,170,176,186,156,67,62,76,66,58
,81,98,98,81,55,65,75,77,35,113,164,153,139,90,44,78,71,71,72,72,72
,62,63,63,64,65,67,67,71,62,77,158,176,181,171,174,177,174,174,128,48,72,72,73,72
,61,57,57,61,72,72,82,36,134,221,206,192,202,197,115,45,79,72,73,73,72
,63,64,64,65,65,66,68,70,70,56,122,168,166,178,181,182,180,144,76,68,74,70,71,72
,74,76,77,78,72,80,66,79,208,228,206,209,215,228,193,66,66,78,73,72,72
,64,65,65,66,66,67,68,69,71,68,63,115,143,161,169,159,128,61,41,69,76,73,70,71
,71,73,73,74,72,85,40,132,218,216,214,225,230,230,208,110,46,79,72,72,72
,64,64,65,67,68,68,69,72,72,73,69,60,76,86,91,64,52,93,101,73,49,70,74,71
,72,72,74,74,74,86,23,149,214,214,223,235,223,223,197,101,52,77,72,71,72
,65,65,67,69,69,70,70,71,72,72,74,73,69,66,50,105,160,190,192,174,127,57,70,74
,72,73,74,75,72,88,40,121,211,222,225,239,218,211,165,60,70,74,72,72,71
,65,66,67,69,70,70,70,71,72,72,72,74,77,60,125,185,180,180,193,197,198,138,50,75
,74,73,75,75,73,75,80,51,151,203,202,207,208,176,93,59,77,71,71,72,72
,66,66,68,70,70,71,71,71,72,72,72,76,58,97,172,189,183,176,169,196,212,185,104,53
,79,72,75,74,75,74,77,75,53,107,147,144,124,79,60,75,72,72,71,71,73
,67,67,69,70,71,72,72,72,72,72,73,74,53,134,187,180,189,193,181,181,202,196,140,45
,78,74,74,74,74,75,73,77,78,58,51,54,50,66,77,72,71,72,71,71,71
,67,68,70,71,72,73,72,72,72,72,75,71,63,141,182,179,197,199,192,180,181,191,143,52
,76,76,74,75,74,75,75,74,77,81,77,77,79,78,73,72,71,71,71,71,71
,69,70,71,73,74,73,73,72,73,73,75,73,58,141,182,173,198,194,190,194,174,172,125,47
,81,74,75,75,76,75,75,75,74,74,76,76,74,73,73,73,72,71,72,72,72
,69,70,72,73,74,74,74,74,74,74,74,78,56,109,178,172,165,172,184,189,175,142,77,66
,78,74,75,75,75,76,75,74,75,74,75,74,74,73,73,73,72,72,72,72,71
,70,71,72,73,74,74,74,74,75,73,73,76,74,61,123,167,163,168,173,169,145,87,63,78
,73,75,75,74,75,76,76,76,75,75,75,74,74,73,73,73,72,72,72,71,72
,70,70,71,72,74,75,74,74,74,74,73,74,76,74,64,93,126,138,135,112,74,67,77,74
,74,74,74,74,76,76,76,76,75,75,74,73,73,73,73,73,73,72,72,72,71
,70,70,71,72,73,74,74,74,74,74,73,73,74,75,76,67,64,67,64,64,71,76,74,74
,74,75,74,75,76,76,75,76,75,76,75,73,73,73,73,72,72,72,72,72,71
};


/* Variavel que armazena a imagem */
image_t img;

/* Função responsavel por carregar a estrutura imagem */
void image_load(image_t *image )
{
  int colun = 0;
  int line  = 0;
  int index = 0;
  int address = 0;
  int totalValues = numLines * numCollums;

  while( index < totalValues ) {

//      int value = EEPROM.read(address);
//      image->buf[line][colun] = value;
      image->buf[line][colun] = imagePixels[index];
      address += sizeof(uint8_t);
      index++;
      colun++;
      if (colun >= numCollums) {
        colun = 0;
        line++;
      }
      delay(5);
  }
}


/**
 *@brief Garante que o pixel se mantenha na area da imagem
 *@param Entrada é uma variavel do tipo image_t, o numero de linhas e colunas
 *@return void
 */
uint8_t image_read_pixel( image_t * img, int col, int row )
{
    /* Nao permite leitura fora das fronteiras da imagem original */
    if( col >= img->ncols ) col = img->ncols - 1;
    if( row >= img->nrows ) row = img->nrows - 1;
    if( col < 0 ) col = 0;
    if( row < 0 ) row = 0;
    return img->buf[row][col];
}

/**
 *@brief Aplica o filtro Gaussiano na imagem carregada.
 *@param Entrada é uma variavel do tipo image_t
 *@return void
 */
void image_gaussian_smooth_filter(image_t * img )
{
    int x, y, col, row;
    float newPixel;
    int pixel;
    int sumPixel = 0;
    int sumKernel;

    int kernel3[3][3] = {{ 2,  4,  2},
                        { 4,  9, 4},
                        { 2,  4,  2}};
                        
    /* Percorre os pixels da imagem */
    for( row = 0; row < numLines; row++ )
    {
        for( col = 0; col < numCollums; col++ )
        {
            sumKernel = 0;
            sumPixel = 0;

            /* Percorre o Kernel da matriz Gaussiana e trata os pixels */
            for( y = 0; y < 3; y++ )
            {
                for( x = 0; x < 3; x++ )
                {
                    pixel = image_read_pixel( img,  col + (x - 1), row + (y - 1) );
                    
                    sumPixel += ( pixel *  kernel3[x][y] );
                    sumKernel += kernel3[x][y];
                }
            }


            /* Externa o valor de cada pixel */
            newPixel = sumPixel / sumKernel;
//            Serial.print(" ");
//            Serial.print(int(newPixel));
            
        }
//        Serial.print("\n");
    }
}


void setup() {

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
//  img.ncols = numCollums;
//  img.nrows = numLines;
}

void loop() {
  Serial.println("Starting Program");

  image_load(&img);
  int col, row;
//  for( row = 0; row < numLines; row++ ){
//        for( col = 0; col < numCollums; col++ ){
//          Serial.print(img.buf[row][col]);
//          Serial.print(" ");
//          delay(2);
//        }
//        Serial.print("\n");
//  }
  unsigned long start = micros();
  image_gaussian_smooth_filter(&img);
  unsigned long end = micros();
  unsigned long delta = end - start;
  
  
  Serial.println("Program Finished\n");
  Serial.print("Tempo de execução: ");
  Serial.println(delta);
  while(true) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);  
    delay(1000);
  };
}
