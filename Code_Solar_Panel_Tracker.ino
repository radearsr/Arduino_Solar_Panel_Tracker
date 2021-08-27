#include <Servo.h>;

Servo rotator;
Servo panel;

// Servo Rotator
int servor = 180;
int servorLimitHigh = 170;
int servorLimitLow = 5;

// Servo Panel
int servop = 45;
int servopLimitHigh = 120;
int servopLimitLow = 1;

int ldrTl = A0; //Sensor LDR Top Left
int ldrTr = A1; //Sensor LDR Top Right
int ldrBl = A2; //Sensor LDR Bottom Left
int ldrBr = A3; //Sensor LDR Bottom Right

void setup() {
  Serial.begin(9600);
  rotator.attach(8); //Inisiasi Servo rotator untuk Pin 8
  panel.attach(9); //Inisisasi Servo Panel untuk Pin 9
  rotator.write(180);
  panel.write(45);
}

void loop() {
//  Membuat variabel Untuk Hasil Baca Sensor LDR
  int rldrTl = analogRead(ldrTl);
  int rldrTr = analogRead(ldrTr);
  int rldrBl = analogRead(ldrBl);
  int rldrBr = analogRead(ldrBr);

// Membuat Variabel untuk Delay dan Waktu Toleransi
  int tdelay = 10;
  int tol = 90;

// Membuat Variabel Untuk Menghitung Average Value Sensor LDR
  int avt = (rldrTl + rldrTr) / 2; // Average Value Top
  int avb = (rldrBl + rldrBr) / 2; // Average Value Bottom
  int avl = (rldrTl + rldrBl) / 2; // Average value Left
  int avr = (rldrTr + rldrBr) / 2; // Average Value Right

//  Membuat Variabel Untuk Cek Selisih Top dan Bottom
  int sPan = avt - avb; 
  int sRot = avl - avr;
  
//  Kondisi 1
  if(-1*tol > sPan || sPan > tol){
    if(avt > avb){
      servop = ++servop;
      if(servop > servopLimitHigh){
        servop = servopLimitHigh;
      }
    }
    else if(avt < avb){
      servop = --servop;
      if(servop < servopLimitLow){
        servop = servopLimitLow;
      }
    }
    panel.write(servop);
  }

  if(-1*tol > sRot || sRot > tol){
    if(avl > avr){
      servor = --servor;
      if(servor < servorLimitLow){
        servor = servorLimitLow;
      }
    }
    else if(avl < avr){
      servor = ++servor;
      if(servor > servorLimitHigh){
        servor = servorLimitHigh;
      }
    }
    else if(avl = avr){
      delay(5000);
    }
    rotator.write(servor);
  }
  delay(tdelay);
}
