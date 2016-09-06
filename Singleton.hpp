#ifndef		SINGLETON_HPP_
# define	SINGLETON_HPP_

template<typename T> class Singleton
{
public:
  static T& Instance()
  {
    static T theSingleInstance;
    return theSingleInstance;
  }
};

#endif
