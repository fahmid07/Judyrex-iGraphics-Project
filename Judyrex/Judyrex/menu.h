#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "variable.h"


void menu(){
		iShowBMP(0, 0, "images\\menubg.bmp");
		iShowBMP2(596, 32, "images\\play.bmp", 0);
		if(p==1) iShowBMP2(593, 31, "images\\play1.bmp", 0);
		iShowBMP2(339, 32, "images\\ins.bmp", 0);
		if(ins==1) iShowBMP2(335, 31, "images\\ins1.bmp", 0);
		iShowBMP2(81, 32, "images\\score.bmp", 0);
		if(sc==1) iShowBMP2(77, 31, "images\\score1.bmp", 0);
		iShowBMP2(855, 32, "images\\about.bmp", 0);
		if(ab==1) iShowBMP2(851, 31, "images\\about1.bmp", 0);
		iShowBMP2(1112, 32, "images\\exit.bmp", 0);
		if(ex==1) iShowBMP2(1108, 31, "images\\exit1.bmp", 0);
		if(mute){
			iShowImage(30, 670, 60, 60, mt);
			iText(2, 660, "Click to unmute", GLUT_BITMAP_8_BY_13);
		}
		else{
			iShowImage(30, 670, 60, 60, sn);
			iText(5, 660, "Click to mute", GLUT_BITMAP_8_BY_13);
		}
		iSetColor(0, 0, 0);
		iText(385, 316, str2 , GLUT_BITMAP_9_BY_15);
		iText(385, 348, "Welcome" , GLUT_BITMAP_9_BY_15);
}

#endif // !MENU_H_INCLUDED