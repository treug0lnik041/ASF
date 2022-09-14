CC=g++
CFLAGS=-std=c++17
LIBS=-lasound -lstdc++fs
TARGET=libasf.so

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

SOURCES:=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS:=$(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(BIN_DIR)/$(TARGET)

install: $(BIN_DIR)/$(TARGET)
	cp $< /usr/lib/libasf.so
	cp -R include/skyfall /usr/include/skyfall

uninstall: /usr/include/skyfall /usr/lib/libasf.so
	rm -rf $^

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -shared -o $@ $(LIBS)

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	@rm -rf $(OBJECTS) $(BIN_DIR)/$(TARGET)