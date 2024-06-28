#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Imprimare {
	const int idExemplar;
	char* tipMaterial;
	int nrExemplare;
	float cost;
public:
	//constructor fara parametrii
	Imprimare():idExemplar(1)
	{
		this->tipMaterial = new char[strlen("Necunoscut") + 1];
		strcpy(this->tipMaterial, "Necunoscut");
		this->nrExemplare = 0;
		this->cost = 0;
	}
	//constructor cu parametrii
	Imprimare( int idExemplar, const char* tipMaterial, int nrExemplare, float cost):idExemplar(idExemplar)
	{
		
		this->tipMaterial = new char[strlen(tipMaterial) + 1];
		strcpy(this -> tipMaterial, tipMaterial);
		this->nrExemplare = nrExemplare;
		this->cost = cost;
	}
	//getter
	const int getIdExemplar()
	{
		return this->idExemplar;
	}
	char* getTipMaterial()
	{
		return this->tipMaterial;
	}
	int getNrExemplare()
	{
		
		return this->nrExemplare;
	}
	float getCost()
	{
		
			return this->cost;
		
	}
	//setter
	void setTipMaterial(const char* tipMaterial)
	{
		if (this->tipMaterial != NULL)
		{
			delete[] this->tipMaterial;
		}
		this->tipMaterial = new char[strlen(tipMaterial) + 1];
		strcpy(this->tipMaterial, tipMaterial);
	}
	void setNrExemplare(int nrExemplare)
	{
		if (nrExemplare >= 0)
		{
			this->nrExemplare = nrExemplare;
		}
	}
	void setCost(float cost)
	{
		if (cost >= 10)
		{
			this->cost = cost;
		}
	}



	//constr de copiere
	Imprimare(const Imprimare& i):idExemplar(i.idExemplar)
	{
		this->tipMaterial = new char[strlen(i.tipMaterial) + 1];
		strcpy(this->tipMaterial, i.tipMaterial);
		this->nrExemplare = i.nrExemplare;
		this->cost = i.cost;
	}
	//operator =
	Imprimare &operator=(const Imprimare& i)
	{
		if (this != &i)
		{
			if (this->tipMaterial != NULL)
			{
				delete[] this->tipMaterial;
			}
			this->tipMaterial = new char[strlen(i.tipMaterial) +1];
			strcpy(this->tipMaterial, i.tipMaterial);
			this->nrExemplare = i.nrExemplare;
			this->cost = i.cost;
		}
		return *this;
	}
	//destructor
	~Imprimare()
	{
		if (this->tipMaterial != NULL)
		{
			delete[] this->tipMaterial;
		}
	}
	friend ostream& operator <<(ostream& out,const Imprimare& i)
	{
		out << i.idExemplar << endl;
		out << i.tipMaterial << endl;
		out << i.nrExemplare << endl;
		out << i.cost << endl;
		return out;
	}
	bool operator <(const Imprimare& obj)
	{
		return this->cost < obj.cost;
	}
	/*bool operator <(const Imprimare& i1, const Imprimare& i2)
	{
		return i1.cost < i2.cost;
	}*/
	Imprimare& operator+=(const Imprimare& i)
	{
		this->nrExemplare += i.nrExemplare;
		return *this;
	}
	//scrierea in fisier binar ->serializare
	void serializare(string numeFisier)
	{
		ofstream f(numeFisier, ios::out | ios::binary);
		//scriere char* in fisier
		int lungTip = strlen(this->tipMaterial);
		f.write((char*)&lungTip, sizeof(lungTip));
		f.write(this->tipMaterial, lungTip + 1);
		//scriere int
		f.write((char*)&this->nrExemplare, sizeof(this->nrExemplare));
		//scriere float
		f.write((char*)&this->cost, sizeof(this->cost));
		f.close();
	}
	//citire din fisier ->deserializare
	void deserializare(string numeFisier)
	{
		ifstream f(numeFisier, ios::in | ios::binary);
		if (f.is_open())
		{
			//citire char*
			if (this->tipMaterial != NULL)
			{
				delete[] this->tipMaterial;
			}
			int lungTip = 0;
			f.read((char*)&lungTip, sizeof(lungTip));
			this->tipMaterial = new char[lungTip + 1];
			f.read(this->tipMaterial, lungTip + 1);
			//scriere int
			f.read((char*)&this->nrExemplare, sizeof(this->nrExemplare));
			//scriere float
			f.read((char*)&this->cost, sizeof(this->cost));
			f.close();
		}
	}
};
void sortareImprimari(Imprimare imprimari[], int n)
{
	for (int i = 0; i < n - 2; i++)
	{
		for (int j = i+1; j < n - 1; j++)
		{
			if (imprimari[i] < imprimari[j])
			{
				swap(imprimari[i], imprimari[j]);
			}
		}
	}
}
class Companie:public Imprimare
{
	string numeCompanie;
public:
	Companie() :Imprimare()
	{
		this->numeCompanie = "Necunoscuta";
	}
	Companie( int idExemplar, const char* tipMaterial, int nrExemplare, float cost,string numeCompanie) 
		:Imprimare(idExemplar, tipMaterial, nrExemplare,cost)
	{
		this->numeCompanie = numeCompanie;
	}
	Companie(const Companie& c):Imprimare(c)
	{
		this->numeCompanie = c.numeCompanie;
	}
	Companie& operator=(const Companie& c)
	{
		if (this != &c)
		{
			Imprimare :: operator=(c);
			this->numeCompanie = c.numeCompanie;
		}
		return *this;
	}
	~Companie()
	{

	}
	friend ostream& operator<<(ostream& out, const Companie& c)
	{
		out << (Imprimare&)c;
		out << c.numeCompanie << endl;
		return out;
	}
};


