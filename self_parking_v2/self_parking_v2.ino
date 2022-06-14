#define echoPin_front 10 //on
#define trigPin_front 11 //on
#define echoPin_right A5 //sag_on
#define trigPin_right A2//sag_on
#define echoPin_rear_right A0 //sag_arka
#define trigPin_rear_right A1 //sag_arka
#define MotorL1 13 //in1
#define MotorL2 12 //in2
#define MotorLE 3//enb
#define MotorR1 8//in3
#define MotorR2 7//in4
#define MotorRE 6//ena
#define PWM 225
long sure,sure2,sure3,on_mesafe,sag_mesafe,sag_arka_mesafe;

int maxdist = 20;
int mindist = 10;

int right_data[10];
int front_data[10];
int rear_right_data[10];

int bosluk_sayici = 0;



void setup() {
  pinMode(echoPin_front, INPUT);
  pinMode(trigPin_front, OUTPUT);
  pinMode(echoPin_right, INPUT);
  pinMode(trigPin_right, OUTPUT);
  pinMode(echoPin_rear_right, INPUT);
  pinMode(trigPin_rear_right, OUTPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRE, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT);

  Serial.begin(9600);

}

void loop() {
Main:
  on_mesafe = on_mesafe_olc();
  sag_mesafe = sag_mesafe_olc();
  sag_arka_mesafe = sag_arka_mesafe_olc();
  
  Serial.print("sag on mesafe : ");
  Serial.println(sag_mesafe);
  Serial.print("sag arka mesafe : ");
  Serial.println(sag_arka_mesafe);
  
//  if((sag_mesafe <= maxdist && sag_mesafe >= mindist) && (sag_arka_mesafe <= maxdist && sag_arka_mesafe >= mindist) && (on_mesafe > mindist)){
//    ileri();
//    Serial.println("ileri ilk if");
//    bosluk_sayici = 0;
//    goto Main;
//  }
// 
//  if((sag_mesafe > maxdist) && (sag_arka_mesafe <= maxdist && sag_arka_mesafe >= mindist) && (on_mesafe > mindist)){
//    ileri();
//    Serial.println("ileri ikinci if");
//    goto Main;
//  }
//  if((sag_mesafe > maxdist) && (sag_arka_mesafe > maxdist) && (on_mesafe > maxdist)){
//    ileri();
//    Serial.println("ileri üçiüncü if");
//    bosluk_sayici++;
//    goto Main;
//  }
//  if((sag_mesafe <= maxdist && sag_mesafe >= mindist) &&  (sag_arka_mesafe > maxdist) && (on_mesafe > mindist) && (bosluk_sayici > 15)){
//    dur();
//    Serial.println("durdu");
//    delay(1000);
//    gerisag();
//    Serial.println("geri sag");
//    delay(800);
//    geri();
//    Serial.println("geri");
//    delay(800);
//    gerisol();
//    ////Serial.println("geri sol");
//    delay(1000);
//    ileri();
//    delay(300);
//      
//    
//  goto Main;
//  }
//  if(on_mesafe <= mindist){
//    dur();
//    ////Serial.println("durdu ikinci");
//    goto Main;
//  }

}

//void park_hareket(){
//Function:
//sag_arka_mesafe = sag_arka_mesafe_olc();
//sag_mesafe = sag_mesafe_olc();
//on_mesafe = on_mesafe_olc();
//
//  
//  
// 
//}

long on_mesafe_olc(){
      long mesafe1;
      long sum_on  = 0;
      long avarage_on = 0;
      digitalWrite(trigPin_front,LOW);
      delay(3);
      digitalWrite(trigPin_front,HIGH);
      delay(10);
      digitalWrite(trigPin_front,LOW);
      sure = pulseIn(echoPin_front,HIGH);
      mesafe1 = (sure / 2) / 29.1;
      for(int i = 0; i<10 ;i++){
      front_data[i] = mesafe1;
      sum_on = sum_on + front_data[i]; 
      }
      avarage_on = sum_on / 10;
      if(avarage_on > 2000){
        avarage_on = 2;
      }
      
      return avarage_on;
      
//      Serial.print("On mesafe: ");
//      ////Serial.println(mesafe1);
}
long sag_mesafe_olc(){
      long avarage_sag = 0;
      long sum_sag = 0;
      long mesafe2;
      digitalWrite(trigPin_right,LOW);
      delay(3);
      digitalWrite(trigPin_right,HIGH);
      delay(10);
      digitalWrite(trigPin_right,LOW);
      sure = pulseIn(echoPin_right,HIGH);
      mesafe2 = (sure / 2) / 29.1;

      for(int i = 0; i<10 ;i++){
        right_data[i] = mesafe2;
        sum_sag = sum_sag + right_data[i]; 
      }
      avarage_sag = sum_sag / 10;
      if(avarage_sag > 2000){
        avarage_sag = 2;
      }
      return avarage_sag;
      
//      Serial.print("sol mesafe: ");
//      //Serial.println(mesafe2);
}
long sag_arka_mesafe_olc(){
      long mesafe3;
      long avarage_sag_arka = 0;
      long sum_sag_arka = 0;
      
      digitalWrite(trigPin_rear_right,LOW);
      delay(3);
      digitalWrite(trigPin_rear_right,HIGH);
      delay(10);
      digitalWrite(trigPin_rear_right,LOW);
      sure = pulseIn(echoPin_rear_right,HIGH);
      mesafe3 = (sure / 2) / 29.1;
    
      for(int i = 0; i<10 ;i++){
        rear_right_data[i] = mesafe3;
        sum_sag_arka = sum_sag_arka + rear_right_data[i]; 
      }
      avarage_sag_arka = sum_sag_arka / 10;
      if(avarage_sag_arka > 2000){
        avarage_sag_arka = 2;
      }
      return avarage_sag_arka;
      
//      Serial.print("sag mesafe: ");
//      //Serial.println(mesafe3);
}
void ileri(){
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, PWM);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, PWM);
}
void hafifileri(){
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, PWM-75);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, PWM-75);
}
void geri(){
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, PWM);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  analogWrite(MotorLE, PWM);
}

void dur(){
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 0);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 0);
}
void sol(){
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, PWM);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  analogWrite(MotorLE, 50); 
}
void sag(){
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, 50);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, PWM); 
}
void hafifsol(){
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, PWM-50);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 0);
}
void hafifsag(){
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 0);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, PWM-50);
}
void gerisag(){
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, 0);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  analogWrite(MotorLE, PWM);
}
void gerisol(){
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, PWM+25);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  analogWrite(MotorLE, 0);
}
