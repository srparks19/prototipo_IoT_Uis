
#include <WiFi.h>
#include <ESP32Time.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TinyGPS++.h>

HardwareSerial mySerial(2);  // Crea un objeto Serial en el puerto 2
HardwareSerial gpsSerial(1);       // Puerto serie para el módulo GPS NEO-M6 (UART)
TinyGPSPlus gps;                   // Objeto para el procesamiento de datos GPS
unsigned long previousMillisGPS = 0;  // Almacena el tiempo anterior del GPS
const unsigned long intervalGPS = 2000;  // Intervalo de tiempo de 2 segundos para el GPS
#define MHZ19B_BAUDRATE 9600  // Velocidad de comunicación del sensor
#define GPS_BAUDRATE 9600          // Velocidad de comunicación del módulo GPS NEO-M6
#define ONE_WIRE_BUS 19 // Sensor de temperatura en el puerto 19

unsigned long previousMillis = 0;    // Variable para almacenar el tiempo anterior
const unsigned long interval = 1000; // Intervalo de actualización en milisegundos

// Replace the next variables with your SSID/Password combination
const char* ssid = "FLIA_PEREZ_LOPEZ_PLUS";
const char* ssid1 = "FLIA_PEREZ_LOPEZ";
const char* ssid2 = "Galaxy A32F676";
const char* ssid3 = "HUAWEI Mate 20 lite";
const char* password = "sp19iv05ep24";
const char* password2 = "mosd4353";
const char* password3 = "sofy1902";

int co2 = 0;
char datoCmd = 0;
long lastMsg = 0;
char msg[50];
int value = 0;
float temperatura = 0.0;
float latitude = 0.0;
float longitude = 0.0;

OneWire oneWire(ONE_WIRE_BUS); // Baudios de inicialización
DallasTemperature sensors(&oneWire); // Inicio de sensor de temperatura


// Conexion del mqtt
const char* mqtt_server = "127.0.0.1";
const char* mqtt_server1 = "0.0.0.0";
const char* mqtt_server2 = "172.17.0.2";
const char* mqtt_server3 = "192.168.1.8";
const char* mqtt_server4 = "192.168.1.16";
const char* mqtt_server5 = "192.168.43.99";

WiFiClient espClient;
ESP32Time rtc;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);  //iniciailzamos la comunicación
  mySerial.begin(MHZ19B_BAUDRATE, SERIAL_8N1, 16, 17);  // Inicializa el puerto serie para el sensor de CO2
  gpsSerial.begin(GPS_BAUDRATE, SERIAL_8N1, 13, 12);  // Inicializa el puerto serie para el módulo GPS NEO-M6 (pines GPIO13 y GPIO12)
  sensors.begin(); //Inicio del sensor de tempratura
  rtc.setTime(0, 0, 0, 27, 5, 2023); //Inicio del tiempo del esp32
  setup_wifi();
  client.setServer(mqtt_server5, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid3);

  WiFi.begin(ssid3, password3);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
    } else if (messageTemp == "off") {
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  temperaturaC();
  sensorCO2();
  gpsFunction();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    StaticJsonDocument<1024> doc;
    doc["deviceUUID"] = "1";
    doc["topic"] = "estacion1";
    doc["timeStamp"] = String(rtc.getDay()) + "-" + String(rtc.getMonth()) + "-" + String(rtc.getYear()) + " " + String(rtc.getTime());

    // Crear un subdocumento para los valores
    JsonObject values = doc.createNestedObject("values");
    values["CO2"] = co2;
    values["temperatura"] = sensors.getTempCByIndex(0);
    values["latitude"] = latitude;  // Asignar el valor real del sensor 3
    values["longitude"] = longitude;
    doc["status"] = "OK";
    doc["alert"] = false;

    char buffer[1024];
    serializeJson(doc, buffer);
    Serial.println(buffer);
    client.publish("device-messages", buffer);
  }
  delay(2000);
}

void temperaturaC(){
  //Serial.println(" Solicitando temperaturas...");
  sensors.requestTemperatures();  // Enviar el comando para obtener la temperatura
  //Serial.println("Hecho");
  //Serial.print("La temperatura en el dispositivo 1 es: ");
  temperatura = sensors.getTempCByIndex(0);
  //Serial.println(sensors.getTempCByIndex(0));
}

void sensorCO2(){
  unsigned long currentMillis = millis();  // Obtén el tiempo actual

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Actualiza el tiempo anterior

    mySerial.write(0xFF);  // Envía el comando de solicitud de lectura de CO2 al sensor
    mySerial.write(0x01);
    mySerial.write(0x86);
    mySerial.write(0x00);
    mySerial.write(0x00);
    mySerial.write(0x00);
    mySerial.write(0x00);
    mySerial.write(0x00);
    mySerial.write(0x79);

    delay(2000);  // Espera unos segundos para que el sensor realice la medición

    if (mySerial.available() >= 9) {
      byte response[9];
      mySerial.readBytes(response, 9);

      // Procesa los datos recibidos
      co2 = 256 * response[2] + response[3];  // Calcula el valor de CO2 en ppm

      //Serial.print("CO2: ");
      //Serial.println(co2);
    }
  }
}

void gpsFunction(){
  // Lectura del GPS
  unsigned long currentMillisGPS = millis();  // Obtiene el tiempo actual

  if (currentMillisGPS - previousMillisGPS >= intervalGPS) {
    previousMillisGPS = currentMillisGPS;  // Actualiza el tiempo anterior del GPS


    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        if (gps.location.isValid()) {
          latitude = gps.location.lat();
          longitude = gps.location.lng();  // Agrega el signo negativo a la longitud

          // Imprime las coordenadas del GPS en formato decimal
          //Serial.print("Latitud: ");
          //Serial.println(latitude, 6);
          //Serial.print("Longitud: ");
          //Serial.println(longitude, 6);
        }
      }
    }
  }
}
