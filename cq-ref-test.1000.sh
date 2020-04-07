for i in {0..1000}
do
	#read -p "Hit Enter: "
	echo '($#3,#3)' | ./cq.o in=/dev/stdin -FT -Fst -Pin
done
