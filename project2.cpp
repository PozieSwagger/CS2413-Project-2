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

	//input the datatype onto DTarray
	void readDT(string datatypes){
		size_t end = 0;

		//construt the DTarray
		DTarray = new string [noCols];

		//split the sting and enter into the array
		for(int i = 0; i < noCols; i++){
			end = datatypes.find(' ');
			DTarray[i] = datatypes.substr(0, end);
			datatypes.erase(0, end + 1); 
		}

	};
	
	// Overload the [] operator to access a row in myTable
	string* operator[](int i){
		if(i < 0 || i >= noRows){
			cout << "nothing here" << endl;
		}

		return myTable[i];

	}; 

	//File reading Method
	void readCSV(string filename){

		//open the csv file
		ifstream file;
		file.open(filename, ifstream::in);


		//Reference https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
		string data;
		int x = 0, y = 0;
		while(getline(file, data)){
			size_t end = 0;
			
			//loop through line and split at a comma
			for(int i = 0; i < noCols; i++){
				end = data.find(',');
				myTable[x][y] = data.substr(0, end);
				data.erase(0, end + 1);
				y++;
			}

			x++;
			y = 0;
		}

		//close the file
		file.close();
	};

	//Output Method
	void display(){
		
		//print out DTarray
		for(int i = 0; i < noCols; i++){
			cout << DTarray[i] << " ";
		}
		cout << endl;

		// loop and print put the line
		for(int x = 0; x < noRows; x++){
			for(int y = 0; y < noCols; y++){
				cout << myTable[x][y] << " ";
			}
			cout << endl;
		}
	};

	//Sort the table
	//Refernece https://stackoverflow.com/questions/44526234/sorting-2d-array-using-selection-sort
	void sortTable(){
		
		string maxV;

		//loop through the 2d array
		for(int i = 0; i < noRows; i++){
			for(int j = 0; j < noCols; j++){
				
				//compare the value to sort
				if(myTable[j][0] > myTable[j + 1][0]){

					//move through the row and swap the values
					for(int y = 0; y < noCols; y++){
						string temp = myTable[j][y];
						myTable[j][y] = myTable[j+1][y];
						myTable[j+1][y] = temp;
					}
				}
			}
		}
		
	};

	//Search record
	// str will be from the first column
	string* searchRecord(string str){

		//loop the first column and find the name
		for(int i = 0; i < noRows; i++){
			if(str == myTable[i][0])
				return myTable[i];
		}

		return nullptr;
	};

	//Search value from table
	void searchValue(string str){
		
		//check if float and search last column
		if(ifFloat(str) == 1){
			for(int i = 0; i < noRows; i++){
				if(str == myTable[posDTarray()][i])
					cout << " found in (" << posDTarray() << ", " << i << ")" << endl;
			}
		}
		//search the int values
		else{
			for(int x = 3; x < 5; x++){
				for(int y= 0; y < noRows; y++){
					if(str == myTable[x][y])
						cout << " found in (" << x << ", " << y << ")" << endl;
				}
			}
		}

	};
	
	//Getters
	// returns the number of rows
	int getNumberRows(){
		return noRows;
	}; 
	// returns the number of columns
	int getNumberCols(){
		return noCols;
	}; 

 	// returns a tableClass with a set of columns from colLeft to colRight indices
	tableClass* getColumns(int colLeft, int colRight){

		//print the DTarry with is being used
		for(int i = colLeft; i < colRight; i++){
			cout << DTarray[colLeft] << " ";
		}
		cout << endl;
		
	};

	// returns a tableClass with a set of rows from rowTop to rowBottom indices
	tableClass* getRows(int rowTop, int rowBottom); 

	// returns a tableClass with the data between the cols and rows given
	tableClass* getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom); 

	//Find info of a given column
	// returns the min of the given column
	double findMin(int colNumber){

		//set the starting value for low
		double low = stod(myTable[0][colNumber]);

		//lopp through the given column and return the lowest value
		for(int i = 1; i < noRows; i++){
			if(stod(myTable[i][colNumber]) < low)
				low = stod(myTable[i][colNumber]);
		}

		return low;
	};

	//Destructor
	~tableClass();

private:
	//check if the string given is a float
	int ifFloat(string str){

		//loop through string
		for(int i = 0; i < str.length(); i++){
			if(str[i] == '.')
				return 1;
		}

		return 0;
	};

	//check the postion of float in the DTarray
	int posDTarray(){
		
		//search for the float
		for(int i = 0; i < noCols; i++){
			if(DTarray[i] == "float")
				return i;
		}

		return noCols - 1;
	};
};



int main()
{
	int numRows, numCols;
	string fileName, dataType, optionStr;
	char option;

	cin >> numRows >> numCols >> fileName;
	cout << "NumRows: " << numRows << endl;
	cout << "NumCols: " << numCols << endl;
	cout << "FileName: " << fileName << endl;

	tableClass* d = new tableClass(numRows, numCols);

    // TODO: read the file input name and call readCSV()
	d->readCSV(fileName);
	
	d->sortTable();
	
    // TODO: read the data types and store in DTarray of d
	cin >> ws;
	getline(cin, dataType);
	d->readDT(dataType);

    // TODO: start reading the options till the end of the file
	while(cin >> option){
		if(option == 'F'){
			cout << "Record found:" << endl;
			cin >> optionStr;
			d->searchRecord(optionStr);
		}
		if(option == 'V'){
			cin >> optionStr;
			cout << "Searching for " << optionStr << endl;
			d->searchValue(optionStr);
		}
		if(option == 'D'){
			d->display();
		}
		if(option == 'I'){
			cin >> optionStr;
			cout << "Min of " << optionStr << " is " << d->findMin(stoi(optionStr)) << endl;
		}
		if(option == 'C'){

		}
		if(option == 'R'){

		}
		if(option == 'S'){

		}
	}

	return 0;
}
