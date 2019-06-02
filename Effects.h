#pragma once

#include "struct.h"

class Effects {
public:
	Effects();
	void makeEffects(int x, int y);
	bool change();
private:
	IMAGE blast[3];
	int cur;
};

