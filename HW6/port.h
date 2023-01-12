#ifndef PORT_H
#define PORT_H

#include "string.h"
#include "generic-field.h"
const int LENGTH =2;


class Port : public  GenericField
{

    String port_mask;
    bool helper_function(String val);
    
public:

   
    int rule_array[LENGTH];
    Port(String s);
    
    bool match(String pack);
    
    bool set_value(String val);
    
};

#endif
