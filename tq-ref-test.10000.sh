for i in {1..10000}
do
	#read -p "Hit Enter: "
	echo '($#3,#3)' | ./tq.o in=/dev/stdin -FT -Pin
done
