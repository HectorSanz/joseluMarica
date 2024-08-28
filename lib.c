#include "lib.h"
#include <ctype.h>

// Datos del ALumno
void hola(){ 
    printf("Alumno: Daniel Garcia Moreno\n");
    printf("Email: daniel.garcia34@goumh.umh.es\n");
    printf("DNI: 48733085H \n\n");
}

// Función para cambiar el color del texto en la consola
void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Presentación de comandos disponibles y ejercicos realizados
void presentacion() {
    cambiarColor(11);  // Amarillo brillante
    printf("=============================================================\n");
    printf("             Bienvenido al Sistema Mini-Mat \n");
    printf("=============================================================\n");
    cambiarColor(14);  // Blanco
    printf("Lista de ejercicios:\n");
    cambiarColor(2);  // Verde
    //printf("  - Ejercicio 1: HECHO\n");
    //printf("  - Ejercicio 2: HECHO\n");
    //printf("  - Ejercicio 3: HECHO\n");
    //printf("  - Ejercicio 4: HECHO\n");
    cambiarColor(11);  // Azul brillante
    printf("=============================================================\n\n");
    cambiarColor(15);  // Blanco
}

// Tokenizador
char* MiStrTok(char *cad1, char *sep, int parentesis){

    static char *pt1 = NULL;
    static char *pt2 = NULL;
    static char *ptFinal;

    if(cad1 != NULL){
        pt1 = cad1;
        ptFinal = pt1+strlen(cad1);
    }
    else{
        pt1 = pt2+1;
    }
    if(pt1>=ptFinal){
        pt1 = pt2 = ptFinal = NULL;
        return NULL;
    }
    if(parentesis == 1){ // corchetes activados
        
        while(pt1[0]!='\0' && pt1 < ptFinal && strchr(sep, pt1[0]) != NULL && pt1[0] != '('){
            pt1++;
        }

        if(pt1[0] == '('){
            pt1++;
            pt2 = pt1;
            while(pt2[0] != '\0' && pt2[0] != ')'){
                pt2++;
            }

            if(pt2[0] == '\0'){
                pt1 = pt2 = ptFinal = NULL;
                return NULL;
            }
            else{
                pt2[0] = '\0';
                return pt1; 
            }
        }

    }
    else{

        while(pt1[0]!='\0' && pt1 < ptFinal && strchr(sep, pt1[0]) != NULL){
            pt1++;
        }

    }
    
    if(pt1>=ptFinal){
        pt1 = pt2 = ptFinal = NULL;
        return NULL;
    }
    pt2 = pt1+1;

    while(pt2[0] != '\0' && strchr(sep, pt2[0]) == NULL){
        pt2++;
    }

    pt2[0] = '\0';
    return pt1;

}

// Valida que los corchetes esten bn escritos. BN 1, MAL 0
int validarParentesis(char * cadena){

    int i=0;
    int contador=0;
    int primeravez = 0;
    int corchetesApertura=0;
    int corchetesCierre=0;
    int orden = 0;

    while(cadena[i] != '\0'){
        if(cadena[i] == '(' || cadena[i] == ')'){
            contador++;
        }
        i++;
    }

    if(contador == 0){
        return 1;
    }

    i = 0;
    contador = 0;

    while(cadena[i] != '\0'){
        if(cadena[i] == '(' && contador == 0){  
            contador++;
            primeravez=1;
        }
        else if(cadena[i] == ')' && contador == 1){
            contador--;
        }

        if(cadena[i] == '('){
            corchetesApertura++;
            if(orden == 1){ // si entra dentro MAL
                return 0;
            }
            orden = 1;
        }
        else if(cadena[i] == ')'){
            corchetesCierre++;
            if(orden == 0){ // si entra dentro MAL
                return 0;
            }
            orden = 0;
        }

        i++;
    }

    if(contador == 0 && primeravez == 1 && corchetesApertura == corchetesCierre){ // Si se mete aqui bn
        return 1;
    }
    else{ // si se mete aqui mal
        return 0;
    }

}

