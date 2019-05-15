main: testing.o NeuralNetwork.o
	g++ -O3 -o main NeuralNetwork.o testing.o
	rm *.o

testing.o: testing.cpp
	g++ -O3 -c testing.cpp

NeuralNetwork.o: NeuralNetwork.cpp NeuralNetwork.h
	g++ -O3 -c NeuralNetwork.cpp

clean:
	rm *.o