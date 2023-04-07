#include "claves.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char TESTLEN[270] = "dwovhcatbhabtxdtvunblubfuwezwtscgtppxuxnyrvshrofwysrxglndputtzlkxrrillmlnjncwvppqyditqxbovchacrkapzvzfuhddbhdubmwyywhtmfjjpgaaoddzcwmkuxnhioejlraamhjyhxedetnfshdbztxlheunrscqpmtwfguyrfrcbhiccetdcwiwqyqdhohoudvwxyvvxeisbuegfjdzkxbqjioqbcpvudmnkutjjjqwbankizasomqquokdlui";

int main(){
    char c_value1[MAX];
    int c_value2;
    double c_value3;
    
    printf("result init() = %d\n", init());
    
   /*
    printf("Hello after init from client\n");
    //insert normal data
    printf("result setvalue(normal) = %d\n",set_value(1, "hi", 9, 3.9));
    printf("result setvalue(normal) = %d\n",set_value(2, "Krystal", 6, 12.5));
    printf("result setvalue(Normal) = %d\n",set_value(3, "Yeah", 12, 5.2));
    //set value of len > 256
    printf("result setvalue(>256) = %d\n",set_value(4, TESTLEN, 1, 14.5));
    
    
    printf("result getvalue(key exists) = %d\n",get_value(1, c_value1, &c_value2, &c_value3));
    printf("Value1: %s\nValue2: %d\nValue3: %f\n", c_value1, c_value2, c_value3);
    
    printf("result get_value(key does not exist) = %d\n", get_value(5, c_value1, &c_value2, &c_value3));
    
    //MODIFY_VALUE
    //case key does exist
    printf("result modify_value(key does exist) = %d\n", modify_value(2, "moyingPlays", 2, 14.5));
    //case key does not exist
    printf("result modify_value(key does not exist) = %d\n", modify_value(7, "moyingPlays", 2, 14.5));
    
    //DELETE_KEY
    //case key does exist
    printf("result delete_key(key does exist) = %d\n", delete_key(2));
    //case key does not exist
    printf("result delete_key(key does not exist) = %d\n", delete_key(7));
    
    //EXISTS
    //case key does exist
    printf("result exist(key does exist) = %d\n", exists(3));
    //case key does not exist
    printf("result exits(key does not exist) = %d\n", exists(7));
    
    //COPY_KEY
    //case key1 does not exist returns -1
    printf("result copy_key(key1 does not exist) = %d\n", copy_key(7, 8));
    //case key2 does not exist, it's created with the same values as key1
    printf("result copy_key(key2 does not exist) = %d\n", copy_key(1, 8));
    //case key2 does exist, it's modified with the same values as key1
    printf("result copy_key(key1 and key2 do exist) = %d\n", copy_key(1, 3));
    
    printf("result init() = %d\n", init());
*/
return 0;
}