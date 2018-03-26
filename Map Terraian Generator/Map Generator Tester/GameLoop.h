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
	sf::Texture * m_grass;
	sf::Texture * m_stone;
	sf::Texture * m_snow;

};

