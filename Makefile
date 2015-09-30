CXXFLAGS=-std=c++14 -Wall -Werror -Wextra

test: src/main.o src/json.o src/map.o src/object.o
	g++ $(LDFLAGS) $^ -o $@ -lboost_system
