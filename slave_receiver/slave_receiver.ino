/* Slave_receiver                    */
/* Masterからデータを受け取る        */
/* Master_writerとセットで使うこと   */

#include <Wire.h>
#include<SD.h>

/* SDカードに記録する準備．GPSロガーシールドを使ってください */
#define ARDUINO_USD_CS 10 //マイクロSDピン（GPSロガーシールド上）

// ファイル名の設定．
// "datalogXX.csv"という名前のファイルが生成されるが，"gpslog99.csv"が限界
#define LOG_FILE_PREFIX "datalog"    // ファイル名
#define MAX_LOG_FILES 100           // 作成できるログファイル数の上限
#define LOG_FILE_SUFFIX "csv"       // ログファイルの拡張子
char logFileName[13]; // ログファイル名を入れるchar型変数．半角13文字．
// 保存されるデータ
#define LOG_COLUMN_COUNT 1
char * log_col_names[LOG_COLUMN_COUNT] = {
 "thermo"
}; // これはファイルの１行目に入る


void setup() {
  Wire.begin(8);                // アドレス8でI2Cに参加(Slave)
  Wire.onReceive(receiveEvent); // イベントを登録
  Serial.begin(9600);          // シリアル通信の開始

  // SDカードが入っているかチェックする
  if (!SD.begin(ARDUINO_USD_CS))
  {
   Serial.println("Error initializing SD card.");
  }
  updateFileName(); // プログラムを始めるたびに新しいファイルを作成
  printHeader();    // ファイルの１行目を書き込む
}

void loop() {
  delay(100);     // ループ内でやることはない．イベント発生を待つ．
}

// Setup()内で定義したイベント関数
// マスターからデータが来たら実行される
void receiveEvent(int howMany) {
  while (1 < Wire.available()) {  // データが残り1バイトになるまでループ
    char c = Wire.read();         // 1バイトを'c'に読み込む
    Serial.print(c);             // シリアルで'c'を表示
  }
  int x = Wire.read();            // 最後の1バイトを受け取る
  Serial.println(x);             // シリアルで表示
  if (logData(x)) // GPSデータを保存
  {
    Serial.println("Data logged."); // Print a debug message
  }
  else // GPSログが保存できないなら
  {
    Serial.println("Failed to log new data.");
  }
}

byte logData(int x)
{
 File logFile = SD.open(logFileName, FILE_WRITE); // Open the log file

 if (logFile)
 {
   logFile.print(x, 1);
   logFile.println();
   logFile.close();

   return 1; // Return success
 }

 return 0; // If we failed to open the file, return fail
}

// printHeader() - prints our eight column names to the top of our log file
void printHeader()
{
 File logFile = SD.open(logFileName, FILE_WRITE); // Open the log file

 if (logFile) // If the log file opened, print our column names to the file
 {
   int i = 0;
   for (; i < LOG_COLUMN_COUNT; i++)
   {
     logFile.print(log_col_names[i]);
     if (i < LOG_COLUMN_COUNT - 1) // If it's anything but the last column
       logFile.print(','); // print a comma
     else // If it's the last column
       logFile.println(); // print a new line
   }
   logFile.close(); // close the file
 }
}

// updateFileName() - Looks through the log files already present on a card,
// and creates a new file with an incremented file index.
void updateFileName()
{
 int i = 0;
 for (; i < MAX_LOG_FILES; i++)
 {
   memset(logFileName, 0, strlen(logFileName)); // Clear logFileName string
   // Set logFileName to "gpslogXX.csv":
   sprintf(logFileName, "%s%d.%s", LOG_FILE_PREFIX, i, LOG_FILE_SUFFIX);
   if (!SD.exists(logFileName)) // If a file doesn't exist
   {
     break; // Break out of this loop. We found our index
   }
   else // Otherwise:
   {
     Serial.print(logFileName);
     Serial.println(" exists"); // Print a debug statement
   }
 }
 Serial.print("File name: ");
 Serial.println(logFileName); // Debug print the file name
}
