#pragma once
#include<MapGeneratorClass.h>
#include<PerlinNoiseMap.h>

#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>

#include<vec4.hpp>
#include<vector>

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	void LoadResources();

	void GameLoopFunction();
	void Render();
	void Events();

	void MoveVeiw();
	
	void RenderDiamondSquare();
	void RenderPerlinNoise();

private:
	MapGeneratorClass * m_mapGenerator;
	PerlinNoiseMap * m_perlinNoise;

	std::vector<glm::vec3> noiseMap;
	int size;

	int nOctives;

	////////////////////////////////////////////////////////////

	sf::RenderWindow * m_rWindow;

	sf::View * m_mainVeiw;
	float m_speed;

	sf::Clock m_clock;
	sf::Time m_time;
	float m_deltaTime;

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

