#include "Mixer.hpp"

chip::Mixer::Mixer()
{
	//constructor
	audioList = new std::vector<IAudio*>(0);
	
	// Initialize the audio buffer
	mixedFinal = new std::vector<float>(FRAMES_PER_BUFFER, 0.0);
}

std::vector<float> chip::Mixer::advance(int numSamples)
{
	//the 0th elements are all added together, the 1st elements, 2nd, all the way to the 
	//nth elements and the result is returned (aka - move along the sound wave)
	//std::vector<float>* mixedFinal = new std::vector<float>(numSamples, 0.0);
	std::vector<float>* temp = new std::vector<float>(numSamples, 0.0);
	
	for(int i = 0; i < numSamples; i++)
	{
	    (*mixedFinal)[i] = 0.0;
	}
	
	for(unsigned int i = 0; i < audioList->size(); i++)
	{ 
	    //for each IAudio in audioList, advance
	    *temp = (*audioList)[i]->advance(numSamples);
		for(int j = 0; j < numSamples; j++)
		{
		    //sum each advanced IAudio to the master mixed vector
			(*mixedFinal)[j] = (*mixedFinal)[j] + (*temp)[j];
		}
	}
	temp->clear();
	delete temp;
	
	return *mixedFinal; //the final, "synthesized" list
}



void chip::Mixer::addObjects(IAudio* audioObject)
{
	audioList->push_back(audioObject);
}

void chip::Mixer::removeObjects(IAudio* audioObject)
{
    //TODO
}
	
