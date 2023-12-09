if [ "$#" -ne "1" ]
then
    echo "Broj argumenata nije odgovarajuci"
elif [ ! -d $1 ]
then
    echo "Morate kao argument zadatu direktorijum"
else
   if [ ! -d $1/KOPIJA ]
   then
       mkdir $1/KOPIJA
   fi
   cd $1
   for f in *.c
   do
       echo $f
       cp  $f ./KOPIJA/$f.bak
   done 
fi 
  
