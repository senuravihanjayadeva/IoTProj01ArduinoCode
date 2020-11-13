#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
 
// Set these to run example.
#define FIREBASE_HOST "iotled-d5189.firebaseio.com"
#define FIREBASE_AUTH "pO2wDOixtiHZDTcFY7kqtPp4ImoJoqyq7Ub0YB4e"
#define WIFI_SSID "Nokia 5"
#define WIFI_PASSWORD "JAYADEVA123"
 
const int LED_1_SLOT = D2;
const int LED_2_SLOT = D4;
const int buzzer = D0; //buzzer to arduino pin 9

void setup()
{

 
   
  // Debug console
  Serial.begin(9600);
   pinMode(LED_1_SLOT, OUTPUT);
   pinMode(LED_2_SLOT, OUTPUT);
   pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  if(Firebase.failed())
  {
    Serial.print(Firebase.error());
  }
  else{
  
    Serial.print("Firebase Connected");
    Firebase.setString("VariableResistor/Value","fahad");
  }



}
 
void loop()
{
 
    String path = "/";
    FirebaseObject object = Firebase.get(path);

    String LED_1 = object.getString("LED_1");
    Serial.println("LED_1 : " + LED_1); 

    String LED_2 = object.getString("LED_2");
    Serial.println("LED_2 : " + LED_2); 

     String BUZZER = object.getString("BUZZER");
    Serial.println("BUZZER : " + BUZZER); 

    
    if(BUZZER == "ON"){
      
       tone(buzzer, 1000); // Send 1KHz sound signal..
      
    }
    else if (BUZZER == "OFF"){
       
      noTone(buzzer);     // Stop sound...

    }
    

    if(LED_1 == "ON"){
      
      digitalWrite(LED_1_SLOT, HIGH);
      
    }
    else if (LED_1 == "OFF"){
      digitalWrite(LED_1_SLOT, LOW);
    }

     if(LED_2 == "ON"){
      
      digitalWrite(LED_2_SLOT, HIGH);
      
    }
    else if (LED_2 == "OFF"){
      digitalWrite(LED_2_SLOT, LOW);
    }
    

   
   
}
