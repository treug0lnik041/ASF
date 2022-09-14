#pragma once
#include <fstream>
#include <filesystem>
#include <cstring>
#include "AudioFile.h"

namespace skyfall
{
	namespace asf
	{
		class WAVFile : public AudioFile
		{
		private:
			struct format
			{
				char RIFF[4];					//RIFF header (magic header)
				unsigned long ChunkSize;		//RIFF chunk size  
				char WAVE[4];					//WAVE header      
				char fmt[4];					//FMT header       
				unsigned long Subchunk1Size;	//Size of the fmt chunk                                
				unsigned short AudioFormat;		//Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
				unsigned short NumOfChan;		//Number of channels 1=Mono 2=Stereo                   
				unsigned long SamplesPerSec;	//Sampling frequency in Hz                             
				unsigned long bytesPerSec;		//Bytes per second 
				unsigned short blockAlign;		//2=16-bit mono, 4=16-bit stereo 
				unsigned short bitsPerSample;	//Number of bits per sample      
				char Subchunk2ID[4];			//"data"  string   
				unsigned long Subchunk2Size;	//Sampled data length 
			};

		public:
			WAVFile(std::filesystem::path path);
		};
	}
}