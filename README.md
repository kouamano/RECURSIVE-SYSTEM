# tq
A tree/graph description language.
- Tree expression: can descrive tree.    
    0(1(2, ... ))
- Implicit graph expression: can describe graph with reference.    
    #0V0(V1($#0)): V0<->V1.    
- Explicit graph expression: can describe homoginized-graph with reference.    
    #0E0(E1($#0)): E0 = hyperedge involving E0, E1 = hyperedge involving E0.

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


