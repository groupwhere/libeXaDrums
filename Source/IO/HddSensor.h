/*
 * Sensor.h
 *
 *  Created on: 7 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_IO_HDDSENSOR_H_
#define RASPIDRUMS_SOURCE_IO_HDDSENSOR_H_


#include "ISensor.h"

#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <thread>
#include <chrono>


namespace IO
{

	class HddSensor : public ISensor
	{

	public:

		HddSensor(const char* filePath);
		virtual ~HddSensor();

		short GetData(char channel);

	private:

		std::ifstream* file;
		std::vector<short> value;

		unsigned int index;

	};

}

#endif /* RASPIDRUMS_SOURCE_IO_HDDSENSOR_H_ */
