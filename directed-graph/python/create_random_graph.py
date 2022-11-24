from random import randint, choices, choice


for i in range(1, 11):
    """ Parameters """
    n_nodes = 20 * i
    n_edges = n_nodes
    n_edge_labels = 5
    query_len = 5
    """ ---------- """


    # Create nodes
    nodes = list(range(n_nodes))


    # Create edge labes
    edge_labels = [chr(randint(ord('a'), ord('z'))) for _ in range(n_edge_labels)]


    # Create edges
    edges = []
    for _ in range(n_edges):
        edge = choices(nodes, k=2)
        if edge not in edges and edge[0] != edge[1]:
            edges.append(edge)


    # Create graph
    graph = [(start, choice(edge_labels), end) for start, end in edges]


    # Create graph file
    with open(f'python/b{i}_g.dat', 'w') as file:
        for line in graph:
            file.write(f'<{line[0]}> <{line[1]}> <{line[2]}>\n')
        file.write('<>')


    # Create query files
    with open(f'python/b{i}_q.dat', 'w') as file:
        for _ in range(query_len):
            file.write(f'<{choice(edge_labels)}> ')
        file.write('<>\n')
        
        for _ in range(query_len):
            file.write(f'<{choice(edge_labels)}> ')
        file.write('<>')