// Valida que la matriz tenga los elemtos correctos / 0 MAL 1 BIEN
int validarMatriz(char * cadena, int* filas ,int* elementosPorFila){
    // Detecta si la entrada parece ser una matriz entre paréntesis
    *filas = 1; // Contador de filas
    int elementosFila = 0; // Contador de elementos en la fila
    *elementosPorFila = -1; // Almacena el número de elementos en la primera fila
    char *caracter = cadena;

    // Variable para indicar si estamos dentro de un número
        
    int dentroNumero = 0;

    // Recorre la cadena y cuenta los elementos en cada fila
    while (*caracter) {
        if (*caracter == ' ' || *caracter == '(' || *caracter == ')') {
            // Si estamos dentro de un número, incrementa elementosFila
            if (dentroNumero) {
            elementosFila++;
            dentroNumero = 0;
            }
        } else if (*caracter == '|') {
            // Si estamos dentro de un número, incrementa elementosFila antes de cambiar de fila
            if (dentroNumero) {
                elementosFila++;
                dentroNumero = 0;
            }
                    
        if (*elementosPorFila == -1) {
           *elementosPorFila = elementosFila; // Establece el número de elementos en la primera fila
        } else if (elementosFila != *elementosPorFila) {

            return 0;

        }

        elementosFila = 0; // Reinicia el contador de elementos
        (*filas)++;

        } else {
            // Estamos dentro de un número
            dentroNumero = 1;

            // Verifica que el caracter sea un dígito
            
            if (!isdigit(*caracter) && *caracter != '+' && *caracter != '-' && *caracter != '.') {
                //printf("Error: La matriz contiene caracteres no numéricos en la fila %d.\n", *filas);
                //printf("caracter mal: %c\n", *caracter);
                return 0;
            }
            
            
        }
        caracter++;
    }

    // Contabiliza el último elemento en la última fila
    if (dentroNumero) {
        elementosFila++;
    }

    if (*filas == 1) {
        // Si hay solo una fila, el número de elementos en esa fila es igual al total de elementos
        *elementosPorFila = elementosFila;
    }

    if (*elementosPorFila != -1 && elementosFila != *elementosPorFila) {
        return 0;
        
    } else {
       
    }

    //printf("Número de filas de la matriz: %d\n", *filas);
    //printf("Número de elementos en cada fila: %d\n", *elementosPorFila);

    return 1;
}

TMatriz *crearMatriz(int filas, int columnas){
    TMatriz *matriz = (TMatriz *)malloc(sizeof(TMatriz));
    matriz->f = filas;
    matriz->c = columnas;
    matriz->m = (double **)malloc(filas * sizeof(double));

    if (matriz->m == NULL){
        perror("Error al asignar memoria para la matriz");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < filas; i++){
        matriz->m[i] = (double *)malloc(columnas * sizeof(double));
        if (matriz->m[i] == NULL){
            perror("Error al asignar memoria para las filas de la matriz");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            matriz->m[i][j] = 0.0;
        }
    }

    return matriz;
}

void mostrarMatriz(TMatriz* matriz){

    for (int i = 0; i <  matriz->f; i++){
        for (int j = 0; j <  matriz->c; j++){
            printf("%.2f ", matriz->m[i][j]);
        }
        printf("\n");
    }
    
}

void llenarMatrizDesdeCadena(TMatriz* matriz, char *cadena){
    int fila = 0;
    int columna = 0;

    char *token = strtok(cadena," ");

    while (token != NULL){
        char *ptr = token;
        while (*ptr) {
            if (*ptr == '(' || *ptr == ')' || *ptr == '|') {
                memmove(ptr, ptr + 1, strlen(ptr));
            } else {
                ptr++;
            }
        }

        if (strlen(token) > 0){
            double numero = atof(token);
            matriz->m[fila][columna] = numero;
            columna++;
        }
        
        token = strtok(NULL, " ");

        if (token != NULL && *token == '|'){
            fila++;
            columna = 0;
            token = strtok(NULL, " ");
        }
    }
}

