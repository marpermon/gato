#include <stdio.h>
#include "Funciones.h"
#include <stdlib.h>

int letra (char k)
{
if (k == 'a')
  {return 0;
  }
if (k == 'b')
  {return 1;
  }
if (k == 'c')
  {return 2;
  }
}

void imprimir_matriz(char b[3][3])//imprime la matriz que se muestra
{
   printf("  a  b  c\n");
   for(int i=0;i<3;i++)
    {printf("%d", i);
  for(int j=0;j<3;j++)
    {printf("[%c]", b[i][j]);}
  printf("\n");
   }
}


int maxval(int arr[10])//despliega el máximo valor en las puntuaciones
{
   int max = *(arr);
   for (int i=0; (i<10); i++)
    {
       if(arr[i] > arr[0])
       {
           max = arr[i];
       }
    }
    return max;
}


int minval(int arr[10]) //despliega el mínimo valor en las puntuaciones
{
   int min = *(arr);
   for (int i=0; (i<10); i++)
    {
       if(arr[i] < arr[0])
       {
           min = arr[i];
       }
    }
    return min;
}

void array_usuarios(char B[10][15]) //llena el array de usuarios con lo que esté en el archivo de usuarios
{
    FILE *pArchivo = fopen("archivo externo.txt","r");
    fseek(pArchivo,-(10*15),SEEK_END);
    for (int i=0; (i<10); i++)
    {
      fscanf(pArchivo, "%s", (B+i));
    }
    fclose(pArchivo);
}

void incluir(char B[10][15])//actualiza el archivo de usuarios
{
    FILE *pArchivo = fopen("archivo externo.txt","w");
    for (int i=0; (i<10); i++)
    {
       fprintf(pArchivo,"%s\n", B+i);
    }
    fclose(pArchivo);
}

//puntajes

void array_puntos(int entero[10]) //llena el array de puntuaciones con lo que esté en el archivo de puntuaciones
{
    FILE *pPuntos = fopen("puntuaciones.txt","r");
    fseek(pPuntos,-(10*4),SEEK_END);
    for (int i=0; (i<10); i++)
    {
      fscanf(pPuntos, "%d", entero+i);
    }
    fclose(pPuntos);
}

void incluir_puntos(int entero[10])  //actualiza el archivo de puntuaciones
{
    FILE *pPuntos = fopen("puntuaciones.txt","w");
    for (int i=0; (i<10); i++)
    {
       fprintf(pPuntos,"%d\n", entero[i]);
    }
    fclose(pPuntos);
}


void imprimir_todo(int entero[10],char B[10][15], int control) //imprime los dos arreglos desde lo último introducido hasta lo más viejo, obteniendo su lugar  gracias a la variable control
{
    printf("\nUsuario-puntuaciones\n");
    for (int i=control; (i<10); i++)
    {
        if (entero[i]!=0)
        {printf("%d:%s-%d\n",i-control+1,B+i,*(entero+i));}
    }
    for (int i=0; (i<control); i++)
    {
        if (entero[i]!=0)
        {printf("%d:%s-%d\n",11+i-control,B+i,*(entero+i));}
    }
}
