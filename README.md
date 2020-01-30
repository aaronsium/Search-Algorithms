# ex4

EX4 implement different search algorithms.
we can compare and chose the best one for certain client.

## Usage

```
include all files in "EX4" create in main wanted search implement (algorithm) and run main.
```

## API

#### server_side

Type: `Interface`

classes that implements server_side open's server and 
thread's which in them we will handel different clients.

#### ClientHandler

Type: `Interface`

classes that implements ClientHandler handel certain client's in the suitable way.

#### Solver

Type: `Interface`

classes that implements Solver receive problem of template type and solve it and return solution of also template type.

#### CacheManager 

Type: `Interface`

classes that implements CacheManager receive both problem and it solution and store it so we can
get by o(1) solutions to problems we already had deal with.

#### State
Type: `object`

holds the position we got into in algorithm. 
Starting from the Initial state all the way to the goal state, every State describes every step.  

#### algorithms

Type: `search object`

- `AStar`, `BestFirstSearch` : receive a searchable implemention, finds the path with
                               the lowest cost and returns it.
            
- `BFS`, `DFS`: receive a searchable implemention, finds the shortest path and returns it.
                

## Github

[pageres-cli](https://github.com/aaronsium/ex3)