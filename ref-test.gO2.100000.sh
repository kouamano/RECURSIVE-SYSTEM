for i in {0..100000}
do
	#read -p "Hit Enter: "
	echo '($#3,#3)' | ./a.out.gO2 in=/dev/stdin -FT -Pin
done
