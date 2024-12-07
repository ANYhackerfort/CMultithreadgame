CXX = g++
CXXFLAGS = -std=c++17

all: game 

game: game.o maingame.o basemap.o topic1.o topic2.o topic3.o topic4.o topic5.o topic6.o topic7.o topic8.o topic9.o topic10.o
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

topic3.o: maps/topic3/topic3.cpp maps/topic3/topic3.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic4.o: maps/topic4/topic4.cpp maps/topic4/topic4.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic5.o: maps/topic5/topic5.cpp maps/topic5/topic5.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic6.o: maps/topic6/topic6.cpp maps/topic6/topic6.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic7.o: maps/topic7/topic7.cpp maps/topic7/topic7.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic8.o: maps/topic8/topic8.cpp maps/topic8/topic8.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic9.o: maps/topic9/topic9.cpp maps/topic9/topic9.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

topic10.o: maps/topic10/topic10.cpp maps/topic10/topic10.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f game *.o