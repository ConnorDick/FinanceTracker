// PersonalFinanceTracker.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
using namespace std;

const double PAYCHECKS_PER_YEAR (26.0);

//personal information that generally does not change on monthly basis
class ConstantFeatures {
private:
	double monthlyBudgetAfterExpenses;
	struct {
		double salary;
		double yearlyIncome;
		double yearlyIncomeTax;
		double biweeklyIncome;
		double biweeklyIncomeTax;
	} IncomeInfo;
public:
	struct {
		double rent;
		double gas;
		double electric;
		double water;
		double subscriptions;
	} FixedExpenses;

	ConstantFeatures() {
		//cout << "*****************************PERSONAL INFORMATION*****************************" << endl << endl;
		cout << "Please provide your approximate yearly salary, then press enter: ";
		cin >> IncomeInfo.salary;
		IncomeInfo.yearlyIncome = determineTaxFromIncome(IncomeInfo.salary);
		IncomeInfo.biweeklyIncome = IncomeInfo.yearlyIncome / PAYCHECKS_PER_YEAR;
		IncomeInfo.yearlyIncomeTax = IncomeInfo.salary - IncomeInfo.yearlyIncome;
		IncomeInfo.biweeklyIncomeTax = IncomeInfo.yearlyIncomeTax / PAYCHECKS_PER_YEAR;
		cout << endl << "According to 2023 IRS Tax Brackets:     " << "Yearly Income Tax -> " << IncomeInfo.yearlyIncomeTax << endl;
		cout << "                                        " << "Biweekly Income Tax-> " << IncomeInfo.biweeklyIncomeTax << endl << endl;
		cout << "Thus, your income is the following:     " << "Yearly -> " << IncomeInfo.yearlyIncome << endl;
		cout << "                                        " << "Biweekly -> " << IncomeInfo.biweeklyIncome << endl << endl;
		cout << "Do you pay for rent and/or utilities? Enter Y for yes or N for no: ";
		char test{ 0 };
		cin >> test;
		if (test == 'Y') {
			setUtilities();
		}
		else {
			FixedExpenses.rent = 0;
			FixedExpenses.gas= 0;
			FixedExpenses.electric = 0;
			FixedExpenses.water = 0;
		}
		cout << "Do you pay for any subscription services? Enter Y for yes or N for no: ";
		cin >> test;
		if (test == 'Y') {
			cout << "Approximately how much do your subscriptions cost per month: ";
			cin >> FixedExpenses.subscriptions;
		}
		else {
			FixedExpenses.subscriptions = 0;
		}

		getFixedExpenses();

		monthlyBudgetAfterExpenses = setMonthlyBudget(IncomeInfo.biweeklyIncome);
		cout << "Thus, your monthly budget after fixed expenses is: " << monthlyBudgetAfterExpenses << endl << endl;

		cout << "*********************************END OF ENTRY*********************************" << endl << endl;
	}
	
	//based on IRS tax bracket
	double determineTaxFromIncome(double &x) {

		double taxableConst{0};
		double taxablePercent{0};
		double income{0};
		if (x <= 22000) {
			taxablePercent = 0.1;
		}
		else if (x > 22000 && x <= 89450) {
			taxableConst = 2200;
			taxablePercent = 0.12;
		}
		else if (x > 89451 && x <= 190750) {
			taxableConst = 10294;
			taxablePercent = 0.22;
		}
		else if (x > 190751 && x <= 364200) {
			taxableConst = 32580;
			taxablePercent = 0.24;
		}
		else if (x > 364201 && x <= 462500) {
			taxableConst = 74208;
			taxablePercent = 0.32;
		}
		else if (x > 462501 && x <= 693750) {
			taxableConst = 105664;
			taxablePercent = 0.35;
		}
		else if (x > 693751) {
			taxableConst = 186601.5;
			taxablePercent = 0.37;
		}

		income = (x - taxableConst) - (taxablePercent * x);
		return income;
	}

	//prompts for setting utilities in user profile
	void setUtilities() {
		cout << "Please enter cost of rent/parking, then press enter: ";
		cin >> FixedExpenses.rent;
		cout << "Please enter cost of cooking/heating gas, then press enter: ";
		cin >> FixedExpenses.gas;
		cout << "Please enter cost of electric, then press enter: ";
		cin >> FixedExpenses.electric;
		cout << "Please enter cost of water, then press enter: ";
		cin >> FixedExpenses.water;
		cout << endl;
		return;
	}

