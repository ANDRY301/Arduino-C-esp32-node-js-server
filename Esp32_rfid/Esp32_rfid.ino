
#include <WiFi.h>
#include <HTTPClient.h>
//----
#include <SPI.h>
#include <MFRC522.h>
const char* ssid = "..........";                  // Your wifi Name       
const char* password = "................." ;

//----------

const int pinRST         = 22;  // pin RST 
const int pinSDA         = 21; // pin SDA 

const int pin2             = 12;
const int pin4             = 13;
const int pin26            = 26; // relai
const int pin15            = 14;// pin SDA 
String inStringHex         = "";
String    matricule        = "and01";
String    porte           = "004";
MFRC522 mfrc522(pinSDA,pinRST);
 
void setup() {
  //---------
  SPI.begin();
  Serial.begin(115200);
  mfrc522.PCD_Init();
  pinMode      (pin2,OUTPUT );
  pinMode      (pin4,OUTPUT );
    pinMode    (pin26,OUTPUT );
  pinMode      (pin15,OUTPUT );
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(pin2,HIGH);
    delay(500);
    digitalWrite(pin2,LOW);
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
    digitalWrite(pin15,HIGH);
}

void miposteservernode(){
  HTTPClient http;
  http.begin("https://............./iot/esp32postset");
  http.addHeader("Content-Type", "application/json");
// MIKASIKA RFID

 if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
  {
    //Serial.print("Card UID:");
    for (byte i = 0; i < 4; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    inStringHex += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();
    Serial.println(F("Hex normal"));
    Serial.print(inStringHex);
    Serial.println();
    Serial.println();
    digitalWrite(pin2,HIGH);
     digitalWrite(pin4,HIGH);
     delay(350);
   digitalWrite(pin4,LOW);
    
     // refa handefa ny valiny rfid 
   String request   = "[" "{\"numero_status\":\""+(String)(inStringHex)+"\"}" "," "{\"matricule\":\""+(String)(matricule)+"\"}""," "{\"porte\":\""+(String)(porte)+"\"}" "]" ;

     int http_response_code    = http.POST(request);

     Serial.println("envoi vraie");
       digitalWrite(pin2,LOW);
 
 
     inStringHex = "";
      if (http_response_code < 0){
    Serial.println("Error in sending sensor value");
   
  }
  else{
    String response = http.getString();
    Serial.print("Response (/sensordata): ");
    Serial.println(response);
        
      if(response == "tsy mitovy"){
      
         digitalWrite(pin4,HIGH); 
          digitalWrite(pin2,HIGH);
         
          delay(250);
          digitalWrite(pin2,LOW);
          delay(250);
          digitalWrite(pin2,HIGH);
          delay(500);
          digitalWrite(pin2,LOW);
           digitalWrite(pin4,LOW);
        
        }else{
          digitalWrite(pin26,HIGH);
          digitalWrite(pin4,HIGH); 
          digitalWrite(pin15,LOW);
          delay(250);
          digitalWrite(pin15,HIGH); 
          digitalWrite(pin4,LOW);
          delay(250);
          digitalWrite(pin15,LOW);
          delay(250);
          digitalWrite(pin15,HIGH);   
            delay(2500);   
           digitalWrite(pin26,LOW);
          }
    
  }
  }
  
// MIKASIKA RFID
 
  http.end();
}

void loop() {
 if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 miposteservernode();
  }
  delay(1000);
}
