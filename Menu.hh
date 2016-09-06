//
// Menu.hh for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Thu Jul 10 00:39:31 2014 Antoine ROY
// Last update Wed Nov  5 22:28:08 2014 etienne bondot
//

#ifndef	__MENU__
#define	__MENU__

#include "GameEngine.hh"
#define	FPS	1. / 60

class Menu
{
  
  typedef	enum
    {
      FIVE_BREAKABLE,
      PAWN_TAKABLE,
      DOUBLE_THREE,
      PAWN_POSSIBLE
    }		eRule;

  typedef	enum
    {
      GAME_TYPE,
      RULE_1,
      RULE_2,
      RULE_3,
      RULE_4,
      DIFFICULTY,
      RUN,
      NB_STEP = 7
    }		eStep;

  typedef	enum
    {
      NO_FOCUS,
      FOCUS
    }		eFocus;

  typedef	enum
    {
      GAME_TITLE,
      FPS_DISPLAY,
      ARROW_GAME_TYPE_LEFT,
      ARROW_GAME_TYPE_RIGHT,
      GAME_TYPE_NORMAL,
      GAME_TYPE_IA,
      GAME_TYPE_ONLINE,
      OPTION_TITLE,
      OPTION_FIVE_BREAKABLE,
      OPTION_PAWN_TAKABLE,
      OPTION_DOUBLE_THREE,
      OPTION_PAWN_POSSIBLE,
      LINE_1_OPTION,
      LINE_2_OPTION,
      LINE_3_OPTION,
      LINE_4_OPTION,
      PRESS_ENTER,
      ARROW_DIFF_LEFT,
      ARROW_DIFF_RIGHT,
      DIFFICULTY_EASY,
      DIFFICULTY_MEDIUM,
      DIFFICULTY_HARD,
      HOST,
      PORT,
      HOST_DISPLAY,
      PORT_DISPLAY
    }		eText;

public:
  
  Menu();
  ~Menu();
  
private:

  sf::Clock			_clock;
  sf::Clock			_time_to_refresh;
  sf::Time			_elapse;

  sf::Vector2i			_screen_dim;
  sf::RenderWindow		_window;
  sf::Texture			_t_background;
  sf::Texture			_t_white_square;
  sf::Texture			_t_white_square_focus;
  sf::Sprite			_s_background;
  sf::Sprite			_s_white_square_host;
  sf::Sprite			_s_white_square_port;
  sf::Sprite			_s_white_square_host_focus;
  sf::Sprite			_s_white_square_port_focus;
  sf::Font			_font;
  sf::Font			_font_line;
  sf::Font			_font_host;

  std::map<eRule, bool>		_m_rules;
  std::map<eStep, sf::Text *>	_m_step;
  std::map<eFocus, sf::Sprite>	_m_sprite_host;
  std::map<eFocus, sf::Sprite>	_m_sprite_port;
  std::map<eText, sf::Text>	_m_all_txt;
  eStep				_current_step;
  eText				_game_type;
  eText				_difficulty;
  bool				_enter_host;
  int				_focus;

public:

  sf::Text	initText(const sf::Font &, const std::string &, int, const sf::Color &, sf::Vector2f);
  void		initSprites();
  void		initAllText();
  void		initRules();
  void		changeGameType(int);
  void		changeGameDifficulty(int);
  void		changeOption();
  void		changeCurrentStep(int);
  void		changeChoicePos();

  void		run();
  void		draw();
  void		updateFPS();
  void		resetColor();
  void		startGame();

  void		displayInformations();

};

#endif
