#include <Servo.h>

Servo   servo;                                  // creates servo object
int     pos     = 0;                            // variable to store servo position
int     red     = 8;                            // declare pin to LED
int     green   = 10;                           
int     pi      = 5;                            // declare pin to raspberry Pi
int     button  = 2;                            // declare pin to 'button'

void setup()
{
    servo.attach(12);                           // attaches servo to pin 12
    pinMode(red,    OUTPUT);                    // declare if pin recieves an input of gives an output as 5V signal
    pinMode(green,  OUTPUT);                    
    pinMode(pi,     INPUT);
    pinMode(button, INPUT);
}

void loop()
{
    if( digitalRead(pi)     == HIGH ||          // Pi gives a HIGH signal when pinged
        digitalRead(button) == HIGH)            // 'button' gives a HIGH signal when pressed
    {  
        digitalWrite(red,   LOW);               // LED gets a LOW signal
        digitalWrite(green, HIGH);              // LED gets a HIGH signal
        for(pos = 30; pos <= 120; pos += 1)     // servo goes from 30 to 120 degrees in steps of 1 degree
        {
            if(pos == 120)                      
            {
                break;                          // break the for-loop when servo reaches 120 degrees
            }
            else                                
            {
                servo.write(pos);               // tell servo to go to position in variable 'pos'
                break;                          // break the for-loop when servo reaches it's final position
            }
        }
        delay(5000);                            // delay of 5000ms before the code continues
    }
    else                                        // as long as 'button' is not pressed OR no signal is recieved from Pi
    {
        digitalWrite(red,   HIGH);
        digitalWrite(green, LOW);
        for(pos = 120; pos >= 30; pos -= 1)     // servo goes from 120 to 30 degrees in steps of 1 degree
        {
            if(pos <= 30)
            {
                break;
            }
            else
            {
                servo.write(pos);
                break;
            }
        }
    }
}
