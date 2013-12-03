CC = cc
CFLAGS = -pc -blas
PROGRAM = cosdist

all:	$(PROGRAM)

$(PROGRAM): cosdist.c
	$(CC) $(CFLAGS) -o $(PROGRAM) $<

clean:
	rm -f *.o *~ $(PROGRAM)
