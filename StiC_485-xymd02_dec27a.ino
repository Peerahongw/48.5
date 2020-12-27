

/*
 * StiC_485-xymd02_dec27a.ino
 * sketch_dec04b.2020   test recieve from RS485 (serial2) M5STICK-C
 * 
 */

#include <M5StickC.h>
#include <ModbusMaster.h>

String inputStream = "";          // a String to hold incoming data
bool streamComplete = false;    // whether the string is complete


ModbusMaster node;

void setup() {
  Serial.begin(115200);
  Serial.println("serial print for debug ");

  Serial2.begin(9600, SERIAL_8N1, 26, 0);
  node.begin(1, Serial2);

  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  delay(100);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Modbus Test reciever");
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println(" data from XY-MD02");

  delay(2000);
  
//  for(int i=0;i<10;i++){
//        Serial2.print(runStateQuery[i]);
//  }
  delay(500);

}

void loop() {

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Modbus Test reciever");
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println(" data from XY-MD02");

    // for debug ruler
    for (int n = 0; n <= 40; n++) {
      Serial.print(n < 16 ? "0" : "");
      Serial.print(n, HEX);
      Serial.print(" ");
    }
    Serial.println();

  static uint32_t i;
  uint8_t j, result;
  uint16_t data[6];
  float tempe,humid;
  
  
  i++;
  
  // slave: read (2) 16-bit Input registers starting at register 1 to 2 buffer
  result = node.readInputRegisters(1, 2);
  
  // do something with data if read is successful
  if (result == node.ku8MBSuccess){
    for (j = 0; j < 2; j++)
    {
      data[j] = node.getResponseBuffer(j);
    }
  }

  tempe = data[0];
  tempe = tempe /10;
  humid = data[1];
  humid = humid /10;
  
  Serial.print("Temperature = ");
  Serial.print(tempe);
  Serial.print(" C ");
  Serial.print(",%RH = ");
  Serial.print(humid);
  Serial.print("");
  Serial.println();

  M5.Lcd.setCursor(0, 50);
  M5.Lcd.println(tempe);
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.println(humid);


  delay(2000);
}
