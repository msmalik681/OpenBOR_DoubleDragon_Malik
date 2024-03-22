#define hres 	openborvariant("hresolution")
#define vres 	openborvariant("vresolution")
#define etime	openborvariant("elapsed_time")
#define self	getlocalvar("self")
#define SLV		setlocalvar
#define GLV		getlocalvar
#define	GFSA	getfilestreamargument
////////////USER SET FILES//////////////////
#define	FILE	"data/story/text.txt"
#define	BORDER	"data/story/border.gif"
#define	PUSH01	"data/story/push01.gif"
#define	PUSH02	"data/story/push02.gif"
////////////////////////////////////////////

void main()
{//Story system by msmalik681.
		
		
		if(GLV("scene") == NULL())
		{//initial setup this will only run once at the start.
	playmusic("data/music/story.bor", 1);
		SLV("scene",getentityproperty(self,"name"));
		SLV("border",loadsprite(BORDER));//comment this out if you want to draw scripted border.
		int i = 0;
		void file = openfilestream(FILE);
				for(i=0;i>-1;i++)
				{//find the scene based on entity name or alias.
					if( GFSA(file,0,"string") == GLV("scene") )
					{
						SLV("line",(i+1));
						break;
					} else { filestreamnextline(file); }
					
					if(i>10000)
					{//just in case something breaks.
					log("broke when finding scene!\n");
					endstory();
					break;
				}	
				}
		closefilestream(file);
		SLV("intro_time",etime+50);//set the delay before player can skip intro.
		drawtext();
		} else if((	playerkeys(0, 1, "attack") ||
					playerkeys(1, 1, "attack") ||
					playerkeys(2, 1, "attack") ||
					playerkeys(3, 1, "attack"))&& GLV("intro_time") < etime)
		{//press the attack button to increment though the story. or select choice.
			nullkeys();
			if(GLV("select"))
			{
				SLV("line",GLV("choice"+GLV("select")));
				endselect();
			} 
			drawtext();
		}
		
		if((playerkeys(0, 1, "jump") || playerkeys(0, 1, "esc") ||
			playerkeys(1, 1, "jump") || playerkeys(1, 1, "esc") ||
			playerkeys(2, 1, "jump") || playerkeys(2, 1, "esc") ||
			playerkeys(3, 1, "jump") || playerkeys(3, 1, "esc"))&& GLV("intro_time") < etime)
		{//jump or esc will skip the story.
			nullkeys();
			if(GLV("noskip")==NULL()){endstory();}
		}
		

		
		void pic1 = GLV("pic1");
		void pic2 = GLV("pic2");
		void pic3 = GLV("pic3");
		void border = GLV("border");
		if(pic1)
		{//this will display all visuals.
		int time = GLV("time");
		
		if(time == NULL() || time < etime)
		{//set the 2 frames for button push animation.
			SLV("time",etime+100);
			SLV("switch",GLV("switch")==1?0:1);
			if(GLV("push")){free(GLV("push"));}
			SLV("push",loadsprite(GLV("switch")==1?PUSH01:PUSH02));
		}
			drawsprite(pic1, 0, 0,999999993);//first front character portrait
			if(pic3)
			{
				drawsprite(pic3, 0, 0,999999995);//third far front item portrait
				drawbox(0,0,hres,vres,999999994,rgbcolor(0,0,0),6);//alternate screen darken.
			} else {drawbox(0,0,hres,vres,999999992,rgbcolor(0,0,0),6);}//screen darken.
			drawsprite(pic2, 0, 0,999999991);//second behind character portrait
			if(GLV("push") && GLV("intro_time") < etime){drawsprite(GLV("push"), hres*0.90, vres*0.85,999999999);}//push button animation
			if(border)
			{
				drawsprite(border, 0, 0,999999990);//border picture.
			} else { drawbox(hres*0.10,vres*0.70,hres*0.80,vres*0.25,999999992,rgbcolor(0,255,255),6);}//scripted text border
		}
		
		if(GLV("choice2"))
			{
			if(GLV("select")==NULL()){SLV("select",2);}//set what text object to display from.
			int fh = 9; //set font height in pixels
			drawbox(0,0,hres,vres,999999991,rgbcolor(0,0,0),6);//screen darken.
			if(border)
			{
				drawsprite(border, 0, 0,999999993);//border picture.
			} else { drawbox(hres*0.10,vres*0.70,hres*0.80,vres*0.25,999999993,rgbcolor(0,255,255),6);}//scripted text border
			drawbox(gettextobjproperty(GLV("select"),"x"),gettextobjproperty(GLV("select"),"y")+((GLV("select")/2)*fh),hres*0.70,fh,999999994,rgbcolor(200,180,255),6);// selection box
			
		if((playerkeys(0, 1, "movedown") ||
			playerkeys(1, 1, "movedown") ||
			playerkeys(2, 1, "movedown") ||
			playerkeys(3, 1, "movedown"))&& GLV("intro_time") < etime)
		{//for selection menu.
			nullkeys();
			if(gettextobjproperty(GLV("select")+2,"x")){SLV("select",GLV("select")+2);}
		}
		
		if((playerkeys(0, 1, "moveup") ||
			playerkeys(1, 1, "moveup") ||
			playerkeys(2, 1, "moveup") ||
			playerkeys(3, 1, "moveup"))&& GLV("intro_time") < etime)
		{//for selection menu.
			nullkeys();
			if(gettextobjproperty(GLV("select")-2,"x")){SLV("select",GLV("select")-2);}
		}
			}
}

