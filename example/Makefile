CC=g++
CFLAGS=-c -Wall $(INC_DIR) -fPIC 

DBG = -O2

SRC_DIR = src/
OBJ_DIR = build/
LIB_DIR = ../lib/
INC_DIR = -I./include/ -I../include/
LDFLAGS = -pthread -L$(LIB_DIR) -lqbism -Wl,-rpath=$(LIB_DIR)
SRC_TEMPLATE = $(SRC_DIR)%.cpp
OBJ_TEMPLATE = $(OBJ_DIR)%.cpp.o
SOURCES=$(shell find src/ -type f -name '*.cpp') 
OBJECTS=$(patsubst $(SRC_TEMPLATE),$(OBJ_TEMPLATE),$(SOURCES))

EXECUTABLE=./app



all: $(EXECUTABLE)

debug: DBG = -g -D DEBUG

debug: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS) 
	@mkdir $(dir $@) -p
	$(CC)  $(OBJECTS)  -o $@ $(DBG) $(LDFLAGS)

$(OBJ_TEMPLATE): $(SRC_TEMPLATE)
	@mkdir $(dir $@) -p
	$(CC) $(CFLAGS) $< -o $@ $(DBG)

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE) 

run: $(EXECUTABLE)
	$(EXECUTABLE) 
