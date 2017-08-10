#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(3,OUTPUT);
}

void loop() {
  char c = Serial.read();
  if(c=='1'){
    digitalWrite(3,HIGH);
    Serial.println("ON");
    Wire.beginTransmission(8) ;             // 通信の開始処理、スレーブのアドレスは８とする
    Wire.write("1",strlen("1"));  // 通信データ送信
    Wire.endTransmission();
  }else if(c=='0'){
    digitalWrite(3,LOW);
    Serial.println("OFF");
    Wire.beginTransmission(8) ;             // 通信の開始処理、スレーブのアドレスは８とする
    Wire.write("0",strlen("1"));  // 通信データ送信
    Wire.endTransmission();
  }
}
