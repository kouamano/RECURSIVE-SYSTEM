for fl in `ls *.c`; do echo $fl; gcc $fl -I../../include -lm  -o ./bin/${fl%.c}; done
for fl in `ls *.pl`; do cp $fl ./bin/; done
