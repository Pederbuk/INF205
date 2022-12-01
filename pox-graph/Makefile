run: test
	./test

test: graph.o query.o test.o 
	g++ -g3 -std=c++17 -o test *.o -fopenmp

%.o: %.cpp
	g++ -g3 -c -std=c++17 -o $@ $< -fopenmp

clean:
	rm -f *.o *.zip test
