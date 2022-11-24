run: benchmark
	benchmark data/eks2.dat data/eks2_q.dat

benchmark: graph.o query.o benchmark.o 
	g++ -g3 -std=c++17 -o benchmark *.o

%.o: %.cpp
	g++ -g3 -c -std=c++17 -o $@ $<

clean:
	rm -f *.o *.zip benchmark
