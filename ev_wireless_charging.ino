#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);  
void setup() 
{ 
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  lcd.init();
  lcd.backlight(); // backlight ON 
    lcd.setCursor(0,0); 
  lcd.print("EV Charging");
      lcd.setCursor(0, 1);
    lcd.print("System");
    delay(1000);
  Serial.println();
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content.substring(1) == "B3 8B 7B C9")  //  ( "4D 4A 05 32" ) change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
        lcd.setCursor(0,0); 
  lcd.print("EV Charging");
    lcd.setCursor(0, 1);
    lcd.print("Authorized");
    delay(3000);
    lcd.clear();
   lcd.setCursor(0,0); 
  lcd.print("EV Charging");
    lcd.setCursor(0, 1);
    lcd.print("Started");
    delay(1000);
    lcd.clear();
   lcd.setCursor(0,0); 
  lcd.print("EV Charging");
    digitalWrite(8, LOW);
    delay(10000); // Change the Delay Time
    digitalWrite(8, HIGH);
    lcd.clear();
   lcd.setCursor(0,0); 
  lcd.print("EV Charging");
    lcd.setCursor(0, 1);
    lcd.print("Ended");
    delay(1000);
lcd.clear();
  }
 
 else   {
    Serial.println(" Access denied");
        lcd.setCursor(0,0); 
  lcd.print("EV Charging");
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    delay(3000);
    lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("EV Charging");
  }
    lcd.init();
  lcd.backlight(); // backlight ON 
    lcd.setCursor(0,0); 
  lcd.print("EV Charging");
      lcd.setCursor(0, 1);
    lcd.print("System");
    delay(1000);
}
