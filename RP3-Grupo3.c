//GRUPO 3
//BECVORT, FRANCO
//MARTINEZ, ROCIO


/*Responder: En el localizar terminan la búsqueda antes de alcanzar el nivel mínimo
bajo el planteo de mejorar eficiencia en evocaciones considerando celdas consultadas
¿mejoran los dos casos (exitosas y no exitosas)?
Si la aplicación estuviera pensada para procesar más alta/bajas que evocaciones
¿cuán eficiente sería este código respecto del localizar que llega el mínimo nivel sin preguntar por igualdad?

RESPUESTA:
Finalizar la busqueda antes de llegar al nivel minimo solo mejor eficiencia en casos exitosos
Un caso no exitoso siempre finaliza en el nivel mínimo

Siempre que se vaya a hacer una alta/baja, el localizar es obligado a finalizar en el nivel minimo
ya que es la unica manera de dejar punteros donde es necesario reapuntar para realizar la alta/baja.
Asi que un localizar que finalice antes del minimo nivel no sirve para eso
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

					//#defines y structs

//bool
typedef int bool;
#define true 1
#define false 0

//numero de niveles
#define CANTIDAD_DE_NIVELES 4
#define NIVEL_MAXIMO (CANTIDAD_DE_NIVELES-1)

//maxima cantidad de vehiculos
#define MAX 300

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
vehiculo scanDatos();
vehiculo nuevoVehiculo(char patente[], char modelo[], int anio, char dueno[], char telefono[], char servicios[], float monto, char fecha[]);
void mostrarVehiculo(vehiculo v);
bool compararVehiculos(vehiculo v1, vehiculo v2);
void copiarVehiculo(vehiculo v1, vehiculo *v2);
void swapVehiculo(vehiculo *v1, vehiculo *v2);

                    //SKIPLIST

//NODO SKIPLIST
typedef struct nodoSL{
	vehiculo data;
	int nivel;
    struct nodoSL** next;
}nodoSL;

//LISTA
typedef struct lista{
   	struct nodoSL* head;
   	nodoSL* update[CANTIDAD_DE_NIVELES];
   	int cantidadDeNodos;
}lista;


nodoSL* newNodoList(vehiculo v, int nivel);
lista newList();
bool isEmptyList(lista l);
bool isFullList(lista l);
void freeList(lista* l);
void clearList(lista* l);
int randomLevel();
bool localizarList(lista* l, char patente[], bool isEvocar, int* k, int* c);
vehiculo evocarList(lista* l, char patente[], int*c);
int altaList(lista* l, vehiculo v, int* c);
int bajaList(lista* l, char patente[], int condicion, vehiculo v, int* c);
void printNodoLista(nodoSL n);
void printLista(lista l);

                    //BINARY_SEARCH_TREE

//NODO BINARY_TREE
typedef struct nodoBT{
    vehiculo data;
    struct nodoBT* left;
    struct nodoBT* right;
}nodoBT;

//ARBOL
typedef struct arbol{
    nodoBT *raiz;
    nodoBT *cur;
    nodoBT *padre;

    int cantidadDeNodos;
}arbol;

nodoBT* newNodoArbol(vehiculo v);
arbol newArbol();
bool isEmptyArbol(arbol a);
bool isFullArbol(arbol a);
void resetArbol(arbol* a);
void freeArbol(nodoBT* raiz);
void clearArbol(arbol* a);
void forwardL(arbol* a);
void forwardR(arbol* a);
bool localizarArbol(arbol* a, char patente[], int* c);
vehiculo evocarArbol(arbol a, char patente[], int *c);
int altaArbol(arbol* a,vehiculo v, int* c);
int bajaArbol(arbol* a, char patente[], int condicion, vehiculo v, int* c);
void printNodoArbol(nodoBT n);
void preOrder(nodoBT n);
void printArbol(nodoBT* n);

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

void compararEstructuras(lista *l, arbol *a);

                            //MAIN

int main(){
    system("color 0A");
    srand(time(NULL));
	lista skiplist = newList();
	arbol tree = newArbol();

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
                printf("[1] Arbol\n");
                printf("[2] Skiplist\n");
                printf("\n[0] Volver\n");
                printf("\nOpcion: ");
                scanf("%d",&menu2);
                getchar();
                switch(menu2){
                case 1: //ARBOL
                    do{
                       system("cls");
                        printf("\t\t ARBOL\n\n");
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
                            if(isFullArbol(tree)){
                                system("cls");
                                printf("Error: no hay mas lugar en la lista\n");
                                system("pause");
                            }
                            else{
                                int rta = altaArbol(&tree, scanDatos(), &c);
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
                            if(isEmptyArbol(tree)){
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

                                int rta = bajaArbol(&tree, patente, 1, v, &c);
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
                            if(isEmptyArbol(tree)){
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

                                v = evocarArbol(tree, patente, &c);
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
                            if(isEmptyArbol(tree)){
                                system("cls");
                                printf("Estructura vacia\n");
                                system("pause");
                            }
                            else{
                                resetArbol(&tree);
                                printArbol(tree.raiz);
                            }
                        break;
                        case 0: //Volver
                            break;
                        default:
                            menu3 = -1;
                        }
                    }while(menu3 != 0);
                    break;

                case 2: //SKIPLIST
                    do{
                       system("cls");
                        printf("\t\t SKIPLIST\n\n");
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
                            if(isFullList(skiplist)){
                                system("cls");
                                printf("Error: no hay mas lugar en la lista\n");
                                system("pause");
                            }
                            else{
                                int rta = altaList(&skiplist, scanDatos(), &c);
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
                            if(isEmptyList(skiplist)){
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

                                int rta = bajaList(&skiplist, patente, 1, v, &c);
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
                            if(isEmptyList(skiplist)){
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

                                v = evocarList(&skiplist, patente, &c);
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
                            if(isEmptyList(skiplist)){
                                system("cls");
                                printf("Estructura vacia\n");
                                system("pause");
                            }
                            else
                                printLista(skiplist);
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
            if(!isEmptyList(skiplist) || !isEmptyArbol(tree)){
                int aux=0;
                do{
                    system("cls");
                    printf("Alguna de las estructuras no se encuentran vacias. Desea vaciarlas para continuar?\n\n[1] Si\n[2] No\n");
                    scanf("%d", &aux);
                }
                while(aux!=1 && aux!=2);
                if(aux==1){
                    clearList(&skiplist);
                    clearArbol(&tree);
                    system("cls");
                    compararEstructuras(&skiplist, &tree);
                    system("pause");
                }
            }
            else{
                system("cls");
                compararEstructuras(&skiplist, &tree);
                system("pause");
            }
            break;
        case 0: //Salir
            printf("Gracias por utilizar el programa!\n");
            freeList(&skiplist);
            freeArbol(tree.raiz);
            exit(0);
            break;
        default:
            menu1 = -1;
        }
	}while(menu1 != 0);

	return 0;
}

					//FUNCIONES DE SKIPLIST

nodoSL* newNodoList(vehiculo v, int nivel){
	int i;
	nodoSL* n = (nodoSL*)malloc(sizeof(nodoSL));
	if (n == NULL)
        return n;

	n->data = v;
	n->nivel = nivel;
	n->next = (nodoSL**)malloc((nivel+1)*sizeof(nodoSL*));
	if (n->next == NULL)
        return n;

	for(i = 0; i <= nivel; i++)
		n->next[i] = NULL;

	return n;
}

lista newList(){
	lista l;
    l.head = newNodoList(nuevoVehiculo("","",0,"","","",0,""), NIVEL_MAXIMO);
    if(l.head == NULL){
        printf("LISTA NO CREADA: head == NULL");
        exit(1);
    }

    l.cantidadDeNodos = 0;

    nodoSL* infinito = newNodoList(nuevoVehiculo("zzzzzzz","",0,"","","",0,""), NIVEL_MAXIMO);
	int i;
    for (i=0; i <= NIVEL_MAXIMO; i++)
		l.head->next[i] = infinito;

	return l;
}

bool isEmptyList(lista l){
    return(strcmp(l.head->next[0]->data.patente, "zzzzzzz") == 0);
}

bool isFullList(lista l){
    return(l.cantidadDeNodos > 300);
}

void freeList(lista* l){
	nodoSL* p = l->head;
	nodoSL* q;

	do{
		q = p->next[0];
		free(p);
		p = q;
	}while(p != NULL);
}

void clearList(lista *l){
    freeList(l);
    *l = newList();
}

int randomLevel(){
	int n=0;

    while(((double)rand()/(double)RAND_MAX) < 0.5 && n < NIVEL_MAXIMO)
		n++;

    return n;
}

bool localizarList(lista* l, char patente[], bool isEvocar, int* nivel, int* c){
	int k = NIVEL_MAXIMO;
	*c = 1;
	nodoSL* p = l->head;
	nodoSL* q;
	do{
		while(q = p->next[k], strcmp(patente, q->data.patente) > 0){
			p = q;

			if(q->nivel == k)
                *c = *c + 1;
		}

		if(q->nivel == k)
                *c = *c + 1;

		l->update[k] = p;

		if(isEvocar && (strcmp(patente, q->data.patente) == 0)){
            l->update[k] = q;
            *nivel = k;
            return true;
        }

	}while(--k>=0);

	return(strcmp(patente, q->data.patente) == 0);
}

vehiculo evocarList(lista *l, char patente[], int* c){
    int nivel;
    if(localizarList(l, patente, true, &nivel, c))
        return l->update[nivel]->data;
    else
        return nuevoVehiculo("0000000","",0,"","","",0,""); //vehiculo invalido
}

int altaList(lista* l, vehiculo v, int* c){
    int* aux;
	if(!localizarList(l, v.patente, false, aux, c)){

		int k = randomLevel();
		*c = 0;
		nodoSL* nuevo = newNodoList(v, k);
		if(nuevo == NULL)
            return -1;

		nodoSL* p;

		do{
			p = l->update[k];
			nuevo->next[k] = p->next[k];
			p->next[k] = nuevo;             *c = *c + 1;
		}while(--k >= 0);

		l->cantidadDeNodos = l->cantidadDeNodos + 1;
		return 1;
	}
	else
		return 0;
}

int bajaList(lista* l, char patente[], int condicion, vehiculo v, int* c){
    int* aux;
    int confirmar = 0;
    if(localizarList(l, patente, false, aux, c)){
        if(condicion == 0 && compararVehiculos(v, l->update[0]->next[0]->data))
            confirmar = 1;
        else{
            if (condicion == 1){
                do{
                    system("cls");
                    printf("Esta seguro que desea dar de baja de la lista al siguiente vehiculo:\n");
                    mostrarVehiculo(l->update[0]->next[0]->data);
                    printf("\n\n[1]Si\n[2]No\n");
                    scanf("%d",&confirmar);
                    getchar();
                }while(confirmar!=1 && confirmar!=2);
            }
        }
    }
    if(confirmar == 1){
        int k; *c = 0;
        nodoSL* q = l->update[0]->next[0]; //el nodoSL a eliminar
        int nivel = q->nivel;

        for(k = nivel; k >= 0; k--){
            l->update[k]->next[k] = q->next[k];     *c = *c + 1;
        }

        free(q);
        l->cantidadDeNodos = l->cantidadDeNodos - 1;
        return 1; //baja exitosa
    }
    else{
        if(confirmar==2)
            return -1;
        else
            return false;
    }
}

void printNodoLista(nodoSL n){
    int i;
	mostrarVehiculo(n.data);
	printf("NIVEL = %d\n", n.nivel);
	for(i = 0; i <= (n.nivel); i++){
        if(strcmp(n.next[i]->data.patente, "zzzzzzz") != 0)
            printf("\tEn nivel %d le sigue el vehiculo con patente %s\n", i, n.next[i]->data.patente);
        else
            printf("\tEn nivel %d le sigue el nodo INFINITO\n", i);
	}
}

void printLista(lista l){
	nodoSL* p = l.head->next[0];

	while(strcmp(p->data.patente, "zzzzzzz") != 0){
        printNodoLista(*p);
        printf("\n");
        system("pause");
        p = p->next[0];
    }
}

                    //FUNCIONES DE ARBOL

nodoBT* newNodoArbol(vehiculo v){
    nodoBT* n = (nodoBT*)malloc(sizeof(nodoBT));
	if (n == NULL)
        return n;
	n->data = v;
	n->left = NULL;
	n->right = NULL;

	return n;
}

arbol newArbol(){
    arbol a;
    a.raiz = NULL;
    a.cur = NULL;
    a.padre = NULL;
    a.cantidadDeNodos = 0;

    return a;
}

bool isEmptyArbol(arbol a){
    return a.raiz == NULL;
}

bool isFullArbol(arbol a){
    return a.cantidadDeNodos > 300;
}

void resetArbol(arbol* a){
    //todos los punteros a la raiz
    a->cur = a->raiz;
    a->padre = a->raiz;
}

void freeArbol(nodoBT* n){

    if (n == NULL)
        return;

    freeArbol(n->left);
    freeArbol(n->right);

    free((void*)n);
}

void clearArbol(arbol* a){
    resetArbol(a);
    freeArbol(a->raiz);
    *a = newArbol();
}

void forwardL(arbol* a){
    a->padre = a->cur;
    a->cur = a->cur->left;
}

void forwardR(arbol* a){
    a->padre = a->cur;
    a->cur = a->cur->right;
}

bool localizarArbol(arbol* a, char patente[], int *c){
    resetArbol(a);
    *c = 0;

    while(a->cur != NULL && strcmp(patente, a->cur->data.patente) != 0){
        if(strcmp(patente, a->cur->data.patente) > 0)
            forwardR(a);
        else
            forwardL(a);

        *c = *c + 1;
    }

    if(a->cur != NULL){
        *c = *c + 1;
        return true;
    }
    else
        return false;
}

vehiculo evocarArbol(arbol a, char patente[], int* c){
    if(localizarArbol(&a, patente, c))
        return a.cur->data;
    else
        return nuevoVehiculo("0000000","",0,"","","",0,""); //vehiculo invalido
}

int altaArbol(arbol* a, vehiculo v, int *c){
    *c = 0;
    int aux;

    if(!localizarArbol(a, v.patente, &aux)){
        nodoBT* nuevo = newNodoArbol(v);
        if(nuevo == NULL)
            return -1; //no memoria disponible
        else{
            if(isEmptyArbol(*a)){
                a->raiz = nuevo;
                *c = *c + 1;
                a->cantidadDeNodos = a->cantidadDeNodos + 1;
                return 1; //alta exitosa
            }
            else{
                if(strcmp(v.patente, a->padre->data.patente) > 0){
                    a->padre->right = nuevo;
                    *c = *c + 1;
                    a->cantidadDeNodos = a->cantidadDeNodos + 1;
                    return 1; //alta exitosa
                }
                else{
                    a->padre->left = nuevo;
                    *c = *c + 1;
                    a->cantidadDeNodos = a->cantidadDeNodos + 1;
                    return 1; //alta exitosa
                }
            }
        }
    }
    else
        return 0; //patente repetida
}

int bajaArbol(arbol* a, char patente[], int condicion, vehiculo v, int* c){
    *c = 0;
    int aux;
    int confirmar = 0;

    if(localizarArbol(a, patente, &aux)){
        if(condicion == 0 && compararVehiculos(v, a->cur->data))
            confirmar = 1;
        else{
            if(condicion == 1){
                do{
                    system("cls");
                    printf("Esta seguro que desea dar de baja del arbol al siguiente vehiculo:\n");
                    mostrarVehiculo(a->cur->data);
                    printf("\n\n[1]Si\n[2]No\n");
                    scanf("%d",&confirmar);
                    getchar();
                }while(confirmar!=1 && confirmar!=2);
            }
        }
    }
    if(confirmar == 1){

        if(a->cur->left == NULL && a->cur->right == NULL){

            if(a->cur == a->raiz){
                free((void*)(a->cur));
                a->raiz = NULL;
                *c = *c + 1; //costo por apuntar la raiz a NULL
                a->cantidadDeNodos = a->cantidadDeNodos - 1;
                //resetArbol(a);
                return true;
            }
            else{
                if(a->padre->left == a->cur){
                    a->padre->left = NULL;
                    *c = *c + 1; //costo por apuntar padre.izquierdo a NULL
                    free((void*)(a->cur));
                    a->cantidadDeNodos = a->cantidadDeNodos - 1;
                    //resetArbol(a);
                    return true;
                }
                else{
                    a->padre->right = NULL;
                    *c = *c + 1; //costo por apuntar padre.derecho a NULL
                    free((void*)(a->cur));
                    a->cantidadDeNodos = a->cantidadDeNodos - 1;
                    //resetArbol(a);
                    return true;
                }
            }
        }

        if(a->cur->left == NULL && a->cur->right != NULL){

            if(a->cur == a->raiz){
                a->raiz = a->cur->right;
                *c = *c + 1; //costo por reasignar la raiz
                free((void*)(a->cur));
                a->cantidadDeNodos = a->cantidadDeNodos - 1;
                //resetArbol(a);
                return true;
            }
            else{
                if(a->padre->left == a->cur){
                    a->padre->left = a->cur->right;
                    *c = *c + 1; //costo por apuntar padre.izquierdo = cursor.derecho
                    free((void*)(a->cur));
                    a->cantidadDeNodos = a->cantidadDeNodos - 1;
                    //resetArbol(a);
                    return true;
                }
                else{
                    a->padre->right = a->cur->right;
                    *c = *c + 1; //costo por apuntar padre.derecho = cursor.derecho
                    free((void*)(a->cur));
                    a->cantidadDeNodos = a->cantidadDeNodos - 1;
                    //resetArbol(a);
                    return true;
                }
            }
        }

        if(a->cur->left != NULL && a->cur->right == NULL){

            if(a->cur == a->raiz){
                a->raiz = a->cur->left;
                *c = *c + 1; //costo por reasignar la raiz
                free((void*)(a->cur));
                a->cantidadDeNodos = a->cantidadDeNodos - 1;
                //resetArbol(a);
                return true;
            }
            else{
                if(a->padre->left == a->cur){
                    a->padre->left = a->cur->left;
                    *c = *c + 1; //costo por apuntar padre.izquierdo = cursor.izquierdo
                    free((void*)(a->cur));
                    a->cantidadDeNodos = a->cantidadDeNodos - 1;
                    //resetArbol(a);
                    return true;
                }
                else{
                    a->padre->right = a->cur->left;
                    *c = *c + 1; //costo por apuntar padre.derecho = cursor.izquierdo
                    free((void*)(a->cur));
                    a->cantidadDeNodos = a->cantidadDeNodos - 1;
                    //resetArbol(a);
                    return true;
                }
            }
        }

        if(a->cur->left != NULL && a->cur->right != NULL){
            forwardR(a);

            while(a->cur->left != NULL)
                a->cur = a->cur->left;

            a->padre->data = a->cur->data;
            *c = *c + 1;

            if(a->padre->right != a->cur){
                a->padre = a->padre->right;
                while(a->padre->left != a->cur)
                    a->padre = a->padre->left;
                a->padre->left = a->cur->right;
                *c = *c + 1;
            }
            else{
                a->padre->right = a->cur->right;
                *c = *c + 1;
            }

            free((void*)(a->cur));
            return true;
        }
    }
    else{
        if(confirmar == 2)
            return -1; //baja cancelada por usuario
        else
            return false; //patente no encontrada
    }
}

void printNodoArbol(nodoBT n){
    if(&n == NULL){
        printf("Se intento imprimir algo NULL");
        return;
    }
    mostrarVehiculo(n.data);

    if(n.left != NULL)
        printf("\n\t*El hijo izquierdo es: PATENTE %s\n\n", n.left->data.patente);
    else
        printf("\n\t*No tiene hijo izquierdo.\n\n");

    if(n.right != NULL)
        printf("\t*El hijo derecho es: PATENTE %s\n\n", n.right->data.patente);
    else
        printf("\t*No tiene hijo derecho.\n\n");
}

void printArbol(nodoBT* raiz){

    if(raiz != NULL){
        printNodoArbol(*raiz);
        printf("\n");
        system("pause");
        printArbol(raiz->left);
        printArbol(raiz->right);
    }
    else
        return;
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

//Comparacion de estructuras
void compararEstructuras(lista* skiplist, arbol* tree){
    FILE *fp;
    if((fp = fopen("Operaciones.txt","r"))==NULL){
        printf("Error, no se pudo abrir el archivo.\n");
    }
    else{
        vehiculo vaux;
        int op;
        int c = 0;

                //PILAS Y FLOATS DE COSTOS

        pila    costosAltaSL,       costosAltaBT,
                costosBajaSL,       costosBajaBT,
                costosLocExitosaSL, costosLocExitosaBT,
                costosLocFracasoSL, costosLocFracasoBT;

        initPila(&costosAltaSL);        initPila(&costosAltaBT);
        initPila(&costosBajaSL);        initPila(&costosBajaBT);
        initPila(&costosLocExitosaSL);  initPila(&costosLocExitosaBT);
        initPila(&costosLocFracasoSL);  initPila(&costosLocFracasoBT);

        //float promedio
        float  promAltaSL, promAltaBT,
                promBajaSL, promBajaBT,
                promLE_SL,  promLE_BT,
                promLF_SL,  promLF_BT;

        //int maximo
        int maxAltaSL,  maxAltaBT,
            maxBajaSL,  maxBajaBT,
            maxLE_SL,   maxLE_BT,
            maxLF_SL,   maxLF_BT;

        while(!feof(fp) && !isFullList(*skiplist) && !isFullArbol(*tree)){
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

            //SkipList
                if(altaList(skiplist, vaux, &c))
                    push(&costosAltaSL, c);

            //BinaryTree
                if(altaArbol(tree, vaux, &c))
                    push(&costosAltaBT, c);

                break;

            case 2: //BAJAS

            //SkipList
                if(bajaList(skiplist, vaux.patente, 0, vaux, &c))
                    push(&costosBajaSL, c);

            //BinaryTree
                if(bajaArbol(tree, vaux.patente, 0, vaux, &c))
                    push(&costosBajaBT, c);

                break;

            case 3: //CONSULTAS

            //SkipList
                if(strcmp(evocarList(skiplist, vaux.patente, &c).patente, vaux.patente) == 0)
                    push(&costosLocExitosaSL, c);
                else
                    push(&costosLocFracasoSL, c);

            //BinaryTree
                if(strcmp(evocarArbol(*tree, vaux.patente, &c).patente, vaux.patente) == 0)
                    push(&costosLocExitosaBT, c);
                else
                    push(&costosLocFracasoBT, c);

                break;
            }
        }

        //calculo de estadisticas

        getEstadisticas(costosAltaSL, &maxAltaSL, &promAltaSL);
        getEstadisticas(costosAltaBT, &maxAltaBT, &promAltaBT);

        getEstadisticas(costosBajaSL, &maxBajaSL, &promBajaSL);
        getEstadisticas(costosBajaBT, &maxBajaBT, &promBajaBT);

        getEstadisticas(costosLocExitosaSL, &maxLE_SL, &promLE_SL);
        getEstadisticas(costosLocFracasoSL, &maxLF_SL, &promLF_SL);
        getEstadisticas(costosLocExitosaBT, &maxLE_BT, &promLE_BT);
        getEstadisticas(costosLocFracasoBT, &maxLF_BT, &promLF_BT);

        //print costos

        printf("/////////////////////////////////////////////////////////////////////////////////\n\n");
        printf("\t\t\t\tSKIP LIST\n\n");

        printf("LOCALIZACION: [Cantidad de nodos consultados]\n\n");

        printf("\t.Costo MEDIO en localizacion EXITOSA:\t\t%f\n", promLE_SL);
        printf("\t.Costo MAXIMO en localizacion EXITOSA:\t\t%d\n\n", maxLE_SL);

        printf("\t.Costo MEDIO en localizacion FRACASADA:\t\t%f\n", promLF_SL);
        printf("\t.Costo MAXIMO en localizacion FRACASADA:\t%d\n\n", maxLF_SL);

        printf("ALTA: [Cantidad de punteros re-asignados]\n\n");

        printf("\t.Costo MEDIO en el alta:\t%f\n", promAltaSL);
        printf("\t.Costo MAXIMO en el alta:\t%d\n\n", maxAltaSL);

        printf("BAJA: [Cantidad de punteros re-asignados]\n\n");

        printf("\t.Costo MEDIO en la baja:\t%f\n", promBajaSL);
        printf("\t.Costo MAXIMO en la baja:\t%d\n\n", maxBajaSL);


        printf("/////////////////////////////////////////////////////////////////////////////////\n\n");

        printf("\t\t\t\tARBOL BINARIO DE BUSQUEDA\n\n");

        printf("LOCALIZACION: [Cantidad de nodos consultados]\n\n");

        printf("\t.Costo MEDIO en localizacion EXITOSA:\t\t%f\n", promLE_BT);
        printf("\t.Costo MAXIMO en localizacion EXITOSA:\t\t%d\n\n", maxLE_BT);

        printf("\t.Costo MEDIO en localizacion FRACASADA:\t\t%f\n", promLF_BT);
        printf("\t.Costo MAXIMO en localizacion FRACASADA:\t%d\n\n", maxLF_BT);

        printf("ALTA: [Cantidad de punteros re-asignados]\n\n");

        printf("\t.Costo MEDIO en el alta:\t%f\n", promAltaBT);
        printf("\t.Costo MAXIMO en el alta:\t%d\n\n", maxAltaBT);

        printf("BAJA: [Cantidad de punteros re-asignados = 1, Cantidad de reemplazos = 1]\n\n");

        printf("\t.Costo MEDIO en la baja:\t%f\n", promBajaBT);
        printf("\t.Costo MAXIMO en la baja:\t%d\n\n", maxBajaBT);

    }
    fclose(fp);
}
