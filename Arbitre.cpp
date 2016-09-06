//
// Arbitre.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Sat Jun 21 15:15:39 2014 Antoine ROY
// Last update Fri Nov  7 13:57:53 2014 adrien perez
//

#include "GameEngine.hh"

Arbitre::Arbitre(std::vector<Case > &cases, Player *_p1, Player *_p2)
{
  cp_cases = &cases;
  x_to = 0;
  y_to = 0;
  p1 = _p1;
  p2 = _p2;
}

Arbitre::~Arbitre()
{}

void	Arbitre::setRules(bool r1, bool r2, bool r3)
{
  rules_taked = r1;
  rules_five_b = r2;
  rules_double_three = r3;
}

bool	Arbitre::rechange_color()
{
  std::vector<Case >::iterator it = cp_cases->begin();
  if (GameEngine::Instance().getRulesPions() == true)
    GameEngine::Instance().add_pion_possible(x_to, y_to);
  
  (*(it + (x_to + (y_to * 19)))).setSprite(GameEngine::Instance().getCenterEmpty(), "empty");
  p1->setTurn((p1->getTurn() == true ? false : true));
  p2->setTurn((p2->getTurn() == true ? false : true));
  return false;
}

bool	Arbitre::rules(Player *player, int x, int y)
{
  printf("player : %p -> x : %d et y : %d\n", player, x, y);

  x_to = x / 50;
  y_to = y / 50;

  if (rules_double_three && double_three(x_to, y_to) == false)
    return rechange_color();

  if (rules_taked)
    {
      this->take_two_pions(player);
      if (player->getTaked() >= 10)
	return (true);
    }

  if (this->five_concecutif(player) == 2)
    return (true);
  return (false);
}

