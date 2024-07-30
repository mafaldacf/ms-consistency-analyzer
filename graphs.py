#!/usr/bin/env python3
import glob
import json
import os
import re
import networkx as nx
import matplotlib.pyplot as plt
import argparse
from collections import defaultdict

FOLDER_NAME_BASE = "output"
FOLDER_NAME_GRAPHS = "graphs"
FOLDER_NAME_OUTPUT = "out"

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

def compute_base_path(app, per_requests):
    path = f"{FOLDER_NAME_BASE}/{app}/{FOLDER_NAME_GRAPHS}"
    if per_requests:
        path += "/per_requests"
    else:
        path += "/global"
    return path

def load(app, graph, per_requests):
    base_path = compute_base_path(app, per_requests)

    filename = f"{base_path}/out/{graph}"
    if not per_requests:
        filename += "_graph"
    
    filename += ".json"
    with open(filename) as f:
        data = json.load(f)
    return data

def save(app, graph, labeled, per_requests):
    base_path = compute_base_path(app, per_requests)

    if labeled:
        plt.title(f"{graph.capitalize()} Labeled Graph")
    else:
        plt.title(f"{graph.capitalize()} Graph")

    #plt.show()

    output_path = f"{base_path}/figures/{graph}"
    if labeled:
        output_path += "_labeled"
    if not per_requests:
        output_path += "_graph"

    output_path += ".png"

    output_dir = os.path.dirname(output_path)
    os.makedirs(output_dir, exist_ok=True)

    plt.savefig(output_path, format='png')
    print(f"[{app.upper()}] graph saved to {output_path}")

def search_all_per_requests(app):
    base_path = compute_base_path(app, True)
    directory = f"{base_path}/out/"
    pattern = os.path.join(directory, 'trace_*.json')
    files = glob.glob(pattern)
    names = [os.path.splitext(os.path.basename(file))[0] for file in files]
    return names

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Visualize graphs based on the specified application and graph type")
    parser.add_argument('--app', '-a', choices=['postnotification', 'foobar', 'sockshop', 'trainticket', 'shopping_app'], help="The application for which to visualize the graph")
    parser.add_argument('--graph', '-g', choices=['app', 'call'], help="The type of graph to visualize")
    parser.add_argument('--labeled', '-l', action='store_true', help="Construct labeled digraph")
    parser.add_argument('--all', action='store_true', help="Construct all combinations of digraphs for all applications")
    args = parser.parse_args()

    if args.all:
        if args.app != None:
            apps = [args.app]
        else:
            apps = ['postnotification', 'trainticket', 'shopping_app', 'sockshop2']
        graphs = ['app', 'call']
        for app in apps:
            print(f"[INFO] saving graphs for {app} app...")
            for graph in graphs:
                data = load(app, graph, False)
                build_digraph(data, graph, False)
                save(app, graph, False, False)
                if graph == 'call':
                    build_digraph(data, graph, True)
                    save(app, graph, True, False)
            for graph in search_all_per_requests(app):
                data = load(app, graph, True)
                build_digraph(data, graph, True)
                save(app, graph, True, True)
            print()

    else:     
        data = load(args.app, args.graph, False)
        build_digraph(data, args.graph, args.labeled)
        save(args.app, args.graph, args.labeled)
