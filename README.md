# tq
A graph description language.

- Implicit expression: can describe graph.    
    V(V, ... )
- Explicit expression: can describe homoginized-graph.    
    E(V, ... )

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


