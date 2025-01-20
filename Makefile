CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := 
EXECUTABLE  := main

all: $(BIN)/$(EXECUTABLE)

rebuild: clean all

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

#$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(SRC)/pt2/*.cpp
$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm -r $(BIN)/*