bool	Arbitre::double_three(int _x, int _y)
{
  std::string			usedColor;
  std::string			currentColor = "";   
  std::vector<Case>::iterator	it;
  std::vector<Case>::iterator	it_check;
  int				count;
  int				countAdversaire;
  int				nbThreeFree = 0;
  
  x_to = _x;
  y_to = _y;
  std::cout << "x_to : " << x_to << " et y_to : "<<y_to<<std::endl;
  it = cp_cases->begin() + (x_to + (y_to * 19));

  currentColor = (*it).getColor();
  usedColor = currentColor;

  it = cp_cases->begin();

  // horizontal

  for (int y = 0; y < 19; y++) { 
    for (int x = 0; x < 19 && it <= cp_cases->end(); x++) {
  	if ((*it).getColor() == usedColor) {
  	  countAdversaire = 0;
  	  count = 0;

  	  it_check = cp_cases->begin() + (x + (y * 19) - 1);	  
  	  if (x == 0 || (it_check <= cp_cases->end() && (*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
  	    countAdversaire++;
	    
  	  it_check = cp_cases->begin() + (x + (y * 19) + 4);
	  if (it_check < cp_cases->end()) { 
	    if (x + 3 >= 19 || x + 4 >= 19 || ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	      countAdversaire++;
	  } else {
	    countAdversaire++;
	  }
	  
  	  it_check = cp_cases->begin() + (x + (y * 19));
  	  for (int i = 0; i <= 4 && it_check < cp_cases->end(); i++) {
  	    if ((*it_check).getColor() == usedColor)
  	      count++;
  	    else if ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty")
  	      countAdversaire++;
  	    it_check++;
  	  }
  	  if (count == 3 && countAdversaire == 0)
  	    nbThreeFree++;
  	}
  	it++;
      }
  }

  // vertical

  it = cp_cases->begin();

  for (int x = 0; x < 19; x++) { 
    for (int y = 0; y < 19; y++) {
      it = cp_cases->begin() + (x + (y * 19));
      if ((*it).getColor() == usedColor) {
	countAdversaire = 0;
	count = 0;

	it_check = cp_cases->begin() + (x + (y * 18));	  
	if (y == 0 || ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;
	    
	it_check = cp_cases->begin() + (x + (y * 23));	  
	if (y + 3 >= 19 || y + 4 >= 19 || ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;

	it_check = cp_cases->begin() + (x + (y * 19));
	for (int i = 0; i <= 4 && it_check < cp_cases->end(); i++) {
	  if ((*it_check).getColor() == usedColor)
	    count++;
	  else if ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty")
	    countAdversaire++;
	  it_check += 19;
	}
	if (count == 3 && countAdversaire == 0)
	  nbThreeFree++;
      }
    }
  }

  // diagonale-droite

  int	x;
  int	y_loop_check;
  int	x_loop_check;
  it = cp_cases->begin();

  for (int y = 4; y < 19; y++) {
    x = 0;
    for (int y_tmp = y; y_tmp >= 0; y_tmp--) {
      it = cp_cases->begin() + (x + (y_tmp * 19)); 
      if ((*it).getColor() == usedColor) {
	countAdversaire = 0;
	count = 0;
	
	x_loop_check = x;
	y_loop_check = y_tmp;

	it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19) + 18);	  
	if (((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;
	
	it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19) - 18);	  
	if (y_loop_check == 0)
	  countAdversaire++;
	else if (y_loop_check - 3 >= 0 || y_loop_check - 4 >= 0 || ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;

	for (int i = 0; i <= 4 && y_loop_check >= 0; i++) {
	  it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19)); 
	  if ((*it_check).getColor() == usedColor)
	    count++;
	  else if ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty")
	    countAdversaire++;	  
	  x_loop_check++;
	  y_loop_check--;
	}
	if (count == 3 && countAdversaire == 0)
	  nbThreeFree++;
      }
      x++;
    }
  }

  int	y;

  for (int x = 14; x >= 0; x--) {
    y = 0;
    for (int x_tmp = x; x_tmp < 19; x_tmp++) {
      it = cp_cases->begin() + (x_tmp + (y * 19)); 

      if ((*it).getColor() == usedColor) {
	countAdversaire = 0;
	count = 0;

	x_loop_check = x_tmp;
	y_loop_check = y;

	it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19) + 18);	  
	if (y_loop_check == 18 || x_loop_check == 0 || ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;
	
	it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19) - 18);	  
	if (y == 0 || y_loop_check + 3 >= 19 || y_loop_check + 4 >= 19 || ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;
	
	for (int i = 0; i <= 4 && y_loop_check < 19; i++) {
	  it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19)); 
	  if ((*it_check).getColor() == usedColor)
	    count++;
	  else if ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty")
	    countAdversaire++;	  
	  x_loop_check--;
	  y_loop_check++;
	}
	if (count == 3 && countAdversaire == 0)
	  nbThreeFree++;
      }
      y++;
    }
  }

  // diagonale-gauche

  for (int x = 14; x >= 0; x--) {
    y = 0;
    for (int x_tmp = x; x_tmp < 19; x_tmp++) {
      it = cp_cases->begin() + (x_tmp + (y * 19)); 

      if ((*it).getColor() == usedColor) {
	countAdversaire = 0;
	count = 0;

	x_loop_check = x_tmp;
	y_loop_check = y;

	it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19) - 20);	  
	if (y_loop_check == 0)
	  countAdversaire++;
	else if (((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;
	
	it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19) + 20);	  
	if (x_loop_check + 3 >= 19 || x_loop_check + 4 >= 19 || ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;
	
	for (int i = 0; i <= 4 && y_loop_check < 19 && x_loop_check < 19; i++) {
	  it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19)); 
	  if ((*it_check).getColor() == usedColor)
	    count++;
	  else if ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty")
	    countAdversaire++;	  
	  x_loop_check++;
	  y_loop_check++;
	}
	if (count == 3 && countAdversaire == 0)
	  nbThreeFree++;
      }
      y++;
    }
  }

  for (int y = 14; y >= 0; y--) {
    x = 0;
    for (int y_tmp = y; y_tmp < 19; y_tmp++) {
      it = cp_cases->begin() + (x + (y_tmp * 19)); 

      if ((*it).getColor() == usedColor) {
	countAdversaire = 0;
	count = 0;

	x_loop_check = x;
	y_loop_check = y_tmp;

	it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19) - 20);	  
	if (x_loop_check == 0)
	  countAdversaire++;
	else if (((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;
	
	it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19) + 20);	  
	
	if (y_loop_check == 18)
	  countAdversaire++;
	else if (y_loop_check + 3 >= 19 || y_loop_check + 4 >= 19 || ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty"))
	  countAdversaire++;		
	
	for (int i = 0; i <= 4 && y_loop_check < 19; i++) {
	  it_check = cp_cases->begin() + (x_loop_check + (y_loop_check * 19)); 
	  if ((*it_check).getColor() == usedColor)
	    count++;
	  else if ((*it_check).getColor() != usedColor && (*it_check).getColor() != "empty")
	    countAdversaire++;	  
	  x_loop_check++;
	  y_loop_check++;
	}
	if (count == 3 && countAdversaire == 0)
	  nbThreeFree++;
      }
      x++;
    }
  }

  if (nbThreeFree >= 2) {
    std::cout << "Double-three rule" << std::endl;
    return false;
  } else
    return true;
}
  
