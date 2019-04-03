#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define USE_SERIAL Serial
#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 60
#define BRIGHTNESS 50
#define PIN 5 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Update these with values suitable for your network.

const char* ssid = "91a";
const char* password = "123456789q";
const char* mqtt_server = "akriya.co.in";

WiFiClient espClient;
PubSubClient client(espClient);
 
int delayval = 5000;


git 
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


  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  pinMode(2,HIGH);
  delay(500);
  pinMode(2,LOW);

  //   String q = "";
  // q = (char)payload[0];
  // q = q + (char)payload[1];
  // int num = q.toInt();

  //  Serial.println(num);




for(int j=0;j<NUM_LEDS;j++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(j, strip.Color(255,255,0)); // Moderately bright green color.

    strip.show(); // This sends the updated pixel color to the hardware.

    // delay(delayval); // Delay for a period of time (in milliseconds).
   
  }

delay(delayval);

  for(int k=0;k<=NUM_LEDS;k++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(k, strip.Color(0,0,0)); // Moderately bright green color.

    strip.show(); // This sends the updated pixel color to the hardware.

    // delay(delayval); // Delay for a period of time (in milliseconds).
   
  }

}

void setup() {
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(2, OUTPUT);
  pinMode(2,LOW);
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

  
}