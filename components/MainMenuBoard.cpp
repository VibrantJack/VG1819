#include "components\MainMenuBoard.h"

#include "kitten\K_GameObject.h"
#include "unit\UnitSpawn.h"
#include "unit\unitComponent\UnitMove.h"
#include <time.h>
#include <algorithm>

MainMenuBoard::MainMenuBoard()
{
	srand(time(NULL));
}

MainMenuBoard::~MainMenuBoard()
{
}

void MainMenuBoard::start()
{
	int units[] = { 
		unit::UnitSpawn::Priest, unit::UnitSpawn::Archer, unit::UnitSpawn::Duelist, 
		unit::UnitSpawn::Engineer, unit::UnitSpawn::newUnitObject, unit::UnitSpawn::Pyromancer, 
		unit::UnitSpawn::StoneSlinger, unit::UnitSpawn::Oligarch, unit::UnitSpawn::King, unit::UnitSpawn::Queen 
	};
	std::random_shuffle(units, units + (sizeof(units)/sizeof(*units)));

	kitten::K_GameObject* archer = unit::UnitSpawn::getInstanceSafe()->spawnSimpleUnitObject(units[0]); // Archer
	archer->getComponent<unit::UnitMove>()->setTile(5, 4);

	kitten::K_GameObject* commander = unit::UnitSpawn::getInstanceSafe()->spawnSimpleUnitObject(units[1]); // Wizard/Commander
	commander->getComponent<unit::UnitMove>()->setTile(6, 5);

	kitten::K_GameObject* engineer = unit::UnitSpawn::getInstanceSafe()->spawnSimpleUnitObject(units[2]); // Engineer
	engineer->getComponent<unit::UnitMove>()->setTile(8, 5);

	kitten::K_GameObject* duelist = unit::UnitSpawn::getInstanceSafe()->spawnSimpleUnitObject(units[3]); // Duelist
	duelist->getComponent<unit::UnitMove>()->setTile(9, 4);	

	//printf("Spawned units: %d, %d, %d, %d\n", units[0], units[1], units[2], units[3]);
}