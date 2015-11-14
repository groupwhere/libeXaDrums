/*
 * Conditioner.cpp
 *
 *  Created on: 4 May 2015
 *      Author: jeremy
 */

#include "Trigger.h"

using namespace std::chrono;

namespace DrumKit
{


	Trigger::Trigger(TriggerParameters triggerParams)
	: triggerParameters(triggerParams),
	  mean(2046),
	  trig(false),
	  out(false),
	  trigTime(0),
	  velocity(0),
	  maxVelocity(0)
	{

		t0 = high_resolution_clock::now();

		return;
	}

	Trigger::~Trigger()
	{


		return;
	}


	bool Trigger::Trig(short value, float& strength)
	{

		// Data normalisation
		short v = std::abs(value - mean);

		velocity = v;

		// Get current time
		high_resolution_clock::time_point t = high_resolution_clock::now();
		unsigned long long dt = (unsigned long long) duration<double, std::micro>(t - t0).count();

		if(velocity > this->triggerParameters.threshold)
		{

			if(!trig)
			{
				 trigTime = dt;
				 trig = true;
			}

			if(maxVelocity < velocity && dt < trigTime + this->triggerParameters.scanTime)
			{
				maxVelocity = velocity;
			}

			if(dt > trigTime + this->triggerParameters.scanTime && !out)
			{
				out = true;

				strength = maxVelocity/numSamples;

				//volume = this->triggerParameters.curve[maxVelocity];
				//mixer->AddToMixer(this->drumId, volume);

				return true;
			}

		}

		if(trig && dt > trigTime + this->triggerParameters.maskTime)
		{
			trig = false;
			maxVelocity = 0;
			out = false;
		}

		strength = 0;

		return false;
	}

}

