#include "../include/skyfall/ASF/WAVFile.h"

skyfall::asf::WAVFile::WAVFile(std::filesystem::path path)
{
	std::ifstream file(path);

	WAVFile::format wav;

	file.read((char*)&wav, sizeof(WAVFile::format));

	this->rate = wav.SamplesPerSec;
	this->channels = wav.NumOfChan;
	this->bitsPerSample = wav.bitsPerSample;

	size_t filesize = std::filesystem::file_size(path) - sizeof(WAVFile::format);

	this->buffer.resize(filesize + 4096 - (filesize - ((int)filesize/4096) * 4096));
		
	memset(this->buffer.data(), 0, this->buffer.size());

	file.read(this->buffer.data(), filesize);

	file.close();
}