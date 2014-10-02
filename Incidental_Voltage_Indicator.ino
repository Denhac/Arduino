/*
  The docs state that voltage detection is very sensitive, such 
  that capacative touch switches are possible, and ambient RF 
  noise will affect read voltage on unconnected pins.
  
  See http://arduino.cc/en/Reference/AnalogRead
  
  This sketch is an attempt to produce a blinking output that will
  indicate changes in voltage and capcitive changes acroos
  the analog read pins.  
  
  It's not very useful but it's the only thing I can think of that 
  gives you a meaningful i/o result without attaching anything else
  to the board.

  Touch your fingers to the back of pins 1-5 and you'll see the 
  blink rate change.
*/

int analog_pins[] = {1,2,3,4,5};

void setup(){}
  
void loop(){
  // sum the detected voltage on all pins
  int ambient_voltage;
  for( int i = 0; i < 5; i++ ){ ambient_voltage += analogRead(analog_pins[i]);}
  
  // pulse the light 
  tone(
    LED_BUILTIN, 
    map(
      ambient_voltage/5, // Avg  pin voltage
      0,    // Min voltage read
      1023, // Max voltage read
      0,    // Min Hz.
      30    // Max Hz.  anything higher looks like a steady light.
    )
  );
}
