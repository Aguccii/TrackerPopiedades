#ifndef MILIBRERIA_H_INCLUDED
#define MILIBRERIA_H_INCLUDED
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Estructura que representa un registro
struct Registro {
    int id;
    char fechaIngreso[15];
    char zona[20];
    char ciudadOBarrio[20];
    int dormitorios;
    int banios;
    float superficieTotal;
    float superficieCubierta;
    float precio;
    char moneda[10];
    char tipoDeProp[15];
    char operacion[20];
    char fechaSalida[15];
    int activo;
}aux;

void cabecera(){
    printf("ID | Fecha de ingreso |\t        Zona\t      |    Ciudad o barrio   | Dormitorios | Ba%cos | Superficie total |"
            " Superficie cubierta | Precio \t|   Moneda   | Tipo de propiedad |     Operaci%cn     |"
            " Fecha de salida | Activo \r\n",164,162);
}

void mostrarMenu(){

    printf("              PropiedadTracker\n");
    printf("\n");
    printf("Men%c: \n", 163);
    printf(" 1. Crear archivo\n 2. Listar datos\n 3. Alta propiedad\n 4. Buscar propiedad\n 5. Modificar propiedad\n 6. Baja l%cgica\n 7. Baja f%csica\n", 162, 161, 161);
    printf("\n");
    printf("Por favor, marque el n%cmero del %cndice de la opci%cn que desea elegir o marque 0 para salir: ", 163, 161, 162);

};

void crearArchivo(){

    const char *nombreArchivo = "propiedades.dat";

    // Crear el archivo binario
    FILE *archivo = fopen(nombreArchivo, "wb");

     if (archivo == NULL) {
        perror("No se pudo crear el archivo.");
        return;
    }else{ printf("Archivo creado correctamente.");
        }

};

// Funci�n de comparaci�n para qsort
int comparar_registros(const void *a, const void *b) {
    return ((struct Registro*)a)->id - ((struct Registro*)b)->id;
}

//funcion para mostrar solo los registros activos
void mostrar_activos(){
    FILE *pArchivo;
    pArchivo=fopen("Propiedades.dat","rb");
    if (pArchivo!=NULL){
        fseek(pArchivo,0,SEEK_SET);
        cabecera();
        while (fread(&aux, sizeof(struct Registro), 1, pArchivo) == 1) {
            if(aux.activo==1){
                printf("%-2d | %-16s | %-21s | %-20s | %-11d | %-5d | %-16.1f | %-19.1f | %-9.1f | %-10s |"
                       " %-17s | %-17s | %-15s | %d \r\n",
                        aux.id, aux.fechaIngreso, aux.zona, aux.ciudadOBarrio, aux.dormitorios, aux.banios,
                        aux.superficieTotal, aux.superficieCubierta, aux.precio, aux.moneda, aux.tipoDeProp, aux.operacion,
                        aux.fechaSalida, aux.activo);
            }
        }
        printf("Ingrese cualquier tecla para continuar: ");
        getchar();
        system("cls");
    }
    else printf("Error al abrir el archivo");
}

//funcion para mostrar todos los registros
void listar_todos(){
    FILE *pArchivo;
    pArchivo=fopen("propiedades.dat","rb");
    if (pArchivo!=NULL){
        fseek(pArchivo,0,SEEK_SET);
        cabecera();
        while (!feof(pArchivo)) {
            if (fread(&aux, sizeof(struct Registro), 1, pArchivo) == 1){
                printf("%-2d | %-16s | %-21s | %-20s | %-11d | %-5d | %-16.1f | %-19.1f | %-9.1f | %-10s |"
                       " %-17s | %-17s | %-15s | %d \r\n",
                       aux.id, aux.fechaIngreso, aux.zona, aux.ciudadOBarrio, aux.dormitorios, aux.banios,
                       aux.superficieTotal, aux.superficieCubierta, aux.precio, aux.moneda, aux.tipoDeProp, aux.operacion,
                       aux.fechaSalida, aux.activo);
            }
        }
        printf("Ingrese cualquier tecla para continuar: ");
        getchar();
        system("cls");
    }
    else printf("Error al abrir el archivo");
}

