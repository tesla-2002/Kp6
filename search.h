#ifndef _SEARCH_H
#define _SEARCH_H

#include "inout.h"
#include "passenger.h"

typedef enum {
    PRINT = 1,
    ADDTOTXT = 2,
    ADDTOBIN = 3,
    DELETEFROMTXT = 4,
    DELETEFROMBIN = 5, 
    SEARCH = 6
} var_flags;

Passenger passenger_get_from_user (Passenger pass);
void passenger_add_to_txt (FILE* filetxt);
void passenger_add_to_bin (FILE* filebin);
void passenger_delete_from_txt (const char* filename, const char* sname, FILE* filetxt);
void passenger_delete_from_bin (const char* filename, const char* sname, FILE* filebin); 
void pass_free(Passenger* pass, int size);
int search_max (Passenger* pass, int size);

#endif