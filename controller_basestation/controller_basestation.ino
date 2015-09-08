
/*
This code handles reading the 3 controllers from the operator's station, and then transmits the results to an MQTT broker. 

From there, the controlled sharks will get the information, and respond approprately.
  
  AN IMPORTANT NOTE: This uses the PubSub library from 
  https://github.com/Imroy/pubsubclient
  This library has been updated to operate with the ESP2866, which is the target platform for this code
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <elapsedMillis.h>
#include <Streaming.h>
#include "controller.h"
#include <SPI.h>


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
SPIController controller1(1,4);
SPIController controller2(2,5);
SPIController controller3(3,2);


void setup()
{
  // Setup console
  Serial.begin(115200);
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
    client.publish("/landshark/basestation", "Basestation online");
    client.subscribe("/landshark/+/status");
  }
}


elapsedMillis printer;

void loop()
{
  //Update the MQTT 
  client.loop();
  
  //grab new data from the controllers
  controller1.update();
  controller2.update();
  controller3.update();
  
  
  
  //update our shark with any relevant button updates
  if(controller1.upUpdated()){
    client.publish("/landshark/1/input/up",controller1.upPressed()?"true":"false");
  }
  if(controller1.downUpdated()){
    client.publish("/landshark/1/input/down",controller1.downPressed()?"true":"false");
  }
  if(controller1.leftUpdated()){
    client.publish("/landshark/1/input/left",controller1.leftPressed()?"true":"false");
  }
  if(controller1.rightUpdated()){
    client.publish("/landshark/1/input/right",controller1.rightPressed()?"true":"false");
  }
  if(controller1.biteUpdated()){
    client.publish("/landshark/1/input/bite",controller1.bitePressed()?"true":"false");
  }
  if(controller1.danceUpdated()){
    client.publish("/landshark/1/input/dance",controller1.dancePressed()?"true":"false");
  }
  
  
  //update our shark with any relevant button updates
  if(controller2.upUpdated()){
    client.publish("/landshark/2/input/up",controller2.upPressed()?"true":"false");
  }
  if(controller2.downUpdated()){
    client.publish("/landshark/2/input/down",controller2.downPressed()?"true":"false");
  }
  if(controller2.leftUpdated()){
    client.publish("/landshark/2/input/left",controller2.leftPressed()?"true":"false");
  }
  if(controller2.rightUpdated()){
    client.publish("/landshark/2/input/right",controller2.rightPressed()?"true":"false");
  }
  if(controller2.biteUpdated()){
    client.publish("/landshark/2/input/bite",controller2.bitePressed()?"true":"false");
  }
  if(controller2.danceUpdated()){
    client.publish("/landshark/2/input/dance",controller2.dancePressed()?"true":"false");
  }
  
  
    //update our shark with any relevant button updates
  if(controller3.upUpdated()){
    client.publish("/landshark/3/input/up",controller3.upPressed()?"true":"false");
  }
  if(controller3.downUpdated()){
    client.publish("/landshark/3/input/down",controller3.downPressed()?"true":"false");
  }
  if(controller3.leftUpdated()){
    client.publish("/landshark/3/input/left",controller3.leftPressed()?"true":"false");
  }
  if(controller3.rightUpdated()){
    client.publish("/landshark/3/input/right",controller3.rightPressed()?"true":"false");
  }
  if(controller3.biteUpdated()){
    client.publish("/landshark/3/input/bite",controller3.bitePressed()?"true":"false");
  }
  if(controller3.danceUpdated()){
    client.publish("/landshark/3/input/dance",controller3.dancePressed()?"true":"false");
  }
  

  
  
  

  //print some human readable things
  if (printer > 3000) {
    printer = 0;
    
    
    
    //int c=controller1.readByte();
    Serial.print("Controller status: ");
    //Serial.println(c);
    
    String s=String(millis()) ;
    client.publish("/landshark/1/status",s );

  }


}


