#ifndef __RCSTRING_H__
#define __RCSTRING_H__
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <stdlib.h> 
#include <math.h> 
#include <fstream>

using namespace std;

class matrix{
  struct datamatrix;
  datamatrix* data;
public:

class IndexOutOfRange{}; //definicja klasy ktorej obekt bedie zwracany jako wyjatek w momencie gdy wykonana bedzie operacja odwolania sie do int spoza zakresu
class WrongDim{};//...nieprawidlowych rozmiarow
class Cref;
matrix(fstream& x);//przyjmuje uchwyt do pliku
matrix(const matrix & x);
matrix(int,int,double,double);
~matrix();
matrix& operator=(const matrix&);
matrix operator*(const matrix&) const;
friend ostream& operator<<(ostream&, const matrix&);//operator sluzacy do wypisania zawartosci macierzy
void write();
double operator[](unsigned int i) const;
Cref operator[](unsigned int i);

};

struct matrix::datamatrix
{
  double* l;
  int kol;
  int wier;
  unsigned int n;

  datamatrix(int nwier,int nkol,double lb1,double lb2=0)
  {
    n=1; 
    wier=nwier;
    kol=nkol;
    l=new double[kol*wier];

	for(int i=0;i<wier;i++)
	{
			for(int j=0;j<kol;j++)
		{
			*(l+i*kol+j)=lb2;
			if(i==j)
			*(l+i*kol+j)=lb1;	
		}
	}

  };
  
  datamatrix(int nwier,int nkol,double* nl)
  {
    n=1;
    wier=nwier;
    kol=nkol;
    l=new double[kol*wier];

	for(int i=0;i<wier;i++)
	{
			for(int j=0;j<kol;j++)
		{
			*(l+i*kol+j)=*(nl+i*kol+j);
		}
	}

  };
  
  ~datamatrix()
  {
    delete [] l;
  };
  
  datamatrix* detach()//oddziela watek od obiektu
  {
    if(n==1)	
    return this;
    datamatrix* t=new datamatrix(wier,kol,l);
    n--;
    return t;
  };
  

};

class matrix::Cref
{ 
  
  class Cref2
	
	{
	  friend class matrix::Cref;
	  matrix& s;
	  int i;
	  int j;
	
	  Cref2 (matrix& ss, unsigned int ii,unsigned int jj): s(ss), i(ii) ,j(jj){};//lista inicjalizacyjna - przypisanie wartosci do zmiennych skladowych klasy
	  
	  public:
	  	
	  operator double() const
	  {
	    cout << "rzutowanie  double()/odczyt "<<endl;
	    return *(s.data->l+i*s.data->kol+j);
	  }
	  Cref2& operator = (double c)
	  {
	    cout << "przypisanie liczby "<<endl;
		s.write();
	    *(s.data->l+i*s.data->kol+j)=c;
	    return *this;
	  }
	  
	 };
 
 
  friend class matrix;
  matrix& s;
  int i;
  Cref (matrix& ss, unsigned int ii): s(ss), i(ii) {};
  
  public:
  	
  operator double() const
  
  {
    cout << "rzutowanie  double()/odczyt "<<endl;
    return s.data->l[i];
  }
  
  matrix::Cref& operator = (double c)
  {
    cout << "przypisanie liczby "<<endl;
	s.write();
	s.data->l[i]=c;
    return *this;
  }
  
Cref2 operator [] (unsigned int j)//operator wyluskania wartosci z danego inedksu macierzy 2d
{
    cout << "nastepny operator []"<<endl;
    if(j>=s.data->kol||i>=s.data->wier)
	throw matrix::IndexOutOfRange();
	return Cref2(s,i,j);
}
}; 




matrix::matrix(const matrix & x)//konstruktor klasy matrix ktory jako argument przyjmuje referencje do innej macierzy tego samego typu
  {
	data=new datamatrix(x.data->wier,x.data->kol,x.data->l);
	cout<<"441"<<endl;
  }

matrix::matrix(fstream& x)
  {
	string dane1,dane2,dane3,dane4;
	int a,b,c,d;
	getline(x,dane1);
	getline(x,dane2);
	getline(x,dane3);
	getline(x,dane4);

	a=atoi(dane1.c_str());//c_str zamiana string na char*, atoi zamiana ciagu znakow na liczbe calkowita
	b=atoi(dane2.c_str());
	c=atoi(dane3.c_str());
	d=atoi(dane4.c_str());       
  	
	data=new datamatrix(a,b,c,d);
  }

  
matrix::~matrix()
{
  if(--data->n==0)
    delete data;
}

matrix& matrix::operator=(const matrix & x)
{
  cout<<"kopiowanie wsk na dane"<<endl;
  x.data->n++;
  if(--data->n == 0)
    delete data;
  data=x.data;
  return *this;
}

matrix::matrix(int nwier,int nkol,double lb1,double lb2=0)
{
  data=new datamatrix(nwier,nkol,lb1,lb2);
}

ostream& operator << (ostream& o, const matrix& s)
{
	
	for(int i=0;i<s.data->wier;i++)
	{
			for(int j=0;j<s.data->kol;j++)
		{
			
			cout<<*(s.data->l+i*s.data->kol+j)<<"\t";
			
		}
		cout<<endl;
	}
	
	return o<<endl;
}

matrix matrix::operator*(const matrix & s) const
{
  matrix k=matrix(s.data->wier,s.data->kol,1,1);
	
		if(!(s.data->wier==this->data->wier&&s.data->kol==this->data->kol))
	  {
		throw WrongDim();
	  }
	
		for(int i=0;i<k.data->wier;i++)
	{
			for(int j=0;j<k.data->kol;j++)
		{
			*(k.data->l+i*k.data->kol+j)=*(s.data->l+i*s.data->kol+j)**(this->data->l+i*this->data->kol+j);
		}
	}	
				

  return k;
}

inline void matrix::write()
{
  data = data->detach();
}




double matrix::operator[](unsigned int i) const
{
  cout << "operacja [] 2 "<<endl;
	
	if(i>this->data->kol)
	throw IndexOutOfRange();	
	
  return data->l[i];
}



matrix::Cref matrix::operator[](unsigned int i)
{
  cout << "operacja [] "<<endl;
	if(i>=this->data->kol)
		throw IndexOutOfRange();
	return Cref(*this,i);
}


#endif /* __RCSTRING_H__ */
