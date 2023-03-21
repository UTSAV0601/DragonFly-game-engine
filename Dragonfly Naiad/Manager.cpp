#include "Manager.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"



df::Manager::Manager()
{
	m_is_started = false;
}

int df::Manager::startUp()  // return 0 if the value of m_is_started is true
{
	m_is_started = true;
	return 0;
}

void df::Manager::shutDown()    //
{
	m_is_started = false;
}

bool df::Manager::isStarted() const   // to return the value of boolean m_is_started
{
	return m_is_started;
}
void df::Manager::setType(std::string type)
{
	m_type = "Manager";  // to set the type of manager to type

}
std::string df::Manager::getType() const 
{
	return m_type;   // to get type of m_type
}

df::Manager::~Manager()
{
	shutDown();   
}

// Send event to all Objects.
// Return count of number of events sent.

int df::Manager::onEvent(const Event* p_event) const
{
	int count = 0;

	ObjectList all_Objects = WM.getAllObjects();
	ObjectListIterator iter(&all_Objects) ;
	for (iter.first(); !iter.isDone(); iter.next())
	{
		iter.currentObject()->eventHandler(p_event);
		count++;
	}


	return count;

}