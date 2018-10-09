#include <SFML\graphics.hpp>
#include "GameLogic.h"

class AIView {
private:
	GameLogic *logic;

public:
	AIView(GameLogic *l);
	void step();
};