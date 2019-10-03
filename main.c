#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcnt1.h>
#include "helper.h"

struct stat currFile;
int badFiles = 0;
int numDir = 0;
int regFiles = 0;
int specialFiles = 0;
off_t size = 0;




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
			int index = open(newBuff,O_RDONLY)
			while(read(open(buff,O_RDONLY),buff,BUFFSIZE)){
				re
			}		
	
		}else{
			specialFiles++;
		}
	}

	printf("bad: %d, dir: %d, reg: %d, size: %lld, special: %d\n",badFiles,numDir,regFiles,size,specialFiles);


}