TMatriz* crearAux(char **cadena, TVar *LaGranVariable){
    int filas, columnas;

    TVar *variableAux = buscarVariable(LaGranVariable, cadena[0]);

    if( variableAux != NULL){
        return variableAux->mat;
    }
    else{
        if(validarMatriz(cadena[0], &filas, &columnas) == 1 && matrizOvariable(cadena[0]) == 2){
            TMatriz *matrizAux = crearMatriz(filas, columnas);
            llenarMatrizDesdeCadena(matrizAux, cadena[0]);
            return matrizAux;
        }
    }

    return NULL;
}

TMatriz* operaciones(char **cadena, TVar *LaGranVariable , int num_arg){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(contarCaracteres(cadena, "+") == 1){
        TMatriz *matrizA = crearAux(&cadena[0],LaGranVariable);
        TMatriz *matrizB = crearAux(&cadena[2],LaGranVariable);
        if (matrizA != NULL && matrizB != NULL) 
        {
            TMatriz *resultadoSuma = sumarMatrices(matrizA, matrizB);
            return resultadoSuma;  
        } else {
            // Manejo de errores si las variables no se encuentran
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: una o ambas variables no existen.\n");
            SetConsoleTextAttribute(hConsole, 7);
            
            return NULL; 
        }          


    }else if(contarCaracteres(cadena, "-") == 1){
        TMatriz *matrizA = crearAux(&cadena[0],LaGranVariable);
        TMatriz *matrizB = crearAux(&cadena[2],LaGranVariable);
        if (matrizA != NULL && matrizB != NULL) 
        {
            TMatriz *resultadoResta = restarMatrices(matrizA, matrizB);
            return resultadoResta;  
        } else {
            // Manejo de errores si las variables no se encuentran
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: una o ambas variables no existen.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(contarCaracteres(cadena, "*") == 1){
        TMatriz *matrizA = crearAux(&cadena[0],LaGranVariable);
        TMatriz *matrizB = crearAux(&cadena[2],LaGranVariable);
        if (matrizA != NULL && matrizB != NULL) 
        {
            TMatriz *resultadoMulti = multiplicarMatrices(matrizA, matrizB);
            return resultadoMulti;  
        } else {
            // Manejo de errores si las variables no se encuentran
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: una o ambas variables no existen.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(contarCaracteres(cadena, "product") == 1){

        if(num_arg != 3){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        if (matrizOvariable(cadena[1]) != 1  && decimalValidar(cadena[2]) == 1) {

            TMatriz *matrizA = crearAux(&cadena[1],LaGranVariable);

            if ( matrizA != NULL) 
            {
                TMatriz *resultadoproduct = productoMatrizPorNumero(&cadena[2],matrizA);
                return resultadoproduct;  
            } else {
                // Manejo de errores si la variable no se encuentra
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: En el argumento 1.\n");
                SetConsoleTextAttribute(hConsole, 7);
                return NULL; 
            }  
        }

        if(decimalValidar(cadena[1]) == 0){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Numero no valido.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizB = crearAux(&cadena[2],LaGranVariable);

        if ( matrizB != NULL) 
        {
            TMatriz *resultadoproduct = productoMatrizPorNumero(&cadena[1],matrizB);
            return resultadoproduct;  
        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento 2.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(contarCaracteres(cadena, "transp") == 1){

        if(num_arg != 2){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizA = crearAux(&cadena[1],LaGranVariable);

        if ( matrizA != NULL) 
        {
            TMatriz *resultadotransp = transponerMatriz(matrizA);
            return resultadotransp;

        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(contarCaracteres(cadena, "&") == 1){

        if(num_arg != 3){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizA = crearAux(&cadena[0],LaGranVariable);
        TMatriz *matrizB = crearAux(&cadena[2],LaGranVariable);

        if (matrizA != NULL && matrizB != NULL) 
        {

            TMatriz *resultadoUnion = unirMatrices(matrizA, matrizB);
            return resultadoUnion;

        } else {
            // Manejo de errores si las variables no se encuentran
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: una o ambas variables no existen.\n");
            SetConsoleTextAttribute(hConsole, 7);
            
            return NULL; 
        } 
    }else{
        
        TMatriz *matrizA = crearAux(&cadena[0], LaGranVariable);
        if (matrizA != NULL)
        {
        return matrizA;
        }

        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: COMANDO\n");
        SetConsoleTextAttribute(hConsole, 7);

        return NULL;
        }
    
}

TVar *crearVariable(char *nombreVariable, TMatriz *matriz){

    TVar *nuevoNodo = (TVar *)malloc(sizeof(TVar));

    if(nuevoNodo != NULL){

        strcpy(nuevoNodo->nomVar, nombreVariable);
        nuevoNodo->mat = matriz;

        nuevoNodo->sig = NULL;
        nuevoNodo->ant = NULL;
    }

    return nuevoNodo;
}

TVar *insertaUltimaVariable(TVar *LagranVariable, TVar *variableAsignar){

    TVar *auxiliar = LagranVariable;

    if(auxiliar == NULL){

        // printf("Primer nodo\n");

        LagranVariable = variableAsignar;

        LagranVariable->sig = NULL;
        LagranVariable->ant = NULL;
    }
    else{

        while(auxiliar->sig != NULL){
            auxiliar = auxiliar->sig;
        }

        auxiliar->sig = variableAsignar;
        variableAsignar->ant = auxiliar;
        variableAsignar->sig = NULL;
    }

    return LagranVariable;

}

TVar *buscarVariable(TVar *laGranVariable, char *nombreVariable){

    TVar *auxiliar = laGranVariable;

    while(auxiliar != NULL){

        if(strcmp(auxiliar->nomVar, nombreVariable) == 0){
            return auxiliar;
        }
        auxiliar = auxiliar->sig;
    }

    return NULL;
}

void imprimirTVar(TVar *LaGranLista){
    TVar *aux = LaGranLista;
    while(aux != NULL){
        printf("%s\n", aux->nomVar);
        mostrarMatriz(aux->mat);
        aux = aux->sig;
    }
}

int matrizOvariable(char *cad){
    
    if(cad[0] >= 'a' && cad[0] <= 'z'){
        return 0;
    }
    else if(cad[0] >= 'A' && cad[0] <= 'Z'){
        return 0;
    }
    else if(cad[0] == '+' || cad[0] == '-'){ 

        if(cad[1] >= '0' || cad[1] <= '9'){
            return 2;
        }
        if(cad[1] == '.'){
            if(cad[2] >= '0' && cad[2] <= '9'){
                return 2;
            }
            return 1;
        }

    }
    else if(cad[0] == '.'){
        if(cad[1] >= '0' && cad[1] <= '9'){
            return 2;
        }
        return 1;
    }
    else if(cad[0] >= '0' || cad[0] <= '9'){
        return 2;
    }

    return 1;
}

int validarNombre(char *nomVar){

    // Verifica la longitud del nombre de la variable
    if (strlen(nomVar) > 15) {
        return 0;
    }

    int i = 0;

    while(nomVar[i] != '\0'){
        if(nomVar[i] >= '0' && nomVar[i] <= '9'){
            i++;
            continue;
        }
        if(nomVar[i]>= 'a' && nomVar[i] <= 'z'){
            i++;
            continue;
        }
        if(nomVar[i] >= 'A' && nomVar[i] <= 'Z'){
            i++;
            continue;
        }
        return 0;
    }

    if(strcmp(nomVar, "quit") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "det") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "product") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "view") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "save") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "load") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "load over") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "$") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "transp") == 0){
        return 0;
    }

    return 1;

}


// Muestra todas las variables almacenadas
void laGranVista(TVar *laGranVariable) {
    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (laGranVariable == NULL) {
        SetConsoleTextAttribute(hConsole, 4);
        printf("No hay variables cargadas\n");
        SetConsoleTextAttribute(hConsole, 7);
        return;
    }

    // Contar el número de variables
    int numVariables = 0;
    TVar *auxiliar = laGranVariable;
    while (auxiliar != NULL) {
        numVariables++;
        auxiliar = auxiliar->sig;
    }

    // Crear un array para almacenar las variables ordenadas
    TVar **variablesOrdenadas = malloc(numVariables * sizeof(TVar *));
    auxiliar = laGranVariable;
    int i = 0;
    while (auxiliar != NULL) {
        variablesOrdenadas[i] = auxiliar;
        auxiliar = auxiliar->sig;
        i++;
    }

    // Ordenar las variables por el nombre de la variable
    for (int j = 0; j < numVariables - 1; j++) {
        for (int k = j + 1; k < numVariables; k++) {
            if (strcmp(variablesOrdenadas[j]->nomVar, variablesOrdenadas[k]->nomVar) > 0) {
                TVar *temp = variablesOrdenadas[j];
                variablesOrdenadas[j] = variablesOrdenadas[k];
                variablesOrdenadas[k] = temp;
            }
        }
    }

    // Mostrar las variables ordenadas
    SetConsoleTextAttribute(hConsole, 2);
    for (int j = 0; j < numVariables; j++) {
        auxiliar = variablesOrdenadas[j];
        TMatriz *matrizaux = auxiliar->mat;
        if (matrizaux->m == 0) {
            printf("%s: [vacia!]\n", auxiliar->nomVar);
        } else {
            printf("%s ( %d x %d ) : ", auxiliar->nomVar, matrizaux->f, matrizaux->c);
            for (int k = 0; k < matrizaux->c; k++) {
                printf("%.2f ", matrizaux->m[0][k]);
            }
            printf("\n");
        }
    }
    SetConsoleTextAttribute(hConsole, 7);

    // Liberar la memoria del array de variables ordenadas
    free(variablesOrdenadas);
}

int contarCaracteres(char **cadena, char *caracter){

    int contador = 0;
    int i=0;

    while(cadena[i] != NULL){ //'\0'
        if(strcmp(cadena[i], caracter) == 0){
            contador++;
        }
        i++;
    }

    return contador;
}

TMatriz* sumarMatrices(TMatriz *matrizA, TMatriz *matrizB) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if ( matrizB != NULL && matrizA != NULL) {
        if (matrizB->f == matrizA->f && matrizB->c == matrizA->c ) {
            TMatriz *resultado = crearMatriz(matrizB->f, matrizB->c);
            for (int i = 0; i < matrizA->f; i++) {
                for (int j = 0; j < matrizA->c; j++) {
                    
                    resultado->m[i][j] = matrizB->m[i][j] + matrizA->m[i][j];
                    //printf("Suma de matriz en (%d, %d) = %.2f\n", i, j, resultado->m[i][j]);
                }
            }
            return resultado;
        }
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: las matrices no son del mismo tamano.\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
   
    return NULL;
}

TMatriz* restarMatrices(TMatriz *matrizA, TMatriz *matrizB) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if ( matrizB != NULL && matrizA != NULL) {
        if (matrizB->f == matrizA->f && matrizB->c == matrizA->c ) {
            TMatriz *resultado = crearMatriz(matrizB->f, matrizB->c);
            for (int i = 0; i < matrizA->f; i++) {
                for (int j = 0; j < matrizA->c; j++) {
                    
                    resultado->m[i][j] = matrizA->m[i][j] - matrizB->m[i][j];
                    //printf("Suma de matriz en (%d, %d) = %.2f\n", i, j, resultado->m[i][j]);
                }
            }
            return resultado;
        }
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: las matrices no son del mismo tamano.\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
   
    return NULL;
}

TMatriz* multiplicarMatrices(TMatriz* matrizA, TMatriz* matrizB) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (matrizA == NULL || matrizB == NULL) {
        // Una o ambas matrices no son válidas
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: Una o ambas matrices no son válidas.\n"); // AQUI NO LLEGA A ENTRAR COMENTAR O QUITAR
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;
    }

    int filasA = matrizA->f;
    int columnasA = matrizA->c;
    int filasB = matrizB->f;
    int columnasB = matrizB->c;

    if (columnasA != filasB) {
        // Las matrices no tienen tamaños compatibles para la multiplicación
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: El número de columnas de la primera matriz no coincide con el número de filas de la segunda matriz.\n");
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;
    }

    TMatriz* resultado = crearMatriz(filasA, columnasB);

    if (resultado == NULL) {
        // Maneja errores de asignación de memoria
        return NULL;
    }

    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            resultado->m[i][j] = 0;
            for (int k = 0; k < columnasA; k++) {
                resultado->m[i][j] += matrizA->m[i][k] * matrizB->m[k][j];
            }
        }
    }

    return resultado;
}

TMatriz* copiarMatriz(TMatriz *matriz) {
    int filas = matriz->f;
    int columnas = matriz->c;

    // Crear una nueva matriz
    TMatriz *matrizCopiada = crearMatriz(filas, columnas);

    // Copiar los elementos de la matriz original a la matriz copiada
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matrizCopiada->m[i][j] = matriz->m[i][j];
        }
    }

    return matrizCopiada;
}

