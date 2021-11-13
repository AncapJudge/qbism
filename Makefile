CC=g++
CFLAGS=-c -Wall -I$(INC_DIR) -fPIC 

DBG = -O2

SRC_DIR = src/
OBJ_DIR = build/
LIB_DIR = ./lib/
INC_DIR = ./include/
LDFLAGS=  -pthread -L$(LIB_DIR) -shared -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
SRC_TEMPLATE = $(SRC_DIR)%.cpp
OBJ_TEMPLATE = $(OBJ_DIR)%.cpp.o
SOURCES=$(shell find src/ -type f -name '*.cpp') 
OBJECTS=$(patsubst $(SRC_TEMPLATE),$(OBJ_TEMPLATE),$(SOURCES))

TEST_SOURCES=$(shell find test/ -type f -name '*.cpp') 
TEST_OBJECTS=$(patsubst test/%.cpp, test/build/%.cpp.o,$(TEST_SOURCES))
LIBRARY=lib/libqbism.so



all: $(LIBRARY)

debug: DBG = -g -D DEBUG

debug: $(LIBRARY) ./test/app


$(LIBRARY): $(OBJECTS) 
	@mkdir $(dir $@) -p
	$(CC)  $(OBJECTS)  -o $@ $(DBG) $(LDFLAGS)

$(OBJ_TEMPLATE): $(SRC_TEMPLATE)
	@mkdir $(dir $@) -p
	$(CC) $(CFLAGS) $< -o $@ $(DBG)

clean:
	rm -rf $(OBJ_DIR) $(LIBRARY) ./test/lib/* ./test/all ./test/build

test: $(LIBRARY) ./test/app
	./test/app

./test/app: $(TEST_OBJECTS)
	@mkdir ./test/lib -p
	cp $(LIBRARY) ./test/lib
	@mkdir $(dir $@) -p
	$(CC) -L./test/lib -Wl,-rpath=./lib  $(TEST_OBJECTS) -o $@ $(DBG) -lqbism

test/build/%.cpp.o: test/%.cpp
	@mkdir $(dir $@) -p
	$(CC) $(CFLAGS) $< -o $@ $(DBG)