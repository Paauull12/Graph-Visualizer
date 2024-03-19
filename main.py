import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

with open("/home/paaull/Documents/grafuri/GrafExportat.txt", "r") as file:
    orientare = file.readline().strip()
    show_costs = file.readline().strip()  # Citirea opțiunii de afișare a costurilor
    data = file.readlines()

G = nx.DiGraph() if orientare == 'dir' else nx.Graph()

cost_dict = {}

for line in data:
    nod1, nod2 = map(int, line.strip("()\n").split(",")[:2])
    G.add_edge(nod1, nod2)
    if int(show_costs) == 1:
        cost = int(line.strip("()\n").split(",")[2])
        cost_dict[(nod1, nod2)] = cost

node_color = np.random.rand(len(G), 3)  

if int(show_costs) == 1:
    nx.draw(G, with_labels=True, node_color=node_color, node_size=1000)
    nx.draw_networkx_edge_labels(G, nx.spring_layout(G), edge_labels=cost_dict)
else:
    nx.draw(G, with_labels=True, node_color=node_color, node_size=1000)

# Afișarea graficului
plt.show()

