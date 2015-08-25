/*
 Basic MQTT example

  - connects to an MQTT server
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
  
  AN IMPORTANT NOTE: This uses the PubSub library from 
  https://github.com/Imroy/pubsubclient
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <elapsedMillis.h>
#include <Streaming.h>
#include "controller.cpp"

/*
  Configure wifi and MQTT Server
*/

const char *ssid =	"HOME-1972";		// cannot be longer than 32 characters!
const char *pass =	"9BC5A011D3345830";		//

// Update these with values suitable for your network.
IPAddress server(10, 0, 0, 15);

WiFiClient wclient;
PubSubClient client(wclient, server);



/*
  MQTT Recieve handling
*/

void callback(const MQTT::Publish& pub) {
  // handle message arrived
  Serial<<"Recieved message in : " << pub.topic() << " :: " << pub.payload_string() << endl;
}

/*
  Create instances for all the controllers
*/
Controller_I2C controller1(1);
Controller_I2C controller2(2);
Controller_I2C controller3(3);


void setup()
{
  // Setup console
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();

  client.set_callback(callback);

  WiFi.begin(ssid, pass);

  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
  }

  if (client.connect("arduinoClient")) {
    Serial<<"Shark 1 connected to MQTT"<<endl;
    client.publish("/landshark/1/status", "Shark 1 online");
    client.subscribe("/landshark/1/input");
  }
}


elapsedMillis sender;

void loop()
{
  client.loop();


  if (sender > 3000) {
    sender = 0;
    String s=String(millis()) ;
    client.publish("/landshark/1/status",s );
    client.publish("/landshark/1/status",s );

  }

}


