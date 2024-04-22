#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void msleep(int milliseconds){
    if (milliseconds >= 1000){
        sleep(milliseconds / 1000);
    }
    usleep((milliseconds % 1000) * 1000);
}

int main(int argc, char *argv[]){
    char  *cmd_string;
    long long int interval;
    int cmd_len;

    if(argc < 4){
        printf("invalid argumments:\n %s <exec name> <interval> <output_file> \n",argv[0]);
        return 0;
    }
    interval = atoi(argv[2]);
    cmd_len = 50 + //space to string "ps --sort=-pcpu -eo pcpu,pid,cmd | grep  >> "
              strlen(argv[1])+
              strlen(argv[3]);

    cmd_string = (char *) malloc ((cmd_len+1)*sizeof(char));
    sprintf(cmd_string,"ps --sort=-pcpu -eo pcpu,pid,cmd | grep %s >> %s",argv[1],argv[3]);
    printf("%s",cmd_string);
    while(1){
        //system("ps --sort=-pcpu -eo pcpu,pid,cmd | grep %s >> %s",argv[1],argv[3]);
        system(cmd_string);
        msleep(interval);
    }
}