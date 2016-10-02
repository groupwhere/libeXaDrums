/*
 * Drum.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_
#define LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_

#include "../../../Sound/SoundBank/SoundBank.h"
#include "../../../Sound/InstrumentSoundType.h"
#include "../../../Sound/SoundProcessor/SoundProcessor.h"

#include "../../Triggers/Triggers/Trigger.h"

#include "../Instrument.h"

#include <functional>
#include <vector>
#include <string>
#include <memory>

using namespace Sound;

namespace DrumKit
{

	class TestDrum : public Instrument
	{

	public:

		TestDrum(InstrumentParameters parameters, std::shared_ptr<SoundBank> sb);
		virtual ~TestDrum();

		virtual void SetTriggers(std::vector<TriggerPtr> const& triggers);
		virtual void SetSound(InstrumentSoundInfo const& soundInfo);
		virtual void SetVolume(float volume);

		virtual bool IsTriggerEvent() const;
		virtual void GetSoundProps(int& id, float& volume) const;

	private:

		static const int numTriggers = 2;

		TriggerPtr drumHeadTrigger;
		TriggerPtr drumRimTrigger;

		int drumHeadSoundId;
		int drumRimSoundId;

	};

}


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_ */
