
#include "string.h"
#include <stddef.h>
#include <iostream>
#include <stdio.h>
#include <string.h>


const int  SUCCESS = 1;
const int  ONE = 1;
const int  FAIL = 0;
const int  MINUS_ONE = -1;



String ::String()
{
    data = new char[ONE];
    data[0] = '\0';
    length = ONE;
}

// in case of receiving class of type String
String ::String(const String &str)
{
    length = str.length;
    data = new char[length];
    strcpy(data,str.data);
    data[length-ONE] = '\0';
}

// in case of receiving string 
String ::String(const char *str)
{
    length = strlen(str)+ONE;
    data = new char[length];
    strcpy(data,str);
    data[length-ONE] = '\0';
}

String ::~String()
{
    delete[] this-> data;
}


// operator=() on class of type String

String &String::operator=(const String &rhs)
{
    if(this == &rhs)
    {
        return *this;
    }

    delete [] data;
    
    char* copied_string = new char[rhs.length];
    strcpy(copied_string,rhs.data);
    copied_string[rhs.length-ONE] = '\0';
    
    this-> data = copied_string;
    this-> length = rhs.length;
    
    return *this;
}

// operator=() on string 
String &String::operator=(const char *str)
{
    delete [] data;
    this-> length = strlen(str)+ONE;
    
    char* copied_string = new char[length];
    strcpy(copied_string,str);
    copied_string[length-ONE] = '\0';
    
    this-> data = copied_string;
    return *this;
}






// equal function on classes of type String
bool String::equals(const String &rhs) const{

    if(this-> length == rhs.length)
    {
    
        for(int i=0; i<(int)this->length; ++i)
        {
            if(this-> data[i] != rhs.data[i])
            {
                return FAIL;
            }
        }
        
        return SUCCESS; // size and data are the same.
        
    }
    return FAIL;
}

// equal function strings
bool String::equals(const char *rhs) const{

    if(this-> length == strlen(rhs)+1)
    {
    	
        for(int i=0; i<(int)this-> length; ++i)
        {
            if(this-> data[i] != rhs[i])
            {
                return FAIL;
            }
        }
        return SUCCESS;
        
    }
    return FAIL;
}

// This is a help function that we will use in the split func.

void copy_String(int begin,int end,char* curr_string,
String **output_strs,int m){

    int i = begin + ONE;       
    int n = 0;
    char str_part[end - begin];
        
    while(i < end)
    {
        str_part[n] = curr_string[i];
        i++;
        n++;
        
    }
    
    str_part[n] ='\0';
    (*output_strs)[m]=String(str_part);
    return;
}


// splitting the original string 
void String::split(const char *delimiters, 
String **output, size_t *size) const{

    if(delimiters == NULL || size == NULL)
        return;
    
            
    if(this-> data == NULL)
    {
        output = NULL;
        *size = 0;
        
        return;
    }
    
    int length = ((int)this-> length); // length of this string
    int tot_delims = ((int)strlen(delimiters)); 
    int delim_num_string = 0; //number of delimeters in string
    
    
    //we'll use this loop to get delim_num_string
    for(int k=0; k < (length); k++)
    {
        for (int i=0; i < tot_delims; i++)
        {
            if(this-> data[k] == delimiters[i])
            {
                delim_num_string++;                
            }
        }
    }
    
    
    if(output == NULL)
    {
        *size = delim_num_string + ONE;
        
        return;
    }
   
    *output = new String[delim_num_string+1];
    int lastof_delims = MINUS_ONE;
    int delim = 0;
    
    //filling output with strings before the delimiters.
    for(int this_word=0; this_word <(length); this_word++)
    {
        for(int this_delim=0; this_delim < tot_delims; this_delim++)
        {
            if(this-> data[this_word] == delimiters[this_delim])
            {
            
                copy_String(lastof_delims, this_word
                ,this-> data, output, delim);
                
                lastof_delims = this_word;
                delim++;
                
            }
        }
    }
    
    
    //fills the last place in output- after the last delim -
    copy_String(lastof_delims, length,
    this-> data , output, delim);
    
    *size = delim_num_string + ONE;
    
    return;
}





int String::to_integer() const{

    return atoi(this-> data);
    
}



// trimming the string according to the delim
String String::trim() const{

    String string_cleaned;    
    string_cleaned = String(this-> data);
    
    for(int i=0; i<(int)this->length; ++i)
    {
        if(string_cleaned.data[i] == ' ')
        {
            for (int m=i,n=i+ONE ; n < (int)this->length; ++n,++m) 
            {
                string_cleaned.data[m] = string_cleaned.data[n];
            }
            
            string_cleaned.length = string_cleaned.length - ONE;
            i=i-ONE;
        }
    }
    
    return string_cleaned;
}








