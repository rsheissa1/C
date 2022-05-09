/*
 * Ejemplo de operadores
 * Por: Roberto Castañeda Sheissa
 * Fecha: 8 de abril 2022
 * 
 * Este programa sirve para probar los operadores
 * lógicos y capturar datos del sensor DHT11.
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
#include <DHT.h>

// Definición de objetos
#define DHTPIN 12     // Digital pin connected to the DHT sensor from ESP32
#define DHTTYPE DHT11 // DHT 11

// Constantes para Botones
const int BOTON1 = 14;
const int BOTON2 = 15;
const int BOTON3 = 13;
// Constantes para LEDs
const int LED1 = 4;
const int LED2 = 2;
// Nivel de temperatura
const int TEMP_H = 28;

// Variables
int boton1_dato;
int boton2_dato;
int boton3_dato;

DHT dht(DHTPIN, DHTTYPE);


 // Condiciones iniciales - Se ejectua sólo una vez al energizar
 void setup()
 {
  // Inicio void de void setup()
  // Aquí va código
  pinMode (BOTON1, INPUT_PULLUP); // Configurar el pin donde se conecta el boton como entrada
  pinMode (BOTON2, INPUT_PULLUP);
  pinMode (BOTON3, INPUT_PULLUP);
  pinMode (LED1, OUTPUT); // Configura el pin donde se conecta el led como salida
  pinMode (LED2, OUTPUT);

  Serial.begin(9600); // Establece comunicación serial y velocidad de transmisión
  Serial.println("DHT11 configurado");
  
  dht.begin(); // Activa la comunicación del sensor DHT11
 } // Fin void setup

// Cuerpo del programa - Se ejecuta constantemente
void loop()
{ // Inicio de void loop
  // Coloca código aquí, para ejecutarse indefinidamente

  // Wait a few seconds between measurements.
  delay(2000);

  //*********Lectura del sensor **********
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float t = dht.readTemperature();
  // Check if any reads failed from DHT sensor
  if (isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("% Temperature: "));
  Serial.print(t);
  
  //*********Lectura del boton1********
  boton1_dato = digitalRead(BOTON1);
  if (boton1_dato == 1)
  {
    digitalWrite(LED1, LOW);
  }
  else
  {
    digitalWrite(LED1, HIGH);
  }

  //*********Automático por temperatura*****
  if (t > TEMP_H)
  {
    digitalWrite(LED2,HIGH);
  }
  else
  {
    digitalWrite(LED2,LOW);
  }

  //*******Automático por temperatura, sobrecarga y alta demanda******
  boton2_dato = digitalRead(BOTON2);
  boton3_dato = digitalRead(BOTON3);
  if ((t > TEMP_H) || (boton2_dato == 1) || (boton3_dato == 1))
  {
    digitalWrite(LED2, HIGH);
  }
  else
  {
    digitalWrite(LED2,LOW);
  }
  
} // Fin void loop

// Funciones del usuario
