#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "helper.h"

struct stat currFile;
int badFiles = 0;
int numDir = 0;
int numAllText = 0;
int regFiles = 0;
int specialFiles = 0;
off_t size = 0;
off_t sizeText = 0;
int textFlag = 0;

#define BUFFSIZE 1024


void main(int argc, char* argv[]){

	while(!feof(stdin)){
		char buff[100] = "";
		scanf("%s",buff);
		//intf("%s\n",buff);
		//fgets(buff,100,stdin);	
		if(stat((const char*) buff,&currFile)<0){badFiles++; printf("%s\n",buff);}
		else if(S_ISDIR(currFile.st_mode)){numDir++;}
		else if(S_ISREG(currFile.st_mode)){
			regFiles++;
			size += currFile.st_size;
			char newBuff[BUFFSIZE];
			int index,cnt;
			textFlag = 0; // assume printable chars until proven otherwise
			if(index = open(buff,O_RDONLY) > 0){
				while(cnt = read(index,newBuff,BUFFSIZE) > 0 && !textFlag){
					for(int i = 0;i< cnt;i++){
						if(!isspace(newBuff[i]) && !isprint(newBuff[i])){
							textFlag = 1;
							printf("%c\n",newBuff[i]);
							printf("reg no print%s\n",buff);
							break;
						}
						textFlag = 0;
					}
					if(!textFlag){printf("al txt%s\n",buff);numAllText++;sizeText += currFile.st_size;}
				}
			close(index); 			
			}else{badFiles++;}
		}else{specialFiles++;}
	}

	printf("bad: %d, dir: %d, reg: %d, size: %lld, textOnly: %d, textSize: %lld, special: %d\n",badFiles,numDir,regFiles,size,numAllText,sizeText,specialFiles);


}
