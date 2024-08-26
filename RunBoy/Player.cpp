#include "pch.h"
#include "Game.h"
#include "iostream"

int Player::level = 0;

Player::Player(Point2f pos)
{   
	state = game::alive;
	iframes = 80;
	
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	player = new Texture("Player.png");
	health = new Texture("Health.png");
	for (int i = 0; i <= level; ++i)
	{
		key[i] = new Texture("Key.png");
	}
	m_speed.x = 3;
	m_speed.y = 3;
	hp = 3;
	hasKey = 0;
	for (int i = 0; i <= level; ++i)
	{
		Kpos[i] = Point2f((rand() % 15 + 2) * 64, (rand() % 10 + 2) * 64);
	}

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

	if (hasKey<=level)
	{
		for (int i = 0; i <= level; ++i)
		{
			key[i]->Draw(Kpos[i], Rectf(0, 0, 64, 64));
		}
	}
	
}
void Player::exit(Point2f* exit)
{
	if (hasKey <= level)
	{
		glColor3f(1.0f, 0.f, 0.f);
	}
	else {
		glColor3f( 0.f, 1.0f, 0.f);
	}

	utils::FillRect(Rectf(exit->x, exit->y, 64, 64));

	
		for (int i = 0; i <= level; ++i)
		{
			if (-64 < exit->x - m_Pos.x && exit->x - m_Pos.x < 64 && -64 < exit->y - m_Pos.y && exit->y - m_Pos.y < 64 && hasKey > level)
			{

				state = game::won;

			}
			else if (-32 < Kpos[i].x - m_Pos.x && Kpos[i].x - m_Pos.x < 32 && -32 < Kpos[i].y - m_Pos.y && Kpos[i].y - m_Pos.y < 32)
			{
				hasKey += 1;
				Kpos[i].x = -100;
				Kpos[i].y = -100;
			}
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
		if (-48 < pos.x - m_Pos.x && pos.x - m_Pos.x < 48 && -48 < pos.y - m_Pos.y && pos.y - m_Pos.y < 48)
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
		
		level = 0;
		return false;
	}
	if (state == game::won)
	{
		
		level += 1;

		if (level == 9)
		{
			level = 0;
		}

		return false;
	}
}


Player::~Player()
{
	delete player;
}



