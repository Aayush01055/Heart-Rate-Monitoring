// Include necessary libraries
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
 
 
// Constants
const int PULSE_SENSOR_PIN = 0;  // Analog PIN where the PulseSensor is connected
const int LED_PIN = 13;          // On-board LED PIN
const int THRESHOLD = 550; 
      // Threshold for detecting a heartbeat
int led1 = 4;
int led2=3;
int led3=2; 
const int one = 7;
// Create PulseSensorPlayground object
PulseSensorPlayground pulseSensor;
 
void setup()
{
  // Initialize Serial Monitor
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

 
  // Configure PulseSensor
  pulseSensor.analogInput(PULSE_SENSOR_PIN);
  pulseSensor.blinkOnPulse(LED_PIN);
  pulseSensor.setThreshold(THRESHOLD);
 
  // Check if PulseSensor is initialized
  if (pulseSensor.begin())
  {
    Serial.println("PulseSensor object created successfully!");
  }
   pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT); 
  pinMode (one, OUTPUT) ;

}
 
void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Heart Rate");
  
  // Get the current Beats Per Minute (BPM)
  int currentBPM = pulseSensor.getBeatsPerMinute();
 
  // Check if a heartbeat is detected
  if (pulseSensor.sawStartOfBeat())
  {
    Serial.println("♥ A HeartBeat Happened!");
    Serial.print("BPM: ");
    Serial.println(currentBPM);
  
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("BPM: ");
    lcd.print(currentBPM);

    Serial.print(currentBPM);
    Serial.print(',');
    
    if(currentBPM<=50)
      currentBPM=currentBPM+50;
    else if(currentBPM>=120)
      currentBPM=currentBPM-70;

    if(currentBPM>=60 && currentBPM<=99)
    {
      digitalWrite(led3, HIGH);
      delay(1000); // Wait for 1000 millisecond(s
      digitalWrite(led3, LOW);
      delay(1000); // Wait for 1000 millisecond(s)
      Serial.println("Light");
      
    }
    else if(currentBPM>=100 && currentBPM<=139)
    {
      digitalWrite(led2, HIGH);
      delay(1000); // Wait for 1000 millisecond(s)
      digitalWrite(led2, LOW);
      delay(1000); // Wait for 1000 millisecond(s)
      Serial.println("Moderate");
    }
    else if(currentBPM>=140)
    {
      digitalWrite(led1, HIGH);
      digitalWrite (one, HIGH);
      delay(1000); // Wait for 1000 millisecond(s)
      digitalWrite(led1, LOW);
      digitalWrite (one, LOW);
      delay(1000);
      Serial.println("High");
    }
    else
    {
      digitalWrite(led1, HIGH);
      delay(300); // Wait for 1000 millisecond(s
      digitalWrite(led1, LOW);
      delay(300); // Wait for 1000 millisecond(s
      digitalWrite(led2, HIGH);
      delay(300); // Wait for 1000 millisecond(s
      digitalWrite(led2, LOW);
      delay(300); // Wait for 1000 millisecond(s
      digitalWrite(led3, HIGH);
      delay(300); // Wait for 1000 millisecond(s
      digitalWrite(led3, LOW);
      delay(300);
      digitalWrite (one, HIGH);
      delay(300); // Wait for 1000 millisecond(s)
      digitalWrite (one, LOW);
      delay(300); // Wait for 1000 millisecond(s)
      
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite (one, HIGH);
      delay(1000); // Wait for 1000 millisecond(s
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite (one, LOW);
      delay(1000); // Wait for 1000 millisecond(s)
      Serial.println("Not Normal");
    }
    delay(50);
  }
 
  // Add a small delay to reduce CPU usage
  delay(20);
}