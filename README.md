# tq
A tree/graph description language.
- Tree expression: can descrive tree.    
    0(1(2, ... ))
- Implicit expression: can describe graph.    
    V(V, ... )
    - Linkage: #1V1(V2($#1)): V1<->V2.    
- Explicit expression: can describe homoginized-graph.    
    E(V, ... )    
    - Linkage: #1E1(E2($#1)): E1 = hyperedge involving E2, E2 = hyperedge involving E1.

## License
GPL    

## Developer
developed by NIMS,
written by K. Amano and K. Sakamoto.

## Compile
```
./compile-all.sh
```

```
cd DimensionDefinitionLanguage
./compile_checker.sh
```
## Example
README.exam

## Performance
### huge tree performance (1): 3m37sec; 106G mem
time numactl --localalloc ./tq.o buff=30 in=lllarge4-single-test.t    
498615417 Nodes were operated.

### large tree performance (2): 0m46sec; 26G mem 
time numactl --localalloc ./tq.o buff=30 in=lllarge-single-test.t    
124653854 Nodes were operated.

### large tree performance (2) vs jq:  2m30sec; 36G mem
time cat lllarge-single-test.json | numactl --localalloc jq . > /dev/null


