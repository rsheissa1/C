/*
 * Ejemplo de operadores
 * Por: Roberto Castañeda Sheissa
 * Fecha: 8 de abril 2022
 * 
 * Este programa permite experimentar el uso y aplicaciones
 * del operador módulo
 */

 // Bibliotecas
// #include <Serial.h>
 // Constantes

// Variables
int dato = 0;
double timeStart, timeFinish;
 // Definición de objetos

 // Condiciones iniciales - Se ejectua sólo una vez al energizar
 void setup()
 {
  // Inicio void de void setup()
  // Aquí va código
  Serial.begin(115200); // Establece comunicación serial y velocidad de transmisión
  Serial.println("Comunicacion Serial iniciada");
  delay(5000);
 } // Fin void setup

// Cuerpo del programa - Se ejecuta constantemente
void loop()
{ // Inicio de void loop
  // Coloca código aquí, para ejecutarse indefinidamente

  timeStart = micros();

  for (int i = 0; i < 1000; i++)
  {
    dato++;
    if (dato > 8)
    {
      dato = 0;
    }
  }

  timeFinish = micros();
  Serial.print("Con if");
  Serial.println(timeFinish - timeStart); // Imprimir valor del contador
  delay(1000);

  timeStart = micros();

  for (int i = 0; i < 1000 ; i++)
  {
    dato++;
    dato %= 8;
  }

  timeFinish = micros();
  Serial.print("Con operadores");
  Serial.println(timeFinish - timeStart); // Imprime valor del contador
  delay(1000);
  
} // Fin void loop

// Funciones del usuario
