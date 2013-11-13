#pragma once
#include "MainData.h"
#include <map>
#include <functional>

using namespace std;
class ActionManager final
{
public:
	ActionManager(void);
	~ActionManager(void);

	void AddAction(const tstring& tag, Action action);
	void RemoveAction(const tstring& tag);
	void RemoveAllActions();
	bool IsActionPresent(const tstring& tag)const;
	Action GetAction(const tstring& tag);

private:
	map<tstring,Action> m_ActionsMap;

private:
	ActionManager(ActionManager& t);
	ActionManager& operator=(ActionManager& t);
};