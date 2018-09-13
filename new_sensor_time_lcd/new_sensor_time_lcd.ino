#include <Time.h>
#include <TimeLib.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h>

//Set Uart Port num
#define pinNumber 13

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C LCD 객체 선언

//Set SoftwareSerial Port 10,11 (Rx,Tx)
SoftwareSerial mySerial(10,11); 


//Global sensor buffer
char sensorBuf[20]="";

void setup(){
  // initialize the LCD
  lcd.begin(); // lcd를 사용을 시작합니다.
  lcd.backlight(); // backlight를 On 시킵니다.
 
  // initialize the Serial,Software Serial
  Serial.begin(9600);
  mySerial.begin(9600);
  
   //initialize the Time
   //hh,mm,ss,dd,mm,yy
  setTime(19,23,0,13,9,18);

  Serial.println(" Co2   Temp   Humidity  Date");
}

void loop(){
  int i=0;

  //Sensor data buf
  char mPpm[4]="";
  char mTemp[4]="";
  char mHumi[4]="";

  //Read Sensor data
  digitalRead(pinNumber);
  while(mySerial.available() > 0){
    sensorBuf[i++] = mySerial.read();
  }

  //Output Spec of Sensor
  //0 1 2 3  4    5 6 7 8 9   10  11 12 13 14    15 16//
  //  Co2   |b|  Temp value  |b| Humidity val  |\ n|
  for (int i=0;i<4;i++){
    mPpm[i]=sensorBuf[i];
    mTemp[i]=sensorBuf[i+6];
    mHumi[i]=sensorBuf[i+10];
  }
 
  //Display Time on LCD, Serial
  digitalClockDisplay(0);
  digitalClockDisplay(1);
  
  //Display Sensor data on LCD, Serial
  Serial.print(sensorBuf);
  lcd.setCursor(0,1);
  for(int i=0;i<15;i++){
    lcd.print(sensorBuf[i]);
  }
 
  
  
  delay(1000);
}

/////Time Lib
void digitalClockDisplay(int flag){ //flag =0 이면 LCD 출력, else Serial 출력
    if(flag == 0){
      lcd.home();
      lcd.print(month());
      lcd.print("/");
      lcd.print(day());
      lcd.print(" ");
      printDigits(hour(),flag);
      lcd.print(":");
      printDigits(minute(),flag);
      lcd.print(":");
      printDigits(second(),flag);
    }else{
      Serial.print(year());
      Serial.print("/");
      Serial.print(month());
      Serial.print("/");
      Serial.print(day());
      Serial.print("  ");
      printDigits(hour(),flag);
      Serial.print(":");
      printDigits(minute(),flag);
      Serial.print(":");
      printDigits(second(),flag);
      Serial.print("  ");
    }
}

void printDigits(int digits,int flag){
   if(flag ==0){
    if(digits <10) lcd.print('0');
    lcd.print(digits);
   }else{
    if(digits <10) Serial.print('0');
    Serial.print(digits);
   }
 }




