#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include <functional>
#include <algorithm>
#include "helper.h"

class Monster {
protected:
	HealthPoints health;
	AttackPower damage;
public:
	Monster(HealthPoints health, AttackPower attackPower)
	: health(health), damage(attackPower) { }
	
	HealthPoints getHealth() {
		return health;
	}
	
	AttackPower getAttackPower() {
		return damage;
	}
	
	void takeDamage(AttackPower damage) {
		health.setHealth(std::max(health.getHealth() - damage.getAttackPower(), static_cast<double>(0)));
	}
};

class Zombie : public Monster {
public:
	Zombie(HealthPoints health, AttackPower attackPower) 
		: Monster(health, attackPower) { }
};

class Vampire : public Monster {
public:
	Vampire(HealthPoints health, AttackPower attackPower) 
		: Monster(health, attackPower) { }
};

class Mummy : public Monster {
public:
	Mummy(HealthPoints health, AttackPower attackPower) 
		: Monster(health, attackPower) { }
};

class GroupOfMonsters {
public:
	std::vector<Monster> monsters;
	
	GroupOfMonsters(const std::vector<Monster> &monsters) : monsters(monsters) { }
	
	HealthPoints getHealth() {
		int sum = 0;
		for (Monster x : monsters) {
			sum += x.getHealth().getHealth();
		}
		
		return sum;
	}
	
	AttackPower getAttackPower() {
		int sum = 0;
		for (Monster x : monsters) {
			sum += x.getAttackPower().getAttackPower();
		}
		
		return sum;
	}
	
	void takeDamage(AttackPower damage) {
		for (Monster x : monsters) {
			x.takeDamage(damage);
		}
	}
};

#endif /* MONSTER_H */