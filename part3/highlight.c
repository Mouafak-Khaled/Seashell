#include<stdio.h>
#include <stdlib.h>
#include<string.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

void highlightWord(char *fileName, char *word, char* color);

int main(int arg, char **args){

    if(arg != 4)
       return -1;
    
    char *word = args[1];
    char *color = args[2];
    char *fileName = args[3];

    highlightWord(fileName, word, color);
    return 0;

}


void highlightWord(char *fileName, char *word, char* color)
{

   
    FILE *file;
    char line[1024][1024];
    file = fopen(fileName, "r+");
     if (file == NULL){
      printf("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }


   
    int i = 0;
    while(fgets(line[i], 1024, file)) {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    fclose(file);     
    


    for(int k = 0; k < i; k++){

        char *token = strtok(line[k], " ");
        while(token != NULL){

            if(strcmp(word, token) == 0){


                if(strcmp(color, "r") == 0){
                  printf("%s%s%s ", RED, token,COLOR_RESET); 
                  
                
                } else if(strcmp(color, "g") == 0){
                  printf("%s%s%s ", GREEN, token,COLOR_RESET); 
                
                } else if(strcmp(color, "b") == 0){
                  printf("%s%s%s ", BLUE, token,COLOR_RESET); 

                }

            } else {
             printf( "%s ", token );
            }
    
             token = strtok(NULL, " ");
        }
        
        printf("\n");
    }


}




   





