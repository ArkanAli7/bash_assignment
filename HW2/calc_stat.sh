#! /bin/bash
if [[ ! $# -eq 1 ]];
then
         echo "Wrong number of arguments" >&2
         exit 1
 else
      courseNum=$1
      if [[ ! -e $courseNum.txt ]];
       then
        echo "Course not found" >&2
         exit 1
      else    
        
         if [[ -d ~/$courseNum"_stat" ]];  
      then
         rm -r $courseNum"_stat"
         fi
         fi
         mkdir $courseNum"_stat"
     fi
      
     
 
gcc hist.c -o hist.exe
gcc min.c -o min.exe
gcc max.c -o max.exe
gcc mean.c -o mean.exe
gcc median.c -o median.exe
cat "$courseNum.txt" | ./hist.exe - -n_bins 10 > $courseNum"_stat"/histogram.txt
cat "$courseNum.txt" | ./mean.exe >> $courseNum"_stat"/statistics.txt
cat "$courseNum.txt" | ./median.exe >> $courseNum"_stat"/statistics.txt
cat "$courseNum.txt" | ./min.exe >> $courseNum"_stat"/statistics.txt
cat "$courseNum.txt" | ./max.exe >> $courseNum"_stat"/statistics.txt
x=$(cat $courseNum"_stat"/histogram.txt)
arr=($x)                   #building a array from the histogram 
                            #and taking the passing students from all students
arrlen=$(echo ${#arr[@]})
for(( i=1; i<arrlen; i=i+2 )); do
p=${arr[i]}
(( sum=sum+p ))
done
for(( i=1; i<arrlen/2; i=i+2 )); do
t=${arr[i]}
(( f=f+t ))
done
(( u=(f*100)/sum ))
echo $u"%" >> $courseNum"_stat"/statistics.txt
