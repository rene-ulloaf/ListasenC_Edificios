#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//declaracion de constantes
const int _FALSE=0, _TRUE=1;
//creo una constante que lleva la ruta de los archivos a leer.
const char *FOLDER = "edificios/";//"C:/edificios/";
const char *rutaEdificios = "edificios.txt";
const char *rutaIdEdificios = "IdEdificios.txt";
const char *rutaGastosEdificios = "gastos_edificios.txt";
const char *rutaepartamentos = "departamentos.txt";
const char *rutaGastosDepartamentos = "gastos_departamentos.txt";

//declaracion de estructuras
typedef struct _edificios{
    int id;
    char *dueno;
    int cant_deptos;
    int cant_deptos_ocupados;
    int gastos;
    struct _edificios *sig;
} edificios;

typedef edificios *NEdif;
typedef edificios *LEdif;

LEdif lis_edif;

//declaracion de funciones
void Menu(char);
void ingresarEdificio();
char GuardarIdDepartamento(char *);
void ObtenerIdEdificio(char **);
char CrearDepartamento(char *,char *);
void selEdificio();
void InsertarEdificio();
void MostrarLista(LEdif);
int ListaEdifVacia(LEdif);
void MenuEdificio(char);
//void ingresarGastos();
//void EliminaEdificio();
//void verDeptos();
void MenuDepartamento(char);
//void ModificarDueno();
//void IngGasto();
//void ObtenerGastos();
//void PagoGastos();
//void ElimnaDepto();
void ObtenerFechaFormateada(char **);
void Salir();

int main() {
    Menu(_TRUE);
    return (EXIT_SUCCESS);
}

void Menu(char op){
    char *sel=NULL;

    sel = (char *) malloc(sizeof(char)* 1);
    printf("###########Trabajo Estructuras############\n\n");
    if(op){
        printf("\nOpcion no permitida\n");
    }

    printf("[1] Ingresar Edificio\n");
    printf("[2] Seleccionar Edificio\n");
    printf("[3] Salir");
    printf("\n\nOpción : ");
    scanf("%s", sel);

    if(!strcmp(sel,"1")){
        system("cls");
        ingresarEdificio();
    }else if(!strcmp(sel,"2")){
        system("cls");
        selEdificio();
    }else if(!strcmp(sel,"3")){
        Salir();
    }else{
        system("cls");
        Menu(_TRUE);
    }
}

void MenuEdificio(char op){
    char *sel=NULL;

    sel = (char *) malloc(sizeof(char)* 1);
    printf("###########Trabajo Estructuras############\n\n");
    if(op){
        printf("\nOpcion no permitida\n");
    }

    printf("[1] Ingresar Gastos\n");
    printf("[2] Ver Departamentos\n");
    printf("[3] Eliminar Edificio\n");
    printf("[4] Volver");
    printf("\n\nOpción : ");
    scanf("%s", sel);

    if(!strcmp(sel,"1")){
        system("cls");
        //ingresarGastos();
    }else if(!strcmp(sel,"2")){
        system("cls");
        //EliminaEdificio();
    }else if(!strcmp(sel,"3")){
        system("cls");
        //verDeptos();
    }else if(!strcmp(sel,"4")){
        Menu(_FALSE);
    }else{
        system("cls");
        MenuEdificio(_FALSE);
    }
}

void MenuDepartamento(char op){
    char *sel=NULL;

    sel = (char *) malloc(sizeof(char)* 1);
    printf("###########Trabajo Estructuras############\n\n");
    if(op){
        printf("\nOpcion no permitida\n");
    }

    printf("[1] Modificar Dueño\n");
    printf("[2] Ingresar Gasto Comun\n");
    printf("[3] Obtener Gasto Comun\n");
    printf("[4] Pago Gastos Comun\n");
    printf("[5] Eliminar\n");
    printf("[6] Volver");
    printf("\n\nOpción : ");
    scanf("%s", sel);

    if(!strcmp(sel,"1")){
        system("cls");
        //ModificarDueno();
    }else if(!strcmp(sel,"2")){
        system("cls");
        //IngGasto();
    }else if(!strcmp(sel,"3")){
        system("cls");
        //ObtenerGastos();
    }else if(!strcmp(sel,"4")){
        system("cls");
        //PagoGastos();
    }else if(!strcmp(sel,"5")){
        system("cls");
        //ElimnaDepto();
    }else if(!strcmp(sel,"6")){
        MenuEdificio(_FALSE);
    }else{
        system("cls");
        MenuDepartamento(_TRUE);
    }
}

