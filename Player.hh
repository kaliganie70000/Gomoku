//
// Player.hh for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Fri Jun 20 18:35:15 2014 Antoine ROY
// Last update Sat Jun 21 21:09:21 2014 Antoine ROY
//

#ifndef	__PLAYER__
#define	__PLAYER__

#include "Singleton.hpp"

class Player : public Singleton<Player>
{
public:
  Player(int _c, bool _t);
  ~Player();

protected:
  int	color;
  int	taked;
  bool	turn;

public:
  bool	change_case(int, int);
  
  void	setTurn(bool turn);
  bool	getTurn() const;

  int	getColor() const;

  void	setTaked(int);
  int	getTaked() const;
};

#endif