void triangularMatriz(TMatriz *matriz) {
    int filas = matriz->f;
    int columnas = matriz->c;

    for (int k = 0; k < filas - 1; k++) {
        for (int i = k + 1; i < filas; i++) {
            double factor = matriz->m[i][k] / matriz->m[k][k];
            for (int j = k; j < columnas; j++) {
                matriz->m[i][j] -= factor * matriz->m[k][j];
            }
        }
    }
}

double determinanteTriangular(TMatriz *matriz) {
    int filas = matriz->f;
    double det = 1.0;

    for (int i = 0; i < filas; i++) {
        det *= matriz->m[i][i];
    }

    return det;
}

double determinanteGauss(TMatriz *matriz) {
    // Copiar la matriz original
    TMatriz *matrizCopiada = copiarMatriz(matriz);

    // Triangular la matriz copiada
    triangularMatriz(matrizCopiada);

    // Calcular el determinante de la matriz triangular copiada
    double det = determinanteTriangular(matrizCopiada);

    // Liberar la memoria de la matriz copiada
    liberarMatriz(matrizCopiada);

    return det;
}

TMatriz* liberarMatriz(TMatriz *matriz) {

    for (int i = 0; i < matriz->f; i++) {
        free(matriz->m[i]);
    }

    // Liberar el doble puntero a las filas
    free(matriz->m);

    // Liberar la estructura de la matriz
    free(matriz);
    
    //Devolver una matriz vacía
    TMatriz *matrizVacia = crearMatriz(0, 0);
    mostrarMatriz(matrizVacia);
    return matrizVacia;
    
}

