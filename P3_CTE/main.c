#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dns_librerias.h" // Incluye la cabecera con las funciones

int main() {
    char DNSFilePath[999];
    char nombreAdaptador[100];

    // Preguntar al usuario la ruta del archivo dnsips.txt
    printf("Introduce la ruta completa del archivo DNSips.txt:\n");
    if (!fgets(DNSFilePath, sizeof(DNSFilePath), stdin)) {
        fprintf(stderr, "Error leyendo la ruta.\n");
        return 1;
    }

    // Eliminar salto de línea
    DNSFilePath[strcspn(DNSFilePath, "\n")] = '\0';

    // Quitar comillas si las hay
    if (DNSFilePath[0] == '"' && DNSFilePath[strlen(DNSFilePath) - 1] == '"') {
        DNSFilePath[strlen(DNSFilePath) - 1] = '\0'; // Quita la última comilla
        memmove(DNSFilePath, DNSFilePath + 1, strlen(DNSFilePath)); // Quita la primera comilla
    }

    // Mostrar contenido del archivo
    printf("\nContenido del archivo:\n");
    if (!imprimirContenido(DNSFilePath)) {
        fprintf(stderr, "Error al leer el archivo %s.\n", DNSFilePath);
        return 1;
    }

    // Preguntar al usuario el adaptador de red
    printf("\nIntroduce el nombre del adaptador de red que deseas modificar: ");
    scanf("%99s", nombreAdaptador);

    // Mostrar los servidores DNS configurados en el adaptador
    printf("\nServidores DNS configurados en el adaptador %s:\n", nombreAdaptador);
    if (!muestraAdaptadorDNS(nombreAdaptador)) {
        fprintf(stderr, "Error al obtener los servidores DNS del adaptador %s.\n", nombreAdaptador);
        return 1;
    }

    // Chequear las IPs del archivo y guardar las accesibles en un archivo temporal
    printf("\nComprobando accesibilidad de las IPs...\n");
    if (!checkDNS(DNSFilePath, "temp_dns.txt")) {
        fprintf(stderr, "Error al comprobar accesibilidad de las IPs.\n");
        return 1;
    }

    // Determinar el DNS más rápido
    printf("\nDeterminando el servidor DNS mas rapido...\n");
    char DNS[32];
    if (!FAST_DNS(nombreAdaptador, "temp_dns.txt", DNS)) {
        fprintf(stderr, "Error al determinar el servidor DNS mas rapido.\n");
        return 1;
    }

    // Configurar el DNS más rápido
    printf("\nConfigurando el servidor DNS mas rapido (%s) en el adaptador %s...\n", DNS, nombreAdaptador);
    if (!modificarDNS(nombreAdaptador, DNS)) {
        fprintf(stderr, "Error al configurar el servidor DNS en el adaptador %s.\n", nombreAdaptador);
        return 1;
    }

    printf("Configuracion completada exitosamente.\n");
    return 0;
}
