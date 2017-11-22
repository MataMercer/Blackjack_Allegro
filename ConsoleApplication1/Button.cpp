#include "stdafx.h"
#include "Button.h"



Button::Button()
{

	enabled = NULL;
}


Button::~Button()
{
}

bool Button::contains(double x, double y) {
	int center_x = this->x + width / 2;
	int center_y = this->y + height / 2;

	double diffx = abs(center_x - x);
	double diffy = abs(center_y - y);

	double limitx = width / 2;
	double limity = height / 2;

	if (diffx <= limitx && diffy <= limity) {
		return true;
	}
	else {
		return false;
	}
}

