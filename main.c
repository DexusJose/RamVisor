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
#include <String.h>


// Definitions
#define true 1
#define false 0
#define max_r 22
#define max_c 64
#define s_rows 6
#define s_cols 20

//Global variables.
char n_message_window[max_r][max_c]={
    "****************************************************************",
    "*                      RamVisor. v.01.0b                       *",
    "****************************************************************",
    "*        Author: Eng. Jose Ramon Perez Miranda.                *",
    "*        About: This program pretends tho show info about      *",
    "*        the memory installed on PC.                           *",
    "*        No warranty that this show exactly info!              *",
    "*                                                              *",
    "*========================== *Menu* ============================*",
    "*                                     +---------------------+  *",
    "*      Chose one. (q) to exit         |        _INFO_       |  *",
    "*                                     +---------------------+  *",
    "*  1.-Max Memory Ram can accepted     |                     |  *",
    "*     this PC (in Kilobytes).         |                     |  *",
    "*  2.-Memory devices.                 |                     |  *",
    "*  3.-Memory Type.                    |                     |  *",
    "*  4.-Memory Speed.                   |                     |  *",
    "*  5.-Manufacturer.                   |                     |  *",
    "*  6.-Memory Capacity(in bytes).      |                     |  *",
    "*  7.-Description.                    +---------------------+  *",
    "*                                                              *",
    "****************************************************************"
};
//Commands
char text[s_cols];    // variable that save the message final

//char inf[] = "MaxCapacity";

//Variable for set the fixed box text
int l_c = max_c - (max_c - 39);
int l_r = max_r - (max_r - 12);
//info box
char inf_box[s_rows][s_cols] = {
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    "
};

//mode
char mode[] = "r";  //open the file to read data inside.
// deb mode
short deb = false;

//counter
int counter = 0;

//Pointer assignation
FILE *fp;
char msg_text[1024];

//Main
int main()
{

    //Show the menu app
    menu();

    // Uncomment for release
    //system("pause");

    return 0;
}

//*****Subfunctions*******

//Update the inf_box.
void update_inf_box(){

    for(int r = l_r ; r < l_r+s_rows ; r++){

        for(int c = l_c ; c < l_c+s_cols ; c++){

            n_message_window[r][c] = inf_box[r - l_r][c - l_c];

        }
    }
}

//This function show the GUI app.
void show_window(){

    for(int r = 0 ; r < max_r; r++){
        for(int c = 0 ; c < max_c ; c++){
            //print the window with all info
            printf("%c",n_message_window[r][c]);
        }
        //print the number lines
        if(deb == true){
            printf(" :L%0*d",2,r);
        }

        printf("\n");
    }

}

void clean_info_box(){
    for(int r = 0 ; r < s_rows ; r++ ){
        for(int c = 0; c < s_cols ; c ++){
            inf_box[r][c] = ' ';
        }
    }
}

// * The menu app *
void menu(){
    int x = 1;

    char op_menu[]="x";

    do{

        show_window();  //show the array GUI

        clean_info_box();

        printf("Enter an option: ");

        gets(op_menu);  //Wait the option

        //Menu choice
        switch(op_menu[0]){

            //Choice 'q' to close the app
            case 'q':
                printf("Exit from the app...\n");
                x = 0;
                //printf("%d",l_c);
                break;

            //Choice '1' to get the maximum memory
            case '1':
                // get the info to show
                get_inf("wmic memphysical get MaxCapacity");
                // update the box info
                update_inf_box();
                break;

            case '2':
                //Next add.
                get_inf("wmic memphysical get MemoryDevices");

                update_inf_box();
                break;

            case '3':
                //Next add.
                get_inf("wmic memorychip get MemoryType");

                update_inf_box();
                break;

            case '4':
                get_inf("wmic memorychip get Speed");
                update_inf_box();
                break;

            case '5':
                get_inf("wmic memorychip get Manufacturer");
                update_inf_box();
                break;

            case '6':
                get_inf("wmic memorychip get Capacity");
                update_inf_box();
                break;

            case '7':
                get_inf("wmic memorychip get Description");
                update_inf_box();
                break;

            case 'i':   //for debug only

                if(deb == true){
                    system("cls");

                    for(int k = 0 ; k < s_rows ; k++ ){
                        for(int l = 0 ; l < s_cols ; l++ ){

                            printf(" %0*x",2,inf_box[k][l]);   //print the info_box

                            }
                        printf(" :l%0*d\n",2,k); //print the line number

                    }
                }

                break;

            //Choice to do nothing
            default:
                break;
        }
        if(deb != true){
            system("cls");
        }

    }while(x);
}

//prototype
void get_inf(char *cmd)
{
    //char command[50] = "wmic memphysical get MaxCapacity";

    //Only for debug
    if(deb == 1){
        printf("into 'get_command'\n"); //for debug only
        puts("Open the file to save the string");
    }

    fp = popen(cmd,mode);   //open the file to receive the strings
    if(fp == NULL)  //if pointer is equals to NULL
    {
        //Do
        printf("Error run command!");   //Print the message error in the console
        exit(1);    //Exit with error
    }
    counter = 0;

    while(fgets(msg_text,sizeof(msg_text),fp) != NULL ){

        //if only for development
        if(deb == true){

            printf("\nPrint the size of length: %d",strlen(text));
            printf("\nEnd While\n");

        }

        no_space(msg_text,text);    //Call for the function to separate the " "

        //insert to box info
        for(int i = 0 ; i < strlen(text) ; i++){

            inf_box[counter][i] = text[i];

        }

        counter++;
    }

    pclose(fp);
}

void no_space(char *s, char *ns){   // *s to msg_text, and *ns to text

    while(*s != '\n'){
        if((*s != ' ') ){

            *ns = *s;   //ad the char of the string(s) to new string(ns)

            if(*ns == 13)*ns = 0;   //if to eliminated any endline

            ns++;   //increment the pinter of new string(ns)

        }
        s++;

    }

}