bool	Arbitre::check_breakable_all(std::string const& color, std::string const& color_inv, int nbr, int inc, int dif)
{
  int   nb = 0;
  std::vector<Case >::iterator it = cp_cases->begin() + (x_to + (y_to * 19));

  while ((*(it - nb)).getColor() == color)
    {
      if ((y_to - 2 >= 0 && (*(it - nb - dif)).getColor() == color) &&
	  (*(it - nb - (dif * 2))).getColor() == color_inv &&
	  (*(it - nb + dif)).getColor() == "empty")
        return true;                                                                                                                                                             
      if ((y_to + 2 < 19 && (*(it - nb + dif)).getColor() == color) &&
	  (*(it - nb + (dif * 2))).getColor() == color_inv &&
	  (*(it - nb - dif)).getColor() == "empty")
        return true;

      if ((y_to - 1 >= 0 && (*(it - nb - dif)).getColor() == color_inv) &&
	  (y_to + 1 < 19 && (*(it - nb + dif)).getColor() == color) &&
	  (*(it - nb + (dif * 2))).getColor() == "empty")
        return true;

      if ((y_to - 1 >= 0 && (*(it - nb - dif)).getColor() == color) &&
	  (y_to + 1 < 19 && (*(it - nb + dif)).getColor() == color_inv) &&
	  (*(it - nb - (dif * 2))).getColor() == "empty")
        return true;
      nb += inc;
    }

  nb = 0;
  while (nb <= nbr && (*(it + nb)).getColor() == color)
    {
      if ((y_to - 2 >= 0 && (*(it + nb - dif)).getColor() == color) &&
	  (*(it + nb - (dif * 2))).getColor() == color_inv && (*(it + nb + dif)).getColor() == "empty")
        return true;

      if ((y_to + 2 < 19 && (*(it + nb + dif)).getColor() == color) &&
	  (*(it + nb + (dif * 2))).getColor() == color_inv && (*(it + nb - dif)).getColor() == "empty")
        return true;
      
      if ((y_to - 1 >= 0 && (*(it + nb - dif)).getColor() == color_inv) &&
	  (y_to + 1 < 19 && (*(it + nb + dif)).getColor() == color) && (*(it + nb + (dif * 2))).getColor() == "empty")
        return true;

      if ((y_to - 1 < 19 && (*(it + nb - dif)).getColor() == color) &&
	  (y_to + 1 < 19 && (*(it + nb + dif)).getColor() == color_inv) && (*(it + nb - (dif * 2))).getColor() == "empty")
        return true;
      nb += inc;
    }
  return false;
}

bool	Arbitre::five_breakable(std::string color, int direc, int nbr)
{
  std::string	color_inv;

  if (color == "white")
    color_inv = "black";
  else if (color == "black")
    color_inv = "white";
  else
    color_inv = "nothing";
  
  if (direc == 0) //horizontal
    return (check_breakable_all(color, color_inv, nbr, 1, 19) ||
	    check_breakable_all(color, color_inv, nbr, 1, 20) ||
	    check_breakable_all(color, color_inv, nbr, 1, 18));
  else if (direc == 1) //vertical
    return (check_breakable_all(color, color_inv, nbr, 19, 1) ||
	    check_breakable_all(color, color_inv, nbr, 19, 20) ||
	    check_breakable_all(color, color_inv, nbr, 19, 18));
  else if (direc == 2) //diagonale haut gauche -> bas droite
    return (check_breakable_all(color, color_inv, nbr, 20, 1) ||
	    check_breakable_all(color, color_inv, nbr, 20, 19) ||
	    check_breakable_all(color, color_inv, nbr, 20, 18));
  else if (direc == 3) //diagonale bas gauche -> haut droite
    return (check_breakable_all(color, color_inv, nbr, 18, 1) ||
	    check_breakable_all(color, color_inv, nbr, 18, 19) ||
	    check_breakable_all(color, color_inv, nbr, 18, 20));
  return (false);
}

bool	Arbitre::getRulesFive()
{
  return (rules_five_b);
}

bool	Arbitre::getRulesTaked()
{
  return (rules_taked);
}

