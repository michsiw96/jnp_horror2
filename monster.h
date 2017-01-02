#ifndef MONSTER_H
#define MONSTER_H

#include "helper.h"

class Monster {
public:
	HealthPoints getHealth() {
		return HealthPoints(0);
	}

	Age getAge() {
		return Age(0);
	}
};

#endif