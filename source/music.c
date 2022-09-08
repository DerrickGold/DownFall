#include <PA9.h>
#include "music.h"
#include "mpc.h"
#include <fat.h>
#include <sys/dir.h>
extern inline char PA_GetSmall(char letter){
   if((letter >= 'A')&&(letter <= 'Z')) return (letter-'A'+'a');
   return letter;
}   

s16 PA_FATSearchExt(DIR_ITER* dir, PAfiletype *filelist, char *ext){
   s16 number = 0;
   u8 i, j;
   struct stat st;
   	
   	
	while (dirnext(dir, filelist[number].filename, &st) == 0) {
	   if(!(st.st_mode & S_IFDIR)){// Is a file...
	   	// Check if right extension...
	   	i = 0;
	   	while( filelist[number].filename[i]) i++; // go to end of name
	   	while( filelist[number].filename[i-1] != '.') i--; // get to extension
	   	
	   	u8 same = 1; // same by default
	   	for(j = 0; ext[j]; j++) if(PA_GetSmall(ext[j]) !=  PA_GetSmall(filelist[number].filename[i+j])) same = 0; // not right extension
	   	
	   	if(same){ // Ok, register file
	   	
		   	for(j = 0; j < i-1; j++) filelist[number].name[j] = filelist[number].filename[j];
		   	filelist[number].name[j] = 0;
		   	
		   	for(i = 0; ext[i]; i++) filelist[number].ext[i] = ext[i];
		   	filelist[number].ext[i] = 0;
		   	
		   	filelist[number].size = st.st_size;
		   	
		   	
		   	number++;
		 	}  	
	   
		}   
	}
 
   
   return number;
}  
char tempmusic[512];
void LoadRandomMPC(void){
	StopMPC();
	s32 number=PA_RandMax(MusicFiles);
	sprintf(tempmusic,"%s%s.%s",FilePath,files[number].name,files[number].ext);
	LoadMPCFile(tempmusic);
	PlayMPC();
}
inline void CheckMusic(void){
	if(check==1){
		if(!MPCPlaying())LoadRandomMPC();
	}
}
bool SetMPC(void){
	//Set up MPC Lib
	InitMPCLib();
	if(!PA_Locate("/", "MPCSongs",true,10,FilePath))return 0;
	check=1;
	DIR_ITER* dir = diropen(FilePath);
	MusicFiles=PA_FATSearchExt(dir, files, "mpc");
	return 1;
}
			
void InitAudio(void){
	//initiate ASlib
	PA_VBLFunctionInit(AS_SoundVBL);
	AS_Init(AS_NO_DELAY| AS_MODE_16CH);
	AS_SetDefaultSettings(AS_PCM_8BIT, 44100,AS_NO_DELAY);
	SetMPC();
}
