//Gsm  sim 900a module
//blue with 7 of arduino
//orange with 8 of arduino
//orange-red with 5V of arduino
//black-green with gnd of arduino


#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);



void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}


void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+9XXXXXXXXXXX\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("fouzan");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
 






###########################RECIEVER ###########################


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8);

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x3F.

const byte address[6] = "00001";

void setup() {
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  lcd.begin(16,2);   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
  lcd.setCursor(0,0); //First line
  lcd.print("Industry Security");
  lcd.setCursor(0,1); //Second line
  lcd.print("Zaka Sarmad");
  lcd.clear(); //First line
}

void loop() {
  if (mySerial.available()>0){
        Serial.write(mySerial.read());
    }

    String message1;
    
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    String text1=text;
    
    if(text1=="4")
    {
      Serial.println("Every thing under control");
        lcd.setCursor(0,0); //First line
        lcd.print("Controlled work");
        lcd.setCursor(0,1); //Second line
        lcd.print("");
        delay(1000);
        lcd.clear();
        message1="Good";
      }

      else if(text1=="3")
      {
        Serial.println("HIGH vibration");
        lcd.setCursor(0,0); //First line
        lcd.print("High vibration");
        lcd.setCursor(0,1); //Second line
        lcd.print("");
         lcd.clear();
         message1="High Vibration";
        }
        else if(text1=="2")
        {
          Serial.println("Concentrated gas and vibration");
          lcd.setCursor(0,0); //First line
          lcd.print("BOHT HIGH");
          lcd.setCursor(0,1); //Second line
          lcd.print("");
          delay(1000);
          message1="Both High";
          
         lcd.clear();
          }

          else{
            Serial.println("Concentrated gas");
            lcd.setCursor(0,0); //First line
            lcd.print("Conc Gas");
            lcd.setCursor(0,1); //Second line
            lcd.print("No vibration");
            delay(1000);
            message1="Conc Gas";
            
            }
            if(message1=="Good")
            {
              Serial.println("No need to send sms");
             }
             else{
            mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
            delay(1000);  // Delay of 1000 milli seconds or 1 second
            mySerial.println("AT+CMGS=\"+9XXXXXXXXX\"\r"); // Replace x with mobile number
            delay(1000);
            mySerial.println(message1);// The SMS text you want to send
            delay(100);
            mySerial.println((char)26);// ASCII code of CTRL+Z
            delay(1000);
             }

  }


}