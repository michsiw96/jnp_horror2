#ifndef HELPER_H
#define HELPER_H


using HealthPoints = float;
using Age = float;
using AttackPower = float;

class Unit {
public:
	virtual void attackedBy(Unit* unit, AttackPower attackPower) = 0;
};


#endif /* HELPER_H */