//
// Menu.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Thu Jul 10 00:39:17 2014 Antoine ROY
// Last update Thu Nov  6 00:56:42 2014 etienne bondot
//

#include <iostream>
#include <sstream>
#include <ostream>
#include "Menu.hh"
#include "Exception.hpp"

Menu::Menu()
  : _screen_dim(1000, 1075),
    _window(sf::VideoMode(_screen_dim.x, _screen_dim.y, 32), "Gomoku !"),
    _current_step(GAME_TYPE),
    _game_type(GAME_TYPE_NORMAL),
    _difficulty(DIFFICULTY_EASY),
    _enter_host(false),
    _focus(1)
{
  _window.setKeyRepeatEnabled(false);
  _window.setFramerateLimit(60);
  initSprites();
  initAllText();
  initRules();
}

Menu::~Menu()
{}

sf::Text	Menu::initText(const sf::Font &f, const std::string &str, int size, const sf::Color &c, sf::Vector2f pos)
{
  sf::Text	txt;
  sf::FloatRect	title_rect;

  txt.setFont(f);
  txt.setString(str);
  txt.setCharacterSize(size);
  txt.setColor(c);
  title_rect = txt.getLocalBounds();
  txt.setOrigin(title_rect.left + title_rect.width / 2.f, title_rect.top + title_rect.height / 2.f);
  txt.setPosition(sf::Vector2f(pos.x, pos.y));
  return (txt);
}

void		Menu::initSprites()
{
  if (!_font.loadFromFile("font/JKAbode-Demo.ttf") ||
      !_font_line.loadFromFile("font/underscr.ttf") ||
      !_font_host.loadFromFile("font/Roboto-Light.ttf") ||
      !_t_background.loadFromFile("img/background_menu.png") ||
      !_t_white_square.loadFromFile("img/white_square.png") ||
      !_t_white_square_focus.loadFromFile("img/white_square_focus.png"))
    throw Exception::LoadFromFileException();

  _s_background.setTexture(_t_background);
  _s_white_square_host.setTexture(_t_white_square);
  _s_white_square_host.setPosition(sf::Vector2f(_screen_dim.x / 4.f, _screen_dim.y / 2.f));
  _s_white_square_port.setTexture(_t_white_square);
  _s_white_square_port.setPosition(sf::Vector2f(_screen_dim.x / 4.f, _screen_dim.y / 2.f + 100.f));

  _s_white_square_host_focus.setTexture(_t_white_square_focus);
  _s_white_square_host_focus.setPosition(sf::Vector2f(_screen_dim.x / 4.f, _screen_dim.y / 2.f));
  _s_white_square_port_focus.setTexture(_t_white_square_focus);
  _s_white_square_port_focus.setPosition(sf::Vector2f(_screen_dim.x / 4.f, _screen_dim.y / 2.f + 100.f));

  _m_sprite_host[FOCUS] = _s_white_square_host_focus;
  _m_sprite_host[NO_FOCUS] = _s_white_square_host;
  _m_sprite_port[FOCUS] = _s_white_square_port_focus;
  _m_sprite_port[NO_FOCUS] = _s_white_square_port;
}

