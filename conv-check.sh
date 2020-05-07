# compile
echo "compile"
./compile-all.sh

echo "T"
./tconv in=test.t -FT > tmp.tcnv.T
./tq.o in=test.t -FT -Pin > tmp.tq.T
diff tmp.tcnv.T tmp.tq.T

echo "S"
./tconv in=test.t -FS > tmp.tcnv.S
./tq.o in=test.t -FS -Pin > tmp.tq.S
diff tmp.tcnv.S tmp.tq.S

echo "J"
./tconv in=test.t -FJ > tmp.tcnv.J
./tq.o in=test.t -FJ -Pin > tmp.tq.J
diff tmp.tcnv.J tmp.tq.J

echo "W"
./tconv in=test.t -FW > tmp.tcnv.W
./tq.o in=test.t -FW -Pin > tmp.tq.W
diff tmp.tcnv.W tmp.tq.W

echo "C"
./tconv in=test.t -FC > tmp.tcnv.C
./tq.o in=test.t -FC -Pin > tmp.tq.C
diff tmp.tcnv.C tmp.tq.C

echo "N"
./tconv in=test.t -FN > tmp.tcnv.N
./tq.o in=test.t -FN -Pin > tmp.tq.N
diff tmp.tcnv.N tmp.tq.N

echo "H"
./tconv in=test.t -Fh > tmp.tcnv.H
./tq.o in=test.t -Fh -FT -Pin > tmp.tq.H
diff tmp.tcnv.H tmp.tq.H


