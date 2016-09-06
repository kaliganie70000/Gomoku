//
// Node.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Sun Sep  7 14:43:11 2014 Antoine ROY
// Last update Thu Sep 11 20:58:22 2014 Antoine ROY
//

#include "Node.hh"

Node::Node(std::vector<Case > cases, std::vector<std::pair<int, int> > poss, int _depth)
{
  plate = cases;
  list_possible = poss;
  m_depth = _depth;
  c_depth = 1;
}

Node::Node(std::vector<Case > cases, std::vector<std::pair<int, int> > poss, int _depth, int _x, int _y)
{
  plate = cases;
  list_possible = poss;
  c_depth = _depth;
  x = _x;
  y = _y;
  if (c_depth != 1)
    {
      //calcul pions                                                                     
    }
}

Node::~Node()
{}

void	Node::play()
{
  std::vector<std::pair<int, int> >::iterator	it = list_possible.begin();

  while (it != list_possible.end())
    {
      to_play.push_back(Node(plate, list_possible, (c_depth + 1), (*it).first, (*it).second));
      it++;
    }
}

int	Node::getX()
{
  return x;
}

int	Node::getY()
{
  return y;
}

int	Node::getEvalNb()
{
  return eval_nb;
}

int	Node::eval_function()
{
  
}
