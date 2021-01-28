gcc cts.c -o cts
gcc cst.c -o cst
gcc tconv.c -o tconv
gcc toPsdJSIN.c -o toPsdJSIN
gcc -Wall -O2 -march=native tq.c -o tq.o
gcc -Wall -g -O0 c_tq.c -o c_tq.o
gcc -Wall -O2 c_tq.c -o cq.o
#sudo install tq.o /usr/local/bin/tq
