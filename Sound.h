#ifndef _SOUND_
#define _SOUND_

#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Winmm.lib")

enum Music {
	START, SHOOT, BK,
	BIN, MOVE, ENEMY_DIE,
	PLAYER_DIE
};

class Sound {
public:
	static void play(Music m);
};


#endif // !_SOUND_
