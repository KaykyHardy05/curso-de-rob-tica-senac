#include <RoboCore_Vespa.h>

///////////////////////////////////////////////////////////////////////////////////////

const int TRIGGER = 26;
const int ECHO = 25;

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

///////////////////////////////////////////////////////////////////////////////////////

void setup(){

  Serial.begin(115200);

  pinMode(TRIGGER,OUTPUT);
  pinMode(ECHO,INPUT);

  digitalWrite(TRIGGER,LOW);

}

///////////////////////////////////////////////////////////////////////////////////////

void loop(){ // N°1.

  int Repeat = 0;

  int distancia = sensor_ultrassonico(TRIGGER,ECHO);
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(100);

///////////////////////////////////////////////////////////////////////////////////////
  motor.forward(85);

  if(distancia < 14){
    motor.stop();
    motor.backward(80);
    delay(200);
    motor.stop();

    motor.turn(80,-80);
    delay(400);

   motor.forward(80); //movimenta o robô para frente
   delay(400); //mantem o movimento do robo
   motor.stop(); //para os motor do robo
   motor.turn(-80, 80); //gira o robo para a esquerda
   delay(400); //mantem o movimento do robo
   motor.forward(80); //movimenta o robo para frente
   delay(400*2); //mantem o movimento do robo
   motor.stop(); //para os motor do robo
   motor.turn(-80, 80); //gira o robo para a esquerda
   delay(400*1.5); //mantem o movimento do robo
   motor.forward(80); //movimenta o robo para frente
   delay(400);
   motor.turn(80, -80);
   delay(400);

  }
///////////////////////////////////////////////////////////////////////////////////////
}