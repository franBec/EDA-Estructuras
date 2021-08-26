//GRUPO 3
//BECVORT, FRANCO
//MARTINEZ, ROCIO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <limits.h>

#define MAX 300

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
bool localizarLSD(LSD lista, char patente[], int *posicion, double *t);
bool perteneceLSD(LSD lista, char patente[], double *t);
vehiculo evocarLSD(LSD lista, char patente[]);
bool altaLSD(LSD *lista, vehiculo v, double *t);
int bajaLSD(LSD *lista, char patente[],int condicion,vehiculo v,double *t);
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
bool localizarLSO(LSO lista, char patente[], int *posicion, double *t);
bool perteneceLSO(LSO lista, char patente[],double *t);
vehiculo evocarLSO(LSO lista, char patente[]);
bool altaLSO(LSO *lista, vehiculo v, double *t);
int bajaLSO(LSO *lista, char patente[],int condicion,vehiculo v,double *t);
void mostrarLSO(LSO lista);

 //PILA - Usada para administrar tiempos y costos

typedef struct{
    double nums[MAX];
    int tope;
}pila;

//Operaciones sobre la Pila

void initPila(pila *p);
void push(pila *p, double n);
double pop(pila *p);
int isFull(pila p);
int isEmpty (pila p);
double copy(pila p);
double getEstadisticas(pila p, double* max, double* prom);


                    //OPERACIONES DE TIEMPOS Y COSTOS

double tiempoDeOperacion(LARGE_INTEGER *a, LARGE_INTEGER *b);
void compararEstructuras(LSD *lsd, LSO *lso);

					//MAIN
