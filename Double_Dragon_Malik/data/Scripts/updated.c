#define OBV  openborvariant
#define COBV changeopenborvariant

void main()
{
void P1 = getplayerproperty(0,"entity");
//drawstring(int x, int y, int font#, text)
//drawstring(100, 150, 3, "player_hp:" + getentityproperty(P1, "health") );
//drawstring(100, 100, 3, "e_hp:" + getentityproperty(findtarget(P1), "health") );

if(OBV("in_titlescreen") && !OBV("in_level"))
{ 
	changeopenborvariant("skiptoset",0);
}


if (OBV("in_level"))
 {
void self = getplayerproperty(0 ,"entity");	
//settextobj(11, 35, 130, 1, 999999993,"weapon:" + getentityproperty(self,"model"));


	if(playerkeys(0, 1, "esc")){ //ESC KEY IS PRESSED?
		if(OBV("in_level")){ //IN ANY LEVEL?

			//test
			//settextobj(11, 35, 130, 1, 999999993,"name" + getentityvar(self,0));
			//test
			if(OBV("pause") == 0 && OBV("in_options") != 1) //NOT PAUSED AND NOT IN OPTIONS?
			{
				COBV("slowmotion", OBV("slowmotion")==0?1:0); //TOGGLE SLOW MOTION
			}
		}
	}

}

}
