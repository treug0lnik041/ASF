CC=g++
CFLAGS=-std=c++17
LIBS=-lasound -lstdc++fs
SRCS=src/AudioContext.cpp src/WAVFile.cpp
OBJS=bin/AudioContext.o bin/WAVFile.o
TARGET=bin/libasf.so

all: $(TARGET)

install: $(TARGET)
	cp $< /usr/lib/libasf.so
	cp -R include/skyfall /usr/include/skyfall

uninstall: /usr/include/skyfall /usr/lib/libasf.so
	rm -rf $^

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -shared -o $@ $(LIBS)

bin/AudioContext.o: src/AudioContext.cpp
	$(CC) $(CFLAGS) -o $@ -c $< -o $@

bin/WAVFile.o: src/WAVFile.cpp
	$(CC) $(CFLAGS) -o $@ -c $< -o $@