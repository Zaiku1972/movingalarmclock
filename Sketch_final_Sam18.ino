#include <LiquidCrystal.h>
#define trigPin 12
#define echoPin A1
int motor_left[] = {A2, A3};
int motor_right[] = {A4, A5};

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int starttime;
int activetime;
int prevoustime = 0;

int hours = 0;
int mins = 0;

int ahours = 0;
int amins = 0;



void setup() {
  Serial.begin(9600);
  //Clock  
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(13, INPUT);
  digitalWrite(13, HIGH);
  pinMode(11, INPUT);
  digitalWrite(11, HIGH);
  pinMode(10, INPUT);
  digitalWrite(10, HIGH);
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  pinMode(9, OUTPUT);
  
  starttime = millis()/1000;

  //Motor Config
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  int i;        //setting up the motors
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
}

void loop() {
while(digitalRead(8) == LOW)
  {
    lcd.setCursor(6,1);
    lcd.print("Alarm");
    lcd.setCursor(6,0);

       if(digitalRead(11) == LOW)
       {
          amins++;
       } 
       else if (digitalRead(10) == LOW)
       {
          ahours++;
       }
     
        lcd.setCursor(6,0);
  
      if(ahours < 10)
      {
        lcd.print("0");
        lcd.print(ahours);
      }
      else
      {
        lcd.print(ahours);
      }
    
        lcd.print(":");
    
      if (amins < 10)
      {
        lcd.print("0");
        lcd.print(amins);
      }
      else
      {
        lcd.print(amins);
      }
 
      if(amins > 59)
      {
        ahours++;
        amins = 0;
      }
       
      if(ahours > 23)
      {
        ahours = 0; 
      }
     delay(500);
     lcd.clear();
  }
  
  if(digitalRead(13) == LOW)
  {
    
    lcd.setCursor(5,1);
    lcd.print("Set Time");
    lcd.setCursor(6,0);
     if(digitalRead(11) == LOW)
    {
     mins++;
    } 
    else if (digitalRead(10) == LOW)
    {
      hours++;
    }
    

  }
  
      activetime = (millis() / 1000) - starttime;
      if(prevoustime < (activetime - 59))
      {
       mins++;
       prevoustime = activetime;
      } 
      
      if(mins > 59)
      {
        hours++;
        mins = 0;
      } 
     
      if(hours > 23)
      {
        hours = 0; 
      }
  
  
  lcd.setCursor(6,0);
  
  if(hours < 10)
  {
    lcd.print("0");
    lcd.print(hours);
  }
  else
  {
    lcd.print(hours);
  }
    
    lcd.print(":");

  if (mins < 10)
  {
    lcd.print("0");
    lcd.print(mins);
  }
  else
  {
      lcd.print(mins);
  }



if(ahours == hours && amins == mins && amins != 0)
{
  mo_drive();
}

else
{
    delay(300);
}
  lcd.clear();
 

  Serial.println(mins);
  Serial.println(hours);
  Serial.println("");
  Serial.println(amins);
  Serial.println(ahours);
  Serial.println("");
  Serial.println(activetime);
  Serial.println(prevoustime);
  Serial.println(starttime);
  Serial.println("");

}

void mo_drive(){

  drive_forward();
  tone(9, 1000,200);
  delay(200);
  noTone(9);
  delay(200);
  
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Distance Calculation http://www.instructables.com/id/Using-a-SR04/
  distance = (duration/2) / 29.1;
  
  if (distance < 15) 
  {  
    motor_stop();
    turn_right();
    delay(1000);
    motor_stop();
   }
  else {
    motor_stop();
  }
  delay(100);
  
}


void motor_stop(){
digitalWrite(motor_left[0], LOW); 
digitalWrite(motor_left[1], LOW); 

digitalWrite(motor_right[0], LOW); 
digitalWrite(motor_right[1], LOW);
delay(25);
}


void drive_forward(){
digitalWrite(motor_left[0], HIGH); 
digitalWrite(motor_left[1], LOW); 

digitalWrite(motor_right[0], HIGH); 
digitalWrite(motor_right[1], LOW); 
}

void turn_right(){
digitalWrite(motor_left[0], HIGH); 
digitalWrite(motor_left[1], LOW); 

digitalWrite(motor_right[0], LOW); 
digitalWrite(motor_right[1], HIGH); 
}
