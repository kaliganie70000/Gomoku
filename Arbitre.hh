//
// Arbitre.hh for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Sat Jun 21 15:10:00 2014 Antoine ROY
// Last update Thu Nov  6 13:43:16 2014 adrien perez
//

#ifndef	__ARBITRE__
#define	__ARBITRE__

#include "Case.hh"
#include "Player.hh"

class	Case;

class	Arbitre
{

public:

  Arbitre(std::vector<Case >& cases, Player *, Player *);
  ~Arbitre();

private:

  std::vector<Case >	*cp_cases;
  Player		*p1;
  Player		*p2;
  bool			rules_taked;
  bool			rules_five_b;
  bool			rules_double_three;
  int			x_to;
  int			y_to;

public:

  bool	rules(Player *, int, int);
  void	take_two_pions(Player *);
  void	destroy_pions(Player *, std::vector<Case >::iterator, std::vector<Case >::iterator);
  bool	five_breakable(std::string, int, int);
  bool	check_breakable_all(std::string const&, std::string const&, int, int, int);
  bool	five_breakable_hori(std::string const&, std::string const&, int);
  bool	five_breakable_verti(std::string const&, std::string const&, int);
  bool	five_breakable_diag_hg_bd(const std::string&, const std::string&, int);
  bool	five_breakable_diag_bg_hd(const std::string&, const std::string&, int);
  bool	double_three(int, int);
  int	five_concecutif(Player *);

  void	setRules(bool, bool, bool);
  bool	getRulesFive();
  bool	getRulesTaked();
  bool	rechange_color();
};

#endif
