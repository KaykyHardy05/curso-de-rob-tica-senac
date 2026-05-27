/*
  Pino na placa | Conexão referente á
  -------------:|:-------------------
  PINO 0        | TX
  PINO 1        | RX
  PINO 2        | Entrada 3(PONTE H) Esq
  PINO 3        | Entrada 4(PONTE H) Esq
  PINO 4        | Velocidade 1(PONTE H)
  PINO 5        | Velocidade 2(PONTE H)
  PINO 6        | Entrada 3(PONTE H) Dir
  PINO 7        | Entrada 4(PONTE H) Dir
  PINO 8        | Servo Motor 1 & 2
  PINO 9        | Sensor de Distância (ECHO)
  PINO 10       | Sensor de Distância (TRIG)


*/




#include<Servo.h>


Servo servo;
// ==================== PINOS ====================
const int RWAH=6; //Right Wheel Anti-Horario
const int RWH =7; //Right Wheel Horario
const int GVel[2]={4,5}; //General Velocity
const int LWAH=2; //Left Wheel Anti-Horario
const int LWH =3; //Left Wheel Horario

const int Serv=8;



// ==================== VARIÁVEIS ====================
int mover=0;
int virar=0;
  int duracao;
  int distancia;
int countlines;
char command; //acessar o Serial

// ==================== FUNÇÕES DE MOTOR ====================
void RodasEsquerda(int Vel=-1, int Direcao=-1){
  if(Vel == -1 || Direcao == -1){     // Desliga o motor
    analogWrite(GVel[1], 0);
    digitalWrite(LWH, 0);
    digitalWrite(LWAH, 0);
    return;
  }
  
  Vel = constrain(Vel, 0, 255);
 
  analogWrite(GVel[1], Vel);
  digitalWrite(LWH , Direcao);
  digitalWrite(LWAH, !Direcao);
}

void RodasDireita(int Vel=-1, int Direcao=-1){
  if(Vel == -1 || Direcao == -1){     // Desliga o motor
    analogWrite(GVel, 0);
    digitalWrite(RWH, 0);
    digitalWrite(RWAH, 0);
    return;
  }
  
  Vel = constrain(Vel, 0, 255);
 
  analogWrite(GVel, Vel);
  digitalWrite(RWH , Direcao);
  digitalWrite(RWAH, !Direcao);
}

// ==================== BOTÕES ====================
void FuncaoBotaoPressionado()
{
  if(Serial.available()){
     command= Serial.read();
    Serial.print(countlines++);Serial.print("| Recebe: ");Serial.println(command);
  }

  switch(command){
    case 'D':   // □ Virar Direita
      if(virar!=-1){virar=-1;}else{virar=0;}
      break;
      
    case 'A':   // o Virar Esquerda
      if(virar!= 1){virar= 1;}else{virar=0;}
      break;
      
    case 'S':   // ↓ Ré
      if(mover != -1){mover--;}else{mover=0;}
      break;
      
    case 'W':  // ↑ Frente
      if(mover !=  1){ mover++;}else{mover=0;}
      break;
  }
}

// ==================== SENSOR ULTRASONICO ====================
long LerDistUS(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(GVel, OUTPUT);
  pinMode(RWAH, OUTPUT);
  pinMode(RWH , OUTPUT);
  pinMode(LWAH, OUTPUT);
  pinMode(LWH , OUTPUT);

  servo.attach(Serv);
  Serial.begin(9600);
}

void loop()
{
  distancia = 0.0343/2 * LerDistUS(10, 9);
  

  FuncaoBotaoPressionado();

  if(virar == 1) //Esquerda
  {
    servo.write(10);
  }else
  if(virar ==-1) //Direita
  {
    servo.write(160);
  }
  else{          //Reto
    servo.write(85);
  }

  if(mover == 1 /*&& !(distancia<30)*/){                    // Frente
    RodasEsquerda(255, 1);
    RodasDireita (255, 1);
  }
  else if(mover == -1){              // Ré
    RodasEsquerda(255, 0);
    RodasDireita (255, 0);
  }
  else {                             // Parado + Virar no lugar
    RodasEsquerda();                 // Desliga ambos
    RodasDireita();
  }

// ==================== MONITOR SERIAL ====================
  Serial.print("mover: ");
  if(mover == -1)      Serial.println("Tras");
  else if(mover == 0)  Serial.println("Parado");
  else if(mover == 1)  Serial.println("Frente");

  Serial.print("Virar: ");
  if(virar == -1)      Serial.println("Esquerda");
  else if(virar == 0)  Serial.println("Reto");
  else if(virar == 1)  Serial.println("Direita");


  Serial.println();
  Serial.println("------------------------------");
  
  Serial.print("Dist: ");
  Serial.println(distancia);

  if(distancia>0) Serial.println("/!\\ OBJETO DETECTADO /!\\");
  	
  Serial.println();
  Serial.println("______________________________");
  //delay(100);
}
