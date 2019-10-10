#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>

/* INIT GLOBALS */
struct stat currFile;
int badFiles = 0;
int numDir = 0;
int numAllText = 0;
int regFiles = 0;
int specialFiles = 0;
off_t size = 0;
off_t sizeText = 0;
int textFlag = 0;
sem_t mutex;


#define BUFFSIZE 1024
#define MAXTHREAD 15

pthread_t threadID[MAXTHREAD];
void handleFile(char*);

void* threadFunction(void* arg){
	char* fileName = (char*) arg;	
	sem_wait(&mutex);	
	handleFile(fileName);
	sem_post(&mutex);
}


void handleFile(char* fileName){
	if(stat(fileName,&currFile) < 0){
                        badFiles++;
                }else if(S_ISDIR(currFile.st_mode)){numDir++;}
                else if(S_ISREG(currFile.st_mode)){
                        regFiles++;
                        size += currFile.st_size;
                        char newBuff[BUFFSIZE];
                        int index,cnt;
                        textFlag = 0; // assume printable chars until proven otherwise
                        if((index = open(fileName,O_RDONLY))> 2){
                                while(cnt = read(index,(void *) &newBuff,BUFFSIZE) > 0 && !textFlag){
                                        for(int i = 0;i< cnt;i++){
                                                if(!isspace(newBuff[i]) && !isprint(newBuff[i])){
                                                        textFlag = 1;
                                                        break;
                                                }
                                                textFlag = 0;
                                        }
                                }
				if(!textFlag){printf("%s\n",fileName); numAllText++;sizeText += currFile.
st_size;}
                                close(index);
			}
	}else{specialFiles++;}	
	
}


void main(int argc, char* argv[]){
	char buff[100] = "";	
	sem_init(&mutex,0,1);
	//sem_init(&fileName,0,1);
	while(fgets(buff,100,stdin) != NULL){
		char* fileName = (char*) malloc(strlen(buff));
		sscanf(buff,"%s",fileName);
		handleFile(fileName);			
	}
	sem_destroy(&mutex);
	printf("Bad Files: %d\n",badFiles);
	printf("Directories: %d\n",numDir);
	printf("Regular Files: %d\n",regFiles);
	printf("Special Files: %d\n",specialFiles);
	printf("Regular File Bytes: %lld\n",size);
	printf("Text Files: %d\n",numAllText);
	printf("Text File Bytes: %lld\n",sizeText);
	//printf("bad: %d, dir: %d, reg: %d, size: %lld, textOnly: %d, textSize: %lld, special: %d\n",badFiles,numDir,regFiles,size,numAllText,sizeText,specialFiles);


}
