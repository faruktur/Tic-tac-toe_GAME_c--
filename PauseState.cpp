#include "pch.h"
#include "MainMenuState.hpp"

#include "DEFINITIONS.hpp"

#include <iostream>
#include "PauseState.hpp"
namespace Game_ {
	PauseState::PauseState(GameDataRef data) :_data(data) {

	}
	void PauseState::Init() {
		this->_data->assetManager.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		this->_data->assetManager.LoadTexture("Resume Button", RESUME_BUTTON);
		this->_data->assetManager.LoadTexture("Home Button", HOME_BUTTON);

		this->_background.setTexture(this->_data->assetManager.GetTexture("Pause Background"));
		this->_homeButton.setTexture(this->_data->assetManager.GetTexture("Home Button"));
		this->_resumeButton.setTexture(this->_data->assetManager.GetTexture("Resume Button"));

		this->_resumeButton.setPosition((this->_data->window.getSize().x/2) - (this->_resumeButton.getLocalBounds().width / 2),
			(this->_data->window.getSize().y/3) - (this->_resumeButton.getLocalBounds().height / 2)
			);
		this->_homeButton.setPosition((this->_data->window.getSize().x/2) - (this->_homeButton.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3*2) - (this->_homeButton.getLocalBounds().height / 2)
		);
	}
	void PauseState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->inputManager.IsSpriteClicked(this->_resumeButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.RemoveState();
			}
			if (this->_data->inputManager.IsSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
			}
		}
	}
	void PauseState::Update(float dt) {

	}
	void PauseState::Draw(float dt) {
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_homeButton);
		this->_data->window.draw(this->_resumeButton);

		this->_data->window.display();
	}
}