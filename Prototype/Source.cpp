#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


// Абстрактный класс аппаратного устройства
class AbstractDevice abstract
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
	virtual AbstractDevice* Clone() abstract;
};

class Box : public AbstractDevice
{
	string color;
public:
	string GetColor()
	{
		return this->color;
	}
	void SetColor(string color)
	{
		this->color = color;
	}
	AbstractDevice* Clone() override
	{
		Box * box = new Box;
		*box = *this;
		return box;
	}
};

class Memory : public AbstractDevice
{
	int volume;
	string type;
public:
	string GetType()
	{
		return this->type;
	}
	void SetType(string type)
	{
		this->type = type;
	}
	int GetVolume()
	{
		return this->volume;
	}
	void SetVolume(int volume)
	{
		this->volume = volume;
	}
	AbstractDevice* Clone() override
	{
		Memory * memory = new Memory;
		*memory = *this;
		return memory;
	}
};

class Hdd : public AbstractDevice
{
	int volume;
	string type;
public:
	string GetType()
	{
		return this->type;
	}
	void SetType(string type)
	{
		this->type = type;
	}
	int GetVolume()
	{
		return this->volume;
	}
	void SetVolume(int volume)
	{
		this->volume = volume;
	}
	AbstractDevice* Clone() override
	{
		Hdd * hdd = new Hdd;
		*hdd = *this;
		return hdd;
	}
};

class Processor : public AbstractDevice
{
	int corecount;
	double frequency;
public:
	double GetFrequency()
	{
		return this->frequency;
	}
	void SetFrequency(double frequency)
	{
		this->frequency = frequency;
	}
	int GetCoreCount()
	{
		return this->corecount;
	}
	void SetCoreCount(int corecount)
	{
		this->corecount = corecount;
	}
	AbstractDevice* Clone() override
	{
		Processor * processor = new Processor;
		*processor = *this;
		return processor;
	}
};

class VideoCard : public AbstractDevice
{
	int volume;
public:
	int GetVolume()
	{
		return this->volume;
	}
	void SetVolume(int volume)
	{
		this->volume = volume;
	}
	AbstractDevice* Clone() override
	{
		VideoCard * videocard = new VideoCard;
		*videocard = *this;
		return videocard;
	}
};

class Mainboard : public AbstractDevice
{
	double busfrequency;
	VideoCard* videocard;
public:
	double GetBusFrequency()
	{
		return this->busfrequency;
	}
	void SetBusFrequency(double busfrequency)
	{
		this->busfrequency = busfrequency;
	}
	VideoCard* GetVideoCard()
	{
		return this->videocard;
	}
	void SetVideoCard(VideoCard* videocard)
	{
		this->videocard = videocard;
	}
	AbstractDevice* Clone() override
	{
		Mainboard *newObj = new Mainboard;
		*newObj = *this;
		newObj->videocard = this->videocard != nullptr? (VideoCard*) this->videocard->Clone() : nullptr;
		return newObj;
	}
};

/*
 Прототип (Prototype) порождающий шаблон проектирования, который предназначен для создания объекта
 через клонирование другого объекта вместо создания посредством конструктора.
Паттерн используется чтобы:
-	избежать дополнительных усилий по созданию объекта стандартным путем (использование ключевого слова new,
	когда создается не только сам объект, но и вся иерархия предков объекта),
	когда это непозволительно дорого для приложения.
-	избежать наследования создателя объекта (object creator) в клиентском приложении, как это делает паттерн abstract factory.
*/

class Prototype abstract
{
public:
	 virtual Prototype* Clone() abstract;
};

