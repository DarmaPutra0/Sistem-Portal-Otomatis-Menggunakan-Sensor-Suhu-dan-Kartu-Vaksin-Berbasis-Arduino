#include<SoftwareSerial.h>
SoftwareSerial myserial(2,3);
String kode; //kode = berisi huruf
const int EN2=6; // mengaktifkan motor
const int motor2_l=7; // pin motor
const int motor2_r=8; // pin motor
const int ls=9;  // limit switch
int lsstopstate=1; // status limit switch
const int analogInPin = A0; // membaca hasil dari sensor suhu
int sensorValue = 0; // membaca hasil dari pin sensor suhu
boolean barcod=false;
boolean desinfektan=false;
boolean stsBuka=false;
void setup() {
  Serial.begin(9600);
  pinMode(EN2, OUTPUT);
  pinMode(motor2_l, OUTPUT);
  pinMode(motor2_r, OUTPUT);
  pinMode(ls, INPUT_PULLUP);
  myserial.begin(9600);
  myserial.setTimeout(100);
}

void loop() {
  readBarcode();
   // perintah portal tertutup
   lsstopstate = digitalRead(ls);
   if ((lsstopstate == LOW)){
//      Serial.println("Portal Tertutup");
      analogWrite (EN2, 0);
      digitalWrite(motor2_l, LOW);
      digitalWrite(motor2_r, LOW);
      }
      int sensorValue=analogRead(analogInPin);
    if(sensorValue<250){
      desinfektan=true;
      stsBuka=true;
      Serial.println("Sensor detected");
//      buka();
    }
   //perintah membaca sbarcode
   
  if(barcod&&desinfektan){
   buka(); 
  }
}
void readBarcode(){
  while (myserial.available() > 0) {
    kode = myserial.readString();
  int length = kode.length();
//    P-R2JSHI3K
    if(kode.length()==11){
      barcod=true;
       stsBuka=true;
  // buka();
    }
       
  }
  Serial.println(kode); 
}
void buka(){
  analogWrite (EN2,100); // driver hidup dengan kekuatan 100 dari maksimalnya 225
      digitalWrite(motor2_l, HIGH); // putar kanan alias terbuka
      digitalWrite(motor2_r, LOW); // harus mati, jika tidak maka motor terbuka
      Serial.println("Portal Buka"); // untuk sekedar tampilan
      delay(370); // waktu penundaan selama terbuka
      
      analogWrite (EN2, 0); // motor berhenti karena sudah posisi terbuka
      digitalWrite(motor2_l, LOW); 
      digitalWrite(motor2_r, LOW);
      Serial.println("Portal berhenti");
      delay(4000); // waktu 5 detik untuk melewati portal
      
      analogWrite (EN2, 100); // kekuatan 80 dari 225 untuk proses tutup
      digitalWrite(motor2_l, LOW);
      digitalWrite(motor2_r, HIGH);
      delay(50);
      analogWrite (EN2, 45); // kekuatan 80 dari 225 untuk proses tutup
      digitalWrite(motor2_l, LOW);
      digitalWrite(motor2_r, HIGH);
      delay(100);
      Serial.println("Portal tutup");
      barcod=false;
      desinfektan=false;
      stsBuka=false;
      kode="";
}