int decimalValidar(char *cad){

    int i, ini, p=0, j;

    if(cad[0] == '+' || cad[0] == '-'){
        ini=1;
    }
    else{
        ini=0;
    }

    for(i=ini; i<strlen(cad); i++){
        if(cad[i]<'0' || cad[i]> '9'){
            if(cad[i] == '.'){
                p++;
            }
            else{
                return 0;
            }
        }
        if(p==2){
            return 0;
        }
    }

    if(ini==1 && strlen(cad) == 1){
        return 0;
    }
    if(strlen(cad) == 0){
        return 0;
    }

    if(ini==1 && strlen(cad) == 2 && cad[1] == '.'){ //+.
        return 0;
    }

    if(ini == 0 && strlen(cad) == 1 && cad[0] == '.'){ // .
        return 0;
    }

    return 1;
}


TMatriz* productoMatrizPorNumero(char **cadena, TMatriz *matriz) {
    double numero = atof(*cadena);  // Convertir la cadena a un número
    int filas = matriz->f;
    int columnas = matriz->c;

    // Crear una nueva matriz para almacenar el resultado
    TMatriz *resultado = crearMatriz(filas, columnas);

    // Multiplicar cada elemento de la matriz por el número
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado->m[i][j] = numero * matriz->m[i][j];
        }
    }

    return resultado;
}

