CXX = g++
CXXFLAGS = -std=c++17

all: game 

# Compile and run game
game: game.o maingame.o basemap.o topic1.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	./game
# Clean up
clean:
	rm -f game *.o
