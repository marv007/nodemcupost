#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid="marvin";
const char* password="12345678c";

float vref = 3.3;
float resolucion = vref/1023;

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.print("Conectando a la red wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("¡Conexión exitosa!");
}

void loop(){
  if (WiFi.status() == WL_CONNECTED){
    float temperatura = analogRead(A0);
    temperatura = (temperatura*resolucion);
    temperatura= temperatura*100;
    

    Serial.print("Temperatura: ");
    Serial.println(temperatura);

    String texto = "temperatura=";
    texto +=temperatura;
    
    HTTPClient http; //Instancia de la clase HTTPClient que sirve para inicializar y cerrar una conexión
    http.begin("http://192.168.43.47:8000/temperatura");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCod = http.POST(texto);
    
    if(httpCod == 200){
        String respuesta = http.getString();
        Serial.println("El servidor respondió: ");
        Serial.println(respuesta);

      }
    
    
    
    http.end(); //Close connection
  }
  delay(5000);
  Serial.println("");
}
