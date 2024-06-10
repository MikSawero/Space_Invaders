#include "GameWindow.hpp"

namespace ms
{
	GameWindow::GameWindow(GameDataRef data) : _data(data)
	{
		
	}

	void GameWindow::Init()
	{
		std::cout << "Game State Initialization\n";


		enemyManager = new EnemyManager(_data);
		std::cout << "Enemy Manager Created" << std::endl;

		player = new Player(_data);
		std::cout << "Player Created" << std::endl;

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		projectileManager = new ProjectileManager(_data);
		std::cout << "Projectile Manager Created" << std::endl;

		shieldManager = new ShieldManager(_data);
		std::cout << "Shield Manager Created" << std::endl;

		_textScore.setFont(_data->assets.GetFont("Font"));
		_textScore.setCharacterSize(30);
		_textScore.setString("Score: " + player->GetScore());
		_textScore.setPosition(10, 10);

		_textLives.setFont(_data->assets.GetFont("Font"));
		_textLives.setCharacterSize(30);
		_textLives.setString("Lives: " + player->GetLives());
		_textLives.setPosition(SCREEN_WIDTH - 100 - _textLives.getGlobalBounds().width, 10);

	}

	void GameWindow::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (sf::Event::KeyPressed == event.type
				&& (event.key.scancode == sf::Keyboard::Scan::Space
				|| event.key.scancode == sf::Keyboard::Scan::Enter)
					&& _shotDelay.getElapsedTime() >= sf::seconds(0.5))
			{
				projectileManager->Add(new Projectile(_data, 
					{ player->GetPosition().x + player->GetBox().width/4, player->GetPosition().y - 15}, 0));
				_shotDelay.restart();
			}
			else if (sf::Event::KeyPressed == event.type 
				&& event.key.scancode == sf::Keyboard::Scan::Left)
			{
				player->Move(-20.0f,0);
			}
			else if (sf::Event::KeyPressed == event.type 
				&& event.key.scancode == sf::Keyboard::Scan::Right)
			{
				player->Move(20.0f,0);
			}
		}
	}

	void GameWindow::Update(float dt)
	{
		if (player->GetLives() == 0 || enemyManager->GetRandomBottomEnemy()->GetPosition().y > SCREEN_LENGTH - PLAYER_Y_LEVEL)
		{
			_data->machine.RemoveState();
			_data->machine.AddState(StateRef(new GameOverWindow(_data)), true);
		}
		enemyManager->GetEnemiesLeft();
		enemyManager->Update();
		projectileManager->Update();

		if (_clock.getElapsedTime() >= enemyManager->GetShotDelay())
		{
			enemyManager->Shot(projectileManager);
			_clock.restart();
		}

		for (auto& projectile : projectileManager->getProjectiles())
		{
			enemyManager->CheckForCollisions(*projectile);
			shieldManager->CheckForCollisions(*projectile);
			player->CheckCollision(*projectile);
		}

		enemyManager->RemoveDeadEnemies();
		projectileManager->RemoveDeadProjectiles();
		shieldManager->RemoveDeadShields();
		_textScore.setString("Score: " + std::to_string(Player::_score));
		_textLives.setString("Lives: " + std::to_string(player->GetLives()));

		if (enemyManager->GetEnemiesLeft() == 0)
		{
			enemyManager->InitEnemies();
		}
	}

	void GameWindow::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_textScore);
		_data->window.draw(_textLives);
		enemyManager->DrawEnemyRow();
		shieldManager->DrawShields();
		player->Draw();
		projectileManager->DrawProjectiles();
		_data->window.display();
	}
}