for fl in `ls *.c`; do echo $fl; gcc $fl -I../../include -lm  -o ./bin/${fl%.c}; done