class PersonalComputer: public Prototype
{
	Box* box;
	Mainboard* mainboard;
	Processor* processor;
	VideoCard* videocard;
	vector<Memory*> memories;
	vector<Hdd*> hdd;
public:
	Box* GetBox()
	{
		return this->box;
	}
	void SetBox(Box* box)
	{
		this->box = box;
	}
	Processor* GetProcessor()
	{
		return this->processor;
	}
	void SetProcessor(Processor* processor)
	{
		this->processor = processor;
	}
	Mainboard* GetMainboard()
	{
		return this->mainboard;
	}
	void SetMainboard(Mainboard* mainboard)
	{
		this->mainboard = mainboard;
	}
	VideoCard* GetVideoCard()
	{
		return this->videocard;
	}
	void SetVideoCard(VideoCard* videocard)
	{
		this->videocard = videocard;
	}
	vector<Memory*>& GetMemories()
	{
		return memories;
	}
	void AddMemory(Memory * m)
	{
		memories.push_back(m);
	}
	vector<Hdd*>& GetHdd()
	{
		return hdd;
	}
	void AddHdd(Hdd * hdd)
	{
		this->hdd.push_back(hdd);
	}
	Prototype* Clone() override
	{
		PersonalComputer *pc = new PersonalComputer;
		pc->box = this->box != nullptr ? (Box*)this->box->Clone(): nullptr;
		pc->mainboard = this->mainboard != nullptr ? (Mainboard*)this->mainboard->Clone(): nullptr;
		pc->processor = this->processor != nullptr ? (Processor*)this->processor->Clone() : nullptr;
		pc->videocard = this->videocard != nullptr ? (VideoCard*)this->videocard->Clone() : nullptr;
		for(Memory* m : this->memories)
		{
			if (m != nullptr)
			{
				pc->AddMemory((Memory*)m->Clone());
			}
		}
		for (Hdd* h : this->hdd)
		{
			if (h != nullptr)
			{
				pc->AddHdd((Hdd*)h->Clone());
			}
		}		
		return pc;
	}
};

//	Класс палитры типичных конфигураций
class PcPrototypes
{
	// Словарь, в котором хранятся прототипы конфигураций
	map<string, PersonalComputer*> pcprototypes;
public:
	PcPrototypes()
	{
		// инициализация палитры прототипами конфигураций
		InitializePcPrototypes();
	}


	// Доступ к прототипу конфигурации по его имени
	PersonalComputer* operator[](string key)
	{
		return  pcprototypes[key];
	}
	void InitializePcPrototypes()
	{
		pcprototypes["Home"] = CreateHomeConfig();
		pcprototypes["Office"] = CreateOfficeConfig();
		pcprototypes["Game"] = CreateGamerConfig();
	}

	PersonalComputer* CreateHomeConfig()
	{
		PersonalComputer* config = new PersonalComputer();

		Box* box = new Box();
		box->SetColor("Silver");
		config->SetBox(box);

		Mainboard* mainboard = new Mainboard();
		mainboard->SetProducer("ATI");
		mainboard->SetBusFrequency(800);
		mainboard->SetVideoCard(nullptr);
		config->SetMainboard(mainboard);

		Processor* processor = new Processor();
		processor->SetProducer("Intel");
		processor->SetCoreCount(2);
		processor->SetFrequency(3);
		config->SetProcessor(processor);

		VideoCard* videocard = new VideoCard();
		videocard->SetProducer("ATI");
		videocard->SetVolume(1024);
		config->SetVideoCard(videocard);

		Hdd* hdd = new Hdd();
		hdd->SetProducer("Samsung");
		hdd->SetType("SATA");
		hdd->SetVolume(500);
		config->AddHdd(hdd);

		Memory* memory = new Memory();
		memory->SetType("DDR2");
		memory->SetVolume(2);
		config->AddMemory(memory);

		return config;
	}