void mostrar_prop(){
    FILE *pArchivo;
    pArchivo = fopen("Propiedades.dat","rb");
    char tipo_prop[15]; //variable de ingreso para saber el tipo de propiedad buscada
    char auxiliar[15];  //variable para copiar el tipo de propiedad sin afectar el registro
    int i=0,cont=0;     //variable para poner en mayuscula letra por letra (i) y variable para ver si imprimir que no se encuentrar coincidencias(cont)
    if (pArchivo!=NULL){
        fseek(pArchivo,0,SEEK_SET);
        printf("Ingrese el tipo de propiedad a buscar: ");
        gets(tipo_prop);
        fflush(stdin);
        cabecera();
        while (fread(&aux, sizeof(struct Registro), 1, pArchivo) == 1){
            i=0;                                            //inicializo la variable por cada registro
            strcpy(auxiliar,aux.tipoDeProp);                //copio el registro para que no se modifique en el archivo
            if ((strlen(tipo_prop))==(strlen(auxiliar))){   //se pone en mayuscula toda la palabra para comparar
                while(i<strlen(auxiliar)){
                    tipo_prop[i]=toupper(tipo_prop[i]);
                    auxiliar[i]=toupper(auxiliar[i]);
                    i++;
                }
            }
            if(strcmp(auxiliar,tipo_prop)==0){
                printf("%-2d | %-16s | %-21s | %-20s | %-11d | %-5d | %-16.1f | %-19.1f | %-9.1f | %-10s |"
                       "%-17s | %-17s | %-15s | %d \r\n",
                        aux.id, aux.fechaIngreso, aux.zona, aux.ciudadOBarrio, aux.dormitorios, aux.banios,
                        aux.superficieTotal, aux.superficieCubierta, aux.precio, aux.moneda, aux.tipoDeProp, aux.operacion,
                        aux.fechaSalida, aux.activo);
                cont++;
            }
        }
        if(cont==0){
            system("cls");
            printf("No se encontraron coincidencias\n");
            printf("Ingrese cualquier tecla para continuar: ");
            system("cls");
            getchar();
            return;
        }
        printf("Ingrese cualquier tecla para continuar: ");
        getchar();
        fflush(stdin);
        system("cls");
    }
    else printf("Error al abrir el archivo");
}

void obtenerFechaActual(char *fecha) {
    time_t date;
    struct tm *info;

    time(&date);
    info = localtime(&date);

    // Formatear la fecha como "DD-MM-YYYY"
    strftime(fecha, 20, "%d/%m/%Y", info);
}

int existeID(const char *nombreArchivo, int idBuscado) {
    FILE *archivo;
    archivo = fopen(nombreArchivo, "rb");

    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return 0; // En este caso, asumimos que no se encontr� el registro.
    }

    struct Registro registro;

    while (fread(&registro, sizeof(struct Registro), 1, archivo)) {
        if (registro.id == idBuscado) {
            fclose(archivo);
            return 1; // El registro con el ID buscado se encontr�.
        }
    }

    fclose(archivo);
    return 0; // No se encontr� el registro con el ID buscado.
}

bool esNumero(const char *valor) {
    int i = 0;
    int puntoDecimal = 0; // Contador de puntos decimales

    // Comprobamos si el valor empieza con un signo negativo o positivo
    if (valor[0] == '-' || valor[0] == '+') {
        i = 1;
    }

    for (; valor[i] != '\0'; i++) {
        if (isdigit(valor[i])) {
            continue; // El car�cter es un d�gito, sigue verificando
        } else if (valor[i] == '.' && puntoDecimal == 0) {
            puntoDecimal++; // Permitimos un solo punto decimal en n�meros de punto flotante
        } else {
            return false; // Contiene caracteres que no son d�gitos o un punto decimal adicional
        }
    }

    return true; // Es un n�mero v�lido (entero o de punto flotante)
}

