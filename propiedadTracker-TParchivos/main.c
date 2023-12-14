#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "milibreria.h"

// Lider de proyecto: Lautaro Corceiro

// Desarrolladores: Lucas Martin Mascaro - Erika Sofía Franco - Franco Navarro - Agustin Scellato

int main() {
    int opcionElegida;

    do {
        mostrarMenu();

        if (scanf("%i", &opcionElegida) != 1) {
            // La entrada no es un número entero válido
            printf("Entrada no válida. Intente de nuevo.\n");
            // Limpiar el búfer de entrada
            while (getchar() != '\n');
            continue;
        }

        if (opcionElegida == 1) {
            crearArchivo();
        } else if (opcionElegida == 2) {
            listarRegistros("propiedades.dat");
        } else if (opcionElegida == 3) {
            agregarPropiedad("propiedades.dat");
        } else if (opcionElegida == 4) {
            submenuBuscar("propiedades.dat");
        } else if (opcionElegida == 5) {
            modificarRegistro("propiedades.dat");
        } else if (opcionElegida == 6) {
            bajaLogica("propiedades.dat");
        } else if (opcionElegida == 7) {
            bajaFisica("propiedades.dat");
        } else if (opcionElegida == 0) {
            break;
        } else {
            printf("Opción no válida. Intente de nuevo.\n");
        }

        printf("\n");
    } while (1);

    return 0;
}
