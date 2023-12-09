echo Unesite ekstenziju:
read ext
if test -f "./headers"
then
  rm headers
 fi
for fname in "$1/*.$ext"
do
  echo Dodajem prve dve linije datoteke $fname
  head -2 $fname >> headers
done 

