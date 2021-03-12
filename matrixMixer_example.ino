/*
 * Matrix mixer example
 * 
 */
#include <Audio.h>
#include "mixerMatrix.h"

#define INS 8
#define OUTS 2
#define BLOX 20

AudioSynthWaveformSine sine1;
AudioAnalyzePeak  peak1;
// define the mixer with the required number of INS and OUTS
AudioMixerMatrix Amixer(INS, OUTS); 
AudioAnalyzePeak  peak2;
AudioAnalyzePeak  peak3;

// we need a source of interrupts for the Audio library to operate
// AudioInputAnalog is convenient for T3s, but doesn't create interrupts on the T4 (yet)
// I2S (SGTL5000) is used herre as it's the most common
//AudioInputAnalog adc1;
AudioOutputI2S    i2s1;
AudioControlSGTL5000 sgtl1;

// sine to mixer input 1 and peak1
AudioConnection p1(sine1, 0, Amixer, 0); 
AudioConnection p2(sine1, 0, peak1, 0); 

// mixer outputs 1 & 2 to peaks and I2S 
AudioConnection p3(Amixer, 0, i2s1, 0); 
AudioConnection p4(Amixer, 0, peak2, 0);   

AudioConnection p5(Amixer, 1, i2s1, 1); 
AudioConnection p6(Amixer, 1, peak3, 0);   
void setup() 
{
  // put your setup code here, to run once:
  AudioMemory(BLOX);
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting matrix mixer example");

  sgtl1.enable();
  sine1.frequency(800);
  sine1.amplitude(1.0);
  
Serial.println("Done setup");
}
uint32_t loops;
float Again1 = 1.0, Again2 = 1.0;
void loop() { 
  int procUse = AudioProcessorUsage();
  int memUse = AudioMemoryUsage();
  float peakA = peak1.read();
  float peakB = peak2.read();
  float peakC = peak3.read();  

  Serial.printf("%i: proc %i, mem %i, input level %3.2f\n", loops, procUse, memUse, peakA);
  Serial.printf("Gain1 %3.2f, output1 level %3.2f\n", Again1, peakB);
  Serial.printf("Gain2 %3.2f, output2 level %3.2f\n\n", Again2, peakC);

  // set gain for next iteration
  Again1 = (float)random(100, 1000) / 1000.0;    // gain 0.1 .. 1.0
  Amixer.gain(0, 0, Again1); 
  Again2 = (float)random(100, 1000) / 1000.0;    // gain 0.1 .. 1.0
  Amixer.gain(0, 1, Again2); 

  delay(5000);
  loops++;
}
