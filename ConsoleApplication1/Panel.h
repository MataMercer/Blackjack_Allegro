#pragma once
#include <vector>
#include "Button.h"
using namespace std;
class Panel
{
public:
	vector <int> calculate_x_positions(int screen_center_x, int numItems, int width_of_each_item) {
		vector <int> positions;
		int space_amount = 10;
		int panelWidth = width_of_each_item*numItems + space_amount*(numItems - 1);
		
		int pos = screen_center_x - panelWidth / 2;
		for (int a = 0; a < numItems; a++) {
			positions.push_back(pos);
			pos += width_of_each_item + space_amount;
		}

		return positions;
	}

	void set_button_x_positions(int screen_center_x, int y_coord, int width_of_each_item, vector<Button*> buttons) {
		int space_amount = 10;
		int panelWidth = width_of_each_item*buttons.size() + space_amount*(buttons.size() - 1);

		int pos = screen_center_x - panelWidth / 2;
		for (int a = 0; a < buttons.size(); a++) {
			buttons[a]->setX(pos);
			buttons[a]->setY(y_coord);
			pos += width_of_each_item + space_amount;
		}
	}

	Panel();
	~Panel();


};

