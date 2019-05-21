main: testing.o NeuralNetwork.o
	g++ -O3 -o main NeuralNetwork.o testing.o
	rm *.o

cuda: cudaTesting.obj NeuralNetwork.obj
	nvcc -O3 -o cudaMain cudaTesting.obj NeuralNetwork.obj
	rm *.obj

cudaTesting.obj: cudaTesting.cu
	nvcc -O3 -c cudaTesting.cu

testing.o: testing.cpp
	g++ -O3 -c testing.cpp

NeuralNetwork.o: src/NeuralNetwork.cpp src/NeuralNetwork.hpp
	g++ -O3 -c src/NeuralNetwork.cpp

NeuralNetwork.obj: src/NeuralNetwork.cpp src/NeuralNetwork.hpp
	nvcc -O3 -c src/NeuralNetwork.cpp

clean:
	rm *.o
	rm *.obj
	rm *.lib