#include <Wire.h>

int val1 = 0;
int val2 = 0;

void setup()
{
    Serial.begin(9600);
    Wire.begin(8); // スレーブのアドレスを８に設定
    Wire.onRequest(sendSensor); // マスターに呼ばれたときに呼び出す関数
}
 
void loop()
{
    val1 = analogRead(2);
    val2 = analogRead(3);
    delay(100);
}
 
void sendSensor()
{
    Wire.write(val1); // 1バイト送信
    Wire.write(val2); // 1バイト送信
}
