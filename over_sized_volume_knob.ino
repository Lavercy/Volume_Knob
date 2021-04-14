#include <ClickEncoder.h>
#include <TimerOne.h>
#include <KeyboardioHID.h>


#define ENCODER_CLK A0
#define ENCODER_DT A1
#define ENCODER_SW A2

ClickEncoder *encoder; // variable representing the rotary encoder
int16_t last, value, mode; // variables for current and last rotation value
void timerIsr() {
  encoder->service();
}

void setup() {
  Serial.begin(9600); // Opens the serial connection used for communication with the PC. 
  ConsumerControl.begin();
  Mouse.begin();
  encoder = new ClickEncoder(ENCODER_DT, ENCODER_CLK, ENCODER_SW, 3); // Initializes the rotary encoder with the mentioned pins

  Timer1.initialize(1000); // Initializes the timer, which the rotary encoder uses to detect rotation
  Timer1.attachInterrupt(timerIsr); 

  last = -1;
  mode = 1;
} 

void loop() {  
  value += encoder->getValue();


  if (value != last) { // New value is different than the last one, that means to encoder was rotated
    if(value < last){ // Detecting the direction of rotation
      // Implemented different modes. Modes is changed by double clicking the button. 
      // In Mode1, rotation of the konb will increase or decrease volume
      // In Mode2, rotation of the know will emulate left and right horizontal scroll. 
      if (mode == 1) 
      {
          ConsumerControl.press(HID_CONSUMER_VOLUME_INCREMENT);
          ConsumerControl.sendReport();
          ConsumerControl.release(HID_CONSUMER_VOLUME_INCREMENT);
          ConsumerControl.sendReport();
      } else{
          Mouse.move(0,0,0,1);
          Mouse.sendReport();
      }
      }else if (value > last){
        if (mode == 1) {
          ConsumerControl.press(HID_CONSUMER_VOLUME_DECREMENT);
          ConsumerControl.sendReport();
          ConsumerControl.release(HID_CONSUMER_VOLUME_DECREMENT);
          ConsumerControl.sendReport();
        }else{
          Mouse.move(0,0,0,-1);
          Mouse.sendReport();
        }     
    }
    last = value;
  }




// Looking for Button Clicks
  ClickEncoder::Button b = encoder->getButton(); // Asking the button for it's current state
  if (b != ClickEncoder::Open) {
    
    switch (b) {
      case ClickEncoder::Clicked: // Button was clicked once
      // In Mode1, single click will play pause media.
      if (mode == 1)
      {
        ConsumerControl.press(HID_CONSUMER_PLAY_SLASH_PAUSE);
        ConsumerControl.sendReport();
        ConsumerControl.release(HID_CONSUMER_PLAY_SLASH_PAUSE);
        ConsumerControl.sendReport();
      } else{
      // In Mode2, single click will skip current track. 
        ConsumerControl.press(HID_CONSUMER_SCAN_NEXT_TRACK);
        ConsumerControl.sendReport();
        ConsumerControl.release(HID_CONSUMER_SCAN_NEXT_TRACK);
        ConsumerControl.sendReport();
      }
      break;
      // Modes are chnaged with a double click. 
      case ClickEncoder::DoubleClicked:
        if (mode == 1){
          mode = 2;
        } else {
          mode = 1;
        }
      break;      
    }
  }

  delay(250);
}
        
