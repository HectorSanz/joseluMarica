#ifndef lib_H
#define lib_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>

//--------------------Definicion de estructuras del enunciado------------------------//
typedef struct
{
    int f, c;     // filas y columnas
    double **m;   // doble puntero a la memoria de la matriz
} TMatriz;


typedef struct variable
{
char nomVar[16];
TMatriz *mat;
struct variable *sig, *ant;
} TVar;


typedef struct
{
int numVars;
TVar *primera;
} TVars;

//-------------------------Funciones de la practica----------------------------------//

//EJemplo
void hola();
void presentacion(); // HELP COMAND
void cambiarColor(int color);
char* MiStrTok(char *cad1, char *sep, int parentesis);
int validarParentesis(char *cadena);
int validarMatriz(char * cadena, int* filas ,int* elementosPorFila);
TMatriz *crearMatriz(int filas, int columnas);
void mostrarMatriz(TMatriz* matriz);

// NUEVA CLASE
void llenarMatrizDesdeCadena(TMatriz* matriz, char *cadena);
TMatriz* crearAux(char **cadena, TVar *LaGranVariable);
TMatriz* operaciones(char **cadena, TVar *LaGranVariable , int num_arg);

//CLASE
TVar *crearVariable(char *nombreVariable, TMatriz *matriz);
TVar *insertaUltimaVariable(TVar *LagranVariable, TVar *variableAsignar);
TVar *buscarVariable(TVar *laGranVariable, char *nombreVariable);
void imprimirTVar(TVar *LaGranLista);
int matrizOvariable(char *cad);
int validarNombre(char *nomVar);
void laGranVista(TVar *laGranVariable);
int contarCaracteres(char **cadena, char *caracter);
TMatriz* sumarMatrices(TMatriz *matrizA, TMatriz *matrizB);
TMatriz* restarMatrices(TMatriz *matrizA, TMatriz *matrizB);
TMatriz* multiplicarMatrices(TMatriz* matrizA, TMatriz* matrizB);
// TODO ESTO SOLO PARA EL DETERMINANTE DE UNA MATRIZ
double determinanteGauss(TMatriz *matriz);
TMatriz* copiarMatriz(TMatriz *matriz);
void triangularMatriz(TMatriz *matriz);
double determinanteTriangular(TMatriz *matriz);
//
TMatriz* liberarMatriz(TMatriz *matriz);
int decimalValidar(char *cad);
TMatriz* productoMatrizPorNumero(char **cadena, TMatriz *matriz);
TVars *crearWorkspace(TVars *workspace);
TVar *liberarVariables(TVar *laGranVariable);
void save(char *nombre, TVars *workspace);
int contadorVariables(TVar *LaGranVariable);
void Trim(char *cad);
TVars *load(char *nombre, TVars *workspace, int sobrescribir);
double productoEscalar(TMatriz *matriz1, TMatriz *matriz2);
TMatriz *transponerMatriz(TMatriz *matriz);
TMatriz* unirMatrices(TMatriz *matrizA, TMatriz *matrizB);


#endif