void ingresarEdificio(){
    char *nombreDueno=NULL, *cantDeptos=NULL, resp=_FALSE;

    nombreDueno = (char *) malloc(sizeof(char)* 100);
    cantDeptos = (char *) malloc(sizeof(char)* 1);

    printf("###########Trabajo Estructuras############\n\n");
    printf("---Ingreso de Edificio---\n\n");

    printf("Nombre dueño:");
    scanf("%s", nombreDueno);

    printf("\n");

    printf("Cantidad departamentos:");
    scanf("%s", cantDeptos);

    if(1==0){
        free(nombreDueno);
        printf("\n\ndatos erroneos, intentelo nuevamente\n\n");
        ingresarEdificio();
    }else{
        resp = CrearDepartamento(nombreDueno,cantDeptos);
    }

    if(resp){
        printf("\n\nagregado\n\n");
    }else{
        printf("\n\nno agregado\n\n");
    }

    free(nombreDueno);
}

void ObtenerIdEdificio(char **ret){
    char *ruta=NULL, *id=NULL, *aux=NULL;
    FILE *archivo;
    int a;

    **ret = '0';

    ruta = (char *) malloc(sizeof(char)* 25);
    id = (char *) malloc(sizeof(char)* 1);
    aux = (char *) malloc(sizeof(char)* 1);

    strcpy(ruta,"");
    strcat(ruta,FOLDER);
    strcat(ruta,rutaIdEdificios);

    archivo = fopen(ruta,"r");
    if(archivo != NULL){
        while(!feof(archivo) && fread(aux,1,1,archivo)){
            fseek(archivo,-1, SEEK_CUR);
            fscanf(archivo,"%s",id);
        }

        fflush(archivo);
        fclose(archivo);
    }

    a= *id;
    a++;
    **ret = a;

    /*free(ruta);
    free(aux);*/
}

char GuardarIdDepartamento(char *id){
    char *ruta=NULL, ret=_FALSE;
    FILE *archivo;

    ruta = (char *) malloc(sizeof(char)* 26);
    
    strcpy(ruta,"");
    strcat(ruta,FOLDER);
    strcat(ruta,rutaIdEdificios);

    archivo = fopen(ruta,"w");
    if(archivo != NULL){
        fputs(id,archivo);

        fflush(archivo);
        fclose(archivo);

        ret = _TRUE;
    }

    free(ruta);

    return ret;
}

char CrearDepartamento(char *nombreDueno, char *cantDeptos){
    char *id=NULL, *fec=NULL, *ruta=NULL, ret=_FALSE;
    FILE *archivo;

    id = (char *) malloc(sizeof(char)* 1);
    fec = (char *) malloc(sizeof(char)* 128);
    ruta = (char *) malloc(sizeof(char)* 26);

    strcpy(ruta,"");
    strcat(ruta,FOLDER);
    strcat(ruta,rutaEdificios);

    archivo = fopen(ruta,"a");
    if(archivo != NULL){
        /*if(ftell(archivo) > 0){
            fputc('\n',archivo);
        }*/
        ObtenerIdEdificio(&id);
        fputs(id,archivo);
        fputc('\t',archivo);
        fputs(nombreDueno,archivo);
        fputc('\t',archivo);
        fputs(cantDeptos,archivo);
        fputc('\t',archivo);
        fputc('0',archivo);
        fputc('\t',archivo);
        ObtenerFechaFormateada(&fec);
        fputs(fec,archivo);
        fputc('\n',archivo);

        fflush(archivo);
        fclose(archivo);

        ret = _TRUE;
    }

    if(ret){
        ret = GuardarIdDepartamento(id);
    }

    //free(id);
    //free(fec);
    free(ruta);

    return ret;
}

