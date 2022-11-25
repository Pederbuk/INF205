run: run-graph
	run-graph

run-graph: graph.o query.o run-graph.o 
	g++ -g3 -f openmp -std=c++17 -o run-graph *.o

%.o: %.cpp
	g++ -g3 -c -std=c++17 -o $@ $<

clean:
	rm -f *.o *.zip run-graph
