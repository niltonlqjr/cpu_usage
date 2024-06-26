#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CMD_STR "ps --sort=-pcpu -eo pcpu,pid,size,cmd | grep %s | awk -F\" \" '{if ($4 == \"%s\") {print $1,$2,$3,$4}}' >> %s"
#define CMD_STR_LEN strlen(CMD_STR)


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
    cmd_len = CMD_STR_LEN+1 + //100 + //"ps --sort=-pcpu -eo pcpu,pid,cmd | grep %s | awk -F\" \" '{if ($3 == \"%s\") {print $1,$2,$3}}' >> %s",argv[1],argv[1],argv[3]);"
              strlen(argv[1])+
              strlen(argv[3]);
    printf("%ld\n\n",CMD_STR_LEN);

    cmd_string = (char *) malloc ((cmd_len+1)*sizeof(char));
    sprintf(cmd_string,CMD_STR,argv[1],argv[1],argv[3]);
    printf("%s",cmd_string);
    while(1){
        //system("ps --sort=-pcpu -eo pcpu,pid,cmd | grep %s >> %s",argv[1],argv[3]);
        system(cmd_string);
        msleep(interval);
    }
}