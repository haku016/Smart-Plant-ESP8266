#include <OneWire.h>
#include <DallasTemperature.h>
#include <BlynkSimpleEsp8266_SSL.h>

#define BLYNK_TEMPLATE_ID "TMPLzg7coE9k"
#define BLYNK_DEVICE_NAME "Smart Plant"
#define BLYNK_AUTH_TOKEN " " //Blynk token

#define BLYNK_PRINT Serial

char auth[] = " "; //Blynk token
char ssid[] = " "; //wifi name
char password[] = " "; // password

int value;

int ctrlPin = D1;

int moisture_pin = A0;
int moisture_value ;

const int oneWirebus = D2;  
  
OneWire oneWire(oneWireBus);
DallasTemperature sensor(&oneWire);

void setup() {
  Serial.begin(115200);
  sensor.begin();
  Blynk.begin(auth, ssid, password, "blynk.cloud", 443);
  pinMode(ctrlPin, OUTPUT);
}

BLYNK_WRITE(V0){
  value = param.asInt();
  digitalWrite(ctrlPin,value);
} //connect with V0 stream on Blynk

void loop() {
  Blynk.run();
  
  //temperature
  sensors.requestTemperatures(); 
  float temperature = sensors.getTempCByIndex(0);
  
  //moisture
  moisture_value = analogRead(moisture_pin);
  moisture_value = map(moisture_value,1024,552,0,100); 

  Blynk.virtualWrite(V2,moisture_value); //write moisture variable on V2 stream
  Blynk.virtualWrite(V2,temperature); //write temperature variable on V3 stream
  
  //execute automatic function
  if(value){
     //threshold check
     if((moisture_value < 40) || (moisture_value < 70 && temperature > 35))
      { 
        digitalWrite(ctrlPin1, LOW);
      }else{
        digitalWrite(ctrlPin1, HIGH);
        }
      }
    delay(100);
}

   
  
