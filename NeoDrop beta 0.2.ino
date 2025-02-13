//www.elegoo.com
// the king of jank, for any questions or remote compatibility request you can email me at burntflowerlabs@gmail.
//2025/feb/13
// keep in mind that if you request a remote it MUST be a IR type remote, as i have no idea of how to make anything else work well 
#include "IRremote.h"
#include <Servo.h>
Servo myservo;

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
//vairable uses to store the last decodedRawData
uint32_t last_decodedRawData = 0;
/*-----( Function )-----*/
void translateIR() // takes action based on IR code received
{
  // Check if it is a repeat IR code 
  if (irrecv.decodedIRData.flags)
  {
    //set the current decodedRawData to the last decodedRawData 
    irrecv.decodedIRData.decodedRawData = last_decodedRawData;
    Serial.println("REPEAT!");
  } else
  {
    //output the IR code on the serial monitor
    Serial.print("IR code:0x");
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
  }
  //IR remote button mapping 
  switch (irrecv.decodedIRData.decodedRawData)
  {
    case 0xB54AFF00: myservo.write(180);    break;// this takes the server and turns it 180 no idea if this will be enough to make the hand open enough
    case 0xBA45FF00: Serial.println("POWER"); break;
    case 0xB847FF00: Serial.println("FUNC/STOP"); break;
    case 0xB946FF00: Serial.println("VOL+"); break;
    case 0xBB44FF00: Serial.println("FAST BACK");    break;
    case 0xBF40FF00: Serial.println("PAUSE");    break;
    case 0xBC43FF00: Serial.println("FAST FORWARD");   break;
    case 0xF807FF00: Serial.println("DOWN");    break;
    case 0xEA15FF00: Serial.println("VOL-");    break;
    case 0xF609FF00: Serial.println("UP");    break;
    case 0xE619FF00: Serial.println("EQ");    break;
    case 0xF20DFF00: Serial.println("ST/REPT");    break;
    case 0xE916FF00: Serial.println("0");    break;
    case 0xF30CFF00: Serial.println("1");    break;
    case 0xE718FF00: Serial.println("2");    break;
    case 0xA15EFF00: Serial.println("3");    break;
    case 0xF708FF00: Serial.println("4");    break;
    case 0xE31CFF00: Serial.println("5");    break;
    case 0xA55AFF00: Serial.println("6");    break;
    case 0xBD42FF00: Serial.println("7");    break;
    case 0xAD52FF00: myservo.write(-180);    break; // and this resets the servo, again no idea if 180 is enough to set it back to the orginal pos as I am yet to make the grabber hand thingie
    //the buttons used for it are buttons nine and eight, useing elegoos remote that comes with the kit, other remotes should work, contact me if you want me to add comapibility for another remote. 
   //nine will turn it 180 and eight will reset it back to the orginal pos. all the other buttons just serial print the name of the button 
    default:
      Serial.println(" other button   ");
      
  }// End Case
  //store the last decodedRawData
  last_decodedRawData = irrecv.decodedIRData.decodedRawData;
  delay(500); // Do not get immediate repeat
} //END translateIR

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); // Start the receiver
    myservo.attach(9);// serial pin for the sevo, plug the other pins in the 3.5v and the gnd pins
  myservo.write(-90);// move servos to center position -> 90° just to set it up 

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode()) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
    
  }
 
}/* --(end main loop )-- */
