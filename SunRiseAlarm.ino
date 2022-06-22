#include <DS3231.h> //Include the clock library
 
// Changable Vars
int fadeTime = 1; // How long the light will fade to max
int setHour = 0; // Set hours to wake (military time)c
int setMin = 0; // Set minute to wake
int uled = 9; // Set pinout with with PWM

// Set up Vars
DS3231 rtc(SDA, SCL);
Time t;
void start();
 
void setup()
{
  pinMode(uled, OUTPUT);
  Serial.begin(9600); // Match to serial monitor
  rtc.begin();
}

void loop()
{
  t = rtc.getTime(); // Make a time class called 't'
  
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  Serial.print("Alper");
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
for(int i = 0; i<24; i++){
  setHour=i;
  for(int j = 0; j<60; j++){
  setMin=j;
  if (t.hour == setHour && t.min == setMin) // Check if it's time to wake up!
  {
    start();
    delay(1000);
  }
  
  // Wait one second before repeating
}
}
}

void start()
{
  // Fix for SB LED  //Brightening slowly
  analogWrite(uled, 1);
  delay((fadeTime * 60000)/50); //if fadeTime is 1,delay is 1.2second
  analogWrite(uled, 2);
  delay((fadeTime * 60000)/50);
  analogWrite(uled, 3);
  delay((fadeTime * 60000)/50);
  analogWrite(uled, 4);
  delay((fadeTime * 60000)/50);
  analogWrite(uled, 4);
  delay((fadeTime * 60000)/50);
  analogWrite(uled, 5);
  delay((fadeTime * 60000)/50);


  // Fade script
  for (int i = 6 ; i <= 255; i++)
  {
    analogWrite(uled, i);
    delay(((fadeTime * 60000)/306));
    Serial.print(" mil sec ");
    Serial.print(((fadeTime * 60000)/306));
    Serial.print(" PWM " );
    Serial.print(i);


  }
  
  delay((fadeTime*60000)/5); // Stay Bright
  analogWrite(uled, 0); // Turn off
}
