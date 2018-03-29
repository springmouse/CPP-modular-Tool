#pragma once
#include<MapGeneratorClass.h>

#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>

//#include<SFML\OpenGL.hpp>

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	void LoadResources();

	void GameLoopFunction();
	void Render();
	void Events();

private:
	MapGeneratorClass * m_mapGenerator;
	MapClass * m_map;


	//sf::Window * m_glWindow;
	sf::RenderWindow * m_rWindow;


	bool m_running;

	sf::Texture * m_watter;
	sf::Sprite * m_watterSprite;

	sf::Texture * m_grass;
	sf::Sprite * m_grassSprite;

	sf::Texture * m_stone;
	sf::Sprite * m_stoneSprite;

	sf::Texture * m_snow;
	sf::Sprite * m_snowSprite;

	float m_watterHeight, m_earthHeight, m_stoneHeight;
};

