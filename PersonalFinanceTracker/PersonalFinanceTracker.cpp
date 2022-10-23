// PersonalFinanceTracker.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
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

	virtual double totalSpent() {

		return 0;
	}
};

ostream& operator<<(ostream& ostr, Categories item) {
	ostr << "Testing Abstract" << endl;
	return ostr;
};

class Transportation : protected Categories {

private:
	static double totalSpending;

public:

	Transportation() {
		//cout << "Constructing Transportation class." << endl;
		PurchaseInfo.year = 0;
		PurchaseInfo.month = 0;
		PurchaseInfo.day = 0;
		itemDescription = "";
		itemPrice = 0.0;
		itemQuantity = 0;
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

	static void setTotalSpending(double &itemPrice, double &quantityGiven) {
		totalSpending += itemPrice * quantityGiven;
		return;
	}

	static void getTotalSpending() {
		cout << "Total spending on Transportation: " << totalSpending << endl;
		return;
	}

	~Transportation() {
		//cout << "Deconstructing Transportation class." << endl;
	}
};

class Groceries : protected Categories {

private:
	static double totalSpending;

public:

	Groceries() {
		//cout << "Constructing Transportation class." << endl;
		PurchaseInfo.year = 0;
		PurchaseInfo.month = 0;
		PurchaseInfo.day = 0;
		itemDescription = "";
		itemPrice = 0.0;
		itemQuantity = 0;
	}

	Groceries(int priceGiven) {
		itemPrice = priceGiven;
		cout << "Please provide basic description for this entry, then press enter." << endl;
		cin >> itemDescription;
		//assume quantity is one since no specifics provided
		itemQuantity = 1;
		setTotalSpending(itemPrice, itemQuantity);
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

	static void setTotalSpending(double& itemPrice, double& quantityGiven) {
		totalSpending += itemPrice * quantityGiven;
		return;
	}

	static void getTotalSpending() {
		cout << "Total spending on Transportation: " << totalSpending << endl;
		return;
	}

	~Groceries() {
		//cout << "Deconstructing Transportation class." << endl;
	}

};

double Transportation::totalSpending = 0;
double Groceries::totalSpending = 0;

ostream& operator<<(ostream& ostr, Transportation item) {
	ostr << "Testing Transporation" << endl;
	return ostr;
};

void compareSalaries(ConstantFeatures x, ConstantFeatures y) {

	double yearlyCurrent = x.getYearlyIncome();
	double yearlyProspective = y.getYearlyIncome();

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
	ConstantFeatures current;
	ConstantFeatures prospective;

	/*option1: Given fixed monthly expenses, determine extra takehome money based on two different salaries
	           Useful for when consider job changes, promotions, etc. */
			   compareSalaries(current, prospective);
	
	//Transportation test(0, 0, 0, "test", 10.0, 2.0);
	//Groceries test2(200);
	//Transportation::getTotalSpending();
	//Groceries::getTotalSpending();
	return 0;
}
