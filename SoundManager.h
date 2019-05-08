#pragma once

#include <Windows.h>
#include <graphics.h>
#pragma comment(lib,"Winmm.lib")

enum Music {
	START, SHOOT, BK,
	BIN, MOVE, ENEMY_DIE,
	PLAYER_DIE
};

class SoundManager {
public:
	SoundManager() {/*
		mciSendString(_T("open .\\res\\music\\bk_sound.mp3"), NULL, 0, NULL);
		mciSendString(_T("play .\\res\\music\\bk_sound.mp3 repeat"), NULL, 0, NULL);*/

		mciSendString(_T("open .\\res\\music\\start.wav alias start"), NULL, 0, NULL);
		mciSendString(_T("open .\\res\\music\\shoot.wav alias shoot"), NULL, 0, NULL);
		mciSendString(_T("open .\\res\\music\\bin.wav alias bin"), NULL, 0, NULL);
		mciSendString(_T("open .\\res\\music\\player_move.wav alias move"), NULL, 0, NULL);
		mciSendString(_T("open .\\res\\music\\enemy-bomb.wav alias enemy_die"), NULL, 0, NULL);
		mciSendString(_T("open .\\res\\music\\player_bomb.wav alias player_die"), NULL, 0, NULL);

	}
	~SoundManager() {
		mciSendString(_T("close all"), NULL, 0, NULL);
	}

inline
void playMusic(Music m) {
	if (m == BK) {
		mciSendString(_T("play bk"), NULL, 0, NULL);
	} else if (m == SHOOT) {
		mciSendString(_T("close shoot"), NULL, 0, NULL);
		mciSendString(_T("open .\\res\\music\\shoot.wav alias shoot"), NULL, 0, NULL);
		mciSendString(_T("play shoot"), NULL, 0, NULL);
	} else if (m == BIN) {
		mciSendString(_T("close bin"), NULL, 0, NULL);
		mciSendString(_T("open .\\res\\music\\bin.wav alias bin"), NULL, 0, NULL);
		mciSendString(_T("play bin"), NULL, 0, NULL);
	} else if (m == START) {
		mciSendString(_T("play start"), NULL, 0, NULL);
	} else if (m == MOVE) {
		mciSendString(_T("close move"), NULL, 0, NULL);
		mciSendString(_T("open .\\res\\music\\player_move.wav alias move"), NULL, 0, NULL);
		mciSendString(_T("play move"), NULL, 0, NULL);
	} else if (m == ENEMY_DIE) {
		mciSendString(_T("close enemy_die"), NULL, 0, NULL);
		mciSendString(_T("open .\\res\\music\\enemy-bomb.wav alias enemy_die"), NULL, 0, NULL);
		mciSendString(_T("play enemy_die"), NULL, 0, NULL);
	} else if (m == PLAYER_DIE) {
		mciSendString(_T("play player_die"), NULL, 0, NULL);
	}
}
};