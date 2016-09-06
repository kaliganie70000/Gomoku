//
// Case.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Thu Jun 19 18:48:44 2014 Antoine ROY
// Last update Wed Jul  9 18:23:56 2014 Antoine ROY
//


#include "Case.hh"

Case::Case(int _x, int _y, sf::Texture const &_img, std::string const& col) : x(_x), y(_y)
{
  sprite.setTexture(_img);
  sprite.setPosition(x + 25, y + 50);
  color = col;
}

Case::~Case()
{}

void		Case::setSprite(sf::Texture const& img, std::string const& _col)
{
  std::cout << "setting sprite\n";
  sprite.setTexture(img);
  color = _col;
}

sf::Sprite	Case::getSprite() const
{
  return (this->sprite);
}

std::string	Case::getColor() const
{
  return (this->color);
}

int		Case::getX() const
{
  return (this->x);
}

int		Case::getY() const
{
  return (this->y);
}
