#! /bin/bash

wget https://www.ynetnews.com/category/3082



results=`grep -Eo "https://www.ynetnews.com/article/[a-zA-Z0-9]+" 3082 | sort | uniq` #taking all the relative links without repeats

wget -iO $results   #make a file for all the linkes

num=$(echo "$results" | wc -w)  #counting the linkes number
arr=($results)                
echo "$num" >> results.csv
for (( i=0; i<num; ++i)); do   #searching for all the 4 names in the linkes 
filename=$(echo ${arr[i]} | grep -o '[^/]\+$') 
netanyahunum=$(grep -o "Netanyahu" "$filename"| wc -w)
lapidnum=$(grep -o "Lapid" "$filename"| wc -w)
Bengvirnum=$(grep -o "Ben-Gvir" "$filename"| wc -w)
gantznum=$(grep -o "Gantz" "$filename"| wc -w)
if (( (( $netanyahunum==0 )) && (( $lapidnum==0 )) && (( $Bengvirnum==0 )) && (( $gantznum==0 )) )); then
echo ${arr[i]}", -" >> results.csv
else

echo ${arr[i]}, "Netanyahu,"" $netanyahunum"", Gantz,"" $gantznum"", Lapid,"" $lapidnum"", Ben-gvir,"" $Bengvirnum" >> results.csv

fi

done
