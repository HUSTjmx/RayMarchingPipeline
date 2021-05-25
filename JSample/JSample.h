#pragma once
#include <vector>
#include "JVector.h"

class JSample {
public:
	
	void init(){
		sampleNum = 1;
		currentSampleId = 0;
		samples.push_back(JVector2f(0.0f, 0.0f));
	}

	virtual JVector2f getSample(int i){
		return samples[i];
		//return *(samples.begin() + i);
	}

	virtual JVector2f getSampleAuto(){

		JVector2f p = getSample(currentSampleId);
		currentSampleId = (currentSampleId + 1) % sampleNum;
		return p;
	}

private:

	int sampleNum;
	int currentSampleId;
	std::vector<JVector2f> samples;
};