	PersonalComputer* CreateOfficeConfig()
	{
		PersonalComputer* config = new PersonalComputer();

		Box* box = new Box();
		box->SetColor("White");
		config->SetBox(box);

		Mainboard* mainboard = new Mainboard();
		mainboard->SetProducer("Albatron");
		mainboard->SetBusFrequency(800);

		VideoCard* videocard = new VideoCard();
		videocard->SetProducer("nVidia");
		videocard->SetVolume(1024);
		mainboard->SetVideoCard(videocard);
		config->SetMainboard(mainboard);

		Processor* processor = new Processor();
		processor->SetProducer("AMD");
		processor->SetCoreCount(1);
		processor->SetFrequency(1.8);
		config->SetProcessor(processor);

		Hdd* hdd = new Hdd();
		hdd->SetProducer("LG");
		hdd->SetType("SATA");
		hdd->SetVolume(160);
		config->AddHdd(hdd);

		Memory* memory = new Memory();
		memory->SetType("DDR2");
		memory->SetVolume(1);
		config->AddMemory(memory);

		config->SetVideoCard(nullptr);

		return config;
	}

	PersonalComputer* CreateGamerConfig()
	{
		PersonalComputer* config = new PersonalComputer();

		Box* box = new Box();
		box->SetColor("Black");
		config->SetBox(box);

		Mainboard* mainboard = new Mainboard();
		mainboard->SetProducer("Asus");
		mainboard->SetBusFrequency(800);
		mainboard->SetVideoCard(nullptr);
		config->SetMainboard(mainboard);

		Processor* processor = new Processor();
		processor->SetProducer("Intel");
		processor->SetCoreCount(4);
		processor->SetFrequency(4);
		config->SetProcessor(processor);

		VideoCard* videocard = new VideoCard();
		videocard->SetProducer("nVidia");
		videocard->SetVolume(1024);
		config->SetVideoCard(videocard);

		Hdd* hdd = new Hdd();
		hdd->SetProducer("WD");
		hdd->SetType("SATA2");
		hdd->SetVolume(1024);
		config->AddHdd(hdd);

		Memory* memory = new Memory();
		memory->SetType("DDR2");
		memory->SetVolume(4);
		config->AddMemory(memory);

		return config;
	}
};

void PrintPc(PersonalComputer *pc)
{
	cout << "PC configuration: " << endl;
	cout << "Box: " << pc->GetBox()->GetColor() << endl;
	cout << "Mainboard: " << pc->GetMainboard()->GetProducer() << pc->GetMainboard()->GetBusFrequency() << " MHz" << endl;
	if (pc->GetMainboard()->GetVideoCard() != nullptr)
	{
		cout << "Integrated VideoCard: " << pc->GetMainboard()->GetVideoCard()->GetProducer()
			 << pc->GetMainboard()->GetVideoCard()->GetVolume() << " Mb" << endl;
	}
	cout << "Processor: " << pc->GetProcessor()->GetProducer()
		 << pc->GetProcessor()->GetFrequency() << " GHz "
		 << pc->GetProcessor()->GetCoreCount() << " core" << endl;
	cout << "Memories: ";
	for(Memory *m : pc->GetMemories())
	{
		cout << m->GetType() << "  " << m->GetVolume() << " Gb\n";
	}
	cout << "Hdds: ";
	for(Hdd *h : pc->GetHdd())
	{
		cout << h->GetProducer() <<"  " << h->GetType() << "  " << h->GetVolume() << " Gb\n";
	}
	
	if (pc->GetVideoCard() != nullptr)
	{
		cout << "VideoCard: ";
		cout << pc->GetVideoCard()->GetProducer() << "  " << pc->GetVideoCard()->GetVolume() << " Mb\n";
	}
}

int main()
{
	// Ввести имя прототипа конфигурации
	cout << "Enter config prototype name: ";
	string prototypeName;
	cin >> prototypeName;
	PcPrototypes pc;
	// Получение прототипа конфигурации из палитры по его имени
	PersonalComputer *prototype = pc[prototypeName];
	if (prototype != nullptr)
	{
		// Создание конфигурации на основе выбранного прототипа
		PersonalComputer *pc = dynamic_cast<PersonalComputer*>(prototype->Clone());
		// Вывод состава конфигурации на консоль
		PrintPc(pc);
	}
	else
	{
		cout << "Error: incorrect config name";
	}

	system("pause");
}

