#ifndef _musicstuff_h_
#define _musicstuff_h_

//holds folder names
typedef struct{
	char filename[100];
	char name[100];
	char ext[10];  
	u32 size;
}  PAfiletype;
PAfiletype files[50];
char FilePath[256];
bool check;
s32 MusicFiles;
void InitAudio(void);
void CheckMusic(void);

#endif

