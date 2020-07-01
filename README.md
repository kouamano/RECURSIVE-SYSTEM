# tq
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

### large tree performance (2): 1m18sec; 41G mem 
time ./tq.o in=lllarge-single-test_double.t buff=30
249307706 Nodes were operated.

### large tree performance (3): 2m33sec; 56G mem
time ./tq.o in=lllarge-single-test_double.t buff=30 -Pin -FJ > lllarge-single-test_double.json

### large tree performance (3) vs jq:  4m43sec; 72G mem
time cat lllarge-single-test_double.json | jq . > /dev/null


