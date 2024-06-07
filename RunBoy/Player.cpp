#include "pch.h"
#include "Game.h"
#include "iostream"

Player::Player(Point2f pos)
{   
	state = game::alive;
	iframes = 80;
	
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	player = new Texture("Player.png");
	health = new Texture("Health.png");
	m_speed.x = 3;
	m_speed.y = 3;
	hp = 3;
	for (int i = 0; i < 50; ++i)
	{
		Point2f start((rand() % 18)*64, (rand() % 12)*64);
		std::vector <Point2f> Plat

		{
			Point2f(start.x,start.y),
			Point2f(start.x+64 ,start.y),
			Point2f(start.x,start.y)

		};
		m_Map.push_back(Plat);
	}
	for (int i = 0; i < 50; ++i)
	{
		Point2f start((rand() % 15) *64, (rand() % 12) * 64);
		std::vector <Point2f> Plat

		{
			Point2f(start.x,start.y),
			Point2f(start.x,start.y+64),
			Point2f(start.x,start.y)

		};
		m_Map.push_back(Plat);
	}
	
}

void Player::Draw()
{
	player->Draw(m_Pos,Rectf(0,0,64,64));
	
}
void Player::exit(Point2f* exit)
{
	utils::FillRect(Rectf(exit->x, exit->y, 64, 64));
	if(-64 < exit->x - m_Pos.x && exit->x - m_Pos.x <64&&-64<exit->y-m_Pos.y&&exit->y-m_Pos.y<64)
	{
		
		state = game::won;
	
	}
	
}
void Player::mapbounds()
{
	
	m_speed.x = 3;
	m_speed.y = 3;
	for (auto i = 0; i < m_Map.size(); i++)
	{
		if (utils::Raycast(m_Map[i], Point2f(m_Pos.x+32, m_Pos.y), Point2f(m_Pos.x+32, m_Pos.y + 32), hit_info))
		{
			
			m_speed.y = 0;
			m_Pos.y++;
		}
		if (utils::Raycast(m_Map[i], Point2f(m_Pos.x+32, m_Pos.y + 32), Point2f(m_Pos.x+32, m_Pos.y+64), hit_info))
		{
			
			m_speed.y = 0;
			m_Pos.y--;
		}
	}
	for (auto i = 0; i < m_Map.size(); i++)
	{
		if (utils::Raycast(m_Map[i], Point2f(m_Pos.x, m_Pos.y + 32), Point2f(m_Pos.x + 32, m_Pos.y+32), hit_info))
		{

			
			m_speed.x = 0;
			m_Pos.x++;
		}
		if (utils::Raycast(m_Map[i], Point2f(m_Pos.x+32, m_Pos.y+32 ), Point2f(m_Pos.x + 64, m_Pos.y+32 ), hit_info))
		{
			
			m_speed.x = 0;
			m_Pos.x--;
		}
	}
	if (m_Pos.x <= 0)
	{
		m_Pos.x=0;
	}
	if (m_Pos.x >= 1200-64)
	{
		m_Pos.x=1136;
	}
	if (m_Pos.y <= 0)
	{
		m_Pos.y=0;
	}
	if (m_Pos.y >= 800 - 64)
	{
		m_Pos.y=736;
	}

	}
	

	


void Player::drawmap()
{
	for (auto i = 0; i < m_Map.size(); i++)
	{
		utils::DrawPolygon(m_Map[i]);
	}
}
void Player::Down()
{
	
	m_Pos.y -= m_speed.y;
}
void Player::Up()
{
	
	m_Pos.y += m_speed.y;
}

void Player::Right()
{
	
	m_Pos.x += m_speed.x;
}
void Player::Left()
{
	
	m_Pos.x -= m_speed.x;
}
void Player::hitcheck(Point2f pos)
{
	 
	
	{
		if (-64 < pos.x - m_Pos.x && pos.x - m_Pos.x < 64 && -64 < pos.y - m_Pos.y && pos.y - m_Pos.y < 64)
		{
			iframes += 1;
			if (iframes >= 60)
			{
				hp -= 1;
				iframes = 0;
			}
		}
		if (hp == 0)
		{
			state = game::lost;
			
		}
	}

}
void Player::healthbar()
{
	Point2f pos;
	for (int i = 0; i < hp ;i++)
	{
		pos.x = 40 * i;
		pos.y = 750;
		health->Draw(pos, Rectf(0, 0, 32, 32));
	}
}
Point2f Player::chase() 
{
	return m_Pos;
}

bool Player::gamestate()
{
	if (state == game::alive)
	{
		return true;
	}
	if (state == game::lost)
	{
		std::cout << " YOU LOST";
		return false;
	}
	if (state == game::won)
	{
		std::cout << " YOU WON";
		return false;
	}
}

Player::~Player()
{
	delete player;
}