	//prints fixed expenses in an easily readable manner
	void getFixedExpenses() {
		cout << endl;
		cout << "Your fixed expenses are the following: ";
		cout << " Rent-> " << FixedExpenses.rent << endl;
		cout << "                                      " << "  Cooking / Heating Gas -> " << FixedExpenses.gas << endl;
		cout << "                                      " << "  Electric -> " << FixedExpenses.electric << endl;
		cout << "                                      " << "  Water -> " << FixedExpenses.water << endl;
		cout << "                                      " << "  Subscriptions -> " << FixedExpenses.subscriptions << endl << endl;
		return;
	}

	double getBiweeklyIncome() {
		return IncomeInfo.biweeklyIncome;
	}

	double getYearlyIncome() {
		return IncomeInfo.yearlyIncome;
	}
	
	//based on biweekly income, determines money left over each month after fixed expenses
	const double setMonthlyBudget(double incomeBiweekly) {
		double totalFixedExpense = 0;
		totalFixedExpense = FixedExpenses.rent + FixedExpenses.electric + FixedExpenses.gas +
							FixedExpenses.subscriptions + FixedExpenses.water;
		double budgetAfterFixedExpenses = (incomeBiweekly * 2.0) - totalFixedExpense;
		return budgetAfterFixedExpenses;
	}

	double getMonthlyBudgetGivenNewIncome(double incomeBiweekly) {
		double totalFixedExpense = 0;
		totalFixedExpense = this->FixedExpenses.rent + this->FixedExpenses.electric + this->FixedExpenses.gas +
							this->FixedExpenses.subscriptions + this->FixedExpenses.water;
		double budgetAfterFixedExpenses = (incomeBiweekly * 2.0) - totalFixedExpense;
		return budgetAfterFixedExpenses;
	}


	~ConstantFeatures() {

	}

};

/*Abstract class for all other classes to be derived
Includes general constructor and totalSpent variable*/
class Categories {

protected:
	
	struct {
		int year;
		int month;
		int day;
	} PurchaseInfo; //values should not need to change

public:

	string itemDescription; //description of item or service
	double itemPrice; //cost of item or service
	double itemQuantity;

	Categories() {
		//cout << "Constructing main class." << endl;
		PurchaseInfo.year = 0;
		PurchaseInfo.month = 0;
		PurchaseInfo.day = 0;
		itemDescription = "";
		itemPrice = 0.0;
		itemQuantity = 0.0;
	}

	~Categories() {
		//cout << "Deconstructing main class." << endl;
	}

	//total spent on objects of this particular class
	virtual double totalSpent() = 0;
};

class Transportation : protected Categories {

private:
	static double totalSpending;

public:

	//prompts for constructing Transportation class object
	Transportation() {
		//cout << "Constructing Transportation class." << endl;
		cout << "Please enter purchase year: ";
		cin >> this->PurchaseInfo.year;
		cout << "Please enter purchase month: ";
		cin >> this->PurchaseInfo.year;
		cout << "Please enter purchase day: ";
		cin >> this->PurchaseInfo.day;
		cout << "Please enter a brief description: ";
		cin >> this->itemDescription;
		cout << "Please enter item price: ";
		cin >> this->itemPrice;
		cout << "Please enter item quantity: ";
		cin >> this->itemQuantity;

		setTotalSpending(itemPrice, itemQuantity);
		appendToTxt("Transportation", PurchaseInfo.year, PurchaseInfo.month, PurchaseInfo.day, itemDescription, itemPrice, itemQuantity);
	}

	Transportation(int yearGiven, int monthGiven, int dayGiven, string desc, double priceGiven, double quantityGiven) {
		PurchaseInfo.year = yearGiven;
		PurchaseInfo.month = monthGiven;
		PurchaseInfo.day = dayGiven;
		itemDescription = desc;
		itemPrice = priceGiven;
		itemQuantity = quantityGiven;
		
		setTotalSpending(itemPrice, quantityGiven);
	}


