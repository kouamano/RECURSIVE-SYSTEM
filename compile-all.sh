gcc cts.c -o cts
gcc cst.c -o cst
gcc cjt.c -o cjt
gcc iq.c -o iq
gcc tconv.c -o tconv
gcc -Wall -O2 -march=native tq.c -o tq.o
gcc -Wall -g -O0 c_tq.c -o c_tq.o
gcc -Wall -O2 c_tq.c -o cq.o
./compile-x.sh
#sudo install tq.o /usr/local/bin/tq