TVars *crearWorkspace(TVars *workspace){

    workspace = (TVars *) malloc(sizeof(TVars));

    workspace->numVars = 0;
    workspace->primera = NULL;

    return workspace;
}

TVar *liberarVariables(TVar *laGranVariable){

    TVar *auxiliarVariable = NULL; //pq trabajar con la granVariable directamente es peligroso

    if(laGranVariable == NULL){ //caso de que este vacio
        free(laGranVariable);
        return NULL;
    }

    auxiliarVariable = laGranVariable;


    while(auxiliarVariable != NULL){ 
        
        laGranVariable = laGranVariable->sig; //ahora la gran variable apunta a la segunda posicion

        // limpiamos la Tmatriz de la variable (TVar)
        auxiliarVariable->mat = liberarMatriz(auxiliarVariable->mat);

        //Recolocamos los punteros
        auxiliarVariable->ant = NULL;
        auxiliarVariable->sig = NULL;

       
        if(laGranVariable != NULL){
            laGranVariable->ant = NULL; //la que estaba en segunda posicion
        }

        free(auxiliarVariable);

        auxiliarVariable = laGranVariable;

    }

    free(laGranVariable);
    //laGranVista(laGranVariable);
    return NULL;
}

void save(char *nombre, TVars *workspace){

    //Si al final acabamos poniendole filtros al nombre descomentar esto
    /*
    int i = validarNombre(nombre);
    if(i == 0){
        printf("ERROR FATAL\n");
        return 0;
    }
    */

   char aux[50]="./";
   int numeroElementos = 0;

    strcat(aux, nombre);

    if(strchr(nombre, '.') == NULL){ //Entramos en el caso de que no tenga .txt
        strcat(aux, ".txt");
    }

    FILE *fichero;
    fichero = fopen(aux, "w");
    if(fichero != NULL){

        //fprintf(fichero, "LIST WORKSPACE\n"); // SI QUEREMOS PONER UN TITULO EN EL SAVE
        //fprintf(fichero, "---------------\n");   

        TVar *auxiliar = workspace->primera; 

        for(int i = 0; i<workspace->numVars; i++){
            
            //Imprimimos el nombre de la variable
            fprintf(fichero, "%s\n", auxiliar->nomVar);

            TMatriz *auxMatriz = auxiliar->mat;

            fprintf(fichero, "( ");
            for (int i = 0; i < auxMatriz->f; i++)
            {
                for (int j = 0; j < auxMatriz->c; j++)
                {
                    fprintf(fichero,"%.8f", auxMatriz->m[i][j]);
                    if (j < auxMatriz->c - 1) {
                        fprintf(fichero," ");
                    }
                }
                if (i < auxMatriz->f - 1) {
                    fprintf(fichero," | ");
                }
            }

            fprintf(fichero, " )\n");
            auxiliar = auxiliar->sig;
        }

        fclose(fichero);
    }
    else{
        printf("ERROR AL GUARDAR\n");
    }

}

