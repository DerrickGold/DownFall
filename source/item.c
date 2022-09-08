#include <PA9.h>
#include "item.h"
#include "BrickGeneration.h"
#include "player.h"


void CreateItemSprite(void){
	Items.X=-32;
	Items.Y=-32;
	PA_DualLoadSpritePal(2,(void*)itempal);	// Palette name
	PA_DualCreateSprite(1,(void*)itemgfx,0,1,1, 2,Items.X,Items.Y); 
}
void StartItemTime(void){
	if(Items.StartTime==FALSE && Items.StartEffect==0){
		Items.AppearTime=PA_RandMinMax(0,1500);
		Items.StartTime=TRUE;
	}
}
void CheckItemTime(void){
	StartItemTime();
	if(Items.StartTime==TRUE && Items.Created==0){
		if(Items.Timer<Items.AppearTime)Items.Timer++;
		if(Items.Timer>=Items.AppearTime){
			Items.X=BricksX[PA_RandMax(17)];
			Items.Y=PA_RandMinMax(140,192)+192;
			PA_DualSetSpriteXY (1,Items.X,Items.Y);
			Items.Created=1;
		}
	}
}
bool Itemcollide(bool screen,int sprite1,int sprite2){
	s16 x1=(PA_GetSpriteX(screen, sprite1)+8);
	s16 y1=(PA_GetSpriteY(screen, sprite1)+8);
	s8 w1=14;
	s8 h1=14;
	s16 x2=(PA_GetSpriteX(screen, sprite2)+7);
	s16 y2=(PA_GetSpriteY(screen, sprite2)+4);
	s8 w2=16;
	s8 h2=8;
	return (((x2 >= x1 - (w1 + w2)/2) && (x2 <= x1 + (w1 + w2)/2) && (y2 >= y1 - (h1 + h2)/2) && (y2 <= y1 + (h1 + h2)/2)));  
}
void ItemCheckRowCollision(s16 rownumber){
	s16 sprite=0;
	if(PlatForms.Used[rownumber]==1){
		for (sprite=0;sprite<17;++sprite){
			if(Items.Y<192-8&&Itemcollide(1,1,PlatForms.numbers[rownumber][sprite]))Items.Y=PlatForms.Y[rownumber]-16;
			else if(Items.Y>192-8&&Itemcollide(0,1,PlatForms.numbers[rownumber][sprite]))Items.Y=PlatForms.Y[rownumber]-16;	
		}
	}
}	
void DestroyItem(void){
	if(Items.Screen==1){
		PA_SwitchScreens();
		Items.Screen=0;
	}
	Player.Inverse=0;
	Items.StartTime=0;
	Items.Timer=0;
	Items.Created=0;
	Items.Duration=0;
	Items.StartEffect=0;	
	Items.Type=0;
	PA_DualSetSpriteXY (1,-32,-32);	
}

void UpdateItemEffect(s8 Type){
	if(Type>0){
		if(Items.Duration<Items.EndDuration){
			Items.Duration++;
			switch(Type){
				case 1://slow motion
					PA_WaitForVBL();
				break;
				case 2://reverse controls
					Player.Inverse=1;
				break;
				case 3:
					if(Items.Screen==0){
						PA_SwitchScreens();
						Items.Screen=1;
					}
				break;
			}
		}
		else if(Items.Duration>= Items.EndDuration) DestroyItem();
	}
}

void UpdateItems(void){
	CheckItemTime();
	if(Items.Created==1){
		if(Items.Y>16){
			if(Items.StartEffect==0){
				Items.Y+=2;
				if(Items.Y+16>=384)Items.Y-=2;
				PA_DualSetSpriteXY (1,Items.X,Items.Y);
			}
			if((Player.Y>192-8 && Items.Y>192-8&&Itemcollide(0,0,1))||(Player.Y<192-8 && Items.Y<192-8&&Itemcollide(1,0,1))){
				PA_DualSetSpriteXY (1,-32,-32);	
				Items.StartEffect=1;
				Items.Type=PA_RandMax(MAXITEMS)+1;
				switch(Items.Type){
					case 1:Items.EndDuration=350;break;
					case 2:Items.EndDuration=500;break;
					case 3:Items.EndDuration=800;break;
				}
			}
		}
		else if(Items.Y<=16){
			DestroyItem();
		}
		UpdateItemEffect(Items.Type);
	}
}
