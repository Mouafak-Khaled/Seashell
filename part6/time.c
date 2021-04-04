#include<stdio.h>
#include<time.h>
#include<string.h>
#include <stdlib.h>



 const char *timeZones[] = {"GMT","ECT", "EET", "ART", "EAT", "MET", "NET", "PLT",
                          "IST", "BST", "VST", "CTT", "JST", "ACT", "AET", "SST", "NST",
                           "MIT", "HST", "AST", "PST", "PNT", "MST", "CST", "EST", "IET",
                            "PRT", "CNT", "AGT", "BET", "CAT"};

void printTime(int index);
int getHourConversion(int index);
int getMinuteConversion(int index);
int getTimeZoneIndex(char *timeZone);



int main(int arg, char **args){

     if(arg > 2)
       return -1;

    if(args[1]  == NULL){
       printTime(0);

    } else {

        int index = getTimeZoneIndex(args[1]);
        if(index == -1){
          printf("%s", "Invalid Time Zone Name!");
        }
        
        printTime(index);

    }

    
}


void printTime(int index){


    FILE *file;
    char descriptionLines[1024][1024];
    file = fopen("Description.txt", "r+");
    if (file == NULL){
      printf("Error while opening the file Description.txt\n");
      exit(EXIT_FAILURE);
   }

    int i = 0;
    while(fgets(descriptionLines[i], 1024, file)) {
        descriptionLines[i][strlen(descriptionLines[i]) - 1] = '\0';
        i++;
    }
    fclose(file);   



    time_t rawtime = time(NULL);
    
    if (rawtime == -1) {
        
        puts("The time() function failed");
       
    }
    
    struct tm *ptm = gmtime(&rawtime);
    
    if (ptm == NULL) {
        
        puts("The localtime() function failed");
     
    }

    int minute = getMinuteConversion(index) + ptm->tm_min;
    int hour = getHourConversion(index) + ptm->tm_hour;
    
    
    printf("The Time According to The %s Zone (%s) is: %02d:%02d:%02d\n", descriptionLines[index], 
           timeZones[index], hour, minute, ptm->tm_sec);

}


int getTimeZoneIndex(char *timeZone){

    for(size_t i = 0; i< sizeof(timeZones); i++){

        if(strcasecmp(timeZone, timeZones[i]) == 0){

            return i;
        }


    }

        return -1;

}


int getHourConversion(int index){

    const int hourConversions[] = {0, 0, +1, +2, +2, +3, +3, +4, +5, +5,
                           +6, +7, +8, +9, +9, +10, +11, +12,-11, 
                           -10, -9, -8, -7, -7, -6, -5, -5, -4,
                           -3, -3, -3, -1};

    return hourConversions[index];



}


int getMinuteConversion(int index){

   const int minuteConversions[] = {0, 0, 0, 0, 0, 0, 30, 0, 0, 30,
                           0, 0, 0, 0, 30, 0, 0, 0,0, 
                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                           -30, 0, 0, 0};

    return minuteConversions[index];



}