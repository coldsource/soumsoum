#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include <Exception/Exception.h>

class GameOver: public Exception
{
public:
	GameOver(int code, const std::string &error): Exception(code, error) {}
};

#endif
