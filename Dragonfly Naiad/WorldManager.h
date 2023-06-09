﻿#pragma once

#include "Manager.h"
#include "ObjectList.h"

#define WM df::WorldManager::getInstance()

namespace df 
{
	const int MAX_ALTITUDE = 4;
	class WorldManager : public Manager
	{
	private:
		WorldManager();							// Private (Singleton)
		WorldManager(WorldManager const&);		// Don't Allow copy
		void operator=(WorldManager const&);	// Don't Allow assignment

		ObjectList m_updates;
		ObjectList m_deletions;

	public:
		// Get one and only instance of world manager
		static WorldManager& getInstance();

		// Startup Game world
		int startUp();

		// Shutdown game world 
		// Delete all game world Objects
		void shutDown();

		// Draw all Objects
		void draw();

		// Insert Objects into world.
		// Return 0 if ok, or else -1 
		int insertObject(Object* p_o);

		// Remove Obejcts from world
		// Return 0 if ok, or else -1
		int removeObject(Object* p_o);

		// Return list of all Objects in world
		ObjectList getAllObjects() const;

		// Return List of all objects in the world that matches
		ObjectList ObjectsOfType(std::string type) const;

		// Update World
		// Delete Objects marked for deletion
		void update();

		// Indicate Object is to be deleted at end of current game loop
		// Return 0 if ok, or else -1
		int markForDelete(Object* p_o);

		// Return list of Objects collided with at position ‘where ’.
		// Collisions only with solid Objects.
		// Does not consider if p o is solid or not.
		ObjectList getCollision(Object* p_o, Vector where) const;

		// Move Object .
		// If collision with solid , send collision events .
		// If no collision with solid , move ok else don’t move Object.
		// If Object is Spectral , move ok.
		// Return 0 if move ok, else −1 if collision with solid .
		int moveObject(Object* p_o, Vector where);

	};

}

