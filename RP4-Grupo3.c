//GRUPO 3
//BECVORT, FRANCO
//MARTINEZ, ROCIO

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

					//#defines y structs

//bool
typedef int bool;
#define true 1
#define false 0

//maxima cantidad de vehiculos
#define MAX 300

//FACTOR_RAC = primo mas cercano de 300/0.82
#define FACTOR_RAC 367

//FACTOR_RS = primo mas cercado de 300/1.9
#define FACTOR_RS 158

                    //VEHICULO

//Estructura vehiculo
typedef struct{
    char patente[8];		//XX111XX
    char marca[61];
    int anio;               //int positivo
    char dueno[51];
    char telefono[16];
    char servicios[71];
    float monto;			//float positivo
    char fecha[11];			//AAAA-MM-DD
}vehiculo;

//Operaciones sobre vehiculos

//todos los printf y scanf con controles para armar un vehiculo
vehiculo scanDatos();

//devuelve un vehiculo con las caracteristicas pasadas por parametro
vehiculo nuevoVehiculo(char patente[], char modelo[], int anio, char dueno[], char telefono[], char servicios[], float monto, char fecha[]);

//muestra toda la info de un vehiculo por pantalla
void mostrarVehiculo(vehiculo v);

//compara si dos vehiculos son exactanente iguales en todas sus características
bool compararVehiculos(vehiculo v1, vehiculo v2);

//copia toda la info de un vehiculo v1 a un vehiculo v2
void copiarVehiculo(vehiculo v1, vehiculo *v2);

//intercambia la info de los vechiculos v1 y v2 entre ellos
void swapVehiculo(vehiculo *v1, vehiculo *v2);

					//RAC

typedef struct celdaRAC{
	vehiculo data;
	int isVirgen; //-1 = virgen, 0 = ocupado, 1 = disponible
}celdaRAC;

typedef struct RAC{
	celdaRAC T[FACTOR_RAC];
	int cantidad;
}RAC;

RAC newRAC();
bool isEmptyRAC(RAC rac);                                           //if rac.cantidad == 0
bool isFullRAC(RAC rac);                                            //if rac.cantidad > 300
void clearRAC(RAC* rac);                                            //vacia un RAC
bool localizarRAC(RAC rac, char patente[], int* posicion, int* c);  //true = patente encontrada, false = patente no encontrada
vehiculo evocarRAC(RAC rac, char patente[], int* c);                //return vehiculo encontrado o vehiculo con patente "0000000" si no se encontro
bool altaRAC(RAC* rac, vehiculo v);                                 //false = patente repetida, true = alta exitosa
int bajaRAC(RAC* rac, char patente[], int condicion, vehiculo v);   //-1=baja cancelada por usuario, 0=patente no encontrada, 1=baja exitosa
void printRAC(RAC rac);												//Imprime un RAC

					//RS

typedef struct celdaRS{
	vehiculo data;
	struct celdaRS* next;
}celdaRS;

typedef struct RS{
	celdaRS T[FACTOR_RS];
	celdaRS* anterior;
	celdaRS* actual;
	int cantidad;
}RS;

celdaRS* newCeldaRS(vehiculo v);
RS newRS();
bool isEmptyRS(RS rs);                                          //if rs.cantidad == 0
bool isFullRS(RS rs);                                           //if rs.cantidad > 300
void clearRS(RS* rs);                                           //vacia un RS
bool localizarRS(RS* rs, char patente[], int* c);               //true = patente encontrada, false = patente no encontrada
vehiculo evocarRS(RS rs, char patente[], int *c);               //return vehiculo encontrado o vehiculo con patente "0000000" si no se encontro
int altaRS(RS* rs, vehiculo v);                                 //-1=no memoria disponible, 0=patente repetida, 1=alta exitosa
int bajaRS(RS* rs, char patente[], int condicion, vehiculo v);	//-1=baja cancelada por usuario, 0=patente no encontrada, 1=baja exitosa
void printListaVinculada(celdaRS* c, int p);					//Imprime toda la lista a la que apunta la cabecera
void printRS(RS rs);											//Imprime un RS

					//HASH
int hashing(char* x, int M){
    int i;
    int contador = 0;

    for(i=0; i<strlen(x); i++)
        contador += (int)x[i] * (i+1);

    return (contador % M);
}

                    //PILA - Usada para administrar costos

