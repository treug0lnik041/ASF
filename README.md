# ASF
Simple Skyfall Audio System

## Install
ASF builing as shared library.

Create bin and obj directories for .o and .so files.

```
make -j4
sudo make install
```

## Linking
```
g++ -std=c++17 hello.cpp -o hello -lstdc++fs -lasf
```

## Example
 ```
#include <iostream>

#include <skyfall/ASF/AudioContext.h>
#include <skyfall/ASF/WAVFile.h>

int main(int argc, char **argv) {
	skyfall::asf::AudioContext context; //creating one context for all audio files
	skyfall::asf::WAVFile file("hello.wav");

	context.play(&file);
}
```

Done:
- [x] Context
- [x] Support WAV files

Working on:
- [ ] Support MP3 files
- [ ] Multithreading
- [ ] Stop and play ability
