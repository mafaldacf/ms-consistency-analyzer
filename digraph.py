#!/usr/bin/env python3
import json
import re
import networkx as nx
import matplotlib.pyplot as plt
import argparse
from collections import defaultdict

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

def build_digraph(data, graph_type, labeled):
    digraph = nx.DiGraph()

    node_colors = {
        'service': 'skyblue',
        'datastore': 'lightgreen',
        'client': 'lightgray',
    }

    for node in data['nodes']:
        node_label = get_spaced_label(node['id'])
        node_type = node.get('type', 'unknown')
        node_color = node_colors.get(node_type, 'white')
        digraph.add_node(node['id'], label=node_label, type=node_type, color=node_color)
    
    for edge in data['edges']:
        digraph.add_edge(edge['caller'],  edge['callee'], call=edge.get('call', ''))

    pos = nx.spring_layout(digraph, seed=14, k=2.5, scale=2.0)
    plt.figure(figsize=(16, 16))

    node_colors = [digraph.nodes[n]['color'] for n in digraph.nodes()]
    nx.draw(
        digraph, pos,
        with_labels=True,
        labels=nx.get_node_attributes(digraph, 'label'),
        node_size=7000,
        node_color=node_colors,
        font_size=11,
        font_color="black",
        font_weight="bold",
        edge_color="gray",
        arrows=True,
        arrowsize=40,
        connectionstyle='arc3,rad=0.3',
    )

    if graph_type != "app" and labeled:
        edge_count = defaultdict(lambda: {'calls': [], 'count': 0})

        for edge in data['edges']:
            caller = edge['caller']
            callee = edge['callee']
            call_depth = edge.get('depth', -1)
            call_type = edge.get('call', '')
            if call_depth != -1:
                call_type = "[" + str(call_depth) + "] " + call_type
            edge_count[(caller, callee)]['calls'].append(call_type)
            edge_count[(caller, callee)]['count'] += 1

        combined_edge_labels = {
            edge: f"{'\n'.join(data['calls'])}" if data['count'] > 1 else f"{data['calls'][0]}"
            for edge, data in edge_count.items()
        }

        nx.draw_networkx_edge_labels(
            digraph, pos,
            edge_labels=combined_edge_labels,
            font_color='black',
            font_size=10,
            label_pos=0.65,
            connectionstyle='arc3,rad=0.3',
        )

def load(app, graph):
    filename = f"assets/{app}/digraphs/{graph}_graph.json"
    with open(filename) as f:
        data = json.load(f)
    return data

def save(app, graph, labeled):
    if labeled:
        plt.title(f"{graph.capitalize()} Multi DiGraph Visualization")
    else:
        plt.title(f"{graph.capitalize()} DiGraph Visualization")

    #plt.show()

    if labeled:
        output_path = f"assets/{app}/digraphs/{graph}_labeled_graph.png"
    else:
        output_path = f"assets/{app}/digraphs/{graph}_graph.png"
    plt.savefig(output_path, format='png')
    print(f"[INFO] graph saved to {output_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Visualize graphs based on the specified application and graph type")
    parser.add_argument('--app', '-a', required=True, choices=['postnotification', 'foobar', 'sockshop', 'trainticket', 'threechain2'], help="The application for which to visualize the graph")
    parser.add_argument('--graph', '-g', required=True, choices=['app', 'call'], help="The type of graph to visualize")
    parser.add_argument('--labeled', '-l', action='store_true', help="Construct labeled digraph")
    args = parser.parse_args()

    data = load(args.app, args.graph)
    build_digraph(data, args.graph, args.labeled)
    save(args.app, args.graph, args.labeled)
