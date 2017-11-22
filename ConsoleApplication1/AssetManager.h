#pragma once
#include <allegro5/allegro.h>
#include <iostream>
#include <list>
#include <map>
#include <allegro5/allegro_font.h>



namespace AssetManager {
	bool initialize();

	ALLEGRO_FONT *getFont(std::string font);
	ALLEGRO_BITMAP *getTexture(std::string texture);


	void destroy();
};
