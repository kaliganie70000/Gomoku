//
// GameEngine.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Thu Jun 19 21:44:00 2014 Antoine ROY
// Last update Wed Nov  5 23:44:33 2014 etienne bondot
//

#include "GameEngine.hh"
#include "Exception.hpp"

using namespace sf;

GameEngine::GameEngine()
{
  int	x = 0;
  std::ostringstream	oss;

  sock = -2;
  rules_pions = true;
  window.create(VideoMode(1000, 1025, 32), "Gomoku !");
  if (!font.loadFromFile("img/font_plateau.png") ||
      !center_empty.loadFromFile("img/center_empty.png") ||
      !center_black.loadFromFile("img/center_black.png") ||
      !center_white.loadFromFile("img/center_white.png") ||
      !white_winner.loadFromFile("img/white_win.png") ||
      !black_winner.loadFromFile("img/black_win.png") ||
      !police.loadFromFile("arial.ttf"))
    throw Exception::LoadFromFileException();

  s_font.setTexture(font);
  s_font.setPosition(0, 0);
  
  oss << "you have : 0 pawn";
  have_you = new Text(oss.str(), police, 15);
  have_you->setPosition(843.0, 5.0);
  have_you->setColor(Color::Black);
  have_you->setStyle(Text::Bold);

  oss.str("");
  
  oss << "he  have : 0 pawn";
  have_him = new Text(oss.str(), police, 15);
  have_him->setPosition(845.0, 25.0);
  have_him->setColor(Color::Black);
  have_him->setStyle(Text::Bold);

  restart = new Text("Restart", police, 35);
  restart->setPosition(23.0, 4.0);
  restart->setColor(Color::Black);
  restart->setStyle(Text::Bold);

  while (x < 361)
    {
      cases.push_back(Case((x % 19) * 50, (x / 19) * 50, center_empty, "empty"));
      x++;
    }

  possible.push_back(std::make_pair(9, 9));  

  p1 = NULL;
  you = NULL;
}

GameEngine::~GameEngine()
{
  if (p1)
    delete p1;
  if (you)
    delete you;
  delete p2;
  delete arbitre;
  delete have_you;
  delete have_him;
  delete restart;
}

Arbitre	*GameEngine::getArbitre()
{
  return arbitre;
}

bool	GameEngine::Restart_all()
{
  int	x = 0;
  std::vector<Case >::iterator it = this->cases.begin();

  if (p1)
    delete p1;
  if (you)
    delete you;
  delete p2;
  Connection();
  while (x < 361)
    {
      (*(it + x)).setSprite(center_empty, "empty");
      x++;
    }
  if (rules_pions == true)
    {
      possible.clear();
      possible.push_back(std::make_pair(9, 9));
    }
  return false;
}

void	GameEngine::Connection(bool ia, bool online, const std::string &port, const std::string &addr)
{
  if (online)
    {
      if (connect_to_srv(port, addr) == "first")
	{
	  you = new Player(0, true);
	  p2 = new Player(1, false);
	  arbitre = new Arbitre(cases, you, p2);
	}
      else
	{
	  you = new Player(1, false);
	  p2 = new Player(0, true);
	  arbitre = new Arbitre(cases, you, p2);
	}
    }
  else if (ia)
    {
      you = new Player(0, true);
      p_ia = new IA(1, false, 0);
      arbitre = new Arbitre(cases, you, p_ia);
    }
  else
    {
      p1 = new Player(0, true);
      p2 = new Player(1, false);
      arbitre = new Arbitre(cases, p1, p2);
    }
}

void	GameEngine::display_plate()
{
  std::vector<Case >::iterator it = cases.begin();
  std::ostringstream	oss;

  window.draw(s_font);
  while (it != this->cases.end())
    {
      window.draw((*it).getSprite());
      it++;
    }
  if (you)
    oss << "you have : " << you->getTaked() << " pawn";
  else
    oss << "you have : " << p1->getTaked() << " pawn";
  have_you->setString(oss.str());
  oss.str("");
  if (p2)
    oss << "he  have : " << p2->getTaked() << " pawn";
  else
    oss << "he  have : " << p_ia->getTaked() << " pawn";
  have_him->setString(oss.str());

  window.draw(*have_you);
  window.draw(*have_him);
  if (you == NULL)
    window.draw(*restart);
}

std::string	GameEngine::connect_to_srv(std::string const& port, std::string const& addr)
{
  std::string		toto;
  struct protoent       *proto;
  struct sockaddr_in    client;
  socklen_t             len;
  std::istringstream	iss(port);
  int			_p;

  iss >> _p;
  proto = getprotobyname("TCP");
  sock = socket(AF_INET, SOCK_STREAM, proto->p_proto);
  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(addr.c_str());
  client.sin_port = htons(_p);
  len = sizeof(struct sockaddr_in);
  if (connect(sock, (struct sockaddr *)&client, len) == -1)
    {
      std::cout << "fail to connect !\n";
      exit(0);
    }
  toto = xrecv(sock);
  std::cout << toto << std::endl;
  return toto;
}

