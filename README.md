# DNS Fast Setter (C App)

**Descripción**

Este proyecto es un proyecto de mis estudios dondé cree una aplicación en **C** para **Windows** que analiza una lista de servidores DNS, comprueba cuáles están accesibles y determina cuál es el más rápido mediante múltiples pruebas de *ping*.
Luego, cambia automáticamente la configuración DNS del adaptador de red elegido utilizando **PowerShell**.

---

**Características principales**

✔ Lee una lista de DNS desde un archivo (`DNSips.txt`)

✔ Muestra los DNS actuales del adaptador de red

✔ Comprueba accesibilidad (ping) de cada servidor

✔ Calcula el DNS más rápido usando tiempo medio y TTL

✔ Configura automáticamente el DNS más rápido en el adaptador

✔ Totalmente automatizado mediante comandos PowerShell

---

**Requisitos**

* Windows 10/11
* Compilador C compatible (MSVC, MinGW, etc.)
* PowerShell habilitado en el sistema
* Permisos para modificar configuración de red

---

**Formato del archivo DNSips.txt**

Debe contener una IP por línea, por ejemplo:

```
8.8.8.8
1.1.1.1
9.9.9.9
208.67.222.222
```

---

**Cómo usar la aplicación**

1. Ejecútala:

   ```
   P3_CTE.exe
   ```
2. Cuando el programa lo pida, introduce la ruta del archivo `DNSips.txt`
   Ejemplo:

   ```
   C:\Users\TuUsuario\Desktop\DNSips.txt
   ```
3. El programa mostrará el contenido del archivo.
4. Introduce el nombre del adaptador de red:
   Ejemplo:

   ```
   Ethernet
   ```

   o

   ```
   Wi-Fi
   ```
5. El programa:

   * Comprobará qué DNS responden (ping)
   * Guardará los accesibles en `temp_dns.txt`
   * Hará pruebas de velocidad (media de 4 pings)
   * Elegirá el mejor DNS
   * Lo configurará automáticamente en el adaptador

---

**Notas de Seguridad**

* Cambiar el DNS requiere permisos de administrador
* El programa usa `system()` y `_popen()` → no introducir entradas no confiables
* El archivo `temp_dns.txt` se sobrescribe en cada ejecución

---

**Posibles futuras mejoras**

🔹 Añadir soporte para IPv6
🔹 Analizar pérdida de paquetes además de promedio de tiempo
🔹 GUI en WinForms o Qt
🔹 Logs con timestamps
🔹 Versión portable sin PowerShell (usando WinAPI)

---

**Autores**
Cèlia Trullà Estruch para la Universidad Oberta de Catalunya y Jesuïtes Educació.
