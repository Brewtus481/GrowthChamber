#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

//SoftwareSerial lcd(4, 2);
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int tempSetPoint = 0;
int stirSetPoint = 0;
int actualTemperature = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT); //Stir Plate
  pinMode(10, OUTPUT); //Heat?
  pinMode(11, OUTPUT); //Cool?
  //Serial.begin(9600);
  lcd.begin(16,2);
  //clearDisplay();
  mlx.begin();
  delay(200);
}

void loop() {
   delay(200);
  getInputs();
  adjustStirSpeed();
  adjustTemperature();

  //Serial.print("Temp Setpoint: ");  Serial.print(tempSetPoint); Serial.print("       Actual Temp: "); Serial.println(actualTemperature);

  lcd.setCursor(0,0);
  lcd.print("Set: "); lcd.print(tempSetPoint);
  if (tempSetPoint < 100)
  {
    lcd.print("  ");
  }
  else
  {
    lcd.print(" ");
  }
  lcd.print("T: "); lcd.print((int)mlx.readObjectTempF());

  lcd.setCursor(0,1);
  lcd.print("Stir Speed: ");

  if (stirSetPoint == 100)
  {
    lcd.print("MAX");
  }
  else
  {

    lcd.print(stirSetPoint);
    if (stirSetPoint < 10)
    {
      lcd.print("%  ");
    }
    else if (stirSetPoint < 100)
    {
      lcd.print("% ");
    }
    else if (stirSetPoint == 100)
    {
      lcd.print("MAX");
    }
    else
    {
      lcd.print("???");
    }
  }
}

void adjustTemperature()
{
  if(tempSetPoint < actualTemperature) //Cooling
  {
    analogWrite(11,0);
    analogWrite(10,255);
  }
  if(tempSetPoint > actualTemperature)  //Heating
  {
    analogWrite(11,255);
    analogWrite(10,0);
  }
}

void adjustStirSpeed()
{
  analogWrite(3, map(stirSetPoint, 0, 100, 0, 255));
}

void getInputs()
{
  tempSetPoint = map(analogRead(A1), 0, 1023, 32, 170);
  //tempSetPoint = 70;
  stirSetPoint = map(analogRead(A0), 0, 1023, 0, 100);
  actualTemperature = (int)mlx.readObjectTempF();
}

void clearDisplay() {
  lcd.write(0xFE);
  lcd.write(0x01);
  //Serial.write(0xFE);
  //Serial.write(0x01);
}

void setLCDCursor()
{
  //lcd.write(0xFE);  // send the special command
  //lcd.write(0x80);  // send the set cursor command
  //Serial.write(0xFE);  // send the special command
  //Serial.write(0x80);  // send the set cursor command
}

void setLCDCursorLine2()
{
  //lcd.write(0xFE);
  //lcd.write(0xC0);
  //Serial.write(0xFE);
  //Serial.write(0xC0);
}
