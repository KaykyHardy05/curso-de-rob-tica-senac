#include <RoboCore_Vespa.h>

///////////////////////////////////////////////////////////////////////////////////////

const int TRIGGER = 25;
const int ECHO = 26;

VespaMotors motor;

int sensor_ultrassonico(int pinotrigger,int pinoecho){

  //realiza o pulso de 10 microsegundos no trigger do sensor
  digitalWrite(pinotrigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrigger,LOW);

  //mede o pulso em microsegundos retornado para o echo do sensor
  //e converte o tempo para distancia ao dividir por 58
  return pulseIn(pinoecho,HIGH)/58;
  
}

int Repeat = 0;

///////////////////////////////////////////////////////////////////////////////////////

void setup(){

  Serial.begin(115200);

  pinMode(TRIGGER,OUTPUT);
  pinMode(ECHO,INPUT);

  digitalWrite(TRIGGER,LOW);


  
}

///////////////////////////////////////////////////////////////////////////////////////

void loop(){ // N°1.
  delay(100);

  int distancia = sensor_ultrassonico(TRIGGER,ECHO);
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  Serial.print("Repetir ");
  Serial.print(Repeat);
  Serial.println(" vezes.");
  Serial.print("////////////////////");
  Serial.println(" ");
  delay(100);

///////////////////////////////////////////////////////////////////////////////////////
  motor.forward(85);

  if(distancia <= 15){
  
    Repeat += 1;

    motor.stop();
    delay(150);
    motor.backward(85);
    delay(150);
    motor.turn(75,-100); //esquerda?
    delay(500);

    motor.forward(85);
    delay(300);
    motor.turn(-100,75); //esquerda?
    delay(500);

  } else if(Repeat >0){
    
    Repeat -= 1;
    
    motor.stop();
    delay(150);
    
    motor.turn(-100, 75); //esquerda?
    delay(500);
    motor.forward(85);
    delay(150);
    motor.turn(75,-100); //esquerda?
    delay(500);

  }
///////////////////////////////////////////////////////////////////////////////////////
}