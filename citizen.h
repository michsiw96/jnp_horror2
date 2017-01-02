#ifndef CITIZEN_H
#define CITIZEN_H

#include <algorithm>
#include <cassert>
#include "helper.h"

class Citizen {
protected:
	HealthPoints health;
	Age age;
public:
	Citizen(HealthPoints health, Age age) : health(health), age(age) {
		assert(health.getHealth() > 0);
	}
	
	HealthPoints getHealth() {
		return health;
	}
	
	Age getAge() {
		return age;
	}
	
	void takeDamage(AttackPower damage) {
		health.setHealth(std::max(health.getHealth() - damage.getAttackPower(), static_cast<double>(0)));
	}
protected:
	Citizen(HealthPoints health, Age age, double minAge, double maxAge) 
		: Citizen(health, age) {
		
		assert(age.getAge() >= minAge && age.getAge() <= maxAge);
	}
};

class Adult : public Citizen {
public:
	Adult(HealthPoints health, Age age) : Citizen(health, age, 18, 100) { }
};

class Teenager : public Citizen {
public:
	Teenager(HealthPoints health, Age age) : Citizen(health, age, 11, 17) { }
};

class Sheriff : public Citizen {
protected:
	AttackPower damage;
public:
	Sheriff(HealthPoints health, Age age, AttackPower attackPower) 
		: Citizen(health, age), damage(attackPower) { 
		
		assert(attackPower.getAttackPower() > 0);
	}
	
	AttackPower getAttackPower() {
		return damage;
	}
};

#endif /* CITIZEN_H */