/*Plant watering system with new blynk update
   Home Page
   
*/
#define BLYNK_TEMPLATE_ID "TMPL3ho8CSsug"
#define BLYNK_TEMPLATE_NAME "Plant Watering System"
#define BLYNK_AUTH_TOKEN "uBIF7hQRgfXQ22zdj3400o4Mrcb7a3qk"

//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "uBIF7hQRgfXQ22zdj3400o4Mrcb7a3qk";  //Enter your Auth token
char ssid[] = "Redmi";                             //Enter your WIFI name
char pass[] = "72580306";                          //Enter your WIFI password

BlynkTimer timer;
bool Relay = 0;

//Define component pins
#define sensor A0

void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, 0); 

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  //Call the function
  timer.setInterval(100L, soilMoistureSensor);
}

//Get the button value
BLYNK_WRITE(V1) {
  int Relay = param.asInt();
  
  if (Relay == 0) {                //Automatic mode
    int moisture = analogRead(sensor);
    moisture = map(moisture, 0, 1024, 0, 100);
    moisture = (moisture - 100) * -1;
    Serial.println(moisture);
    if (moisture < 20) {    //Threshold value
      digitalWrite(D0, 1);  // turn on the motor     
    } else {
      digitalWrite(D0, 0);  // turn off the motor
    }

  } else if (Relay == 1){         //Manual mode
    digitalWrite(D0, 0);          //motor manually turned on by switch
    Serial.println(Relay);
  } else{
    digitalWrite(D0, 1);
    Serial.print(Relay);          //motor manually turned off by switch
  }
}

//Get the soil moisture values for widget
void soilMoistureSensor() {
  int moisture = analogRead(sensor);
  moisture = map(moisture, 0, 1024, 0, 100);
  moisture = (moisture - 100) * -1;

  Blynk.virtualWrite(V0, moisture);
}


void loop() {
  Blynk.run();
  Blynk.syncVirtual(V1);  //Run the Blynk library
  timer.run();  //Run the Blynk timer
}