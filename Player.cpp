//
// Player.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Fri Jun 20 18:37:14 2014 Antoine ROY
// Last update Mon Jul  7 12:55:03 2014 Antoine ROY
//

#include "GameEngine.hh"

Player::Player(int _c, bool _t) : color(_c), turn(_t)
{
  taked = 0;
}

Player::~Player()
{}


void	Player::setTaked(int val)
{
  this->taked = val;
}

int	Player::getTaked() const
{
  return (this->taked);
}

int	Player::getColor() const
{
  return (this->color);
}

bool	Player::getTurn() const
{
  return (this->turn);
}

void	Player::setTurn(bool t)
{
  this->turn = t;
}

bool    Player::change_case(int x, int y)
{
  std::cout << "avance bien " << x<< " " << y << "\n";
  if (this->color == 0)
    return GameEngine::Instance().change_case(x, y, "black");
  else if (this->color == 1)
    return GameEngine::Instance().change_case(x, y, "white");
  else
    std::cout << "putain pas de couleur\n";
}
