#include <Wire.h>
void setup() {
  Wire.begin(8) ; //アドレスを8に設定
  pinMode(3,OUTPUT);
  Wire.onReceive(myReadLine); //割り込み関数の指定
}

void loop() {
//ここでは何もしない。
}

void myReadLine(int a){
  char c;
  if(Wire.available()) c = (char)Wire.read();
  if(c=='1'){
    digitalWrite(3,HIGH);
  }else if(c=='0'){
    digitalWrite(3,LOW);
  }
}
