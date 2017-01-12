#include "citizen.h"
#include "monster.h"
#include "smalltown.h"
#include <iostream>

int main(int argc, const char * argv[]) {
	auto groupOfMonsters = createGroupOfMonsters({
		createMummy(90, 20),
		createZombie(20, 20),
		createVampire(30, 20)
	});
	
	auto greg = createSheriff(100, 35, 20);
	auto anna = createAdult(100, 21);
	auto bobby = createTeenager(50, 14);
	
	auto smallTown = SmallTown::Builder()
	.monster(groupOfMonsters)
	.monster(groupOfMonsters)
	.startTime(2)
	.startTime(3)
	.maxTime(26)
	.maxTime(27)
	.citizen(greg)
	.citizen(anna)
	.citizen(anna)
	.citizen(bobby)
	.build();
	
	smallTown.tick(18);
	smallTown.tick(3);
	
	auto status = smallTown.getStatus();
	assert(status.getMonsterName() == "GroupOfMonsters");
	assert(status.getMonsterHealth() == 80);
	assert(status.getAliveCitizens() == 3);
	
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	smallTown.tick(3);
	
	status = smallTown.getStatus();
	std::cout << status.getMonsterHealth() << " " << status.getAliveCitizens() << std::endl;
	
	
	return 0;
}