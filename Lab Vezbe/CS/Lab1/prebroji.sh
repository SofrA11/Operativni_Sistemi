if [ "$#" -ne "1" ]
then
    echo "Broj argumenata nije odgovarajuci"
elif [ ! -d $1 ]
then
    echo "Morate zadati ime direktorijuma"
else
   cd $1
   count=0
   for f in *
   do
       if [ -f $f ]
       then
           if [ -s $f ]
           then 
               count=$((count+1))
           fi
       fi
   done
   echo "Broj datoteka koje su vece od 0B je $count"
fi 
