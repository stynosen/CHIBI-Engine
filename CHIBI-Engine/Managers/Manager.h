#pragma once

//!The base class of all managers
/*!This class is a mere buffer class.
It only exists to store the different managers in the same containers
And write methods that would accept them all*/
class Manager
{
public:
	virtual ~Manager(){};
protected:
	Manager(){};
private:
	Manager(Manager& t);
	Manager& operator=(Manager& t);
};