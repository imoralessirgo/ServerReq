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




void main(int argc, char* argv[]){

	while(!feof(stdin)){
		char buff[100] = "";
		scanf("%s",buff);

		//fgets(buff,100,stdin);	
		if(stat((const char*) buff,&currFile)<0){
			badFiles++;		
		}else if(S_ISDIR(currFile.st_mode)){
			numDir++;
		}else if(S_ISREG(currFile.st_mode)){
			regFiles++;
			size += currFile.st_size;
			char newBuff[currFile.st_size];
			int index = open(newBuff,O_RDONLY);
			if(read(index,newBuff,currFile.st_size)){
				for(off_t i = 0;i<currFile.st_size;i++){
					if(!isspace(newBuff[i]) && !isprint(newBuff[i])){
						textFlag = 1;
						break;
					}
					textFlag = 0;
				}
				if(!textFlag){numAllText++;sizeText += currFile.st_size;}
			}		
	
		}else{
			specialFiles++;
		}
	}

	printf("bad: %d, dir: %d, reg: %d, size: %lld, textOnly: %d, special: %d\n",badFiles,numDir,regFiles,size,numAllText,specialFiles);


}
