#include "iGraphics.h"
#include "bitmap_loader.h"
#include<math.h>
#include "variable.h"
#include "menu.h"
#include "topscore.h"
#include "image.h"
#include "audio.cpp"
#include<algorithm>
#include<vector>
#include<iostream> 
using namespace std;

audio introSound;
audio gameSound;

//intro sound
void introGameSound(){
	introSound.fileName = "judyrex.wav";
	introSound.load();
	introSound.play();
	introSound.set_volume(200);
} 

//ingame sound
void ingameSound(){
	gameSound.fileName = "judyrexInGame.mp3";
	gameSound.load();
	gameSound.play();
}

//click sound
void clickSound(){
	PlaySound("click.wav", NULL, SND_ASYNC);
	/*audio obj;
	obj.fileName = "click.wav";
	obj.load();
	obj.play();*/
}


//coordinate checking
bool validPoint(int x1, int y1, int x2, int y2, int m, int n) { 
    if (m > x1 && m < x2 && n > y1 && n < y2) 
        return true; 
    return false; 
}


//background coordinate
void setBg(){
	Background[0].x = 0;
	Background[0].y = 0;
	Background[1].x = 1360;
	Background[1].y = 0;
}


//background rendering
void bgChange(){
	if(Background[0].x >=-1360) Background[0].x -= bgspeed;
	if(Background[0].x <=-1360) Background[0].x = 1360;
	if(Background[1].x >=-1360) Background[1].x -= bgspeed;
	if(Background[1].x <=-1360) Background[1].x = 1360;

	if(obsX >= -100) obsX -= bgspeed;
	if(obsX < -100){
		obsX = 2050;
		obsCrash = false;
	}

	if(e1X >= -258) e1X -= bgspeed;
	if(e1X < -258){
		e1X = 3050;
		enem1 = true;
		point1 = true;
	}

	if(e2X >= -235) e2X -= bgspeed;
	if(e2X < -235){
		e2X = 2500;
		enem2 = true;
		point3 = true;
	}

	if(ufox >= -220) ufox -= ufospeed;
	if(ufox < -220){
		ufox = 1650;
		ufo = true;
		point2 = true;
	}

	if(level==2){
		if(ufox1 >= -220) ufox1 -= ufospeed;
		if(ufox1 < -220){
			ufox1 = 2280;
			ufo1 = true;
			point4 = true;
		}
	}
	
}

void bgChange2(){
	Background[0].x += bgspeed; 
	Background[1].x += bgspeed;

	obsX += bgspeed;

	e1X += bgspeed;

	e2X += bgspeed;

	ufox += ufospeed;

	if(level==2){
		ufox1 += ufospeed;
	}
	
}