int	Arbitre::five_concecutif(Player *p)
{
  int	s_v = 1;
  int	s_h = 1;
  int	s_dhgd = 1;
  int	s_dbgd = 1;
  int	nb = 1;
  bool	breakable = false;

  std::vector<Case >::iterator it = cp_cases->begin() + (x_to + (y_to * 19));
  std::string	color_p = (*it).getColor();

  //checking_gauche
  while (x_to - nb >= 0 && (*(it - nb++)).getColor() == color_p)
    s_h++;
  nb = 1;
  
  //checking_droite
  while (x_to + nb < 19 && (*(it + nb++)).getColor() == color_p)
    s_h++;

  if (s_h >= 5 && (!rules_five_b || (!rules_taked ? true : !five_breakable(color_p, 0, nb))))
    return 2;

  nb = 1;
  //checking_haut
  while (y_to - nb >= 0 && (*(it - (19 * nb++))).getColor() == color_p)
    s_v++;

  //checking_bas
  nb = 1;
  while (y_to + nb < 19 && (*(it + (19 * nb++))).getColor() == color_p)
    s_v++;

  if (s_v >= 5 && (!rules_five_b || (!rules_taked ? true : !five_breakable(color_p, 1, nb))))
    return 2;

  nb = 1;
  //checking_haut_gauche
  while (y_to - nb >= 0 && x_to - nb >= 0 && (*(it - (20 * nb++))).getColor() == color_p)
    s_dhgd++;

  nb = 1;
  //checking_bas_droite
  while (y_to + nb < 19 && x_to + nb < 19 && (*(it + (20 * nb++))).getColor() == color_p)
    s_dhgd++;

  if (s_dhgd >= 5 && (!rules_five_b || (!rules_taked ? true : !five_breakable(color_p, 2, nb))))
    return 2;

  nb = 1;
  //checking_bas_gauche
  while (y_to + nb < 19 && x_to - nb >= 0 && (*(it + (18 * nb++))).getColor() == color_p)
    s_dbgd++;

  nb = 1;
  //checking_haut_droite
  while (y_to - nb >= 0 && x_to + nb < 19 && (*(it - (18 * nb++))).getColor() == color_p)
    s_dbgd++;

  if (s_dbgd >= 5 && (!rules_five_b || (!rules_taked ? true : !five_breakable(color_p, 3, nb))))
    return 2;

  return 0;
}

void	Arbitre::destroy_pions(Player * p, std::vector<Case >::iterator first, std::vector<Case >::iterator second)
{
  if (GameEngine::Instance().getRulesPions() == true)
    GameEngine::Instance().add_pion_possible((*(first)).getX() / 50, (*(first)).getY() / 50);
  (*(first)).setSprite(GameEngine::Instance().getCenterEmpty(), "empty");
  if (GameEngine::Instance().getRulesPions() == true)
    GameEngine::Instance().add_pion_possible((*(second)).getX() / 50, (*(second)).getY() / 50);
  (*(second)).setSprite(GameEngine::Instance().getCenterEmpty(), "empty");
  p->setTaked(p->getTaked() + 2);
}

void	Arbitre::take_two_pions(Player *p)
{
  std::string	color_inv;
  std::vector<Case >::iterator it = cp_cases->begin() + (x_to + (y_to * 19));

  if ((*it).getColor() == "black")
    color_inv = "white";
  else
    color_inv = "black";

  //gauche
  if (((x_to - 3) >= 0) && (*(it - 1)).getColor() == color_inv && (*(it - 2)).getColor() == color_inv &&
      (*(it - 3)).getColor() == (*it).getColor())
    destroy_pions(p, it - 1, it - 2);

  //droite
  if (((x_to + 3) < 19) && (*(it + 1)).getColor() == color_inv && (*(it + 2)).getColor() == color_inv &&
      (*(it + 3)).getColor() == (*it).getColor())
    destroy_pions(p, it + 1, it + 2);

  //haut
  if (((y_to - 3) >= 0) && (*(it - 19)).getColor() == color_inv && (*(it - 38)).getColor() == color_inv &&
      (*(it - 57)).getColor() == (*it).getColor())
    destroy_pions(p, it - 19, it - 38);

  //bas
  if (((y_to + 3) < 19) && (*(it + 19)).getColor() == color_inv && (*(it + 38)).getColor() == color_inv &&
      (*(it + 57)).getColor() == (*it).getColor())
    destroy_pions(p, it + 19, it + 38);

  //haut_gauche
  if (((y_to - 3) >= 0) && ((x_to - 3) >= 0) && (*(it - 20)).getColor() == color_inv &&
      (*(it - 40)).getColor() == color_inv && (*(it - 60)).getColor() == (*it).getColor())
    destroy_pions(p, it - 20, it - 40);

  //haut_droite
  if (((y_to - 3) >= 0) && ((x_to + 3) < 19) && (*(it - 18)).getColor() == color_inv &&
      (*(it - 36)).getColor() == color_inv && (*(it - 54)).getColor() == (*it).getColor())
    destroy_pions(p, it - 18, it - 36);

  //bas_gauche
  if (((y_to + 3) < 19) && ((x_to - 3) >= 0) && (*(it + 18)).getColor() == color_inv &&
      (*(it + 36)).getColor() == color_inv && (*(it + 54)).getColor() == (*it).getColor())
    destroy_pions(p, it + 18, it + 36);

  //bas_droite
  if (((y_to + 3) < 19) && ((x_to + 3) < 19) && (*(it + 20)).getColor() == color_inv &&
      (*(it + 40)).getColor() == color_inv && (*(it + 60)).getColor() == (*it).getColor())
    destroy_pions(p, it + 20, it + 40);
}