void		Menu::initAllText()
{
  _m_all_txt[GAME_TITLE] = initText(_font, "gomoku", 100, sf::Color::Black, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 4.f));
  _m_all_txt[PRESS_ENTER] = initText(_font, "press enter to play", 100, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y - 140.f));
  _m_all_txt[FPS_DISPLAY] = initText(_font, "fps ", 20, sf::Color::Black, sf::Vector2f(50.f, _screen_dim.y - 50.f));
  _m_all_txt[ARROW_GAME_TYPE_LEFT] = initText(_font, "(", 20, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f - _screen_dim.x / 5.f, _screen_dim.y / 2.f));
  _m_all_txt[ARROW_GAME_TYPE_RIGHT] = initText(_font, ")", 20, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f + _screen_dim.x / 5.f, _screen_dim.y / 2.f));
  _m_all_txt[ARROW_DIFF_LEFT] = initText(_font, "(", 20, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f - _screen_dim.x / 5.f, _screen_dim.y / 2.f + 270.f));
  _m_all_txt[ARROW_DIFF_RIGHT] = initText(_font, ")", 20, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f + _screen_dim.x / 5.f, _screen_dim.y / 2.f + 270.f));
  _m_all_txt[OPTION_TITLE] = initText(_font, ".... Options ........................................................", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f + 40.f));
  _m_all_txt[LINE_1_OPTION] = initText(_font_line, "___", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f + 170.f, _screen_dim.y / 2.f + 115.f));
  _m_all_txt[LINE_2_OPTION] = initText(_font_line, "___", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f + 170.f, _screen_dim.y / 2.f + 155.f));
  _m_all_txt[LINE_3_OPTION] = initText(_font_line, "___", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f + 170.f, _screen_dim.y / 2.f + 195.f));
  _m_all_txt[LINE_4_OPTION] = initText(_font_line, "___", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f + 170.f, _screen_dim.y / 2.f + 235.f));
  _m_all_txt[OPTION_FIVE_BREAKABLE] = initText(_font, "5 pions cassables          yes   no", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f + 95.f));
  _m_all_txt[OPTION_PAWN_TAKABLE] = initText(_font, "pion prenable                  yes   no", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f + 135.f));
  _m_all_txt[OPTION_DOUBLE_THREE] = initText(_font, "double trois                       yes   no", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f + 175.f));
  _m_all_txt[OPTION_PAWN_POSSIBLE] = initText(_font, "pion possible                    yes   no", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f + 215.f));
  _m_all_txt[DIFFICULTY_EASY] = initText(_font, "easy", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f + 270.f));
  _m_all_txt[DIFFICULTY_MEDIUM] = initText(_font, "medium", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f + 270.f));
  _m_all_txt[DIFFICULTY_HARD] = initText(_font, "hard", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f + 270.f));
  _m_all_txt[HOST] = initText(_font, "host", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 3.f - 25.f, _screen_dim.y / 2.f - 25.f));
  _m_all_txt[PORT] = initText(_font, "port", 30, sf::Color::White, sf::Vector2f(_screen_dim.x / 3.f - 25.f, _screen_dim.y / 2.f + 75.f));
  _m_all_txt[HOST_DISPLAY] = initText(_font_host, "", 30, sf::Color::Black, sf::Vector2f(_screen_dim.x / 4.f + 10.f, _screen_dim.y / 2.f + 5.f));
  _m_all_txt[PORT_DISPLAY] = initText(_font_host, "", 30, sf::Color::Black, sf::Vector2f(_screen_dim.x / 4.f + 10.f, _screen_dim.y / 2.f + 105.f));
  _m_all_txt[GAME_TYPE_NORMAL] = initText(_font, "player vs player", 30, sf::Color::Black, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f));
  _m_all_txt[GAME_TYPE_IA] = initText(_font, "player vs ia", 30, sf::Color::Black, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f));
  _m_all_txt[GAME_TYPE_ONLINE] = initText(_font,"online", 30, sf::Color::Black, sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y / 2.f));
  _m_step[GAME_TYPE] = &_m_all_txt[GAME_TYPE_NORMAL];
  _m_step[RULE_1] = &_m_all_txt[OPTION_FIVE_BREAKABLE];
  _m_step[RULE_2] = &_m_all_txt[OPTION_PAWN_TAKABLE];
  _m_step[RULE_3] = &_m_all_txt[OPTION_DOUBLE_THREE];
  _m_step[RULE_4] = &_m_all_txt[OPTION_PAWN_POSSIBLE];
  _m_step[RUN] = &_m_all_txt[PRESS_ENTER];
}

void		Menu::initRules()
{
  _m_rules[FIVE_BREAKABLE] = false;
  _m_rules[PAWN_TAKABLE] = false;
  _m_rules[DOUBLE_THREE] = false;
  _m_rules[PAWN_POSSIBLE] = false;
}