int main()
{
	Imprimare i;
	cout << i.getIdExemplar() << endl;
	cout << i.getTipMaterial() << endl;
	cout << i.getNrExemplare() << endl;
	cout << i.getCost() << endl;
	cout << endl << endl;

	Imprimare i1(1,"Lemn", 3, 450);
	cout << i1.getIdExemplar() << endl;
	cout << i1.getTipMaterial() << endl;
	cout << i1.getNrExemplare() << endl;
	cout << i1.getCost() << endl;
	cout << endl << endl;

	Imprimare i2(2, "Geam", 5, 650);
	cout << i2.getIdExemplar() << endl;
	cout << i2.getTipMaterial() << endl;
	cout << i2.getNrExemplare() << endl;
	cout << i2.getCost() << endl;
	cout << endl << endl;

	Imprimare i3(3, "Sticla", 60, 10050);
	cout << i3.getIdExemplar() << endl;
	cout << i3.getTipMaterial() << endl;
	cout << i3.getNrExemplare() << endl;
	cout << i3.getCost() << endl;
	cout << endl << endl;

	Imprimare i4(i2);
	cout << i4.getIdExemplar() << endl;
	cout << i4.getTipMaterial() << endl;
	cout << i4.getNrExemplare() << endl;
	cout << i4.getCost() << endl;
	cout << endl << endl;

	i1 = i3;
	cout << i1.getIdExemplar() << endl;
	cout << i1.getTipMaterial() << endl;
	cout << i1.getNrExemplare() << endl;
	cout << i1.getCost() << endl;
	cout << endl << endl;

	cout << i1 << endl;
	cout << "---------------------------------------" << endl;
	Imprimare imprimari[] = { i , i1, i2, i3, i4 };
	//int n = sizeof(imprimari) / sizeof(imprimari[0]);
	int n = 5;
	sortareImprimari(imprimari, n);
	for (int i = 0; i < n; i++)
	{
		cout << imprimari[i] << endl;
	}
	cout << i2 << endl;
	cout << i3 << endl;
	i2 += i3;
	cout << i2 << endl;
	cout << "-------------------------" << endl;
	Companie c;
	cout << c << endl;
	Companie c1(5, "Aluminiu", 10, 10000, "Dedeman");
	cout << c1 << endl;
	Companie c2(6, "Diamant", 15, 10050, "Bucuresti");
	cout << c2 << endl;
	Companie c3(7, "Otel", 50, 150000, "CalimanestiSC");
	cout << c3 << endl;
	Companie c4(c3);
	cout << c4 << endl;
	c4 = c1;
	cout << c4 << endl;

	//fisiere->scriere
	i1.serializare("ex.bin");
	//fisiere->citire
	cout << "----------" << endl;
	Imprimare i10;
	cout << i10 << endl;
	i10.deserializare("ex.bin");
	
	cout << i10 << endl;
}