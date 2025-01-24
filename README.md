# Microservices Consistency Analyzer

**Microservices Consistency Analyzer** is a toolkit that statically analyzes microservice applications written in frameworks (e.g. [Service Weaver](https://dl.acm.org/doi/10.1145/3593856.3595909) and [Blueprint](https://dl.acm.org/doi/10.1145/3600006.3613138)) that introduce a new modular approach for building and deploying microservices. The goal is to detect potential consistency violations at configuration time by leveraging the global view over the entire application, including the relationship between services and operations to underlying databases. At the moment, the toolkit supports Blueprint ([code](https://github.com/Blueprint-uServices/blueprint)), and is capable of capturing _cross-service inconsistencies_, introduced in [Antipode](https://dl.acm.org/doi/10.1145/3600006.3613176). In the future, we aim to support a wide variety of similar frameworks and capture additional consistency anomalies.

## Getting Started

After cloning the repository, fetch submodules for `blueprint` repository

```zsh
cd ms-consistency-analyzer
git submodule update --init --recursive
```

## Requirements

- [Golang](https://go.dev/doc/install) >= 1.22.2

## How to Run

Available applications:
- `foobar`
- `shopping_simple`
- `shopping_app`
- `postnotification_simple`
- `postnotification`
- `sockshop2`
- `trainticket`

```zsh
python3 -m venv ~/.venv
source ~/.venv/bin/activate
pip3 install -r requirements.txt

go run main.go --help

go run main.go -app=foobar
go run main.go -app=shopping_simple
go run main.go -app=shopping_app
go run main.go -app=postnotification_simple
go run main.go -app=postnotification
go run main.go -app=sockshop2
go run main.go -app=trainticket

go run main.go -app=foobar --xcy --fk --cascade
go run main.go -app=shopping_simple --xcy --fk --cascade
go run main.go -app=shopping_app --xcy --fk --cascade
go run main.go -app=postnotification_simple --xcy --fk --cascade --specialization
go run main.go -app=postnotification --xcy --fk --cascade
go run main.go -app=sockshop2 --xcy --fk --cascade
go run main.go -app=trainticket --xcy --fk --cascade
go run main.go -app=app_constraints_referential_integrity --xcy --fk --cascade
go run main.go -app=app_constraints_specialization --xcy --fk --cascade --specialization

go run main.go -app=dsb_sn --xcy --fk --cascade

# TODO
go run main.go -app=dsb_hotel --xcy --fk --cascade


go run main.go -all=true --xcy --fk --cascade

#FIXME: XCY analysis doesn't work if we enable "app.ResetAllDataflows()" in abstractgraph/schema.go

source ~/.venv/bin/activate

./graphs.py --help
# usage: graphs.py [-h] [--app {postnotification,postnotification_simple,trainticket,shopping_app,shopping_simple,sockshop2,foobar}] [--graph {app,call}] [--labeled] [--all]

./graphs.py --app foobar
./graphs.py --app shopping_simple
./graphs.py --app shopping_app
./graphs.py --app postnotification_simple
./graphs.py --app postnotification
./graphs.py --app sockshop2
./graphs.py --app trainticket
./graphs.py --app app_constraints_referential_integrity
./graphs.py --app app_constraints_specialization

./graphs.py --app dsb_sn
./graphs.py --app dsb_hotel

./graphs.py --all
```

## Summary

| Application Name                          | Runs          | XCY Analysis  | Cascade Analysis  | Foreign Key Analysis  | Specialization |
|-------------------------------------------|---------------|---------------|-------------------|-----------------------|----------------|
| `foobar`                                  | **YES**       | 0             | 0                 | 0                     | 0              |
| `shopping_simple`                         | **YES**       | 0             | 1;1               | 0                     | 0              |
| `shopping_app`                            | **YES**       | 1?            | 0                 | 1?                    | 0              |
| `postnotification_simple`                 | **YES**       | 1             | 0                 | 1                     | 0              |
| `postnotification`                        | **YES**       | 2             | 0                 | 2                     | 0              |
| `sockshop2`                               | **YES**       | 0             | 4;0               | 0                     | 0              |
| `trainticket`                             | **YES**       | 0             | 13;0              | 0                     | 0              |
| `dsb_sn`                                  | **YES**       | 0             | 0                 | 0                     | 0              |
| `dsb_hotel`                               | **NO**        | -             | -                 | -                     | -              |
| `app_constraints_referential_integrity`   | **YES**       | 0             | 2;1               | 1                     | 0              |
| `app_constraints_specialization`          | **YES**       | 0             | 2;3               | 0                     | 1              |

## Structure

The toolkit takes as input applications in the `examples` folder from the [blueprint](https://github.com/mafaldacf/blueprint) git module forked from the original repository.

The representation of the application and the abstract graph are saved in the `assets` folder in JSON format.

The source code is located in the `pkg` folder, divided into the following modules: `abstractgraph`, `app`, `controlflow`, `frameworks`, `logger`, `service`, `types`, `utils`.

| Module                 | Description                                                                                                                                                                                                                                            |
| ---------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
|                        |                                                                                                                                                                                                                                                        |
| **Application**        | Initializes the application and registers **service nodes** and **database instances** with the application spec generated by Blueprint                                                                                                                |
| **Frameworks**         | Contains utilities specific to each framework. In the context of Blueprint, it contains (i) helper functions to compute the service spec from Intermediate Representation (IR), and (ii) methods that define backends like databases and queues        |
| **Service**            | Parses the **abstract syntax tree (ast)** of each service, capturing all service, database, or even internal calls within each exposed method                                                                                                          |
| **Control Flow Graph** | Parses the **control flow graph (cfg)** of each service, capturing all dependencies in declared and assigned variables within each exposed method block from service, database, or internal calls                                                      |
| **Abstract Graph**     | Generates the final abstract graph containing nodes (**abstract service calls** or **abstract database calls**) and edges representing the relationship and order between service and database calls, including queue handlers triggered by publishers |
