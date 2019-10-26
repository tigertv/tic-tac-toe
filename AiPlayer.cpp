#include "AiPlayer.h"
#include <iostream>

AiPlayer::~AiPlayer() {

}

AiPlayer::AiPlayer(std::string seed) {
    this->seed = seed;
}

int AiPlayer::negamax(Game &game, int depth, int alpha, int beta) {
    if (depth == 0) return this->evaluate(game);
    std::vector<GameMove> moves = game.getPossibleMoves();
    int size = moves.size();
    if (size == 0) return 0;

    for (int i = 0; i < size; i++) {
        if (game.makeMove(moves[i])) {
            if (game.hasWon(moves[i])) {
                game.unmakeMove(moves[i]);
                return 10;
            } else {
                game.switchPlayer();
                int ret = - this->negamax(game, depth - 1, -beta, -alpha);
                game.switchPlayer();
                game.unmakeMove(moves[i]);

                if(ret >= beta ) return beta;
                if(ret > alpha ) alpha = ret;
            }

        }
    }
    return alpha;
}

int AiPlayer::evaluate(Game &game) {
    return 0;
}

GameMove AiPlayer::askMove(const Game& game) {
    Game aigame = game;
    std::vector<GameMove> moves = aigame.getPossibleMoves();
    int size = moves.size();
    int bestMove = 0;
    int alpha = -10000;
    int beta = 10000;

    for (int i = 0; i < size; i++) {
        if (aigame.makeMove(moves[i])) {
            if (aigame.hasWon(moves[i])) {
                return moves[i];
            } else {
                aigame.switchPlayer();

                int ret = - this->negamax(aigame, 5, -beta, -alpha);
                if (ret >= beta) return moves[i];
                if (ret > alpha) {
                    alpha = ret;
                    bestMove = i;
                }

                aigame.unmakeMove(moves[i]);
                aigame.switchPlayer();
            }

        }
    }

    return moves[bestMove];
}
