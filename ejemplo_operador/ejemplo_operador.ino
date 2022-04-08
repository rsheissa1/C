/*
 * Ejemplo de operadores
 * Por: Roberto Castañeda Sheissa
 * Fecha: 8 de abril 2022
 * 
 * Este programa permite experimentar el uso y aplicaciones
 * del operador módulo
 */

 // Bibliotecas
#include <Serial.h>
 // Constantes

// Variables
int dato = 0;

 // Definición de objetos

 // Condiciones iniciales - Se ejectua sólo una vez al energizar
 void setup()
 {
  // Inicio void de void setup()
  // Aquí va código
  Serial.begin(115200); // Establece comunicación serial y velocidad de transmisión
  Serial.println("Comunicacion Serial iniciada");
 } // Fin void setup

// Cuerpo del programa - Se ejecuta constantemente
void loop()
{ // Inicio de void loop
  // Coloca código aquí, para ejecutarse indefinidamente

  // Incremento
  //dato = dato +1;
  dato++;

  if (dato > 8)
  {
    dato = 0;
  }

  //dato %= 8;
  
} // Fin void loop

// Funciones del usuario
