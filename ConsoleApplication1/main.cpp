// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <cmath>
#include "Button.h"
#include "BlackJack.h"
#include "AssetManager.h"
#include "Panel.h"
#include <vector>

//constants (mostly sizes) 
const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int BUTTON_HEIGHT = 64;
const int BUTTON_WIDTH = 128;
const int CARD_WIDTH = 90;
const int CARD_HEIGHT = 140;
const int BUTTON_WIDTH_GAME_UI = 96;
const int BUTTON_HEIGHT_GAME_UI = 48;
const int SCORE_PANEL_WIDTH = SCREEN_W / 3;
const int SCORE_PANEL_HEIGHT = 96;

using namespace std;

//STATE used for deciding what to display and ask for input in the game loop. aka organizes the game loop.
enum STATE { TITLE, PLAYING, GAMEOVER };

int main(int argc, char **argv)
{
	//declare variables 
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP  *image = NULL;
	ALLEGRO_BITMAP *title = NULL;
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_BITMAP *player_score_panel = NULL;
	ALLEGRO_BITMAP *dealer_score_panel = NULL;
	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	int state = -1;



	//initialize ui objects
	//title buttons
	Button start_button;
	start_button.setX(SCREEN_W / 2 - BUTTON_WIDTH / 2);
	start_button.setY(SCREEN_H / 2 - BUTTON_HEIGHT);
	start_button.setWidth(BUTTON_WIDTH);
	start_button.setHeight(BUTTON_HEIGHT);

	Button exit_button;
	exit_button.setX(SCREEN_W / 2 - BUTTON_WIDTH / 2);
	exit_button.setY(SCREEN_H / 2 + SCREEN_H / 16);
	exit_button.setWidth(BUTTON_WIDTH);
	exit_button.setHeight(BUTTON_HEIGHT);




	//gameplay buttons
	//initialize each button, push them to a vector, put vector in a function that sets their x positions centered on the screen.
	Button deal_button;
	deal_button.setWidth(BUTTON_WIDTH_GAME_UI);
	deal_button.setHeight(BUTTON_HEIGHT_GAME_UI);

	Button hit_button;
	hit_button.setWidth(BUTTON_WIDTH_GAME_UI);
	hit_button.setHeight(BUTTON_HEIGHT_GAME_UI);

	Button stand_button;
	stand_button.setWidth(BUTTON_WIDTH_GAME_UI);
	stand_button.setHeight(BUTTON_HEIGHT_GAME_UI);

	Button split_button;
	split_button.setWidth(BUTTON_WIDTH_GAME_UI);
	split_button.setHeight(BUTTON_HEIGHT_GAME_UI);

	Button new_hand_button;
	new_hand_button.setWidth(BUTTON_WIDTH_GAME_UI);
	new_hand_button.setHeight(BUTTON_HEIGHT_GAME_UI);

	Button surrender_button;
	surrender_button.setWidth(BUTTON_WIDTH_GAME_UI);
	surrender_button.setHeight(BUTTON_HEIGHT_GAME_UI);
	
	Button quit_button;
	quit_button.setWidth(BUTTON_WIDTH_GAME_UI);
	quit_button.setHeight(BUTTON_HEIGHT_GAME_UI);

	int y_pos_game_ui_buttons = SCREEN_H - BUTTON_HEIGHT - BUTTON_HEIGHT/16;
	vector<Button*> game_ui_button_list;
	game_ui_button_list.push_back(&deal_button);
	game_ui_button_list.push_back(&hit_button);
	game_ui_button_list.push_back(&stand_button);
	game_ui_button_list.push_back(&split_button);
	game_ui_button_list.push_back(&new_hand_button);
	game_ui_button_list.push_back(&surrender_button);
	game_ui_button_list.push_back(&quit_button);
	Panel panel;
	panel.set_button_x_positions(SCREEN_W/2, y_pos_game_ui_buttons, BUTTON_WIDTH_GAME_UI, game_ui_button_list);

	int y_pos_game_bet_ui_buttons = SCREEN_H/4;
	vector<Button*> game_ui_bet_button_list;
	Button bet_100_button;
	bet_100_button.setWidth(BUTTON_WIDTH);
	bet_100_button.setHeight(BUTTON_WIDTH);

	Button bet_250_button;
	bet_250_button.setWidth(BUTTON_WIDTH);
	bet_250_button.setHeight(BUTTON_WIDTH);

	Button bet_500_button;
	bet_500_button.setWidth(BUTTON_WIDTH);
	bet_500_button.setHeight(BUTTON_WIDTH);

	Button bet_1000_button;
	bet_1000_button.setWidth(BUTTON_WIDTH);
	bet_1000_button.setHeight(BUTTON_WIDTH);
	
	game_ui_bet_button_list.push_back(&bet_100_button);
	game_ui_bet_button_list.push_back(&bet_250_button);
	game_ui_bet_button_list.push_back(&bet_500_button);
	game_ui_bet_button_list.push_back(&bet_1000_button);
	panel.set_button_x_positions(SCREEN_W / 2, y_pos_game_bet_ui_buttons, BUTTON_WIDTH, game_ui_bet_button_list);


	//initialize tools
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_font_addon()) {
		fprintf(stderr, "failed to create font addon!\n");
		return -1;
	}

	if (!al_init_ttf_addon()) {
		fprintf(stderr, "failed to create ttf addon!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	al_set_window_title(display, "Allegro Blackjack");

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to create image!\n");
		return -1;
	}


	//init assets
	if (!AssetManager::initialize()) {
		std::cerr << "[ERROR] Error initializing assets" << std::endl;
	}

	//initialize gamesession;
	BlackJack* blackjackGame = new BlackJack();

	vector<ALLEGRO_BITMAP*> dealer_card_image_list;
	vector<ALLEGRO_BITMAP*> player_card_image_list;
	int dealer_hand_y_pos = SCREEN_H / 16;
	int player_hand_y_pos = dealer_hand_y_pos + CARD_HEIGHT + SCREEN_H /16;
	vector<int>dealer_card_x_positions = panel.calculate_x_positions(SCREEN_W / 2, dealer_card_image_list.size(), CARD_WIDTH);
	vector<int>player_card_x_positions;


	//set button textures
	start_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("start_button"));
	exit_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("exit_button"));
	deal_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("deal_button"));
	hit_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("hit_button"));
	stand_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("stand_button"));
	split_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("split_button"));
	new_hand_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("new_hand_button"));
	surrender_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("surrender_button"));
	quit_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("quit_button"));

	bet_100_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("100_button"));
	bet_250_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("250_button"));
	bet_500_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("500_button"));
	bet_1000_button.set_Default_Pressed_Hover_Images(AssetManager::getTexture("1000_button"));

	//attach whether you can use the buttons to the conditions in blackjack
	hit_button.setEnabled(blackjackGame->getCanHit());
	deal_button.setEnabled(blackjackGame->getCanDeal());
	stand_button.setEnabled(blackjackGame->getCanStand());
	split_button.setEnabled(blackjackGame->getCanSplit());
	new_hand_button.setEnabled(blackjackGame->getCanStartNewHand());
	surrender_button.setEnabled(blackjackGame->getCanSurrender());
	
	//grab font and init non-button textures
	font = AssetManager::getFont("small");
	title = AssetManager::getTexture("title");
	background = AssetManager::getTexture("game_background");

	//init score panels
	player_score_panel = AssetManager::getTexture("score_panel");
	dealer_score_panel = AssetManager::getTexture("score_panel");
	int score_panel_y_pos = y_pos_game_ui_buttons - SCORE_PANEL_HEIGHT -SCREEN_H / 10;
	int score_panel_player_x_pos = SCREEN_W/64;
	int score_panel_dealer_x_pos = SCREEN_W - SCORE_PANEL_WIDTH - SCREEN_W/64;
	al_set_display_icon(display, AssetManager::getTexture("facedowncard"));
	
	//display stuffs
	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(display));

	//init event 
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	//initialize event sources on game tools
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);

	//set state before entering game loop
	state = TITLE;


	//start game loop
	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			doexit = true;
			break;
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
			ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

			if (state == TITLE) {
				if (start_button.contains(ev.mouse.x, ev.mouse.y)) {
					start_button.setStatus(Button::HOVER);

				}
				else if (exit_button.contains(ev.mouse.x, ev.mouse.y)) {
					exit_button.setStatus(Button::HOVER);
				}
				else {
					start_button.setStatus(Button::DEFAULT);
					exit_button.setStatus(Button::DEFAULT);
				}

			}
			else if (state == PLAYING) {
				for (int a = 0; a < game_ui_button_list.size(); a++) {
					if (game_ui_button_list[a]->contains(ev.mouse.x, ev.mouse.y)) {
						game_ui_button_list[a]->setStatus(Button::HOVER);
						break;
					}
					else {
						game_ui_button_list[a]->setStatus(Button::DEFAULT);
					}

				}

			}
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (state == TITLE) {
				if (start_button.contains(ev.mouse.x, ev.mouse.y)) {
					start_button.setStatus(Button::PRESSED);
				}
				else if (exit_button.contains(ev.mouse.x, ev.mouse.y)) {
					exit_button.setStatus(Button::PRESSED);
				}
			}
			else if (state == PLAYING) {
				for (int a = 0; a < game_ui_button_list.size(); a++) {
					if (game_ui_button_list[a]->contains(ev.mouse.x, ev.mouse.y)) {
						game_ui_button_list[a]->setStatus(Button::PRESSED);
						break;
					}
					else {
						game_ui_button_list[a]->setStatus(Button::DEFAULT);
					}

				}

			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (state == TITLE) {
				if (start_button.contains(ev.mouse.x, ev.mouse.y)) {
					start_button.setStatus(Button::DEFAULT);
					cout << "Clicked on start" << endl;
					state = PLAYING;
					
				}
				else if (exit_button.contains(ev.mouse.x, ev.mouse.y)) {
					cout << "Clicked on exit" << endl;
					exit_button.setStatus(Button::DEFAULT);
					doexit = true;
					state = -1;
				}
		
				else {
					start_button.setStatus(Button::DEFAULT);
					exit_button.setStatus(Button::DEFAULT);
				}

			}
			else if (state == PLAYING) {
				
			
				if (deal_button.getEnabled() && deal_button.contains(ev.mouse.x, ev.mouse.y)) {
					blackjackGame->makeMove(BlackJack::DEAL);
				}
				else if (hit_button.getEnabled() && hit_button.contains(ev.mouse.x, ev.mouse.y)) {
					blackjackGame->makeMove(BlackJack::HIT);
				}
				else if (surrender_button.getEnabled() && surrender_button.contains(ev.mouse.x, ev.mouse.y)) {
					blackjackGame->makeMove(BlackJack::SURRENDER);
				}
				else if (new_hand_button.getEnabled() && new_hand_button.contains(ev.mouse.x, ev.mouse.y)) {
					blackjackGame->makeMove(BlackJack::START_NEW_HAND);
				}
				else if (stand_button.getEnabled() && stand_button.contains(ev.mouse.x, ev.mouse.y)) {
					blackjackGame->makeMove(BlackJack::STAND);
				}
				else if (split_button.getEnabled() && split_button.contains(ev.mouse.x, ev.mouse.y)) {
					blackjackGame->makeMove(BlackJack::SPLIT);
				}
				else if (quit_button.contains(ev.mouse.x, ev.mouse.y)) {
					blackjackGame->makeMove(BlackJack::QUIT);
					delete blackjackGame;
					blackjackGame = new BlackJack();
					hit_button.setEnabled(blackjackGame->getCanHit());
					deal_button.setEnabled(blackjackGame->getCanDeal());
					stand_button.setEnabled(blackjackGame->getCanStand());
					split_button.setEnabled(blackjackGame->getCanSplit());
					new_hand_button.setEnabled(blackjackGame->getCanStartNewHand());
					surrender_button.setEnabled(blackjackGame->getCanSurrender());
					state = TITLE;
					
				}
				else if (*(blackjackGame->getCanBet())==true) {
					
					if (bet_100_button.contains(ev.mouse.x, ev.mouse.y)) {
						blackjackGame->makeMove(BlackJack::BET_100);
					}
					else if (bet_250_button.contains(ev.mouse.x, ev.mouse.y)) {
						blackjackGame->makeMove(BlackJack::BET_250);
					}
					else if (bet_500_button.contains(ev.mouse.x, ev.mouse.y)) {
						blackjackGame->makeMove(BlackJack::BET_500);
					}
					else if (bet_1000_button.contains(ev.mouse.x, ev.mouse.y)) {
						blackjackGame->makeMove(BlackJack::BET_1000);
					}
				}

				
				

			}
		}

		

		//draw objects on the screen 
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			if (state == TITLE) {
				//Draw title screen
				al_draw_bitmap(title, 0, 0, 0);

				al_draw_bitmap(start_button.getImage(), start_button.getX(), start_button.getY(), 0);
				if (start_button.getOverlay()) {
					al_draw_bitmap(start_button.getOverlay(), start_button.getX(), start_button.getY(), 0);
				}
				al_draw_bitmap(exit_button.getImage(), exit_button.getX(), exit_button.getY(), 0);
				if (exit_button.getOverlay()) {
					al_draw_bitmap(exit_button.getOverlay(), exit_button.getX(), exit_button.getY(), 0);
				}
			}

			else if (state == PLAYING) {
				al_draw_bitmap(background, 0, 0, 0);

				for (int a = 0; a<game_ui_button_list.size(); a++) {
					/*
					al_draw_bitmap(game_ui_button_list[a]->getImage(), game_ui_button_list[a]->getX(), game_ui_button_list[a]->getY(), 0);
					if (game_ui_button_list[a]->getOverlay()) {
						al_draw_bitmap(game_ui_button_list[a]->getOverlay(), game_ui_button_list[a]->getX(), game_ui_button_list[a]->getY(), 0);
					}

					*/
					al_draw_scaled_bitmap(game_ui_button_list[a]->getImage(),
						0, 0,                                // source origin
						al_get_bitmap_width(game_ui_button_list[a]->getImage()),     // source width
						al_get_bitmap_height(game_ui_button_list[a]->getImage()),    // source height
						game_ui_button_list[a]->getX(), game_ui_button_list[a]->getY(),                                // target origin
						BUTTON_WIDTH_GAME_UI, BUTTON_HEIGHT_GAME_UI,                                // target dimensions
						0                                    // flags
					);

					if (game_ui_button_list[a]->getOverlay()) {
						al_draw_scaled_bitmap(game_ui_button_list[a]->getOverlay(),
							0, 0,                                // source origin
							al_get_bitmap_width(game_ui_button_list[a]->getOverlay()),     // source width
							al_get_bitmap_height(game_ui_button_list[a]->getOverlay()),    // source height
							game_ui_button_list[a]->getX(), game_ui_button_list[a]->getY(),                                // target origin
							BUTTON_WIDTH_GAME_UI, BUTTON_HEIGHT_GAME_UI,                                // target dimensions
							0                                    // flags
						);
					}
				}

				if (*(blackjackGame->getCanBet()) == true) {
					for (int a = 0; a<game_ui_bet_button_list.size(); a++) {
						al_draw_scaled_bitmap(game_ui_bet_button_list[a]->getImage(),
							0, 0,                                // source origin
							al_get_bitmap_width(game_ui_bet_button_list[a]->getImage()),     // source width
							al_get_bitmap_height(game_ui_bet_button_list[a]->getImage()),    // source height
							game_ui_bet_button_list[a]->getX(), game_ui_bet_button_list[a]->getY(),                                // target origin
							BUTTON_WIDTH, BUTTON_WIDTH,                                // target dimensions
							0                                    // flags
						);
					}
				}

				int cardwidthpos = CARD_WIDTH;
				if (dealer_card_image_list.size() > 5) {
					cardwidthpos /= 2;
				}
				dealer_card_image_list = blackjackGame->getDealer_Hand_Card_Images();
				vector<int>dealer_card_x_positions = panel.calculate_x_positions(SCREEN_W / 2, dealer_card_image_list.size(), cardwidthpos);
				if (dealer_card_image_list.size() > 0 && dealer_card_image_list.size()==dealer_card_x_positions.size()) {
					for (int a = 0; a<dealer_card_image_list.size(); a++) {
						al_draw_scaled_bitmap(dealer_card_image_list[a],
							0, 0,                                // source origin
							al_get_bitmap_width(dealer_card_image_list[a]),     // source width
							al_get_bitmap_height(dealer_card_image_list[a]),    // source height
							dealer_card_x_positions[a], dealer_hand_y_pos,                                // target origin
							CARD_WIDTH, CARD_HEIGHT,                                // target dimensions
							0                                    // flags
						);
					}
				}

				cardwidthpos = CARD_WIDTH;
				if (player_card_image_list.size() > 5) {
					cardwidthpos /= 2;
				}
				player_card_image_list = blackjackGame->getPlayer_Hand_Card_Images();
				vector<int>player_card_x_positions = panel.calculate_x_positions(SCREEN_W / 2, player_card_image_list.size(), cardwidthpos);
				if (player_card_image_list.size() > 0) {
					for (int a = 0; a<player_card_image_list.size(); a++) {
						al_draw_scaled_bitmap(player_card_image_list[a],
							0, 0,                                // source origin
							al_get_bitmap_width(player_card_image_list[a]),     // source width
							al_get_bitmap_height(player_card_image_list[a]),    // source height
							player_card_x_positions[a], player_hand_y_pos,                                // target origin
							CARD_WIDTH, CARD_HEIGHT,                                // target dimensions
							0                                    // flags
						);
					}
				}

				al_draw_scaled_bitmap(player_score_panel,
					0, 0,                                // source origin
					al_get_bitmap_width(player_score_panel),     // source width
					al_get_bitmap_height(player_score_panel),    // source height
					score_panel_player_x_pos, score_panel_y_pos,                                // target origin
					SCORE_PANEL_WIDTH, SCORE_PANEL_HEIGHT,                                // target dimensions
					0                                    // flags
				);

				al_draw_scaled_bitmap(dealer_score_panel,
					0, 0,                                // source origin
					al_get_bitmap_width(dealer_score_panel),     // source width
					al_get_bitmap_height(dealer_score_panel),    // source height
					score_panel_dealer_x_pos, score_panel_y_pos,                                // target origin
					SCORE_PANEL_WIDTH, SCORE_PANEL_HEIGHT,                                // target dimensions
					0                                    // flags
				);

				al_draw_multiline_textf(font, al_map_rgb(255, 255, 255), score_panel_player_x_pos+SCORE_PANEL_HEIGHT/8, score_panel_y_pos + SCORE_PANEL_HEIGHT / 8, 800, 25, 0, blackjackGame->playerString().c_str());
				al_draw_multiline_textf(font, al_map_rgb(255, 255, 255), score_panel_dealer_x_pos+SCORE_PANEL_HEIGHT/8, score_panel_y_pos + SCORE_PANEL_HEIGHT / 8, 800, 25, 0, blackjackGame->dealerString().c_str());
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}


	}

	//shut down
	AssetManager::destroy();
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}