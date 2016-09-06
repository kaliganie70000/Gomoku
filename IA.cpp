//
// IA.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Wed Sep  3 20:35:17 2014 Antoine ROY
// Last update Thu Sep 11 20:50:49 2014 Antoine ROY
//

# include "IA.hh"

IA::IA(int _c, bool b, int hard) : Player(_c, b)
{
  depth = hard;
}

IA::~IA()
{}

int	IA::getX() const
{
  return x;
}

int	IA::getY() const
{
  return y;
}

bool	IA::play(std::vector<Case > &plate, std::vector<std::pair<int, int> > &poss)
{
  std::cout << "ia play()" << std::endl;
  int	nb;
  if (depth == 0)
    {
      if (poss.size() > 0)
	{
	  std::vector<std::pair<int, int> >::iterator	it = poss.begin();
	  nb = rand() % poss.size();
	  std::cout << "ia choose : " << nb << " sur " << poss.size() << std::endl;
	  while (nb > 0)
	    {
	      it++;
	      nb--;
	    }
	  std::cout << "ia push on : " << (*it).first << " and " << (*it).second << std::endl;
	  x = (*it).first * 50;
	  y = (*it).second * 50;
	}
      else
	{
	  std::cout << "je suis dans le else\n";
	  x = 0;
	  y = 0;
	  std::vector<Case >::iterator	it = plate.begin();
	  int	c = 0;
	  while (x == 0 || y == 0)
	    {
	      nb = rand() % 361;
	      if ((*(it + nb)).getColor() != "empty")
		{
		  x = 0;
		  y = 0;
		}
	      else
		{
		  x = (*(it + nb)).getX();
		  y = (*(it + nb)).getY();
		}
	    }
	}
      turn = false;
      return true;
    }
  // first_node = new Node(plate, poss, 1);
  // first_node->play();
  return true;
}

