#! /bin/bash
if [[ ! $# -eq 1 ]];
then
         echo "Wrong number of arguments" >&2
         exit 1
 else
      cNum=$1
      if [[ ! -e $cNum.txt ]];
       then
        echo "Course not found" >&2
         exit 1
      else    
        
         if [[ -d $cNum"_stat" ]];  
      then
         rm -r $cNum"_stat"
         fi
         fi
       mkdir $cNum"_stat"
     fi  
      
     #cNUM is the course number
 
gcc -g -Wall hist.c -o hist.exe
gcc -g -Wall min.c -o min.exe
gcc -g -Wall max.c -o max.exe
gcc -g -Wall mean.c -o mean.exe
gcc -g -Wall median.c -o median.exe
cat "$cNum.txt" | ./hist.exe - -n_bins 10 > $cNum"_stat"/histogram.txt
cat "$cNum.txt" | ./mean.exe >> $cNum"_stat"/statistics.txt
cat "$cNum.txt" | ./median.exe >> $cNum"_stat"/statistics.txt
cat "$cNum.txt" | ./min.exe >> $cNum"_stat"/statistics.txt
cat "$cNum.txt" | ./max.exe >> $cNum"_stat"/statistics.txt
x=$(cat "$cNum.txt" | ./hist.exe - -n_bins 100)
arr=($x)             #building a array from the histogram 
                     #and taking the passing students from all students
arrlen=$(echo ${#arr[@]})
for(( i=1; i<arrlen; i=i+2 )); do
students_with_gradei=${arr[i]}
(( sum1=sum1+students_with_gradei ))
done
for(( i=1; i<110; i=i+2 )); do
failed_with_gradei=${arr[i]}
(( sum2=sum2+failed_with_gradei ))
done
#checking if there is no students or we have invalid input to not /0
if [[ ! $sum1 -eq 0 ]];
then
(( the_percent=(sum2*100)/sum1 ))
echo $the_percent"%" >> $cNum"_stat"/statistics.txt
fi
