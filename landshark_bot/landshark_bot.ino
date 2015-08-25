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
#include <Servo.h>
#include "RemoteController.cpp"
#include "sharkbot.cpp"


const char *ssid =	"HOME-1972";		// cannot be longer than 32 characters!
const char *pass =	"9BC5A011D3345830";		//

// Update these with values suitable for your network.
IPAddress server(10, 0, 0, 15);
WiFiClient wclient;
PubSubClient client(wclient, server);


//Set up a tiny remote instance to handle virtual buttons
RemoteController remote(1);


//Create our physical sharkbot
Sharkbot shark;


//Set up our input handling functions
void callback(const MQTT::Publish& pub) {
  // handle message arrived
  String msg = pub.payload_string();
  String topic = pub.topic();

  //Echo things out to serial
  Serial << "Recieved message in : " << pub.topic() << " :: " << msg << endl;

  //trip the last bit of the topic to get the button
  topic = topic.substring(topic.lastIndexOf('/') + 1);

  //The remote class will handle all of the button tracking. 
  remote.setButton(topic, msg);
}

//Create our MQTT connection in advance to simplify things later
MQTT::Connect mqtt_connect = MQTT::Connect("landshark1")
                             .set_will("/landshark/1/status", "Shark 1 offline")
                             .set_keepalive(5);

MQTT::Subscribe mqtt_subs = MQTT::Subscribe("/landshark/1/controller/+")
                            //.add_topic("/landshark/1/jabber");
                            ;

//Misc Variables
int retries = 0;
elapsedMillis heartbeat;

void setup()
{
  // Setup console
  Serial.begin(9600);
  delay(10);

  Serial << "Shark 1 cbooting " << endl;
  Serial << "Chip ID Number " << ESP.getChipId() << endl;

  client.set_callback(callback);


  //Ensure that we're connected to wifi
  while ((WiFi.status() != WL_CONNECTED)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial << "WiFi connected: took " << retries << " attempts" << endl;


    //Connect to MQTT server
    if (client.connect(mqtt_connect)) {
      Serial << "Shark 1 connected to MQTT" << endl;
      client.publish("/landshark/1/status", "Shark 1 online");
      client.subscribe(mqtt_subs);
    }

  }


}



void loop()
{

  //MQTT client loop structure
  client.loop();

  //maintain a heartbeat on serial and server, and reboot if we've totally lost wifi.
  if (WiFi.status() == WL_CONNECTED) {
    //Send a heartbeat
    if (heartbeat > 1000) {
      heartbeat = 0;
      String s = String(millis()) ;
      Serial << "Heartbeat: " << s << endl;
    }
  }
  else if (heartbeat > 12000) {
    Serial << "Lost Wifi: Restarting at time" << heartbeat << endl;
    ESP.reset();
  }
  
  //
  //Now, do some clever things with the shark! :D
  //
  
  //If no one is around, do something reasonable and/or cool.
  if(remote.isIdle()){
    shark.idle();
  }
  
  
  //This is the main shark logic, which goes through it's state machine and controlls the physical shark! 
  shark.update();
  

}

