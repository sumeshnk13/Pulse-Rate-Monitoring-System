
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
 
 
// Constants
const int PULSE_SENSOR_PIN = 0;  // Analog PIN where the PulseSensor is connected
const int LED_PIN = 13;          // On-board LED PIN
const int THRESHOLD = 550;       // Threshold for detecting a heartbeat
const int rs=12,en=11,d4=5,d5=4,d6=3,d7=2;

const int buzzerpin = A3;

// Create PulseSensorPlayground object
PulseSensorPlayground pulseSensor;
 
void setup()
{
  // Initialize Serial Monitor
  Serial.begin(9600);
  lcd.begin(16,2);
  // Configure PulseSensor
  pulseSensor.analogInput(PULSE_SENSOR_PIN);
  pulseSensor.blinkOnPulse(LED_PIN);
  pulseSensor.setThreshold(THRESHOLD);
  pinMode(A3,OUTPUT);
 
  // Check if PulseSensor is initialized
  if (pulseSensor.begin())
  {
    Serial.println("PulseSensor object created successfully!");
  }
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
    Serial.print("Pulse rate: ");
    Serial.println(currentBPM);
 
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Pulse rate: ");
    lcd.print(currentBPM); 
  }
  if(currentBPM >= 10 && currentBPM <= 60)
  {
  tone (buzzerpin,1000);
  delay(1000);
  noTone(buzzerpin);
  delay(1000);
  Serial.println("Pulse rate is low");
  }
  if(currentBPM >= 60 && currentBPM <= 100)
  {
  Serial.println("Pulse rate is normal"); 
  }
  if(currentBPM>=100)
  {
  tone (buzzerpin,1000);
  delay(1000);
  noTone(buzzerpin);
  delay(1000);
  Serial.println("Pulse rate is high");
  } 
  delay(1000);
  }
 
