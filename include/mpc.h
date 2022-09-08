#ifndef __MPCFILE__
#define __MPCFILE__
//Include the Sound Files for Use
#include "plane1.h"
#include "plane2.h"
#include "plane3.h"
#include "car1.h"
#include "car2.h"
#include "car3.h"
#include "boat1.h"
#include "boat2.h"
#include "boat3.h"
#include "flower1.h"
#include "flower2.h"
#include "flower3.h"
#include "gameboy1.h"
#include "gameboy2.h"
#include "gameboy3.h"
#include "heart1.h"
#include "heart2.h"
#include "heart3.h"
#include "mario1.h"
#include "mario2.h"
#include "mario3.h"
#include "star1.h"
#include "star2.h"
#include "star3.h"
#include "cat1.h"
#include "cat2.h"
#include "cat3.h"
#include "dog1.h"
#include "dog2.h"
#include "dog3.h"
#include "face1.h"
#include "face2.h"
#include "face3.h"
#include "pig1.h"
#include "pig2.h"
#include "pig3.h"
#include "swan1.h"
#include "swan2.h"
#include "swan3.h"
#include "yoshi1.h"
#include "yoshi2.h"
#include "yoshi3.h"
#include "mushroom1.h"
#include "mushroom2.h"
#include "mushroom3.h"
#include "bowser1.h"
#include "bowser2.h"
#include "bowser3.h"
#include "umbrella1.h"
#include "umbrella2.h"
#include "umbrella3.h"
#include "orchestral1.h"
#include "orchestral2.h"
#include "orchestral3.h"
#include "harp1.h"
#include "harp2.h"
#include "harp3.h"

//MPC File Struct
typedef struct{
	u8 frame;
	u8 x;
	u8 y;	
	u8 Note;
	s8 Pitch;
	s8 SoundFile;
	s8 Sign;
	bool used;
}spriteinfos;
spriteinfos Sprite[258][30];

char Author[30];
bool Original;

//used for playback
bool Play;
u16 Page,Note,EndPage;
float NoteBar;
float Tempo;
u8 MPCchan;

//decoding stuff
void PickSoundFile(int note, int page);
u8 NoteToNum(u16 note, u8 scale);
u16 NumToNote(u8 number);

//file handling
bool MPCPlaying(void);
bool LoadMPCFile(char *file);
void PlayMPC(void);
void StopMPC(void);
void UpdateMPC(void);
void InitMPCLib(void);
#endif

