#pragma once

#include <vector>

class GameObject;
class Texture;

class Level
{
public:
	explicit Level();
	explicit Level(const std::string& svgPath, const std::string& texturePath);
	~Level();

	void Update(float elapsedSec);
	void Draw()const;

	friend std::ofstream& operator<<(std::ofstream& out,const Level& l);
	Rectf GetBorder();

private:
	float m_scale;
	Texture* m_pTexture;
	std::vector<std::vector<Point2f>> m_mapVertices;
	std::vector<GameObject*> m_objects;
	Rectf m_border;
};