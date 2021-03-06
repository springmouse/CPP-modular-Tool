#include "GameLoop.h"



GameLoop::GameLoop()
{
	m_mapGenerator = new MapGeneratorClass();

	//m_map = new MapClass(m_mapGenerator->GenerateNewMap(eMapGenTypes::PERLINNOISE, 3, 1));

	m_perlinNoise = new PerlinNoiseMap();
	nOctives = 10;
	size = 175;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			noiseMap.push_back(glm::vec3(x, y, m_perlinNoise->OctivePerlin( x * 0.01f, y * 0.01f, nOctives, 0.5f) * 10));
		}
	}

	m_watterHeight = 0.26f;
	m_earthHeight = 0.51f;
	m_stoneHeight = 0.76f;

	m_rWindow = new sf::RenderWindow(sf::VideoMode(1200, 800), "My Window");

	m_mainVeiw = new sf::View(sf::FloatRect(1200, 400, 1800, 1200) );

	m_running = true;

	LoadResources();

	//m_mainVeiw->setCenter(sf::Vector2f(m_map->g_mapVertecs[((m_map->size * m_map->size) - 1) / 2].x + 150, m_map->g_mapVertecs[((m_map->size * m_map->size) - 1) / 2].y + 150));
}


GameLoop::~GameLoop()
{
}

void GameLoop::LoadResources()
{
	m_watter = new sf::Texture();
	m_watter->loadFromFile	("../Resources/Sprites/Terrain/Watter.png");
	m_watterSprite = new sf::Sprite();
	m_watterSprite->setTexture(*m_watter);

	m_grass = new sf::Texture();
	m_grass->loadFromFile	("../Resources/Sprites/Terrain/Grass.png");
	m_grassSprite = new sf::Sprite();
	m_grassSprite->setTexture(*m_grass);

	m_stone = new sf::Texture();
	m_stone->loadFromFile	("../Resources/Sprites/Terrain/Stone.png");
	m_stoneSprite = new sf::Sprite();
	m_stoneSprite->setTexture(*m_stone);

	m_snow = new sf::Texture();
	m_snow->loadFromFile	("../Resources/Sprites/Terrain/Snow.png");
	m_snowSprite = new sf::Sprite();
	m_snowSprite->setTexture(*m_snow);

}

void GameLoop::GameLoopFunction()
{
	while (m_running)
	{
		m_time = m_clock.restart();
		m_deltaTime = m_time.asSeconds();

		Events();
		
		MoveVeiw();

		Render();
	}
}

void GameLoop::Render()
{
	m_rWindow->setView(*m_mainVeiw);

	m_rWindow->clear(sf::Color::Black);
	
	//RenderDiamondSquare();

	RenderPerlinNoise();
	
	m_rWindow->display();
}

void GameLoop::Events()
{
	sf::Event event;

	while (m_rWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			//end the program
			m_running = false;
		}
		else if (event.type == sf::Event::Resized)
		{
			//adjust the viewport when the window is resized
			//m_rWindow->setSize(0, 0, event.size.width, event.size.height);
		}
	}

}

void GameLoop::MoveVeiw()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		m_speed = 1000;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) != true)
	{
		m_speed = 100;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_mainVeiw->move(sf::Vector2f(-1.0f * m_deltaTime * m_speed, 0.0f));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_mainVeiw->move(sf::Vector2f(1.0f * m_deltaTime * m_speed, 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_mainVeiw->move(sf::Vector2f(0.0f, -1.0f * m_deltaTime * m_speed));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_mainVeiw->move(sf::Vector2f(0.0f, 1.0f * m_deltaTime * m_speed));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		noiseMap.clear();
		m_perlinNoise->NewSeed((unsigned int)rand() % 13000000, 255);

		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				noiseMap.push_back(glm::vec3(x, y, m_perlinNoise->OctivePerlin(x * 0.01f, y * 0.01f, nOctives, 0.5f) * 10));
			}
		}
	}
}

void GameLoop::RenderDiamondSquare()
{
	//for (int i = 0; i < m_map->g_mapVertecs.size(); i++)
	//{
	//	if (m_map->g_mapVertecs[i].z < m_watterHeight)
	//	{
	//		m_watterSprite->setPosition(m_map->g_mapVertecs[i].x * 32, m_map->g_mapVertecs[i].y * 32);
	//		m_rWindow->draw(*m_watterSprite);
	//	}
	//	else if (m_map->g_mapVertecs[i].z < m_earthHeight)
	//	{
	//		m_grassSprite->setPosition(m_map->g_mapVertecs[i].x * 32, m_map->g_mapVertecs[i].y * 32);
	//		m_rWindow->draw(*m_grassSprite);
	//	}
	//	else if (m_map->g_mapVertecs[i].z < m_stoneHeight)
	//	{
	//		m_stoneSprite->setPosition(m_map->g_mapVertecs[i].x * 32, m_map->g_mapVertecs[i].y * 32);
	//		m_rWindow->draw(*m_stoneSprite);
	//	}
	//	else
	//	{
	//		m_snowSprite->setPosition(m_map->g_mapVertecs[i].x * 32, m_map->g_mapVertecs[i].y * 32);
	//		m_rWindow->draw(*m_snowSprite);
	//	}
	//}
}

void GameLoop::RenderPerlinNoise()
{
	for (int i = 0; i < noiseMap.size(); i++)
	{
		if (noiseMap[i].z < m_watterHeight)
		{
			m_watterSprite->setPosition(noiseMap[i].x * 32, noiseMap[i].y * 32);
			m_rWindow->draw(*m_watterSprite);
		}
		else if (noiseMap[i].z < m_earthHeight)
		{
			m_grassSprite->setPosition(noiseMap[i].x * 32, noiseMap[i].y * 32);
			m_rWindow->draw(*m_grassSprite);
		}
		else if (noiseMap[i].z < m_stoneHeight)
		{
			m_stoneSprite->setPosition(noiseMap[i].x * 32, noiseMap[i].y * 32);
			m_rWindow->draw(*m_stoneSprite);
		}
		else
		{
			m_snowSprite->setPosition(noiseMap[i].x * 32, noiseMap[i].y * 32);
			m_rWindow->draw(*m_snowSprite);
		}
	}
}
