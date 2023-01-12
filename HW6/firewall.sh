#! /bin/bash

data_in=$(cat /dev/stdin | sed -e 's/#.*//' | tr -d ' ')


while read line #going over all the rules lines

do
	#removing spaces and "," to put all the line rules in an array
    rules=$(echo "$line" | tr -d ',' | tr -d ' ' | sed -e 's/#.*//' | 
	sed -e 's/src-port/   src-port/g' | sed -e 's/dst/   dst/g')
	 
	 if [[ "$rules" != "" ]]; then
	 #building the array of 4 rules (for maximum)
	rules_array=($rules)
	
	rule1=${rules_array[0]}
	rule2=${rules_array[1]}
	rule3=${rules_array[2]}
	rule4=${rules_array[3]}
  #piping into our c++ project to set the result in output
		output+=$(echo "$data_in" | 
		./firewall.exe $rule1 | 
		./firewall.exe $rule2 |
		./firewall.exe $rule3 | 
		./firewall.exe $rule4 )
		 
		output+="\n"
		
	fi

#redirection
done < "$1"
#printing the results
echo -e "$output" | sed "s/src-ip/\n&/g" | sed '/^$/d' | sort | uniq
