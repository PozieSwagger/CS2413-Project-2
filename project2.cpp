// Spring 2023
// Data Structures
// Project 2
// Samuel Posey


#include <iostream>
#include <string>
#include <fstream> // for reading fileInput

using namespace std;

class tableClass {
protected:
	string** myTable; // 2D string array to store all values (strings and numbers)
	string* DTarray; // 1D array to store the data types of each column
	int noRows, noCols; // number of rows and columns

public:
	//Constructors
	tableClass();
	tableClass(int rows, int cols){
		noRows = rows;
		noCols = cols;

		//creats rows and columns of the myTable empty
		//Reference https://stackoverflow.com/questions/70192457/initialize-2d-array-in-constructor-of-cpp-class
		myTable = new string* [noRows];
		for(int i = 0; i < noRows; i++){
			myTable[i] = new string [noCols];
		}
		
	};
	
	// Overload the [] operator to access a row in myTable
	string* operator[](int i); 

	//File reading Method
	void readCSV(string filename){

		ifstream file;
		file.open(filename, ifstream::in);


		//Reference https://favtutor.com/blogs/split-string-cpp
		string data;
		int x = 0, y = 0;
		while(getline(file, data)){
			int end = data.find(',');
			while(end != -1){
				myTable[x][y] = data.substr(0, end);
				data.erase(data.begin(), data.begin() + end + 1);
				end = data.find(',');
				y++;
			}
			x++;
			y = 0;
		}

		file.close();
	};

	//Output Method
	void display(){
		for(int x = 0; x < noRows; x++){
			for(int y = 0; y < noCols; y++){
				cout << myTable[x][y] << " ";
			}
			cout << endl;
		}
	};

	//Sort the table
	void sortTable(){
		int i, x, y;
		string key;
		for(i = 0; i < noRows; i++){
			key = myTable[i][0];
			x = i + 1;
			while(x >= 0 && myTable[x][0] > key){
				y = 0;
				myTable[x + 1][y] = myTable[x][y];
				
				//Error here with moving the other columns
				while(y < noCols){
					myTable[x][y + 1] = myTable[x][y];
					y++;
				}

				x++;
			}
			myTable[x + 1][0] = key;
		}
	};

	//Search record
	string* searchRecord(string str); // str will be from the first column

	//Search value from table
	void searchValue(string str);
	
	//Getters
	// returns the number of rows
	int getNumberRows(){
		return noRows;
	}; 
	// returns the number of columns
	int getNumberCols(){
		return noCols;
	}; 
	tableClass* getColumns(int colLeft, int colRight); // returns a tableClass with a set of columns from colLeft to colRight indices
	tableClass* getRows(int rowTop, int rowBottom); // returns a tableClass with a set of rows from rowTop to rowBottom indices
	tableClass* getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom); // returns a tableClass with the data between the cols and rows given

	//Find info of a given column
	double findMin(int colNumber); // returns the min of the given column

	//Destructor
	~tableClass();
};



int main()
{
	int numRows, numCols;
	string fileName;
	char option;

	cin >> numRows >> numCols >> fileName;
	cout << "NumRows: " << numRows << endl;
	cout << "NumCols: " << numCols << endl;
	cout << "FileName: " << fileName << endl;

	tableClass* d = new tableClass(numRows, numCols);

    // TODO: read the file input name and call readCSV()

	d->readCSV(fileName);
	d->display();

	d->sortTable();
	d->display();
	
    
    // TODO: read the data types and store in DTarray of d

    // TODO: start reading the options till the end of the file

	return 0;
}
