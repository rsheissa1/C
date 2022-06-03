// Programa que utilizará datos del DHT11 y una conexión por MQTT.
// Opcional, se pueden agregar LEDs para indicar el estado de operación.
// Se agregan las bibliotecas requeridas
#include <WiFi.h> // Biblioteca para control de WiFi
#include <PubSubClient.h> // Biblioteca de conexión MQTT
#include "DHT.h" // Biblioteca para conexión con DHT11

// Definición del pin correspondiente
#define DHTPIN 12
#define DHTTYPE DHT11

// Datos de WiFi
// Nomber de la red, esto debe ser un String
const char* ssid = "PrivateLab";
// Contraseña de la red, también de tipo String
const char* password = "112233445566aX2";

// Datos del broker MQTT
// En una red local, escribir la IP asignada de tipo String
const char* mqtt_server = "192.168.0.100";
// IP asignada en formato adecuado
IPAddress server(192,168,0,100);

// Objetos
// Objeto que maneja los datos de conexión WiFi
WiFiClient espClient;
// Objeto que maneja los datos de conexión hacia el Broker
PubSubClient client(espClient);

// Variables
int flashLedPin = 4; // Indica estatus de conexión
int statusLedPin = 33; // Controlado por MQTT
int wait = 5000; // Espera de 5 segundos para envío de mensajes MQTT
long timeNow, timeLast; // Variables control de tiempo
int data = 0; // Contador
float t = 0; // Variable para temperatura

// Configuración tipo de dato para el sensor
DHT dht(DHTPIN, DHTTYPE);

// Función de Configuración
void setup()
{
	// Se configura la velocidad del transmisión serial
	Serial.begin(115200);
	// Configuración del modo de los pines para el ESP32
	pinMode (flashLedPin, OUTPUT);
	pinMode (statusLedPin, OUTPUT);
	// Establece los valores lógicos para los pines
	digitalWrite (flashLedPin, LOW);
	digitalWrite (statusLedPin, HIGH);
	
	Serial.println();
	Serial.println();
	Serial.print("Conectando a ");
	Serial.println(ssid);

	// Activación de dispositivos
	dht.begin(); // DHT11
	WiFi.begin(ssid, password); // ESP32 conexi WiFi

	// Bucle para espera de conexión a la red WiFi
	while (WiFi.status()!= WL_CONNECTED)
	{
		digitalWrite (statusLedPin, HIGH);
		delay(500); // Espera de 500 milisegundos
		digitalWrite (statusLedPin, LOW);
		Serial.print("."); // Indicador de progreso
		delay(5); // Espera de 5 milisegundos
	}

	// Al existir conexión, se puede mostrar lo siguiente
	Serial.println();
	Serial.println();
	Serial.println("WiFi Conectado");
	Serial.println("Dirección IP ");
	Serial.println(WiFi.localIP());
	Serial.println();
	Serial.println("Sensor DHT11 activado");

	// Conexión realizada
	if (WiFi.status() > 0)
	{
		digitalWrite (statusLedPin, LOW);
	}
	
	// Espera para iniciar la comunicación con el Broker
	delay(1000); // Espera de 1000 milisegundos

	// Conexión con el Broker MQTT
	// server tiene el IP asignado en la línea 11
	client.setServer(server, 1883);
	// Activación de la función CallBack
	// Permite recibir mensajes MQTT y ejecutar funciones, en dado caso
	client.setCallback(callback);
	// Espera para prevenir pérdida de información
	delay(1500); // 1500 milisegundos

	timeLast = millis(); // Inicia control de tiempo
} // Fin de setup()

// Función Lazo Principal
void loop()
{
	// Verfica conexión continua con el Broker
	if (!client.connected())
	{
		// En caso de no tener conexión, ejecuta la función
		// para volver a conectarse.
		reconnect();
	}

	// Ejecuta 
	client.loop(); // Cliente esperando mensajes

	timeNow = millis(); // Control de tiempo
	if (timeNow - timeLast > wait) // Manda mensaje MQTT cada 5 segundos
	{
		timeLast = timeNow; // Actualiza seguimiento de tiempo
		// data++; // Incremento a variable para enviarse por MQTT
    t = dht.readTemperature();

    // Verifica que el dato recibido sea correcto
    // de lo contrario, no hay conexión
    if (isnan(t))
    {
      Serial.println(F("No hay conexión"));
      return;
    }
    
		char dataString[8]; // Longitud de mensaje a 8 caracteres
		//dtostrf(data,1,2,dataString); // Función AVR convierte arreglo de caracteres en String
    dtostrf(t,1,2,dataString);
		Serial.print("Contador "); // Solo para visualizar que el evento sucede
		Serial.println(dataString);
		client.publish("codigoIoT/medidor/MQTT", dataString); // Función envía datos por MQTT. Especifica tema y valor.
	}
}

// Función para realizar una acción en caso de recibir un mensaje
void callback(char* topic, byte* message, unsigned int length)
{
	// Muestra en terminal serial que un mensaje se ha recibido
	Serial.print("Mensaje recibido del tema: ");
	Serial.println(topic);

	// Unir mensajes recibidos y guardarlos en una variable String
	String messageTemp; // Declaración de variable donde se guardará el mensaje completo
	for (int i=0; i < length; i++)
	{
		Serial.print((char) message[i]);
		messageTemp += (char) message[i];
	}

	// Verifica que el mensaje se haya formado correctamente
	Serial.println();
	Serial.print("Mensaje guardado en una sola variable: ");
	Serial.println(messageTemp);
}

// Función de reconexión
void reconnect()
{
	// Bucle para realizar la conexión
	while(!client.connected()) // Verifica si existe conexión
	{
		Serial.print("Intentando conexión...");
		if(client.connect("codigoIoT/medidor/MQTT")) // Recibe resultado del intento de conexión
		{
			Serial.println("Conectado");
			//client.subscribe("esp32/output"); // Suscripción al tema
		}
		else // Sin conexión
		{
			Serial.print("Fallo en conexión, Error rc=");
			Serial.print(client.state()); // Imprime el código del error
			Serial.println("Intento de conexión en 5 segundos");
			// Espera de 5 segundos
			delay(5000);
			Serial.println(client.connected()); // Imprime estatus de conexión
		}
	}
}