std::string	GameEngine::xrecv(int sock)
{
  int                   ret;
  char		        msg[100];

  std::cout << "en attente de msg\n";
  memset(msg, 0, 100);
  if ((ret = recv(sock, msg, 100, 0)) < 0)
    {
      std::cout << "Client #" << sock << " has gone" << std::endl;
      close(sock);
    }
  std::string	toto(msg);
  std::cout << "msg reçu : " << toto << std::endl;
  return (toto);
}

void		GameEngine::xsend(int sock, std::string msg)
{
  std::cout << "envoye de : " << msg << std::endl;
  if (send(sock, msg.c_str(), msg.size(), 0) < 0)
    std::cout << "error to send : " << msg << std::endl;
}

void	GameEngine::add_pion_possible(int x, int y)
{
  int	nb;
  std::vector<std::pair<int, int > >::iterator  it_p = possible.begin();

  while (it_p != possible.end() && ((*(it_p)).first != x || (*(it_p)).second != y))
    it_p++;

  
  if (it_p == possible.end())
    {
      nb = x + (19 * y);
      std::cout << "nb : " << nb << std::endl;
      if ((*(cases.begin() + nb)).getColor() == "empty")
	possible.push_back(std::make_pair(x, y));
    }
}

bool	GameEngine::change_case(int x, int y, std::string const& color)
{
  int	s;
  std::vector<std::pair<int, int > >::iterator	it_p = possible.begin();

  if (you == NULL && x >= -5 && x < 125 && y >= -45 && y < 0)
    return Restart_all();

  x = (x / 50);
  y = (y / 50);
  
  std::cout << "push on : " << x << " and " << y << std::endl;
  if (rules_pions == true)
    {
      while (it_p != possible.end() && ((*(it_p)).first != x || (*(it_p)).second != y))
	it_p++;
      
      if (!(it_p != possible.end() && (*(it_p)).first == x && (*(it_p)).second == y))
	return false;

      possible.erase(it_p);
      add_pion_possible(x - 1, y - 1);
      add_pion_possible(x, y - 1);
      add_pion_possible(x + 1, y - 1);
      add_pion_possible(x + 1, y);
      add_pion_possible(x + 1, y + 1);
      add_pion_possible(x, y + 1);
      add_pion_possible(x - 1, y + 1);
      add_pion_possible(x - 1, y);
    }

  x > 19 ? x = 19 : x = x;
  x < 0 ? x = 0 : x = x;
  
  y > 19 ? y = 19 : y = y;
  y < 0 ? y = 0 : y = y;
  
  s = x + (19 * y);
  if ((*(cases.begin() + s)).getColor() != "empty")
    return false;
  if (color == "black")
    (*(cases.begin() + s)).setSprite(center_black, "black");
  else if (color == "white")
    (*(cases.begin() + s)).setSprite(center_white, "white");
  return true;
}

bool	GameEngine::play(int x, int y)
{
  x -= 25;
  y -= 50;
  if (p1->getTurn() == true // && arbitre->double_three(x/50, y/50)
      && p1->change_case(x, y))
    {  
      p1->setTurn(false);
      p2->setTurn(true);
      return arbitre->rules(p1, x, y);
    }
  else if (p2->getTurn() == true // && arbitre->double_three(x/50, y/50)
	   && p2->change_case(x, y))
    {
      p1->setTurn(true);
      p2->setTurn(false);
      return arbitre->rules(p2, x, y);
    }
  return false;
}

bool	GameEngine::play_with_ia(int x, int y)
{
  if (you->getTurn() == true)
    {
      x -= 25;
      y -= 50;
    }
  if (you->getTurn() == true && you->change_case(x, y))
    {
      you->setTurn(false);
      std::cout << "change turn p_ia\n";
      p_ia->setTurn(true);
      return arbitre->rules(you, x, y);
    }
  else if (p_ia->getTurn() == false && you->getTurn() == false && p_ia->change_case(x, y))
    {
      you->setTurn(true);
      std::cout << "change turn you\n";
      return arbitre->rules(p_ia, x, y);
    }
  else
    std::cout << "j'ai un autre probleme\n";
  return false;
}

bool    GameEngine::play_online(int x, int y)
{
  std::ostringstream	oss;
  std::string	msg;

  std::cout << "put on : " << x << " and " << y << std::endl;
  x -= 25;
  y -= 50;
  if (you->getTurn() == true && you->change_case(x, y))
    {
      you->setTurn(false);
      p2->setTurn(true);
      oss << x << " " << y;
      msg = oss.str();
      xsend(sock, msg);
      return arbitre->rules(you, x, y);
    }
  return false;
}

