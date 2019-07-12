cd /home/kamano/gitsrc/utility/algebra+graph
for fl in `ls *.c`; do gcc $fl -I../../include -lm  -o bin/${fl%.c}; done
