#pragma once
#include <cmath>
#include <allegro5/allegro.h>
#include "AssetManager.h"
#include <iostream>
class Button {

public:
	enum STATUS { DEFAULT, PRESSED, HOVER };

private:

	int x;
	int y;
	int width;
	int height;
	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *hoverOverlay;
	ALLEGRO_BITMAP *pressedOverlay;
	ALLEGRO_BITMAP *disabledOverlay;
	STATUS status;
	bool* enabled;

public:
	Button();
	~Button();

	bool contains(double x, double y);
	int getX() { return x; }
	int getY() { return y; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	void setX(int x) { this->x = x; };
	void setY(int y) { this->y = y; }
	void setWidth(int width) { this->width = width; };
	void setHeight(int height) { this->height = height; }
	void setEnabled(bool* cond) {
		enabled = cond;
		std::cout << *cond;
	}
	bool getEnabled() {
		return *enabled;
	}
	STATUS getStatus() {
		return status;
	}

	void setStatus(STATUS status) {
		this->status = status;
	}

	void set_Default_Pressed_Hover_Images(ALLEGRO_BITMAP *image) {
		this->image = image;
		hoverOverlay = AssetManager::getTexture("hover_button_overlay");
		pressedOverlay = AssetManager::getTexture("pressed_button_overlay");
		disabledOverlay = AssetManager::getTexture("disabled_button_overlay");
	}

	ALLEGRO_BITMAP* getImage() {
		return image;
	}

	ALLEGRO_BITMAP* getHoverOverlay() {
		return hoverOverlay;
	}

	ALLEGRO_BITMAP* getPressedOverlay() {
		return pressedOverlay;
	}

	ALLEGRO_BITMAP* getOverlay() {
		const bool cond = false;
		if (enabled!=NULL && *enabled==cond) {
			return disabledOverlay;
		}

		switch (status) {
		case PRESSED:
			return pressedOverlay;
		case HOVER:
			return hoverOverlay;
		case DEFAULT:
			return NULL;
		}
	}




};
