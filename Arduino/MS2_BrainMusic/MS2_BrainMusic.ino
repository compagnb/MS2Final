//Major Studio 2 Final
//Blu:m
//Barbara Compagnoni
//Code for Brain Music On Multiple Speakers
//

//include Brain Library For Mind Flex
#include <Brain.h>
#include <toneAC.h>

// Set up the brain reader, pass it the hardware serial object you want to listen on.
Brain brain(Serial);

//Frequency Output Pins - Brain Sounds
const int meditationPin = 9; // 9 for large speaker 1
const int attentionPin = 10; // 10 for large speaker 2
const int alphaHiPin = 11; // 11 for small speaker 1
const int alphaLoPin = 12; // 12 for small speaker 2

///long interval = 500; // Changes based on attention value.
long previousMillis = 0;
int ledState = LOW;   

// Timer reload value, globally available 
unsigned int tcnt2;

// Toggle HIGH or LOW digital write 
int toggle1 = 0;
int toggle2 = 0;
int toggle3 = 0;
int toggle4 = 0;
int toggle5 = 0;

// Keep track of when each note needs to be switched 
int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count5 = 0;

//Meditation Values 
long medVal = 0;
//Attention Values
long atVal = 0;
//Alpha Values
long alphaHiVal = 0;
//Beta Values
long alphaLoVal = 0;



void setup() {
    // Configure I/O Pin Directions
    pinMode(meditationPin, OUTPUT);
    pinMode(attentionPin, OUTPUT);
    pinMode(alphaHiPin, OUTPUT);
    pinMode(alphaLoPin, OUTPUT);
    
    // Start the hardware serial.
    Serial.begin(9600);
    
    // First disable the timer overflow interrupt
    TIMSK2 &= ~(1<<TOIE2);

    // Configure timer2 in normal mode (no PWM) 
    TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
    TCCR2B &= ~(1<<WGM22);

    // Select clock source: internal I/O clock 
    ASSR &= ~(1<<AS2);

    // Disable Compare Match A interrupt (only overflow) 
    TIMSK2 &= ~(1<<OCIE2A);

    // Configure the prescaler to CPU clock divided by 128 */
    TCCR2B |= (1<<CS22)  | (1<<CS20); // Set bits
    TCCR2B &= ~(1<<CS21);             // Clear bit

// We need to calculate a proper value to load the counter.
// The following loads the value 248 into the Timer 2 counter
// The math behind this is:
// (Desired period) = 64us.
// (CPU frequency) / (prescaler value) = 125000 Hz -> 8us.
// (desired period) / 8us = 8.
// MAX(uint8) - 8 = 248;
//

  // Save value globally for later reload in ISR 
  tcnt2 = 248;

  // Finally load end enable the timer 
  TCNT2 = tcnt2;
  TIMSK2 |= (1<<TOIE2);

  }

  // Install the Interrupt Service Routine (ISR) for Timer2.  
  ISR(TIMER2_OVF_vect) {
  // Reload the timer 
  TCNT2 = tcnt2;

  //count1++; count2++; count3++; count4++; count5++;

  if (medVal => 80){
    digitalWrite(meditationPin, toggle1 == 0 ? HIGH : LOW);
    toggle1 = ~toggle1;
    count1 = 0;
  }
  if (atVal => 80){
  digitalWrite(attentionPin, toggle2 == 0 ? HIGH : LOW);
  toggle2 = ~toggle2;
  count2 = 0;
  }
  if (count3 == alphaHiVal){
  digitalWrite(alphaHiPin, toggle3 == 0 ? HIGH : LOW);
  toggle3 = ~toggle3;
  count3 = 0;
  }
  if (count4 == alphaLoVal){
  digitalWrite(alphaLoPin, toggle4 == 0 ? HIGH : LOW);
  toggle4 = ~toggle4;
  count4 = 0;
  }
}


void loop() {
    // Expect packets about once per second.
    if (brain.update()) {
        Serial.println(brain.readCSV());
        
        // Meditation runs from 0 to 100.
        medVal = (100 - brain.readMeditation()) * 10;
       
        // Attention runs from 0 to 100.
        atVal = (100 - brain.readAttention()) * 10;
        
        // Alpha Low runs from 0 to 100.
        alphaLoVal = (100 - brain.readLowAlpha()) * 10;
        
        // Alpha Hi runs from 0 to 100.
        alphaHiVal = (100 - brain.readHighAlpha()) * 10;
    }
    
    // Make sure we have a signal.
    if(brain.readSignalQuality() == 0) {
  
      if (medVal == 50){
            toneAC(25); // Play the frequency (150 Hz to 15 kHz in 10 Hz steps).
            }else if 
        
      count1 = medVal;
      count2 = atVal;
      count3 = alphaHiVal;
      count4 = alphaLoVal;
      Serial.println(medVal);
//        
//        // Blink the LED.
//      if (millis() - previousMillis > interval) {
//        // Save the last time you blinked the LED.
//        previousMillis = millis();   
//
//        // If the LED is off turn it on and vice-versa:
//        if (ledState == LOW)
//          ledState = HIGH;
//        else
//          ledState = LOW;
//      
//        // Set the LED with the ledState of the variable:
//        digitalWrite(ledPin, ledState);
//      } 
    }
    else {
//    digitalWrite(ledPin, LOW);
    }
    
}
