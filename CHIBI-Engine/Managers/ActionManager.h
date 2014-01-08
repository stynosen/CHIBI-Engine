#pragma once
#include "Manager.h"

#include "MainData.h"
#include <map>
#include <functional>

using namespace std;
//!The manager that stores and manages all the actions
class ActionManager final : public Manager
{
public:
	ActionManager(void);
	~ActionManager(void);

	//!Add an action to the manager, with a given tag
	void AddAction(const tstring& tag, Action action);
	//!Remove an action from the manager
	void RemoveAction(const tstring& tag);
	//!Remove all actions from the manager
	void RemoveAllActions();
	//!Check if there is an action with given tag
	bool IsActionPresent(const tstring& tag)const;
	//!Get the action with given tag
	Action GetAction(const tstring& tag);

private:
	//!A map that stores all actions with a tag
	/*!By storing it with a tag, it can be retrieved much faster*/
	map<tstring,Action> m_ActionsMap;

private:
	ActionManager(ActionManager& t);
	ActionManager& operator=(ActionManager& t);
};