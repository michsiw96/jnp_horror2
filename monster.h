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
	Monster() { }

public:
	Monster(HealthPoints health, AttackPower attackPower)
	: health(health), damage(attackPower) { }

	virtual HealthPoints getHealth() const {
		return health;
	}

	virtual AttackPower getAttackPower() const  {
		return damage;
	}

	virtual void takeDamage(AttackPower damage) {
		health = std::max(health - damage, .0f);
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

class GroupOfMonsters : public Monster {
private:
	std::vector<Monster> monsters;

public:
	GroupOfMonsters(const std::vector<Monster>& monsters) : monsters(monsters) { }

	virtual HealthPoints getHealth() const override {
		int sum = 0;
		for (Monster x : monsters) {
			sum += x.getHealth();
		}

		return sum;
	}

	virtual AttackPower getAttackPower() const override {
		int sum = 0;
		for (Monster const& x : monsters) {
			sum += x.getAttackPower();
		}

		return sum;
	}

	virtual void takeDamage(AttackPower damage) override {
		for (Monster& x : monsters) {
			x.takeDamage(damage);
		}
	}
};

#endif /* MONSTER_H */