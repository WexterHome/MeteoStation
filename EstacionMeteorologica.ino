#include <LowPower.h>
#include <LiquidCrystal.h>   
#include <DHT.h>      

#define DHTTYPE DHT22  // DHT 22

const int DHTPin = 6;

DHT dht(DHTPin, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup(){
   Serial.begin(9600);
   lcd.begin(16, 2);   // Inicia un LCD 16x02 (columnas,fila)
   dht.begin();        // Inicia el sensor de temp y humedad
}
 
void loop(){
    
   float h = dht.readHumidity();
   float t = dht.readTemperature();

   if (isnan(h) || isnan(t)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DHT Error");
      delay(10000);
      return;
   }

   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Temp: ");
   lcd.print(t);

   lcd.setCursor(0, 1);
   lcd.print("Humedad: ");
   lcd.print(h);
   lcd.print("%");

   //Modo Sleep durante 4 minutos
   for(int i=0; i<30; i++){
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
   }
}
