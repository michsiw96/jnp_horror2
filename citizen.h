#ifndef CITIZEN_H
#define CITIZEN_H

#include <algorithm>
#include <cassert>
#include <memory>
#include "helper.h"

class Citizen : public Unit {
protected:
	HealthPoints _health;
	Age _age;

public:

	HealthPoints getHealth() const override {
		return _health;
	}

	Age getAge() const {
		return _age;
	}

	void takeDamage(AttackPower damage) {
		_health = std::max(_health - damage, 0.0f);
	}

	virtual void attackedBy(Unit* unit, AttackPower damage) override {
		takeDamage(damage);
	}

protected:
	Citizen(HealthPoints health, Age age, double minAge, double maxAge)
		 : _health(health), _age(age)  {
		assert(age >= minAge && age <= maxAge);
		assert(health > 0);
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
	AttackPower _damage;
public:
	Sheriff(HealthPoints health, Age age, AttackPower attackPower)
		: Citizen(health, age, 18, 100), _damage(attackPower) {
		assert(attackPower > 0);
	}

	AttackPower getAttackPower() const {
		return _damage;
	}

	void attackedBy(Unit* unit, AttackPower damage) override {
		Citizen::attackedBy(unit, damage);
		unit->attackedBy(this, getAttackPower());
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