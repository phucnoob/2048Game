# The compiler PATH
COMPILER = g++


LIB_FLAGS = -LSDL/lib -lSDL2main -lSDL2 -lSDL2_image
INCLUDE_FLAGS = -ISDL/include

# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
COMPILE_FLAGS = -Wall -c -std=c++11 $(INCLUDE_FLAGS)
BUILD_FLAGS = -mwindows -mconsole $(LIB_FLAGS)

# Your main source code
SRC = main.cpp
# Your executable directory
OUT = out

# The obj name
TARGET = main

all: build run

run:
	$(OUT)/$(TARGET).exe

build: compile 
	$(COMPILER) $(OUT)/$(TARGET).o $(BUILD_FLAGS) -o $(OUT)/$(TARGET).exe
compile:
	$(COMPILER) $(COMPILE_FLAGS) $(SRC) -o $(OUT)/$(TARGET).o

clean:
	rm $(OUT)/*.o $(OUT)/*.exe