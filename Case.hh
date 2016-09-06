//
// Case.hh for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Thu Jun 19 18:48:48 2014 Antoine ROY
// Last update Wed Jul  9 00:29:39 2014 Antoine ROY
//

#ifndef	__CASE__
#define	__CASE__

#include "GameEngine.hh"

class	Case
{
public:
  
  Case(int, int, sf::Texture const&, std::string const&);
  ~Case();

  private:
  
  int		x;
  int		y;
  sf::Sprite	sprite;
  std::string	color;

public:

  sf::Sprite	getSprite() const;
  void		setSprite(sf::Texture const&, std::string const&);
  int		getX() const;
  int		getY() const;
  std::string	getColor() const;

};


#endif
