 
      // Temperature Controlled Fan //

#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int tempPin = A0;   // the output pin of LM35
int fan = 11;       // the fan is connectoed to tha erduino through this pin
int buzzer = 13;    // buzzer pin
int temp;
int tempMin = 35;   // the temperature to start the fan
int tempMax = 50;   // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;
 
void setup() {
  pinMode(fan, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(tempPin, INPUT);
  lcd.begin(16,2);  
  lcd.setCursor(0,0);
  lcd.print("  WELCOME  ");
  lcd.setCursor(0,1);
  lcd.print("  AmziSys ");
  delay(1500);
  lcd.clear();
}
 
void loop() {  
   temp = readTemp();     // Read the temperature
   
   if((temp >= tempMin) && (temp <= tempMax)) {  // if temperature is higher than minimum temp (35 degree)
       fanSpeed = map(temp, tempMin, tempMax, 32, 255); // the actual speed of fan
       fanLCD = map(temp, tempMin, tempMax, 0, 100);  // speed of fan to display on LCD
       analogWrite(fan, fanSpeed);  // spin the fan at the fanSpeed speed
   } 

   if(temp < tempMin) {   // if temp is lower than minimum temp
    fanSpeed = 0;      // fan is not spinning
    fanLCD = 0; 
    digitalWrite(fan, LOW);       
   } 
   
   if(temp > tempMax) {        // if temp is higher than tempMax (50 degree)
    digitalWrite(fan, HIGH); 
    digitalWrite(buzzer, HIGH);  // turn on buzzer
   } else {                    // else turn of buzzer
     digitalWrite(buzzer, LOW); 
   }
   
   lcd.setCursor(0,0);
   lcd.print("Temperature:");
   lcd.print(temp); // display the temperature
   lcd.write(223);
   lcd.print("C  ");
   
   lcd.setCursor(0,1); // move cursor to next line
   lcd.print("Fan Speed:");
   lcd.print(fanLCD); // display the fan speed
   lcd.print("%   ");
   delay(200);
}
 
int readTemp() {  // get the temperature and convert it to celsius
  temp = analogRead(tempPin);
  return temp * 0.48828125;
}