typedef struct{
    int nums[MAX];
    int tope;
} pila;

//Operaciones sobre la Pila

void initPila(pila *p);
void push(pila *p, int n);
int pop(pila *p);
int isFull(pila p);
int isEmpty (pila p);
int copy(pila p);
void getEstadisticas(pila p, int* max, float* prom);

                    //FUNCION DE COSTOS
void compararEstructuras(RAC* rac, RS* rs); //compara costos de RAC y RS

                    //MAIN

int main(){
    system("color 0A");
    RAC rac = newRAC();
    RS rs = newRS();
	//variables auxiliares para el funcionamiento de las funciones
    char patente[8];
    int c; //costo
    vehiculo v;

	int menu1, menu2, menu3;
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
                printf("[1] RAC\n");
                printf("[2] RS\n");
                printf("\n[0] Volver\n");
                printf("\nOpcion: ");
                scanf("%d",&menu2);
                getchar();
                switch(menu2){
                case 1: //RAC
                    do{
                       system("cls");
                        printf("\t\t RAC\n\n");
                        printf("Seleccione una opcion:\n\n");
                        printf("[1] Ingresar Vehiculo\n");
                        printf("[2] Eliminar Vehiculo Existente\n");
                        printf("[3] Consultar Datos de un Vehiculo\n");
                        printf("[4] Mostrar Estructura\n");
                        printf("\n[0] Volver\n");
                        printf("\nOpcion: ");
                        scanf("%d",&menu3);
                        getchar();
                        switch(menu3){
                        case 1: //Ingresar vehiculo
                            if(isFullRAC(rac)){
                                system("cls");
                                printf("Error: no hay mas lugar en la lista\n");
                                system("pause");
                            }
                            else{
                                int rta = altaRAC(&rac, scanDatos());
                                switch(rta){
                                case false: //Elemento repetido
                                    system("cls");
                                    printf("Error: patente repetida\n");
                                    system("pause");
                                    break;
                                case true: //Exito
                                    system("cls");
                                    printf("Exito al cargar vehiculo\n");
                                    system("pause");
                                    break;
                                }
                            }
                            break;
                        case 2: //Eliminar Vehiculo Existente
                            if(isEmptyRAC(rac)){
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

                                int rta = bajaRAC(&rac, patente, 1, v);
                                switch(rta){
                                case -1: //se decidio no dar de baja
                                    system("cls");
                                    printf("Baja cancelada por el usuario\n");
                                    system("pause");
                                    break;
                                case 0: //patente no encontrada
                                    system("cls");
                                    printf("No existe el vehiculo\n");
                                    system("pause");
                                    break;
                                case 1: //exito en la baja
                                    system("cls");
                                    printf("Eliminacion exitosa\n");
                                    system("pause");
                                    break;
                                }
                            }
                            break;
                        case 3: //Consultar Datos de un vehiculo
                            if(isEmptyRAC(rac)){
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

                                v = evocarRAC(rac, patente, &c);
                                if(strcmp(v.patente, "0000000")==0){ //si la patente de v es invalida
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

                        case 4: //Mostrar Estructura
                            if(isEmptyRAC(rac)){
                                system("cls");
                                printf("Estructura vacia\n");
                                system("pause");
                            }
                            else
                                printRAC(rac);
                        break;
                        case 0: //Volver
                            break;
                        default:
                            menu3 = -1;
                        }
                    }while(menu3 != 0);
                    break;

                case 2: //RS
                    do{
                       system("cls");
                        printf("\t\tRS\n\n");
                        printf("Seleccione una opcion:\n\n");
                        printf("[1] Ingresar Vehiculo\n");
                        printf("[2] Eliminar Vehiculo Existente\n");
                        printf("[3] Consultar Datos de un Vehiculo\n");
                        printf("[4] Mostrar Estructura\n");
                        printf("\n[0] Volver\n");
                        printf("\nOpcion: ");
                        scanf("%d",&menu3);
                        getchar();
                        switch(menu3){
                        case 1: //Ingresar vehiculo
                            if(isFullRS(rs)){
                                system("cls");
                                printf("Error: no hay mas lugar en la lista\n");
                                system("pause");
                            }
                            else{
                                int rta = altaRS(&rs, scanDatos());
                                switch(rta){
                                case -1: //No hay memoria disponible
                                    system("cls");
                                    printf("ALTA FALLIDA: no se pudo asignar memoria");
                                    system("pause");
                                    break;
                                case 0: //Elemento repetido
                                    system("cls");
                                    printf("Error: patente repetida\n");
                                    system("pause");
                                    break;
                                case 1: //Exito
                                    system("cls");
                                    printf("Exito al cargar vehiculo\n");
                                    system("pause");
                                    break;
                                }
                            }
                            break;
                        case 2: //Eliminar Vehiculo Existente
                            if(isEmptyRS(rs)){
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

                                int rta = bajaRS(&rs, patente, 1, v);
                                switch(rta){
                                case -1: //se decidio no dar de baja
                                    system("cls");
                                    printf("Baja cancelada por el usuario\n");
                                    system("pause");
                                    break;
                                case 0: //patente no encontrada
                                    system("cls");
                                    printf("No existe el vehiculo\n");
                                    system("pause");
                                    break;
                                case 1: //exito en la baja
                                    system("cls");
                                    printf("Eliminacion exitosa\n");
                                    system("pause");
                                    break;
                                }
                            }
                            break;
                        case 3: //Consultar Datos de un vehiculo
                            if(isEmptyRS(rs)){
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

                                v = evocarRS(rs, patente, &c);
                                if(strcmp(v.patente, "0000000")==0){ //si la patente de v es invalida
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
                        case 4: //Mostrar Estructura
                            if(isEmptyRS(rs)){
                                system("cls");
                                printf("Estructura vacia\n");
                                system("pause");
                            }
                            else
                                printRS(rs);
                        break;
                        case 0: //Volver
                            break;
                        default:
                            menu3 = -1;
                        }
                    }while(menu3 != 0);
                    break;
                case 0: //VOLVER
                       break;
                default:
                    menu2 = -1;
                }
            }while(menu2 != 0);
            break;
        case 2: //Comparacion de Estructuras
            if(!isEmptyRAC(rac) || !isEmptyRS(rs)){
                int aux=0;
                do{
                    system("cls");
                    printf("Alguna de las estructuras no se encuentran vacias. Desea vaciarlas para continuar?\n\n[1] Si\n[2] No\n");
                    scanf("%d", &aux);
                }
                while(aux!=1 && aux!=2);
                if(aux==1){
                    clearRAC(&rac);
                    printf("RAC VACIADO\n");
                    clearRS(&rs);
                    printf("RS VACIADO\n");
                    system("cls");
                    compararEstructuras(&rac, &rs);
                    system("pause");
                }
            }
            else{
                system("cls");
                compararEstructuras(&rac, &rs);
                system("pause");
            }
            break;
        case 0: //Salir
            printf("Gracias por utilizar el programa!\n");
            clearRS(&rs); //free de las listas vinculadas de RS
            exit(0);
            break;
        default:
            menu1 = -1;
        }
	}while(menu1 != 0);

	return 0;
}

					//FUNCIONES DE RAC

RAC newRAC(){
	RAC rac;
	int i;

	for (i = 0; i < FACTOR_RAC; i++)
		rac.T[i].isVirgen = -1;
		copiarVehiculo(nuevoVehiculo("","",0,"","","",0,""),&(rac.T[i].data));

	rac.cantidad = 0;

	return rac;
}

bool isEmptyRAC(RAC rac){
	return rac.cantidad == 0;
}

bool isFullRAC(RAC rac){
	return rac.cantidad > MAX;
}

void clearRAC(RAC* rac){
	int i;

	for (i = 0; i < FACTOR_RAC; i++){
		strcpy(rac->T[i].data.patente,"");
		rac->T[i].isVirgen = -1;
	}

	rac->cantidad = 0;
}

bool localizarRAC(RAC rac, char patente[], int* posicion, int* c){

	int i = hashing(patente,FACTOR_RAC);
	int iAux = -1; //va a guardar el primer hueco donde pudo estar el elemento
	int k = 1;
	*c = 0;
	int iteraciones = 0;

	/*
	si iteraciones == FACTOR_RAC, ya vi todas las celdas
	y tengo que cortar la busqueda

	isVirgen

	-1  = virgen
	0   = desocupado no virgen
	1   = ocupado no virgen
	*/

	while((iteraciones < FACTOR_RAC) && (rac.T[i].isVirgen != -1) && ((strcmp(patente, rac.T[i].data.patente) != 0) || rac.T[i].isVirgen == 0)){
        if(rac.T[i].isVirgen == 0 && iAux == -1)
            iAux = i;

        i = (i+k) % FACTOR_RAC;
		k++;
        iteraciones++;
        *c = *c + 1;
	}

	if(strcmp(patente, rac.T[i].data.patente) == 0){
        *c = *c + 1;
        *posicion = i;
        return true;
	}
	else{
        if(rac.T[i].isVirgen == -1){
            *c = *c + 1;
            *posicion = i;
        }
        if(iAux != -1)
            *posicion = iAux;

        return false;
	}
}

vehiculo evocarRAC(RAC rac, char patente[], int* c){
	int posicion;
	if(localizarRAC(rac, patente, &posicion, c))
		return rac.T[posicion].data;
	else
		return nuevoVehiculo("0000000","",0,"","","",0,""); //vehiculo invalido
}

bool altaRAC(RAC* rac, vehiculo v){
	int posicion;
	int aux;
	if(localizarRAC(*rac, v.patente, &posicion, &aux))
		return false;
	else{
		copiarVehiculo(v, &(rac->T[posicion].data));
		rac->T[posicion].isVirgen = 1; //ocupado
		rac->cantidad = rac->cantidad + 1;
	}
	return true;
}

bool bajaRAC(RAC* rac, char patente[], int condicion, vehiculo v){
	int aux, posicion;
	int confirmar = 0;

	if(localizarRAC(*rac, patente, &posicion, &aux)){
		if(condicion == 0 && compararVehiculos(v, rac->T[posicion].data))
			confirmar = 1;
		else{
			if(condicion == 1){
				do{
					system("cls");
	                printf("Esta seguro que desea dar de baja al siguiente vehiculo:\n");
	                mostrarVehiculo(rac->T[posicion].data);
	                printf("\n\n[1]Si\n[2]No\n");
	                scanf("%d",&confirmar);
	                getchar();
				}while(confirmar!=1 && confirmar!=2);
			}
		}
	}
	if(confirmar == 1){
		strcpy(rac->T[posicion].data.patente,"");
		rac->T[posicion].isVirgen = 0; //desocupado
		rac->cantidad = rac->cantidad - 1;
		return true;
	}
	else{
		if(confirmar == 2)
			return -1; //baja cancelada
		else
			return false; //patente no encontrada
	}
}

void printRAC(RAC rac){
	int i;

	for(i=0; i<FACTOR_RAC; i++){
        system("cls");
		printf("POSICION #%d de %d\n", i, FACTOR_RAC-1);

		switch(rac.T[i].isVirgen){
        case -1:
            printf("ESTADO: VIRGEN\n");
            break;

        case 0:
            printf("ESTADO: DISPONIBLE\n");
            break;

        case 1:
            printf("ESTADO: OCUPADO\n");
            mostrarVehiculo(rac.T[i].data);
            printf("\n");
            break;
		}
		system("pause");
	}
}

					//FUNCIONES DE RS

celdaRS* newCeldaRS(vehiculo v){
	celdaRS* n = (celdaRS*)malloc(sizeof(celdaRS));
	if(n == NULL)
		return n;

	n->data = v;
	n->next = NULL;

	return n;
}

RS newRS(){
	RS rs;
	int i;

	for(i = 0; i < FACTOR_RS; i++){
		rs.T[i].data = nuevoVehiculo("","",0,"","","",0,"");
		rs.T[i].next = NULL;
	}

	rs.actual = NULL;
	rs.anterior = NULL;
	rs.cantidad = 0;

	return rs;
}

bool isEmptyRS(RS rs){
	return rs.cantidad == 0;
}

bool isFullRS(RS rs){
	//return rs.cantidad > 300;

	bool boo = false;

	celdaRS* nuevo = newCeldaRS(nuevoVehiculo("","",0,"","","",0,""));
	if (nuevo == NULL)
        boo = true;

    free((void*)nuevo);
    return boo;
}

void clearRS(RS* rs){
	int i;

	for(i = 0; i < FACTOR_RS; i++){
		rs->anterior = &(rs->T[i]);
		rs->actual = rs->anterior->next;

		while(rs->actual != NULL){
			rs->anterior = rs->actual;
			rs->actual = rs->actual->next;
			free((void*)rs->anterior);
		}
	}

	for(i = 0; i < FACTOR_RS; i++){
		rs->T[i].data = nuevoVehiculo("","",0,"","","",0,"");
		rs->T[i].next = NULL;
	}

    rs->cantidad = 0;
}

bool localizarRS(RS* rs, char patente[], int* c){
	int i = hashing(patente, FACTOR_RS);
	rs->anterior = &(rs->T[i]);
	rs->actual = &(rs->T[i]);

	rs->actual = rs->actual->next; //en la cabecera no hay nada, es ua celda con dato invalido

	*c = 0;

	while(rs->actual != NULL && strcmp(patente, rs->actual->data.patente) != 0){

		rs->anterior = rs->actual;
        rs->actual = rs->actual->next;
		*c = *c + 1;
	}

	if(rs->actual != NULL && strcmp(patente, rs->actual->data.patente) == 0){
        *c = *c + 1;
        return true;
    }
	else
		return false;
}

vehiculo evocarRS(RS rs, char patente[], int* c){
	if(localizarRS(&rs, patente, c))
		return rs.actual->data;
	else
		return nuevoVehiculo("0000000","",0,"","","",0,""); //vehiculo invalido
}

int altaRS(RS* rs, vehiculo v){
	int aux;

	if(localizarRS(rs, v.patente, &aux))
		return 0; //patente repetida
	else{
		celdaRS* nuevo = newCeldaRS(v);
		if(nuevo==NULL)
			return -1; //memoria no disponible
		else{
            rs->anterior->next = nuevo;
            //no necesito apuntar nuevo a null, ya lo hace newCeldaRs()
            rs->cantidad = rs->cantidad + 1;
            return true;
		}
	}
}

int bajaRS(RS* rs, char patente[], int condicion, vehiculo v){
	int aux;
	int confirmar = 0;

	if(localizarRS(rs, patente, &aux)){
		if(condicion == 0 && compararVehiculos(v, rs->actual->data))
			confirmar = 1;
		else{
			if(condicion == 1){
				do{
					system("cls");
	                printf("Esta seguro que desea dar de baja al siguiente vehiculo:\n");
	                mostrarVehiculo(rs->actual->data);
	                printf("\n\n[1]Si\n[2]No\n");
	                scanf("%d",&confirmar);
	                getchar();
				}while(confirmar!=1 && confirmar!=2);
			}
		}
	}
	if(confirmar == 1){
        rs->anterior->next = rs->actual->next;
        free((void*)rs->actual);
        rs->cantidad = rs->cantidad - 1;
		return true;
	}
	else{
		if(confirmar == 2)
			return -1; //baja cancelada
		else
			return false; //patente no encontrada
	}
}

void printRS(RS rs){
    int i;
    for(i=0; i<FACTOR_RS; i++){
        if(rs.T[i].next == NULL){
            system("cls");
            printf("POSICION %d de %d\n", i, FACTOR_RS-1);
            printf("Cabecera apunta a NULL\n");
            system("pause");
        }
        else{
            celdaRS* p = rs.T[i].next;
            while(p != NULL){
                system("cls");
                printf("POSICION %d de %d\n", i, FACTOR_RS-1);
                mostrarVehiculo(p->data);
                system("pause");
                p = p->next;
            }
        }
    }
}

                    //FUNCIONES DE VEHICULO

vehiculo scanDatos(){
	//vehiculo v; //el vehiculo que vamos a armar y devolver
	//variables para almacenar los scans
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

                    //FUNCIONES DE PILA

void initPila(pila *p){
    (*p).tope=-1;
}

void push(pila *p, int n){
    if(!(isFull(*p))){
        (*p).tope++;
        (*p).nums[(*p).tope]=n;
    }
}

int pop(pila *p){
    //solo llamada por el promedio
    int aux = (*p).nums[(*p).tope];
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

int isEmpty(pila p){
    if(p.tope==-1){
        return(1);
    }
    else{
        return(0);
    }
}

int copy(pila p){
    return(p.nums[p.tope]);
}

void getEstadisticas(pila p, int* max, float* prom){
    int sumador=0, aux=0, i=0, maximo=0;
    float promedio = 0;

    while(!isEmpty(p)){
        aux = pop(&p);
        if(aux>maximo)
            maximo=aux;
        sumador+=aux;
        i++;
    }
    *max = maximo;

    if(i>0)
        promedio = (float)sumador/(float)i;

    *prom = promedio;
}

void compararEstructuras(RAC* rac, RS* rs){
    FILE *fp;
    if((fp = fopen("Operaciones.txt","r"))==NULL){
        printf("Error, no se pudo abrir el archivo.\n");
    }
    else{
        vehiculo vaux;
        int boo; //recibe los returns de alta y baja, no tiene funcion realmente
        int op;
        int c = 0;

                //PILAS Y FLOATS DE COSTOS

        pila    costosLocExitosaRAC, costosLocExitosaRS,
                costosLocFracasoRAC, costosLocFracasoRS;

        initPila(&costosLocExitosaRAC);  initPila(&costosLocExitosaRS);
        initPila(&costosLocFracasoRAC);  initPila(&costosLocFracasoRS);

        //float promedio
        float   promLE_RAC,  promLE_RS,
                promLF_RAC,  promLF_RS;

        //int maximo
        int maxLE_RAC,   maxLE_RS,
            maxLF_RAC,   maxLF_RS;

        int cond1, cond2 = 0;  //basura??


        while(!feof(fp) && (!isFullRAC(*rac) || !isFullRS(*rs))){
            fscanf(fp,"%d\n",&op);
            fscanf(fp,"%[^\n]\n",vaux.patente);
            strupr(vaux.patente);
           /*
            if op==3
                deja de escanear y procede a consultar
            else
                sigue escaneando para luego realizar alta o baja
            */
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
                if(!isFullRAC(*rac))
                    boo = altaRAC(rac, vaux);

                if(!isFullRS(*rs))
                    boo = altaRS(rs, vaux);
                break;

            case 2: //BAJAS
                boo = bajaRAC(rac, vaux.patente, 0, vaux);
                boo = bajaRS(rs, vaux.patente, 0, vaux);
                break;

            case 3: //CONSULTAS

            //RAC
                if(strcmp(evocarRAC(*rac, vaux.patente, &c).patente, vaux.patente) == 0)
                    push(&costosLocExitosaRAC, c);

                else
                    push(&costosLocFracasoRAC, c);


            //RS
                if(strcmp(evocarRS(*rs, vaux.patente, &c).patente, vaux.patente) == 0)
                    push(&costosLocExitosaRS, c);

                else
                    push(&costosLocFracasoRS, c);

                break;
            }
        }

        //calculo de estadisticas

        getEstadisticas(costosLocExitosaRAC, &maxLE_RAC, &promLE_RAC);
        getEstadisticas(costosLocFracasoRAC, &maxLF_RAC, &promLF_RAC);
        getEstadisticas(costosLocExitosaRS, &maxLE_RS, &promLE_RS);
        getEstadisticas(costosLocFracasoRS, &maxLF_RS, &promLF_RS);

        //print costos

        printf("/////////////////////////////////////////////////////////////////////////////////\n\n");
                            printf("\t\t\t\tRAC\n\n");

        printf("LOCALIZACION: [Cantidad de baldes consultadas]\n\n");

        printf("\t.Costo MEDIO en localizacion EXITOSA:\t\t%f\n", promLE_RAC);
        printf("\t.Costo MAXIMO en localizacion EXITOSA:\t\t%d\n\n", maxLE_RAC);

        printf("\t.Costo MEDIO en localizacion FRACASADA:\t\t%f\n", promLF_RAC);
        printf("\t.Costo MAXIMO en localizacion FRACASADA:\t%d\n\n", maxLF_RAC);

        printf("/////////////////////////////////////////////////////////////////////////////////\n\n");

                            printf("\t\t\t\tRS\n\n");

        printf("LOCALIZACION: [Cantidad de baldes consultados]\n\n");

        printf("\t.Costo MEDIO en localizacion EXITOSA:\t\t%f\n", promLE_RS);
        printf("\t.Costo MAXIMO en localizacion EXITOSA:\t\t%d\n\n", maxLE_RS);

        printf("\t.Costo MEDIO en localizacion FRACASADA:\t\t%f\n", promLF_RS);
        printf("\t.Costo MAXIMO en localizacion FRACASADA:\t%d\n\n", maxLF_RS);

    }
    fclose(fp);
}
