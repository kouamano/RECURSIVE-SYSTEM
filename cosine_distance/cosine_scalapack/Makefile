CC = mpifcc
CFLAGS = -Kfast -SSL2 -SCALAPACK
PROGRAM = cosdist

all:	$(PROGRAM)

$(PROGRAM): cosdist.c
	$(CC) $(CFLAGS) -o $(PROGRAM) $<

clean:
	rm -f *~ $(PROGRAM)