	//sets total spending for static variable for this class
	static void setTotalSpending(double &itemPrice, double &quantityGiven) {
		totalSpending += itemPrice * quantityGiven;
		return;
	}


	//gets total spending for static variable for this class
	static void getTotalSpending() {
		cout << "Total spending on Transportation: " << totalSpending << endl;
		return;
	}

	double totalSpent() override {
		double total = Transportation::totalSpending;
		return total;
	}

	ostream& operator<<(ostream& ostr) {
		ostr << this->PurchaseInfo.day << "/" << this->PurchaseInfo.month << "/" << this->PurchaseInfo.year;
		return ostr;
	}

	void appendToTxt(string Class, int year, int month, int day, string desc, double price, double quantity) {
		fstream file;
		file.open("FinanceTracker.dat", ios::out | ios::in | ios::app);
		if (!file) {
			cout << "Error opening data file for read and write." << endl;
		}
		file << Class << " " << day << "/" << month << "/" << year << " " << desc << " " << price << " " << quantity << endl;
		file.close();
	}

	~Transportation() {
		//cout << "Deconstructing Transportation class." << endl;
	}

};

class Groceries : protected Categories {

private:
	static double totalSpending;

public:

	//prompts for constructing Groceries class object
	Groceries() {
		//cout << "Constructing Transportation class." << endl;
		cout << "Please enter purchase year: ";
		cin >> this->PurchaseInfo.year;
		cout << "Please enter purchase month: ";
		cin >> this->PurchaseInfo.month;
		cout << "Please enter purchase day: ";
		cin >> this->PurchaseInfo.day;
		cout << "Please enter a brief description: ";
		cin >> this->itemDescription;
		cout << "Please enter item price: ";
		cin >> this->itemPrice;
		cout << "Please enter item quantity: ";
		cin >> this->itemQuantity;

		setTotalSpending(itemPrice, itemQuantity);
	}

	Groceries(int priceGiven) {
		itemPrice = priceGiven;
		cout << "Please provide basic description for this entry, then press enter." << endl;
		cin >> itemDescription;
		//assume quantity is one since no specifics provided
		itemQuantity = 1;
		setTotalSpending(itemPrice, itemQuantity);
		appendToTxt("Groceries", PurchaseInfo.year, PurchaseInfo.month, PurchaseInfo.day, itemDescription, itemPrice, itemQuantity);
	}

	//Constructor if user wants to be specific about grocery purchases.
	Groceries(int yearGiven, int monthGiven, int dayGiven, string desc, double priceGiven, double quantityGiven) {
		PurchaseInfo.year = yearGiven;
		PurchaseInfo.month = monthGiven;
		PurchaseInfo.day = dayGiven;
		itemDescription = desc;
		itemPrice = priceGiven;
		itemQuantity = quantityGiven;

		setTotalSpending(itemPrice, quantityGiven);
	}


	//sets total spending for static variable for this class
	static void setTotalSpending(double& itemPrice, double& quantityGiven) {
		totalSpending += itemPrice * quantityGiven;
		return;
	}


	//gets total spending for static variable for this class
	static void getTotalSpending() {
		cout << "Total spending on Transportation: " << totalSpending << endl;
		return;
	}

	double totalSpent() override {
		double total = Groceries::totalSpending;
		return total;
	}

	void appendToTxt(string Class, int year, int month, int day, string desc, double price, double quantity) {
		fstream file;
		file.open("FinanceTracker.dat", ios::out | ios::in | ios::app);
		if (!file) {
			cout << "Error opening data file for read and write." << endl;
		}
		file << Class << " " << day << "/" << month << "/" << year << " " << desc << " " << price << " " << quantity << endl;
		file.close();
	}

	~Groceries() {
		//cout << "Deconstructing Transportation class." << endl;
	}

};

class GiftsAndDonations : protected Categories {

private:
	static double totalSpending;

public:

