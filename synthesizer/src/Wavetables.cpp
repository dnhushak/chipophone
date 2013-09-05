#include "Wavetables.hpp"

using namespace chip;

Wavetables::Wavetables()
{
    /*
    int waveType;
    int i;
    
    for (waveType = 0; waveType < NUM_WAVES; waveType++)
	{ 
        for (i = 0; i < TABLE_SIZE; i++)
	    { 
	        table[waveType][i] = 0;
	    }
    }
    */

	wavetablegen();
}

float Wavetables::getSample(int waveType, float phase, int numSamples) 
{
    // return table[waveType][??];
	return 0;
}

//Generate Waves
void Wavetables::wavetablegen(void){

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
	
		//First half of the wave
		if ( i < half )
		{
			table[SQUARE][i] = -16384;
		}
		//Third quarter of the wave
		else if ( i < three_fourths )
		{
			table[SQUARE][i] = 16383;
		}
		//Fourth quarter of the wave
		else 
		{
			table[SQUARE][i] = 16383;
		}
	}
}
