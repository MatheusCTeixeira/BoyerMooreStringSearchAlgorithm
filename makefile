CC = g++

boyer_moore_algorithm: boyer_moore_algorithm.o
	$(CC) $< -o $@

boyer_moore_algorithm.o: boyer_moore_algorithm.cpp
	$(CC) $< -c