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
#define DHTPIN 14     // Digital pin connected to the DHT sensor from ESP32
#define DHTTYPE DHT11 // DHT 11

// Constantes
const int BOTON1 = 4;
const int LED1 = 2;

// Variables
int dato1;
DHT dht(DHTPIN, DHTTYPE);


 // Condiciones iniciales - Se ejectua sólo una vez al energizar
 void setup()
 {
  // Inicio void de void setup()
  // Aquí va código
  pinMode (BOTON1, INPUT_PULLUP); // Configurar el pin donde se conecta el boton como entrada
  pinMode (LED1, OUTPUT); // Configura el pin donde se conecta el led como salida
  digitalWrite (LED1, LOW); // 0, false, LOW, 1, ture, HIGH

  
  Serial.begin(9600); // Establece comunicación serial y velocidad de transmisión
  Serial.println("DHT11 configurado");
  
  dht.begin(); // Activa la función del sensore
 } // Fin void setup

// Cuerpo del programa - Se ejecuta constantemente
void loop()
{ // Inicio de void loop
  // Coloca código aquí, para ejecutarse indefinidamente

  dato1 = digitalRead(BOTON1); // Lectura digital de boton1
  digitalWrite(LED1,dato1);
  
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C"));
  
} // Fin void loop

// Funciones del usuario
