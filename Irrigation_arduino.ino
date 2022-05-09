#include <RH_ASK.h>
#include <SPI.h> 
#include <dht.h>

dht DHT;
RH_ASK rf_driver;

int soilsensor = A0;
#define DHT11_PIN A1
int water_pump = 5;
 
int soilValue = 0;
int moisture_percentage;
char inst;

void setup(){
  rf_driver.init();
  Serial.begin(9600);
  pinMode(soilsensor, INPUT);
  pinMode(water_pump, OUTPUT); // Relay
 
  digitalWrite(water_pump, HIGH);

}

void loop(){

      int chk = DHT.read11(DHT11_PIN);
      int temp=(DHT.temperature);
      int humid=(DHT.humidity);
      

      soilValue = analogRead(soilsensor);
      
      moisture_percentage = ( 100 - ( (soilValue/1023.00) * 100 ) );
      
      String combine=String(moisture_percentage)+"-"+String(temp)+"-"+humid;
      rf_driver.send((uint8_t *)msg, strlen(msg));
      rf_driver.waitPacketSent();
      delay(1000);
  
      
      if(moisture_percentage < 35){
      Serial.println("Give water to plant");

      digitalWrite(water_pump, LOW);
     
     }
     else if(moisture_percentage > 38){
      digitalWrite(water_pump, HIGH);
      
      
     }
     Serial.println(String(moisture_percentage)+"-"+String(temp)+"-"+humid);
     
    delay(500);
  if(Serial.available()>0)
   {
    inst=Serial.read();
  
   }
   
  

 
}
