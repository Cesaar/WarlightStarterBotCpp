#pragma once

#include <vector>
using namespace std;


class BotState;
class Bot;

class BotParser
{
public:
	BotParser(Bot* inpBot);
	virtual ~BotParser(void);

	void	Run();

private:
	Bot*		mpBot;
	BotState*	mpCurrentstate;
};

