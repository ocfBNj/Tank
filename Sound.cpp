#include "Sound.h"

void Sound::init() {
	mciSendString(_T("open ./res/music/start.wav alias start"), NULL, 0, NULL);
	mciSendString(_T("open ./res/music/shoot.wav alias shoot"), NULL, 0, NULL);
	mciSendString(_T("open ./res/music/bk_sound.mp3 alias bk"), NULL, 0, NULL);
	mciSendString(_T("open ./res/music/bin.wav alias bin"), NULL, 0, NULL);
	mciSendString(_T("open ./res/music/player_move.wav alias player_move"), NULL, 0, NULL);
	mciSendString(_T("open ./res/music/enemy-bomb.wav alias enemy_die"), NULL, 0, NULL);
	mciSendString(_T("open ./res/music/player_bomb.wav alias player_die"), NULL, 0, NULL);

}

void Sound::play(Music m) {
	switch (m) {
	case START:
		mciSendString(_T("play start from 0"), NULL, 0, NULL);
		break;
	case SHOOT:
		mciSendString(_T("play shoot from 0"), NULL, 0, NULL);
		break;
	case BK:
		mciSendString(_T("play bk repeat"), NULL, 0, NULL);
		break;
	case BIN:
		mciSendString(_T("play bin from 0"), NULL, 0, NULL);
		break;
	case MOVE:
		mciSendString(_T("play player_move from 0"), NULL, 0, NULL);
		break;
	case ENEMY_DIE:
		mciSendString(_T("play enemy_die from 0"), NULL, 0, NULL);
		break;
	case PLAYER_DIE:
		mciSendString(_T("play player_die from 0"), NULL, 0, NULL);
		break;
	default:
		break;
	}

}

void Sound::pauseMove(bool status) {
	if (!status)
		mciSendString(_T("play player_move from 0"), NULL, 0, NULL);
	else
		mciSendString(_T("pause move"), NULL, 0, NULL);
}
