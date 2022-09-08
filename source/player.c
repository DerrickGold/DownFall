#include <PA9.h>
#include "player.h"

//Collision Detection for sprites

inline void HideSprite(bool screen,int sprite,bool hide){
	#define ATTR0_DISABLED   (2<<8) 
	switch(hide){
		case 0:PA_obj[screen][sprite].atr0 &= ~ATTR0_DISABLED;break;//show sprite
		case 1:PA_obj[screen][sprite].atr0 |= ATTR0_DISABLED;break;//hide sprite
	}
}

inline void BAG_DualSetSpriteY(u8 obj, s16 y){ 
	if (y <192) {
		HideSprite(1,obj,0);
		PA_SetSpriteY(1, obj, y);
		PA_SetSpriteX(1, obj, DualSpriteX[obj]);
	}
	else HideSprite(1,obj,1);
	//PA_SetSpriteX(0, obj, 256); // hide sprite if not on screen...
	if (y > PA_ScreenSpace) {
		HideSprite(0,obj,0);
		PA_SetSpriteY(0, obj, y - PA_ScreenSpace);
		PA_SetSpriteX(0, obj, DualSpriteX[obj]);
	}
	else HideSprite(0,obj,1);
	//PA_SetSpriteX(1, obj,256);
}
inline bool spritecollide(bool screen,int sprite1,int sprite2){
	s16 x1=0,y1=0,w1=0,h1=0;
	x1=(PA_GetSpriteX(screen, sprite1)+3);
	y1=(PA_GetSpriteY(screen, sprite1)+4);
	w1=4;
	h1=8;
  
	s16 x2=(PA_GetSpriteX(screen, sprite2)+7);
	s16 y2=(PA_GetSpriteY(screen, sprite2)+4);
	s8 w2=14;
	s8 h2=8;
	return (((x2 >= x1 - (w1 + w2)/2) && (x2 <= x1 + (w1 + w2)/2) && (y2 >= y1 - (h1 + h2)/2) && (y2 <= y1 + (h1 + h2)/2)));  
}

	
inline void LoadPlayer(void){
	Player.X=128;
	Player.Y=40;
	PA_DualLoadSpritePal(1,(void*)spritepal);	// Palette name
	PA_DualCreateSprite(0,(void*)spritegfx,PlayerSizeX,PlayerSizeY,1, 1,Player.X,Player.Y); 
	free(spritegfx);
}
	
void PlayerMovement(void){
	if(Player.Inverse==0)Player.X += (Pad.Held.Right - Pad.Held.Left)*(Player.Speed-1);//Controlled movement
	else Player.X += (Pad.Held.Left - Pad.Held.Right)*(Player.Speed-1);//Controlled movement
	Player.Y+=Player.Speed;//fall speed
	
	if(Player.X<0)Player.X+=Player.Speed;
	else if(Player.X+8>256)Player.X-=Player.Speed;
	if(Player.Y+8>384)Player.Y-=Player.Speed;
	BAG_DualSetSpriteY(0,Player.Y); 
	PA_DualSetSpriteX(0,Player.X);
}

