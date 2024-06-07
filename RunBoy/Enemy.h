#include "Texture.h"
class Enemy
{
public:
	Enemy(Point2f);
	~Enemy();
	void chase(Point2f);
	void Draw();
	Point2f hitcheck();

private:
	Point2f m_EPos;
	float m_espeed;
	Texture* enemy;

};