//funcion para buscar rango de fecha de ingreso
void buscar_rango(){
    FILE *pArchivo;
    pArchivo=fopen("propiedades.dat","rb");
    int cont=0;

    char fecha_minimo[15];
    printf("Ingrese fecha minima (DD/MM/AAAA): ");
    fgets(fecha_minimo, sizeof(fecha_minimo), stdin);
    fecha_minimo[strcspn(fecha_minimo, "\n")] = 0; // Elimina el salto de l�nea capturado por fgets

    char fecha_maximo[15];
    printf("Ingrese fecha maxima (DD/MM/AAAA): ");
    fgets(fecha_maximo, sizeof(fecha_maximo), stdin);
    fecha_maximo[strcspn(fecha_maximo, "\n")] = 0; // Elimina el salto de l�nea capturado por fgets

    int fecha_min = convertirFechaStringANumero(fecha_minimo);
    int fecha_max = convertirFechaStringANumero(fecha_maximo);

    if (pArchivo != NULL) {
        fseek(pArchivo, 0, SEEK_SET);
        cabecera();
        while (fread(&aux, sizeof(struct Registro), 1, pArchivo) == 1) {
            int fecha_enc = convertirFechaStringANumero(aux.fechaIngreso);
            if (fecha_enc >= fecha_min && fecha_enc <= fecha_max) {
                printf("%-2d | %-16s | %-21s | %-20s | %-11d | %-5d | %-16.1f | %-19.1f | %-9.1f | %-10s |"
                       "%-17s | %-17s | %-15s | %d \r\n",
                        aux.id, aux.fechaIngreso, aux.zona, aux.ciudadOBarrio, aux.dormitorios, aux.banios,
                        aux.superficieTotal, aux.superficieCubierta, aux.precio, aux.moneda, aux.tipoDeProp, aux.operacion,
                        aux.fechaSalida, aux.activo);
                cont++;
            }
        }
        if (cont==0){
            system("cls");
            printf("No se encontraron registros en esas fechas");
        }
        fclose(pArchivo);
        printf("Ingrese cualquier tecla para continuar: ");
        getchar();
        system("cls");
    }
    else printf("Error al abrir�el�archivo");
}

// Funcion para realizar la busqueda por ID
int buscarRegistroPorID(const char *nombreArchivo) {
    FILE *archivo;
    archivo = fopen(nombreArchivo, "rb");

    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return 0; // En este caso, asumimos que no se encontr� el registro.
    }

    struct Registro registro;

    int idBuscado;
    printf("Ingrese el ID a buscar: \n");
    scanf("%d", &idBuscado);

    int encontrado = 0; // Variable para indicar si se encontr� el registro

    while (fread(&registro, sizeof(struct Registro), 1, archivo)) {
        if (registro.id == idBuscado) {
            printf("Resultado encontrado:\n");
            printf("ID de propiedad: %d\n", registro.id);
            printf("Fecha de ingreso: %s\n", registro.fechaIngreso);
            printf("Zona: %s\n", registro.zona);
            printf("Ciudad/Barrio: %s\n", registro.ciudadOBarrio);
            printf("Dormitorios: %d\n", registro.dormitorios);
            printf("Banios: %d\n", registro.banios);
            printf("Superficie Total: %f\n", registro.superficieTotal);
            printf("Superficie Cubierta: %f\n", registro.superficieCubierta);
            printf("Precio: %f\n", registro.precio);
            printf("Moneda: %s\n", registro.moneda);
            printf("Tipo de Operacion: %s\n", registro.operacion);
            printf("Tipo de Propiedad: %s\n", registro.tipoDeProp);
            printf("Fecha de Salida: %s\n", registro.fechaSalida);
            printf("activo: %d\n", registro.activo);

            encontrado = 1; // Indicar que se encontr� el registro
        }
    }

    fclose(archivo);

    return encontrado; // Devolver 1 si se encontr�, 0 si no se encontr�
}

