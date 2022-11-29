run: benchmark
	./benchmark

benchmark: graph.o query.o benchmark.o 
	g++ -g3 -std=c++17 -o benchmark *.o -fopenmp

%.o: %.cpp
	g++ -g3 -c -std=c++17 -o $@ $< -fopenmp

clean:
	rm -f *.o *.zip benchmark
