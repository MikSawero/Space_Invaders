#include "GameWindow.hpp"

namespace ms
{
	GameWindow::GameWindow(GameDataRef data) : _data(data)
	{
		
	}

	void GameWindow::Init()
	{
		std::cout << "Game State Initialization\n";

		_data->assets.LoadTexture("Game Background",
			GAME_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Enemy",
			YELLOW_ENEMY);
		_data->assets.LoadTexture("Player",
			PLAYER);
		_data->assets.LoadTexture("Projectile",
			PROJECTILE);

		_data->assets.LoadTexture("Shield1", SHIELD1);
		_data->assets.LoadTexture("Shield2", SHIELD2);
		_data->assets.LoadTexture("Shield3", SHIELD3);
		_data->assets.LoadTexture("Shield4", SHIELD4);
		_data->assets.LoadTexture("Shield5", SHIELD5);
		std::cout << "Shields loaded" << std::endl;

		_data->assets.LoadFont("Font", FONT);
		_textScore.setFont(_data->assets.GetFont("Font"));
		_textScore.setCharacterSize(30);
		_textScore.setPosition(10,10);

		enemyManager = new EnemyManager(_data);
		std::cout << "Enemy Manager Created" << std::endl;

		player = new Player(_data);
		std::cout << "Player Created" << std::endl;

		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));

		projectileManager = new ProjectileManager(_data);
		std::cout << "Projectile Manager Created" << std::endl;

		shieldManager = new ShieldManager(_data);
		std::cout << "Shield Manager Created" << std::endl;

		_textScore.setString("Score: " + player->GetScore());
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
				&& event.key.scancode == sf::Keyboard::Scan::Space && _shotDelay.getElapsedTime() >= sf::seconds(0.5))
			{
				projectileManager->Add(new Projectile(_data, 
					{ player->GetPosition().x + player->GetBox().width/4, player->GetPosition().y - 15}, 0));
				_shotDelay.restart();
			}
			else if (sf::Event::KeyPressed == event.type 
				&& event.key.scancode == sf::Keyboard::Scan::Left)
			{
				std::cout << "Left Key Pressed" << std::endl;
				player->Move(-20.0f,0);
			}
			else if (sf::Event::KeyPressed == event.type 
				&& event.key.scancode == sf::Keyboard::Scan::Right)
			{
				std::cout << "Right Key Pressed" << std::endl;
				player->Move(20.0f,0);
			}
		}
	}

	void GameWindow::Update(float dt)
	{
		enemyManager->GetEnemiesLeft();
		enemyManager->Update();
		projectileManager->Update();
		if (_enemyShotDelay.getElapsedTime() >= sf::seconds(1.5f))
		{
			enemyManager->Shot(projectileManager);
			_enemyShotDelay.restart();
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
	}

	void GameWindow::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_textScore);
		enemyManager->DrawEnemyRow();
		shieldManager->DrawShields();
		player->Draw();
		projectileManager->DrawProjectiles();
		_data->window.display();
	}
}