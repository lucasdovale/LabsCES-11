#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main( )
{
   char   s [51];    // string
   int    i,
          k,
          n,         // quantidade de strings
          tam,       // tamanho de cada string
          cart;      // numero carteado
   FILE * sai;       // arquivo de saida

   // ler quantidade
   printf ("Quantos elementos? ");
   scanf  ("%d", & n);
   // abre arquivo e escreve quantidade
   sai = fopen ("StringsAleatorias.txt", "w");
   fprintf (sai, "%d\n", n);
   // inicializa o gerador de numeros aleatorios
   time_t t;
   srand((unsigned) time(&t));
   // gera  n  strings
   for(i=0; i<n; i++)
   {
      // sorteia o tamanho entre 10 e 50
      tam = 10 + rand () % 41;
      // primeiro caractere e' uma letra
      cart = rand () % 26;
      s[0] = 'a' + cart;
      // demais caracteres: letras ou espaco
      for (k=1; k<tam; k++)
      {
         cart = rand () % 27;
         // se sortear 26, escreve espaco. De 0 a 25 sao letras
         if (cart == 26)
              s[k] = ' ';
         else s[k] = 'a' + cart;
      }
      // marca fim de string e escreve
      s[tam] = '\0';
      fprintf (sai, "%s\n", s);
   }
   fclose (sai);
   system ("pause");
   return 0;
}
