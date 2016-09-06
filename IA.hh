//
// IA.hpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Wed Sep  3 19:56:09 2014 Antoine ROY
// Last update Sun Sep  7 15:49:49 2014 Antoine ROY
//

#ifndef	__IA__
#define	__IA__

#include "GameEngine.hh"

class	Node;

class IA : public Player
{
public:
  IA(int, bool, int);
  ~IA();

private:
  int	depth;
  int	x;
  int	y;
  Node	*first_node;

public:
  int	getX() const;
  int	getY() const;

  bool	play(std::vector<Case > &, std::vector<std::pair<int, int> > &);

};


#endif
