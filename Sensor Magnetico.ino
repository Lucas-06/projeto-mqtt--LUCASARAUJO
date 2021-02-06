/* Sensor Magnetico

    O objetivo de programa é identificar se a porta do rack está a aberta ou fechada, 
    utilizando um arduino, um sensor magnético e um shield de rede. 

    Criador: Lucas Araujo.
    Data: 27/01/2021
    Ultima Modificação: 03/02/2021

*/

//Bibiotecas nescessárias.
#include <PubSubClient.h>
#include <UIPEthernet.h>
#include <SPI.h>

//Endereço MAC
byte mac[] = {0xC8,0x45,0x17,0xDF,0x5D,0x67}; 
boolean mensagem;

//Definição das Variaveis.
int pino2 = 2;
bool estado_sensor;

EthernetClient client;
PubSubClient mqttClient(client);

void setup() {

  //Definindo os Pinos que serão usados.
  pinMode(pino2,INPUT_PULLUP);

  //Inicio da Serial.
  Serial.begin(9600);

  //Inicio da conexão da Ethernet.
  Ethernet.begin(mac);

  //Definindo Endereço IP do Servidor AWS.
  mqttClient.setServer("54.144.190.205", 1883);
  
  //Definindo algumas mensagens para facilitar a conexão.
  Serial.print("O IP do Arduino e: ");
  Serial.println(Ethernet.localIP());
  
  Serial.print("A Mascara de Rede do Arduino e: ");
  Serial.println(Ethernet.subnetMask());
  
  Serial.print("O Gateway do Arduino e: ");
  Serial.println(Ethernet.gatewayIP());

  Serial.println("");

}

void loop() {

  //Definindo o cliente do Protocolo MQTT.
  mqttClient.connect("lucasaraujo");

  //Variavel de Leitura do Sensor.   
  estado_sensor = digitalRead(pino2);
  Serial.println("");
  Serial.println("");

  //Condição do Sensor.
  if(estado_sensor == 1){

    //Definindo qual o topico e qual mensagem deve aparecer no MQTT Dash.
    mensagem = mqttClient.publish("lucasaraujo-t", "RACK ABERTO");
    Serial.print("RACK ABERTO");
    
    
  }
  else{
    
    //Definindo qual o topico e qual mensagem deve aparecer no MQTT Dash.
    mensagem = mqttClient.publish("lucasaraujo-t", "RACK FECHADO");
    Serial.print("RACK FECHADO");
   
    
  }
  
  mqttClient.loop();
  
}
