#include <iostream>
#include "citizen.h"

using namespace std;

int main() {
	Citizen greg = Adult(100, 20);
	Citizen bobby = Teenager(100, 16);
	Sheriff carlos = Sheriff(100, 42, 20);
	
	cout << "Greg taking damage:" << endl;
	cout << greg.getHealth().getHealth() << endl;
	greg.takeDamage(AttackPower(30));
	cout << greg.getHealth().getHealth() << endl;
	assert(greg.getHealth().getHealth() == 70);
	
	cout << "Bobby taking damage:" << endl;
	cout << bobby.getHealth().getHealth() << endl;
	bobby.takeDamage(AttackPower(20));
	cout << bobby.getHealth().getHealth() << endl;
	assert(bobby.getHealth().getHealth() == 80);
	
	cout << "Carlos taking damage:" << endl;
	cout << carlos.getHealth().getHealth() << endl;
	carlos.takeDamage(AttackPower(40));
	cout << carlos.getHealth().getHealth() << endl << endl;
	assert(carlos.getHealth().getHealth() == 60);
	
	cout << "Greg data:" << endl;
	cout << greg.getHealth().getHealth() << " ";
	cout << greg.getAge().getAge() << endl << endl;
	
	cout << "Bobby data:" << endl;
	cout << bobby.getHealth().getHealth() << " ";
	cout << bobby.getAge().getAge() << endl << endl;
	
	cout << "Greg data:" << endl;
	cout << carlos.getHealth().getHealth() << " ";
	cout << carlos.getAge().getAge() << " ";
	cout << carlos.getAttackPower().getAttackPower() << endl << endl;
	
	// shouldn't run without assertion fail
// 	Citizen margaret = Adult(100, 15);
// 	Citizen martha = Adult(100, 104);
// 	Citizen susan = Teenager(100, 20);
// 	Citizen marley = Sheriff(-3, 20, 20);
// 	Citizen mike = Sheriff(100, 20, -3);
	
}