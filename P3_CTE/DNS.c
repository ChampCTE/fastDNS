#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <windows.h>

int imprimirContenido(const char* RutaAcceso) { //Función para que imprima el contenido de un archivo en pantalla, en este caso recibiendo la ruta de archivo como argumento,
	//1. Pedimos al usuario la ruta
	FILE* file = fopen(RutaAcceso, "r");//Lectura
	if (!file) return 0;
	//2. Generamos la ruta obtenido y la imprimimos en pantalla
	char linea[256];
	while (fgets(linea, sizeof(linea), file)) {
		printf("%s", linea);
	}
	//3. Cerranos el archivo. Retorna 1 si tiene éxito, 0 si falla.
	fclose(file);
	return 1;
}
int muestraAdaptadorDNS(const char* nombreAdaptador) { //Fución para mostrar los servidores NDS configurados en el adpatador de red
	//1. Generamos un comando para ejecurarlo en PowerShell, utilizamos la ruta que nos ha dado el ususario.
	char commando[300];
	snprintf(commando, sizeof(commando), "powershell.exe Get-DnsClientServerAddress -InterfaceAlias \"%s\"", nombreAdaptador);
	//2. Ejecutamos comando.
	return system(commando) == 0;
}
int checkDNS(const char* inputFile, const char* outputFile) { //Función para leers las IP del archivo DNSip.txt y hace ping con los que está disponibles. Lo guarda en un arhivo temporal.
	//1. Abrimos los archivos
	FILE* in = fopen(inputFile, "r");//Lectura
	FILE* out = fopen(outputFile, "w");//Escritura

	if (!in || !out) {
		if (in) fclose(in);
		if (out) fclose(out);
		return 0;
	}
	//2. Empezamos la lectura de la IP dentro del archivo en ruta
	char ip[17];
	while (fgets(ip, sizeof(ip), in)) {
		ip[strcspn(ip, "\n")] = '\0'; //Eliminamos el salto de liena y ponemos 0.
		char commando[50];
		snprintf(commando, sizeof(commando), "ping -n 1 %s > nul", ip); //Enviamos un paquete.

		if (system(commando) == 0) {
			fprintf(out, "%s\n", ip);
		}
	}
	//3. Cerramos los documentos.
		fclose(in);
		fclose(out);
		return 1;
}
int FAST_DNS(const char* nombreAdaptador, const char* tempFile, char* fastDNS) { //Función para encontrar cual es el DNS más rápido. LO debe guardar en un archivo tenporal y tendrá que guardar la IP en DNSip.txt
	//1. Abrimos el archivo temporal
	FILE* file = fopen(tempFile, "r");//Lectura
	if (!file) return 0;

	char currentIP[32];
	double tiempoMin = DBL_MAX; //De la biblioteca float.h. Representa el valor máximo que puede almancenar una variable
	int maxTTL = -1; //TTL es el Time-To-Live de lo paquetes de datros que se utilizan en los ping. Es -1 porque cualquier TTL real será mayor.

	//2. Leemos cada liena IP y enviamos paquetes de datos para saber cual es el más rápido.
	while (fgets(currentIP, sizeof(currentIP), file)) {
		currentIP[strcspn(currentIP, "\n")] = '\0';

		// Ejecutar ping y medir tiempo/TTL
		char command[100];
		sprintf(command, "ping -n 4 \"%s\"", currentIP);//Enviamos 4 paquetes
		FILE* pingStream = _popen(command, "r"); //_popen crea una canalización y ejecuta un comando. EN este caso en formato de lectura.
		if (!pingStream) continue;

		double tiempoMedio = -1; //Ponemos que el tiempo medio es -1
		int ttl = -1;
		char line[256];

		while (fgets(line, sizeof(line), pingStream)) {
			// Estaremos el TTL
			if (strstr(line, "TTL=")) {
				char* ttlStart = strstr(line, "TTL=");
				ttl = atoi(ttlStart + 4);
			}
			// Extraemos el tiempo medio
			char* timeStart = strstr(line, "Media =");
			if (timeStart != NULL) {
				int avgTemp;
				if (sscanf(timeStart, "Media = %dms", &avgTemp) == 1) {
					tiempoMedio = (double)avgTemp;
				}
			}
		}
		_pclose(pingStream);

		//Comprobamos el tiempo y nos quedamos con el tiempo mmás rapido.
		if (tiempoMedio > 0 && ttl > 0) {
			if (tiempoMedio < tiempoMin) {
				tiempoMin = tiempoMedio;
				maxTTL = ttl;
				strncpy(fastDNS, currentIP, 31);
				fastDNS[32] = '\0'; // Asegurar terminación nula
			}
			else if (tiempoMedio == tiempoMin && ttl > maxTTL) {
				maxTTL = ttl;
				strncpy(fastDNS, currentIP, 32);
				fastDNS[32] = '\0';
			}
		}
	}
	fclose(file);
	return (tiempoMin != DBL_MAX); // Éxito solo si se encontró al menos un DNS.
}
int modificarDNS(const char* nombreAdaptador, const char* dnsIP) { //Función para modificar la configuración de DNS al indicado.
	//1. COnstruimos el commando de powershell con la el alias que hemos puesto y el DNS que ha funcionado más rápido. 
	char commando[300];
	snprintf(commando, sizeof(commando), "powershell.exe Set-DnsClientServerAddress -InterfaceAlias \"%s\" -ServerAddresses \"%s\"", nombreAdaptador, dnsIP);
	//2. Ejecutamos commando.
	return system (commando) == 0;
}