#include "pch.h"
#include <sstream>
#include "SplashState.hpp"	
#include <iostream>
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"

namespace Sonar { 

	SplashState::SplashState(GameDataRef data) : _data(data) {

	}
	void SplashState::Init() {
		this->_data->assetManager.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assetManager.GetTexture("Splash State Background"));

	}
	void SplashState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
		}
	}
	void SplashState::Update(float dt) {
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) {
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
	}
	void SplashState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw(this->_background);
		this->_data->window.display();
	}
}