// Funcion para realizar la busqueda por tipo
void buscarPorTipo(const char *nombreArchivo) {
    FILE *archivo;
    archivo = fopen(nombreArchivo, "rb");

    if (archivo == NULL) {
        perror("No se pudo abrir el archivo\n");
        return; // En este caso, asumimos que no se encontr� el registro.
    }

    struct Registro registro;

    char buscarOperacion[50];
    char buscarPropiedad[50];
    printf("Ingrese el Tipo de Operacion: \n");
    scanf("%s", buscarOperacion);
    printf("Ingrese el Tipo de Propiedad: \n");
    scanf("%s", buscarPropiedad);

    priLetMayus(buscarOperacion);
    priLetMayus(buscarPropiedad);

    int encontrados = 0;

    while (fread(&registro, sizeof(struct Registro), 1, archivo)) {
        if (strcmp(registro.operacion, buscarOperacion) == 0 && strcmp(registro.tipoDeProp, buscarPropiedad) == 0) {
            printf("Resultado encontrado:\n");
            printf("ID de propiedad: %d\n", registro.id);
            printf("Fecha de ingreso: %s\n", registro.fechaIngreso);
            printf("Zona: %s\n", registro.zona);
            printf("Ciudad/Barrio: %s\n", registro.ciudadOBarrio);
            printf("Dormitorios: %d\n", registro.dormitorios);
            printf("Banios: %d\n", registro.banios);
            printf("Superficie Total: %f\n", registro.superficieTotal);
            printf("Superficie Cubierta: %f\n", registro.superficieCubierta);
            printf("Precio: %f\n", registro.precio);
            printf("Moneda: %s\n", registro.moneda);
            printf("Tipo de Operacion: %s\n", registro.operacion);
            printf("Tipo de Propiedad: %s\n", registro.tipoDeProp);
            printf("Fecha de Salida: %s\n", registro.fechaSalida);
            printf("activo: %d\n", registro.activo);

            encontrados = 1;
        }
    }

    fclose(archivo);

    if (!encontrados) {
        printf("No se encontraron resultados para la busqueda.\n");
    }
}

const char *tipoMoneda() {
    char seleccion;

    scanf(" %c", &seleccion);
    while (seleccion != 'p' && seleccion != 'P' && seleccion !='d' && seleccion !='D'){
    printf("Por favor ingrese una opci%cn v%clida: ", 162, 160);
    scanf(" %c", &seleccion);
    fflush(stdin);
    }

    if (seleccion == 'P' || seleccion == 'p') {
        return "Pesos";
    } else if (seleccion == 'D' || seleccion == 'd') {
        return "Dolares";
    } else {
        printf("Valor ingresado no v%clido",160);
    }
}

const char *seleccionarTipoPropiedad() {
    int opcion;
    scanf(" %d", &opcion);
    while (opcion != 1 && opcion != 2 && opcion != 3 && opcion !=4){
        printf("Por favor ingrese una opci%cn v%clida: ", 162, 160);
        scanf(" %d", &opcion);
        fflush(stdin);
        }

    switch (opcion) {
        case 1:
            return "Casa";
        case 2:
            return "Departamento";
        case 3:
            return "PH";
        case 4:
            return "Galpon";
        default:
            return "Opcion no valida";
    }
}

const char *seleccionarOperacion() {
    int indice;
    scanf(" %d", &indice);
    while (indice != 1 && indice != 2 && indice != 3){
        printf("Por favor ingrese una opci%cn v%clida: ", 162, 160);
        scanf(" %d", &indice);
        fflush(stdin);
    }
    switch (indice) {
        case 1:
            return "Venta";
        case 2:
            return "Alquiler";
        case 3:
            return "Alquiler temporal";
        default:
            return "Operacion no valida";
    }
}

int submenuBuscar(const char *nombreArchivo) {
    int opcion;

    printf("Submenu de Busqueda:\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por Tipo\n");
    printf("0. Volver al Menu Principal\n");

    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        buscarRegistroPorID(nombreArchivo);
    } else if (opcion == 2) {
        buscarPorTipo(nombreArchivo);
    } else if (opcion == 0) {
        mostrarMenu();
    } else {
        printf("Opci�n no v�lida. Vuelve a intentar.\n");
    }

    return opcion; // Devuelve la opci�n seleccionada
}

