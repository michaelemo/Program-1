/* This is for CS 300 Program 1
 * Michael Emo
 * Last Updated: 09/15/2016
 */
  
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Part		// This is the class for the part information
{
	public:		// it is public so everthing can use it
	
		int partNumber, quantity;
		string description;
		float unitPrice;
};

// List of all the functions that are used in this program with their parameters

void readInInventory (Part [], int &);
void menu (Part [], int &);
void printAllParts(Part [], int);	
void addPart (Part [], int &);
void modifyPart (Part [], int &);
void printPrice (Part [], int &);
void writeToInventory (Part [], int &);

int main ()		// Start of the main function
{	
	cout.setf(ios::fixed);		// This sets all number values to have to decimal places.
	cout.setf(ios::showpoint);
	cout.precision(2);
	
	Part array[100];		// This is the array to hold objects	
	int count = 0;			// This is the count to tell how many different parts in array
	
	readInInventory(array, count); // This is where the function is called that reads in the inventory.txt file

	menu(array, count);		// This is where the funciton that runs the menu and the menu options is called.
	
	// save data to inventory.txt here
	
	writeToInventory(array, count); // This is where the new parts and changed parts are saved and written to
									// the inventory.txt file
	
	return 0;		// The program ends here
}

void readInInventory (Part array[], int & count) // Here the function uses the parameters of the array, which uses
{ 												 // the class variables, and a reference parameter of count
	// try to read from inventory.txt here
	// read from inventory.txt and update array[i]
	
	int i = 0; // i is the index
	fstream inventoryRead("inventory.txt", std::ios::in); // Function that opens the file
		
	if(inventoryRead)		// Statement to read into the array
	{
		int partNumber = 0;		// Parameters for this function
		string description = "";
		int quantity = 0;
		float unitPrice = 0;
		
		// use a loop to keep reading file
		// if reading file fails, the loop will end
		
		while(inventoryRead >> partNumber && i < 100) // Loop that will go through the entire file
		{
			// These functions actually read from the file and set variables equal to the information
			
			inventoryRead.ignore(); 
			getline(inventoryRead, description);
			inventoryRead >> quantity;
			inventoryRead >> unitPrice;
			
			// copy info from local variables to array element variables
			
			array[i].partNumber = partNumber;
			array[i].description = description;
			array[i].quantity = quantity;
			array[i].unitPrice = unitPrice;
			i++;
			count++;
		}
	}
	
	else
	{
		cout << "Error when reading from inventory.txt file \"inventory.txt\"" << endl << endl;
	}
	
	// close file when done
	
	inventoryRead.close();
}

// Function that displays the menu and calls the functions that are associated with the menu

void menu (Part array [], int & count)		// Function uses the parameter array with the class part variables and the reference parameter count
{
	// Here is the menu with the variable choice that the user sets the value to
	
	int choice = 0;
	
	// Menu is printed on the screen
	
	cout << endl;
	cout << "  Welcome to Tiny Part Management" << endl;
	cout << "***********************************" << endl;
	cout << "  1. Print the parts inventory" << endl;
	cout << "  2. Create a new part" << endl;
	cout << "  3. Modify a part" << endl;
	cout << "  4. Print price total of inventory" << endl;
	cout << "  5. Exit the program" << endl << endl;
	cout << "  Dear user please make a choice: ";
	cin >> choice;
	cout << endl;
	
	// This loop uses the user's choice to execute the corresponding function
	
	while (cin.good () && choice != 5)
	{	
		switch (choice)
		{
			case 1:
				printAllParts(array, count);	// Calls the function that prints the part on the screen
				break;
				
			case 2:
				cin.ignore();
				addPart(array, count);	// Calls the function that allows user to add parts
				break;
				
			case 3:
				modifyPart(array, count);	// Calls the function that allows user to modify parts
				break;
				
			case 4:
				printPrice(array, count);	// Calls the funtion that allows the user to print the total price in the inventory
				break;
			
			default:
				cout << "  Invalid choice. Please choose again." << endl << endl;
		}
		
		// This keeps reprinting the menu so the user can choose options as many times as needed
		
		cout << endl << endl;
		cout << "  Welcome to Tiny Part Management" << endl;
		cout << "***********************************" << endl;
		cout << "  1. Print the parts inventory" << endl;
		cout << "  2. Create a new part" << endl;
		cout << "  3. Modify a part" << endl;
		cout << "  4. Print price total of inventory" << endl;
		cout << "  5. Exit the program" << endl << endl;
		cout << "  Dear user please make a choice: ";
		cin >> choice;
		cout << endl;
	}
}

