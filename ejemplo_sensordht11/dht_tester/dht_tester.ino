/*
 * Ejemplo de operadores
 * Por: Roberto Castañeda Sheissa
 * Fecha: 11 de abril 2022
 * 
 * Este programa permite experimentar el uso y aplicaciones
 * de los operadores relacionales.
 * Sensor DHT11.
 * 
 * Connect pin 1 (on the left) of the sensor to +5V
 * NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
 * to 3.3V instead of 5V!
 * Connect pin 2 of the sensor to whatever your DHTPIN is
 * Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
 * Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
 * Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
 * 
 */

 // Bibliotecas
#include "DHT.h"

#define DHTPIN 14 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

 // Constantes

// Variables


 // Definición de objetos

 // Condiciones iniciales - Se ejectua sólo una vez al energizar
 void setup()
 {
  // Inicio void de void setup()
  // Aquí va código
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
 } // Fin void setup

// Cuerpo del programa - Se ejecuta constantemente
void loop()
{ // Inicio de void loop
  // Coloca código aquí, para ejecutarse indefinidamente

  
  
} // Fin void loop

// Funciones del usuario
