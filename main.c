#include <stdio.h>
#include "Funciones.h"
#include <stdlib.h>


int fila; 
char columna;
char mat[3][3];
char movida;
char* jugador;
char usuarios[10][15];
int puntajes[10];
char str1[2];

void casilla()
{ printf("Ingrese casilla %s\n", jugador);
scanf("%s", str1);
char str2[]={str1[0]};
char str3[]={str1[1]};
sscanf(str2," %d", &fila);
sscanf(str3," %c", &columna);
if((fila==0||fila==1||fila==2)&&(columna=='a'||columna=='b'||columna=='c'))
{if (mat[fila][letra(columna)] == ' ')
  {mat[fila][letra(columna)] = movida;
  system("cls");
  imprimir_matriz(mat);}  
 else
  {printf("\nCasilla ocupada, elija otra\n");
  casilla();}
  }
else
{printf("\nCaracter invalido\n");
casilla();}
}


int main() 
{FILE *pExtra = fopen("extra.txt", "r+");
  int tres;
  fscanf(pExtra, "%d", &tres);
  int cuatro;
  fseek(pExtra, 2, SEEK_SET);
  fscanf(pExtra, "%d", &cuatro);
  int cinco;
  fseek(pExtra, 4, SEEK_SET);
  fscanf(pExtra, "%d", &cinco);
  int ultimo_valor; //este es para tener un valor de referencia de cuál fue la última casilla llenada y que las puntuaciones se impriman en orden de más nuevo a más antigua
  fseek(pExtra, 6, SEEK_SET);
  fscanf(pExtra, "%d", &ultimo_valor);
  
char jug1[15];
char jug2[15];  

array_puntos(puntajes);
array_usuarios(usuarios);
printf("%d",minval(puntajes));
int opt;
printf("\nMenú Principal. Elija una opción:");
printf("\n1-Empezar el juego");
printf("\n2-Ver 10 últimas puntuaciones");
printf("\nCualquier otra tecla-Salir\n");
scanf("%d",&opt);
switch (opt)
{case 1:
printf("\nIngrese nombre jugador 1\n");
  scanf("%s",jug1);
  printf("\nIngrese nombre jugador 2\n");
  scanf("%s",jug2);

  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      mat[i][j] = ' ';}
  }
  
  imprimir_matriz(mat);
 
  int contadorG = 0; //[0,8] sólo se puede hacer 9 movimientos en el juego del gato

  while(contadorG<9)
  {//designa  quién es el jugador en determinado momento, con su respectivo símbolo
    if (contadorG % 2 == 0)
    {
      jugador = jug1;
      movida = 'x';
    }
    else
    {
      jugador = jug2;
      movida = 'o';
    }
    casilla();

    if (
  //filas x
      (mat[0][0]=='x' && mat[0][1]=='x' && mat[0][2]=='x')||(mat[1][0]=='x' && mat[1][1]=='x' && mat[1][2]=='x')||(mat[2][0]=='x' && mat[2][1]=='x' && mat[2][2]=='x')
  //filas o
    ||(mat[0][0]=='o' && mat[0][1]=='o' && mat[0][2]=='o')||(mat[1][0]=='o' && mat[1][1]=='o' && mat[1][2]=='o')||(mat[2][0]=='o' && mat[2][1]=='o' && mat[2][2]=='o')||
  //columnas x  
    (mat[0][0]=='x' && mat[1][0]=='x' && mat[2][0]=='x')||(mat[0][1]=='x' && mat[1][1]=='x' && mat[2][1]=='x')||(mat[0][2]=='x' && mat[1][2]=='x' && mat[2][2]=='x')||
  //columnas o 
    (mat[0][0]=='o' && mat[1][0]=='o' && mat[2][0]=='o')||(mat[0][1]=='o' && mat[1][1]=='o' && mat[2][1]=='o')||(mat[0][2]=='o' && mat[1][2]=='o' && mat[2][2]=='o')
  //diagonal °125  x
  || (mat[0][0]=='x'&& mat[1][1]=='x'&& mat[2][2]=='x') 
  // diagonal °45  x
  || (mat[0][2]=='x'&& mat[1][1]=='x'&& mat[2][0]=='x')
  //diagonal °125  o
  || (mat[0][0]=='o'&& mat[1][1]=='o'&& mat[2][2]=='o') 
  // diagonal °45  o
  || (mat[0][2]=='o'&& mat[1][1]=='o'&& mat[2][0]=='o')
    )
      {
      printf("\nFin del juego, gana %s", jugador);
      break;
      }
    contadorG++;
  }
  

  int size = sizeof(mat)/sizeof(mat[0][0]);
  int mov_x =0;
  int mov_o =0;  
  int mov_gana;
  for (int i=0; i<size;i++)
  {//cantidad de movimientos del ganador
    if (*(mat[0]+i)=='x')
    {mov_x++;}
    else if (*(mat[0]+i)=='o')
    {mov_o++;}
    }

  if (jugador == jug1)
    {mov_gana = mov_x;}
  else if (jugador == jug2)
    {mov_gana = mov_o;}
  printf(" con %d movimientos\n",  mov_gana);

