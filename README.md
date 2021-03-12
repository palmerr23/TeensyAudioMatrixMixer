# TeensyAudioMatrixMixer
A matrix mixer for the Teensy Audio Library

A mixer that has a flexible number of inputs and outputs - up to 8x8.

AudioMixerMatrix Amixer(INPUTS, OUTPUTS) - create the mixer object with the required number of inputs and outputs

gain(int inputChannel, int outputChannel, float level) - set the mixer gain for this combination of input and output

Tested with T4.0, T4.1 SGTL5000 and CS42448 audio cards up to 8x8 channels.

I have only tested static creation of the mixer object (outside setup()) with constants for the arguments. Dynamic object creation and variable arguments may also work. 
