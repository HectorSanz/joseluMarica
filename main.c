#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "lib.h"

// Comando para compilar el main y las librerias en el cmd y crear el ejecutable main.exe
// gcc lib.c main.c -o main.exe

int main(int argc, char *argv[]) {

    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Variables:
    // Cadena de números con paréntesis y tuberías
    char comando[1000];
    // Suponemos un tamaño máximo para la matriz
    double matriz[10][10];
    // Variable para rastrear la fila actual en la matriz
    int fila = 0;
    // Variable para rastrear la columna actual en la matriz
    int columna = 0;

    char separadores[8] = " \t\n";

    // Puntero a la cadena de texto que introducimos
    char *comtok[1000]; 

    // Numero de argumentos en la cadena introducida la separcion son los espacios fuera de parentesis
    int num_arg; 

    // Inicializamos el workspace y LaGranVariable(donde estaran todas las variables)
    TVars *workspace = NULL;
    TVar *LaGranVariable = NULL;

    // Funciones de texto
    hola();
    presentacion();

    // Crear workspace
    workspace = crearWorkspace(workspace);

    while (1) {
        // Se tiene que modificar para mostrar el numero de variables almacenadas
        printf(":[%d]> ", workspace->numVars);

        // Uso de fgets para leer la entrada del usuario de manera segura, 
        if (fgets(comando, sizeof(comando), stdin) == NULL) {
            // Manejo del error o fin de archivo
            break;
        }

        //y se elimina el carácter de nueva línea (\n) que fgets agrega al final de la entrada si está presente. 
        comando[strcspn(comando, "\n")] = 0;

        // Comprobar que está entre paréntesis, sino lanzar ERROR
        if(validarParentesis(comando) == 0){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);
            continue;
        }

        // Inicializa el contador de argumentos en 0
        num_arg = 0;

        // Dividir la cadena comando en tokens según los separadores
        // El primer token se obtiene de la cadena comando
        comtok[num_arg] = MiStrTok(comando, separadores, 1);

        // Incrementa el contador de argumentos
        num_arg++;

        // Utiliza un bucle while para continuar dividiendo la cadena comando en tokens
        // MiStrTok con NULL como primer argumento continúa desde la última posición en la cadena
        // El bucle se detiene cuando no se encuentran más tokens (es decir, cuando MiStrTok devuelve NULL)
        // Incrementa el contador de argumentos con cada token encontrado
        while ((comtok[num_arg] = MiStrTok(NULL, separadores, 1)) != NULL){
            num_arg++;
        }
        // Si el primer token es NULL, continúa con la siguiente iteración del bucle principal
        // Esto maneja el caso en que el comando está vacío o no contiene tokens válidos
        if (comtok[0] == NULL)
        {
            continue;
        }
        
        // Logica para leer comandos basicos
        if (strcmp(comtok[0], "quit") == 0 && num_arg == 1) {
            // Liberar memoria de las variables
            LaGranVariable = liberarVariables(LaGranVariable);
            // Si el numero de variables es 0 liberar la primera poicion del workspace
            
            // Libera el workspace por complet
            if(workspace->numVars == 0){
                workspace->primera = liberarVariables(workspace->primera);
            }

            free(workspace);
            workspace = NULL;

            // Muestra mensaje exitoso de salida
            SetConsoleTextAttribute(hConsole, 2);
            printf("Exit ok\n");
            SetConsoleTextAttribute(hConsole, 7);
            return 0;

        } else if (strcmp(comtok[0], "view") == 0) {

            if (num_arg != 1 )
            {
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
            }

            laGranVista(LaGranVariable);

        } else if (strcmp(comtok[0], "det") == 0) {
            if (num_arg != 2 )
            {
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
            }

            TMatriz *matrizA = crearAux(&comtok[1],LaGranVariable);

            if (matrizA == NULL) 
            {
                // Manejo de errores si las variables no se encuentran
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: La variable no existe.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            } 

            if (matrizA->f != matrizA->c) {
                // Las matrices no son cuadradas
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Las matrices no son cuadradas.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            double det = determinanteGauss(matrizA);

            SetConsoleTextAttribute(hConsole, 2);
            printf("Determinante: %.2lf\n", det);
            SetConsoleTextAttribute(hConsole, 7);


        }else if (strcmp(comtok[0], "save") == 0) {

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Argumentos\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            
            if(contadorVariables(LaGranVariable) <= 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: No hay nada que guardar\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            workspace->numVars = contadorVariables(LaGranVariable);
            //printf("Numero de variables en el workspace: %d\n", workspace->numVars);
            workspace->primera = LaGranVariable;
            //imprimirTVAR(workspace->primera);

            save(comtok[1], workspace);

            //printf("Guardao\n");

        } else if (strcmp(comtok[0], "load") == 0) {

            TVars *nuevoWorkspace;

            if(num_arg == 1){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Falta el nombre del archivo\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            if(strcmp(comtok[1], "over") == 0){
                
                if(num_arg != 3){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR: Argumentos\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    continue;
                }

                nuevoWorkspace = load(comtok[2],workspace,0);
                
                if(nuevoWorkspace == NULL){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR: Al cargar el fichero\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    
                    continue;
                }
                else
                {
                    workspace = load(comtok[2],workspace,0);
                }

                LaGranVariable = workspace->primera;
            
            }else{
                
                if(num_arg != 2){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR: Argumentos exceso\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    continue;
                }

                nuevoWorkspace = load(comtok[1],workspace,1);
                
                if(nuevoWorkspace == NULL){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR: Al cargar el fichero\n");
                    SetConsoleTextAttribute(hConsole, 7);
                        
                    continue;
                }
                else
                {
                    workspace = load(comtok[1],workspace,1);
                }

                LaGranVariable = workspace->primera;
            }

        }else if(num_arg>=2 && strcmp(comtok[1], "$") == 0){
            
            if(num_arg != 3){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Argumentos\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TMatriz *matrizA = crearAux(&comtok[0],LaGranVariable);
            TMatriz *matrizB = crearAux(&comtok[2],LaGranVariable);

            if (matrizA == NULL || matrizB == NULL) 
            {
                // Manejo de errores si las variables no se encuentran
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: Una o ambas variables o matrices no existen.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            } 

            if (matrizA->f != 1 || matrizB->f != 1 || matrizA->c != matrizB->c) {
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: Las matrices deben ser de 1xN y tener el mismo número de columnas.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue; // Manejo de error, puedes ajustarlo según tus necesidades
            }

            double escalar = productoEscalar(matrizA,matrizB);

            SetConsoleTextAttribute(hConsole, 2);
            printf("Producto Escalar: %.2lf\n", escalar);
            SetConsoleTextAttribute(hConsole, 7);
        
        }else if (num_arg > 1 && strcmp(comtok[1], "=") == 0) {
            // Implementar lógica para asignación

            if(matrizOvariable(comtok[0]) != 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            if(validarNombre(comtok[0]) == 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TVar *variableDestino = buscarVariable(LaGranVariable, comtok[0]);

            int cortafuegos = 0;

            if(variableDestino == NULL){
                variableDestino = crearVariable(comtok[0], NULL);
                cortafuegos = 2;
            }

            TMatriz *matrizValor = operaciones(&comtok[2],LaGranVariable, num_arg-2);

            if (matrizValor == NULL)
            {
                continue;
            }

            variableDestino->mat = matrizValor;

            if (cortafuegos == 2)
            {
                LaGranVariable = insertaUltimaVariable(LaGranVariable, variableDestino);
            }
            

        }else {
            // Implementar lógica para operaciones y mostar matrices resultado
            TMatriz *verMatriz =  operaciones(comtok, LaGranVariable, num_arg);    
            if(verMatriz != NULL){
                SetConsoleTextAttribute(hConsole, 2);
                mostrarMatriz(verMatriz);
                SetConsoleTextAttribute(hConsole, 7);
                //liberarMatriz(verMatriz);
            }
            
        }

        // Actualizar workspace con las nuevas variables y su numero
        workspace->numVars = contadorVariables(LaGranVariable);
        workspace->primera = LaGranVariable;
    }
    return 0;
}
