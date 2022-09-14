#include "../include/skyfall/ASF/AudioContext.h"

skyfall::asf::AudioContext::AudioContext()
{
	unsigned int pcm, period_time;
	snd_pcm_hw_params_t* params;

	unsigned int rate = 44100;

	//Open the PCM device in playback mode
	if (pcm == snd_pcm_open(&this->pcm_handle, PCM_DEVICE_DEFAULT, SND_PCM_STREAM_PLAYBACK, 0) < 0)
		throw std::runtime_error(snd_strerror(pcm));

	//Allocate parameters object and fill it with default values
	snd_pcm_hw_params_alloca(&params);
	snd_pcm_hw_params_any(this->pcm_handle, params);

	//Set parameters
	if (pcm = snd_pcm_hw_params_set_access(this->pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
		throw std::runtime_error(snd_strerror(pcm));

	if (pcm = snd_pcm_hw_params_set_format(this->pcm_handle, params, SND_PCM_FORMAT_S16_LE) < 0)
		throw std::runtime_error(snd_strerror(pcm));

	if (pcm = snd_pcm_hw_params_set_channels(this->pcm_handle, params, 2) < 0)
		throw std::runtime_error(snd_strerror(pcm));

	if (pcm = snd_pcm_hw_params_set_rate_near(this->pcm_handle, params, &rate, 0) < 0)
		throw std::runtime_error(snd_strerror(pcm));

	//Write parameters
	if (pcm = snd_pcm_hw_params(this->pcm_handle, params) < 0)
		throw std::runtime_error(snd_strerror(pcm));

		
	snd_pcm_hw_params_get_period_size(params, &this->frames, 0);
	snd_pcm_hw_params_get_period_time(params, &period_time, 0);
}

skyfall::asf::AudioContext::~AudioContext()
{
	snd_pcm_drain(this->pcm_handle);
	snd_pcm_close(this->pcm_handle);
}

void skyfall::asf::AudioContext::play(const AudioFile* file)
{
	unsigned int pcm = 0;

	int buffer_size = this->frames * file->channels * 2;
	char* buffer = new char[buffer_size];

	for (int loops = file->buffer.size() / buffer_size, i = 0; loops > 0; loops--, i += buffer_size)
	{
		memcpy(buffer, file->buffer.data()+i, buffer_size);

		if (pcm = snd_pcm_writei(this->pcm_handle, buffer, this->frames) == -EPIPE)
		{
			throw std::runtime_error("EPIPE error");
			snd_pcm_prepare(this->pcm_handle);
		}
		else if (pcm < 0)
			throw std::runtime_error(snd_strerror(pcm));
	}

	delete[] buffer;
}