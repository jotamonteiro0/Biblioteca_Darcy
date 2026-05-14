#include <stdio.h>
#include <stdbool.h>


int main () {

    bool isOnline = 1;
    bool isStudent = 0;
    bool forSale = true;

    if (forSale) {
        printf ("That item is for sale");
    }        
    
    else {
        printf ("That item is not for sale");
    }


    return 0;

}