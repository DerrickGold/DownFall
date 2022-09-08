#ifndef _itemstuff_h_
#define _itemstuff_h_

typedef struct{
	s16 X,Y;
	s8 Type;
	s32 Duration;
	s32 EndDuration;
	s32 AppearTime;
	s32 Timer;
	bool Created;
	bool StartTime;
	bool StartEffect;
	bool Screen;
}iteminfos;
iteminfos Items;
u16 itempal[256]; 
u8 *itemgfx;
#define MAXITEMS 2

void DestroyItem(void);
void ItemCheckRowCollision(s16 rownumber);
void CreateItemSprite(void);
void UpdateItems(void);
#endif

