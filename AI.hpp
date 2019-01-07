#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Game.hpp"


namespace Game_ {
	class AI {
	public:
		AI(int playerPiece, GameData data);

		void PlacePiece(int(*gridArray)[3][3], sf::Sprite gridPieces[3][3], int *gameState);
	private:
		void CheckSection(int x1,int y1, int x2, int y2, int X, int Y,int pieceToCheck,int(*gridArray)[3][3],sf::Sprite gridPieces[3][3]);
		void CheckIfPieceIsEmpty();
	};
}