// Funcion para modificar un registro
void modificarRegistro(const char *nombreArchivo) {
    FILE *archivo;
    archivo = fopen(nombreArchivo, "r+b");

    if (archivo == NULL) {
        perror("No se pudo abrir el archivo\n");
        return;
    }

    struct Registro registro;
    int idModificar;
    int encontrado = 0; // Variable para indicar si se encontró el registro

    printf("\nIngrese el ID del registro que desea modificar: \n");
    scanf("%d", &idModificar);

    while (fread(&registro, sizeof(struct Registro), 1, archivo)) {
        if (registro.id == idModificar && registro.activo == 1) {
            encontrado = 1;

            printf("Esta seguro que desea modificar los datos de la propiedad ID %i (S/N)? \n", registro.id);
            char respuesta;
            scanf(" %c", &respuesta);

            if (respuesta == 'S' || respuesta == 's') {
                printf("Ingrese la nueva ciudad/barrio: \n");
                scanf(" %[^\n]s", registro.ciudadOBarrio);
                priLetMayus(registro.ciudadOBarrio);

                printf("Ingrese el nuevo precio: \n");
                scanf("%f", &registro.precio);

                // Volver al principio del registro y sobreescribirlo
                fseek(archivo, -sizeof(struct Registro), SEEK_CUR);
                fwrite(&registro, sizeof(struct Registro), 1, archivo);

                printf("Los datos se han modificado correctamente.\n");
            } else {
                printf("No se han realizado modificaciones.\n");
            }

            break;
        }
    }

    fclose(archivo);

    if (!encontrado) {
        printf("No se encontro un registro activo con el ID %d o el ID no existe.\n", idModificar);
    }
}

//Funci�n Baja L�gica
void bajaLogica(const char *nombreArchivo) {
    FILE *archivo;
    struct Registro registro;
    int idABorrar;
    int encontrado = 0;
    char confirmacion;

    printf("Ingrese el ID del registro que desea eliminar: ");
    scanf("%d", &idABorrar);

    archivo = fopen(nombreArchivo, "r+b");
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return;
    }



    while (fread(&registro, sizeof(struct Registro), 1, archivo) == 1) {
        if (registro.id == idABorrar && registro.activo == 1) {
            encontrado = 1;
            printf("Se dar%c de baja a: \n", 160);
            printf("%0s | %0s | %0s | %0s | %0s | %0s | %0s | %0s | %0s | %0s | %0s | %0s | %0s | %0s\n",
            "ID", "Fecha Ingreso", "Zona", "Ciudad", "Dormitorios", "Banios",
            "Sup.Total", "Sup.Cubierta", "Precio", "Moneda", "Tipo Prop", "Operacion",
            "Fecha Salida", "Activo");

            printf("%2d | %2s | %2s | %2s | %2d | %3d | %.2f | %.2f | %.2f | %0s | %5s | %0s | %0s | %0d\n",
               registro.id, registro.fechaIngreso, registro.zona, registro.ciudadOBarrio,
               registro.dormitorios, registro.banios, registro.superficieTotal,
               registro.superficieCubierta, registro.precio, registro.moneda,
               registro.tipoDeProp, registro.operacion, registro.fechaSalida,
               registro.activo);

            printf("�Desea eliminar este registro? S/N: ");
            scanf(" %c", &confirmacion);
            fflush(stdin);

            while (confirmacion != 'S' && confirmacion != 's' && confirmacion != 'N' && confirmacion !='n'){
            printf("Por favor ingrese una opci%cn v%clida: ", 162, 160);
            scanf(" %c", &confirmacion);
            fflush(stdin);
            }

            if(confirmacion== 's' || confirmacion=='S'){
            registro.activo = 0;
            obtenerFechaActual(registro.fechaSalida);
            fseek(archivo, -sizeof(struct Registro), SEEK_CUR);
            fwrite(&registro, sizeof(struct Registro), 1, archivo);
            printf("El registro se ha eliminado\n");
            break;
        } else{
            printf("No se ha eliminado el registro\n");
        }
    }
    }

    fclose(archivo);

    if (!encontrado) {
        printf("No se encontr%c un registro activo con ID %d o el ID no existe.\n", 162, idABorrar);
    }
}

