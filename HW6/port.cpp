
#include "port.h"
#include "string.h"
#include <iostream>
#include <stddef.h>
const int MAXIMUM_PORT =  65535; //defining consts
const int ARR_LENGTH =2;
const int FAIL= 0;
const int SUCCESS =1;
const int ONE =1;
// inaitializing the array to 0
Port ::Port(String s) : port_mask(s) 
{
    rule_array[0] = 0;
    rule_array[1] = 0;
}


bool Port::match( String pack) //match function 
{

 size_t length; 
 
 bool value = false;
 
 String *arr;
// splitting by delimeters
 pack.split("=, ", &arr, &length); 
 
  if(!length)    // checking length correctness
  { 
  delete[] arr;
  return false;
  }
  
 for(size_t j = 0; j < length; j=j+2 )
 {

  if(port_mask.equals(arr[j]))
  {
  
   value = helper_function(arr[j+1]);
       break;
  }
  
 }
  delete[] arr;
   return value;
 }



bool Port::set_value(String val)
{
	
    char delimiters[ONE]={'-'};
    
    String *strings_array;
    
    size_t array_len = 0;
// splitting by delimeters
    val.split(delimiters,&strings_array,&array_len); 
    

    if((int)array_len != ARR_LENGTH)
    {
       delete[] strings_array;
        return FAIL;
    }

// here we check if there are problems in the data
    for (int j = 0; j < (int)array_len ; ++j)
                                             
    {
        if(strings_array[j].to_integer() >= 0 || 
        strings_array[j].to_integer() <= MAXIMUM_PORT)
        {
            rule_array[j] = strings_array[j].to_integer();
        }
        else
        {
        delete[] strings_array;
            return FAIL;
        }
    }
	delete[] strings_array;
    return SUCCESS;
}


// helper function for match function
bool Port::helper_function(String val) 
{  
	
    
    int ports_num = (val.trim()).to_integer();
    
   
   

    if((rule_array[0]<=ports_num) && (rule_array[ONE]>=ports_num))
    {
        return SUCCESS;
    }
    
    else
    {
        return FAIL;
    }
}
