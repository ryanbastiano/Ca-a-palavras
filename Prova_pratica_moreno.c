#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxpal 114
#define tam 25

FILE *f;
int qpal = 0;
char palavras[maxpal][20];
char palavrasorteada[20];
char pal[tam][tam];

int abreArquivo();
void leArquivo();
void mostraPalavras();
void sorteia();
void inserePalavra();
void mostra();
int buscaPalavra(char *palavra);

//---
int main()
{
   srand(time(NULL));

   if (abreArquivo() == 0)
      return 0;

   leArquivo();
   printf("");
   //mostraPalavras();
   strcpy(palavrasorteada, palavras[rand() % maxpal]);
   printf("Palavra sorteada do arquivo: %s \n", palavrasorteada);

   sorteia();
   inserePalavra();
   printf("Matriz de caracteres gerada aleatoriamente: \n");
   mostra();

   char palavra[tam];
   printf("Digite uma palavra para buscar na matriz: ");
   scanf("%s", palavra);

   if (buscaPalavra(palavra))
      printf("A palavra %s foi encontrada na matriz.\n", palavra);
  
   else
      printf("A palavra %s nao foi encontrada na matriz.\n", palavra);

   return 1;
}

//----
int abreArquivo()
{
   f = fopen("..\\palavras.txt", "r"); // leitura
   if (f == NULL)
   { // erro na leitura do arquivo
      printf("Problemas na leitura do arquivo\n");
      system("pause");
      return 0; // não abriu o arquivo
   }
   else
   {
      fclose(f);
      return 1; //  abriu o arquivo
   }
}

//---
void leArquivo()
{
   f = fopen("..\\palavras.txt", "r"); // leitura
   qpal = 0;
   while (!feof(f))
   {
      printf("%i\n", qpal);
      // fgets(string,tamanho,arquivo)
      fgets(palavras[qpal], 20, f);
      palavras[qpal][strlen(palavras[qpal]) - 1] = '\0';
      qpal++;
   }
   fclose(f);
}

//---
void mostraPalavras()
{
   for (int x = 0; x < qpal; x++)
   {
      printf("%s\n", palavras[x]);
   }
}

//----
void sorteia()
{
   char vog[6] = "AEIOU";
   char con[22] = "BCDFGHJKLMNPQRSTVXWYZ";
   int cont = 1;
   // A=65 Z=90
   for (int x = 0; x < tam; x++)
      for (int y = 0; y < tam; y++)
      {
         if (cont == 1 || cont == 3)
         {
            pal[x][y] = vog[rand() % 5];
         }
         else
         {
            pal[x][y] = con[rand() % 21];
         }
         cont++;
         if (cont > 3)
         {
            cont = 1;
         }
      }
}

//----
void inserePalavra()
{
   int tamPalavra = strlen(palavrasorteada);
   int linhaInicial = rand() % (tam - tamPalavra + 1);
   int colunaInicial = rand() % (tam - tamPalavra + 1);
   // inserindo a palavra na horizontal ou vertical aleatoriamente
   int direcao = rand() % 2;
   if (direcao == 0) // horizontal
   {
      for (int i = 0; i < tamPalavra; i++)
      {
         pal[linhaInicial][colunaInicial + i] = palavrasorteada[i];
      }
   }
   else // vertical
   {
      for (int i = 0; i < tamPalavra; i++)
      {
         pal[linhaInicial + i][colunaInicial] = palavrasorteada[i];
      }
   }
}

//-------
void mostra()
{
   for (int x = 0; x < tam; x++)
   {
      for (int y = 0; y < tam; y++)
      {
         printf("%c ", pal[x][y]);
      }
      printf("\n");
   }
}

//----
int buscaPalavra(char *palavra)
{
   int tamPalavra = strlen(palavra);
   for (int x = 0; x < tam; x++)
   {
      for (int y = 0; y < tam; y++)
      {
         if (pal[x][y] == palavra[0])
         {
            // busca na horizontal
            int encontrou = 1;
            for (int i = 1; i < tamPalavra; i++)
            {
               if (y + i >= tam || pal[x][y + i] != palavra[i])
               {
                  encontrou = 0;
                  break;
               }
            }
            if (encontrou)
               return 1;
            // busca na vertical
            encontrou = 1;
            for (int i = 1; i < tamPalavra; i++)
            {
               if (x + i >= tam || pal[x + i][y] != palavra[i])
               {
                  encontrou = 0;
                  break;
               }
            }
            if (encontrou)
               return 1;
         }
      }
   }
   return 0;
}