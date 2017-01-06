#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include <memory>
#include "helper.h"

class Monster {
public:
	virtual HealthPoints getHealth() const  = 0;

	virtual AttackPower getAttackPower() const = 0;

	virtual void takeDamage(AttackPower damage) = 0;
};

class ConcreteMonster : public Monster {
protected:
	HealthPoints health;
	AttackPower damage;
public:
	ConcreteMonster(HealthPoints health, AttackPower attackPower)
		: health(health), damage(attackPower) { }

	HealthPoints getHealth() const override {
		return health;
	}

	AttackPower getAttackPower() const override {
		return damage;
	}

	void takeDamage(AttackPower damage) override{
		health = std::max(health - damage, .0f);
	}
};

class Zombie : public ConcreteMonster {
public:
	Zombie(HealthPoints health, AttackPower attackPower)
		: ConcreteMonster(health, attackPower) { }
};

class Vampire : public ConcreteMonster {
public:
	Vampire(HealthPoints health, AttackPower attackPower)
		: ConcreteMonster(health, attackPower) { }
};

class Mummy : public ConcreteMonster {
public:
	Mummy(HealthPoints health, AttackPower attackPower)
		: ConcreteMonster(health, attackPower) { }
};

class GroupOfMonsters : public Monster {
private:
	std::vector<std::shared_ptr<Monster> > monsters;

public:
	GroupOfMonsters(std::vector<std::shared_ptr<Monster> > const& _monsters) : monsters(_monsters) { }
	GroupOfMonsters(std::initializer_list<std::shared_ptr<Monster> > _monsters) : monsters(_monsters) { }

	HealthPoints getHealth() const override {
		int sum = 0;
		for (auto const& x : monsters) {
			sum += x->getHealth();
		}

		return sum;
	}

	AttackPower getAttackPower() const override {
		int sum = 0;
		for (auto const& x : monsters) {
			sum += x->getAttackPower();
		}

		return sum;
	}

	void takeDamage(AttackPower damage) override {
		for (auto& x : monsters) {
			x->takeDamage(damage);
		}
	}
};

std::shared_ptr<Monster> createGroupOfMonsters(std::initializer_list<std::shared_ptr<Monster> > _monsters) {
	return std::make_shared<GroupOfMonsters>(_monsters);
}

std::shared_ptr<Monster> createMummy(int health, int attackPower) {
	return std::make_shared<Mummy>(health, attackPower);
}

std::shared_ptr<Monster> createZombie(int health, int attackPower) {
	return std::make_shared<Zombie>(health, attackPower);
}

std::shared_ptr<Monster> createVampire(int health, int attackPower) {
	return std::make_shared<Vampire>(health, attackPower);
}

#endif /* MONSTER_H */