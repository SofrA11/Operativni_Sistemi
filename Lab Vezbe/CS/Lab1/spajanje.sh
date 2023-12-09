read datoteka
while test "$datoteka" != "KRAJ"
do
    if test -f $datoteka
    then
        cat $datoteka >> ./spoj.dat
    else
        echo "Uneto ime ne predstavlja datoteku"
    fi
    read datoteka
done
