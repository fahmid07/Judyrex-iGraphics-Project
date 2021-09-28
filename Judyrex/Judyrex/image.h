#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "variable.h"

void loadImages(){
	//loading images
	load1 = iLoadImage(background[0]);
	load2 = iLoadImage(background[1]);
	load3 = iLoadImage("images\\00.png");
	load4 = iLoadImage("images\\001.png");
	c1 = iLoadImage("images\\c1.png");
	c2 = iLoadImage("images\\c2.png");
	c3 = iLoadImage("images\\c3.png");
	ps = iLoadImage("images\\pause.png");
	st = iLoadImage("images\\start.png");
	obs = iLoadImage("images\\obstacle.png");
	load = iLoadImage("images\\load.png");
	loadd = iLoadImage("images\\load1.png");
	ts = iLoadImage("images\\ts.png");
	ht = iLoadImage("images\\htplay.png");
	hbar = iLoadImage("images\\health.png");
	mt = iLoadImage("images\\mute.png");
	sn = iLoadImage("images\\sound.png");
	scoreB = iLoadImage("images\\scoreB.png");
	e1 = iLoadImage("images\\e1.png");
	e2 = iLoadImage("images\\e2.png");
	e11 = iLoadImage("images\\e11.png");
	e22 = iLoadImage("images\\e22.png");
	uf = iLoadImage("images\\ufo.png");
	uf1 = iLoadImage("images\\ufo1.png");
	b1 = iLoadImage("images\\11.png");
	b2 = iLoadImage("images\\2.png");
	b3 = iLoadImage("images\\3.png");
	b4 = iLoadImage("images\\4.png");
	b5 = iLoadImage("images\\5.png");
	obsMsgImg = iLoadImage("images\\bam.png");
	over = iLoadImage("images\\over.png");
}

#endif // !IMAGE_H_INCLUDED