/*
    Title: RamVisor.
    Author: Eng. Jose Ramon Perez Miranda.
    Date: 21-11-21.
    About: this program pretends to show info about
    the memory installed on pc.
*/

//Librarys
#include <stdio.h>
#include <stdlib.h>

//Global variables.
char message_splash[]=  "\n"
                        "               Title: RamVisor. v. 0.1.0alpha\n"
                        "   ***********************************************\n"
                        "   Author: Eng. Jose Ramon Perez Miranda.\n"
                        "   Date: 21-11-21.\n"
                        "   About: this program pretends to show info about\n"
                        "   the memory installed on pc.\n\n";

//Main
int main()
{
    splash();
    return 0;
}

//Subfunctions
void splash()
{
    printf("%s",message_splash);
}

