main: testing.o NeuralNetwork.o
	g++ -O3 -o main NeuralNetwork.o testing.o
	rm *.o

testing.o: testing.cpp
	g++ -O3 -c testing.cpp

NeuralNetwork.o: src/NeuralNetwork.cpp src/NeuralNetwork.hpp
	g++ -O3 -c src/NeuralNetwork.cpp

clean:
	rm *.o