void drawtext()
{//This function reads and displays the text from the input file.
			cleartext(); //clear any previous text.
			if(GLV("pic1"))
			{//clear previous pictures.
				free(GLV("pic1"));
				SLV("pic1", NULL());
			} 
			
			if(GLV("pic2"))
			{//clear previous pictures.
				free(GLV("pic2"));
				SLV("pic2", NULL());
			} 

			if(GLV("pic3"))
			{//clear previous pictures.
				free(GLV("pic3"));
				SLV("pic3", NULL());
			}
			
			int i;
			void file = openfilestream(FILE);
			
			////////////text customization //////////////
			int min = hres*0.15;		//how far from the left to start text.
			int max = hres*0.85;		//how close to the right end the text.
			int height = vres*0.78;		//how far down the screen to start the text.
			int font = 3;				//what font to use.
			//////////////////////////////////////////
			
			char string;
			int line = GLV("line");
			
				for(i=0;i>-1;i++)
				{//lets set the input file to correct line.
				 filestreamnextline(file);
				 if((i+1) == line){break;}
				 if(i>10000)
				 {//just in case something breaks.
					log("broke when incrementing!\n");
					endstory();
					break;
				 }
				}
		
		
		if(GFSA(file,0,"string") == "#END")
		{//if the line reads #END end the story.
			closefilestream(file);
			endstory();
		} else if(GFSA(file,0,"string") == "#CHOICE")
		{//multiple choice selection
	
			settextobj(20, min,  height, font, 9999999999, GFSA(file,1,"string")); // display choice question.
			char newline = "\n"; //increment line.
			for(i=2;i<9;i++)
			{
				if(GFSA(file,i,"string") == "#END")
				{
				break;
				}else {
				settextobj(i, min,  height, font, 9999999999, newline+GFSA(file,i,"string")); // display choice text.
				SLV("choice"+i, GFSA(file,i+1,"int")+GLV("line"));//hold the line number for choice.
				i++; //move to the line for this choice.
				newline = newline + "\n"; //set next line down.
				}
			}
		} else if(GFSA(file,0,"string") == "#GOTO")
		{//skip forward relative to current line.
			SLV("line",GLV("line")+GFSA(file,1,"int"));
			closefilestream(file);
			drawtext();
		} else if(GFSA(file,0,"string") == "#NOSKIP")
		{
			SLV("noskip", 1);
			SLV("line",GLV("line")+1);
			closefilestream(file);
			drawtext();
		} else if(GFSA(file,0,"string") == "#FOLLOW")
		{
			changeentityproperty(GLV("self"), "animation", openborconstant("ani_follow"+GFSA(file,1,"string"))); //Change the animation
			SLV("line",GLV("line")+1);
			closefilestream(file);
			drawtext();
		} else if(GFSA(file,0,"string") == "#NAME")
		{//check for a player name example: #NAME		name_of_player		player_number		goto_line_true		goto_line_false
		 //names are case sensitive. if you use skipselect use the matching case to player name.
		 //remember goto_line is relative from the line your on so 1 will skip to the next line.
		 //for player_number your type player 1 to 4 and 5 is to check all players.
			int pass = 0;
			i=GFSA(file,2,"int");

			if(i==5)
			{//check all players for name.
				for(i=0;i!=5;i++)
					{
						if(getplayerproperty(i,"name")==GFSA(file,1,"string"))
						{
							SLV("line",GLV("line")+GFSA(file,3,"int"));
							pass = 1;
							break;
						}
					}
			} else
			{//check fixed player for name.
				if(getplayerproperty((i-1),"name")==GFSA(file,1,"string"))
				{
					SLV("line",GLV("line")+GFSA(file,3,"int"));
					pass = 1;
					//break;
				}
			}

			if(pass==0)
			{//goto false line as name not found.
				SLV("line",GLV("line")+GFSA(file,4,"int"));
			}
			closefilestream(file);
			drawtext();
		} else {
		if(GFSA(file,0,"string") == "#SOUND")
		{// if line reads #SOUND play sample from next argument then increment the line.
			playsample(loadsample(GFSA(file,1,"string")));
			filestreamnextline(file);
			SLV("line", GLV("line")+1);
		}
		SLV("pic1", loadsprite(GFSA(file,0,"string"))); //set first picture from current line.
		SLV("pic2", loadsprite(GFSA(file,1,"string"))); //set second picture from current line.
		if(GFSA(file,3,"string")){ SLV("pic3", loadsprite(GFSA(file,3,"string"))); } //set third picture from current line.
		char newline = "";
		string = GFSA(file,2,"string");
		char str_buf = "";
		int cutoff = NULL();
		int k =1;

		if(GLV("con") >= 1)
		{//check the continue line variable.
		string = strright(string,GLV("con"));
		} else {SLV("con",0);}	

		for(i=1;i>-1;i++)
		{//read words and display lines of text.
			if(cutoff)
			{//this cuts off each lines and moves to the next one.
				string = strright(string,strlength(str_buf));
				SLV("con",GLV("con")+strlength(str_buf));
				i=1;
				cutoff = NULL();
			}
			
			if(newline == "\n\n")
				{//here you can limit max the number of lines displayed.
					break;
				}
			
			if(min + strwidth(string,font) < max)
				{//if the remaining text is less then a line limit just display it.
				settextobj(k, min,  height, font, 9999999998,newline+""+string);
				SLV("line",GLV("line")+1);
				SLV("con",0);
				break;
				}
			
			
		str_buf = strleft(string,i);
		if(strright(str_buf,strlength(str_buf)-1)=="_")
		{//if completed a word.
			if(min + strwidth(str_buf,font) >= max)
				{//check if word goes over the limit
					for(i=i-2;i>-1;i--)
					{//cut back to last word before the limit.
					str_buf = strleft(string,i);
					if(strright(str_buf,strlength(str_buf)-1)=="_"){break;}
					}
				settextobj(k, min,  height, font, 9999999998,newline+str_buf);
				k++;
				newline += "\n"; 
				cutoff = 1;
				}
		}
			if(i>10000)
				{//just in case something breaks.
					log("broke when reading!\n");
					endstory();
					break;
				}	
		}
			closefilestream(file);
			}
}

void endstory()
{//function to end story.
	cleartext();
	SLV("line",NULL());
	if(GLV("pic1")){free(GLV("pic1"));}
	SLV("pic1",NULL());
	if(GLV("pic2")){free(GLV("pic2"));}
	SLV("pic2",NULL());
	SLV("con",NULL());
	if(GLV("push")){free(GLV("push"));}
	SLV("push",NULL());
	SLV("noskip",NULL());
	killentity(self);
}

void endselect()
{//end selection screen.
SLV("select",NULL());
SLV("choice2",NULL());
SLV("choice4",NULL());
SLV("choice6",NULL());
SLV("choice8",NULL());
}

void cleartext()
{//remove all text objects.
	int i=0;
	for(i=i;i<50;i++)
	{
	cleartextobj(i);
	}
}

void nullkeys()
{//stop all key presses.
	int i;
	for(i=3:i<4:i++)
	{
	changeplayerproperty(i, "newkeys", 0);
	changeplayerproperty(i, "playkeys", 0);
	}
}