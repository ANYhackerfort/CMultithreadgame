CXX = g++
CXXFLAGS = -std=c++17

all: game 

game: game.o maingame.o basemap.o topic1.o topic2.o topic6.o 
	$(CXX) $(CXXFLAGS) -o $@ $^
	./game

game.o: game.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

maingame.o: basemap/maingame.cpp basemap/maingame.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

basemap.o: basemap/basemap.cpp basemap/basemap.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

# sort.o: basemap/Util/sort.h
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# inventory.o: basemap/GameEntities/inventory.h
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

gameItem.o: basemap/GameEntities/gameItem.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic1.o: maps/topic1/topic1.cpp maps/topic1/topic1.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic2.o: maps/topic2/topic2.cpp maps/topic2/topic2.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic6.o: maps/topic6/topic6.cpp maps/topic6/topic6.h
	$(CXX) $(CXXFLAGS) -c $< -o $@



clean:
	rm -f game *.o