#include <iostream>
#include "my_prettyprint.h"


#include <cstdio>


#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>





int main()
{
    int a {759};
    char* cStr {"World"};

    my::PrettyPrint prettyPrint;

    prettyPrint.displayLevel(true, true, true, true);
    prettyPrint.displayTime(true);
    prettyPrint.displayFuncName(true);
    prettyPrint.setSeparator("::");
    prettyPrint.setFiller(' ');
    //    prettyPrint.setCallerName(__FUNCTION__);


    prettyPrint.debug("Hello, %s!", cStr);



    return 0;
}