void		Menu::changeGameType(int type)
{
  if (_current_step != GAME_TYPE)
    return;
  if (type < GAME_TYPE_NORMAL)
    type = GAME_TYPE_ONLINE;
  else if (type > GAME_TYPE_ONLINE)
    type = GAME_TYPE_NORMAL;
  _game_type = static_cast<eText>(type);
  _m_all_txt[_game_type].setColor(sf::Color::Black);
}

void		Menu::changeGameDifficulty(int diff)
{
  if (_current_step != DIFFICULTY)
    return;
  if (diff < DIFFICULTY_EASY)
    diff = DIFFICULTY_HARD;
  else if (diff > DIFFICULTY_HARD)
    diff = DIFFICULTY_EASY;
  _difficulty = static_cast<eText>(diff);
  _m_all_txt[_difficulty].setColor(sf::Color::Black);
}

void		Menu::changeOption()
{
  if (!_current_step)
    return;
  _m_rules[static_cast<eRule>(_current_step - 1)] = !_m_rules[static_cast<eRule>(_current_step - 1)];
}

void		Menu::changeCurrentStep(int step)
{
  if (step > NB_STEP - 1)
    step--;
  else if (step < 0)
    step = 0;
  _current_step = static_cast<eStep>(step);
  resetColor();
  if (_current_step == GAME_TYPE)
    _m_all_txt[_game_type].setColor(sf::Color::Black);
  else if (_current_step == DIFFICULTY)
    _m_all_txt[_difficulty].setColor(sf::Color::Black);
  else
    _m_step[_current_step]->setColor(sf::Color::Black);
}

void		Menu::changeChoicePos()
{  
  if (_current_step == GAME_TYPE || _current_step == DIFFICULTY)
    return;
  if (_current_step == RULE_1)
    {
      if(_m_rules[static_cast<eRule>(_current_step - 1)])
	_m_all_txt[LINE_1_OPTION].setPosition(sf::Vector2f(_screen_dim.x / 2.f + 115.f, _screen_dim.y / 2.f + 115.f));
      else
	_m_all_txt[LINE_1_OPTION].setPosition(sf::Vector2f(_screen_dim.x / 2.f + 170.f, _screen_dim.y / 2.f + 115.f));
    }
  else if (_current_step == RULE_2)
    {
      if(_m_rules[static_cast<eRule>(_current_step - 1)])
	_m_all_txt[LINE_2_OPTION].setPosition(sf::Vector2f(_screen_dim.x / 2.f + 115.f, _screen_dim.y / 2.f + 155.f));
      else
	_m_all_txt[LINE_2_OPTION].setPosition(sf::Vector2f(_screen_dim.x / 2.f + 170.f, _screen_dim.y / 2.f + 155.f));
    }
  else if (_current_step == RULE_3)
    {
      if(_m_rules[static_cast<eRule>(_current_step - 1)])
	_m_all_txt[LINE_3_OPTION].setPosition(sf::Vector2f(_screen_dim.x / 2.f + 115.f, _screen_dim.y / 2.f + 195.f));
      else
	_m_all_txt[LINE_3_OPTION].setPosition(sf::Vector2f(_screen_dim.x / 2.f + 170.f, _screen_dim.y / 2.f + 195.f));
    }
  else if (_current_step == RULE_4)
    {
      if(_m_rules[static_cast<eRule>(_current_step - 1)])
	_m_all_txt[LINE_4_OPTION].setPosition(sf::Vector2f(_screen_dim.x / 2.f + 115.f, _screen_dim.y / 2.f + 235.f));
      else
	_m_all_txt[LINE_4_OPTION].setPosition(sf::Vector2f(_screen_dim.x / 2.f + 170.f, _screen_dim.y / 2.f + 235.f));
    }
}

