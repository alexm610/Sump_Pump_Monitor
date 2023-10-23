#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <lcd.h>
#include <time.h>
#include <unistd.h>

#define LCD_RS 25
#define LCD_E 24
#define LCD_D4 23
#define LCD_D5 22
#define LCD_D6 21
#define LCD_D7 14
#define TRIGGER 29
#define ECHO 28
#define LED 2

void Blink_LED(int);
int Find_Distance(int);

int main()
{
    int i;
    int LCD;

    wiringPiSetup();
    pinMode(LED, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(TRIGGER, OUTPUT);

    LCD = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);


    
    system("cd /home/pi/Desktop/Math/Python && /usr/bin/python3 sonar.py");

    
    Blink_LED(LCD);

    delay(500);
    

    return 0;
}

int Find_Distance(int LCD)
{
    time_t start, end;
    double time_elapsed, distance, flag;
    
    digitalWrite(TRIGGER, HIGH);
    delay(0.01);
    digitalWrite(TRIGGER, LOW);

    
    /*
    // save start time
    while(digitalRead(ECHO) == 0)
    {
        time(&start);
    }
    
    // save time of arrival
    while(digitalRead(ECHO) == 1)
    {
        time(&end);
    }
    */

    flag = 0;
    while(flag != 1)
    {
        if(digitalRead(ECHO) == 0)
        {
            time(&start);
            flag = 1;
        }
    }

    flag = 0;
    while(flag != 1)
    {
        if(digitalRead(ECHO) == 1)
        {
            time(&end);
            flag = 1;
        }
    }




    // time difference
    time_elapsed = difftime(end, start);

    // convert time into distance, using speed of sound
    distance = (time_elapsed * 34300) / 2;



    return distance;
}

void Blink_LED(int LCD)
{
    lcdPuts(LCD, "Hello World!");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW); 
    lcdClear(LCD);
    delay(300);
    
}