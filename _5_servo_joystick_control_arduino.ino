//this project includes code addapted from "Superb Tech" on youtube https://www.youtube.com/watch?v=F39-1hnjWn0
// as well as single button control from "Robojax" on youtube https://www.youtube.com/watch?v=fPrPRZlGdvA

//this code functions as mapping for 5 servos on a Keys_SJoys joystick module,
//X axis for 1 servo control Y axis mirroring for 2 servos as well as push button mirroring for 2 servos
//future functions will include servo smoothing for more natural movement of animatronics.
//check the github repo for a fritzing diagram of the project

//------------------------------------------------------------------------------------------------Mike Loves you <3--------------------

#include <Servo.h> // include servo library

Servo brows; // define servos
Servo ears1;
Servo ears2;
Servo eyes;
Servo eyes2;

//joystick axis int's
int joyX = 0; // give variable to joystick readings
int joyY = 1;

int joyVal; // create variable for joystick value

const int BUTTON_PIN = 6; // Arduino pin connected to button's pin
const int SERVO_PIN  = 12; //arduino pin connected to pin 12

//push button int's
int angle = 0;          // the current angle of servo motor
int lastButtonState;    // the previous state of button
int currentButtonState;

void setup()
{
brows.attach(9); // start servos
ears1.attach(10);
ears2.attach(11);
eyes2.attach(13);

  Serial.begin(9600);                // initialize serial
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  eyes.attach(SERVO_PIN);           // attaches the servo on pin 12 to the servo object

  eyes.write(angle); //writes initial servo angle for eyes servos
  eyes2.write(90-angle);
  currentButtonState = digitalRead(BUTTON_PIN);



}


void loop()
{

//Joystick loop  
joyVal = analogRead(joyX); // read value from joystick
//joyVal = map(joyVal, 0, 1023, 0, 180); // change value range to 0-180
brows.write(map(joyVal, 0, 1023, 0, 180)); // write value to servo

joyVal = analogRead(joyY); // repeat same for y axis
//joyVal = map(joyVal, 0, 1023, 0, 180);
ears1.write(map(joyVal, 0, 1023, 0, 180));
delay(20); // add small delay to reduce noise

ears2.write(180-joyVal); //writes mirrored servo position for second ear servo
delay(20); 

//Button loop
  lastButtonState    = currentButtonState;      // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state

  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The button is pressed");

    // change angle of servo motor
    if(angle == 0)
      angle = 90;
    else
    if(angle == 90)
      angle = 0;

    // control servo motor arccoding to the angle
    eyes.write(angle);
    eyes2.write(90-angle);
  }
  
  
}
