//
// Server.cpp for  in /home/aroy/gomoku/srv
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Sun Jun 29 00:12:47 2014 Antoine ROY
// Last update Wed Jul  9 00:07:46 2014 Antoine ROY
//

#include "Server.hh"

Server::Server(int port, std::string const& addr) : _port(port), _addr(addr), _nb_client(0)
{}

Server::~Server()
{
  close(_socket);
  close(fd_cli1);
  close(fd_cli2);
  std::cout << "in closing\n";
}

void	Server::error(const std::string &msg, int socket)
{
  if (socket != -1)
    close(socket);
  perror(msg.c_str());
  throw Exception::SysCallException();
}

void                  Server::informations(struct sockaddr_in sin)
{
  std::cout << "[NETWORK] informations: "
	    << inet_ntoa(sin.sin_addr) << ":"
	    << htons(sin.sin_port) << " and "
	    << _socket << std::endl;

  std::cout << "port : " << _port
	    << " and addr : " << _addr << std::endl;
}

void	Server::create()
{
  struct sockaddr_in    sin;
  struct protoent       *pe;

  pe = getprotobyname("tcp");
  if ((_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    error("ERROR: socket() failed", -1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(_port);
  sin.sin_addr.s_addr = !_addr.compare("localhost") ? INADDR_ANY : inet_addr(_addr.c_str());
  if (bind(_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    error("ERROR: bind() failed", _socket);
  if (listen(_socket, 2) == -1)
    error("ERROR: listend() failed", _socket);
  informations(sin);
}

void                    Server::accept_client()
{
  int                   cli_size;
  struct sockaddr_in    cli_addr;

  cli_size = sizeof(cli_addr);
  if (((_nb_client == 0 ? fd_cli1 : fd_cli2) = accept(_socket, (struct sockaddr *)&cli_addr, (socklen_t *)&cli_size)) == -1)
    error("ERROR: [server] accept() failed", -1);
  informations(cli_addr);
  _nb_client++;
  if (_nb_client == 1)
    {
      xsend(fd_cli1, "first");
      accept_client();
    }
  else
    xsend(fd_cli2, "second");
}

void			Server::run()
{
  std::string		from_p1 = "";
  std::string		from_p2 = "";

  while (from_p1 != "winner" && from_p2 != "winner")
    {
      //player 1 turn
      from_p1 = xrecv(fd_cli1);
      if (from_p1 == "winner")
	return ;
      std::cout << "player 1 msg : " << from_p1 << std::endl;
      xsend(fd_cli2, from_p1);
      
      //player 2 turn
      from_p2 = xrecv(fd_cli2);
      if (from_p2 == "winner")
	return ;
      xsend(fd_cli1, from_p2);
    }
  std::cout << "finish\n";
}

void                  Server::xsend(int socket, std::string msg)
{
  if (send(socket, msg.c_str(), msg.size(), 0) < 0)
    error("ERROR: send() failed", socket);
}

std::string		Server::xrecv(int sock)
{
  int                   ret;
  char                  msg[100];

  memset(msg, 0, 100);
  if ((ret = recv(sock, msg, 100, 0)) < 0)
    {
      std::cout << "Client #" << sock << " has gone" << std::endl;
      close(sock);
    }
  std::string   toto(msg);
  return (toto);
}
