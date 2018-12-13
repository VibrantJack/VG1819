#include "components\MainMenuBoard.h"

#include "kitten\K_GameObject.h"
#include "unit\UnitSpawn.h"
#include "unit\unitComponent\UnitMove.h"


MainMenuBoard::MainMenuBoard()
{

}

MainMenuBoard::~MainMenuBoard()
{
}

void MainMenuBoard::start()
{
	kitten::K_GameObject* archer = unit::UnitSpawn::getInstanceSafe()->spawnSimpleUnitObject(2); // Archer
	archer->getComponent<unit::UnitMove>()->setTile(5, 4);

	kitten::K_GameObject* commander = unit::UnitSpawn::getInstanceSafe()->spawnSimpleUnitObject(6); // Wizard/Commander
	commander->getComponent<unit::UnitMove>()->setTile(6, 5);

	kitten::K_GameObject* engineer = unit::UnitSpawn::getInstanceSafe()->spawnSimpleUnitObject(4); // Engineer
	engineer->getComponent<unit::UnitMove>()->setTile(8, 5);

	kitten::K_GameObject* duelist = unit::UnitSpawn::getInstanceSafe()->spawnSimpleUnitObject(3); // Duelist
	duelist->getComponent<unit::UnitMove>()->setTile(9, 4);	
}