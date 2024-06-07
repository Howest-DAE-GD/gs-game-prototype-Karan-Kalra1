#include "pch.h"
#include "Game.h"

Enemy::Enemy(Point2f pos)
{
	m_EPos.x = pos.x;
	m_EPos.y = pos.y;
	enemy = new Texture("Enemy.png");
	m_espeed = 1.0f;
}

void Enemy::Draw()
{
	enemy->Draw(m_EPos, Rectf(0, 0, 64, 64));
	
}
Point2f Enemy::hitcheck()
{
	return m_EPos;
}
void Enemy::chase(Point2f pos)
{
	if (m_EPos.x > pos.x)
	{
		m_EPos.x -= m_espeed;
	}
	if (m_EPos.x < pos.x)
	{
		m_EPos.x += m_espeed;
	}
	if (m_EPos.y > pos.y)
	{
		m_EPos.y -= m_espeed;
	}
	if (m_EPos.y < pos.y)
	{
		m_EPos.y += m_espeed;
	}
}

Enemy::~Enemy()
{
	delete enemy;
}