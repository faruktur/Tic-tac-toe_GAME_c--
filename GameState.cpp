#include "pch.h"
#include "GameState.hpp"

#include "DEFINITIONS.hpp"

#include <iostream>
#include "PauseState.hpp"

 
namespace Game_ {
	GameState::GameState(GameDataRef data) :_data(data) {

	}
	void GameState::Init() {
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->_data->assetManager.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assetManager.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);

		this->_data->assetManager.LoadTexture("X PIECE", X_PIECE_FILEPATH);
		this->_data->assetManager.LoadTexture("O PIECE", O_PIECE_FILEPATH);

		this->_data->assetManager.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		this->_data->assetManager.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		
		_background.setTexture(this->_data->assetManager.GetTexture("Background"));
		_gridSprite.setTexture(this->_data->assetManager.GetTexture("GridSprite"));
		_pauseButton.setTexture(this->_data->assetManager.GetTexture("Pause Button"));

		_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));
		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);	

		InitGridPiece();

		for (int i = 0;  i< 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				gridArray[i][j] = EMPTY_PIECE;
			}
		}

	}
	void GameState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->inputManager.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new PauseState(_data)),false);
			}
			else if (this->_data->inputManager.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window)) {
				if (STATE_PLAYING==gameState) {
					this->CheckAndPlacePiece();
				}
			}
		}
	}
	void GameState::Update(float dt) {

	}

	void GameState::CheckAndPlacePiece() {
		sf::Vector2i touchPoint = this->_data->inputManager.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);
		int column, row;
		if (gridLocalTouchPos.x < gridSectionSize.x) {
			column = 1;
		}
		else if (gridLocalTouchPos.x<gridSectionSize.x*2) {
			column = 2;	
		}
		else if (gridLocalTouchPos.x < gridSize.width * 2) {
			column = 3;
		}

		if (gridLocalTouchPos.y < gridSectionSize.y) {
			row = 1;
		}
		else if (gridLocalTouchPos.y < gridSectionSize.y * 2) {
			row = 2;
		}
		else if (gridLocalTouchPos.y < gridSize.height) {
			row = 3;
		}
		// X x
		if (gridArray[column - 1][row - 1] == EMPTY_PIECE) {
			gridArray[column - 1][row - 1] = turn;
			if (PLAYER_PIECE == turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assetManager.GetTexture("X Piece"));
				this->CheckPlayerHasWon(turn);
				turn = AI_PIECE;
			}
			else if (AI_PIECE == turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assetManager.GetTexture("O Piece"));
				this->CheckPlayerHasWon(turn);
				turn = PLAYER_PIECE;
			}
			_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}
	void GameState::CheckPlayerHasWon(int player) {
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

		int emptyNum = 9;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (EMPTY_PIECE != gridArray[i][j]) {
					emptyNum--;
				}
			}
		}
		if (0 == emptyNum && (STATE_WON != gameState) && (STATE_LOSE != gameState)) {
			gameState = STATE_DRAW;
		}

		if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState) {
			//SHOW GAME OVER
		}
		std::cout << gameState << std::endl;
	}
	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
		if(STATE_LOSE!=gameState&&STATE_WON!=gameState&&STATE_DRAW!=gameState){ 
		if (pieceToCheck==gridArray[x1][y1]&& pieceToCheck == gridArray[x2][y2]&& pieceToCheck == gridArray[x3][y3]) {
			std::string winningPieceStr;
			if (O_PIECE == pieceToCheck) {
				winningPieceStr = "O Winning Piece";
			}
			if (AI_PIECE == pieceToCheck) {
				winningPieceStr = "X Winning Piece";
			}
			_gridPieces[x1][y1].setTexture(this->_data->assetManager.GetTexture(winningPieceStr));
			_gridPieces[x2][y2].setTexture(this->_data->assetManager.GetTexture(winningPieceStr));
			_gridPieces[x3][y3].setTexture(this->_data->assetManager.GetTexture(winningPieceStr));

			if (PLAYER_PIECE == pieceToCheck) {
				gameState = STATE_WON;
			}
			else {
				gameState = STATE_LOSE;
			}
		}
		}
	}
	void GameState::Draw(float dt) {
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);
			
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->_data->window.draw(this->_gridPieces[i][j]);
			}
		}
		this->_data->window.display();
	}
	void GameState::InitGridPiece() {
		sf::Vector2u tempSpriteSize = this->_data->assetManager.GetTexture("X Piece").getSize();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				_gridPieces[i][j].setTexture(this->_data->assetManager.GetTexture("X Piece"));
				_gridPieces[i][j].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x*i) - 7, _gridSprite.getPosition().y + (tempSpriteSize.y*j) - 7);
				_gridPieces[i][j].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}
}