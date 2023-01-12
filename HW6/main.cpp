#include <iostream>
#include "port.h"
#include "ip.h"
#include "input.h"
#include "string.h"
const int MINUS_ONE = -1;
const int ONE =1;
const int DEL_SIZE =2;

 
int main(int argc, char ** argv)
{

    if(check_args(argc,argv))
    {
        return MINUS_ONE;
     }

	String temp = String(argv[ONE]);
	
	String argv_trim = String();
	
	argv_trim = temp.trim();

    char delimiters[DEL_SIZE]={'=',','};
    String *array_of_fields;
    size_t arr_len =0;

    argv_trim .split(delimiters,&array_of_fields,&arr_len);
    //making 4 object of class "String"
    
    String src_port("src-port"); 
    String dst_port("dst-port");
    String src_ip("src-ip");
    String dst_ip("dst-ip");
    
    
    
    
    
   
    if(array_of_fields[0].equals(src_port)) //checks if its src_port
    {
    	
    	Port src_portp(src_port); //making port object and sending mask
    	
        src_portp.set_value(array_of_fields[ONE]);
        
        parse_input(src_portp);
        
    }
 
    if(array_of_fields[0].equals(src_ip))//checks if its src_ip
    {
    	
    	ip src_ipi(src_ip);//making ip object and sending mask
    	
        src_ipi.set_value(array_of_fields[ONE]);
        
        parse_input(src_ipi);
        
    }
    
    

     
    if(array_of_fields[0].equals(dst_ip))//checks if its dst_ip
    {
    	
    	ip dst_ipi(dst_ip);//making ip object and sending mask
    	
        dst_ipi.set_value(array_of_fields[ONE]);
        
        parse_input(dst_ipi);
        
    }
    
    if(array_of_fields[0].equals(dst_port))//checks if its dst_port
    {
    	
    	Port dst_portp(dst_port);//making port object and sending mask
    	
        dst_portp.set_value(array_of_fields[ONE]);
        
        parse_input(dst_portp);
        
    }
    //free the memory we have allocated in splitt function

    delete[] array_of_fields; 


    

    return 0;
}
