//
// Exception.hpp for Bomberman in /home/bondot_e/rendu/2/projects_c++/cpp_bomberman
// 
// Made by etienne bondot
// Login   <bondot_e@epitech.net>
// 
// Started on  Wed May  7 10:37:44 2014 etienne bondot
// Last update Sat Oct 25 17:05:49 2014 etienne bondot
//

#ifndef		EXCEPTION_HPP_
# define	EXCEPTION_HPP_

# include <exception>

namespace Exception
{
  class BasicException : public std::exception
  {
  public:
    const char *	what() const throw() { return "Error : the program encounter an error and exit"; }
  };

  class LoadFromFileException : public std::exception
  {
  public:
    const char *	what() const throw() { return "Error : loadFromFile() failed"; }
  };

  class GameDimensionException : public std::exception
  {
  public:
    const char *	what() const throw() { return "Error : game dimension too large"; }
  };

  /** NETWORK **/

  class SocketException : public std::exception
  {
  public:
    const char *	what() const throw() { return "Error : something goes wrong with network"; }
  };

  /** DEFAULT **/

  class SysCallException : public std::exception
  {
  public:
    const char *	what() const throw() { return "Error : syscall failure"; }
  };

  class NullPointerException : public std::exception
  {
  public:
    const char *	what() const throw() { return "Error : Null pointer Exception"; }
  };

}

#endif		/* !EXCEPTION_HPP_ */





