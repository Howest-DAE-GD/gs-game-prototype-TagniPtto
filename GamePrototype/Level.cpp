#include "pch.h"
#include "Level.h"

#include "SVGParser.h"
#include "Texture.h"
#include "utils.h"

#include <iostream>
#include "GameObject.h"

Level::Level():
	Level(NULL , NULL)
{

}

Level::Level(const std::string& svgPath, const std::string& texturePath):
	m_scale(2.f)
{
	m_pTexture = new Texture{texturePath};
	if (!SVGParser::GetVerticesFromSvgFile(svgPath, m_mapVertices)) {
		std::cout << "couldn't load : " << svgPath << std::endl;
	}
	if (m_mapVertices.size()<1) {
		std::cout << "no vertices are present" << std::endl;
	}
	else {
		m_border = utils::GetBoundingRectangle(m_mapVertices[0]);
		m_mapVertices.erase(m_mapVertices.begin());
	}

	const int count{ 50 };
	for (int i{}; i < count; ++i) {
		m_objects.push_back(new GameObject(
			Vector2f{ m_border.left + float(std::rand()%int(m_border.width)),m_border.bottom+ float(std::rand() % int(m_border.height))},
			Vector2f{float(std::rand()%40-20),float(std::rand() % 40 - 20) }));
	}
}

Level::~Level()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Level::Update(float elapsedSec)
{
	for (GameObject* object1 : m_objects) {
		object1->Update(elapsedSec);
	}
	for (GameObject* object1 : m_objects) {
		for (GameObject* object2 : m_objects) {
			if (object1 != object2) {
				object1->Collistion(*object2);
			}
		}
	}

}

void Level::Draw() const
{
	//glScalef(m_scale, m_scale,1.f);
	utils::SetColor(Color4f{0.7f,0.7f ,0.7f ,1.f});
	for (std::vector<Point2f> shape : m_mapVertices) {
		utils::FillPolygon(shape);
	}
	for (const GameObject* object : m_objects) {
		object->Draw();
	}
	//glScalef(1.f / m_scale, 1.f/m_scale,1.f);
}

Rectf Level::GetBorder()
{
	return m_border;
}

std::ofstream& operator<<(std::ofstream& out, const Level& l)
{
	std::cout << "Map" << std::endl;
	std::cout << "scale" << l.m_scale << std::endl;
	return out;
}
