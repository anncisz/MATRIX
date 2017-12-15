#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{

try{

	  	matrix A2(4,4,1,4);	
		matrix A3(4,4,2,3);	
		matrix A4=A3;
		cout<<A4;
		A2=A3;	
		cout<<A2;
		
		cout<<A2;
		cout<<A3;
		A2=A3;
		cout<<A2;
		cout<<A3;
		A2[0][0]=11;
		/*
		A2[0][11]=11;	//AOR
		*/
		cout<<"____________________________"<<endl;
		cout<<A2;
		cout<<A3;
		A4=A3*A2;
		cout<<A4;
		cout<<A3;
		cout<<A2;
	
		cout<<"____________________________"<<endl;
		
		/*
		matrix A6(1,1,1);
		matrix A5=A6*A3;	//Dim
		cout<<A5;*/
		
		fstream f1;
		f1.open("matrix.txt", ios::in);
		
		if( f1.good() == true )
			
			{
			std::cout << "Uzyskano dostep do pliku!" << std::endl;
			} 

			else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
		
		matrix B(f1);				//Read the matrix data from file matrix.dat
		f1.close();				//First two values in this file specify the matrix dimensions
			
		cout<<B;

}
catch(matrix::IndexOutOfRange&)
	{
		cout << "Index Out of Range" << endl;
	}
	catch(matrix::WrongDim&)
	{
		cout << "Wrong Matrix Dimensions" << endl;
	}
	catch(bad_alloc)
	{
		cout << "Out of Memory" << endl;
	}
		
return 0;		
}
