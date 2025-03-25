#include <iostream>
#include "my_prettyprint.h"


#include <execinfo.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>





int main()
{
    int a {759};
    char* cStr {"World"};
    char* testString = "Others who use this device won’t see your activity, so you can browse more privately. This won't change how data is collected by websites you visit and the services they use, including Google. Downloads, bookmarks and reading list items will be saved.";

    my::PrettyPrint prettyPrint;
    prettyPrint.setLevels({false, true, true, false});



    prettyPrint.debug("%s", testString);
    prettyPrint.info("%s", testString);
    prettyPrint.warn("%s", testString);
    prettyPrint.error("%s", testString);



    return 0;
}
