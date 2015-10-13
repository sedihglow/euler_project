/*
    This main is for the all my euler project problems. This main takes in
    a number corresponding to the euler project problem to run.

    ./a.out #problem
*/


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


#include "euler_project.h"
#include "err_handle/err_handle.h"
#include "get_num/get_num.h"


int32_t main(int32_t argc, char *argv[])
{
    register uint32_t probNum = 0;

    if(argc != 2){
        noerrExit("Invalid cmd arguments. $ cmd problemNumber");}

    probNum = getu32_t(argv[1], 0, "probNum");
    
    switch(probNum)
    {
        case 1: prob1();                                break;
        case 2: prob2();                                break;
        case 3: prob3();                                break;
        case 4: prob4();                                break;
        case 5: prob5();                                break;
        case 6: prob6();                                break;
        case 7: prob7();                                break;
        case 8: prob8();                                break;
        default: noerrExit("Problem number not found"); break;
    }

    exit(EXIT_SUCCESS);
} 
