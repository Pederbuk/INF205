run: run-graph
<<<<<<< HEAD
	run-graph data/eks1.dat data/eks1_q.dat
=======
	run-graph graph-benchmark/kb.dat graph-benchmark/query.dat
>>>>>>> cf14e83c89a7e842d9d2ffd625d3a67a90359ad0

run-graph: graph.o query.o run-graph.o 
	g++ -g3 -std=c++17 -o run-graph *.o

%.o: %.cpp
	g++ -g3 -c -std=c++17 -o $@ $<

clean:
	rm -f *.o *.zip run-graph
