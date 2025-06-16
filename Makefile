CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17 -Iinc `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: grig

grig: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	-find . -type f -name "*.o" -delete
	rm -rf grig
