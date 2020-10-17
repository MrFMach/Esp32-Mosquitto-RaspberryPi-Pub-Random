#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "wifi ssid";
const char* password =  "wifi password";
const char* mqttServer = "mqtt address";
const int mqttPort = 1883;
const char* topic = "topic/test";
const char* mqttUser = "mqtt user name;
const char* mqttPassword = "mqtt password";

WiFiClient esp32Client;
PubSubClient client(esp32Client);

int count = 1;
char message[30];

void setup()
{
  Serial.begin(115200);

  // connect wifi
  Serial.print("\nEsp32 connect with ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Starting wifi connect...");
    WiFi.begin(ssid, password);
    delay(2000);
  }
  Serial.println("Wifi connected!");
  Serial.print("Esp32 IP address: ");
  Serial.println(WiFi.localIP());
}

void connect_broker() {
  // Connect with broker.mqttdashboard.com
  client.setServer(mqttServer, mqttPort);
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword ))
    {
      Serial.println("Connected with MQTT broker!");
    }
    else
    {
      Serial.print("Connect broker fail - State: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void send_message() {
  int randNumber = random(1000);
  sprintf(message, "MQTT Esp32 message %d", randNumber);
  Serial.print("Message sent: ");
  Serial.println(message);

  //Send one message to the broker
  client.publish(topic, message);

  Serial.print("Publishing successfully to: ");
  Serial.println(topic);

  delay(1000);
}

void loop()
{
  connect_broker();
  send_message();
}