// Function that prints all the parts on the screen.

void printAllParts (Part array[], int count)	// Uses the parameter array that uses the information from the class part
{												// and uses the variable count that is not a reference parameter	
	if (count == 0) // Checks to make sure there isn't an empty inventory
	{
		cout << "  Empty Inventory. " << endl << endl;
		return;
	}
	
	for (int i = 0; i < count; i++) // Loop that prints out all the information from the array on the screen
	{
		cout << "  Part Number: " << array[i].partNumber << endl;
		cout << "  Description: " << array[i].description << endl;
		cout << "  Quantity: " << array[i].quantity << endl;
		cout << "  Unit Price: $" << array[i].unitPrice << endl << endl;
	}
}

// Function that allows the user to add a part to the inventory

void addPart (Part array[], int & count)	// Function uses the parameter array with the class part variables and the reference parameter count
{
	cout << "  New part description: ";		// Allows user to add part description
	string desc;
	getline(cin, desc);
	
	cout << "  New part quantity: "; 		// Allows user to add part quantity
	int quantity = 0;
	cin >> quantity;
	
	cout << "  New part unit price: $";		// Allows user to add new part price
	float price = 0;
	cin >> price;
	cout << endl;
	
	array[count].partNumber = count + 1;	// These lines actually add the new values to the array
	array[count].description = desc;
	array[count].quantity = quantity;
	array[count].unitPrice = price;
	
	count++;				
}

// This function allows the user to modify a part

void modifyPart (Part array[], int & count)		// Function uses the parameter array with the class part variables and the reference parameter count
{
	// Variables for the modification menu
	
	int modifyChoice;
	int partNumberChoice;
	char continueChoice;
	
	if (count == 0)		// Checks to make sure the inventory isn't empty
	{
		cout << "  Empty Inventory. " << endl << endl;
	}
	
	else     // If the inventory is not empty, the funtion will allow the user to modify a part
	{
		do
		{
			// Menu for the user to enter which part number they would like to enter
			
			cout << "What part number would you like to modify?" << endl;
			cout << "Part number: ";
			cin >> partNumberChoice;
			cout << endl;
			
			while(partNumberChoice > count)		// This loop makes sure the user's partNumberChoice value is an actual part number
			{
				cout << "Invalid part number choice. Please pick a valid part number: ";
				cin >> partNumberChoice;
				cout << endl;
			}
			
			// This shows the user the current values of that part number
			
			cout << "  Description: " << array[partNumberChoice-1].description << endl;
			cout << "  Quantity: " << array[partNumberChoice-1].quantity << endl;
			cout << "  Unit Price: $" << array[partNumberChoice-1].unitPrice << endl << endl;
			
			// This prints the menu to modify the part and logs the users choice
			
			cout << "    Inventory Part Modifier" << endl;
			cout << "*******************************" << endl;
			cout << "  1. Change part description" << endl;
			cout << "  2. Change part quantity" << endl;
			cout << "  3. Change unit price" << endl;
			cout << "  4. Exit the modifier" << endl << endl;
			cout << "  Dear user please make a choice: ";
			cin >> modifyChoice;
			cout << endl;
			
			// These variables are used to modify the part
			
			string desc;
			int quantity = 0;
			float price = 0;
			
			while (cin.good () && modifyChoice != 4) // This loop is used to modify the parts and add the changes to the array
			{	
				switch (modifyChoice) // This switch goes off the user's choice
				{
					case 1:
					
						// This case takes the new description entered by the user and changes the part it in the array
					
						cout << "  New part description: ";
						cin.ignore();
						getline(cin, desc);
						array[partNumberChoice-1].description = desc;
						cout << endl;
						
						// This prints the updated part in the array
						
						cout  << endl << endl;
						cout << "*******************************" << endl;
						cout << "New Part Information:" << endl;
						cout << "  Description: " << array[partNumberChoice-1].description << endl;
						cout << "  Quantity: " << array[partNumberChoice-1].quantity << endl;
						cout << "  Unit Price: $" << array[partNumberChoice-1].unitPrice << endl;
						cout << "*******************************" << endl << endl << endl << endl;
						break;
						
					case 2:
					
						// This case takes the new quantity entered by the user and changes the part in the array
					
						cout << "  New part quantity: ";
						cin >> quantity;
						array[partNumberChoice-1].quantity = quantity;
						cout << endl;
						
						// This prints the updated part in the array
						
						cout  << endl << endl;
						cout << "*******************************" << endl;
						cout << "New Part Information:" << endl;
						cout << "  Description: " << array[partNumberChoice-1].description << endl;
						cout << "  Quantity: " << array[partNumberChoice-1].quantity << endl;
						cout << "  Unit Price: $" << array[partNumberChoice-1].unitPrice << endl;
						cout << "*******************************" << endl << endl << endl << endl;
						break;
						
					case 3:
					
						// This case takes the new part price entered by the user and changes the part in the array
					
						cout << "  New part unit price: $";
						cin >> price;
						array[partNumberChoice-1].unitPrice = price;
						cout << endl;
						
						// This prints the updated part in the array
						
						cout  << endl << endl;
						cout << "*******************************" << endl;
						cout << "New Part Information:" << endl;
						cout << "  Description: " << array[partNumberChoice-1].description << endl;
						cout << "  Quantity: " << array[partNumberChoice-1].quantity << endl;
						cout << "  Unit Price: $" << array[partNumberChoice-1].unitPrice << endl;
						cout << "*******************************" << endl << endl << endl << endl;
						break;
					
					default:
						cout << "  Invalid choice. Please choose again." << endl << endl;
				}
				
				// The menu is reprinted until the user decides to exit and chose to modify another part or go back to the main menu
				
				cout << "    Inventory Part Modifier" << endl;
				cout << "*******************************" << endl;
				cout << "  1. Change part description" << endl;
				cout << "  2. Change part quantity" << endl;
				cout << "  3. Change unit price" << endl;
				cout << "  4. Exit the modifier" << endl << endl;
				cout << "  Dear user please make a choice: ";
				cin >> modifyChoice;
				cout << endl;
				
				// Reprints the final changes to the part
				
				cout << endl << endl;
				cout << "*******************************" << endl;
				cout << "New Part Information:" << endl;
				cout << "  Description: " << array[partNumberChoice-1].description << endl;
				cout << "  Quantity: " << array[partNumberChoice-1].quantity << endl;
				cout << "  Unit Price: $" << array[partNumberChoice-1].unitPrice << endl;
				cout << "*******************************" << endl << endl;
				
			}
			
			// Asks the user whether or not the want to modify another part or return to the main menu
			
			cout << "Do you want to modify another part?" << endl;
			cout << "Enter 'Y' for Yes or 'N' for No: ";
			cin >> continueChoice;
			cout << endl;
			
			while((continueChoice != 'Y') && (continueChoice != 'y') && (continueChoice != 'N') && (continueChoice != 'n'))
			{
				cout << "You have entered an invalid choice. Please pick again: ";
				cin >> continueChoice;
			}
		}while(((continueChoice == 'Y') || (continueChoice == 'y')) && ( (continueChoice != 'N') || (continueChoice != 'n')));
	}
}

