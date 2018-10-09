#include "AIView.h"
#include <iostream>

AIView::AIView(GameLogic* l) {
	logic = l;
}

void AIView::step() {

	//if the ball is above the paddle, move up. Otherwise, move down.
	if (logic->getBallPos().y < logic->getRightPaddlePos().y) {
		logic->moveRightPaddle(-1);
	}
	else {
		logic->moveRightPaddle(1);
	}
}