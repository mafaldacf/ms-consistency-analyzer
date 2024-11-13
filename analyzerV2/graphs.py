#!/usr/bin/env python3
import re
import networkx as nx
import matplotlib.pyplot as plt
import argparse

import yaml

FOLDER_NAME_BASE = "output"

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

def build_digraph_deps(app, data):
    digraph = nx.DiGraph()
    node_colors = {
        'service': 'skyblue',
        'datastore': 'lightgreen'
    }

    # add service nodes
    for service_name, service_data in data['services'].items():
        digraph.add_node(service_name, label=service_name, type='service', color=node_colors['service'])
        # add edges to dependent services
        for dependent_service in service_data.get('services', []):
            digraph.add_edge(service_name, dependent_service)
        # add edges to datastores
        for datastore in service_data.get('datastores', []):
            digraph.add_edge(service_name, datastore)

    # add datastore nodes
    for datastore_name, datastore_data in data['datastores'].items():
        digraph.add_node(datastore_name, label=datastore_name, type='datastore', color=node_colors['datastore'])

    pos = nx.spring_layout(digraph, seed=14, k=2.5, scale=2.0)
    plt.figure(figsize=(16, 16))
    plt.title("Dependency Graph @ " + app, fontsize=22, fontweight='bold')

    # get node colors from graph attributes
    node_colors_list = [digraph.nodes[n]['color'] for n in digraph.nodes()]
    nx.draw(
        digraph, pos,
        with_labels=True,
        labels=nx.get_node_attributes(digraph, 'label'),
        node_size=7000,
        node_color=node_colors_list,
        font_size=11,
        font_color="black",
        font_weight="bold",
        edge_color="gray",
        arrows=True,
        arrowsize=40
    )

def load_data(app, filename):
    filepath = f"{FOLDER_NAME_BASE}/{app}/{filename}.yaml"
    with open(filepath) as f:
        data = yaml.load(f, Loader=yaml.SafeLoader)
    return data

def save(app, filename):
    filepath = f"{FOLDER_NAME_BASE}/{app}/{filename}_graph.png"
    plt.savefig(filepath, format='png')
    print(f"[{app.upper()}] graph saved to {filepath}")

APPS = ['postnotification', 'postnotification_simple', 'trainticket', 'shopping_app', 'shopping_simple', 'sockshop2', 'foobar']

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Visualize graphs based on the specified application and graph type")
    parser.add_argument('--app', '-a', choices=APPS, required=True, help="The application for which to visualize the graph")
    parser.add_argument('--graph', '-g', choices=['deps', 'call'], required=True, help="The type of graph to visualize")
    args = parser.parse_args()

    if args.graph == "deps":
        data = load_data(args.app, "app")
        build_digraph_deps(args.app, data)
        save(args.app, args.graph)