void bajaFisica(FILE *pA) {
    FILE *temp;
    FILE *archivoTexto;
    struct Registro prop;

    pA = fopen("propiedades.dat", "rb");

    archivoTexto = fopen("bajas_fisicas.txt", "w");

    if (pA == NULL || temp == NULL || archivoTexto == NULL) {
        perror("Error al abrir archivos.");
        return;
    }

    fseek(pA, 0, SEEK_SET);
    temp = fopen("propiedades.temp", "w+b");

    while (fread(&prop, sizeof(struct Registro), 1, pA) == 1) {
        if (prop.activo == 0) {
            // Guardar el registro en el archivo de texto antes de eliminarlo
            fprintf(archivoTexto, " %5d | %12s | %12s | %13s | %11d | %4d | %10.2f | %13.2f | %6.2f | %6s | %13s | %15s | %12s | %d\n", prop.id, prop.fechaIngreso, prop.zona, prop.ciudadOBarrio, prop.dormitorios, prop.banios, prop.superficieTotal, prop.superficieCubierta, prop.precio, prop.moneda, prop.tipoDeProp, prop.operacion, prop.fechaSalida, prop.activo);
        } else {
        //    fseek(temp, 0, SEEK_SET);
            fwrite(&prop, sizeof(struct Registro), 1, temp);
        }
    }

    fclose(temp);
    fclose(pA);
    fclose(archivoTexto);

    remove("propiedades.dat"); // Eliminar el archivo original
    rename("propiedades.temp", "propiedades.dat"); // Renombrar el archivo temporal

    printf("\n***-- Baja física satisfactoria --***\n");
}

void listarBajasFisicas(const char *nombreArchivo) {
    FILE *archivo;
    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return;
    }

    struct Registro registro;

    cabecera();

    // Leer y mostrar cada registro de la estructura Registro
    while (fscanf(archivo, "%d %s %s %s %d %d %f %f %f %s %s %s %s %d",
                &registro.id, registro.fechaIngreso, registro.zona,
                registro.ciudadOBarrio, &registro.dormitorios, &registro.banios,
                &registro.superficieTotal, &registro.superficieCubierta,
                &registro.precio, registro.moneda, registro.tipoDeProp,
                registro.operacion, registro.fechaSalida, &registro.activo) == 14 ) {
        // Mostrar los datos del registro en forma de tabla
        printf("%-5d%-15s%-20s%-20s%-12d%-7d%-16.2f%-18.2f%-12.2f%-10s%-15s%-15s%-7d\n",
            registro.id, registro.fechaIngreso, registro.zona, registro.ciudadOBarrio,
            registro.dormitorios, registro.banios, registro.superficieTotal,
            registro.superficieCubierta, registro.precio, registro.moneda,
            registro.tipoDeProp, registro.operacion, registro.activo);
    }


    fclose(archivo);
}

void priLetMayus(char *str) {
    // Verifica si la cadena es nula o est� vac�a
    if (str == NULL || str[0] == '\0') {
        return;
    }

    // Convierte el primer car�cter a may�sculas si es una letra
    if (isalpha(str[0])) {
        str[0] = toupper(str[0]);
    }
}

bool Cadena(const char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isalpha(cadena[i])) {
            return false; // Se encontr� un car�cter que no es una letra
        }
    }
    return true; // Todos los caracteres son letras
}

