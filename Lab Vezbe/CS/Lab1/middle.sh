if [ "$#" -ne "3" ]
then
    echo "Broj argumenata nije odgovarajuci"
elif [ ! -f $3 ]
then
    echo "Morate kao argument zadati datoteku"
else
   tail -n+$1 $3 | head -n$(($2-$1+1))
fi 
  