// This function prints the total price of all the parts in the inventory file

void printPrice (Part array[], int & count)		// Function uses the parameter array with the class part variables and the reference parameter count
{
	float unitPrice = 0;
	
	if (count == 0) // This makes sure the inventory isn't empty
	{
		cout << "  Empty Inventory. Total price in inventory $0.00" << endl << endl;
		return;
	}
	
	else 
	{
		for (int i = 0; i < count; i++)		// This loop goes through the entire array and calculates the total price
		{									// of the inventory
			unitPrice += array[i].unitPrice * array[i].quantity;
		}  
	
		cout << "  Total price in inventory: $" << unitPrice << endl << endl;
	}
}

// This function is done at the end of the program and writes the updated information to the inventory.txt file

void writeToInventory (Part array[], int & count) // Function uses the parameter array with the class part variables and the reference parameter count
{
	fstream inventoryWrite("inventory.txt", std::ios::out); 	// ios deletes overwrites the old file and/or creates a new one. It is used as a flag to describe what we are going to do
												
	// if file is good, then write to the file
	
	int i = 0;
	
	if (inventoryWrite) 
	{
		while (i < count)	// This loop goes through the entire array and writes the information to the inventory.txt file
		{
			inventoryWrite << array[i].partNumber << endl;
			inventoryWrite << array[i].description << endl;
			inventoryWrite << array[i].quantity << endl;
			inventoryWrite << array[i].unitPrice << endl;
			i++;
		}	
		cout << "Writing inventory file \"inventory.txt\" succeed." << endl << endl;
	}
	
	else  // This shows if there is an error writing to the file
	{
		cout << "Error when writitng to inventory.txt \"inventory.txt\"" << endl << endl;
	}
	
	// close file when done
	
	inventoryWrite.close();	
}
