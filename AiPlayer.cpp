#include "AiPlayer.h"
#include <random>
#include <chrono>
#include <iostream>

AiPlayer::~AiPlayer() {

}

AiPlayer::AiPlayer(std::string seed) {
    this->seed = seed;
}

int AiPlayer::minimax(Game &game) {
    std::vector<GameMove> moves = game.getPossibleMoves();
    int size = moves.size();
    if (size == 0) return 0;
    int max = 0;
    bool isSet = false;
    for (int i = 0; i < size; i++) {
        if (game.makeMove(moves[i])) {
            if (game.hasWon(moves[i])) {
                max = 10;
                game.unmakeMove(moves[i]);
                break;
            } else {
                game.switchPlayer();
                int ret = - this->minimax(game);
                if (!isSet) {
                    isSet = true;
                    max = ret;
                } else if (ret > max) {
                    max = ret;
                }
                game.switchPlayer();
                game.unmakeMove(moves[i]);
            }

        }
    }
    return max;
}

GameMove AiPlayer::askMove(const Game& game) {
    Game aigame = game;
    std::vector<GameMove> moves = aigame.getPossibleMoves();
    int size = moves.size();
    int bestMove = 0;
    int max = 0;
    bool isSet = false;
    for (int i = 0; i < size; i++) {
        if (aigame.makeMove(moves[i])) {
            if (aigame.hasWon(moves[i])) {
                max = 10;
                bestMove = i;
                aigame.unmakeMove(moves[i]);
                break;
            } else {
                aigame.switchPlayer();
                int ret = - this->minimax(aigame);
                if (!isSet) {
                    max = ret;
                    isSet = true;
                } else if (ret > max) {
                    max = ret;
                    bestMove = i;
                }

                aigame.switchPlayer();
                aigame.unmakeMove(moves[i]);
            }

        }
    }

    return moves[bestMove];
}
