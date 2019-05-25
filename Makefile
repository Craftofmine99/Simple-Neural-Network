BIN=./bin/
SRC=./src/

main: testing.o NeuralNetwork.o
	g++ -O3 -o $(BIN)main NeuralNetwork.o testing.o
	rm *.o

cuda: cudaTesting.obj NeuralNetwork.obj
	nvcc -O3 -o $(BIN)cudaMain cudaTesting.obj NeuralNetwork.obj
	rm *.obj

cudaTesting.obj: cudaTesting.cu
	nvcc -O3 -c cudaTesting.cu

testing.o: testing.cpp
	g++ -O3 -c testing.cpp

NeuralNetwork.o: $(SRC)neuralNetwork/NeuralNetwork.cpp $(SRC)neuralNetwork/NeuralNetwork.hpp
	g++ -O3 -c $(SRC)neuralNetwork/NeuralNetwork.cpp

NeuralNetwork.obj: $(SRC)neuralNetwork/NeuralNetwork.cpp $(SRC)neuralNetwork/NeuralNetwork.hpp
	nvcc -O3 -c $(SRC)neuralNetwork/NeuralNetwork.cpp

chess:
	g++ -O3 -c $(SRC)chess/chess.cpp
	g++ -O3 -c $(SRC)chess/main.cpp
	g++ -O3 -o $(BIN)chessMain chess.o main.o
	rm *.o

clean:
	rm $(BIN)*