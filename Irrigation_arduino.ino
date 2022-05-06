#include <RH_ASK.h>
#include <SPI.h> 
#include <dht.h>

dht DHT;
RH_ASK rf_driver;

int soilsensor = A0;
#define DHT11_PIN A1
int water_pump = 5;
int med_pump = 6;
 
int soilValue = 0;
int moisture_percentage;
char inst;

void setup(){
  rf_driver.init();
  Serial.begin(9600);
  pinMode(soilsensor, INPUT);
  pinMode(water_pump, OUTPUT); // Relay
  pinMode(med_pump, OUTPUT);  // Relay

  digitalWrite(med_pump, HIGH);
  digitalWrite(water_pump, HIGH);

}

void loop(){

      int chk = DHT.read11(DHT11_PIN);
      int temp=(DHT.temperature);
      int humid=(DHT.humidity);
      //delay(500);
	    //Serial.print("Temperature: ");
      //Serial.println(temp);
	    //Serial.print("Humidity: ");
      //Serial.println(humid);

      soilValue = analogRead(soilsensor);
      
      moisture_percentage = ( 100 - ( (soilValue/1023.00) * 100 ) );
      //Serial.print("Moisture Percentage = ");
      //Serial.print(moisture_percentage);
      //Serial.println(" %");

      String combine=String(moisture_percentage)+"-"+String(temp)+"-"+humid;
      const char *msg = combine.c_str();
      rf_driver.send((uint8_t *)msg, strlen(msg));
      rf_driver.waitPacketSent();
      delay(1000);
  
      
      if(moisture_percentage < 35){
      Serial.println("Give water to plant");

      digitalWrite(water_pump, LOW);
     
     }
     else if(moisture_percentage > 38){
      digitalWrite(water_pump, HIGH);
      //Serial.println("Soil has enough water for plant");
      
     }
     Serial.println(String(moisture_percentage)+"-"+String(temp)+"-"+humid);
     
    delay(500);
  if(Serial.available()>0)
   {
    inst=Serial.read();
  
   }
   
  if(inst=="m")
  {
      digitalWrite(med_pump, LOW);
      
  }
  if(inst=="s")
  {
      digitalWrite(med_pump, HIGH);
  }

 
}
