#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include <memory>
#include "helper.h"

class Monster : public Unit {
public:
	virtual HealthPoints getHealth() const  = 0;

	virtual AttackPower getAttackPower() const = 0;

	virtual void takeDamage(AttackPower damage) = 0;
	
	virtual std::string const& getName() const = 0;

	void attack(std::shared_ptr<Unit> unit) {
		unit->attackedBy(this, getAttackPower());
	}

	void attackedBy(Unit* unit, AttackPower damage) override {
		takeDamage(damage);
	}
};

class ConcreteMonster : public Monster {
protected:
	HealthPoints _health;
	AttackPower _damage;
public:
	ConcreteMonster(HealthPoints health, AttackPower attackPower)
		: _health(health), _damage(attackPower) { }

	HealthPoints getHealth() const override {
		return _health;
	}

	AttackPower getAttackPower() const override {
		return _damage;
	}

	void takeDamage(AttackPower damage) override{
		_health = std::max(_health - damage, 0.0f);
	}
};

class Zombie : public ConcreteMonster {
public:
	Zombie(HealthPoints health, AttackPower attackPower)
		: ConcreteMonster(health, attackPower) { }

	std::string const& getName() const override {
		static std::string name = "Zombie";
		return name;
	}
};

class Vampire : public ConcreteMonster {
public:
	Vampire(HealthPoints health, AttackPower attackPower)
		: ConcreteMonster(health, attackPower) { }

	std::string const& getName() const override {
		static std::string name = "Vampire";
		return name;
	}
};

class Mummy : public ConcreteMonster {
public:
	Mummy(HealthPoints health, AttackPower attackPower)
		: ConcreteMonster(health, attackPower) { }

	std::string const& getName() const override {
		static std::string name = "Mummy";
		return name;
	}
};

class GroupOfMonsters : public Monster {
private:
	std::vector<std::shared_ptr<Monster> > _monsters;

public:
	GroupOfMonsters(std::vector<std::shared_ptr<Monster> > const& monsters) : _monsters(monsters) { }
	GroupOfMonsters(std::initializer_list<std::shared_ptr<Monster> > monsters) : _monsters(monsters) { }

	HealthPoints getHealth() const override {
		int sum = 0;
		for (auto const& x : _monsters) {
			sum += x->getHealth();
		}

		return sum;
	}

	AttackPower getAttackPower() const override {
		int sum = 0;
		for (auto const& x : _monsters) {
			if (x->getHealth() > 0)
				sum += x->getAttackPower();
		}

		return sum;
	}

	void takeDamage(AttackPower damage) override {
		for (auto& x : _monsters) {
			if (x->getHealth() > 0)
				x->takeDamage(damage);
		}
	}

	std::string const& getName() const override {
		static std::string name = "GroupOfMonsters";
		return name;
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