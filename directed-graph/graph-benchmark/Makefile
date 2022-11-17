run: generate-graph
	./generate-graph 20 5 kb.dat query.dat

generate-graph: graph-benchmark.o
	g++ -g3 -std=c++17 -o generate-graph *.o

clean:
	rm -f *.o kb.dat query.dat ./generate-graph