void		Menu::run()
{
  std::string	str;
  sf::Event	event;

  while (_window.isOpen())
    {
      _elapse = _clock.restart();
      while (_window.pollEvent(event))
	{
	  if (_elapse.asSeconds() > FPS)
	    {
	      if (event.type == sf::Event::Closed)
		_window.close();
	      if (event.type == sf::Event::KeyPressed)
		{
		  if (event.key.code == sf::Keyboard::Left)
		    {
		      changeGameType(static_cast<int>(_game_type) - 1);
		      changeGameDifficulty(static_cast<int>(_difficulty) - 1);
		      changeOption();
		      changeChoicePos();
		    }
		  else if (event.key.code == sf::Keyboard::Right)
		    {
		      changeGameType(static_cast<int>(_game_type) + 1);
		      changeGameDifficulty(static_cast<int>(_difficulty) + 1);
		      changeOption();
		      changeChoicePos();
		    }
		  else if (event.key.code == sf::Keyboard::Up)
		    {
		      changeCurrentStep(static_cast<int>(_current_step) - 1);
		    }
		  else if (event.key.code == sf::Keyboard::Down)
		    {
		      changeCurrentStep(static_cast<int>(_current_step) + 1);
		    }
		  else if (event.key.code == sf::Keyboard::Return)
		    {
		      if (_enter_host)
			startGame();
		      else if (_game_type == GAME_TYPE_ONLINE)
			_enter_host = true;
		      else
			startGame();
		    }
		  else if (event.key.code == sf::Keyboard::Escape)
		    {
		      _window.close();
		    }
		  else if (event.key.code == sf::Keyboard::Tab)
		    {
		      if (_enter_host)
			{
			  _focus = !_focus;
			  str = "";
			}
		    }
		}
	      if (event.type == sf::Event::TextEntered)
		{
		  if (event.text.unicode > 30 && (event.text.unicode < 128 || event.text.unicode > 159))
		    {
		      str += event.text.unicode;
		    }
		  else if (event.text.unicode == 8)
		    {
		      str = str.substr(0, str.size()-1);
		    }
		  _focus ? _m_all_txt[HOST_DISPLAY].setString(str) : _m_all_txt[PORT_DISPLAY].setString(str);
		}
	    }
	  updateFPS();
	}
      draw();
      _window.display();
    }
}

void		Menu::draw()
{
  _window.clear();
  _window.draw(_s_background);
  _window.draw(_m_all_txt[GAME_TITLE]);
  if (_enter_host)
    {
      _window.draw(_m_all_txt[HOST]);
      _window.draw(_m_all_txt[PORT]);
      _window.draw(_m_sprite_host[static_cast<eFocus>(_focus)]);
      _window.draw(_m_sprite_port[static_cast<eFocus>(!_focus)]);
      _window.draw(_m_all_txt[HOST_DISPLAY]);
      _window.draw(_m_all_txt[PORT_DISPLAY]);
    }
  else
    {
      _window.draw(_m_all_txt[_game_type]);
      _window.draw(_m_all_txt[FPS_DISPLAY]);
      _window.draw(_m_all_txt[OPTION_TITLE]);
      _window.draw(_m_all_txt[OPTION_FIVE_BREAKABLE]);
      _window.draw(_m_all_txt[OPTION_PAWN_TAKABLE]);
      _window.draw(_m_all_txt[OPTION_DOUBLE_THREE]);
      _window.draw(_m_all_txt[OPTION_PAWN_POSSIBLE]);
      _window.draw(_m_all_txt[LINE_1_OPTION]);
      _window.draw(_m_all_txt[LINE_2_OPTION]);
      _window.draw(_m_all_txt[LINE_3_OPTION]);
      _window.draw(_m_all_txt[LINE_4_OPTION]);
      _window.draw(_m_all_txt[_difficulty]);
      if (_current_step == GAME_TYPE)
  	{
  	  _window.draw(_m_all_txt[ARROW_GAME_TYPE_LEFT]);
  	  _window.draw(_m_all_txt[ARROW_GAME_TYPE_RIGHT]);
  	}
      else if (_current_step == DIFFICULTY)
  	{
  	  _window.draw(_m_all_txt[ARROW_DIFF_LEFT]);
  	  _window.draw(_m_all_txt[ARROW_DIFF_RIGHT]);
  	}
    }
  _window.draw(_m_all_txt[PRESS_ENTER]);
}

