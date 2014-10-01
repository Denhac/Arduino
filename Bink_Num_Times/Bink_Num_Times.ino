/* 
  blinkNumTimes() makes the onboard LED blink a countable number of times.
  
  This is the only way I can think of to get an understandable numeric
  readout without connecting another device to the Arduino.
  
  I suppose I could write a Morse method...
*/

void setup(){ }

void loop(){
  //Just demonstrate the blink
  int nothing = blinkCounter(5);  
}

void blinkNumTimes(int num_times){
  
  // this seems to be the highest rate at which I can count blinks.
  int delay_ms = 100; 
    
  int i; for( int  i = 0; i < num_times; i++ ){
    
    digitalWrite(13, HIGH);   // turn the LED on
    delay(delay_ms);          // pause
    digitalWrite(13, LOW);    // turn the LED off
    delay(delay_ms);          // pause
  } 
  
  delay( delay_ms * 5 );       // proportional pause after blinks 
}
