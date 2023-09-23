#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "audio_gen.c"

int main(){

unsigned int menu = 0;

    while(1)
    {

        printf("Select a mode:\n");
        printf("1. Generate Audio\n");
        printf("2. Terminate\n");

        scanf("%d",&menu);

            switch(menu)
            {
                case 1:
                    audio_gen();
                    menu = 0;
                    break;
                
                case 2:
                    return 0;
            }
    }

return 0;

}