	//prompts for constructing GiftsAndDonations class object
	GiftsAndDonations() {
		cout << "Please enter purchase year: ";
		cin >> this->PurchaseInfo.year;
		cout << "Please enter purchase month: ";
		cin >> this->PurchaseInfo.month;
		cout << "Please enter purchase day: ";
		cin >> this->PurchaseInfo.day;
		cout << "Please enter a brief description: ";
		cin >> this->itemDescription;
		cout << "Please enter item price: ";
		cin >> this->itemPrice;
		cout << "Please enter item quantity: ";
		cin >> this->itemQuantity;

		setTotalSpending(itemPrice, itemQuantity);

		appendToTxt("Gifts and Donations", PurchaseInfo.year, PurchaseInfo.month, PurchaseInfo.day, itemDescription, itemPrice, itemQuantity);
	}

	GiftsAndDonations(int yearGiven, int monthGiven, int dayGiven, string desc, double priceGiven, double quantityGiven) {
		PurchaseInfo.year = yearGiven;
		PurchaseInfo.month = monthGiven;
		PurchaseInfo.day = dayGiven;
		itemDescription = desc;
		itemPrice = priceGiven;
		itemQuantity = quantityGiven;

		setTotalSpending(itemPrice, quantityGiven);
	}


	//sets total spending for static variable for this class
	static void setTotalSpending(double& itemPrice, double& quantityGiven) {
		totalSpending += itemPrice * quantityGiven;
		return;
	}

	//gets total spending for static variable for this class
	static void getTotalSpending() {
		cout << "Total spending on Gifts and Donations: " << totalSpending << endl;
		return;
	}

	double totalSpent() override {
		double total = GiftsAndDonations::totalSpending;
		return total;
	}

	void appendToTxt(string Class, int year, int month, int day, string desc, double price, double quantity) {
		fstream file;
		file.open("FinanceTracker.dat", ios::out | ios::in | ios::app);
		if (!file) {
			cout << "Error opening data file for read and write." << endl;
		}
		file << Class << " " << day << "/" << month << "/" << year << " " << desc << " " << price << " " << quantity << endl;
		file.close();
	}

	~GiftsAndDonations() {
		//cout << "Deconstructing Transportation class." << endl;
	}

};

class Events : protected Categories {

private:
	static double totalSpending;

public:

	//prompts for constructing Events class object
	Events() {
		cout << "Please enter purchase year: ";
		cin >> this->PurchaseInfo.year;
		cout << "Please enter purchase month: ";
		cin >> this->PurchaseInfo.month;
		cout << "Please enter purchase day: ";
		cin >> this->PurchaseInfo.day;
		cout << "Please enter a brief description: ";
		cin >> this->itemDescription;
		cout << "Please enter event price: ";
		cin >> this->itemPrice;
		cout << "Please enter event quantity: ";
		cin >> this->itemQuantity;

		setTotalSpending(itemPrice, itemQuantity);

		appendToTxt("Events", PurchaseInfo.year, PurchaseInfo.month, PurchaseInfo.day, itemDescription, itemPrice, itemQuantity);
	}

	Events(int yearGiven, int monthGiven, int dayGiven, string desc, double priceGiven) {
		PurchaseInfo.year = yearGiven;
		PurchaseInfo.month = monthGiven;
		PurchaseInfo.day = dayGiven;
		itemDescription = desc;
		itemPrice = priceGiven;
		itemQuantity = 1;

		setTotalSpending(itemPrice, itemQuantity);
	}

	//sets total spending for static variable for this class
	static void setTotalSpending(double& itemPrice, double& quantityGiven) {
		totalSpending += itemPrice * quantityGiven;
		return;
	}

	//gets total spending for static variable for this class
	static void getTotalSpending() {
		cout << "Total spending on Gifts and Donations: " << totalSpending << endl;
		return;
	}

	double totalSpent() override {
		double total = Events::totalSpending;
		return total;
	}

	void appendToTxt(string Class, int year, int month, int day, string desc, double price, double quantity) {
		fstream file;
		file.open("FinanceTracker.dat", ios::out | ios::in | ios::app);
		if (!file) {
			cout << "Error opening data file for read and write." << endl;
		}
		file << Class << " " << day << "/" << month << "/" << year << " " << desc << " " << price << " " << quantity << endl;
		file.close();
	}

	~Events() {
		//cout << "Deconstructing Transportation class." << endl;
	}

};

class Other : protected Categories {

private:
	static double totalSpending;

public:

