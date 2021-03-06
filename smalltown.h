#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include "citizen.h"
#include "monster.h"

using Time = int;

class Status {
private:
	std::string _name;
	HealthPoints _monsterHealth;
	size_t _aliveCitizens;

public:
	Status(std::shared_ptr<Monster> monster, size_t aliveCitizens)
		: _aliveCitizens(aliveCitizens) {
		_name = monster->getName();
		_monsterHealth = monster->getHealth();	
	}

	size_t getAliveCitizens() const { return _aliveCitizens; }
	std::string const& getMonsterName() const { return _name; }
	HealthPoints getMonsterHealth() const { return _monsterHealth; }
};

class AttackTimeStrategy {
public:
	virtual bool isAttackTime(Time time) const = 0;
};

class DivisibleAttackTimeStrategy : public AttackTimeStrategy {
public:
	bool isAttackTime(Time time) const override {
		return (time % 3 == 0 || time % 13 == 0) && time % 7 != 0;
	}
};

class SmallTown {
protected:
	Time _time;
	Time _end;
	std::shared_ptr<Monster> _monster;
	std::vector<std::shared_ptr<Citizen> > _citizens;
	size_t _aliveCitizens;
	std::unique_ptr<AttackTimeStrategy> _attackTimeStrategy;

	static constexpr const char* MSG_CITIZENS_WON = "CITIZENS WON";
	static constexpr const char* MSG_MONSTER_WON = "MONSTER WON";
	static constexpr const char* MSG_DRAW = "DRAW";

	bool isMonsterAlive() const {
		return _monster->getHealth() > 0;
	}

	void computeResults() const {
		if (!isMonsterAlive()) {
			if (_aliveCitizens > 0)
				std::cout << MSG_CITIZENS_WON << "\n";
			else
				std::cout << MSG_DRAW << "\n";
		} else if (_aliveCitizens == 0)
			std::cout << MSG_MONSTER_WON << "\n";
	}

	void attackCitizen(Citizen* citizen) {
		if (citizen->getHealth() > 0) {
			_monster->attack(citizen);
			
			if (citizen->getHealth() == 0) // if citizen died, decrease counter
				--_aliveCitizens;
		}
	}

	void attackAll() {
		for (auto& citizen : _citizens) {
			if (_monster->getHealth() == 0)
				return;
			attackCitizen(citizen.get());
		}
	}


public:

	SmallTown(Time start, Time end, std::vector<std::shared_ptr<Citizen> > const& citizens, std::shared_ptr<Monster> const& monster)
		: _time(start), _end(end), _monster(monster), _citizens(citizens) {
		_attackTimeStrategy = std::make_unique<DivisibleAttackTimeStrategy>();
		_aliveCitizens = citizens.size();
	}

	Status getStatus() const {
		return Status(_monster, _aliveCitizens);
	}

	void tick(Time timeStep) {
		computeResults();

		if (_attackTimeStrategy->isAttackTime(_time) && isMonsterAlive())
			attackAll();

		_time += timeStep;
		_time %= (_end + 1);
	}

	class Builder {
	private:
		Time _startTime;
		Time _maxTime;
		std::shared_ptr<Monster> _monster;
		std::vector<std::shared_ptr<Citizen> > _citizens;
		
		std::set<std::shared_ptr<Citizen> > _wasAlready;

		enum INITIALIZED_FLAGS {
			INITIALIZED_START_TIME = 0x1,
			INITIALIZED_END_TIME = 0x2,
			INITIALIZED_MONSTER = 0x4,
			INITIALIZED_CITIZENS = 0x8,
			INITIALIZED_ALL = INITIALIZED_START_TIME | INITIALIZED_END_TIME | INITIALIZED_MONSTER | INITIALIZED_CITIZENS,
		};

		int _initializedFlags;

	public:
		Builder& startTime(Time time) {
			_startTime = time;
			_initializedFlags |= INITIALIZED_START_TIME;
			return *this;
		}

		Builder& maxTime(Time time) {
			_maxTime = time;
			_initializedFlags |= INITIALIZED_END_TIME;
			return *this;
		}

		Builder& citizen(std::shared_ptr<Citizen> const& citizen) {
			if (_wasAlready.find(citizen) == _wasAlready.end()) {
				_wasAlready.insert(citizen);
				_citizens.push_back(citizen);
			
				_initializedFlags |= INITIALIZED_CITIZENS;	
			}
			
			return *this;
		}

		Builder& monster(std::shared_ptr<Monster> const& monster) {
			_monster = monster;
			_initializedFlags |= INITIALIZED_MONSTER;
			return *this;
		}

		SmallTown build() {
			assert((_initializedFlags & INITIALIZED_ALL) == INITIALIZED_ALL);
			return SmallTown(_startTime, _maxTime, _citizens, _monster);
		}

	};

};

#endif