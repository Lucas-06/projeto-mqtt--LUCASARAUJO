#include <PubSubClient.h>
#include <UIPEthernet.h>
#include <SPI.h>

byte mac[] = {0xC8,0x45,0x17,0xDF,0x5D,0x67}; 
boolean mensagem;


int pino2 = 2;
bool estado_sensor;

EthernetClient client;
PubSubClient mqttClient(client);

void setup() {

  pinMode(pino2,INPUT_PULLUP);
  Serial.begin(9600);
  
  Ethernet.begin(mac);

  Serial.begin(9600);

  mqttClient.setServer("3.82.94.158", 1883);
  
  Serial.print("O IP do Arduino e: ");
  Serial.println(Ethernet.localIP());
  
  Serial.print("A Mascara de Rede do Arduino e: ");
  Serial.println(Ethernet.subnetMask());
  
  Serial.print("O Gateway do Arduino e: ");
  Serial.println(Ethernet.gatewayIP());

  Serial.println("");

  delay(5000);
}

void loop() {

  mqttClient.connect("lucasaraujo");

  estado_sensor = digitalRead(pino2);
  Serial.println("");
  Serial.println("");


  if(estado_sensor == 1){

    mensagem = mqttClient.publish("lucasaraujo-t", "RACK ABERTO");
    delay(500);
    
  }
  else{
    
    mensagem = mqttClient.publish("lucasaraujo-t", "RACK FECHADO");
    delay(500);
    
  }
  
  mqttClient.loop();
  
  delay(500);
  
}
