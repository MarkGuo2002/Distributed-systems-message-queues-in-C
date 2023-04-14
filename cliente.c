#include "claves.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char TESTLEN[270] = "dwovhcatbhabtxdtvunblubfuwezwtscgtppxuxnyrvshrofwysrxglndputtzlkxrrillmlnjncwvppqyditqxbovchacrkapzvzfuhddbhdubmwyywhtmfjjpgaaoddzcwmkuxnhioejlraamhjyhxedetnfshdbztxlheunrscqpmtwfguyrfrcbhiccetdcwiwqyqdhohoudvwxyvvxeisbuegfjdzkxbqjioqbcpvudmnkutjjjqwbankizasomqquokdlui";

int main(){
    char c_value1[MAX];
    int c_value2;
    double c_value3;
    
    printf("result init() = %d\n\n", init());
    
    printf("Hello after init from client\n\n");
    
    //insert normal data
    printf("result setvalue(normal) = %d\n\n",set_value(1, "hi", 9, 3.9));
    printf("result setvalue(normal) = %d\n\n",set_value(2, "hasdasdasda", 3, 6.30000));
    printf("result setvalue(alrdy existing key) = %d\n\n",set_value(2, "YU)/)&NAOOU98765", 6, 12.5));
    printf("result setvalue(Normal) = %d\n\n",set_value(3, "dd", 12, 5.2));
    //set value of len > 256
    printf("result setvalue(>256) = %d\n\n",set_value(4, TESTLEN, 1, 14.5));
    
    printf("result getvalue(key = 1) = %d\n\n",get_value(1, c_value1, &c_value2, &c_value3));
    printf("Value1: %s\nValue2: %d\nValue3: %f\n\n", c_value1, c_value2, c_value3);
    printf("result get_value(key does not exist) = %d\n\n", get_value(5, c_value1, &c_value2, &c_value3));
    printf("Value1: %s\nValue2: %d\nValue3: %f\n\n", c_value1, c_value2, c_value3);
    
    printf("result modify_value(key does exist) = %d\n\n", modify_value(2, "moyingPlays", 2, 14.5));
    printf("result modify_value(key does not exist) = %d\n\n", modify_value(7, "moyingPlays", 2, 14.5));
    
    printf("result delete_key(key does exist) = %d\n\n", delete_key(2));
    printf("result delete_key(key does not exist) = %d\n\n", delete_key(7));
    
    printf("result exist(key does exist) = %d\n\n", exist(3));
    printf("result exits(key does not exist) = %d\n\n", exist(7));
   
    //case key1 does not exist returns -1
    printf("result copy_key(key1 does not exist) = %d\n\n", copy_key(7, 8));
    //case key2 does not exist, it's created with the same values as key1
    printf("result copy_key(key2 does not exist) = %d\n\n", copy_key(1, 8));
    //case key2 does exist, it's modified with the same values as key1
    printf("result copy_key(key1 and key2 do exist) = %d\n\n", copy_key(1, 3));
    
    printf("result init() = %d\n\n", init());  
   
   /*
    printf("result init() = %d\n", init());
    
    
    //MODIFY_VALUE
    //case key does exist
    //case key does not exist
    
    //DELETE_KEY
    //case key does exist
    //case key does not exist
    
    //EXISTS
    //case key does exist
    //case key does not exist
    
    //COPY_KEY
    //case key1 does not exist returns -1
    printf("result copy_key(key1 does not exist) = %d\n\n", copy_key(7, 8));
    //case key2 does not exist, it's created with the same values as key1
    printf("result copy_key(key2 does not exist) = %d\n\n", copy_key(1, 8));
    //case key2 does exist, it's modified with the same values as key1
    printf("result copy_key(key1 and key2 do exist) = %d\n\n", copy_key(1, 3));
    
    printf("result init() = %d\n\n", init());
*/
return 0;
}