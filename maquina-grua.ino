
//biblioteca para servomotores
#include <Servo.h>

Servo garra;
Servo base;//base giratoria

//motor A para la pinza
int motorA_1 = 5; 
int motorA_2 = 6;

//motor B para que la garra baje y suba
int motorB_1 = 7;
int motorB_2 = 8;

int boton = 4;// botón para lanzar garra

//variable para potenciometros 
int pot = A0;
int pot2 = A1;

int sensorMoneda = 12;// sensor herradura infrarrojo para detectar moneda
int piezo =11; //variable para piezo produce sonido


int creditos = 0;
// variables para que el potenciometro controle motor adelante y atras
int adelante;
int atras;

int valpot;

void setup()
{
  Serial.begin(9600);

  //pines pwm, simula pines de entrada análogos 
  garra.attach(3);//inicializa pines servo de garra y la base
  base.attach(9);

 //inicializa pines motor A
  pinMode (motorA_1, OUTPUT);  
  pinMode (motorA_2, OUTPUT);  
   
  pinMode (motorB_1, OUTPUT);  
  pinMode (motorB_2, OUTPUT);   

  //posiciones iniciales para garra y la base
  base.write(70);
  garra.write(10);//20
  
  pinMode(piezo, OUTPUT);
  pinMode(sensorMoneda , INPUT);  //d

  

}
void loop()
{
 insertaCredito();// inserta creditos
 Serial.println(creditos);
 if(creditos > 0){// si los créditos son mayores a 0 entonses inicia juego
 start();
 }

}

void insertaCredito(){//función para aumentar creditos cada vez que el piezo detecta una moda 
  int value = 0;  //y repoduce sonido el piezo
  value = digitalRead(sensorMoneda );  //lectura digital de pin
  if (value == LOW) {
      Serial.println("Créditos insertado");
     analogWrite(piezo, 370);
     delay(500);
     analogWrite(piezo, 330);
      delay(500);
     analogWrite(piezo, 0);
        creditos++;
  }

  delay(100);
  }
  
void start(){// inicia juego
 valpot = analogRead(pot);//lectura de potenciometros, y pasa los valores mapeados a el motor A
 adelante = map (valpot,0,1023,0,255); //
 atras = map (valpot,0,1023,255,0);
 
 analogWrite(motorA_1,atras);
 analogWrite(motorA_2,adelante);

int valpo2 = map(analogRead(pot2), 0, 1023, 0, 180);
// valor proporcional a la escala del servomotor (valor entre 0 y 180) para la base de la grua

base.write(valpo2);// se mueve la bese dependiendo el valor mapeado del potenciometro

int pulsa = digitalRead(boton);// si presiona el botón entonces baja la pinza o garra ( motor B)
if(pulsa == HIGH){
    pinza();    
    
  }
 
}
void pinza(){

  digitalWrite (motorB_1, HIGH);// Baja motor B
  digitalWrite (motorB_2, LOW);
  delay(800);

  analogWrite(motorB_1,LOW);// Apaga motor B
  analogWrite(motorB_2,LOW);
  delay(1000);

  // funcion garra
  garraFun();
  digitalWrite (motorB_1, LOW);// Sube motor B
  digitalWrite (motorB_2, HIGH); 
  delay(800); 
  analogWrite(motorB_1,LOW);// Apaga motor B
  analogWrite(motorB_2,LOW);
  delay(1000);
  terminar_juego();// función para terminar juego
  }


  void terminar_juego(){

    base.write(10);// la base se posiciona en donde la pinsa soltará lo que atrapo
    delay(500);
    analogWrite(piezo, 380); // repoduce sonido
    delay(1000);
    analogWrite(piezo, 0);
    delay(500);
    garra.write(10); // la garra abre para soltar
  // Esperamos 1 segundo
    delay(1000);
    base.write(70); //la base se coloca en su posición inicial
    delay(500); 
   creditos--; // créditos disminuyen
  }

void garraFun(){// CUANDO BAJA LA GARRA APRIETA Y SUBE
  garra.write(10);
  // Esperamos 1 segundo
  delay(1000);
  garra.write(65);
  // Esperamos 1 segundo
  delay(1000);
  }
 void stop(){ // para motor A
 analogWrite(motorA_1,LOW);
 analogWrite(motorA_2,LOW);
  }