	//prompts for constructing Other class object
	Other() {
		cout << "Please enter purchase year: ";
		cin >> this->PurchaseInfo.year;
		cout << "Please enter purchase month: ";
		cin >> this->PurchaseInfo.month;
		cout << "Please enter purchase day: ";
		cin >> this->PurchaseInfo.day;
		cout << "Please enter a brief description: ";
		cin >> this->itemDescription;
		cout << "Please enter item price: ";
		cin >> this->itemPrice;
		cout << "Please enter item quantity: ";
		cin >> this->itemQuantity;

		setTotalSpending(itemPrice, itemQuantity);

		appendToTxt("Other", PurchaseInfo.year, PurchaseInfo.month, PurchaseInfo.day, itemDescription, itemPrice, itemQuantity);
	}

	Other(int yearGiven, int monthGiven, int dayGiven, string desc, double priceGiven, double quantityGiven) {
		PurchaseInfo.year = yearGiven;
		PurchaseInfo.month = monthGiven;
		PurchaseInfo.day = dayGiven;
		itemDescription = desc;
		itemPrice = priceGiven;
		itemQuantity = quantityGiven;

		setTotalSpending(itemPrice, itemQuantity);
	}

	//sets total spending for static variable for this class
	static void setTotalSpending(double& itemPrice, double& quantityGiven) {
		totalSpending += itemPrice * quantityGiven;
		return;
	}

	//gets total spending for static variable for this class
	static void getTotalSpending() {
		cout << "Total spending on Gifts and Donations: " << totalSpending << endl;
		return;
	}

	double totalSpent() override {
		double total = Other::totalSpending;
		return total;
	}

	void appendToTxt(string Class, int year, int month, int day, string desc, double price, double quantity) {
		fstream file;
		file.open("FinanceTracker.dat", ios::out | ios::in | ios::app);
		if (!file) {
			cout << "Error opening data file for read and write." << endl;
		}
		file << Class << " " << day << "/" << month << "/" << year << " " << desc << " " << price << " " << quantity << endl;
		file.close();
	}

	~Other() {
		//cout << "Deconstructing Transportation class." << endl;
	}

};


double Transportation::totalSpending = 0;
double Groceries::totalSpending = 0;
double GiftsAndDonations::totalSpending = 0;
double Events::totalSpending = 0;
double Other::totalSpending = 0;

/*this function reads all data from .dat file*/
void readFromTxt() {
	fstream file;
	file.open("FinanceTracker.dat", ios::out | ios::in | ios::app);
	if (!file) {
		cout << "Error opening data file for read and write." << endl;
	}
	//while file is not at end
	while (file) {
		char read = file.get();
		cout << read;
	}
	file.close();
}

ostream& operator<<(ostream& ostr, Transportation mode) {
	ostr << "Testing Transportation" << endl;
	return ostr;
};

ostream& operator<<(ostream& ostr, Groceries grocery) {
	ostr << "Testing Abstract" << endl;
	return ostr;
};

ostream& operator<<(ostream& ostr, GiftsAndDonations gift) {
	ostr << "Testing GiftsAndDonations" << endl;
	return ostr;
};

ostream& operator<<(ostream& ostr, Events event) {
	ostr << "Testing GiftsAndDonations" << endl;
	return ostr;
};

