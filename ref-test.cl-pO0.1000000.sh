for i in {0..1000000}
do
	#read -p "Hit Enter: "
	echo '($#3,#3)' | ./cl.out.pO0 in=/dev/stdin -FT -Pin
done
