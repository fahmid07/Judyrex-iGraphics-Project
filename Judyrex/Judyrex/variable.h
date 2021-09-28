#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED


int level = 1;
int b1, b2, b3, b4, b5;
char str[100], str2[100]="Unknown";
int len;
int mode;
bool start1 = false;
bool start2 = false;
bool intro = false;
bool gamesound = true;
bool musicOn = false;
bool click = false;
bool mute = false;
bool obsMsg = false;
int bgspeed = 5;
int enemyBulletSpeed = 10;
int ufospeed = 3;
int reduceLife = 3;
int reduceLife2 = 2;
bool ingame = false;
bool ingame2 = false;
int screen = 0;
int p, ins, sc, ab, ex, bc;
char name[100]="Unknown";
int addF = 0;
int score = 0;
int score2 = 0;
int loadX = 0;
int shoot = 0;
int obsX = 2050;
int cbullet1X = 225;
int cbullet1Y = 153;
int cbullet2X = 197;
int cbullet2Y = 224;
int cbullet1[20]={0};
int cbullet2[20]={0};
//bool cbullet2 = false;
bool obsCrash = false;
int ps;
int st;
int c1, c2, c3, charY = 5, charX = 10;
char background[2][14] = {"images\\0.png", "images\\1.png"};
int load1;
int load2;
int load3;
int load4;
int load;
int loadd;
int obsMsgImg;
int obs;
int healthX = 320;
int ts, ht;
int hbar;
int mt, sn;
int over;
int scoreB;
int obsCnt = 3;
int e1, e2;
int e11, e22;
int e1X=3050, e1Y = 0, e1bx = 1260, e1by = 143;
int e2X=2500, e2Y = 0, e2bx = 1260, e2by = 130;
bool enem1 = true, enem2 = true;
bool e1s = false;
bool e2s = false;
bool point1 = true;
bool point2 = true;
bool point3 = true;
bool point4 = true;
bool hit1 = true;
bool hit2 = true;
bool hit3 = true;
bool hit4 = true;
int uf, ufox = 1780, ufoy = 500;
bool ufo = true, ufos = true;
int uf1, ufox1 = 1980, ufoy1 = 500;
bool ufo1 = true, ufos1 = true;
int bcnt=1;
int shb;
int sy = 580;
int ufosx=10, ufosy=0;
int ufosx1=10, ufosy1=0;
int counter = 1;
int cnt = 1;
int counter1 = 1;
int cnt1 = 1;
int cnt2 = 1;

struct bgxy{
	int x;
	int y;
};

struct cCbullet1{
	int x;
	int y;
};

struct cCbullet2{
	int x;
	int y;
};

bgxy Background[2];
cCbullet1 ccbullet1[100];
int indx = 0;

cCbullet2 ccbullet2[100];
int indx1 = 0;

void ini2(){
	for(int k=0; k<100; k++){
		cbullet1[k] = 0;
		ccbullet1[k].x = 225;
	}
}

void ini3(){
	for(int k=0; k<100; k++){
		cbullet2[k] = 0;
		ccbullet2[k].x = 197;
		ccbullet2[k].y = 224;
	}
}

#endif // !VARIABLE_H_INCLUDED