#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#define USE_SERIAL Serial


// Update these with values suitable for your network.

const char* ssid = "ESP";
const char* password = "123456789q";
const char* mqtt_server = "akriya.co.in";

WiFiClient espClient;
PubSubClient client(espClient);

int delayval = 5000;

int num = 0;
int pin = 2;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  String TOP = topic;

if(TOP == "91s/springboardKarta-otaEnabled"){

  pinMode(2,HIGH);
  delay(500);
  pinMode(2,LOW);

 String q = "";
  q = (char)payload[0];
  q = q + (char)payload[1];
   num = q.toInt();

   Serial.println(num);

}


}

void setup() {

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(pin, OUTPUT);
  pinMode(pin, LOW);
  String mac = WiFi.macAddress();
  Serial.println(mac);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...

      client.subscribe("91s/intercom");
      client.subscribe("91s/springboardKarta-otaEnabled");
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

    pinMode(pin,LOW);
    delay(1000);
    pinMode(pin,HIGH);

    if (num == 1 && WiFi.status() == WL_CONNECTED){
  Serial.println("Connected, updating");
  t_httpUpdate_return ret = ESPhttpUpdate.update("https://ashtam55.github.io/.bin", "", "70 0B 6F 62 4F 41 EB 1A 42 3F 73 5A DA 96 98 2D 7F 2B 75 6F");
        switch(ret) {
            case HTTP_UPDATE_FAILED:
                USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                break;

            case HTTP_UPDATE_NO_UPDATES:
                USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                USE_SERIAL.println("HTTP_UPDATE_OK");
                break;
        }
}
}