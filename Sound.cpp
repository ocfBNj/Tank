#include "Sound.h"

void Sound::play(Music m) {
	if (m == BK) {
		//mciSendString(_T("play .\\res\\music\\bk_sound.mp3"), NULL, 0, NULL);
	} else if (m == SHOOT) {
		//mciSendString(_T("close .\\res\\music\\shoot.wav"), NULL, 0, NULL);
		//mciSendString(_T("play .\\res\\music\\shoot.wav"), NULL, 0, NULL);
		PlaySound(_T(".\\res\\music\\shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
	} /*else if (m == BIN) {
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
	}*/

}
