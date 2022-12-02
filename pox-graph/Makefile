# to run the test or benchmark simply swap run-graph for benchmark or test
run: run-graph
	./run-graph

run-graph: graph.o query.o run-graph.o 
	g++ -g3 -std=c++17 -o run-graph *.o -fopenmp

%.o: %.cpp
	g++ -g3 -c -std=c++17 -o $@ $< -fopenmp

clean:
	rm -f *.o *.zip run-graph

