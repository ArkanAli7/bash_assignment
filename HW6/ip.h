
#ifndef IP_H
#define IP_H
#include "generic-field.h"
#include "string.h"
const int IP_LEN =4;

class ip : public GenericField
{
    int rule_array[IP_LEN];
    int the_bits;
    String ip_mask;
    bool helper_function(String val);
    
public:

    ip(String s);
    bool match(String pack);
    bool set_value(String val);
    
};

#endif
