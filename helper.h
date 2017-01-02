#ifndef HELPER_H
#define HELPER_H

class HealthPoints {
private:
	double health;
public:
	HealthPoints(double hp) : health(hp) { }
	
	double getHealth() {
		return health;
	}
	
	void setHealth(double hp) {
		health = hp;
	}
};

class Age {
private:
	const double age;
public:
	Age(double years) : age(years) { }
	
	double getAge() {
		return age;
	}
};

class AttackPower {
private:
	const double damage;
public:
	AttackPower(double attack) : damage(attack) { }
	
	double getAttackPower() {
		return damage;
	}
};

#endif /* HELPER_H */