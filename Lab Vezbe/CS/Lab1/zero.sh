if [ "$#" -ne "1" ]
then
    echo "Broj argumenata nije odgovarajuci"
else
   for f in $( locate $1 )
   do
       [ -f $f ] && [ -s $f ] || echo $f
   done
fi 

