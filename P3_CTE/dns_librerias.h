#define _CRT_SECURE_NO_WARNINGS
#pragma once

//Los archivos termiandos en .h son las cabeceras en C. Aquí puedo poner funciones y solo tengo que llamrla en main como una biblioteca más.
//Este documento lo usamos para declarar las funci´´ones que usaraemos en main y en otros archivos.

#ifndef DNS_UTILS_H //Estás dos lineas evitan que el contenido del archivo se incluya más de una vez en el mismo proyecto.
#define DNS_UTILS_H

int imprimirContenido(const char* RutaAcceso); //Función para que imprima el contenido de un archivo en pantalla, en este caso recibiendo la ruta de archivo como argumento,
int muestraAdaptadorDNS(const char* nombreAdaptador); //Fución para mostrar los servidores NDS configurados en el adpatador de red
int checkDNS (const char* inputFile, const char* outputFile); //Función para leers las IP del archivo DNSip.txt y hace ping con los que está disponibles. Lo guarda en un arhivo temporal.
int FAST_DNS(const char* nombreAdaptador, const char* tempFile, char* fastDNS); //Función para encontrar cual es el DNS más rápido. LO debe guardar en un archivo tenporal y tendrá que guardar la IP en DNSip.txt
int modificarDNS(const char* nombreAdaptador, const char* dnsIP); //Función para modificar la configuración de DNS al indicado.

#endif // DNS_UTILS_H
