#pragma once
#include <vector>

namespace skyfall
{
	namespace asf
	{
		class AudioFile
		{
			friend class AudioContext;
		protected:
			unsigned int rate;
			unsigned short bitsPerSample;
			int channels;

			std::vector<char> buffer;
		};
	}
}