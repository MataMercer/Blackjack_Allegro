#include "stdafx.h"
#include "AssetManager.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <string.h>
#include <allegro5/allegro.h>

#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <fstream>
using namespace std;

namespace AssetManager {
	static map<string, ALLEGRO_FONT *> _fonts;
	static map<string, ALLEGRO_BITMAP *> _textures;
	static ofstream _accounts_list_text_File_output;
	static ifstream _accounts_list_text_File_input;

	bool initialize() {
		map<string, int> fonts = {
			{ "small", 23 },
			{ "normal", 30 },
			{ "big", 40 }
		};



		map<string, string> textures = {
			{ "start_button", "assets/startbutton.png" },
			{ "exit_button", "assets/exitbutton.png" },
			{ "load_button", "assets/loadbutton.png" },
			{ "deal_button", "assets/dealbutton.png" },
			{ "hit_button", "assets/hitbutton.png" },
			{ "new_hand_button", "assets/newhandbutton.png" },
			{ "quit_button", "assets/quitbutton.png" },
			{ "split_button", "assets/splitbutton.png" },
			{ "stand_button", "assets/standbutton.png" },
			{ "surrender_button", "assets/surrenderbutton.png" },
			{ "100_button", "assets/100chip.png" },
			{ "250_button", "assets/250chip.png" },
			{ "500_button", "assets/500chip.png" },
			{ "1000_button", "assets/1000chip.png" },
			{ "score_panel", "assets/score_display.png"},
			

			{ "hover_button_overlay", "assets/hoverbuttonoverlay.png" },
			{ "pressed_button_overlay", "assets/pressedbuttonoverlay.png" },
			{ "disabled_button_overlay", "assets/disabledbuttonoverlay.png" },

			{ "title", "assets/title.png" },
			{ "game_background", "assets/gamebackground.png" },

			//2
			{ "2_clubs", "assets/cardpng/2_of_clubs.png" },
			{ "2_diamonds", "assets/cardpng/2_of_diamonds.png" },
			{ "2_hearts", "assets/cardpng/2_of_hearts.png" },
			{ "2_spades", "assets/cardpng/2_of_spades.png" },
			//3
			{ "3_clubs", "assets/cardpng/3_of_clubs.png" },
			{ "3_diamonds", "assets/cardpng/3_of_diamonds.png" },
			{ "3_hearts", "assets/cardpng/3_of_hearts.png" },
			{ "3_spades", "assets/cardpng/3_of_spades.png" },
			//4
			{ "4_clubs", "assets/cardpng/4_of_clubs.png" },
			{ "4_diamonds", "assets/cardpng/4_of_diamonds.png" },
			{ "4_hearts", "assets/cardpng/4_of_hearts.png" },
			{ "4_spades", "assets/cardpng/4_of_spades.png" },
			//5
			{ "5_clubs", "assets/cardpng/5_of_clubs.png" },
			{ "5_diamonds", "assets/cardpng/5_of_diamonds.png" },
			{ "5_hearts", "assets/cardpng/5_of_hearts.png" },
			{ "5_spades", "assets/cardpng/5_of_spades.png" },
			//6
			{ "6_clubs", "assets/cardpng/6_of_clubs.png" },
			{ "6_diamonds", "assets/cardpng/6_of_diamonds.png" },
			{ "6_hearts", "assets/cardpng/6_of_hearts.png" },
			{ "6_spades", "assets/cardpng/6_of_spades.png" },
			//7
			{ "7_clubs", "assets/cardpng/7_of_clubs.png" },
			{ "7_diamonds", "assets/cardpng/7_of_diamonds.png" },
			{ "7_hearts", "assets/cardpng/7_of_hearts.png" },
			{ "7_spades", "assets/cardpng/7_of_spades.png" },
			//8
			{ "8_clubs", "assets/cardpng/8_of_clubs.png" },
			{ "8_diamonds", "assets/cardpng/8_of_diamonds.png" },
			{ "8_hearts", "assets/cardpng/8_of_hearts.png" },
			{ "8_spades", "assets/cardpng/8_of_spades.png" },
			//9
			{ "9_clubs", "assets/cardpng/9_of_clubs.png" },
			{ "9_diamonds", "assets/cardpng/9_of_diamonds.png" },
			{ "9_hearts", "assets/cardpng/9_of_hearts.png" },
			{ "9_spades", "assets/cardpng/9_of_spades.png" },
			//jacks
			{ "jack_clubs", "assets/cardpng/jack_of_clubs2.png" },
			{ "jack_diamonds", "assets/cardpng/jack_of_diamonds2.png" },
			{ "jack_hearts", "assets/cardpng/jack_of_hearts2.png" },
			{ "jack_spades", "assets/cardpng/jack_of_spades2.png" },
			//kings
			{ "king_clubs", "assets/cardpng/king_of_clubs2.png" },
			{ "king_diamonds", "assets/cardpng/king_of_diamonds2.png" },
			{ "king_hearts", "assets/cardpng/king_of_hearts2.png" },
			{ "king_spades", "assets/cardpng/king_of_spades2.png" },
			//queens
			{ "queen_clubs", "assets/cardpng/queen_of_clubs2.png" },
			{ "queen_diamonds", "assets/cardpng/queen_of_diamonds2.png" },
			{ "queen_hearts", "assets/cardpng/queen_of_hearts2.png" },
			{ "queen_spades", "assets/cardpng/queen_of_spades2.png" },
			//aces
			{ "ace_clubs", "assets/cardpng/ace_of_clubs.png" },
			{ "ace_diamonds", "assets/cardpng/ace_of_diamonds.png" },
			{ "ace_hearts", "assets/cardpng/ace_of_hearts.png" },
			{ "ace_spades", "assets/cardpng/ace_of_spades.png" },

			{ "facedowncard", "assets/cardpng/facedown.png" },
			{ "divider", "assets/cardpng/divider.png"}



		};

		for (pair<string, int> font : fonts) {
			_fonts[font.first] = al_load_font("assets/arial.ttf", font.second, NULL);
			if (_fonts[font.first] == NULL) {
				return false;
			}
		}



		for (pair<string, string> texture : textures) {
			_textures[texture.first] = al_load_bitmap(texture.second.c_str());
			//al_convert_mask_to_alpha(_textures[texture.first], al_map_rgb(255, 0, 255));
			if (_textures[texture.first] == NULL) {
				return false;
			}
		}


		_accounts_list_text_File_output.open("accounts_list_text_file.txt");
		_accounts_list_text_File_input.open("accounts_list_text_file.txt");

		return true;
	}

	ALLEGRO_FONT *getFont(string font) {
		return _fonts[font];
	}

	ALLEGRO_BITMAP *getTexture(string texture) {
		return _textures[texture];
	}

	void updateAccount(string accountNumber) {
		ostringstream text;
		text << _accounts_list_text_File_input.rdbuf();
		string str = text.str();


	}

	int readAccount(string accountNumber) {

		while (!_accounts_list_text_File_input.eof())
		{
			string accountName = "";
			_accounts_list_text_File_input >> accountName;
			int balance = 0;
			_accounts_list_text_File_input >> balance;
			if (accountName == accountNumber) {
				return balance;
			}


		}

		return 0;
	}

	void destroy() {
		for (pair<string, ALLEGRO_FONT *> font : _fonts) {
			al_destroy_font(font.second);
		}

		for (pair<string, ALLEGRO_BITMAP *> texture : _textures) {
			al_destroy_bitmap(texture.second);
		}

		_fonts.clear();
		_textures.clear();
		_accounts_list_text_File_output.close();
		_accounts_list_text_File_input.close();
	}
};