from random import randint, choices, choice

""" Parameters """
n_nodes = 20
n_edges = 20
n_edge_labels = 4

q_len = 4
p_len = 3

# Create nodes
nodes = list(range(n_nodes))

# Create edge labes
edge_labels = [chr(randint(ord('a'), ord('z'))) for _ in range(n_edge_labels)]
print(edge_labels)

# Create edges
edges = []
for _ in range(n_edges):
    edge = choices(nodes, k=2)
    if edge not in edges and edge[0] != edge[1]:
        edges.append(edge)

# Create graph
graph = [(start, choice(edge_labels), end) for start, end in edges]

# Create graph file
with open('directed-graph/python/rand_graph.dat', 'w') as file:
    for line in graph:
        file.write(f'<{line[0]}> <{line[1]}> <{line[2]}>\n')

# Create query files
with open('directed-graph/python/rand_q.dat', 'w') as file:
    for _ in range(q_len):
        file.write(f'<{choice(edge_labels)}> ')

with open('directed-graph/python/rand_p.dat', 'w') as file:
    for _ in range(p_len):
        file.write(f'<{choice(edge_labels)}> ')
