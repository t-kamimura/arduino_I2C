# arduino_I2C
arduinoでI2C通信をするプログラム群

## master <- slave
マスターからリクエストを送り，スレーブからデータを送るプログラム

### データの送受信テスト
1. master
スレーブからデータを取ってくる
2. slave
マスターにデータを送る

### センサーデータの送受信
1. master_sensor
スレーブから2個のセンサーデータを受取る
2. slave_sensor
マスターにセンサー2個のデータを送る

## master <- slave
マスターからデータを送り，スレーブが受け取るプログラム
1. master_writer
slave_receiverにデータを送る
2. slave_receiver
master_writerからデータを受け取る
データをSDに書き込む機能もつけました
