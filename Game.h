#ifndef GAME_H_
#define GAME_H_

#include "Board.h"

enum GameState {
	PLAYING, DRAW, CROSS_WON, ZERO_WON
};

enum Player {
	PLAYER_CROSS, PLAYER_ZERO
};

class Game {
private:
	Board board;
	GameState currentState;
	Player currentPlayer;
	void playerStep();
	bool hasWon();
	void switchPlayer();
public:
	Game();
	virtual ~Game();
	void run();

};

#endif