int main(){
    system("color 0A");
    LSD lsd;initLSD(&lsd);
    LSO lso;initLSO(&lso);
    int menu1, menu2, menu3;


    char patente[8];
    double t;
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
                                system("cls");
                                printf("Error: no hay mas lugar en la lista\n");
                                system("pause");
                            }
                            else{
                                if(altaLSD(&lsd,scanDatos(), &t)){
                                    system("cls");
                                    printf("Exito al cargar vehiculo\n");
                                    system("pause");
                                }
                                else{
                                    system("cls");
                                    printf("Error: patente repetida\n");
                                    system("pause");
                                }
                            }
                            break;
                        case 2: //Eliminar vehiculo existente
                            if(isEmptyLSD(lsd)){
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

                                int rta = bajaLSD(&lsd, patente,1, v, &t);
                                switch(rta){
                                case 1:
                                    system("cls");
                                    printf("Eliminacion exitosa\n");
                                    system("pause");
                                    break;
                                case 2:
                                    system("cls");
                                    printf("Baja cancelada por el usuario\n");
                                    system("pause");
                                    break;
                                case 3:
                                    system("cls");
                                    printf("No existe el vehiculo\n");
                                    system("pause");
                                    break;
                                }
                            }
                            break;
                        case 3: //Consultar datos de un vehiculo
                            if(isEmptyLSD(lsd)){
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

                                v = evocarLSD(lsd, patente);
                                if(strcmp(v.patente, "0000000")==0){
                                    system("cls");
                                    printf("No existe un vehiculo con la patente %s en el sistema\n", patente);
                                    system("pause");
                                }
                                else{
                                    system("cls");
                                    mostrarVehiculo(v);
                                    system("pause");
                                }
                            }
                            break;
                        case 4: //Determinar si un vehiculo ha realizado servicio mecanico
                            if(isEmptyLSD(lsd)){
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

                                if(perteneceLSD(lsd, patente, &t))
                                {
                                    system("cls");
                                    printf("El vehiculo con la patente %s esta en el sistema\n", patente);
                                    system("pause");
                                }
                                else
                                {
                                    system("cls");
                                    printf("No existe un vehiculo con la patente %s en el sistema\n", patente);
                                    system("pause");
                                }
                            }
                            break;
                        case 5: //Mostrar estructura
                            if(isEmptyLSD(lsd)){
                                system("cls");
                                printf("Error: no hay vehiculos en el sistema\n");
                                system("pause");
                            }
                            else mostrarLSD(lsd);
                            break;
                        case 6: //Comparar Odenamiento: Burbuja e Insercion
                            if(isEmptyLSD(lsd)){
                                        system("cls");
                                        printf("Error: no se puede realizar la operacion seleccionada con la LSD vacia\n");
                                        system("pause");
                            }
                            else{
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
                                system("cls");
                                printf("Error: no hay mas lugar en la lista\n");
                                system("pause");
                            }
                            else{
                                if(altaLSO(&lso, scanDatos(), &t)){
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
                                int rta = bajaLSO(&lso, patente,1, v, &t);
                                switch(rta){
                                case 1:
                                    //exito en la baja, informa por pantalla
                                    system("cls");
                                    printf("Eliminacion exitosa\n");
                                    system("pause");
                                    break;
                                case 2:
                                    //se decidio no dar de baja, informa por pantalla
                                    system("cls");
                                    printf("Baja cancelada por el usuario\n");
                                    system("pause");
                                    break;
                                case 3:
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

                                v = evocarLSO(lso, patente);
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

                                if(perteneceLSO(lso, patente, &t)){
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
                case 0: //Volver
                    break;
                default:
                    menu2=-1;
                }
            }
            while(menu2 != 0);
            break;
        case 2: //Comparacion de Estructuras
            if(!isEmptyLSD(lsd) || !isEmptyLSO(lso)){
                int aux=0;
                do{
                    system("cls");
                    printf("Alguna de las estructuras no se encuentran vacias. Desea vaciarlas para continuar?\n\n[1] Si\n[2] No\n");
                    scanf("%d", &aux);
                }
                while(aux!=1 && aux!=2);
                if(aux==1){
                    initLSD(&lsd); initLSO(&lso); //initLSOBT(&lsobt);
                    system("cls");
                    compararEstructuras(&lsd, &lso);
                    system("pause");
                }
            }
            else{
                system("cls");
                compararEstructuras(&lsd, &lso);
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

bool localizarLSD(LSD lista, char patente[], int *posicion, double *t){
    int i=0;
    LARGE_INTEGER t_ini, t_fin;
    QueryPerformanceCounter(&t_ini);
    while((i <= lista.ultimo) && (strcmp(patente, lista.arr[i].patente) != 0)){
        i = i+ 1;
    }
    *posicion = i;
    QueryPerformanceCounter(&t_fin);
    *t = tiempoDeOperacion(&t_fin, &t_ini);

    if(strcmp(patente, lista.arr[i].patente) == 0)
    return ((i <= lista.ultimo) && (strcmp(patente, lista.arr[i].patente) == 0));
}


bool perteneceLSD(LSD lista, char patente[], double *t){
    int aux; //variable necesaria para que localizar funcione correctamente
	return localizarLSD(lista, patente, &aux, t);
}

vehiculo evocarLSD(LSD lista, char patente[]){
	int posicion;
	vehiculo v;
	double t; //variables necesarias para que localizar funcione correctamente
	if(localizarLSD(lista, patente, &posicion, &t))
		//el vehiculo localizado exitosamente es retornado
		return lista.arr[posicion];
	else{
		//retorno un vehiculo con patente invalida
		strcpy(v.patente, "0000000");
		return v;
	}
}

bool altaLSD(LSD *lista, vehiculo v, double *t){
	int posicion;
	if(localizarLSD(*lista, v.patente, &posicion, t))
		//patente ya existe, no se puede dar de alta
		return false;
	else{
		//añado en la ultima posicion
		(*lista).ultimo=(*lista).ultimo+1;
	    (*lista).arr[(*lista).ultimo] = v;
	    return true;
	}
}

int bajaLSD(LSD *lista, char patente[], int condicion, vehiculo v, double *t){
    if (condicion == 1){
        //baja sin lectura de archivo
        int posicion, aux;
        if(localizarLSD(*lista, patente, &posicion, t)){
            //vehiculo se encontro, vamos a preguntar si esta seguro antes de seguir
            do{
                system("cls");
                printf("Esta seguro que desea dar de baja al siguiente vehiculo:\n");
                mostrarVehiculo((*lista).arr[posicion]);
                printf("\n\n[1]Si\n[2]No\n");
                scanf("%d",&aux);
                getchar();
            }
            while(aux!=1 && aux!=2);
            if(aux==1)
            {
                //dando de baja
                swapVehiculo(&((*lista).arr[(*lista).ultimo]), &((*lista).arr[posicion]));
                strcpy((*lista).arr[(*lista).ultimo].patente,"");
                (*lista).ultimo = (*lista).ultimo - 1;
                return 1; //baja exitosa
            }
            else
                return 2; //se decidio no darle de baja
        }
        else
            return 3; //patente no se encontro
    }
    else{
        //baja con lectura de archivo
        int posicion;
        if(localizarLSD(*lista, v.patente, &posicion, t)){
            //la patente existe, se verifica que el vehiculo a eliminar sea el deseado
            if(compararVehiculos((*lista).arr[posicion], v)){

                if(posicion != (*lista).ultimo){
                    swapVehiculo(&((*lista).arr[(*lista).ultimo]), &((*lista).arr[posicion]));
                }
                else

                strcpy((*lista).arr[(*lista).ultimo].patente,"");
                (*lista).ultimo=(*lista).ultimo-1;
                return true; //baja exitosa
            }
        }
        else
            return false; //patente no se encontro o comparar vehiculo fallo
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
    int n = (*lista).ultimo; //me simplifica mucho la sintaxis dentro de las iteraciones
    int corrimientos=0;
    int i,j;
    for (i=0; i<=n; i++)
        for (j=0; j<n-i; j++)
            if(strcmp((*lista).arr[j].patente,(*lista).arr[j+1].patente)>0){
                swapVehiculo(&((*lista).arr[j]), &((*lista).arr[j+1]));
                corrimientos++;
            }
    printf("\nORDEN BURBUJA\n\nCantidad de corrimientos: %d\n", corrimientos);

}

void ordenInsercion(LSD *lista){
    vehiculo k;
    int n = (*lista).ultimo + 1; //me simplifica mucho la sintaxis dentro de las iteraciones
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

bool localizarLSO(LSO lista, char patente[], int *posicion, double *t){
    int i=0;
    LARGE_INTEGER t_ini, t_fin;
    QueryPerformanceCounter(&t_ini);
    while((i<= lista.ultimo) && (strcmp(patente, lista.arr[i].patente) > 0)){
        i++;
    }
    *posicion = i;
    QueryPerformanceCounter(&t_fin);
    *t = tiempoDeOperacion(&t_fin, &t_ini);
    if((i <= lista.ultimo) && (strcmp(patente, lista.arr[i].patente) == 0)){
        return true;
    }
    else{
        if (i<=lista.ultimo)
        return false;
    }
}

bool perteneceLSO(LSO lista, char patente[], double *t){
	int aux; //variable auxiliar necesaria para que localizar funcione correctamente
	return localizarLSO(lista, patente, &aux, t);
}

vehiculo evocarLSO(LSO lista, char patente[]){
	int posicion;
	vehiculo v;
	double t; //variables auxiliares necesarias para que localizar funcione correctamente
	if(localizarLSO(lista, patente, &posicion, &t))
		//el vehiculo localizado exitosamente es retornado
		return lista.arr[posicion];
	else{
		//retorno un vehiculo con patente invalida
		strcpy(v.patente, "0000000");
		return v;
	}
}

bool altaLSO(LSO *lista, vehiculo v, double *t){
	int posicion;
	if(localizarLSO(*lista, v.patente, &posicion, t))
		//patente ya existe, no se puede dar de alta
		return false;
	else{
		//hacer lugar para que vehiculo entre en lista.arr[posicion]
		(*lista).ultimo = (*lista).ultimo + 1;
		int i;
		for(i = (*lista).ultimo; i > posicion; i--){
			copiarVehiculo((*lista).arr[i-1], &((*lista).arr[i]));
		}
        //inserta el nuevo vehiculo en la posicion donde fracaso la localizacion
		copiarVehiculo(v, &((*lista).arr[posicion]));
	    return true;
	}
}

int bajaLSO(LSO *lista, char patente[] ,int condicion, vehiculo v, double *t){
	if (condicion == 1){
        //baja sin lectura de archivo
        int posicion, aux;
        if(localizarLSO(*lista, patente, &posicion, t)){
            //vehiculo se encontro, vamos a preguntar si esta seguro antes de seguir
            do{
                system("cls");
                printf("Esta seguro que desea dar de baja al siguiente vehiculo:\n");
                mostrarVehiculo((*lista).arr[posicion]);
                printf("\n\n[1]Si\n[2]No\n");
                scanf("%d",&aux);
                getchar();
            }
            while(aux!=1 && aux!=2);
            if(aux==1){
                //dando de baja
                int i;
                for(i=posicion; i<(*lista).ultimo; i++)
                    swapVehiculo(&(*lista).arr[i],&(*lista).arr[i+1]);
                strcpy((*lista).arr[(*lista).ultimo].patente,"");
                (*lista).ultimo=(*lista).ultimo-1;
                return 1; //baja exitosa
            }
            else
                return 2; //se decidio no darle de baja
        }
        else
            return 3; //patente no se encontro
    }
    else{
        //baja con lectura de archivo
        int posicion;
        if(localizarLSO(*lista, v.patente, &posicion, t)){
            //la patente existe, se verifica que el vehiculo a eliminar sea el deseado
            if(compararVehiculos((*lista).arr[posicion], v)){
                //dando de baja
                int i;
                for(i=posicion; i<(*lista).ultimo; i++){
                    swapVehiculo(&(*lista).arr[i],&(*lista).arr[i+1]);
                }
                strcpy((*lista).arr[(*lista).ultimo].patente,"");
                (*lista).ultimo=(*lista).ultimo-1;
                return true; //baja exitosa
            }
        }
        else
            return false; //patente no se encontro o comparar fallo
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

//Funcion auxiliar para calcular tiempos
double tiempoDeOperacion(LARGE_INTEGER *a, LARGE_INTEGER *b){
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

//Comparacion de estructuras
void compararEstructuras(LSD *lsd, LSO *lso){
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

                //PILAS Y FLOATS DE TIEMPOS


        pila tiemposExitosLSD, tiemposFracasosLSD,
        tiemposExitosLSO, tiemposFracasosLSO;

        initPila(&tiemposExitosLSD); initPila(&tiemposFracasosLSD);
        initPila(&tiemposExitosLSO); initPila(&tiemposFracasosLSO);

        //floats promedio
        double promLocExitosaLSD, promLocFracasoLSD, promLocExitosaLSO,
        promLocFracasoLSO;
        //floats maximos
        double maxLocExitosaLSD, maxLocFracasoLSD, maxLocExitosaLSO,
        maxLocFracasoLSO;

        while(!feof(fp) && !isFullLSD(*lsd) && !isFullLSO(*lso)){
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
                if(altaLSD(lsd, vaux, t)){
                    push(&tiemposFracasosLSD, *t);
                }

                else
                    push(&tiemposExitosLSD, *t);


            //LSO
                if(altaLSO(lso, vaux, t)){
                    push(&tiemposFracasosLSO, *t);
                }

                else
                    push(&tiemposExitosLSO, *t);


                break;

            case 2: //BAJAS

            //LSD
                if(bajaLSD(lsd,"",2, vaux, t)){
                    push(&tiemposExitosLSD, *t);
                }

                else
                    push(&tiemposFracasosLSD, *t);


            //LSO
                if(bajaLSO(lso,"",2, vaux, t)){
                    push(&tiemposExitosLSO, *t);
                }

                else
                    push(&tiemposFracasosLSO, *t);

                break;

            case 3: //CONSULTAS

            //LSD
                if(strcmp(evocarLSD(*lsd, vaux.patente).patente, vaux.patente) == 0){
                    push(&tiemposExitosLSD, *t);
                }
                else{
                    push(&tiemposFracasosLSD, *t);
                }

            //LSO
                if(strcmp(evocarLSO(*lso, vaux.patente).patente, vaux.patente) == 0){
                    push(&tiemposExitosLSO, *t);
                }
                else{
                    push(&tiemposFracasosLSO, *t);
                }

                break;
            }
        }

        //calculo de estadisticas

        getEstadisticas(tiemposExitosLSD, &maxLocExitosaLSD, &promLocExitosaLSD);
        getEstadisticas(tiemposFracasosLSD, &maxLocFracasoLSD, &promLocFracasoLSD);

        getEstadisticas(tiemposExitosLSO, &maxLocExitosaLSO, &promLocExitosaLSO);
        getEstadisticas(tiemposFracasosLSO, &maxLocFracasoLSO, &promLocFracasoLSO);


        //print tiempos
        printf("\t\t\t\tLISTA SECUENCIAL DESORDENADA\n\n");
        printf("Tiempo promedio de Localizacion Exitosa:\t%.16g milliseconds\n", promLocExitosaLSD * 1000.0);
        printf("Tiempo maximo de Localizacion Exitosa:\t\t%.16g milliseconds\n\n", maxLocExitosaLSD * 1000.0);
        printf("Tiempo promedio de Localizacion Fracasada:\t%.16g milliseconds\n", promLocFracasoLSD * 1000.0);
        printf("Tiempo maximo de Localizacion Fracasada:\t%.16g milliseconds\n\n", maxLocFracasoLSD * 1000.0);

        printf("\t\t\t\tLISTA SECUENCIAL ORDENADA\n\n");
        printf("Tiempo promedio de Localizacion Exitosa:\t%.16g milliseconds\n", promLocExitosaLSO * 1000.0);
        printf("Tiempo maximo de Localizacion Exitosa:\t\t%.16g milliseconds\n\n", maxLocExitosaLSO * 1000.0);
        printf("Tiempo promedio de Localizacion Fracasada:\t%.16g milliseconds\n", promLocFracasoLSO * 1000.0);
        printf("Tiempo maximo de Localizacion Fracasada:\t%.16g milliseconds\n\n", maxLocFracasoLSO * 1000.0);

        void free(void *t);
        void free(void *c);
    }
    fclose(fp);
}
