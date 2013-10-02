#include "Wavetables.hpp"
#include <iostream>


using namespace chip;

bool Wavetables::instanceFlag;
chip::Wavetables *Wavetables::single;

float Wavetables::getSample(int waveType, int phase) 
{
    if (waveType > NUM_WAVES || phase > TABLE_SIZE )
    {
        std::cerr << "Warning:(Wavetables.cpp) Array out of bounds in the wavetable.\n";
        waveType = waveType % NUM_WAVES;
        phase = phase % TABLE_SIZE;
    }

    return table[waveType][phase];
}

//Generate Waves
void Wavetables::wavetableGen(){

    int i;

    //Divide TABLE_SIZE into four regions
    int quarter = TABLE_SIZE/4;
    int half = TABLE_SIZE/2;
    int three_fourths = 3*quarter;

    //Cycle through the entirety of TABLE_SIZE and generate triangle, and square waves
    //The triangle wave statement takes the current index of the for loop, casts it to a float (to do division), and scales it to do the correct math in triangle wave generation
	for (i = 0; i < TABLE_SIZE; i++)
	{    
		// TODO: Add more than just square wave
	    
	    table[SAWTOOTH][i] = -16384 + (((float)i/TABLE_SIZE) * 16384);
	    
	    table[NOISE][i] = -16384 + rand() % (16384 * 2);
	    
		//First half of the wave
		if ( i < half )
		{
			table[SQUARE][i] = -16384;
			table[TRIANGLE][i] = -16384 + (((float)i/quarter) * 16384);
		}
		//Third quarter of the wave
		else if ( i < three_fourths )
		{
			table[SQUARE][i] = 16383;
			table[TRIANGLE][i] = 16383 - ((((float)i-half)/quarter) * 16384);
		}
		//Fourth quarter of the wave
		else 
		{
			table[SQUARE][i] = 16383;
			table[TRIANGLE][i] = 16383 - ((((float)i-half)/quarter) * 16384);
		}
	}
}
