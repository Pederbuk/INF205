import networkx as nx
import matplotlib.pyplot as plt


# Graph to be visualized
file_name = 'pox-graph/data/eks1.dat'


# Create figure
plt.figure("Graph")
plt.title("Graph eks1")
G = nx.DiGraph()


# Read graph from file
node_labels = {}
edge_labels = {}
for line in open(file_name).readlines():
    line = line.strip().replace('>', '').replace('<', '').split(' ')

    if len(line) == 3:
        G.add_node(line[0])
        G.add_node(line[2])
        G.add_edge(line[0], line[2])
        
        edge_labels[(line[0], line[2])] = str(line[1])
        node_labels[line[0]] = str(line[0])
        node_labels[line[2]] = str(line[2])


# Draw graph
pos = nx.shell_layout(G)
nx.draw_networkx(G, pos=pos, labels=node_labels, arrows=True, node_color="skyblue")
nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=edge_labels)

plt.show()