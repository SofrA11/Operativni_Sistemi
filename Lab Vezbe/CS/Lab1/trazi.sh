for fname in $1*
do
  cat $fname | grep $2 > /dev/null
  if test $? -eq 0; then
     echo Datoteka $fname sadrzi $2
  else
     echo Datoteka $fname ne sadrzi $2
  fi
done
 

