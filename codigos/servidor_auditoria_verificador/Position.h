
#ifndef Position_class
#define Position_class

#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Position {

public:
	Position(int x, int y);
	Position();
	void move(int);
	void move(int, int);
	void setPosition(json);
	string getPosition();
	json getJson();
	int getX();
	int getY();
	int getSide();
	bool isEqual(Position);

private:
	int side, x, y;
};



#endif