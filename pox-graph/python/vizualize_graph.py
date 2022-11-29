import networkx as nx
import matplotlib.pyplot as plt

file_name = 'directed-graph/python/rand_graph.dat'

plt.figure("Graph")
G = nx.DiGraph()

node_labels = {}
edge_labels = {}
for line in open(file_name).readlines():
    line = line.strip().replace('>', '').replace('<', '').split(' ')
    if len(line) == 3:
        G.add_nodes_from(line[0])
        G.add_edges_from([(line[0], line[-1])])
        edge_labels[(line[0], line[-1])] = str(line[1])
        
        node_labels[line[0]] = str(line[0])
        node_labels[line[-1]] = str(line[-1])

# pos = nx.shell_layout(G)
pos = nx.random_layout(G)

nx.draw_networkx(G, pos=pos, labels=node_labels, arrows=True, node_color="skyblue")
# nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=edge_labels)

plt.show()