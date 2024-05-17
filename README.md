# Blueprint Static Analyzer

Blueprint Static Analyzer is a toolkit that statically analyzes microservice applications written in [Blueprint](https://dl.acm.org/doi/10.1145/3600006.3613138) ([code](https://github.com/Blueprint-uServices/blueprint)) to detect potential consistency violations at configuration time. At the moment, it is capable of capturing *cross-service inconsistencies*, introduced in [Antipode](https://dl.acm.org/doi/10.1145/3600006.3613176).

## Requirements

- [Golang](https://go.dev/doc/install) >= 1.22.2

## How to Run

Available applications:
- `postnotification`
- `foobar`

```zsh
go run main.go -app=postnotification
go run main.go -app=footbar
```

## Toolkit Structure

The toolkit takes as input applications in the `examples` folder.

The representation of the application and the abstract graph are saved in the `assets` folder in JSON format.

The source code is in the `pkg` folder, divided into the following modules: `abstractgraph`, `app`, `controlflow`, `frameworks`, `logger`, `service`, `types`, `utils`.

#### Application

Initializes the application and registers **service nodes** and **database instances** with the application spec generated by Blueprint.

#### Frameworks

Contains utilities specific to each framework. In the context of Blueprint, it contains (i) helper functions to compute the service spec from Intermediate Representation (IR), and (ii) methods that define backends like databases and queues.

#### Service

Parses the Abstract Syntax Tree (AST) of each service, capturing all service, database, or even internal calls within each exposed method.

#### Control Flow Graph

Parses the Control Flow Graph (CFG) of each service, capturing all dependencies in declared and assigned variables within each exposed method block.

Registers the flow of the captured variables to other service, database, or internal calls.

#### Abstract Graph

Generates the final abstract graph containing nodes and edges representing the relationship and order between service and database calls, including queue handlers triggered by publishers.

Nodes can be either **abstract service calls** or **abstract database calls**. An **abstract queue handler** is a subset of service calls representing a queue handler, and an **abstract temporary internal call** is an internal node that represent an internal call in function that handles a service call.
