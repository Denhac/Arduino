/*
  The documentation states that analog voltage detection is very
  sensitive, such that capacative touch switches are possible, and 
  ambient RF noise will affect read voltage on unconnected pins.
  
  See http://arduino.cc/en/Reference/AnalogRead
  
  This sketch is an attempt to produce a blinking output that will
  indicate changes in ambient rf noise and capcitive changes acroos
  the analog read pins.  
  
  It's not very useful but it's the only thing I can think of that 
  gives you a meaningful i/o result without attaching anything else
  to the board.
*/

int led_pin = 13;

int analog_pins[] = {1,2,3,4,5};
int num_of_pins = 5;

void setup(){
  
  // make all the analog pins inputs.
  // this should happen by defalt anyway.
  for(int i = 0; i < num_of_pins; i++){
    
    pinMode(analog_pins[i], INPUT);
  }
}

void loop(){
 
  
  int ambient_noise_value;
  
  // sum the detected voltage on all pins
  for( int i = 0; i < 5; i++ ){
    
    ambient_noise_value += analogRead(analog_pins[i]);
  }
  
  //average the voltage
  int ambient_noise_value =  / 5 ; 
  
  // Blink the number of times equalling the read voltage
  // in units of 1/5000th of a volt
  blinkNumTimes(ambient_noise_value);
  
  
  
  // An alternative way of giving us an idea of the read voltages
  // using the duration of a really fast LED flicker.
  //
  //blink_freq_hz = 20; 
  //tone(13, blink_freq_hz, blink_freq_hz * ambient_noise_value);
  
}


// blink a number of times and then pause
void blinkNumTimes(int num_times){
  
  // this seems to be the highest blink rate at which I can count blinks.
  int delay_ms = 100; 
    
  int i; for( int  i = 0; i < num_times; i++ ){
    
    digitalWrite(13, HIGH);   // turn the LED on
    delay(delay_ms);          // pause
    digitalWrite(13, LOW);    // turn the LED off
    delay(delay_ms);          // pause
  } 
  
  delay( delay_ms * 5 );       // proportional pause after blinks 
}
