run: run-graph
	run-graph data/eks2.dat data/eks2_q.dat

run-graph: graph.o query.o run-graph.o 
	g++ -g3 -std=c++17 -o run-graph *.o

%.o: %.cpp
	g++ -g3 -c -std=c++17 -o $@ $<

clean:
	rm -f *.o *.zip run-graph
