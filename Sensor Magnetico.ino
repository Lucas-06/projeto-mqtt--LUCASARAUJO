Serial.print("A Mascara de Rede do Arduino e: ");
Serial.println(Ethernet.subnetMask());

Serial.print("O Gateway do Arduino e: ");
Serial.println(Ethernet.gatewayIP());

Serial.println("");

delay(5000);
}

void loop() {

mqttClient.connect("lucasaraujo");

//mensagem = mqttClient.publish("lucasaraujo-t", "O RACK ESTA FECHADO");

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