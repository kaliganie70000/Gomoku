//
// Server.hh for  in /home/aroy/gomoku/srv
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Sun Jun 29 00:04:35 2014 Antoine ROY
// Last update Tue Jul  8 18:38:15 2014 Antoine ROY
//

#ifndef	__SERVER__
#define	__SERVER__

# include       <iostream>
# include       <sstream>
# include       <fstream>
# include       <sys/types.h>
# include       <sys/socket.h>
# include       <netinet/in.h>
# include       <netinet/ip.h>
# include       <arpa/inet.h>
# include       <netdb.h>
# include       <unistd.h>
# include       "Singleton.hpp"
# include       "Exception.hpp"
# include	<cstring>
# include	<SFML/Graphics.hpp>
# include	<SFML/Audio.hpp>
# include	<SFML/Window.hpp>
# include	<SFML/System.hpp>
# include	<vector>

class Server
{
public:
  Server(int port = 6667, std::string const& addr = "localhost");
  ~Server();
  void	create();

  void	error(const std::string &msg, int socket);
  void	informations(struct sockaddr_in sin);
  void	accept_client();
  void	run();
  void	xsend(int, std::string);
  std::string	xrecv(int);

private:
  int                                 _port;
  std::string                         _addr;
  int				      _nb_client;
  int                                 _socket;
  int				      fd_cli1;
  int				      fd_cli2;
};

#endif