void iDraw()
{
	iClear();
	if(screen==0){
		//name input
		iShowBMP(0, 0, "images\\username.bmp");
		if(mode == 1){
			iSetColor(255, 255, 255);
			iText(482, 330, str, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if(mode==0) iText(565, 50, "Click the username box to activate.", GLUT_BITMAP_8_BY_13);
		else iText(460, 50, "Type your username and press enter or click 'SUBMIT' to Submit.", GLUT_BITMAP_8_BY_13);
	}
	else if(screen==1){
		//home menu
		menu();
	}
	else if(screen==5){
		//about us
		iShowBMP(0, 0, "images\\aboutus.bmp");
		if(bc==1) iShowBMP2(60, 631, "images\\bc.bmp", 0);
		iSetColor(255, 255, 255);
		iText(75, 600, "Click to go back", GLUT_BITMAP_8_BY_13);
	}
	else if(screen == 11){
		//game

		//character jump
		if(charY > 5) charY -= 2;
		else charY = 5;

		//background image
		if(level==2) iShowImage(Background[0].x, Background[0].y, 1360, 768, load3);
		else iShowImage(Background[0].x, Background[0].y, 1360, 768, load1);
		if(level==2) iShowImage(Background[1].x, Background[1].y, 1360, 768, load4);
		else iShowImage(Background[1].x, Background[1].y, 1360, 768, load2);

		//background change
		if(ingame2) bgChange2();
		else if(ingame) bgChange();

		//character
		if(shoot==2) iShowImage(charX, charY, 230, 306, c2);
		else if(shoot==3) iShowImage(charX, charY, 238, 306, c3);
		else iShowImage(charX, charY, 174, 306, c1);


		if(ingame) iShowImage(630, 705, 100, 47, ps);
		else iShowImage(630, 705, 100, 47, st);
		iSetColor(255, 255, 255);
		if(ingame) iText(610, 690, "Press 'p' to pause", GLUT_BITMAP_8_BY_13);
		else iText(610, 690, "Press 's' to start", GLUT_BITMAP_8_BY_13);


		//showing obstacle and enemies
		iShowImage(obsX, 0, 147, 81, obs);
		//if(enem1) iShowImage(e1X, e1Y, 258, 231, e1);
		//if(enem2) iShowImage(e2X, e2Y, 235, 216, e2);
		if(level==2) iShowImage(e1X, e1Y, 258, 231, e11);
		else iShowImage(e1X, e1Y, 258, 231, e1);
		if(level==2) iShowImage(e2X, e2Y, 235, 216, e22);
		else iShowImage(e2X, e2Y, 235, 216, e2);
		//if(ufo) iShowImage(ufox, ufoy, 220, 133, uf);
		iShowImage(ufox, ufoy, 220, 133, uf);
		if(level == 2) iShowImage(ufox1, ufoy1, 220, 133, uf1);


		//trowing bullet to enemy 1/2
		for(int k = 0; k<indx; k++){
			if(cbullet1[k] && ingame){
				ccbullet1[k].y = 148 + charY;
				iShowBMP2(ccbullet1[k].x , ccbullet1[k].y , "images\\bullet.bmp", 0);

				ccbullet1[k].x += 20;
				if (ccbullet1[k].x  >= 1360){
					cbullet1[k] = 0;
					ccbullet1[k].x = 225;
				}
			}
		}

		//checking bullet collision with enemy 1
		for(int k = 0; k<indx; k++){
			if((ccbullet1[k].x >= (e1X+97)) && (ccbullet1[k].x <= (e1X+235)) && ccbullet1[k].y<=228 && ingame && e1X<1360 && e1X>0){
					//if(point1) score += 5;
					score += 5;
					ccbullet1[k].x = 225;
					cbullet1[k] = 0;
					//enem1 = false;
					//point1 = false;
					int zz = e1X + 1500;
					e1X = zz;
					//e1bx = 1180 - 5;
			}
		}

		//checking bullet collision with enemy 2
		for(int k = 0; k<indx; k++){
			if((ccbullet1[k].x >= (e2X+97)) && (ccbullet1[k].x <= (e2X+235)) && ccbullet1[k].y<=228 && ingame && e2X<1360 && e2X>0){
					//if(point3) score += 5;
					score += 5;
					ccbullet1[k].x = 225;
					cbullet1[k] = false;
					//enem2 = false;
					//point3 = false;
					int zz = e2X + 1700;
					e2X = zz;
					//e1bx = 1100-5;
			}
		}

		//enemy 1 reverse shooting & collision
		if(ingame){
			if(e1X>=350 && e1X<=1180){
				e1s = true;
				//e1bx -= enemyBulletSpeed;
			}

			if(e1X<=1180){
				start1 = true;
			}

			if(e1bx<=155 && charY<=e1by){
				if(hit1){
					healthX -= reduceLife2;
				}
				e1s = false;
				hit1 = false;
			}

			if(e1bx<=0){
				e1bx = e1X - 5;
				e1s = true;
				hit1 = true;
				start1 = false;
			}

			if(level==2) iSetColor(222, 70, 54);
			else iSetColor(240, 190, 44);
			if(e1s) iFilledCircle(e1bx, e1by, 5, 10);	
			e1bx -= enemyBulletSpeed;
		}

		//enemy 2 reverse shooting  & collision
		if(ingame){
			if(e2X>=350 && e2X<=1100){
				e2s = true;
				//e2bx -= enemyBulletSpeed;
			}

			if(e2X<=1100){
				start2 = true;
			}

			if(e2bx<=155 && charY<=e2by){
				if(hit2){
					healthX -= reduceLife2;
				}
				e2s = false;
				hit2 = false;
			}

			if(e2bx<=0){
				e2bx = e2X - 5;
				e2s = true;
				hit2 = true;
				start2 = false;
			}
			
			if(level==2) iSetColor(222, 70, 54);
			else iSetColor(240, 190, 44);
			if(e2s) iFilledCircle(e2bx, e2by, 5, 10);	
			e2bx -= enemyBulletSpeed;
		}

		//enemy 1 reverse shoot collision
		/*if((e1bx <= 155) && (e1by<=charY+32) && ingame && enem1){
			if(hit1){
				healthX -= 5;
				iText(610, 400, "Press 's' to start", GLUT_BITMAP_8_BY_13);
			}
			e1s = false;
			hit1 = false;
		}

		//enemy 2 reverse shoot collision
		if((e2bx <= 155) && (e2by<=charY+32) && ingame && enem2){
			if(hit3){
				healthX -= 5;
				iText(610, 400, "Press 's' to start", GLUT_BITMAP_8_BY_13);
			}
			e2s = false;
			hit3 = false;
		}*/

		//throwing upper bullet
		for(int k = 0; k<indx1; k++){
			if(cbullet2[k] && ingame){
				if(bcnt==1) shb = b1;
				else if(bcnt==2) shb = b2;
				else if(bcnt==3) shb = b3;
				else if(bcnt==4) shb = b4;
				else shb = b5;
				//iShowBMP2(cbullet2X, cbullet2Y, "images\\bullet3.bmp", 0);
				iShowImage(ccbullet2[k].x, ccbullet2[k].y, 30, 31, shb);
				bcnt++;
				if(bcnt==6) bcnt = 1;

				ccbullet2[k].x += 8;
				ccbullet2[k].y += 6;
				if (ccbullet2[k].y >= 768){
					cbullet2[k] = 0;
					ccbullet2[k].x = 197;
					ccbullet2[k].y = 219 + charY;
				}	
			}
		}

		//showing ufo bullet
		if(ingame && ufox<1450 && ufox>-100){
			if(ufosy<=0){
				ufosx = ufox + 91;
				ufosy = ufoy + 40;
				ufos = true;
				hit2 = true;
			}
			if(counter%3==0) {
				iSetColor(255, 141, 145);
				if(ufos) iFilledCircle(ufosx, ufosy, 5, 10);
				counter = 1;
			}
			counter++;
			
			ufosx -= 9;
			ufosy -= 4;
		}

		if(level==2){
			if(ingame && ufox1<1550 && ufox1>-100){
				if(ufosy1<=0){
					ufosx1 = ufox1 + 91;
					ufosy1 = ufoy1 + 40;
					ufos1 = true;
					hit4 = true;
				}
				if(counter1%3==0) {
					iSetColor(255, 141, 145);
					if(ufos1) iFilledCircle(ufosx1, ufosy1, 5, 10);
					counter1 = 1;
				
				}
				counter1++;
				ufosx1 -= 9;
				ufosy1 -= 4;
			}
		}

		//ufo reverse shoot collision
		if((ufosx >= 59) && (ufosx <= 154) && (ufosy >= charY+34) && (ufosy <= charY+267) && ingame){
				if(hit2) healthX -= 5;
				ufos = false;
				hit2 = false;
		}

		if(level==2){
			if((ufosx1 >= 59) && (ufosx1 <= 154) && (ufosy1 >= charY+34) && (ufosy1 <= charY+267) && ingame){
					if(hit4) healthX -= 5;
					ufos1 = false;
					hit4 = false;
			}
		}

		//checking bullet collision with ufo
		for(int k = 0; k<indx1; k++){
			if((ccbullet2[k].x >= (ufox+17)) && (ccbullet2[k].x <= (ufox+204)) && (ccbullet2[k].y >= (ufoy+18)) && (ccbullet2[k].y <= (ufox+120)) && ingame && ufox<1360 && ufox>0 && ccbullet2[k].y<620){
					//if(point2) score += 5;
					score += 5;
					ccbullet2[k].x = 197;
					ccbullet2[k].y = 219 + charY;
					cbullet2[k] = 0;
					//ufo = false;
					//point2 = false;
					int zz = ufox + 1360;
					ufox = zz;
			}
		}
		/*else if((cbullet2X >= (ufox+64)) && (cbullet2X <= (ufox+164)) && (cbullet2Y >= (ufoy+69)) && (cbullet2Y <= (ufox+115)) && ingame && ufox<1360 && ufox>0){
				if(point2) score += 5;
				cbullet2X = 197;
				cbullet2Y = 219 + charY;
				cbullet2 = false;
				ufo = false;
				point2 = false;
		}
		else if((cbullet2X >= (ufox+77)) && (cbullet2X <= (ufox+167)) && (cbullet2Y >= (ufoy+46)) && (cbullet2Y <= (ufox+63)) && ingame && ufox<1360 && ufox>0){
				if(point2) score += 5;
				cbullet2X = 197;
				cbullet2Y = 219 + charY;
				cbullet2 = false;
				ufo = false;
				point2 = false;
		}*/

		if(level==2){
			for(int k = 0; k<indx1; k++){
				if((ccbullet2[k].x >= (ufox1+17)) && (ccbullet2[k].x <= (ufox1+204)) && (ccbullet2[k].y >= (ufoy1+18)) && (ccbullet2[k].y <= (ufox1+120)) && ingame && ufox1<1360 && ufox1>0 && ccbullet2[k].y<620){
						//if(point2) score += 5;
						score += 5;
						ccbullet2[k].x = 197;
						ccbullet2[k].y = 219 + charY;
						cbullet2[k] = 0;
						//ufo = false;
						//point2 = false;
						int zz = ufox1 + 1360;
						ufox1 = zz;
				}
			}
		}

		//healthbar and score
		iShowImage(10, 670, 350, 89, hbar);
		iSetColor(26, 245, 10);
		if(healthX <= 128) iSetColor(255, 0, 0);
		iFilledRectangle(27, 692, healthX, 27);
		iShowImage(1145, 680, 189, 80, scoreB);
		char  buf[BUFSIZ];
		sprintf(buf, "%d", score);
		iSetColor(26, 245, 10);
		iText(1162, 696, buf, GLUT_BITMAP_TIMES_ROMAN_24);

		//checking crash with obstacle
		if(obsX<=124 && obsX>=20 && charY<=68 && obsCrash==false){
			obsCrash = true;
			healthX -= reduceLife;
			obsMsg = true;
		}

		if(obsMsg){
			iShowImage(135, 10, 120, 68, obsMsgImg);
			if(obsCnt==0){
				obsMsg = false;
				obsCnt = 5;
			}
			obsCnt--;
		}

		//game end
		if(healthX <= 0){
			score2 = score;
			FILE *fp = fopen("score.txt", "a");
			fprintf(fp, "%s %d\n", name, score);
			fclose(fp);
			score = 0;
			healthX = 320;
			e1X=3050;
			e1X=2500;
			reduceLife = 3;
			reduceLife2 = 2;
			bgspeed = 5;
			enemyBulletSpeed = 12;
			ufospeed = 3;
			ingame = false;
			level = 1;
			setBg();
			screen = 13;
		}

		//new level
		if(score>=90 && level==1){
			ingame = false;
			iShowImage(0, 0, 1360, 768, loadd);
			iSetColor(255, 113, 185);
			iFilledRectangle(407, 382, loadX, 37);
			loadX += 2;
			if(loadX>=528){
				setBg();
				level = 2;
				e1X=3050;
				e1X=2500;
				ufox = 1650;
				ufox1 = 2080;
				loadX = 0;
				reduceLife = 5;
				reduceLife2 = 3;
				bgspeed = 8;
				enemyBulletSpeed = 13;
				ufospeed = 5;
				ingame = true;
			}
		}
	}
	else if(screen == 3){
		//instructions
		iShowImage(0, 0, 1360, 768, ht);
		if(bc==1) iShowBMP2(60, 631, "images\\bc.bmp", 0);
		iSetColor(255, 255, 255);
		iText(75, 600, "Click to go back", GLUT_BITMAP_8_BY_13);
	}
	else if(screen == 2){
		//top scores
		drawBG();
		topscore();
	}
	else if(screen == 12){
		//game loading
		iShowImage(0, 0, 1360, 768, load);
		iSetColor(255, 113, 185);
		iFilledRectangle(407, 382, loadX, 37);
		loadX += 8;
		if(loadX>=528){
			screen = 11;
			loadX = 0;
		}
	}
	else if(screen == 13){
		//game over scene
		iSetColor(0, 0, 0);
		iShowImage(0, 0, 1360, 768, over);
		char  buf[BUFSIZ];
		sprintf(buf, "%d", score2);
		iText(668, 347, buf, GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 255);
		iText(115, 25, "Press 'b'", GLUT_BITMAP_8_BY_13);
		iText(1180, 25, "Press 'h'", GLUT_BITMAP_8_BY_13);
	}
}

void iPassiveMouse(int x, int y)
{
	if(screen == 1){
		//button pop-up
		if(validPoint(616, 35, 731, 106, x, y)){
				p = 1;
		}
		else p = 0;

		if(validPoint(98, 35, 215, 106, x, y)){
				sc = 1;
		}
		else sc = 0;

		if(validPoint(359, 35, 475, 106, x, y)){
				ins = 1;
		}
		else ins = 0;

		if(validPoint(874, 35, 990, 106, x, y)){
				ab = 1;
		}
		else ab = 0;

		if(validPoint(1131, 35, 1246, 106, x, y)){
				ex = 1;
		}
		else ex = 0;
	}
	else if(screen==5){
		//button pop-up
		if(validPoint(84, 634, 199, 704, x, y)){
				bc = 1;
		}
		else bc = 0;
	}
	else if(screen==3){
		//button pop-up
		if(validPoint(84, 634, 199, 704, x, y)){
				bc = 1;
		}
		else bc = 0;
	}
	else if(screen==2){
		//button pop-up
		if(validPoint(84, 634, 199, 704, x, y)){
				bc = 1;
		}
		else bc = 0;
	}
	printf("x = %d, y= %d\n", x, y);
}


/*
 function iMouseMove() is called when the user presses and drags the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouseMove(int mx, int my)
{
	//printf("x = %d, y= %d\n", mx, my);
	//place your codes here
}

/*
 function iMouse() is called when the user presses/releases the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouse(int button, int state, int mx, int my)
{
	if(screen==11){
		//ingame
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ingame){
			shoot = 2;
			PlaySound("lower.wav", NULL, SND_ASYNC);
			cbullet1[indx] = 1;
			indx++;
			if(indx>19) indx = 0;
		}
		else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && ingame){
			shoot = 3;
			PlaySound("upper.wav", NULL, SND_ASYNC);
			cbullet2[indx1] = 1;
			indx1++;
			if(indx1>6) indx1 = 0;
		}
		else{
			shoot = 0;
			//PlaySound("judyrex.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}
	else if(screen==0){
		//name input
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(validPoint(472, 294, 915, 374, mx, my) && mode == 0){
				clickSound();
				mode = 1;
			}
		}

		//name submit
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if(validPoint(594, 193, 799, 242, mx, my)){
				clickSound();
				screen = 1;
				mode = 0;
				if(strlen(str) >= 1){
					strcpy(str2, str);
					strcpy(name, str);
				}
				strcat(str2, "!");
			}
		}
	}
	else if(screen==1){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(validPoint(1131, 35, 1246, 106, mx, my)){
				clickSound();
				click = true;
				exit(0);
			}
			if(validPoint(874, 35, 990, 106, mx, my)){
				clickSound();
				screen = 5;
			}
			if(validPoint(616, 35, 731, 106, mx, my)){
				clickSound();
				introSound.stop();
				ingameSound();
				screen = 12;
			}
			if(validPoint(37, 680, 81, 722, mx, my)){
				if(mute){
					//PlaySound("judyrex.wav", NULL, SND_LOOP | SND_ASYNC);
					introSound.resume();
					mute = false;
				}
				else{
					//PlaySound("click.wav", NULL, SND_ASYNC);
					introSound.pause();
					mute = true;
				}
			}
			if(validPoint(359, 35, 475, 106, mx, my)){
				clickSound();
				screen = 3;
			}
			if(validPoint(98, 35, 215, 106, mx, my)){
				clickSound();
				screen = 2;
			}
		}
	}
	else if(screen==5){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(validPoint(84, 634, 199, 704, mx, my)){
				clickSound();
				screen = 1;
			}
		}
	}
	else if(screen==3){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(validPoint(84, 634, 199, 704, mx, my)){
				clickSound();
				screen = 1;
			}
		}
	}
	else if(screen==2){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(validPoint(84, 634, 199, 704, mx, my)){
				clickSound();
				screen = 1;
			}
		}
	}
	else if(screen==13){
		if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
			if(validPoint(90, 205, 50, 122, mx, my)){
				clickSound();
				screen = 1;
			}

			if(validPoint(1157, 1270, 50, 122, mx, my)){
				clickSound();
				screen = 2;
			}
		}
	}
}

/*
 function iKeyboard() is called whenever the user hits a key in keyboard.
 key- holds the ASCII value of the key pressed.
 */
void iKeyboard(unsigned char key)
{
	if(screen==0){
		int i;
		if(mode == 1){
			if(key == '\r'){
				screen = 1;
				mode = 0;
				strcpy(str2, str);
				strcpy(name, str);
				strcat(str2, "!");
				for(i = 0; i < len; i++)
					str[i] = 0;
				len = 0;
			}
			else{
				str[len] = key;
				len++;
			}
		}
		if(key == 'x'){
			exit(0);
		}
	}
	if(screen==1){
		if(key == 'x'){
			exit(0);
		}
		if(key == 'p'){
			clickSound();
			screen = 12;
		}
		if(key == 'f'){
			clickSound();
			screen = 5;
		}
		if(key == 'i'){
			clickSound();
			screen = 3;
		}
		if(key == 'h'){
			clickSound();
			screen = 2;
		}
	}
	if(screen==5){
		if(key == 'b'){
			clickSound();
			screen = 1;
		}
	}
	if(screen==11){
		if(key == 'b'){
			screen = 1;
			ingame = false;
		}
		if(key == 'p'){
			clickSound();
			gameSound.pause();
			ingame = false;
		}
		if(key == 's'){
			clickSound();
			gameSound.resume();
			ingame = true;
		}

		if((key == 'w' || key == 'd') && ingame){
			if(key == 'd'){
				shoot = 2;
				cbullet1[indx] = 1;
			}
			else{
				shoot = 3;
				cbullet2[indx1] = 1;
			}
		}
		else shoot = 0;

		if (key == ' ' && ingame){
			charY += 160;
			if(charY >= 165) charY = 165;
		}
		else charY = 5;
	}
	if(screen==2){
		if(key == 'b'){
			clickSound();
			screen = 1;
		}
	}
	if(screen==3){
		if(key == 'b'){
			clickSound();
			screen = 1;
		}
	}
	if(screen==13){
		if(key == 'b'){
			clickSound();
			gameSound.stop();
			introGameSound();
			screen = 1;
		}
		if(key == 'h'){
			clickSound();
			gameSound.stop();
			introGameSound();
			screen = 2;
		}
	}
}


/*
 function iSpecialKeyboard() is called whenver user hits special keys like-
 function keys, home, end, pg up, pg down, arraows etc. you have to use
 appropriate constants to detect them. A list is:
 GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
 GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
 GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
 GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
 */
void iSpecialKeyboard(unsigned char key)
{
	if(screen==11) {
		if (key == GLUT_KEY_RIGHT){
			ingame2 = true;
		}
		else ingame2 = false;
	}
}



int main()
{
	setBg();
	ini2();
	ini3();
	introGameSound();
	//ingameSound();
	//if(musicOn) PlaySound("judyrex.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(1360, 768, "Judyrex");
	loadImages();
	iStart();

	return 0;
}