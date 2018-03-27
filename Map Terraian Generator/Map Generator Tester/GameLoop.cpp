#include "GameLoop.h"



GameLoop::GameLoop()
{
	m_mapGenerator = new MapGeneratorClass();

	m_map = new MapClass(m_mapGenerator->GenerateNewMap(eMapGenTypes::DIAMONDSQUARE, 3, 1));

	//sf::ContextSettings settings;
	//settings.depthBits = 24;
	//settings.stencilBits = 8;
	//settings.antialiasingLevel = 4;
	//settings.majorVersion = 3;
	//settings.minorVersion = 0;
	//
	//m_glWindow = new sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
	//glEnable(GL_TEXTURE_2D);

	m_rWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "My Window");

	m_running = true;

	LoadResources();
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
		Events();

		Render();
	}
}

void GameLoop::Render()
{
	/*
	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw...

	// end the current frame (internally swaps the front and back buffers)
	m_glWindow->display();
	*/

	// clear the window with black color
	m_rWindow->clear(sf::Color::Black);

	for (int i = 0; i < m_map->g_mapVertecs.size(); i++)
	{
		if (m_map->g_mapVertecs[i].z < 0.25f)
		{
			m_watterSprite->setPosition(m_map->g_mapVertecs[i].x * 32, m_map->g_mapVertecs[i].y * 32);
			m_rWindow->draw(*m_watterSprite);
		}
		else if (m_map->g_mapVertecs[i].z < 0.50f)
		{
			m_grassSprite->setPosition(m_map->g_mapVertecs[i].x * 32, m_map->g_mapVertecs[i].y * 32);
			m_rWindow->draw(*m_grassSprite);
		}
		else if (m_map->g_mapVertecs[i].z < 0.75f)
		{
			m_stoneSprite->setPosition(m_map->g_mapVertecs[i].x * 32, m_map->g_mapVertecs[i].y * 32);
			m_rWindow->draw(*m_stoneSprite);
		}
		else
		{
			m_snowSprite->setPosition(m_map->g_mapVertecs[i].x * 32, m_map->g_mapVertecs[i].y * 32);
			m_rWindow->draw(*m_snowSprite);
		}
	}

	// draw everything here...
	// window.draw(...);

	// end the current frame
	m_rWindow->display();

}

void GameLoop::Events()
{
	sf::Event event;

	/*
	while (m_glWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			// end the program
			m_running = false;
		}
		else if (event.type == sf::Event::Resized)
		{
			// adjust the viewport when the window is resized
			glViewport(0, 0, event.size.width, event.size.height);
		}
	}

	if (m_glWindow->isOpen == false)
	{
		m_running = false;
	}
	*/

	while (m_rWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			// end the program
			m_running = false;
		}
		else if (event.type == sf::Event::Resized)
		{
			// adjust the viewport when the window is resized
			//m_rWindow->(0, 0, event.size.width, event.size.height);
		}
	}
	
	if (m_rWindow->isOpen() == false)
	{
		m_running = false;
	}
}