int contadorVariables(TVar *LaGranVariable){

    TVar *aux = LaGranVariable;
    int i = 0;

    while(aux != NULL){

        i++;
        aux = aux->sig;
    }

    return i;

}

TVars *load(char *nombre, TVars *workspace, int sobrescribir) {

    FILE *fichero;
    char aux[50] = "./";
    char linea[1000]; // Caracteres en la linea
    int n = 0;

    strcat(aux, nombre);

    if (strchr(nombre, '.') == NULL) { //Entramos en el caso de que no tenga .txt
        strcat(aux, ".txt");
    }

    // printf("La ruta del load es: %s\n", aux);

    fichero = fopen(aux, "r");//abrimos fichero en modo lectura

    if (sobrescribir){
        workspace = crearWorkspace(NULL);
    }
    
    if (fichero == NULL) {
        // El archivo no existe o no puede ser abierto
        // perror("Error al abrir el archivo");
        fclose(fichero);
        return NULL; // Devolvemos el workspace actual sin cambios
    }

    // Contar las líneas del documento
    while (fgets(linea, sizeof(linea), fichero) != NULL) {
        n++;
    }

    // Validar que hay suficientes líneas para representar variables
    if (n % 2 != 0) {
        fclose(fichero);
        printf("Error: El número de líneas no es par.\n");
        return NULL;
    }

    fseek(fichero, 0, SEEK_SET); // Mover el cursor al principio del documento

    // Si el número de variables es 0, devolvemos un workspace vacío
    if (n == 0) {
        fclose(fichero);
        return workspace;
    }

    int numeroVariables = n / 2;
    workspace->numVars = numeroVariables;

    TVar *laGranVariable = workspace->primera;

    for (int i = 0; i < numeroVariables; i++) {
        char nombreVariable[16] = "";

        fgets(linea, 1000, fichero);
        strcpy(nombreVariable, linea);
        Trim(nombreVariable);

        TVar *existingVariable = buscarVariable(laGranVariable, nombreVariable);

        if (existingVariable != NULL) {
            fgets(linea, 1000, fichero);
            char separadores[8] = " \t\n";
            MiStrTok(linea, separadores, 1);
            int filas, columnas;
            if (validarMatriz(linea, &filas, &columnas) == 1) {
                existingVariable->mat = crearMatriz(filas,columnas);
                llenarMatrizDesdeCadena(existingVariable->mat,linea);
            }
        }else{
            fgets(linea, 1000, fichero);
            char separadores[8] = " \t\n";
            MiStrTok(linea, separadores, 1);
            int filas, columnas;
            if (validarMatriz(linea, &filas, &columnas) == 1) {
                TMatriz *matrizAux = crearMatriz(filas, columnas);
                llenarMatrizDesdeCadena(matrizAux, linea);
                TVar *auxiliarVariable = crearVariable(nombreVariable, matrizAux);
                laGranVariable = insertaUltimaVariable(laGranVariable, auxiliarVariable);
            }
        }
        
    }

    workspace->primera = laGranVariable;

    //imprimirTVAR(laGranVariable);
    fclose(fichero);
    return workspace;
}

