#ifndef TOPSCORE_H_INCLUDED
#define TOPSCORE_H_INCLUDED


#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;
#include "variable.h"

void drawBG(){
	iShowImage(0, 0, 1360, 768, ts);
	if(bc==1) iShowBMP2(60, 631, "images\\bc.bmp", 0);
	iSetColor(255, 255, 255);
	iText(75, 600, "Click to go back", GLUT_BITMAP_8_BY_13);
}

//top score
void topscore(){
	vector<string> name;
	vector<int> score;
	char s1[100];
	int st, n, i;
	string s;
	FILE *fp1 = fopen("score.txt", "r");
	while(fscanf(fp1, "%s %d", &s1, &st) != EOF){
		name.push_back(s1);
		score.push_back(st);
    }
	n = score.size();
	int c, d, swap;
	string ss;
	for (c = 0 ; c < n - 1; c++){
        for (d = 0 ; d < n-1; d++){
            if (score[d] < score[d+1]){
                swap       = score[d];
                score[d]   = score[d+1];
                score[d+1] = swap;
				ss       = name[d];
                name[d]   = name[d+1];
                name[d+1] = ss;
            }
        }
    }
	if(n>14) n = 14;
	int nx = 350, sx = 860;
	for(i=0; i<n; i++){
		char  buf[BUFSIZ];
		sprintf(buf, "%d", score[i]);
		char char_array[100];
		strcpy(char_array, name[i].c_str());
		iText(sx, sy, buf, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(nx, sy, char_array, GLUT_BITMAP_TIMES_ROMAN_24);
		sy -= 30;
		if(i==n-1) sy = 580;
	}
	fclose(fp1);
}

#endif // !TOPSCORE_H_INCLUDED
