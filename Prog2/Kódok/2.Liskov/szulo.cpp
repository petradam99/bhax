#include <iostream>
#include <string>
using namespace std;

class Szulo{
public:

	void uzenet(){
		cout << "Az uzenet, ami nem fog tovabbitodni a szulo fele." <<endl;
	}
};

class Gyerek : public Szulo{
public:
	void gyerekuzenete(string meguzente){
		cout << meguzente << endl;
	}
};

class Feladat{
	int main(){
		Szulo* vmi = new Szulo();
		Szulo* maszagyvasag = new Gyerek();

		vmi->uzenet();
		maszagyvasag->gyerekuzenete();

		delete vmi;
		delete maszagyvasag;
	}
};