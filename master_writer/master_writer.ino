/* Master_writer                    */
/* Slaveにデータを送る              */
/* Slave_receiverとセットで使うこと */

#include <Wire.h>

void setup() {
  Wire.begin(); // MasterとしてI2Cに参加
}

byte x = 0;

void loop() {
  Wire.beginTransmission(8); // アドレス8に向けて通信開始
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // 通信終わり

  x++;
  delay(500);
}

