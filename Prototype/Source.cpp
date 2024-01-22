#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


class Part abstract
{
protected:
	string producer;

public:
	string GetProducer()
	{
		return this->producer;
	}
	void SetProducer(string producer)
	{
		this->producer = producer;
	}
	// Метод создания клона объекта
	virtual Part* Clone() abstract;
};

class Engine : public Part
{
	string type;
public:
	string GetType()
	{
		return this->type;
	}
	void SetType(string t)
	{
		this->type = t;
	}
	Part* Clone() override
	{
		Engine* eng = new Engine;
		*eng = *this;
		return eng;
	}
};

class gearBox : public Part
{
	bool avtomat;
public:
	bool GetAvtomat()
	{
		return this->avtomat;
	}
	void SetAvtomat(bool t)
	{
		this->avtomat = t;
	}
	Part* Clone() override
	{
		gearBox* eng = new gearBox;
		*eng = *this;
		return eng;
	}
};
class Fluel : public Part
{
	string type;
public:
	string GetType()
	{
		return this->type;
	}
	void SetType(string t)
	{
		this->type = t;
	}
	Part* Clone() override
	{
		Fluel* eng = new Fluel;
		*eng = *this;
		return eng;
	}
};


class Clearence : public Part
{
	int size;
public:
	int GetSize()
	{
		return this->size;
	}
	void SetSize(int t)
	{
		this->size = t;
	}
	Part* Clone() override
	{
		Clearence* eng = new Clearence;
		*eng = *this;
		return eng;
	}
};

class Wheels : public Part
{
	int count;
public:
	int GetCount()
	{
		return this->count;
	}
	void SetType(int t)
	{
		this->count = t;
	}
	Part* Clone() override
	{
		Wheels* eng = new Wheels;
		*eng = *this;
		return eng;
	}
};



class Prototype abstract
{
public:
	virtual Prototype* Clone() abstract;
};

class Car : public Prototype
{
	Engine* engine1;
	Wheels* wheels1;
	Clearence* clierence1;
	gearBox* gearbox1;
	Fluel* fluel1;

public:
	Engine* GetEngine()
	{
		return this->engine1;
	}
	void SetEngine(Engine* box)
	{
		this->engine1 = box;
	}
	Wheels* GetProcessor()
	{
		return this->wheels1;
	}
	void SetWheels(Wheels* w)
	{
		this->wheels1 = w;
	}
	Clearence* GetClearencd()
	{
		return this->clierence1;
	}
	void SetClierence(Clearence* c)
	{
		this->clierence1 = c;
	}
	Fluel* GetFluel()
	{
		return this->fluel1;
	}
	void SetFluel(Fluel* f)
	{
		this->fluel1 = f;
	}
	gearBox* GetgearBox()
	{
		return this->gearbox1;
	}
	void SetGearBox(gearBox* f)
	{
		this->gearbox1 = f;
	}

	Prototype* Clone() override
	{
		Car* car = new Car;
		car->engine1 = this->engine1 != nullptr ? (Engine*)this->engine1->Clone() : nullptr;
		car->fluel1 = this->fluel1 != nullptr ? (Fluel*)this->fluel1->Clone() : nullptr;
		car->clierence1 = this->clierence1 != nullptr ? (Clearence*)this->clierence1->Clone() : nullptr;
		car->gearbox1 = this->gearbox1 != nullptr ? (gearBox*)this->gearbox1->Clone() : nullptr;
		car->wheels1 = this->wheels1 != nullptr ? (Wheels*)this->wheels1->Clone() : nullptr;

		return car;
	}
};



int main()
{


	// Получение прототипа конфигурации из палитры по его имени
	Car* prototype = new Car();
	Clearence* c = new Clearence();
	prototype->SetClierence(c);
	if (prototype != nullptr)
	{
		Car* car = dynamic_cast<Car*>(prototype->Clone());
	}
	else
	{
		cout << "Error: incorrect config name";
	}

	system("pause");
}

