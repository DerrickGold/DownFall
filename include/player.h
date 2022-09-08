#ifndef _playerstuff_h_
#define _playerstuff_h_
#define DUALSCREEN 1

typedef struct{
	s32 X,Y;
	s8 Speed;
	bool Inverse;
}playerinfos;
playerinfos Player;
typedef struct{
	int Score;
	char Name[32];
}scoreinfos;
scoreinfos High[10];
u16 CharacterGfx;
u8 *spritegfx;
u16 spritepal[256]; 
s8 difficulty;

s8 PlayerSizeX;
s8 PlayerSizeY;
int Score;
bool spritecollide(bool screen,int sprite1,int sprite2);
void LoadPlayer(void);
void PlayerMovement(void);
#endif