void compareSalaries(ConstantFeatures x, ConstantFeatures y) {

	//gets current salary
	double yearlyCurrent = x.getYearlyIncome();
	//gets prospective salary
	double yearlyProspective = y.getYearlyIncome();

	//assummes + growth in print statements
	if (yearlyProspective > yearlyCurrent) {
		double differencePerYear = yearlyProspective - yearlyCurrent;
		cout << "Your difference in income is: " << "      Yearly ->   " << differencePerYear << endl;
		double biweeklyCurrent = x.getBiweeklyIncome();
		double biweeklyProspective = y.getBiweeklyIncome();
		double differencePerPaycheck = biweeklyProspective - biweeklyCurrent;
		const double newBudget = y.getMonthlyBudgetGivenNewIncome(biweeklyProspective);
		cout << "                              " << "      Per Paycheck ->   " << differencePerPaycheck << endl << endl;
		cout << "Your new monthly (assuming fixed expenses) is:   " << "      Budget -> " << newBudget << endl << endl;
	} 
	//assumes negative growth in print statements
	else if (yearlyCurrent > yearlyProspective) {
		double differencePerYear = yearlyProspective - yearlyCurrent;
		cout << "Your difference in income is: " << "      Yeary ->   " << differencePerYear << endl;
		double biweeklyCurrent = x.getBiweeklyIncome();
		double biweeklyProspective = y.getBiweeklyIncome();
		double differencePerPaycheck = biweeklyProspective - biweeklyCurrent;
		cout << "                              " << "      Per Paycheck ->   " << differencePerPaycheck << endl;
		const double newBudget = y.getMonthlyBudgetGivenNewIncome(biweeklyProspective);
		cout << "                              " << "      Per Paycheck ->   " << differencePerPaycheck << endl << endl;
		cout << "Your new monthly budget is:   " << "      Budget -> " << newBudget << endl << endl;
	}
	else {
		cout << "Incomes are the same." << endl;
	}

	cout << "********************************END OF FUNCTION*******************************" << endl << endl;
}

int main()
{
	fstream file;
	file.open("FinanceTracker.dat", ios::out | ios::in | ios::app);
	if (!file) {
		cout << "Error opening data file for read and write." << endl;
	}

	cout << "Welcome to your Personal Finance Tracker." << endl << endl;
	cout << "This program has several different use cases. See the descriptions below:" << endl;
	cout << "(1) Compare salary information: Useful for when considering a job change or promotion." << endl;
	cout << "(2) Append expense to .txt file: Useful for keeping a running log of expenses." << endl;
	cout << "(3) Read expenses from .txt file: View all expenses and information regarding those expenses." << endl;
	cout << "(4) Finish entries and exit." << endl;

	while (1) {
		cout << "Please enter 1, 2, 3, or 4 to choose from the above menu: ";
		char test{ 0 };
		cin >> test;
		while (test != '4') {
			if (test == '1') {
				/*option1: Given fixed monthly expenses, determine extra takehome money based on two different salaries
				   Useful for when consider job changes, promotions, etc. */
				cout << "To start, please follow the prompt for your current salary and fixed expense information." << endl;
				ConstantFeatures current;
				ConstantFeatures prospective;
				compareSalaries(current, prospective);
				cout << "Please enter 1, 2, 3, or 4 from program menu to choose your next action: ";
				cin >> test;
				continue;
			}
			/*program will dynamically allocate and deallocate each object to append to .dat file*/
			else if (test == '2') {
				char expense{ 0 };
				cout << "We will account for five expense types in this program. These types are: " << endl;
				cout << "(1) Transporation" << endl;
				cout << "(2) Groceries" << endl;
				cout << "(3) Gifts and Donations" << endl;
				cout << "(4) Events/Dinners/Outings" << endl;
				cout << "(5) Other" << endl;
				cout << "Please enter the number corresponding to type of expense: ";
				cin >> expense;

				if (expense == '1') {
					Transportation* ptr;
					ptr = new Transportation();
					delete ptr;
				}
				else if (expense == '2') {
					Groceries* ptr;
					ptr = new Groceries();
					delete ptr;
				}
				else if (expense == '3') {
					GiftsAndDonations* ptr;
					ptr = new GiftsAndDonations();
					delete ptr;
				}
				else if (expense == '4') {
					Events* ptr;
					ptr = new Events();
					delete ptr;
				}
				else if (expense == '5') {
					Other* ptr;
					ptr = new Other();
					delete ptr;
				}
				else {
					cout << "Invalid option number.";
				}
				cout << "Please enter 1, 2, 3, or 4 from program menu to choose your next action: ";
				cin >> test;
			}
			/*program will print all information from .dat file to serial terminal*/
			else if (test == '3') {
				readFromTxt();
				cout << "Please enter 1, 2, 3, or 4 from program menu to choose your next action: ";
				cin >> test;
			}
			/*end program*/
			else if (test == '4') {
				break;
			}
			else {
				cout << "Invalid option. Please enter 1, 2, 3, or 4 to continue: ";
				cin >> test;
			}
		}
		cout << "All entries saved to text file for future use. Exiting program now. Thank you!" << endl;
		break;
	}

	file.close();
	return 0;
}
