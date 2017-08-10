#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(3,OUTPUT);
}

void loop() {
    // スレーブの8番に接続されているデバイスから1バイトのデータを取得
    // 送られてくる値は10進数で255以下、つまり1バイト以内であるため
    Wire.requestFrom(8, 2);
 
    // Wire.available()がfalseになるまでループ
    // 要求より短いデータがくる可能性あり
    while(Wire.available())
    { 
        int c1 = Wire.read(); // 1バイト受信
        Serial.print(c1);
        int c2 = Wire.read(); // 1バイト受信
        Serial.print(",");
        Serial.println(c2);
        
    }
    Serial.println("...");
 
    delay(500);
  
}
