#include <toneAC.h>

void setup() {} // Nothing to setup, just start playing!

void loop() {
  //for (unsigned long freq = 15; freq <= 15000; freq += 10) {  
    toneAC(25); // Play the frequency (150 Hz to 15 kHz in 10 Hz steps).
    delay(1);     // Wait 1 ms so you can hear it.
    toneAC(30); // Play the frequency (150 Hz to 15 kHz in 10 Hz steps).
    delay(1);     // Wait 1 ms so you can hear it.
    toneAC(20); // Play the frequency (150 Hz to 15 kHz in 10 Hz steps).
    delay(1);     // Wait 1 ms so you can hear it.
    toneAC(10); // Play the frequency (150 Hz to 15 kHz in 10 Hz steps).
    delay(1);     // Wait 1 ms so you can hear it.
 
 // }
  //toneAC(0); // Turn off toneAC, can also use noToneAC().

  //while(1); // Stop (so it doesn't repeat forever driving you crazy--you're welcome).
}
