#ifndef ENGINESTATE_HPP
#define ENGINESTATE_HPP

#include "singleton.hpp"


class engineState : public singleton<engineState> {
protected:
	bool global_exit;
public:
	engineState();
	void setExit(bool exit);
	bool exit();

};

#endif