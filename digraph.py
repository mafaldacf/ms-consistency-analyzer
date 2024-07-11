#!/usr/bin/env python3
import json
import re
import networkx as nx
import matplotlib.pyplot as plt
import argparse

def get_spaced_label(name):
    # case-insensitive match for 'Service'
    re_pattern = re.compile(r'(?i)(Service)$')
    if re_pattern.search(name):
        # add a space before 'Service'
        name = re_pattern.sub(r' \1', name)

    # add new line between words separated by spaces
    splits = name.split(' ')
    if len(splits) > 1:
        name = splits[0] + '\n' + splits[1]
    return name

#splits = node['id'].split(' ')
#graph.add_node(node['id'], label=splits[0] + '\n' + splits[1])

parser = argparse.ArgumentParser(description="Visualize graphs based on the specified application and graph type")
parser.add_argument('--app', '-a', required=True, choices=['postnotification', 'foobar', 'sockshop', 'trainticker'], help="The application for which to visualize the graph")
parser.add_argument('--graph', '-g', required=True, choices=['app', 'callgraph'], help="The type of graph to visualize")
args = parser.parse_args()

# load json file
filename = f"assets/{args.app}/digraphs/{args.graph}.json"
with open(filename) as f:
    data = json.load(f)

# create a directed graph and add nodes and edges
graph = nx.DiGraph()
node_colors = {
    'service': 'skyblue',
    'datastore': 'lightgreen',
    'client': 'lightgray',
}
for node in data['nodes']:
    node_label = get_spaced_label(node['id'])
    node_type = node.get('type', 'unknown')
    node_color = node_colors.get(node_type, 'white')
    #print("ADDED NODE", node_label, "WITH COLOR", node_color)
    graph.add_node(node['id'], label=node_label, type=node_type, color=node_color)
    
for link in data['edges']:
    node_call = link.get('call', '')
    graph.add_edge(link['caller'], link['callee'], call=node_call)

# draw the graph
#pos = nx.spring_layout(graph, seed=42)
#plt.figure(figsize=(15, 15))
pos = nx.spring_layout(graph, seed=14, k=2.5, scale=2.0)
plt.figure(figsize=(12, 12))

# debug colors
#print(list(graph.nodes(data="color", default="Not Available")))

node_colors = [graph.nodes[n]['color'] for n in graph.nodes()]
edge_labels = nx.get_edge_attributes(graph, 'call')

# draw nodes with colors and labels
nx.draw(
    graph, pos,
    with_labels=True,
    labels=nx.get_node_attributes(graph, 'label'),
    node_size=7000,
    #node_color="skyblue",
    node_color=node_colors,
    font_size=12,
    font_color="black",
    font_weight="bold",
    edge_color="gray",
    arrows=True,
    arrowsize=40,
    connectionstyle='arc3,rad=0.2',
    #arrowstyle='->',
)

# draw edge labels separately
nx.draw_networkx_edge_labels(
    graph, pos,
    edge_labels=edge_labels,
    font_color='black',
    font_size=11,
    label_pos=0.75,
    connectionstyle='arc3,rad=0.2',
)


plt.title(f"{args.graph.capitalize()} Graph Visualization")
#plt.show()

output_path = f"assets/{args.app}/digraphs/{args.graph}.png"
plt.savefig(output_path, format='png')
print(f"[INFO] graph saved to {output_path}")
