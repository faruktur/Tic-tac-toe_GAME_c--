#include "pch.h"
#include "GameOverState.hpp"

#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include <iostream>

namespace Sonar {
	GameOverState::GameOverState(GameDataRef data) :_data(data) {

	}
	void GameOverState::Init() {
		this->_data->assetManager.LoadTexture("Retry Button", RETRY_BUTTON);
		this->_data->assetManager.LoadTexture("Home Button", HOME_BUTTON);
		
		this->_retryButton.setPosition((this->_data->window.getSize().x / 2) - (this->_retryButton.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3) - (this->_retryButton.getLocalBounds().height / 2)
		);
		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3*2) - (this->_homeButton.getLocalBounds().height / 2)
		);
	}
	void GameOverState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->inputManager.IsSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
			if (this->_data->inputManager.IsSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}
	void GameOverState::Update(float dt) {

	}
	void GameOverState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);
		this->_data->window.display();
	}
}