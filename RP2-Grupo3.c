//GRUPO 3
//BECVORT, FRANCO
//MARTINEZ, ROCIO

/*
FALTA CORREGIR: "en los costos de ordenamiento cuando intercambia
nuplas son dos los corrimientos (aplica para los dos ordenamientos)"
*/

//ENTREGA CORRECCIONES PM2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <limits.h>

#define MAX 300	//Longitud de las listas

//Creo tipo booleano
typedef int bool;
#define true 1
#define false 0

					//VEHICULO

//Estructura vehiculo
typedef struct{
    char patente[8];
    char marca[61];
    int anio;
    char dueno[51];
    char telefono[16];
    char servicios[71];
    float monto;
    char fecha[11];
}vehiculo;

//Operaciones sobre vehiculos

vehiculo scanDatos();
vehiculo nuevoVehiculo(char patente[], char modelo[], int anio, char dueno[], char telefono[], char servicios[], float monto, char fecha[]);
void mostrarVehiculo(vehiculo v);
bool compararVehiculos(vehiculo v1, vehiculo v2);
void copiarVehiculo(vehiculo v1, vehiculo *v2);
void swapVehiculo(vehiculo *v1, vehiculo *v2);

					//LISTA SECUENCIAL DESORDENADA

//Estructura
typedef struct{
    vehiculo arr[MAX];
    int ultimo;
}LSD;

//Operaciones sobre la LSD

void initLSD(LSD *lista);
bool isFullLSD(LSD lista);
bool isEmptyLSD(LSD lista);
bool localizarLSD(LSD lista, char patente[], int *posicion, double *c);
bool perteneceLSD(LSD lista, char patente[], double *c);
vehiculo evocarLSD(LSD lista, char patente[], double *c);
bool altaLSD(LSD *lista, vehiculo v, double *c);
int bajaLSD(LSD *lista, char patente[],int condicion,vehiculo v, double *c);
void mostrarLSD(LSD lista);
void ordenBurbuja(LSD *lista);
void ordenInsercion(LSD *lista);
void copiarLSD(LSD original, LSD *nueva);

					//LISTA SECUENCIAL ORDENADA

//Estructura
typedef struct{
    vehiculo arr[MAX];
    int ultimo;
}LSO;

//Operaciones sobre la LSO

void initLSO(LSO *lista);
bool isFullLSO(LSO lista);
bool isEmptyLSO(LSO lista);
bool localizarLSO(LSO lista, char patente[], int *posicion, double *c);
bool perteneceLSO(LSO lista, char patente[], double *c);
vehiculo evocarLSO(LSO lista, char patente[], double *c);
bool altaLSO(LSO *lista, vehiculo v, double *c);
int bajaLSO(LSO *lista, char patente[],int condicion,vehiculo v, double *c);
void mostrarLSO(LSO lista);

					//LISTA SECUENCIAL ORDENADA BUSQUEDA BINARIA POR TRISECCION

//Estructura
typedef struct{
    vehiculo arr[MAX];
    int ultimo;
}LSOBT;

//Operaciones sobre la LSOBT

void initLSOBT(LSOBT *lista);
bool isFullLSOBT(LSOBT lista);
bool isEmptyLSOBT(LSOBT lista);
bool localizarLSOBT(LSOBT lista, char patente[], int *posicion, double *c);
bool perteneceLSOBT(LSOBT lista, char patente[], double *c);
vehiculo evocarLSOBT(LSOBT lista, char patente[], double *c);
bool altaLSOBT(LSOBT *lista, vehiculo v, double *c);
int bajaLSOBT(LSOBT *lista, char patente[],int condicion,vehiculo v, double *c);
void mostrarLSOBT(LSOBT lista);

                    //PILA - Usada para administrar tiempos y costos)

typedef struct{
    double nums[MAX];
    int tope;
} pila;

//Operaciones sobre la Pila

void initPila(pila *p);
void push(pila *p, double n);
double pop(pila *p);
int isFull(pila p);
int isEmpty (pila p);
double copy(pila p);
double getEstadisticas(pila p, double* max, double* prom);


                    //OPERACIONES DE TIEMPOS Y COSTOS
void compararEstructuras(LSD *lsd, LSO *lso, LSOBT *lsobt);

					//MAIN
