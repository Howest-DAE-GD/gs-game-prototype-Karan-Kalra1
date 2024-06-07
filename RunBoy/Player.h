#include "Texture.h"
#include "vector"
#include "utils.h"


class Player
{
public:
	    Player(Point2f pos);
	   ~Player();
		void Draw();
		void Left();
		void Right();
		void Up();
		void Down();
		void mapbounds();
		void hitcheck(Point2f);
		void exit(Point2f* exit);
		void drawmap();
		void healthbar();
		Point2f chase();
		bool gamestate();


	private:
		Point2f m_Pos;
		Point2f m_speed;
	    Texture* player;
		Texture* health;
		int hp;
		enum class game { alive, lost, won };
		game state;
		std::vector < std::vector <Point2f> > m_Map;
		utils::HitInfo
			hit_info;
		int iframes;
		

};

