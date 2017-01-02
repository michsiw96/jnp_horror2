#ifndef CITIZEN_H
#define CITIZEN_H

#include <algorithm>
#include <cassert>
#include <memory>
#include "helper.h"

class Citizen {
protected:
	HealthPoints health;
	Age age;

public:

	HealthPoints getHealth() {
		return health;
	}

	Age getAge() {
		return age;
	}

	void takeDamage(AttackPower damage) {
		health.setHealth(std::max(health.getHealth() - damage.getAttackPower(), 0.0));
	}

protected:
	Citizen(HealthPoints health, Age age, double minAge, double maxAge)
		 : health(health), age(age)  {
		assert(age.getAge() >= minAge && age.getAge() <= maxAge);
		assert(health.getHealth() > 0);
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
		: Citizen(health, age, 18, 100), damage(attackPower) {
		assert(attackPower.getAttackPower() > 0);
	}

	AttackPower getAttackPower() {
		return damage;
	}
};

std::shared_ptr<Citizen> createSheriff(int health, int age, int attackPower) {
	return std::make_shared<Sheriff>(health, age, attackPower);
}

std::shared_ptr<Citizen> createAdult(int health, int age) {
	return std::make_shared<Adult>(health, age);
}

std::shared_ptr<Citizen> createTeenager(int health, int age) {
	return std::make_shared<Teenager>(health, age);
}

#endif /* CITIZEN_H */