int main(){
    system("color 0A");
    LSD lsd;initLSD(&lsd);
    LSO lso;initLSO(&lso);
    LSOBT lsobt; initLSOBT(&lsobt);
    int menu1, menu2, menu3;


    char patente[8];
    double c;
    vehiculo v;

    do{
        system("cls");
        printf("BIENVENIDO! Seleccione una de las siguientes opciones:\n\n");
        printf("[1] Administracion de Estructuras\n");
        printf("[2] Comparacion de Estructuras\n");
        printf("\n[0] Salir");
        printf("\n\nOpcion: ");
        scanf("%d",&menu1);
        getchar();
        switch(menu1){
        case 1: //Administracion de Estructuras
            do{
                system("cls");
                printf("Con que estructura desea trabajar?:\n\n");
                printf("[1] Lista Secuencial Desordenada\n");
                printf("[2] Lista Secuencial Ordenada\n");
                printf("[3] Lista Secuencial Ordenada con Busqueda Binaria por Triseccion\n");
                printf("\n[0] Volver\n");
                printf("\nOpcion: ");
                scanf("%d",&menu2);
                getchar();
                switch(menu2){
                case 1: //LSD
                    do{
                        system("cls");
                        printf("\t\t Lista secuencial desordenada\n\n");
                        printf("Seleccione una opcion:\n\n");
                        printf("[1] Ingresar Vehiculo\n");
                        printf("[2] Eliminar Vehiculo Existente\n");
                        printf("[3] Consultar Datos de un Vehiculo\n");
                        printf("[4] Determinar si un Vehiculo ha realizado servicio mecanico\n");
                        printf("[5] Mostrar Estructura\n");
                        printf("[6] Comparar Ordenamiento: Burbuja e Insercion\n");
                        printf("\n[0] Volver\n");
                        printf("\nOpcion: ");
                        scanf("%d",&menu3);
                        getchar();
                        switch(menu3){
                        case 1: //Ingresar vehiculo
                            if(isFullLSD(lsd)){
                                //estructura llena, informa por pantalla
                                system("cls");
                                printf("Error: no hay mas lugar en la lista\n");
                                system("pause");
                            }
                            else{
                                //Se arma un nuevo vehiculo, se intenta dar de alta, y se evalua el exito de la operacion
                                if(altaLSD(&lsd,scanDatos(), &c)){
                                    //exito en el alta, informa por pantalla
                                    system("cls");
                                    printf("Exito al cargar vehiculo\n");
                                    system("pause");
                                }
                                else{
                                    //patente repetida, informa por pantalla
                                    system("cls");
                                    printf("Error: patente repetida\n");
                                    system("pause");
                                }
                            }
                            break;
                        case 2: //Eliminar vehiculo existente
                            if(isEmptyLSD(lsd)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else{
                                system("cls");
                                printf("Ingrese patente: ");
                                scanf("%[^\n]",patente);
                                getchar();
                                while(strlen(patente)!=7){
                                    printf("\n\nError: la patente ingresada debe ser de 7 caracteres. Intente nuevamente\nIngrese patente: ");
                                    scanf("%[^\n]",patente);
                                    getchar();
                                }
                                strupr(patente);

                                //Se intenta dar de baja y se evalua el exito de la operacion
                                int rta = bajaLSD(&lsd, patente,1, v, &c);
                                switch(rta){
                                case true:
                                    //exito en la baja, informa por pantalla
                                    system("cls");
                                    printf("Eliminacion exitosa\n");
                                    system("pause");
                                    break;
                                case -1:
                                    //se decidio no dar de baja, informa por pantalla
                                    system("cls");
                                    printf("Baja cancelada por el usuario\n");
                                    system("pause");
                                    break;
                                case false:
                                    //patente no encontrada, informa por pantalla
                                    system("cls");
                                    printf("No existe el vehiculo\n");
                                    system("pause");
                                    break;
                                }
                            }
                            break;
                        case 3: //Consultar datos de un vehiculo
                            if(isEmptyLSD(lsd)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else{
                                system("cls");
                                printf("Ingrese patente: ");
                                scanf("%[^\n]",patente);
                                getchar();
                                while(strlen(patente)!=7){
                                    printf("\n\nError: la patente ingresada debe ser de 7 caracteres. Intente nuevamente\nIngrese patente: ");
                                    scanf("%[^\n]",patente);
                                    getchar();
                                }
                                strupr(patente);

                                v = evocarLSD(lsd, patente, &c);
                                if(strcmp(v.patente, "0000000")==0){ //si la patente de v es invalida
                                    //vehiculo no encontrado, se informa por pantalla
                                    system("cls");
                                    printf("No existe un vehiculo con la patente %s en el sistema\n", patente);
                                    system("pause");
                                }
                                else{
                                    //vehiculo encontrado, se muestra por pantalla
                                    system("cls");
                                    mostrarVehiculo(v);
                                    system("pause");
                                }
                            }
                            break;
                        case 4: //Determinar si un vehiculo ha realizado servicio mecanico
                            if(isEmptyLSD(lsd)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else{
                                system("cls");
                                printf("Ingrese patente: ");
                                fflush(stdin);
                                scanf("%7[^\n]",patente);
                                getchar();
                                system("pause");
                                while(strlen(patente)!=7)
                                {
                                    printf("\n\nError: la patente ingresada debe ser de 7 caracteres. Intente nuevamente\nIngrese patente: ");
                                    scanf("%[^\n]",patente);
                                    getchar();
                                }
                                strupr(patente);

                                if(perteneceLSD(lsd, patente, &c))
                                {
                                    //vehiculo existe, informar por pantalla
                                    system("cls");
                                    printf("El vehiculo con la patente %s esta en el sistema\n", patente);
                                    system("pause");
                                }
                                else
                                {
                                    //vehiculo no existe, informar por pantalla
                                    system("cls");
                                    printf("No existe un vehiculo con la patente %s en el sistema\n", patente);
                                    system("pause");
                                }
                            }
                            break;
                        case 5: //Mostrar estructura
                            if(isEmptyLSD(lsd)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else mostrarLSD(lsd); //muestra estructura
                            break;
                        case 6: //Comparar Odenamiento: Burbuja e Insercion
                            if(isEmptyLSD(lsd)){
                                //estructura vacia, informa por pantalla
                                        system("cls");
                                        printf("Error: no se puede realizar la operacion seleccionada con la LSD vacia\n");
                                        system("pause");
                            }
                            else{
                                //estructura no vacia, realizo la operación
                                LSD lsdBurbuja; initLSD(&lsdBurbuja);
                                LSD lsdInsercion; initLSD(&lsdInsercion);
                                copiarLSD(lsd, &lsdBurbuja);
                                copiarLSD(lsd, &lsdInsercion);
                                //Orden por Insercion
                                ordenInsercion(&lsdInsercion);
                                printf("\nA continuacion se muestra el resultado del ordenamiento por insercion\n");
                                system("pause");
                                mostrarLSD(lsdInsercion);
                                //Orden Burbuja
                                ordenBurbuja(&lsdBurbuja);
                                printf("\nA continuacion se muestra el resultado del ordenamiento burbuja\n");
                                system("pause");
                                mostrarLSD(lsdBurbuja);
                            }
                            break;
                        case 0: //Volver
                            break;
                        default:
                            menu3=-1;
                        }
                    }
                    while(menu3!=0);
                    break;
                case 2: //LSO
                    do{
                        system("cls");
                        printf("\t\t Lista secuencial ordenada\n\n");
                        printf("Seleccione una opcion:\n\n");
                        printf("[1] Ingresar Vehiculo\n");
                        printf("[2] Eliminar Vehiculo Existente\n");
                        printf("[3] Consultar Datos de un Vehiculo\n");
                        printf("[4] Determinar si una Vehiculo ha realizado servicio mecanico\n");
                        printf("[5] Mostrar Estructura\n");
                        printf("\n[0] Volver\n");
                        printf("\nOpcion: ");
                        scanf("%d",&menu3);
                        getchar();
                        switch(menu3){
                        case 1: //Ingresar vehiculo
                            if(isFullLSO(lso)){
                                //estructura llena, informa por pantalla
                                system("cls");
                                printf("Error: no hay mas lugar en la lista\n");
                                system("pause");
                            }
                            else{
                                //Se arma un nuevo vehiculo, se intenta dar de alta, y se evalua el exito de la operacion
                                if(altaLSO(&lso, scanDatos(), &c)){
                                    //exito en el alta, informa por pantalla
                                    system("cls");
                                    printf("Exito al cargar vehiculo\n");
                                    system("pause");
                                }
                                else{
                                    //patente repetida, informa por pantalla
                                    system("cls");
                                    printf("Error: patente repetida\n");
                                    system("pause");
                                }
                            }
                            break;
                        case 2: //Eliminar vehiculo existente
                            if(isEmptyLSO(lso)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else{
                                system("cls");
                                printf("Ingrese patente: ");
                                scanf("%[^\n]",patente);
                                getchar();
                                while(strlen(patente)!=7){
                                    printf("\n\nError: la patente ingresada debe ser de 7 caracteres. Intente nuevamente\nIngrese patente: ");
                                    scanf("%[^\n]",patente);
                                    getchar();
                                }
                                strupr(patente);

                                //Se intenta dar de baja y se evalua el exito de la operacion
                                int rta = bajaLSO(&lso, patente,1, v, &c);
                                switch(rta){
                                case true:
                                    //exito en la baja, informa por pantalla
                                    system("cls");
                                    printf("Eliminacion exitosa\n");
                                    system("pause");
                                    break;
                                case -1:
                                    //se decidio no dar de baja, informa por pantalla
                                    system("cls");
                                    printf("Baja cancelada por el usuario\n");
                                    system("pause");
                                    break;
                                case false:
                                    //patente no encontrada, informa por pantalla
                                    system("cls");
                                    printf("No existe el vehiculo\n");
                                    system("pause");
                                    break;

                                }
                            }
                            break;
                        case 3: //Consultar datos de un vehiculo
                            if(isEmptyLSO(lso)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else{
                                system("cls");
                                printf("Ingrese patente: ");
                                scanf("%[^\n]",patente);
                                getchar();
                                while(strlen(patente)!=7){
                                    printf("\n\nError: la patente ingresada debe ser de 7 caracteres. Intente nuevamente\nIngrese patente: ");
                                    scanf("%[^\n]",patente);
                                    getchar();
                                }
                                strupr(patente);

                                v = evocarLSO(lso, patente, &c);
                                if(strcmp(v.patente, "0000000")==0){ //si la patente de v es invalida
                                    //vehiculo no encontrado, se informa por pantalla
                                    system("cls");
                                    printf("No existe un vehiculo con la patente %s en el sistema\n", patente);
                                    system("pause");
                                }
                                else{
                                    //vehiculo encontrado, se muestra por pantalla
                                    system("cls");
                                    mostrarVehiculo(v);
                                    system("pause");
                                }
                            }
                            break;
                        case 4: //Determinar si un vehiculo ha realizado servicio mecanico
                            if(isEmptyLSO(lso)){
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else{
                                system("cls");
                                printf("Ingrese patente: ");
                                scanf("%[^\n]",patente);
                                getchar();
                                while(strlen(patente)!=7){
                                    printf("\n\nError: la patente ingresada debe ser de 7 caracteres. Intente nuevamente\nIngrese patente: ");
                                    scanf("%[^\n]",patente);
                                    getchar();
                                }
                                strupr(patente);

                                if(perteneceLSO(lso, patente, &c)){
                                    //vehiculo existe, informar por pantalla
                                    system("cls");
                                    printf("El vehiculo con la patente %s esta en el sistema\n", patente);
                                    system("pause");
                                }
                                else{
                                    //vehiculo no existe, informar por pantalla
                                    system("cls");
                                    printf("No existe un vehiculo con la patente %s en el sistema\n", patente);
                                    system("pause");
                                }
                            }
                            break;
                        case 5: //Mostrar estructura
                            if(isEmptyLSO(lso)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else mostrarLSO(lso);
                            break;
                        case 0: //Volver
                            break;
                        default:
                            menu3=-1;
                        }
                    }
                    while(menu3!=0);
                    break;
                case 3: //LSOBT
                    do{
                        system("cls");
                        printf("\t\t Lista secuencial ordenada con busqueda por triseccion\n\n");
                        printf("Seleccione una opcion:\n\n");
                        printf("[1] Ingresar Vehiculo\n");
                        printf("[2] Eliminar Vehiculo Existente\n");
                        printf("[3] Consultar Datos de un Vehiculo\n");
                        printf("[4] Determinar si una Vehiculo ha realizado servicio mecanico\n");
                        printf("[5] Mostrar Estructura\n");
                        printf("\n[0] Volver\n");
                        printf("\nOpcion: ");
                        scanf("%d",&menu3);
                        getchar();
                        switch(menu3){
                        case 1: //Ingresar vehiculo
                            if(isFullLSOBT(lsobt)){
                                //estructura llena, informa por pantalla
                                system("cls");
                                printf("Error: no hay mas lugar en la lista\n");
                                system("pause");
                            }
                            else{
                                if(altaLSOBT(&lsobt, scanDatos(), &c)){
                                    //exito en el alta, informa por pantalla
                                    system("cls");
                                    printf("Exito al cargar vehiculo\n");
                                    system("pause");
                                }
                                else{
                                    //patente repetida, informa por pantalla
                                    system("cls");
                                    printf("Error: patente repetida\n");
                                    system("pause");
                                }
                            }
                            break;
                        case 2: //Eliminar vehiculo existente
                            if(isEmptyLSOBT(lsobt)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else{
                                system("cls");
                                printf("Ingrese patente: ");
                                scanf("%[^\n]",patente);
                                getchar();
                                while(strlen(patente)!=7){
                                    printf("\n\nError: la patente ingresada debe ser de 7 caracteres. Intente nuevamente\nIngrese patente: ");
                                    scanf("%[^\n]",patente);
                                    getchar();
                                }
                                strupr(patente);

                                //Se intenta dar de baja y se evalua el exito de la operacion
                                int rta = bajaLSOBT(&lsobt, patente,1, v, &c);
                                switch(rta){
                                case true:
                                    //exito en la baja, informa por pantalla
                                    system("cls");
                                    printf("Eliminacion exitosa\n");
                                    system("pause");
                                    break;
                                case -1:
                                    //se decidio no dar de baja, informa por pantalla
                                    system("cls");
                                    printf("Baja cancelada por el usuario\n");
                                    system("pause");
                                    break;
                                case false:
                                    //patente no encontrada, informa por pantalla
                                    system("cls");
                                    printf("No existe el vehiculo\n");
                                    system("pause");
                                    break;

                                }
                            }
                            break;
                        case 3: //Consultar datos de un vehiculo
                            if(isEmptyLSOBT(lsobt)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else{
                                system("cls");
                                printf("Ingrese patente: ");
                                scanf("%[^\n]",patente);
                                getchar();
                                while(strlen(patente)!=7){
                                    printf("\n\nError: la patente ingresada debe ser de 7 caracteres. Intente nuevamente\nIngrese patente: ");
                                    scanf("%[^\n]",patente);
                                    getchar();
                                }
                                strupr(patente);

                                v = evocarLSOBT(lsobt, patente, &c);
                                if(strcmp(v.patente, "0000000")==0){ //si la patente de v es invalida
                                    //vehiculo no encontrado, se informa por pantalla
                                    system("cls");
                                    printf("No existe un vehiculo con la patente %s en el sistema\n", patente);
                                    system("pause");
                                }
                                else{
                                    //vehiculo encontrado, se muestra por pantalla
                                    system("cls");
                                    mostrarVehiculo(v);
                                    system("pause");
                                }
                            }
                            break;
                        case 4: //Determinar si un vehiculo ha realizado servicio mecanico
                            if(isEmptyLSOBT(lsobt)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else{
                                system("cls");
                                printf("Ingrese patente: ");
                                scanf("%[^\n]",patente);
                                getchar();
                                while(strlen(patente)!=7){
                                    printf("\n\nError: la patente ingresada debe ser de 7 caracteres. Intente nuevamente\nIngrese patente: ");
                                    scanf("%[^\n]",patente);
                                    getchar();
                                }
                                strupr(patente);

                                if(perteneceLSOBT(lsobt, patente,&c)){
                                    //vehiculo existe, informar por pantalla
                                    system("cls");
                                    printf("El vehiculo con la patente %s esta en el sistema\n", patente);
                                    system("pause");
                                }
                                else{
                                    //vehiculo no existe, informar por pantalla
                                    system("cls");
                                    printf("No existe un vehiculo con la patente %s en el sistema\n", patente);
                                    system("pause");
                                }
                            }
                            break;
                        case 5: //Mostrar estructura
                            if(isEmptyLSOBT(lsobt)){
                                //estructura vacia, informa por pantalla
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else mostrarLSOBT(lsobt);
                            break;
                        case 0: //Volver
                            break;
                        default:
                            menu3=-1;
                        }
                    }
                    while(menu3!=0);
                    break;
                case 0: //Volver
                    break;
                default:
                    menu2=-1;
                }
            }
            while(menu2 != 0);
            break;
        case 2: //Comparacion de Estructuras
            if(!isEmptyLSD(lsd) || !isEmptyLSO(lso) || !isEmptyLSOBT(lsobt)){
                int aux=0;
                do{
                    system("cls");
                    printf("Alguna de las estructuras no se encuentran vacias. Desea vaciarlas para continuar?\n\n[1] Si\n[2] No\n");
                    scanf("%d", &aux);
                }
                while(aux!=1 && aux!=2);
                if(aux==1){
                    initLSD(&lsd); initLSO(&lso); initLSOBT(&lsobt);
                    system("cls");
                    compararEstructuras(&lsd, &lso, &lsobt);
                    system("pause");
                }
            }
            else{
                system("cls");
                compararEstructuras(&lsd, &lso, &lsobt);
                system("pause");
            }
            break;
        case 0: //Salir
            printf("Gracias por utilizar el programa!\n");
            exit(0);
            break;
        default:
            menu1=-1;
        }
    }
    while(menu1 != 0);

    return 0;
}

					//OPERACIONES
//LSD

void initLSD(LSD *lista){
    (*lista).ultimo = -1;
}

bool isFullLSD(LSD lista){
	return(lista.ultimo == (MAX-1));
}

bool isEmptyLSD(LSD lista){
    return(lista.ultimo==-1);
}

bool localizarLSD(LSD lista, char patente[], int *posicion, double *c){
    int i=0;
    *c=0;
    LARGE_INTEGER t_ini, t_fin;
    QueryPerformanceCounter(&t_ini);
    while((i <= lista.ultimo) && (strcmp(patente, lista.arr[i].patente) != 0)){
        i = i+ 1;
        *c = *c + 1;
    }
    *posicion = i;
    QueryPerformanceCounter(&t_fin);

    if(strcmp(patente, lista.arr[i].patente) == 0)
        *c = *c + 1;
    return ((i <= lista.ultimo) && (strcmp(patente, lista.arr[i].patente) == 0));
}


bool perteneceLSD(LSD lista, char patente[], double *c){
    int aux;
	return localizarLSD(lista, patente, &aux, c);
}

vehiculo evocarLSD(LSD lista, char patente[], double *c){
	int posicion;
	vehiculo v;
	if(localizarLSD(lista, patente, &posicion, c))
		//el vehiculo localizado exitosamente es retornado
		return lista.arr[posicion];
	else{
		//retorno un vehiculo con patente invalida
		strcpy(v.patente, "0000000");
		return v;
	}
}

bool altaLSD(LSD *lista, vehiculo v, double *c){
	int posicion;
	if(localizarLSD(*lista, v.patente, &posicion, c))
		//patente ya existe, no se puede dar de alta
		return false;
	else{
		//añado en la ultima posicion
		*c = 0;
		(*lista).ultimo=(*lista).ultimo+1;
	    (*lista).arr[(*lista).ultimo] = v;
	    return true;
	}
}

int bajaLSD(LSD *lista, char patente[], int condicion, vehiculo v, double *c){
    int posicion;
    int aux = 0;
    *c = 0;
    if(localizarLSD(*lista, v.patente, &posicion, c)){
    	if(condicion == 0 && compararVehiculos((*lista).arr[posicion], v))
    		aux = 1;

    	else{
    		if(condicion == 1){
    			do{
	                system("cls");
	                printf("Esta seguro que desea dar de baja al siguiente vehiculo:\n");
	                mostrarVehiculo((*lista).arr[posicion]);
	                printf("\n\n[1]Si\n[2]No\n");
	                scanf("%d",&aux);
	                getchar();
	            }while(aux!=1 && aux!=2);
    		}
    	}
    }
	if(aux == 1){
		//dando de baja
        if(posicion != (*lista).ultimo){
            swapVehiculo(&((*lista).arr[(*lista).ultimo]), &((*lista).arr[posicion]));
            *c = 1;
        }
        else
            *c = 0;

        strcpy((*lista).arr[(*lista).ultimo].patente,"");
        (*lista).ultimo=(*lista).ultimo-1;

        return true; //baja exitosa
    }
    else{
        if(aux==2)
            return -1;
        else
            return false;
    }
}

void mostrarLSD(LSD lista){
    int i;
	for (i = 0; i <= lista.ultimo; i++){
		printf("\n****************************\n");
		printf("Elemento #%d de %d", i+1, lista.ultimo+1);
		mostrarVehiculo(lista.arr[i]);
		printf("\nEnter para continuar\n");getchar();
	}
}

void ordenBurbuja(LSD *lista){
    int n = (*lista).ultimo;
    int corrimientos=0;
    int i,j;
    for (i=0; i<=n; i++)
        for (j=0; j<n-i; j++)
            if(strcmp((*lista).arr[j].patente,(*lista).arr[j+1].patente)>0){
                swapVehiculo(&((*lista).arr[j]), &((*lista).arr[j+1]));
                corrimientos++;
            }
    corrimientos*=2;
    printf("\nORDEN BURBUJA\n\nCantidad de corrimientos: %d\n",corrimientos);

}

void ordenInsercion(LSD *lista){
    vehiculo k;
    int n = (*lista).ultimo + 1;
    int i, j;
    int corrimientos=0;
    for (i=1; i<n; i++){
        copiarVehiculo((*lista).arr[i], &k);
        j = i - 1;
        while (j >= 0 && strcmp((*lista).arr[j].patente, k.patente)>0){
            copiarVehiculo((*lista).arr[j], &((*lista).arr[j+1]));
            j--;
            corrimientos++;
        }
        copiarVehiculo(k, &((*lista).arr[j+1]));

    }
    corrimientos*=2;
    printf("\nORDEN POR INSERCION\n\nCantidad de corrimientos: %d\n", corrimientos);
}

void copiarLSD(LSD original, LSD *nueva){
    initLSD(nueva);
    int i;
    for(i=0; i<=original.ultimo; i++){
        copiarVehiculo(original.arr[i], &((*nueva).arr[i]));
        (*nueva).ultimo = (*nueva).ultimo + 1;
    }
}

//LSO

void initLSO(LSO *lista){
    (*lista).ultimo = -1;
}

bool isFullLSO(LSO lista){
    return(lista.ultimo == (MAX-1));
}

bool isEmptyLSO(LSO lista){
    return(lista.ultimo == -1);
}

bool localizarLSO(LSO lista, char patente[], int *posicion, double *c){
    int i=0; *c=0;
    while((i<= lista.ultimo) && (strcmp(patente, lista.arr[i].patente) > 0)){
        i++;
        *c = *c+1;
    }
    *posicion = i;
    if((i <= lista.ultimo) && (strcmp(patente, lista.arr[i].patente) == 0)){
        *c = *c+1;
        return true;
    }
    else{
        if (i<=lista.ultimo)
            *c = *c+1;
        return false;
    }
}

bool perteneceLSO(LSO lista, char patente[], double *c){
	int aux; //variable auxiliar necesaria para que localizar funcione correctamente
	return localizarLSO(lista, patente, &aux, c);
}

vehiculo evocarLSO(LSO lista, char patente[], double *c){
	int posicion;
	vehiculo v;
	if(localizarLSO(lista, patente, &posicion, c))
		//el vehiculo localizado exitosamente es retornado
		return lista.arr[posicion];
	else{
		//retorno un vehiculo con patente invalida
		strcpy(v.patente, "0000000");
		return v;
	}
}

bool altaLSO(LSO *lista, vehiculo v, double *c){
	int posicion;
	if(localizarLSO(*lista, v.patente, &posicion, c))
		//patente ya existe, no se puede dar de alta
		return false;
	else{
		//hacer lugar para que vehiculo entre en lista.arr[posicion]
		(*lista).ultimo = (*lista).ultimo + 1;
		int i; *c = 0;
		for(i = (*lista).ultimo; i > posicion; i--){
			copiarVehiculo((*lista).arr[i-1], &((*lista).arr[i]));
			*c = *c + 1;
		}
        //inserta el nuevo vehiculo en la posicion donde fracaso la localizacion
		copiarVehiculo(v, &((*lista).arr[posicion]));
	    return true;
	}
}

int bajaLSO(LSO *lista, char patente[] ,int condicion, vehiculo v, double *c){
	int posicion;
    int aux = 0;
    if(localizarLSO(*lista, v.patente, &posicion, c)){
    	if(condicion == 0 && compararVehiculos((*lista).arr[posicion], v))
    		aux = 1;

    	else{
    		if(condicion == 1){
    			do{
	                system("cls");
	                printf("Esta seguro que desea dar de baja al siguiente vehiculo:\n");
	                mostrarVehiculo((*lista).arr[posicion]);
	                printf("\n\n[1]Si\n[2]No\n");
	                scanf("%d",&aux);
	                getchar();
	            }while(aux!=1 && aux!=2);
    		}
    	}
    }
	if(aux == 1){
		//dando de baja
        int i; *c = 0;
        for(i=posicion; i<(*lista).ultimo; i++){
            swapVehiculo(&(*lista).arr[i],&(*lista).arr[i+1]);
            *c = *c + 1;
        }
        strcpy((*lista).arr[(*lista).ultimo].patente,"");
        (*lista).ultimo=(*lista).ultimo-1;
        return true; //baja exitosa
    }
    else{
        if(aux==2)
            return -1;
        else
            return false;
    }
}


void mostrarLSO(LSO lista){
    int i;
	for (i = 0; i <= lista.ultimo; i++){
		printf("\n****************************\n");
		printf("Elemento #%d de %d", i+1, lista.ultimo+1);
		mostrarVehiculo(lista.arr[i]);
		printf("\nEnter para continuar\n");getchar();
	}
}

//LSOBT

void initLSOBT(LSOBT *lista){
    (*lista).ultimo = -1;
}

bool isFullLSOBT(LSOBT lista){
    return(lista.ultimo == (MAX-1));
}

bool isEmptyLSOBT(LSOBT lista){
    return(lista.ultimo == -1);
}

int localizarLSOBT(LSOBT lista, char patente[], int *posicion, double *c){
    int li = -1;
    int ls = lista.ultimo;
    int m = li + (ls-li)/2 + 1;
    *c = 0;
    while(li<ls){
        if(strcmp(patente, lista.arr[m].patente) == 0){
            *c = *c + 1;
            break;
        }
        else{
            if(strcmp(patente, lista.arr[m].patente) > 0)
                li = m;
            else
                ls = m-1;

            m = li + (ls-li)/2 + 1;
            *c = *c + 1;
        }
    }
    *posicion = m;

    return(li<ls);
}

bool perteneceLSOBT(LSOBT lista, char patente[], double *c){
	int aux; //variable auxiliar necesaria para que localizar funcione correctamente
	return localizarLSOBT(lista, patente, &aux, c);
}

vehiculo evocarLSOBT(LSOBT lista, char patente[], double *c){
	int posicion;
	vehiculo v;
	if(localizarLSOBT(lista, patente, &posicion, c))
		//el vehiculo localizado exitosamente es retornado
		return lista.arr[posicion];
	else{
		//retorno un vehiculo con patente invalida
		strcpy(v.patente, "0000000");
		return v;
	}
}

bool altaLSOBT(LSOBT *lista, vehiculo v, double *c){
	int posicion;
	if(localizarLSOBT(*lista, v.patente, &posicion, c))
		//patente ya existe, no se puede dar de alta
		return false;
	else{
		//hacer lugar para que vehiculo entre en lista.arr[posicion]
		(*lista).ultimo = (*lista).ultimo + 1;
		int i; *c = 0;
		for(i = (*lista).ultimo; i > posicion; i--){
			copiarVehiculo((*lista).arr[i-1], &((*lista).arr[i]));
			*c = *c + 1;
        }
        //inserta el nuevo vehiculo en la posicion donde fracaso la localizacion
		copiarVehiculo(v, &((*lista).arr[posicion]));
	    return true;
	}
}

int bajaLSOBT(LSOBT *lista, char patente[] ,int condicion, vehiculo v, double *c){
	int posicion;
    int aux = 0;
    if(localizarLSOBT(*lista, v.patente, &posicion, c)){
    	if(condicion == 0 && compararVehiculos((*lista).arr[posicion], v))
    		aux = 1;

    	else{
    		if(condicion == 1){
    			do{
	                system("cls");
	                printf("Esta seguro que desea dar de baja al siguiente vehiculo:\n");
	                mostrarVehiculo((*lista).arr[posicion]);
	                printf("\n\n[1]Si\n[2]No\n");
	                scanf("%d",&aux);
	                getchar();
	            }while(aux!=1 && aux!=2);
    		}
    	}
    }

	if(aux == 1){

		//dando de baja
        int i; *c = 0;
        for(i=posicion; i<(*lista).ultimo; i++){
            swapVehiculo(&(*lista).arr[i],&(*lista).arr[i+1]);
            *c = *c + 1;
        }
        strcpy((*lista).arr[(*lista).ultimo].patente,"");
        (*lista).ultimo=(*lista).ultimo-1;
        return true; //baja exitosa
    }
    else{
        if(aux==2)
            return -1;
        else
            return false;
    }
}

void mostrarLSOBT(LSOBT lista){
    int i;
	for (i = 0; i <= lista.ultimo; i++){
		printf("\n****************************\n");
		printf("Elemento #%d de %d", i+1, lista.ultimo+1);
		mostrarVehiculo(lista.arr[i]);
		printf("\nEnter para continuar\n");getchar();
	}
}

//Operaciones de Vehiculo

vehiculo scanDatos(){
	char patente[7];
    char marca[60];
    int anio;
    char dueno[50];
    char telefono[15];
    char servicios[70];
    float monto;
    char fecha[10];

    system("cls");
    printf("\tCarga de Vehiculo:\n ");

    //Ingreso de patente
    printf("\nPatente: ");
	scanf("%[^\n]", patente); getchar();
    while(strlen(patente)!= 7){
        printf("\nLa patente debe tener una longitud de 7 caracteres\nReintente: ");
        scanf("%[^\n]", patente); getchar();
    }
    strupr(patente);

    //Ingreso de Marca y Modelo
    printf("\nMarca y Modelo: ");
    scanf("%[^\n]", marca); getchar();
    while(strlen(marca)>60){
        printf("\nError, capacidad maxima de caracteres (60) excedida. Reintente: ");
        scanf("%[^\n]",marca); getchar();
	}

	//Ingreso año de fabricacion
    printf("\nAnio de fabricacion: ");
    scanf("%d",&anio); getchar();
    while (anio<=0){
        printf("\nError, se ingreso un valor menor igual a 0. Reintente: ");
	    scanf("%d",&anio); getchar();
	}

	//Ingreso de nombre del dueno
    printf("\nNombre del dueno: ");
    fflush(stdin);
    scanf("%[^\n]",dueno); getchar();
	while(strlen(dueno)>50){
        printf("\nError, capacidad maxima de caracteres (50) excedida. Reintente: ");
        scanf("%[^\n]",dueno); getchar();
	}

	//Ingreso numero de telefono
    printf("\nNumero de telefono: ");
    scanf("%[^\n]",telefono); getchar();
    while(strlen(telefono)>15){
        printf("\nError, capacidad maxima de caracteres (15) excedida. Reintente: ");
        scanf("%[^\n]",telefono); getchar();
    }

    //Ingreso de servicios realizados
    printf("\nServicios realizados: ");
    scanf("%[^\n]",servicios); getchar();
    while(strlen(servicios)>70){
        printf("\nError, capacidad maxima de caracteres (70) excedida. Reintente: ");
		scanf("%[^\n]",servicios); getchar();
	}

	//Ingreso monto
	printf("\nMonto: $ ");
    scanf("%f", &monto); getchar();
    while (monto<=0){
	    printf("\nError, se ingreso un valor menor igual a 0. Reintente: ");
        scanf("%f", &monto); getchar();
 	}

 	//Ingreso fecha
	printf("\nFecha de realizacion(dd-mm-aaaa): ");
    scanf("%[^\n]", fecha); getchar();
    while(strlen(fecha)!=10){
        printf("\nError, la fecha debe tener una longitud de 10 caracteres. Reintente: ");
        scanf("%[^\n]", fecha); getchar();
    }

    return nuevoVehiculo(patente, marca, anio, dueno, telefono, servicios, monto, fecha);
}

vehiculo nuevoVehiculo(char patente[], char marca[], int anio, char dueno[], char telefono[], char servicios[], float monto, char fecha[]){

	vehiculo v;
    strcpy(v.patente, patente);
    strcpy(v.marca, marca);
	v.anio = anio;
	strcpy(v.dueno, dueno);
	strcpy(v.telefono, telefono);
	strcpy(v.servicios, servicios);
	v.monto = monto;
	strcpy(v.fecha, fecha);
	strcpy(v.marca, marca);
	return v;
}

void mostrarVehiculo(vehiculo v){
    printf("\n****************************");
    printf("\nPatente: %s",v.patente);
    printf("\nMarca y modelo: %s",v.marca);
    printf("\nAnio de fabricacion: %d",v.anio);
    printf("\nNombre del dueno: %s",v.dueno);
    printf("\nNumero de telefono: %s",v.telefono);
    printf("\nServicios realizados: %s",v.servicios);
    printf("\nMonto: $%f",v.monto);
    printf("\nFecha: %s",v.fecha);
    printf("\n****************************\n");
}

bool compararVehiculos(vehiculo v1, vehiculo v2){
	bool samePatente = strcmp(v1.patente, v2.patente)==0;
	bool sameMarca = strcmp(v1.marca, v2.marca)==0;
	bool sameAnio = v1.anio==v2.anio;
	bool sameDueno = strcmp(v1.dueno, v2.dueno)==0;
	bool sameTelefono = strcmp(v1.telefono, v2.telefono)==0;
	bool sameServicios = strcmp(v1.servicios, v2.servicios)==0;
	bool sameMonto = v1.monto==v2.monto;
	bool sameFecha = strcmp(v1.fecha, v2.fecha)==0;
	//con que algo no haya sido igual, sera sufiente para que return sea false
	return(samePatente && sameMarca && sameAnio && sameDueno && sameTelefono && sameServicios && sameMonto && sameFecha);
}

void copiarVehiculo(vehiculo v1, vehiculo *v2){
	strcpy((*v2).patente, v1.patente);
	strcpy((*v2).marca, v1.marca);
	(*v2).anio = v1.anio;
	strcpy((*v2).dueno, v1.dueno);
	strcpy((*v2).telefono, v1.telefono);
	strcpy((*v2).servicios, v1.servicios);
	(*v2).monto = v1.monto;
	strcpy((*v2).fecha, v1.fecha);
}

void swapVehiculo(vehiculo *v1, vehiculo *v2){
    vehiculo aux;
    copiarVehiculo(*v1, &aux);
    copiarVehiculo(*v2, v1);
    copiarVehiculo(aux, v2);
}

//Funciones de pila

void initPila(pila *p){
    (*p).tope=-1;
}

void push(pila *p, double n){
    if(!(isFull(*p))){
        (*p).tope++;
        (*p).nums[(*p).tope]=n;
    }
}

double pop(pila *p){
    //solo llamada por el promedio
    double aux = (*p).nums[(*p).tope];
    (*p).tope--;
    return(aux);
}

int isFull(pila p){
    if (p.tope==(MAX-1)){
        return(1);
    }
    else{
        return(0);
    }
}

int isEmpty (pila p){
    if(p.tope==-1){
        return(1);
    }
    else{
        return(0);
    }
}

double copy(pila p){
    return(p.nums[p.tope]);
}

double getEstadisticas(pila p, double* max, double* prom){
    double sumador=0, aux=0, i=0, maximo=0, promedio=0;

    while(!isEmpty(p)){
        aux = pop(&p);
        if(aux>maximo)
            maximo=aux;
        sumador+=aux;
        i++;
    }
    *max = maximo;

    if(i>0)
        promedio=sumador/i;

    *prom = promedio;
}


//Comparacion de estructuras
void compararEstructuras(LSD *lsd, LSO *lso, LSOBT *lsobt){
    FILE *fp;
    if((fp = fopen("Operaciones.txt","r"))==NULL){
        system("cls");
        printf("Error, no se pudo abrir el archivo.\n");
    }
    else{
        vehiculo vaux;
        int op;
        double *t; t=malloc(sizeof(double));
        double *c; c=malloc(sizeof(double));


                //PILAS Y FLOATS DE COSTOS

        pila costosAltaLSD, costosAltaLSO, costosAltaLSOBT,
        costosBajaLSD, costosBajaLSO, costosBajaLSOBT,
        costosLocExitosaLSD, costosLocExitosaLSO, costosLocExitosaLSOBT,
        costosLocFracasoLSD, costosLocFracasoLSO, costosLocFracasoLSOBT;

        initPila(&costosAltaLSD); initPila(&costosAltaLSO); initPila(&costosAltaLSOBT);
        initPila(&costosBajaLSD); initPila(&costosBajaLSO); initPila(&costosBajaLSOBT);
        initPila(&costosLocExitosaLSD); initPila(&costosLocExitosaLSO); initPila(&costosLocExitosaLSOBT);
        initPila(&costosLocFracasoLSD); initPila(&costosLocFracasoLSO); initPila(&costosLocFracasoLSOBT);

        //floats promedio
        double promAltaLSO, promAltaLSD, promAltaLSOBT,
        promBajaLSO, promBajaLSD, promBajaLSOBT,
        promLE_LSO, promLE_LSD, promLE_LSOBT,
        promLF_LSO, promLF_LSD, promLF_LSOBT;
        //floats maximo
        double maxAltaLSO, maxAltaLSD, maxAltaLSOBT,
        maxBajaLSO, maxBajaLSD, maxBajaLSOBT,
        maxLE_LSO, maxLE_LSD, maxLE_LSOBT,
        maxLF_LSO, maxLF_LSD, maxLF_LSOBT;

        while(!feof(fp) && !isFullLSD(*lsd) && !isFullLSO(*lso) && !isFullLSOBT(*lsobt)){
            fscanf(fp,"%d\n",&op);
            fscanf(fp,"%[^\n]\n",vaux.patente);
            strupr(vaux.patente);
            if(op!=3){
                fscanf(fp,"%[^\n]\n",vaux.marca);
                fscanf(fp,"%d\n",&vaux.anio);
                fscanf(fp,"%[^\n]\n",vaux.dueno);
                fscanf(fp,"%[^\n]\n",vaux.telefono);
                fscanf(fp,"%[^\n]\n",vaux.servicios);
                fscanf(fp,"%f\n",&vaux.monto);
                fscanf(fp,"%[^\n]\n",vaux.fecha);
            }
            switch(op){

            case 1: //ALTAS

            //LSD
                if(altaLSD(lsd, vaux, c)){
                    push(&costosAltaLSD, *c);
                }


            //LSO
                if(altaLSO(lso, vaux,c)){
                    push(&costosAltaLSO, *c);
                }


            //LSOBT
                if(altaLSOBT(lsobt, vaux,c)){
                    push(&costosAltaLSOBT, *c);
                }

                break;

            case 2: //BAJAS

            //LSD
                if(bajaLSD(lsd,"",0, vaux, c)){
                    push(&costosBajaLSD, *c);
                }

            //LSO
                if(bajaLSO(lso,"",0, vaux, c)){
                    push(&costosBajaLSO, *c);
                }

            //LSOBT
                if(bajaLSOBT(lsobt,"",0, vaux, c)){
                    push(&costosBajaLSOBT, *c);
                }

                break;

            case 3: //CONSULTAS

            //LSD
                if(strcmp(evocarLSD(*lsd, vaux.patente, c).patente, vaux.patente) == 0){
                    push(&costosLocExitosaLSD, *c);
                }
                else{
                    push(&costosLocFracasoLSD, *c);
                }

            //LSO
                if(strcmp(evocarLSO(*lso, vaux.patente, c).patente, vaux.patente) == 0){
                    push(&costosLocExitosaLSO, *c);
                }
                else{
                    push(&costosLocFracasoLSO, *c);
                }

            //LSOBT
                if(strcmp(evocarLSOBT(*lsobt, vaux.patente, c).patente, vaux.patente) == 0){
                    push(&costosLocExitosaLSOBT, *c);
                }
                else{
                    push(&costosLocFracasoLSOBT, *c);
                }
                break;
            }
        }

        getEstadisticas(costosAltaLSD, &maxAltaLSD, &promAltaLSD);
        getEstadisticas(costosAltaLSO, &maxAltaLSO, &promAltaLSO);
        getEstadisticas(costosAltaLSOBT, &maxAltaLSOBT, &promAltaLSOBT);

        getEstadisticas(costosBajaLSD, &maxBajaLSD, &promBajaLSD);
        getEstadisticas(costosBajaLSO, &maxBajaLSO, &promBajaLSO);
        getEstadisticas(costosBajaLSOBT, &maxBajaLSOBT, &promBajaLSOBT);

        getEstadisticas(costosLocExitosaLSD, &maxLE_LSD, &promLE_LSD);
        getEstadisticas(costosLocFracasoLSD, &maxLF_LSD, &promLF_LSD);
        getEstadisticas(costosLocExitosaLSO, &maxLE_LSO, &promLE_LSO);
        getEstadisticas(costosLocFracasoLSO, &maxLF_LSO, &promLF_LSO);
        getEstadisticas(costosLocExitosaLSOBT, &maxLE_LSOBT, &promLE_LSOBT);
        getEstadisticas(costosLocFracasoLSOBT, &maxLF_LSOBT, &promLF_LSOBT);

        //print costos

        printf("/////////////////////////////////////////////////////////////////////////////////\n\n");

        printf("\t\t\t\tLISTA SECUENCIAL DESORDENADA\n\n");

        printf("LOCALIZACION: [Cantidad de celdas consultadas]\n\n");

        printf("\t.Costo MEDIO en localizacion EXITOSA:\t\t%f\n", promLE_LSD);
        printf("\t.Costo MAXIMO en localizacion EXITOSA:\t\t%d\n\n", (int)maxLE_LSD);

        printf("\t.Costo MEDIO en localizacion FRACASADA:\t\t%f\n", promLF_LSD);
        printf("\t.Costo MAXIMO en localizacion FRACASADA:\t%d\n\n", (int)maxLF_LSD);

        printf("ALTA: [Cantidad de corrimientos]\n\n");

        printf("\t.Costo MEDIO en el alta:\t%f\n", promAltaLSD);
        printf("\t.Costo MAXIMO en el alta:\t%d\n\n", (int)maxAltaLSD);

        printf("BAJA: [Cantidad de corrimientos]\n\n");

        printf("\t.Costo MEDIO en la baja:\t%f\n", promBajaLSD);
        printf("\t.Costo MAXIMO en la baja:\t%d\n\n", (int)maxBajaLSD);

        printf("/////////////////////////////////////////////////////////////////////////////////\n\n");

        printf("\t\t\t\tLISTA SECUENCIAL ORDENADA\n\n");

        printf("LOCALIZACION: [Cantidad de celdas consultadas]\n\n");

        printf("\t.Costo MEDIO en localizacion EXITOSA:\t\t%f\n", promLE_LSO);
        printf("\t.Costo MAXIMO en localizacion EXITOSA:\t\t%d\n\n", (int)maxLE_LSO);

        printf("\t.Costo MEDIO en localizacion FRACASADA:\t\t%f\n", promLF_LSO);
        printf("\t.Costo MAXIMO en localizacion FRACASADA:\t%d\n\n", (int)maxLF_LSO);

        printf("ALTA: [Cantidad de corrimientos]\n\n");

        printf("\t.Costo MEDIO en el alta:\t%f\n", promAltaLSO);
        printf("\t.Costo MAXIMO en el alta:\t%d\n\n", (int)maxAltaLSO);

        printf("BAJA: [Cantidad de corrimientos]\n\n");

        printf("\t.Costo MEDIO en la baja:\t%f\n", promBajaLSO);
        printf("\t.Costo MAXIMO en la baja:\t%d\n\n", (int)maxBajaLSO);

        printf("/////////////////////////////////////////////////////////////////////////////////\n\n");

        printf("\tLISTA SECUENCIAL ORDENADA CON BUSQUEDA BINARIA POR TRISECCION\n\n");

        printf("LOCALIZACION: [Cantidad de celdas consultadas]\n\n");

        printf("\t.Costo MEDIO en localizacion EXITOSA:\t\t%f\n", promLE_LSOBT);
        printf("\t.Costo MAXIMO en localizacion EXITOSA:\t\t%d\n\n", (int)maxLE_LSOBT);

        printf("\t.Costo MEDIO en localizacion FRACASADA:\t\t%f\n", promLF_LSOBT);
        printf("\t.Costo MAXIMO en localizacion FRACASADA:\t%d\n\n", (int)maxLF_LSOBT);

        printf("ALTA: [Cantidad de corrimientos]\n\n");

        printf("\t.Costo MEDIO en el alta:\t%f\n", promAltaLSOBT);
        printf("\t.Costo MAXIMO en el alta:\t%d\n\n", (int)maxAltaLSOBT);

        printf("BAJA: [Cantidad de corrimientos]\n\n");

        printf("\t.Costo MEDIO en la baja:\t%f\n", promBajaLSOBT);
        printf("\t.Costo MAXIMO en la baja:\t%d\n\n", (int)maxBajaLSOBT);

        void free(void *t);
    }
    fclose(fp);
}
