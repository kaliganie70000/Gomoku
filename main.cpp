//
// main.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Wed Jun 18 19:18:10 2014 Antoine ROY
// Last update Wed Nov  5 22:28:35 2014 etienne bondot
//

#include "GameEngine.hh"
#include "Menu.hh"

int		main(int ac, char **av)
{
  try
    {
      Menu	m;
      m.run();
    }
  catch (std::exception &e)
    {
      std::cout << e.what() << std::endl;
    }
  return (0);
}