void selEdificio(){
    char *aux=NULL, *id=NULL, *dueno=NULL, *cant_deptos=NULL, *cant_deptos_ocupados=NULL, *vigente=NULL, *fecha=NULL, *gasto=NULL, *ruta=NULL;
    FILE *archivo;

    aux = (char *) malloc(sizeof(char)* 1);
    dueno = (char *) malloc(sizeof(char)* 50);
    cant_deptos = (char *) malloc(sizeof(char)* 1);
    cant_deptos_ocupados = (char *) malloc(sizeof(char)* 1);
    vigente = (char *) malloc(sizeof(char)* 1);
    fecha = (char *) malloc(sizeof(char)* 13);
    gasto = (char *) malloc(sizeof(char)* 1);
    ruta = (char *) malloc(sizeof(char)* 26);

    strcpy(ruta,"");
    strcat(ruta,FOLDER);
    strcat(ruta,rutaEdificios);

    archivo = fopen(ruta,"r");
    if(archivo != NULL){
        while(!feof(archivo) && fread(aux,1,1,archivo)){
            fseek(archivo,-1, SEEK_CUR);

            fscanf(archivo,"%s",id);
            fscanf(archivo,"%s",dueno);
            fscanf(archivo,"%s",cant_deptos);
            fscanf(archivo,"%s",cant_deptos_ocupados);
            fscanf(archivo,"%s",vigente);
            fscanf(archivo,"%s",fecha);
        }

        fflush(archivo);
        fclose(archivo);

        if(vigente){
            *gasto = '0';
            InsertarEdificio(&lis_edif, *id, *dueno, *cant_deptos, *cant_deptos_ocupados, *gasto);
        }
    }

    MostrarLista(lis_edif);
}

void InsertarEdificio(LEdif *lista, int id, char* dueno, int cant_deptos, int cant_deptos_ocupados, int gasto){
   NEdif nuevo, anterior;

   /* Crear un nodo nuevo */
   nuevo = (NEdif)malloc(sizeof(edificios));
   nuevo->id = id;
   nuevo->dueno = dueno;
   nuevo->cant_deptos = cant_deptos;
   nuevo->cant_deptos_ocupados = cant_deptos_ocupados;
   nuevo->gastos = gasto;

   /* Si la lista está vacía */
   if(ListaEdifVacia(*lista)){
      /* Añadimos la lista a continuación del nuevo nodo */
      nuevo->sig = *lista;
      /* Ahora, el comienzo de nuestra lista es en nuevo nodo */
      *lista = nuevo;
   }else{
      /* Buscar el nodo de valor menor a v */
      anterior = *lista;
      /* Avanzamos hasta el último elemento o hasta que el siguiente tenga un valor mayor que v */
      while(anterior->sig)
         anterior = anterior->sig;
      /* Insertamos el nuevo nodo después del nodo anterior */
      nuevo->sig = anterior->sig;
      anterior->sig = nuevo;
   }
}

void MostrarLista(LEdif lista){
   NEdif nodo = lista;

   if(ListaEdifVacia(lista)) printf("No se encontro a nadie\n");
   else{
      while(nodo){
         printf("animalito encontrado en [%d][%d]\n", nodo->id,nodo->dueno);
         nodo = nodo->sig;
     }
     printf("\n");
   }
}

int ListaEdifVacia(LEdif lista){
   return (lista == NULL);
}

void ObtenerFechaFormateada(char **fec){
    time_t tiempo = time(0);
    char f[128];

    struct tm *tlocal = localtime(&tiempo);
    strftime(f,128,"%d-%m-%Y %H:%M:%S",tlocal);
    //printf("La hora local es: %s\n",asctime(tlocal));
    //printf( "La hora y fecha locales son: %s\n", fec );

    *fec = f;
}

void Salir(){
    system("EXIT_SUCCESS");
}