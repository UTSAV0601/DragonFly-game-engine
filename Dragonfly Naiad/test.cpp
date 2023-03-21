#include "Manager.h"
#include "GameManager.h"
#include "Vector.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h";
#include "Clock.h"
#include "Event.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "DisplayManager.h"
#include "InputManager.h"

#include <Windows.h>
#include <assert.h>
#include<iostream>

bool gameManagerTest();
bool vectorTest();
void objectTest();
bool clockTest();
bool eventTest();
bool worldManagerTest();
bool DisplayTest();
bool InputTest();

int main(int argc, char* argv[]) 
{
	std::cout << "Hello";

	//if (clockTest())
	//	puts("\nPASS");
	//else
	//	puts("\nFAIL");

	//if (vectorTest())
	//	puts("\nPASS");
	//else
	//	puts("\nFAIL");


	gameManagerTest();

	//GM.run();
	//objectTest();
	//worldManagerTest();
	//eventTest();
	//GM.shutDown();

}

bool gameManagerTest() 
{
	GM.startUp();

	DisplayTest();

	GM.run();

	GM.shutDown();
	return true;
}

// Class to test input manager, object and events
class Saucer : public df::Object 
{

public:
	Saucer() 
	{
		setType("Saucer");

		df::Vector pos(7.0f, DM.getVertical() / 2.0f);
		setPosition(pos);
	}

	// TEST EVENTS
	int eventHandler(const df::Event* p_e) {
		if (p_e->getType() == df::KEYBOARD_EVENT) 
		{
			const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
			kbd(p_keyboard_event);
			return 1;
		}

		if (p_e->getType() == df::MSE_EVENT) 
		{
			const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
			mouse(p_mouse_event);
			return 1;
		}

		if (p_e->getType() == df::COLLISION_EVENT) 
		{
			LM.writeLog("COLLISION OCCURED\n");
		}

		if (p_e->getType() == df::STEP_EVENT) 
		{
			LM.writeLog("STEP EVENT\n");
			return 1;
		}

		if (p_e->getType() == df::OUT_EVENT) 
		{
			LM.writeLog("OUT EVENT\n");
			return 1;
		}

		// If get here, have ignored this event.
		return 0;
	}

	void mouse(const df::EventMouse* p_mouse_event) 
	{
		// Pressed button?
		if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
			(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
			std::cout << "Left Button Clicked\n";

		if ((p_mouse_event->getMouseAction() == df::MOVED))
			std::cout << "MOUSE MOVED\n";
	}

	// Take appropriate action according to key pressed.
	void kbd(const df::EventKeyboard* p_keyboard_event) 
	{

		switch (p_keyboard_event->getKey()) 
		{
		case df::Keyboard::W:			// up
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				move(-1);
			break;
		case df::Keyboard::S:			// down
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				move(+1);
			break;
		};

		return;
	}

	void move(int dy) {
		df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
		// If stays on screen, allow move.
		//if ((new_pos.getY() >= 0) &&
		//	(new_pos.getY() < DM.getVertical()))
		WM.moveObject(this, new_pos);
	}


};



bool DisplayTest() {

	df::Object* test_object = new df::Object();
	test_object->setType("Saucer");
	test_object->setAltitude(2);
	test_object->setPosition(df::Vector(0, 0));
	test_object->setSolidness(df::HARD);
	test_object->setDirection(df::Vector(1, 0));
	test_object->setSpeed(0.5f);

	new Saucer;

	df::Object* block_object = new df::Object();
	block_object->setType("Blocker");
	block_object->setAltitude(2);
	block_object->setPosition(df::Vector(30, 0));
	block_object->setSolidness(df::HARD);

	df::Object* block_object2 = new df::Object();
	block_object->setAltitude(2);
	block_object2->setPosition(df::Vector(7, 20));
	block_object2->setSolidness(df::SOFT);
	

	DM.drawString(df::Vector(10, 20), "HELLO", df::LEFT_JUSTIFIED, df::YELLOW);
	return true;

}

	// Clock test.
bool clockTest()
{
	df::Clock clock;

	clock.delta();// Start time
	Sleep(100); 
	int t = (int)clock.split() / 1000000; // About 1 second .


	// Print time to logfile for debugging . 
	LM.writeLog(" split time t is % d", t);

	// See if reported 1 second as expected .
	if (t != 1) {
		LM.writeLog(" split time t is % d", t);
		return false;
	}
	// If we get here , test has passed.
	LM.writeLog(" % s passed.n", __func__);
	return true;
}

// Vector test
bool vectorTest() 
{
	// Create Vector
	df::Vector vec = df::Vector(4.0f, 3.0f);
	LM.writeLog("Vector X, Y Coordinate: %f  %f\n", vec.getX(), vec.getY());

	// Check Test result
	if (vec.getX() != 11.0f && vec.getY() != 11.0f) {
		LM.writeLog("%s FAILED \n", __FUNCTION__);
		return false;
	}
	LM.writeLog("%s PASSED \n", __FUNCTION__);
	return true;

}
 
//Object test
void objectTest() 
{

	//Creating 2 Objects
	LM.writeLog("Creating 2 Objects\n");
	df::Object* newObj = new df::Object();
	newObj->setType("Stone");

	df::Object* test_object2 = new df::Object();
	test_object2->setType("Tree");

	//Getting ObjectList from WM
	LM.writeLog("Getting ObjectList from World Manager\n");
	df::ObjectList test_object_list = WM.getAllObjects();

	// isFull, isEmpty, Count
	LM.writeLog("is Object List Empty: %d \n", test_object_list.isEmpty());
	LM.writeLog("is Object List Full: %d \n", test_object_list.isFull());
	LM.writeLog("Object Count: %d \n", test_object_list.getCount());

	// Using Iterator
	LM.writeLog("Iterating through List using ListIterator\n");
	df::ObjectListIterator list_itr(&test_object_list);
	for (list_itr.first(); !list_itr.isDone(); list_itr.next()) 
	{
		LM.writeLog(" Object type : % s\n", list_itr.currentObject()->getType());
		LM.writeLog(" Object ID: %d \n", list_itr.currentObject()->getId());

	}


}

// World Manager test
bool worldManagerTest() 
{
	
	// Creating 2 Objects
	LM.writeLog("Creating 2 more Objects\n");
	df::Object* newObj = new df::Object();
	newObj->setType("Stone");

	df::Object* test_object2 = new df::Object();
	test_object2->setType("Tree");

	// Getting Objects of one type
	df::ObjectList same_type_list = WM.ObjectsOfType("Saucer");
	LM.writeLog("Number of Stones : %d \n", same_type_list.getCount());

	// Removing one objects
	LM.writeLog("Removing stoones from World\n");
	WM.removeObject(newObj);
	LM.writeLog("Getting all Objects in World\n");
	df::ObjectList test_object_list = WM.getAllObjects();

	LM.writeLog("New Object Count: %d \n", test_object_list.getCount());

	//Marking for Delete
	LM.writeLog("Marking for Delete : ");
	if (WM.markForDelete(test_object2) == 0)
		LM.writeLog(" Success\n");
	else
		LM.writeLog(" Failed\n");
	// Update WM
	WM.update();

	return true;

}

// event test
bool eventTest() 
{
	
	//Creating Event
	df::Event* new_event = new df::Event();
	new_event->setType("Event");

	df::EventStep step_event;

	LM.writeLog("New Event: %s \n", new_event->getType());
	if (new_event->getType() == "TEST_EVENT") {
		LM.writeLog("Success\n");
		return true;
	}

	return false;
}