void		Menu::updateFPS()
{
  std::stringstream	ss;

  if (_time_to_refresh.getElapsedTime().asSeconds() > 0.5)
    {
      ss << "fps " << (int)(1 / _elapse.asSeconds());
      _m_all_txt[FPS_DISPLAY].setString(ss.str());
      _time_to_refresh.restart();
    }
}

void		Menu::resetColor()
{
  for (std::map<eText, sf::Text>::iterator it = _m_all_txt.begin();
       it != _m_all_txt.end();
       it++)
    {
      if (it->first != GAME_TITLE)
	it->second.setColor(sf::Color::White);
    }
}

void		Menu::startGame()
{
  displayInformations();
  _window.close();
  if (_game_type == GAME_TYPE_ONLINE)
    {
      GameEngine::Instance().Connection(false, true, std::string(_m_all_txt[PORT_DISPLAY].getString()),
					std::string(_m_all_txt[HOST_DISPLAY].getString()));
      GameEngine::Instance().setRules(_m_rules[PAWN_TAKABLE],
				      _m_rules[FIVE_BREAKABLE],
				      _m_rules[DOUBLE_THREE],
				      _m_rules[PAWN_POSSIBLE]);
      GameEngine::Instance().loop_online();
    }
  else if (_game_type == GAME_TYPE_IA)
    {
      GameEngine::Instance().Connection(true, false,std::string(""), std::string(""));
      GameEngine::Instance().setRules(_m_rules[PAWN_TAKABLE],
				      _m_rules[FIVE_BREAKABLE],
				      _m_rules[DOUBLE_THREE],
				      _m_rules[PAWN_POSSIBLE]);
      GameEngine::Instance().loop_IA();
    }
  else
    {
      GameEngine::Instance().Connection(false, false, std::string(""), std::string(""));
      GameEngine::Instance().setRules(_m_rules[PAWN_TAKABLE],
				      _m_rules[FIVE_BREAKABLE],
				      _m_rules[DOUBLE_THREE],
				      _m_rules[PAWN_POSSIBLE]);
      GameEngine::Instance().loop();
    }
}

void		Menu::displayInformations()
{
  std::cout << "GAME INFORMATIONS________________" << std::endl
	    << "mode: ";
  if (_game_type == GAME_TYPE_NORMAL)
    std::cout << "player vs player" << std::endl;
  else if (_game_type == GAME_TYPE_IA)
    std::cout << "player vs ia" << std::endl;
  else
    {
      std::cout << "online" << std::endl
		<< "host: " << std::string(_m_all_txt[HOST_DISPLAY].getString()) << std::endl
		<< "port: " << std::string(_m_all_txt[PORT_DISPLAY].getString()) << std::endl;
    }
  std::cout << "five pawn breakable: " << (_m_rules[FIVE_BREAKABLE] ? "TRUE" : "FALSE") << std::endl
	    << "pawn takable       : " << (_m_rules[PAWN_TAKABLE] ? "TRUE" : "FALSE") << std::endl
	    << "double three       : " << (_m_rules[DOUBLE_THREE] ? "TRUE" : "FALSE") << std::endl
	    << "pawn possible      : " << (_m_rules[PAWN_POSSIBLE] ? "TRUE" : "FALSE") << std::endl
	    << "difficulty         : ";
  if (_difficulty == DIFFICULTY_EASY)
    std::cout << "easy" << std::endl;
  else if (_difficulty == DIFFICULTY_MEDIUM)
    std::cout << "medium" << std::endl;
  else
    std::cout << "hard" << std::endl;
  std::cout << std::endl;
}
