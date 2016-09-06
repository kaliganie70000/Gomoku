//
// Node.hh for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Sat Sep  6 16:24:52 2014 Antoine ROY
// Last update Sun Sep  7 15:27:14 2014 Antoine ROY
//

#ifndef	__NODE__
#define	__NODE__

#include "GameEngine.hh"

class Node
{
public:
  Node(std::vector<Case >, std::vector<std::pair<int, int> >, int);
  Node(std::vector<Case >, std::vector<std::pair<int, int> >, int, int, int);
  ~Node();

private:
  std::vector<Case > plate;
  std::vector<std::pair<int, int> > list_possible;
  std::vector<Node > to_play;

  int	x;
  int	y;
  int	eval_nb;
  int	m_depth;
  int	c_depth;

public:
  int	getX();
  int	getY();
  int	getEvalNb();
  int	eval_function();
  void	play();
};

#endif
