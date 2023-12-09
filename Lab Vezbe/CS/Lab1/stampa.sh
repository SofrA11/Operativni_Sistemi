if test "$#" -ne "1"
then 
    echo "Broj argumenata nije odgovarajuci"
else
	if test -f $1
        then
            cat $1
        elif test -d $1
        then 
            cd $1;ls -al
        else
            echo "Nije ni datoteka ni direktorijum"
        fi
fi