void Trim(char *cad){
    int c, i=0, j, n = strlen(cad);

    if(cad == NULL || n < 1){
        return;
    }
    
    n--;

    while(n>0 && ((c=cad[n]) == ' ' || c=='\n')){ 
        n--;
    }

    cad[n+1] = '\0';

    while(i<=n && ((c=cad[i]) == ' ' || c == '\n')){ 
        i++;
    }

    for(j=0; j<=n-i+1; j++){
        cad[j] = cad[j+i];
    }
    
}

double productoEscalar(TMatriz *matriz1, TMatriz *matriz2){
    double resultado = 0.0;

    for (int i = 0; i < matriz1->c; i++) {
        resultado += matriz1->m[0][i] * matriz2->m[0][i];
    }

    return resultado;
}

// Función para calcular la matriz transpuesta
TMatriz *transponerMatriz(TMatriz *matriz) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    TMatriz *transpuesta = crearMatriz(matriz->c, matriz->f);

    for (int i = 0; i < matriz->f; i++) {
        for (int j = 0; j < matriz->c; j++) {
            transpuesta->m[j][i] = matriz->m[i][j];
        }
    }

    return transpuesta;
}

TMatriz* unirMatrices(TMatriz *matrizA, TMatriz *matrizB) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (matrizA->f != matrizB->f) {
        // Las matrices no tienen el mismo numero de filas
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Las matrices no tienen el mismo numero de filas.\n");
            SetConsoleTextAttribute(hConsole, 7);
        return NULL; 
    }
    
    int filas = matrizA->f;
    int columnasA = matrizA->c;
    int columnasB = matrizB->c;
    int columnasTotales = columnasA + columnasB;
    
    TMatriz* resultado = crearMatriz(filas, columnasTotales);
    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnasA; j++) {
            resultado->m[i][j] = matrizA->m[i][j];
        }
        for (int j = columnasA; j < columnasTotales; j++) {
            resultado->m[i][j] = matrizB->m[i][j - columnasA];
        }
    }
    
    return resultado;
}
