
case $# in 
2 | 4 | 6 | 8)
	while test $# -ne 0 
	do
		if test -r $1 
		then
			cp $1 $2
			echo "$2 kreirana" 
		else
			echo "$1 ne postoji" 
		fi
		shift 2 
	done;; 
1 | 3 | 5 | 7)
	echo "neparan broj argumenata";; 
0)
	echo "nema argumenata";;
esac