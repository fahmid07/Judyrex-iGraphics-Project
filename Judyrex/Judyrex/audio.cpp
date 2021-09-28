#include<iostream> 
using namespace std;
#include<string>
#include<Windows.h>

class audio{
	int id;
public:
	static int x;
	string fileName;

	audio(){
		id = x;
		++x;
	}
	void load(){
		string st = "open \"";
		st += fileName;
		st += "\" type mpegvideo alias mp3";
		st += to_string((long long)id);

		mciSendString(st.c_str(), NULL, 0, NULL);
	}

	void play(int s = -1, int e = -1)
	{
		if(s == -1) s =0;
		string st = "play mp3";
		st += to_string((long long)id);
		st += " from ";
		st += to_string((long long)s*1000);

		if(e != -1){
			st += " to ";
			st += to_string((long long)e*1000);
		}

		mciSendString(st.c_str(), NULL, 0, NULL);
	}

	void resume(){
		string st = "resume mp3";
		st += to_string((long long) id);

		mciSendString((char *)st.c_str(), NULL, 0, NULL);
	}

	void pause()
	{
		string st = "pause mp3";
		st += to_string((long long) id);

		mciSendString((char *)st.c_str(), NULL, 0, NULL);
	}

	void stop(){
		string st = "close mp3";
		st += to_string((long long) id);

		mciSendString((char *)st.c_str(), NULL, 0, NULL);
	}

	void set_volume(int v = 50){
		string st = "setaudio mp3";
		st += to_string((long long) id);
		st += " volume to ";
		st += to_string((long long) v);

		mciSendString((char *)st.c_str(), NULL, 0, NULL);
	}
};
int audio::x = 0;

//from where I got this
//https://docs.microsoft.com/en-us/previous-versions/dd757161(v%3Dvs.85)
//https://www.codespeedy.com/play-a-part-of-an-mp3-file-in-cpp/