//actualización de arrays
if (mov_gana==3)
  {for (int i=9; (i>=0); i--)
    {//verifica primero si se pueden reemplazar valores mayores a 3 mientras no hayan 0s, o si existen 0s
    if ((puntajes[i]==5 && maxval(puntajes)==5 && minval(puntajes)!=0)||(puntajes[i]==4 && maxval(puntajes)==4 && minval(puntajes)!= 0)||(puntajes[i]==0))
     {ultimo_valor =i;
      puntajes[i]=mov_gana;
        sscanf(jugador, "%s", usuarios+i);
        break;}
    //los dos else if siguientes se encargan de reemplazar vlores en los arrays si las puntuaciones sólo están compuestas de 3, reemplazando el primer 3 introducido
     else if (i==tres && puntajes[tres]==3 && puntajes[tres-1]==3 && tres!= 0 && minval(puntajes)!=0 && maxval(puntajes)==3)
       {ultimo_valor = i ;
         puntajes[tres]=mov_gana;
        sscanf(jugador, "%s", usuarios+tres);
        tres--;
        fseek(pExtra, 0, SEEK_SET);
        fprintf(pExtra,"%d\n",tres);
        break;}
    else if (i==tres && tres== 0 && puntajes[tres]==3 && puntajes[9]==3 && minval(puntajes)!=0 && maxval(puntajes)==3)
       {ultimo_valor = i;
        puntajes[tres]=mov_gana;
        sscanf(jugador, "%s", usuarios+tres);
        tres=9;
        fseek(pExtra, 0, SEEK_SET);
        fprintf(pExtra,"%d\n",tres);
        break;}
      }   
  }
  if (mov_gana==4)
  {for (int i=9; (i>=0); i--)
    {//verifica primero si se pueden reemplazar valores mayores a 4 mientras no hayan 0s, o si existen 0s
    if ((puntajes[i]==5 && maxval(puntajes)==5&& minval(puntajes)!=0)||(puntajes[i]==0)) 
        {ultimo_valor =i;
          puntajes[i]=mov_gana;
          sscanf(jugador, "%s",usuarios+i);
          break;}
    //los dos else if siguientes se encargan de reemplazar vlores en los arrays si las puntuaciones sólo están compuestas de 4, reemplazando el primer 4 introducido
    else if (i== cuatro && puntajes[cuatro]==4 && puntajes[cuatro-1]==4 && cinco!= 0 && minval(puntajes)!=0 && maxval(puntajes)==4)
       {ultimo_valor =i;
        puntajes[cuatro]=mov_gana;
        sscanf(jugador, "%s", usuarios+cuatro);
        cuatro--;
        fseek(pExtra, 2, SEEK_SET);
        fprintf(pExtra,"%d\n",cuatro);
        break;}
    else if (i== cuatro && cuatro== 0 && puntajes[cuatro]==4 && puntajes[9]==4 && minval(puntajes)!=0 && maxval(puntajes)==4)
       {ultimo_valor =i;
        puntajes[cuatro]=mov_gana;
        sscanf(jugador, "%s", usuarios+cuatro);
        cuatro=9;
        fseek(pExtra, 2, SEEK_SET);
        fprintf(pExtra,"%d\n",cuatro);
        break;}
      }  
  }

  if (mov_gana==5)
  {for (int i=9; (i>=0); i--)
    {//verifica si hay 0s
    if (puntajes[i]==0)
      {ultimo_valor =i;
        puntajes[i]=mov_gana;
      sscanf(jugador, "%s", usuarios+i);
      break;}
    //los dos else if siguientes se encargan de reemplazar vlores en los arrays si las puntuaciones sólo están compuestas de 5, reemplazando el primer 5 introducido
    else if (i== cinco && puntajes[cinco]==5 && puntajes[cinco-1]==5 && cinco!= 0 && minval(puntajes)!=0 && maxval(puntajes)==5)
       {ultimo_valor =i;
         puntajes[cinco]=mov_gana;
        sscanf(jugador, "%s", usuarios+cinco);
        cinco--;
        fseek(pExtra, 4, SEEK_SET);
        fprintf(pExtra,"%d\n",cinco);
        break;}
    else if (i== cinco && cinco== 0 && puntajes[cinco]==5 && puntajes[9]==5 && minval(puntajes)!=0 && maxval(puntajes)==5)
       {ultimo_valor = i;
        puntajes[cinco]=mov_gana;
        sscanf(jugador, "%s", usuarios+cinco);
        cinco=9;
        fseek(pExtra, 4, SEEK_SET);
        fprintf(pExtra,"%d\n",cinco);
        break;}
      }
  }
 
fseek(pExtra, 6, SEEK_SET);
fprintf(pExtra,"%d\n",ultimo_valor);
fclose(pExtra);
 //actualizamos los archivos de usuarios y puntajes
  incluir_puntos(puntajes);
  incluir(usuarios);
 //nos cercioramos de que se imprimirán bien e imprimimos
  array_puntos(puntajes);
  array_usuarios(usuarios);
  imprimir_todo(puntajes,usuarios,ultimo_valor);

break;

case 2:
imprimir_todo(puntajes,usuarios,ultimo_valor);
break;

default:
printf("Juego terminado");
break;
}

return 0;
}

