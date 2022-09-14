#pragma once
#include <exception>
#include <stdexcept>
#include <vector>

#include <alsa/asoundlib.h>

#include "AudioFile.h"

#define PCM_DEVICE_DEFAULT "default"

namespace skyfall
{
	namespace asf
	{
		class AudioContext
		{
		private:
			snd_pcm_t* pcm_handle;

		private:
			snd_pcm_uframes_t frames;

		public:
			AudioContext();
			~AudioContext();

		public:
			void play(const AudioFile* file);
		};
	}
}