// Funci�n para listar registros de un archivo en la consola
void listarRegistros(const char *nombreArchivo) {
   char opc;
    fflush(stdin);
    do{
        printf("a) Listar todos\n");
        printf("b) S%clo el campo activo\n",162);
        printf("c) Ingresar por teclado un tipo de propiedad\n");
        printf("d) Ingresar un rango de tiempo de ingreso\n");
        printf("Ingrese 0 para salir\n\n");
        scanf("%c",&opc);
        fflush(stdin);
        switch (opc){
            case 'a':
            case 'A':
                system("cls");
                listar_todos();
                break;
            case 'b':
            case 'B':
                system("cls");
                mostrar_activos();
                break;
            case 'c':
            case 'C':
                system("cls");
                mostrar_prop();
                break;
            case 'd':
            case 'D':
                system("cls");
                buscar_rango();
                break;
            case '0':
                return;
            default:
                printf("Ha ingresado una opci%cn incorrecta, ingrese cualquier tecla para reintentar: ",162);
                getchar();
                fflush(stdin);
                system("cls");
                break;
        }
    }while(opc!='a' && opc!='A' && opc!='b' && opc!='B' && opc!='c' && opc!='C' && opc!='d' && opc!='D');
}

// Funci�n para escribir registros en un archivo binario
void agregarPropiedad(const char *nombreArchivo) {
    struct Registro nuevaPropiedad;
    char fecha[80];
    char zonaProp[30];
    char ciudad[30];
    char cero[2] = "0";
    int numUno = 1;
    int existeProp;

    FILE *archivo = fopen(nombreArchivo, "r+b");
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return;
    }

    printf("\nIngrese el n%cmero ID de la propiedad: ", 163);
        while (1) {
            if (scanf("%d", &nuevaPropiedad.id) != 1 || nuevaPropiedad.id < 0) {
                printf("Entrada no v%clida. Debe ingresar un n%cmero: ",160,163);
                while (getchar() != '\n');
            } else {
                existeProp = existeID(nombreArchivo, nuevaPropiedad.id);
                if (existeProp) {
                    printf("El ID ya existe, por favor elija otro: ");
                    while (getchar() != '\n');
                } else {
                    break;
                }
            }
        }
    fflush(stdin);

    obtenerFechaActual(fecha);
    strcpy(nuevaPropiedad.fechaIngreso, fecha);

    printf("\nIngrese zona de la propiedad: ");
    gets(zonaProp);
    priLetMayus(zonaProp);
    strcpy(nuevaPropiedad.zona, zonaProp);


    printf("\nIngresar la ciudad o barrio de la propiedad: ");
    gets(ciudad);
    priLetMayus(ciudad);
    strcpy(nuevaPropiedad.ciudadOBarrio, ciudad);



    printf("\nCantidad de dormitorios: ");
    while(1){
        char input[100];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Elimina el car�cter de nueva l�nea
        int dormitorios = atoi(input);

        if (!esNumero(input)) {
            printf("Entrada no v%clida. Debe ingresar un n%cmero: ", 160,163);
            continue; // Volver a solicitar entrada
        } else if (dormitorios < 0) {
            printf("La cantidad de dormitorios no puede ser negativa, elija un n%cmero positivo: ",163);
            continue;
        } else {
            nuevaPropiedad.dormitorios = dormitorios; // Asigna el valor a registro.dormitorios
            break;
        }
    }


    printf("\nCantidad de ba%cos: ",164);
    while(1){
        char input[100];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Elimina el car�cter de nueva l�nea
        int banios = atoi(input);

        if (!esNumero(input)) {
            printf("Entrada no v%clida. Debe ingresar un n%cmero: ",160,163);
            continue; // Volver a solicitar entrada
        } else if (banios < 0) {
            printf("La cantidad de ba%cos no puede ser negativa, elija un n%cmero positivo: ", 164,163);
            continue;
        } else {
            nuevaPropiedad.banios = banios; // Asigna el valor a registro.dormitorios
            break;
        }
    }

    printf("\nSuperficie total: ");
    while (1) {
        if (scanf("%f", &nuevaPropiedad.superficieTotal) != 1) {
            printf("Entrada no v%clida. Debe ingresar un n%cmero: ",160,163);
            // Limpia el b�fer de entrada
            while (getchar() != '\n');
            continue; // Volver a solicitar entrada
        }

        if (nuevaPropiedad.superficieTotal < 0) {
            printf("La superficie total no puede ser negativa, elija un n%cmero positivo: ",163);
        } else {
            // No hay necesidad de usar la variable supTotal aqu�
            break;
        }
    }

    printf("\nSuperficie cubierta: ");
    while (1) {
        if (scanf("%f", &nuevaPropiedad.superficieCubierta) != 1) {
            printf("Entrada no v%clida. Debe ingresar un n%cmero: ", 160,163);
            // Limpia el b�fer de entrada
            while (getchar() != '\n');
            continue; // Volver a solicitar entrada
        }

        if (nuevaPropiedad.superficieCubierta < 0) {
            printf("La superficie cubierta no puede ser negativa, elija un n%cmero positivo: ",163);
        } else {
            // No hay necesidad de usar la variable supTotal aqu�
            break;
        }
    }

   printf("\nPrecio de la propiedad: ");
    while (1) {
        if (scanf(" %f", &nuevaPropiedad.precio) != 1) {
            printf("Entrada no v%clida. Debe ingresar un n%cmero: ", 160,163);
            // Limpia el b�fer de entrada
            while (getchar() != '\n');
            continue; // Volver a solicitar entrada
        }

        if (nuevaPropiedad.precio < 0) {
            printf("El precio de la propiedad no puede ser negativo, elija un n%cmero positivo: ",163);
        } else {
            // No hay necesidad de usar la variable supTotal aqu�
            break;
        }
    }


    printf("\nElija tipo de moneda, 'P' para pesos o 'D' para dolares: ");
    strcpy(nuevaPropiedad.moneda, tipoMoneda());

    printf("\n1. Casa \n2. Departamento \n3. PH \n4. Galpon \nElija con el indice el tipo de propiedad: ");
    strcpy(nuevaPropiedad.tipoDeProp, seleccionarTipoPropiedad());

    printf("\n1. Venta \n2. Alquiler \n3. Alquiler temporal \nElija con el indice la operacion deseada: ");
    strcpy(nuevaPropiedad.operacion, seleccionarOperacion());

    strcpy(nuevaPropiedad.fechaSalida, cero);

    nuevaPropiedad.activo = numUno;

    if (nuevaPropiedad.id == 1){
        fseek(archivo,0,SEEK_SET);
        fwrite(&nuevaPropiedad,sizeof(struct Registro),1,archivo);}
    else {
        fseek(archivo,(nuevaPropiedad.id-1)*sizeof(struct Registro),SEEK_SET);
        fwrite(&nuevaPropiedad,sizeof(struct Registro),1,archivo);
        }

    printf("\nPropiedad ingresada:\n-ID: %-2d\n-Fecha de ingreso: %-16s\n-Zona: %-21s\n-Ciudad: %-20s\n-Domitorios: %-11d\n-Banios: %-5d\n-Superficie total: %-16.1f\n-Superficie cubierta: %-19.1f \
           \n-Precio: %-9.1f\n-Moneda: %-10s\n-Tipo de Propiedad: %-17s\n-Operacion: %-17s\n-Fecha de salida: %-15s\n-Activo: %d \r\n",
                       nuevaPropiedad.id, nuevaPropiedad.fechaIngreso, nuevaPropiedad.zona, nuevaPropiedad.ciudadOBarrio, nuevaPropiedad.dormitorios, nuevaPropiedad.banios,
                       nuevaPropiedad.superficieTotal, nuevaPropiedad.superficieCubierta, nuevaPropiedad.precio, nuevaPropiedad.moneda, nuevaPropiedad.tipoDeProp, nuevaPropiedad.operacion,
                       nuevaPropiedad.fechaSalida, nuevaPropiedad.activo);

    fclose(archivo);
}

// Funci�n para convertir una fecha en formato DD/MM/AAAA a un n�mero entero para facilitar la comparaci�n
int convertirFechaStringANumero(char *fechaString) {
    int dia, mes, anio;
    sscanf(fechaString, "%d/%d/%d", &dia, &mes, &anio);
    return (anio * 10000 + mes * 100 + dia);
}
#endif // MILIBRERIA_H_INCLUDED
