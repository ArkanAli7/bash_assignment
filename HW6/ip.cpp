
#include "ip.h"
#include "string.h"
#include <iostream>
#include <stddef.h>
#include <math.h>
const int MAXIMUM_IP = 256; //  defining consts
const int BITS_NUM= 32;
const int DOTS_SIZE= 3;
const int SLASH_SIZE= 1;
const int MINUS_ONE =-1;
const int FIRST_8= 8;
const int ALL =32;
const int FAIL= 0;
const int SUCCESS= 1;
const int RULES_LENGTH= 4 ;
const int TWO= 2 ;

int remove_dc_helper(int synonymous_bits,int number)
{
    int temp1 = number, temp2=(FIRST_8-synonymous_bits), i=0; 
    while (i < temp2)
     {
        temp1 = temp1/TWO;
        i++;
    }
    return temp1;
}

ip::ip(String s) : ip_mask(s)
{
    for(int i=0; i<RULES_LENGTH; i++)// inaitializing the array to 0
    {                                 //the_bits and ip_mask to 0
    
        this->rule_array[i] = MINUS_ONE;
        
    }
    
    this->the_bits = 0;
}

bool ip::match(String pack) // match function which use our helperfunction
{

 
 bool value = false;
 size_t size;
 String *arr;

 pack.split("=, ", &arr, &size); //splitting
 
  if(size==0)
  { 
  delete[] arr;
  return false;
  
  }
  
 for(size_t j = 0; j < size; j=j+2)
 {

  if(ip_mask.equals(arr[j]))
  {
   value = helper_function(arr[j+1]);
       break;
   }
 }
   delete[] arr;
   return value;
 }


bool ip::set_value(String val)
{
    char delimeter1[] = ".";  //defining the delimeters
    
    char delimeter2[] = "/";
   
    String *s_slash;
    
     String *s_dot;

    size_t dots = DOTS_SIZE;
    
    size_t slashes = SLASH_SIZE;
    

    val.split(delimeter1 , &s_dot , &dots);  // splitting
    val.split(delimeter2 , &s_slash , &slashes);
    

                //here we checks number is valid.
    for (int i=0;i<(int)dots;  ++i ) 
    {
        if(s_dot[i].to_integer() > MAXIMUM_IP || s_dot[i].to_integer() < 0)
        
        {
        delete []s_dot;
        delete []s_slash;
            return FAIL;     //fails
        }

    }
                //here we checks after slash
    if(s_slash[1].to_integer() > BITS_NUM || s_slash[1].to_integer() < 0)
    {
        delete [] s_dot;
        delete [] s_slash;
        return FAIL;
    }

    this->the_bits = s_slash[1].to_integer();
    
    if((this->the_bits <= ALL) && (this->the_bits>=0))
    
    {
        for(int j=0 ; j<(int)dots ; j++)
        
        {
            this->rule_array[j] = s_dot[j].to_integer();
            
        }
    }
    
    delete [] s_dot;
    delete [] s_slash;
    return SUCCESS; //return that we have succeed

}


bool ip::helper_function(String val) 

{

    int j = 0, i=0; // for loops indexes
    
    int  synonymous_bits = this->the_bits;
    
    char delimeter1[] = "."; // defining delimeters
    
    String *s_dot;
    
    val=val.trim();
    
	int temp[RULES_LENGTH];
	
	while(i<RULES_LENGTH) // going over rules and setting in temp
	{
	temp[i] = this->rule_array[i];
	i++;
	}
	
    size_t dots = DOTS_SIZE;
    
    val.split(delimeter1, &s_dot, &dots); //splitting
    
    
    
    if(synonymous_bits == 0)
    {
    delete[] s_dot;
        return SUCCESS;
    }
   
  
    while (synonymous_bits>0)
    
    {
     if(s_dot[j].to_integer() != this->rule_array[j] 
     && synonymous_bits >= FIRST_8)
     {
     delete[] s_dot;
            return FAIL;
            
     }
     
        if( ((remove_dc_helper(synonymous_bits,s_dot[j].to_integer()))
            != (remove_dc_helper(synonymous_bits,temp[j]))) 
             &&  (synonymous_bits<FIRST_8))
            {
            delete[] s_dot;
            return FAIL;
            
            }
            
        synonymous_bits = (synonymous_bits - FIRST_8);
        j++;
    }
   delete[] s_dot;
    return SUCCESS;
}



