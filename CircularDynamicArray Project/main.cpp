#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "CircularDynamicArray.cpp"

void test1(ostream &fp);
void test2(ostream &fp);
void test3(ostream &fp);
void test4(ostream &fp);
void test5(ostream &fp);
void test6(ostream &fp);

void foo(CircularDynamicArray<int> x) {
	for (int i=0; i<x.length()/2; i++){
		int temp = x[i];
		x[i] = x[x.length()/2+i];
		x[x.length()/2+i] = temp;
	}
}

int printWrapper = 0;

int main(int argc, char **argv){
	int testToRun = atoi(argv[1]);
	switch (testToRun){
		case 1:
			test1(cout);
			break;
		case 2:
			test2(cout);
			break;
		case 3:
			test3(cout);
			break;
		case 4:
			test4(cout);
			break;
		case 5:
			test5(cout);
			break;
		case 6:
			test6(cout);
			break;
	}
}

void test1(ostream &fp){
	if(printWrapper) fp << "Running test 1" << endl;
	//fp.open("test1.out");
	CircularDynamicArray<int> C(25);
	for (int i=0; i< C.length();i++) C[i] = i*10;
	for (int i=0; i< C.length();i++) fp << C[i] << " "; fp << endl;
	C.delFront();
	for (int i=0; i< C.length();i++) fp << C[i] << " ";  fp << endl;
	C.delEnd();
	for (int i=0; i< C.length();i++) fp << C[i] << " ";  fp << endl;
	C.addEnd(1001);
	for (int i=0; i< C.length();i++) fp << C[i] << " ";  fp << endl;
	C.addEnd(1005);
	for (int i=0; i< C.length();i++) fp << C[i] << " ";  fp << endl;
	C.delEnd(); C.delEnd();
	C.addFront(-105); C.addFront(-250);
	for (int i=0; i< C.length();i++) fp << C[i] << " ";  fp << endl;
	fp << "Capacity is " << C.capacity() << endl;

	CircularDynamicArray<int> A;
	int temp = 0;
	for(int i=0; i<25;i++){
		A.addEnd(i*10);
		if(A.capacity() != temp){
			temp = A.capacity();
			fp << "Capacity is " << temp << " ";
		}
	}
    fp << endl;
	fp << "Capacity is " << A.capacity() << endl;
	fp << "Search is " << A.linearSearch(60) << endl;
	fp << "Select is " << A.QuickSelect(2) << endl;
	A.stableSort();
	A.addFront(12); 
	fp << "Search is " << A.binSearch(60) << endl;
	A.reverse();
	fp << "A[0] is " << A[0] << endl;
	A.addFront(-12);
	A.stableSort();
	fp << "BinSearch is " << A.binSearch(30) << endl;
	A.delFront(); A.delFront(); A.addEnd(61);
	for (int i=0; i< A.length();i++) fp << A[i] << " ";  fp << endl;
	CircularDynamicArray<int> B;
	B = A;
	A[0] = -1001;
	fp << B[0] << endl;
	foo(A);
	for (int i=0; i< B.length();i++) fp << B[i] << " ";  fp << endl;
	CircularDynamicArray<long int> testGeneric1(10);
	CircularDynamicArray<short int> testGeneric2(10);
	CircularDynamicArray<double> testGeneric3(10);
	fp << "Passed Generics Test" << endl;
	//fp.close();
	if(printWrapper)fp << "-----------------Finished Test----------------------" << endl;
}

void test2(ostream &fp){
	if(printWrapper) fp << "Running test 2" << endl;   //testing O(nlgn) sort
	CircularDynamicArray<int> A;
	for(int i = 0; i < 500500; i++) A.addFront(i);
	A.reverse();
	fp << "A[0] is " << A[0] << endl;
	A.reverse();
	fp << "A[0] is " << A[0] << endl;
	A.reverse();
	fp << "A[0] is " << A[0] << endl;
	A.stableSort();
	fp << "Search is " << A.linearSearch(400) << endl;
	fp << "Search is " << A.linearSearch(4000) << endl;
	fp << "Search is " << A.binSearch(40000) << endl;
	fp << "Select is " << A.QuickSelect(4000) << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test3(ostream &fp){
	if(printWrapper) fp << "Running test 3" << endl;   //testing initialization constructor
	int initCounter = 0;
	for(int i=1; i<200; i++) {
		CircularDynamicArray<double> D(500500);
		for(int j=0; j<500500; j++) D[j] = -10.0;
		for(int j=1; j<1000; j++) D[i*j] = i*j;
		for(int j=50*i; j<51*i; j++) 
			if(D[j] != -10.0 && i % 39 == 0){
				cout << "D["<<j<<"] is : "<<D[j] << endl;  //should output where D[j] is : j once per value of i
				initCounter++;
			} 
	}
	int printNumber = 0;
	if(initCounter < 6) printNumber = 5;
	else if(initCounter < 30) printNumber = 4;
	else if(initCounter < 60) printNumber = 3;
	else if(initCounter < 100) printNumber = 2;
	else if(initCounter < 200) printNumber = 1;
	else if(initCounter < 300) printNumber = 0;
	for(int i =0; i < printNumber; i++) cout << "This print counts as a line" << endl;
	CircularDynamicArray<char> E(1000000);
	for(int i = 0; i < 1000000; i++) E[i] = 'X';
	E[490000] = 'A';
	E[500000] = 'B';
	cout << E.linearSearch('B')<< endl;   //should output 500000
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test4(ostream &fp){
	if(printWrapper) fp << "Running test 4" << endl;
	CircularDynamicArray<int> A;
	for(int i = 0; i < 50000; i++) {A.addFront(i);A.addEnd(100000-i);}
	fp << "A[24999] is " << A[24999] << endl;
	fp << "A[25000] is " << A[25000] << endl;	
	for(int i = 0; i < 25000; i++) {A.delFront();A.delEnd();}	
	fp << "A[12499] is " << A[12499] << endl;
	fp << "A[12500] is " << A[12500] << endl;
	fp << "Search is " << A.linearSearch(400) << endl;
	A.reverse();
	A.stableSort();
	fp << "BinSearch is " << A.binSearch(4000) << endl;
	fp << "BinSearch is " << A.binSearch(50000) << endl;	  //looking for a value not in the array	
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


void test5(ostream &fp){
	if(printWrapper) fp << "Running test 5" << endl;	
	CircularDynamicArray<int> A;
	for(int i = 0; i < 1000000; i++) 
	{
		A.addEnd(i);
	}
	for(int i = 0; i < 23000; i++) 
	{
		int value = A.binSearch(i);
		if(i % 3500 == 0) fp << "binSearch at " << i << " is " << value << endl;
	}
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


void test6(ostream &fp){
	if(printWrapper) fp << "Running test 6" << endl;
	CircularDynamicArray<int> A;
	for(int i = 0; i < 500000; i++) 
	{
		A.addFront(i);
	}
	A.stableSort();
	for(int i = 0; i < 40; i++) 
	{
		int value = A.binSearch(i);
		if(i % 10 == 0) fp << "Search at " << i << " is " << value << endl;
	}
	for(int i = 40; i < 50; i++) 
	{
		int value = A.linearSearch(i);
		if(i % 10 == 0) fp << "Search at " << i << " is " << value << endl;
	}
	for(int i = 1; i < 450000; i++) 
	{
		A.reverse();
		if(i % 100000 == 0)
		fp << "A at " << i << " is " << A[i] << endl;
	}
	for(int i = 49900; i < 49905; i++) 
	{
		int value = A.QuickSelect(i);
		fp << "Select at " << i << " is " << value << endl;
	}
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


