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
### huge tree performance (1): 2m37sec; 83G mem
time tq.o in=lllarge-single-test_dd.t buff=30
498615410 Nodes were operated.

### large tree performance (2): 1m18sec; 41G mem 
time ./tq.o in=lllarge-single-test_double.t buff=30
249307706 Nodes were operated.

### large tree performance (3): 1m47sec; 41G mem 
time ./tq.o in=lllarge-single-test_double.t buff=30 -FT -Pin > /dev/null

### large tree performance (4): 2m33sec; 56G mem
time ./tq.o in=lllarge-single-test_double.t buff=30 -Pin -FJ > lllarge-single-test_double.json

### large tree performance (4) vs jq:  4m43sec; 72G mem
time cat lllarge-single-test_double.json | jq . > /dev/null


