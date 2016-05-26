/*
  Commander.ino - default firmware for arbotiX Commander (V1.1)
  Copyright (c) 2009-2012 Michael E. Ferguson.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/


#define USER      10

#define FRAME_LEN 33         // 30hz
unsigned long ltime;         // last time we sent data
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 7;
const unsigned long timePerTurn = 120000;//120000;

#include <Wire.h>       //include the Wire/I2C Library
#include <WiiClassy.h>  //include the WiiClassy Libary

WiiClassy classy = WiiClassy(); //start an instance of the WiiClassy Library

//include the I2C Wire library - needed for communication with the I2C chip attached to the LCD manual 
#include <Wire.h> 
// include the RobotGeekLCD library
#include <RobotGeekLCD.h>

// create a robotgeekLCD object named 'lcd'
RobotGeekLCD lcd;

unsigned long timeEllapsed;
unsigned long startTime;

signed int rxOffset;
signed int lxOffset;
signed int ryOffset;
signed int lyOffset;


int i;
void setup(){
    Serial.begin(38400);
    ltime = millis();
    pinMode(USER,OUTPUT);    // user LED
    
    
    i = 0;
  delay(100);
  classy.init();  //start classy library
  delay(100);
  classy.update();  //read data from the classic controller

    lcd.init();
  // Print a message to the LCD.
  lcd.print("Geekbot");
      lcd.setCursor(0,1);
  lcd.print("      Challenge");

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  tone(BUZZER_PIN, 2000);
  delay(500);
  tone(BUZZER_PIN, 10000);
  delay(500);
  noTone(BUZZER_PIN);
  lcd.clear();

  classy.update();
  delay(1000);
//  classy.update();
//  delay(1000);
//  classy.update();
//  delay(1000);
//  classy.update();
//
//
//  lcd.setCursor(0, 0);
//   lcd.print( classy.leftStickY);
//   lcd.print("   ");
//  lcd.setCursor(4, 0);
//   lcd.print( classy.leftStickX);
//   lcd.print("   ");
//  lcd.setCursor(0, 1);
//   lcd.print(classy.rightStickX);
//   lcd.print("   ");
//  lcd.setCursor(4, 1);
//   lcd.print(classy.rightStickY);
//   lcd.print("   ");
//
//   
//
//   delay(3000);
//   lcd.clear();
//   delay(1000);
//  classy.update();
  
 rxOffset = 16 -(classy.rightStickX);
 ryOffset = 16 - (classy.rightStickY);
 lxOffset = 32 - (classy.leftStickX);
 lyOffset = 32 - (classy.leftStickY);
//
//  lcd.setCursor(0, 0);
//   lcd.print(lxOffset);
//   lcd.print("   ");
//  lcd.setCursor(4, 0);
//   lcd.print(lyOffset);
//   lcd.print("   ");
//  
//  lcd.setCursor(0, 1);
//   lcd.print(rxOffset);
//   lcd.print("   ");
//  lcd.setCursor(4, 1);
//   lcd.print(ryOffset);
//   lcd.print("   ");
//
//
//   delay(5000);
}

void loop(){
  classy.update();  //read data from the classic controller


    int right_V = (classy.rightStickY + ryOffset) * 8;
    int right_H = (classy.rightStickX + rxOffset) * 8;
    int left_V = (classy.leftStickY + lyOffset)  * 4;
    int left_H = (classy.leftStickX + lxOffset)  * 4;

    
    right_V = constrain(right_V, 0, 255);
    right_H = constrain(right_H, 0, 255);
    left_V = constrain(left_V, 0, 255);
    left_H = constrain(left_H, 0, 255);
    
    //buttons =    
    unsigned char buttons = 0;
    if(classy.rzPressed == true) buttons += 1;
    if(classy.lzPressed == true) buttons += 2;
    if(classy.rightShoulderPressed == true) buttons += 4;
    if(classy.leftShoulderPressed == true) buttons += 8;
    if(classy.upDPressed == true) buttons += 16;
    if(classy.downDPressed == true) buttons += 32;
    if(classy.leftDPressed == true) buttons += 64;
    if(classy.rightDPressed == true) buttons += 128;


    unsigned char ext = 0;
    if(classy.selectPressed == true) ext += 1;
    if(classy.homePressed == true) ext += 2;
    if(classy.startPressed == true) ext += 4;
    if(classy.xPressed == true) ext += 8;
    if(classy.yPressed == true) ext += 16;
    if(classy.aPressed == true) ext += 32;
    if(classy.bPressed == true) ext += 64;
    //if(classy.rightDPressed == true) buttons += 128;

    
 
//
//  lcd.setCursor(0, 1);
//   lcd.print(classy.rightStickY);
//   lcd.print("   ");
//  lcd.setCursor(4, 1);
//   lcd.print(classy.rightStickX);
//   lcd.print("   ");
//
//   lcd.print(classy.rzPressed);
//   lcd.print(" ");
//   lcd.print(classy.rightShoulderPressed);
//   
//  lcd.setCursor(0, 0);
//   lcd.print(classy.leftStickY);
//   lcd.print("   ");
//  lcd.setCursor(4, 0);
//   lcd.print(classy.leftStickX);
//   lcd.print("   ");
//
//lcd.print(classy.leftShoulderPressed);
//
//  lcd.setCursor(0, 0);
//   lcd.print(left_V);
//   lcd.print("   ");
//  lcd.setCursor(4, 0);
//   lcd.print(left_H);
//   lcd.print("   ");
//   
//  lcd.setCursor(0, 1);
//   lcd.print(right_V);
//   lcd.print("   ");
//  lcd.setCursor(4, 1);
//   lcd.print(right_H);
//   lcd.print("   ");
//
//   lcd.print(classy.rzPressed);
//   lcd.print(" ");
//   lcd.print(classy.rightShoulderPressed);
//   
//
//lcd.print(classy.leftShoulderPressed);
   

   
    Serial.write(0xff);
    Serial.write((unsigned char) right_V);
    Serial.write((unsigned char) right_H);
    Serial.write((unsigned char) left_V);
    Serial.write((unsigned char) left_H);
    Serial.write(buttons);              // buttons
    Serial.write(ext);     // extra
    Serial.write((unsigned char)(255 - (right_V+right_H+left_V+left_H+buttons+ext)%256));
    
    if(i > 10){
      digitalWrite(USER,HIGH-digitalRead(USER));
      i=0;
    }
    i = i + 1;
    delay(FRAME_LEN);
    
    timeEllapsed = millis();

    unsigned long timeRemaining = timePerTurn - (timeEllapsed - startTime);

    if((timeRemaining  < 30000) && (timeRemaining  > 29000))
    {
    
      tone(BUZZER_PIN, 10000);

    }
    else if(timeRemaining  < 29000 && (timeRemaining  > 28000))
    {
    
      noTone(BUZZER_PIN);

      
    }
    
    else if(timeRemaining  < 10000)
    {

      float tempTime = (float)timeRemaining / 1000;
      
      if(tempTime - floor(tempTime) > .9)
      {
         tone(BUZZER_PIN, timeRemaining );
      }
      else
      {
        noTone(BUZZER_PIN);
      }
      
    }

    lcd.setCursor(0,0);
    if(timeEllapsed - startTime< timePerTurn )
    {
        
      lcd.print("Time Remaining: ");
      lcd.setCursor(0,1);
      lcd.print((timeRemaining)/1000);
      lcd.print("    ");
    
    }
    else
    {
      noTone(BUZZER_PIN);
      lcd.print("NEXT PLAYER!    ");
      lcd.setCursor(0,1);
      lcd.print("Press B to start");
      
      tone(BUZZER_PIN, 10000);
      delay(500);
      tone(BUZZER_PIN, 5000);
      delay(500);
      tone(BUZZER_PIN, 2000);
      delay(500);
      noTone(BUZZER_PIN);

      while(classy.bPressed == false)
      {
        classy.update();  //read data from the classic controller

      }
      
      tone(BUZZER_PIN, 2000);
      delay(500);
      tone(BUZZER_PIN, 5000);
      delay(500);
      tone(BUZZER_PIN, 10000);
      delay(500);
      noTone(BUZZER_PIN);


      lcd.clear();
      startTime = millis();
    }
    
}

/* Revisions 
 *  V1.2 - Feb 11, 2012 - Updated for Arduino 1.0
 *  V1.1 - Feb 19, 2010 - Replaced Walk/Look with Right/Left 
 *         (since apparently, I used something called "southpaw")
 *  V1.0 - Feb 10, 2010 - Firmware Finalized
 */

