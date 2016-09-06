//
// main.cpp for  in /home/aroy/gomoku/srv
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Sun Jun 29 13:32:21 2014 Antoine ROY
// Last update Wed Jul  9 00:07:27 2014 Antoine ROY
//

#include "Server.hh"

int	main(int ac, char **av)
{
  if (ac < 3)
    {
      std::cout << "error param\n";
      return (0);
    }

  std::string	param1(av[1]);
  std::string	param2(av[2]);
  std::istringstream	iss(param1);
  int		port;

  iss >> port;
  Server	s(port, param2);

  s.create();
  s.accept_client();
  s.run();
  std::cout << "finish run\n";
  return (0);
}