bool	GameEngine::play_online_other_player(std::string msg)
{
  std::istringstream    iss(msg.c_str());
  int	x;
  int	y;

  iss >> x;
  iss >> y;
  std::cout << "je suis ici car c'est pas mon tour\n";
  if (p2->getTurn() == true && p2->change_case(x, y))
    {
      std::cout << "passage dans le if\n";
      if (arbitre->rules(p2, x, y) == true)
	affiche_winner();
      you->setTurn(true);
      p2->setTurn(false);
    }
  return false;
}

void	GameEngine::affiche_winner()
{
  sf::Sprite	winner;
  std::string	win("winner");
  int		color = -1;

  if ((p1 && p1->getTurn() == true) || (you && you->getTurn() == true))
    winner.setTexture(white_winner);
  else
    winner.setTexture(black_winner);
  
  if (you)
    color = you->getColor();
  if ((color == 0 && you && you->getTaked() >= 10) || (color == 1 && (p2 ? p2->getTaked() >= 10 : p_ia->getTaked() >= 10)))
    winner.setTexture(black_winner);
  else if ((color == 1 && you && you->getTaked() >= 10) || (color == 0 && (p2 ? p2->getTaked() >= 10 : p_ia->getTaked() >= 10)))
    winner.setTexture(white_winner);

  if (sock != 2)
    {
      std::cout << "finish so sock is : " << sock << std::endl;
      if (sock != -2)
	xsend(sock, win);
    }
  while (window.isOpen())
    {
      while (window.pollEvent(event))
        {
          if (event.type == Event::Closed)
            window.close();
	  window.clear();
	  window.draw(winner);
	  window.display();
	}
    }
}

void	GameEngine::loop_online()
{
  Vector2i	pos;

  std::cout << "online\n";
  while (window.isOpen())
    {
      while (window.pollEvent(event))
        {
          if (event.type == Event::Closed)
            window.close();
          if (Mouse::isButtonPressed(Mouse::Left) && you->getTurn() == true)
	    {
	      while (Mouse::isButtonPressed(Mouse::Left))
		;
	      pos = Mouse::getPosition(window);
	      if (pos.x >= 0 && pos.x <= 1000 && pos.y >= 0 && pos.y <= 1075 && play_online(pos.x, pos.y) == true)
		affiche_winner();
	    }
	  window.clear();
	  display_plate();
	  window.display();
	  if (you->getTurn() == false)
	    play_online_other_player(xrecv(sock));
	}
      window.clear();
      display_plate();
      window.display();
    }
}

void	GameEngine::loop_IA()
{
  Vector2i	pos;

  std::cout << "loop ia" << std::endl;
  while (window.isOpen())
    {
      while (window.pollEvent(event))
        {
          if (event.type == Event::Closed)
            window.close();
	  if (Mouse::isButtonPressed(Mouse::Left) && you->getTurn() == true)
	    {
	      while (Mouse::isButtonPressed(Mouse::Left))
		;
	      pos = Mouse::getPosition(window);
	      if (pos.x >= 0 && pos.x <= 1000 && pos.y >= 0 && pos.y <= 1075 && play_with_ia(pos.x, pos.y) == true)
		affiche_winner();
	    }
        }
      if (you->getTurn() == false && p_ia->getTurn() == true && p_ia->play(cases, possible) == true)
	play_with_ia(p_ia->getX(), p_ia->getY());
      else if (you->getTurn() == false && p_ia->getTurn() == false)
	std::cout << "probleme \n";
      window.clear();
      display_plate();
      window.display();      
    }
}

void	GameEngine::loop()
{
  Vector2i	pos;

  std::cout << "loop" << std::endl;
  while (window.isOpen())
    {
      while (window.pollEvent(event))
        {
          if (event.type == Event::Closed)
            window.close();
	  if (Mouse::isButtonPressed(Mouse::Left))
	    {
	      while (Mouse::isButtonPressed(Mouse::Left))
		;
	      pos = Mouse::getPosition(window);
	      if (pos.x >= 0 && pos.x <= 1000 && pos.y >= 0 && pos.y <= 1075 && play(pos.x, pos.y) == true)
		affiche_winner();
	    }
        }
      window.clear();
      display_plate();
      window.display();      
    }
}


std::vector<Case >	GameEngine::getCases() const
{
  return (this->cases);
}

sf::Texture const&	GameEngine::getCenterEmpty() const
{
  return (this->center_empty);
}

bool			GameEngine::getRulesPions() const
{
  return (rules_pions);
}

void			GameEngine::setRules(bool rule_took, bool rule_five_b, bool rule_double_three, bool rule_possible)
{
  arbitre->setRules(rule_took, rule_five_b, rule_double_three);
  rules_pions = rule_possible;
  if (rules_pions == false)
    possible.clear();
}
