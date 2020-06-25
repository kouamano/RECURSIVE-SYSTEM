# tq
## License
GPL    
developed by K. Amano and K. Sakamoto @ NIMS

## compile
```
./compile-all.sh
```

```
cd DimensionDefinitionLanguage
./compile_checker.sh
```
## 使用例
README.exam

## performance
### large tree performance (2) ; 1m18sec; 41G mem 
time ./tq.o in=lllarge-single-test_double.t buff=30
249307706 Nodes were operated.

### large tree performance (3) ; 1m47sec; 41G mem 
time ./tq.o in=lllarge-single-test_double.t buff=30 -FT -Pin > /dev/null

### large tree performance (4) ; 2m33sec; 56G mem
time ./tq.o in=lllarge-single-test_double.t buff=30 -Pin -FJ > lllarge-single-test_double.json

### large tree performance (4) vs jq ; 4m43sec; 72G mem
time cat lllarge-single-test_double.json | jq . > /dev/null

### large-large tree performance (1): 2m37sec; 83G mem
time tq.o in=lllarge-single-test_dd.t buff=30
498615410 Nodes were operated.

### time: 80 sec.; mem in use:640Byte
time ./tq.o in=lllarge-test.t

### time: 55 sec.; mem in use:612Byte
time ./tq.o in=lllarge-test.t

### time: 1m 24sec.; mem in use:560Byte
time ./tq.o in=lllarge-test.t Sp=0,1

### time: 1m43sec.; mem in use:560Byte
time ./tq.o in=lllarge-test.t -FS > /dev/null

### time: 14 sec.; mem in use:520Byte
time ./tq.o in=llarge-test.t

### time: 20 sec. ; mem in use:570Byte
time ./tq.o in=llarge-test.t -FT > /dev/null

### time: 20 sec. ; mem in use:570Byte
time ./tq.o in=llarge-test.t -FN > /dev/null

### time: 75 sec. ; mem: 89G. @ N007 ; 13M nodes
time ./tq.o in=llarge-single-test.t -FT it=single > /dev/null

### 参考 jq 80 sec. ; mem: 17G @ N007 ; 11M nodes
time cat llarge-single-test.t.j | jq . > tmp.json

### 参考 mathematica 20 sec. ; mem: 4G
js=Import["llarge-test-single.t.j","JSON"];


