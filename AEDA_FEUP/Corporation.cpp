#include "Corporation.h"

Utilities u1;
Menu corpMenu;

Corporation * Corporation::instance() {

	if (!singleton_instance) {
		singleton_instance = new Corporation;
	}

	return singleton_instance;
}

void Corporation::createPriorityQueueFromRents()
{
	priority_queue<Rent> tmp;
	for (int i = 0; i < rentsVec.size(); i++)
	{
		tmp.push(rentsVec[i]);
	}
	discountsRents = tmp;
}

vector<Rent> Corporation::setDiscounts(vector<Rent> v)
{
	priority_queue<Rent> tmp;

	for (int i = 0; i < v.size(); i++)
	{
		float newPrice;
		if (v[i].lastRent() >= 0 && v[i].lastRent() < 20)
			continue;
		else if (v[i].lastRent() >= 100)
			newPrice = v[i].getPrice() - 0.2 * v[i].getPrice();
		else if (v[i].lastRent() >= 50)
			newPrice = v[i].getPrice() - 0.1 * v[i].getPrice();
		else if (rentsVec[i].lastRent() >= 20)
			newPrice = v[i].getPrice() - 0.05 * v[i].getPrice();

		v[i].setPrice(newPrice);
		tmp.push(v[i]);
	}

	discountsRents = tmp;
	return v;
}

void Corporation::displayDiscounts()
{
	priority_queue<Rent> tmp = discountsRents;

	string city, nameRent, typeRent, type;
	unsigned int n_people, n, counter = 1, option;
	bool isIn = true;
	float xPrice;
	vector<int> v;

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);


	city = Corporation::instance()->cities();
	u1.cinClear();
	u1.clearScreen();


	u1.setColor(11); cout << "Rooms available right now that are available at a discount: \n\n"; u1.setColor(15);

	while (!tmp.empty())
	{
		Rent x = tmp.top();
		tmp.pop();
		if ((x.getCity() == city) && (x.lastRent() > 20)) {
			if (x.getTypeRent() == "Hotel") {
				u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
				cout << "Type of accommodation: " << x.getTypeRent() << endl;
				cout << "Name: " << x.getName() << endl;
				cout << "Available from: " << x.getDataInicio();
				cout << "  To: " << x.getDataFim() << endl;
				cout << "Room type: " << x.getType() << endl;
				cout << "Price per night:\n"; u1.setColor(11); cout << "Was: ";
				if (x.lastRent() > 20 && x.lastRent() < 50)
					cout << x.getPrice() + 0.05* x.getPrice() << "\nNow: " << x.getPrice() << endl;
				else if (x.lastRent() >= 50 && x.lastRent() < 100)
					cout << x.getPrice() + 0.1* x.getPrice() << "\nNow: " << x.getPrice() << endl;
				else if (x.lastRent() >= 100)
					cout << x.getPrice() + 0.2* x.getPrice() << "\nNow: " << x.getPrice() << endl;
				u1.setColor(15);
				cout << "Capacity: " << x.getNumPeople() << endl << endl;
				counter++;
			}
			else if (x.getTypeRent() == "Apartment" && x.lastRent() > 20) {
				u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
				cout << "Type of accommodation: " << x.getTypeRent() << endl;
				cout << "Name: " << x.getName() << endl;
				cout << "Available from: " << x.getDataInicio();
				cout << "  To: " << x.getDataFim() << endl;
				cout << "Has Kitchen: " << x.getKitchen() << endl;
				cout << "Has Living Room: " << x.getLivingRoom() << endl;
				cout << "Has Suite: " << x.getSuite() << endl;
				cout << "Price per night:\n"; u1.setColor(11); cout << "Was: ";
				if (x.lastRent() > 20 && x.lastRent() < 50)
					cout << x.getPrice() + 0.05* x.getPrice() << "\nNow: " << x.getPrice() << endl;
				else if (x.lastRent() >= 50 && x.lastRent() < 100)
					cout << x.getPrice() + 0.1* x.getPrice() << "\nNow: " << x.getPrice() << endl;
				else if (x.lastRent() >= 100)
					cout << x.getPrice() + 0.2* x.getPrice() << "\nNow: " << x.getPrice() << endl;
				u1.setColor(15);
				cout << "Capacity: " << x.getNumPeople() << endl << endl;
				counter++;
			}
			else {
				u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
				cout << "Type of accommodation: " << x.getTypeRent() << endl;
				cout << "Name: " << x.getName() << endl;
				cout << "Available from: " << x.getDataInicio();
				cout << "  To: " << x.getDataFim() << endl;
				cout << "Price per night:\n"; u1.setColor(11); cout << "Was: ";
				if (x.lastRent() > 20 && x.lastRent() < 50)
					cout << x.getPrice() + 0.05* x.getPrice() << "\nNow: " << x.getPrice() << endl;
				else if (x.lastRent() >= 50 && x.lastRent() < 100)
					cout << x.getPrice() + 0.1* x.getPrice() << "\nNow: " << x.getPrice() << endl;
				else if (x.lastRent() >= 100)
					cout << x.getPrice() + 0.2* x.getPrice() << "\nNow: " << x.getPrice() << endl;
				u1.setColor(15);
				cout << "Capacity: " << x.getNumPeople() << endl << endl;
				counter++;

			}
		}
	}


	if (counter == 1) {
		u1.setColor(12); cerr << "  There are no rents available between the dates specified.\n  Returning to the menu."; u1.setColor(15);
		Sleep(2000);
		return;

	}

	cout << "\n In order to make a reservation, please proceed to the appropriate menu.\n";

	u1.pressToContinueMessage();
	return;

}

void Corporation::createBST()
{
	for (int i = 0; i < usersVec.size(); i++)
	{
		receipt.insert(usersVec[i]);
	}
	BSTItrIn<Users> notFound(receipt);

	bool hasNotFound = false;
	while (!hasNotFound)
	{
		notFound.retrieve().getNif();
		if (notFound.retrieve().getNif() == 999999999)
			hasNotFound = true;
		else
			notFound.advance();
	}

	for (int i = 0; i < rentsVec.size(); i++)
	{
		Rent x = rentsVec[i];

		for (int j = 0; j < rentsVec[i].getReservations().size(); j++)
		{
			BSTItrIn<Users> it(receipt);
			while (!it.isAtEnd())
			{
				if (it.retrieve().getNif() == x.getReservations()[j].getnif())
				{
					it.retrieve().addReservation(x.getReservations()[j]);
					it.retrieve().orderReservations();
				}
				it.advance();
				if ((!checkExistance(x.getReservations()[j].getnif())) && it.isAtEnd())
				{
					notFound.retrieve().addReservation(x.getReservations()[j]);
					notFound.retrieve().orderReservations();
				}
			}
		
		}
	}

	return;
}


void Corporation::displayBST()
{
	BSTItrIn<Users> it(receipt);
	long nonReg = 999999999;

	while (!it.isAtEnd())
	{
		if (!(it.retrieve().getReservation().empty())) {

			if (it.retrieve().getNif() == nonReg) {
				u1.setColor(14); cout << "Reservations made by unregistered users: \n\n"; u1.setColor(15);

				for (int i = 0; i < it.retrieve().getReservation().size(); i++) {
					cout << "  NIF: " << it.retrieve().getReservation()[i].getnif() << "\n  Check-in Date: " << it.retrieve().getReservation()[i].getDate1() << "\n  Check-out Date: " << it.retrieve().getReservation()[i].getDate2() << "\n  Price: " << it.retrieve().getReservation()[i].getPrice() << " euros" << endl << endl;
				}
			}
			else {
				u1.setColor(14); cout << "Reservations made by: " << it.retrieve().getUsername() << endl << endl; u1.setColor(15);
				for (int i = 0; i < it.retrieve().getReservation().size(); i++) {
					cout << "  Check-in Date: " << it.retrieve().getReservation()[i].getDate1() << "\n  Check-out Date: " << it.retrieve().getReservation()[i].getDate2() << "\n  Price: " << it.retrieve().getReservation()[i].getPrice() << " euros" << endl << endl;
				}
			}
		}
		
		it.advance();
	}

	u1.pressToContinueMessage();
}

bool Corporation::checkExistance(int nif)
{
	for (int i = 0; i < usersVec.size(); i++)
	{
		if (nif == usersVec[i].getNif())
		{
			return true;
		}
	}
	return false;
}

void Corporation::login() {

	string password, user;
	bool foundUser = false;
	bool foundSupplier = false;
	bool isIn = true;

	while (isIn) {

		u1.setColor(14); cout << "\n  ::| LOGIN |::\n\n"; u1.setColor(15);

		cout << "Username:  ";
		getline(cin, user);

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.MainMenu();
		}

		cout << "\nPassword:  "; cin >> password;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.MainMenu();
		}

		u1.cinClear();

		for (size_t i = 0; i != usersVec.size(); i++) {
			if (usersVec.at(i).getUsername() == user && usersVec.at(i).getPassword() == password) {
				Corporation::instance()->username = user;
				Corporation::instance()->nif = usersVec.at(i).getNif();
				foundUser = true;
				u1.clearScreen();
				corpMenu.UsersMenu();
				return;
			}
		}

		for (size_t i = 0; i != suppliersVec.size(); i++) {
			if (suppliersVec.at(i).getName() == user && suppliersVec.at(i).getPassword() == password) {
				Corporation::instance()->supplierName = user;
				Corporation::instance()->nif = suppliersVec.at(i).getNif();
				foundSupplier = true;
				u1.clearScreen();
				corpMenu.SuppliersMenu();
				return;
			}
		}

		if (!foundUser && !foundSupplier) {
			u1.setColor(12);
			cout << "\n  ERROR: The username/password combination you inserted does not exist.";
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z."; u1.setColor(15);
			Sleep(1500);
			u1.clearScreen();
			continue;
		}
	}
}

void Corporation::managmentLogin(){

	string password, user;
	bool isIn = true;

	while (isIn) {

		u1.setColor(14); cout << "\n  ::| LOGIN |::\n\n"; u1.setColor(15);

		u1.setColor(11); cout << "Insert the manager credentials below:\n\n"; u1.setColor(15);

		cout << " Username:  ";
		getline(cin, user);

		if (user != "manager") {
			u1.setColor(12); cout << "The username you inserted does not match the manager's one.\n";
			Sleep(1500);
			cout << endl << "  Please try again or login normally from the main menu. If you wish to cancel the operation press CTRL + Z."; u1.setColor(15);
			Sleep(2500);
			u1.clearScreen();
			continue;
		}

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.MainMenu();
		}

		cout << "\n Password:  "; cin >> password;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.MainMenu();
		}

		if (password != "manager123") {
			u1.setColor(12); cout << "The password you inserted does not match the manager's one.\n";
			Sleep(1500);
			cout << endl << "  Please try again or login normally from the main menu. If you wish to cancel the operation press CTRL + Z."; u1.setColor(15);
			Sleep(2500);
			u1.clearScreen();
			continue;
		}

		u1.cinClear();
		u1.clearScreen();
		corpMenu.ManagmentMenu();
	}
	
	return;
}

//Checks existance of the users file
bool Corporation::foundUsersFile(string usersFile) {

	fstream f;

	f.open(usersFile);

	if (f.fail()) {
		f.close();
		u1.setColor(12); cerr << "\n  ERROR: " << usersFile << " (users file) could not be found!\n         Verify the directory!\n\n"; u1.setColor(15);
		return false;
	}

	f.close();

	this->usersFile = usersFile;
	return true;
}

//Loads the users file to memory (Users vector)
void Corporation::loadUsers() {

	string line;
	fstream f;

	f.open(usersFile);

	while (getline(f, line)) {

		string username = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string password = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int nif = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int points = stoi(line);
		usersVec.push_back(Users(username, password, nif, points));
	}
	f.close();
	return;
}

//Loads memory to the users file
void Corporation::saveUsers() {

	ofstream f("temp.txt");

	for (size_t i = 0; i < usersVec.size(); i++) {
		f << usersVec[i].getUsername() << " ; " << usersVec[i].getPassword() << " ; " << usersVec[i].getNif() << " ; " << usersVec[i].getPoints() << endl;
	}

	f.close();

	remove(usersFile.c_str());
	rename("temp.txt", usersFile.c_str());

	return;
}

//Adds a user to the users vector
void Corporation::registerUser() {

	string user, password, nif;
	bool isIn = true;

	while (isIn) {

		u1.setColor(14); cout << "\n  ::| REGISTER |::\n"; u1.setColor(15);

		cout << "\n Username:  "; getline(cin, user);

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.RegisterMenu();
		}

		for (unsigned int index = 0; index != user.size(); index++) {
			if (!isalpha(user[index]) && user[index] != ' ') {
				u1.setColor(12); cerr << "  ERROR: Name must only contain alphabetic characters."; u1.setColor(15);
				Sleep(1500);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.cinClear();
				u1.clearScreen();
				continue;
			}
		}

		for (unsigned int index2 = 0; index2 != usersVec.size(); index2++) {
			if (usersVec.at(index2).getUsername() == user) {
				u1.setColor(12); cerr << "  ERROR: The username you selected already exists. Please choose another one. "; u1.setColor(15);
				Sleep(1500);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.cinClear();
				u1.clearScreen();
				continue;
			}
		}

		cout << "\n Password:  "; cin >> password;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.RegisterMenu();
		}
		u1.cinClear();

		for (unsigned int index3 = 0; index3 != password.size(); index3++) {
			if (!isalnum(password[index3])) {
				u1.setColor(12); cerr << "  ERROR: Password cannot contain special characters. "; u1.setColor(15);
				Sleep(1500);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.clearScreen();
				continue;
			}
		}

		cout << "\n NIF:  "; cin >> nif;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.RegisterMenu();
		}
		u1.cinClear();

		for (unsigned int index4 = 0; index4 != nif.size(); index4++) {
			if (!isdigit(nif[index4])) {
				u1.setColor(12); cerr << "  ERROR: NIF can only contain digits. "; u1.setColor(15);
				Sleep(1500);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.clearScreen();
				continue;
			}
		}

		for (unsigned int index5 = 0; index5 != usersVec.size(); index5++) {
			if (usersVec.at(index5).getNif() == stoi(nif)) {
				u1.setColor(12); cerr << "  ERROR: The NIF you selected was already found in our system. Probably you already have an account. "; u1.setColor(15);
				Sleep(2000);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.clearScreen();
				continue;
			}

		}

		if (nif.size() != 9) {
			u1.setColor(12); cerr << "  ERROR: The NIF must have 9 digits. "; u1.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.clearScreen();
			continue;
		}
		break;
	}

	usersVec.push_back(Users(user, password, stoi(nif), 0));
	u1.clearScreen();
	corpMenu.MainMenu();
}

void Corporation::printSuppliersRents()
{
	int counter = 1;
	
	u1.setColor(14); cout << "Your active rents: \n\n"; u1.setColor(15);

	for (int i = 0; i < rentsVec.size(); i++) {
		if (nif == rentsVec.at(i).getNif()) {
			if (rentsVec.at(i).getTypeRent() == "Hotel") {
				u1.setColor(11); cout << "Rent [" << counter << "]\n"; u1.setColor(15);
				cout << "Type of accomodation: " << rentsVec.at(i).getTypeRent() << endl;
				cout << "Name: " << rentsVec.at(i).getName() << endl;
				cout << "Available from: " << rentsVec.at(i).getDataInicio();
				cout << "   To: " << rentsVec.at(i).getDataFim() << endl;
				cout << "Price per night: " << rentsVec.at(i).getPrice() << endl;
				cout << "Capacity: " << rentsVec.at(i).getNumPeople() << endl;
				cout << "Type of room: " << rentsVec.at(i).getType() << endl << endl;
				counter++;
			}
			else if (rentsVec.at(i).getTypeRent() == "Apartment") {
				u1.setColor(11); cout << "Rent [" << counter << "]\n"; u1.setColor(15);
				cout << "Type of accomodation: " << rentsVec.at(i).getTypeRent() << endl;
				cout << "Name: " << rentsVec.at(i).getName() << endl;
				cout << "Available from: " << rentsVec.at(i).getDataInicio();
				cout << "   To: " << rentsVec.at(i).getDataFim() << endl;
				cout << "Has Kitchen: " << rentsVec.at(i).getKitchen() << endl;
				cout << "Has Living Room: " << rentsVec.at(i).getLivingRoom() << endl;
				cout << "Has Suite: " << rentsVec.at(i).getSuite() << endl;
				cout << "Price per night: " << rentsVec.at(i).getPrice() << endl;
				cout << "Capacity: " << rentsVec.at(i).getNumPeople() << endl << endl;
				counter++;
			}
			else {
				u1.setColor(11); cout << "Rent [" << counter << "]\n"; u1.setColor(15);
				cout << "Type of accomodation: " << rentsVec.at(i).getTypeRent() << endl;
				cout << "Name: " << rentsVec.at(i).getName() << endl;
				cout << "Available from: " << rentsVec.at(i).getDataInicio();
				cout << "   To: " << rentsVec.at(i).getDataFim() << endl;
				cout << "Price per night: " << rentsVec.at(i).getPrice() << endl;
				cout << "Capacity: " << rentsVec.at(i).getNumPeople() << endl << endl;
				counter++;
			}
		}
	}

	if (counter == 1) {
		cout << "You currently have no rents... You can add a rent in the Menu.\n";
	}

	u1.pressToContinueMessage();

}

bool Corporation::foundSuppliersFile(string suppliersFile) {

	fstream f;

	f.open(suppliersFile);

	if (f.fail()) {
		f.close();
		u1.setColor(12); cerr << "\n  ERROR: " << suppliersFile << " (suppliers file) could not be found!\n         Verify the directory!\n\n"; u1.setColor(15);
		return false;
	}

	f.close();

	this->suppliersFile = suppliersFile;
	return true;
}

void Corporation::loadRents()
{
	Rent tmp;
	fstream r;
	float price;
	r.open("rents.txt");
	string lineRents;
	while (getline(r, lineRents)) {
		int nif = stoi(u1.trim(lineRents.substr(0, lineRents.find(" ; "))));
		lineRents.erase(0, lineRents.find(" ; ") + 3);

		string typeRent = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
		lineRents.erase(0, lineRents.find(" ; ") + 3);
		if (typeRent == "Hotel") {
			string nameHotel = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string roomType = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents);
			lineRents.erase(0, lineRents.length());
			tmp = Hotel(nif, typeRent, nameHotel, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), roomType, price, numPeople);

		}
		else if (typeRent == "Bed'n'Breakfast") {
			string nameBB = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents);
			lineRents.erase(0, lineRents.length());

			tmp = bedNbreakfast(nif, typeRent, nameBB, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople);

		}
		else if (typeRent == "Shared House") {
			string nameSH = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents);
			lineRents.erase(0, lineRents.length());
			tmp = sharedHouse(nif, typeRent, nameSH, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople);

		}
		else if (typeRent == "Flat") {
			string nameFlat = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = lineRents.substr(0, lineRents.find(" ; "));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents);
			lineRents.erase(0, lineRents.length());
			tmp = flat(nif, typeRent, nameFlat, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople);
		}
		else if (typeRent == "Apartment") {
			string nameApartment = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			string city = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int startDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int startYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int endDay = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endMonth = stoi(lineRents.substr(0, lineRents.find("/")));
			lineRents.erase(0, lineRents.find("/") + 1);
			unsigned int endYear = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			price = stof(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			unsigned int numPeople = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			int numRooms = stoi(lineRents.substr(0, lineRents.find(" ; ")));
			bool k, s, l;
			string x = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			if (x == "true")
				k = true;
			else
				k = false;
			x = u1.trim(lineRents.substr(0, lineRents.find(" ; ")));
			lineRents.erase(0, lineRents.find(" ; ") + 3);
			if (x == "true")
				s = true;
			else
				s = false;
			x = u1.trim(lineRents);
			lineRents.erase(0, lineRents.length());
			if (x == "true")
				l = true;
			else
				l = false;

			tmp = apartment(nif, typeRent, nameApartment, city, Date(startDay, startMonth, startYear), Date(endDay, endMonth, endYear), price, numPeople, numRooms, k, s, l);
		}
		string reservationsLine;
		getline(r, reservationsLine);
		int numIterations = stoi(u1.trim(reservationsLine.substr(0, reservationsLine.find(" ; "))));
		reservationsLine.erase(0, reservationsLine.find(" ; ") + 3);
		for (int j = 0; j < numIterations; j++) {

			float nifR = stof(u1.trim(reservationsLine.substr(0, reservationsLine.find(" ; "))));
			reservationsLine.erase(0, reservationsLine.find(" ; ") + 3);

			Date d1, d2;
			d1 = reservationsLine.substr(0, reservationsLine.find(" ; "));
			reservationsLine.erase(0, reservationsLine.find(" ; ") + 3);

			d2 = reservationsLine.substr(0, reservationsLine.find(" ; "));

			if (j == (numIterations - 1))
				reservationsLine.erase(0, reservationsLine.length());
			else
				reservationsLine.erase(0, reservationsLine.find(" ; ") + 3);
			price = (d2.minus(d1))*price;
			Reservation newR(nifR, price, d1, d2);
			tmp.setReservation(newR);
		}
		rentsVec.push_back(tmp);
	}
}

void Corporation::loadSuppliers() {

	string line, lineRents;
	fstream f;
	vector<Rent> xVec;

	double price;
	f.open(suppliersFile);

	while (getline(f, line)) {

		string supplierName = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string password = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		unsigned int nif = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		string address = line;
		line.erase(0, line.length());

		suppliersVec.push_back(Supplier(supplierName, password, nif, address));
	}

	f.close();

	return;
}

//Loads suppliersVec to the .txt file
void Corporation::saveSuppliers()
{
	ofstream f("tempSuppliers.txt");

	for (int i = 0; i < suppliersVec.size(); i++)
	{
		int j;
		f << suppliersVec[i].getName() << " ; " << suppliersVec[i].getPassword() << " ; " << suppliersVec[i].getNif() << " ; " << suppliersVec[i].getAddress() << "\n";
	}


	f.close();
	remove(suppliersFile.c_str());
	rename("tempSuppliers.txt", suppliersFile.c_str());

	return;
}

void Corporation::saveRents()
{
	int j;
	ofstream r("rents.txt");
	for (j = 0; j < rentsVec.size(); j++)
	{
		vector<Rent> x;
		x = rentsVec;
		if (x[j].getTypeRent() == "Hotel")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Hotel ; " << x[j].getName() << " ; " << x[j].getCity() << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getType() << " ; " << x[j].getPrice() << " ; " << x[j].getNumPeople();
			r << "\n";
		}

		if (x[j].getTypeRent() == "Bed'n'Breakfast")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Bed'n'Breakfast ; " << x[j].getName() << " ; " << u1.trim(x[j].getCity()) << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getPrice() << " ; " << x[j].getNumPeople();
			r << "\n";
		}
		if (x[j].getTypeRent() == "Shared House")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Shared House ; " << x[j].getName() << " ; " << u1.trim(x[j].getCity()) << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getPrice() << " ; " << x[j].getNumPeople();
			r << "\n";
		}
		if (x[j].getTypeRent() == "Flat")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Flat ; " << x[j].getName() << " ; " << u1.trim(x[j].getCity()) << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getPrice() << " ; " << x[j].getNumPeople();
			r << "\n";
		}
		if (x[j].getTypeRent() == "Apartment")
		{
			r << rentsVec[j].getNif() << " ; ";
			r << "Apartment ; " << x[j].getName() << " ; " << u1.trim(x[j].getCity()) << " ; ";
			r << x[j].getDataInicio() << " ; ";
			r << x[j].getDataFim() << " ; ";
			r << x[j].getPrice() << " ; " << x[j].getNumPeople() << " ; ";
			r << x[j].getNumRooms() << " ; ";
			r << x[j].getKitchen() << " ; " << x[j].getSuite() << " ; " << x[j].getLivingRoom();
			r << "\n";
		}
		if (x[j].getReservations().size() == 0)
			r << x[j].getReservations().size() << " ;\n";
		else {
			r << x.at(j).getReservations().size() << " ; ";
			for (int k = 0; k < x.at(j).getReservations().size(); k++)
			{
				if (k == (x[j].getReservations().size() - 1))
					r << x[j].getReservations()[k].getnif() << " ; " << x[j].getReservations()[k].getDate1() << " ; " << x[j].getReservations()[k].getDate2();
				else
					r << x[j].getReservations()[k].getnif() << " ; " << x[j].getReservations()[k].getDate1() << " ; " << x[j].getReservations()[k].getDate2() << " ; ";
			}
			r << endl;
		}

	}
	r.close();
	return;
}

void Corporation::deleteRents()
{
	bool isIn = true;
	int i;
	int nif;
	vector <int> v;
	for (int k = 0; k < suppliersVec.size(); k++)
		if (suppliersVec[k].getName() == Corporation::instance()->supplierName) {
			nif = suppliersVec[k].getNif();
		}
	while (isIn) {
		//u1.clearScreen();
		u1.setColor(14); cout << "\n  ::| DELETE RENT |::\n"; u1.setColor(15);
		cout << "\n\nHere are all your available rents. Type the number of the rent you wish to delete.\n\n";
		int counter = 1, tmp = 0;
		for (i = 0; i < rentsVec.size(); i++) {
			if (nif == rentsVec[i].getNif())
			{
				Rent x = rentsVec[i];
				cout << counter << "- ";
				cout << "City: " << x.getCity() << endl << "Beginning date: " << x.getDataInicio() << "\nEnd date: " << x.getDataFim() << endl;
				if (x.getTypeRent() == "Hotel")
				{
					cout << "Hotel - " << x.getName() << endl << "Type: " << x.getType() << "\nNumber of ocupants: " << x.getNumPeople() << "\nPrice: " << x.getPrice() << endl << endl;
					counter++;
					v.push_back(i);
				}
				if (x.getTypeRent() == "Apartment")
				{
					cout << "Apartment - " << x.getName() << "Beginning date: " << x.getDataInicio() << "\nEnd date: " << x.getDataFim() << "\nNumber of people: " << x.getNumPeople() << endl;
					if (x.getKitchen())
						cout << "With kitchen, ";
					else
						cout << "No kitchen, ";
					if (x.getSuite())
						cout << "with suite, ";
					else
						cout << "no suite, ";
					if (x.getLivingRoom())
						cout << "and with living room\n";
					else
						cout << " and without living room\n";
					cout << "Price: " << x.getPrice() << endl << endl;
					counter++;
					v.push_back(i);
				}
				if (x.getTypeRent() == "Flat")
				{
					cout << "Flat -" << x.getName() << "\nBeginning date: " << x.getDataInicio() << "\nEnd date:" << x.getDataFim() << "\nNumber of people: " << x.getNumPeople() << endl;
					if (x.getKitchen())
						cout << "With kitchen.\n";
					else
						cout << "Without kitchen.\n";

					cout << "Price " << x.getPrice() << endl << endl;
					counter++;
					v.push_back(i);
				}
				if (x.getTypeRent() == "Shared House")
				{
					cout << "Shared House - " << x.getName() << "\nBeginning date: " << x.getDataInicio() << "\nEnd date:" << x.getDataFim() << "\nNumber of people: " << x.getNumPeople() << endl;

					cout << "\nPrice :" << x.getPrice() << ".\n" << endl;
					counter++;
					v.push_back(i);
				}
				if (x.getTypeRent() == "Bed'n'Breakfast")
				{
					cout << "Bed'n'Breakfast - " << x.getName() << "\nBeginning date: " << x.getDataInicio() << "\nEnd date:" << x.getDataFim() << "\nNumber of people: " << x.getNumPeople() << endl;

					cout << "Price : " << x.getPrice() << endl << endl;
					counter++;
					v.push_back(i);
				}


			}
		}
		if (counter == 1) {
			cout << "You currently have no rents... You can add a rent in the Menu.\n";
			break;
		}
		isIn = false;
	}
	isIn = true;
	while (isIn) {

		int choice;
		cout << "Option: ";
		cin >> choice;
		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.SuppliersMenu();
		}
		if (cin.fail()) {
			cout << "\nInvalid input. Retrying last step.\n";
			continue;
		}
		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.SuppliersMenu();
		}

		if (choice < 1 || choice > i) {
			u1.setColor(12); cerr << endl << "  ERROR: Input can only range positive numbers.\n"; u1.setColor(15);
			Sleep(1500);
			u1.cinClear();
			corpMenu.SuppliersMenu();
		}


		if (rentsVec[v[choice - 1]].getReservations().size() > 0) {
			u1.setColor(12); cout << "WARNING : There are already reservations in that rent! Do you wish to continue? (y/n)\n"; u1.setColor(15);
			string option;
			cin >> option;
			if (option == "yes" || option == "y") {
				rentsVec.erase(rentsVec.begin() + (v[choice - 1]));
				cout << "\n  Operation completed successfully.\n";
				Sleep(1000);
			}
			else {
				cout << "\n  Returning to Main Menu.\n";
				Sleep(1000);
			}
			isIn = false;
			break;

		}
		else
		{
			rentsVec.erase(rentsVec.begin() + (v[choice - 1]));
			cout << "\n  Operation completed successfully.\n";
			Sleep(1000);
		}

		isIn = false;
	}
	u1.clearScreen();

}

//Adds a supplier to the suppliers vector
void Corporation::registerSupplier() {

	string user, password, nif, address;
	bool isIn = true;

	while (isIn) {

		u1.setColor(14); cout << "\n  ::| REGISTER |::\n"; u1.setColor(15);

		cout << "\n Username:  ";
		getline(cin, user);

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.RegisterMenu();
		}

		for (unsigned int index = 0; index != user.size(); index++) {
			if (!isalpha(user.at(index)) && user.at(index) != ' ') {
				u1.setColor(12); cerr << "  ERROR: Name must only contain alphabetic characters. "; u1.setColor(15);
				Sleep(1500);
				u1.clearScreen();
				u1.cinClear();
				continue;
			}
		}


		for (unsigned int index2 = 0; index2 != suppliersVec.size(); index2++) {
			if (suppliersVec.at(index2).getName() == user) {
				u1.setColor(12); cerr << "  ERROR: The username you selected already exists. Please choose another one. "; u1.setColor(15);
				Sleep(3000);
				u1.clearScreen();
				u1.cinClear();
				continue;
			}
		}


		cout << "\n Password:  "; cin >> password;
		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.RegisterMenu();
		}
		u1.cinClear();

		for (unsigned int index3 = 0; index3 != password.size(); index3++) {
			if (!isalnum(password.at(index3))) {
				u1.setColor(12); cerr << "  ERROR: Password cannot contain special characters. "; u1.setColor(15);
				Sleep(3000);
				u1.clearScreen();
				continue;
			}
		}

		cout << "\n NIF:  "; cin >> nif;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.RegisterMenu();
		}
		u1.cinClear();

		for (unsigned int index4 = 0; index4 != nif.size(); index4++) {
			if (!isdigit(nif.at(index4))) {
				u1.setColor(12); cerr << "  ERROR: NIF can only contain digits. "; u1.setColor(15);
				Sleep(3000);
				u1.clearScreen();
				continue;
			}
		}

		for (unsigned int index5 = 0; index5 != suppliersVec.size(); index5++) {
			if (suppliersVec.at(index5).getNif() == stoi(nif)) {
				u1.setColor(12); cerr << "  ERROR: The NIF you selected was already found in our system. Probably you already have an account. "; u1.setColor(15);
				Sleep(3000);
				u1.clearScreen();
				continue;
			}

		}

		if (nif.size() != 9) {
			u1.setColor(12); cerr << "  ERROR: The NIF must have 9 digits. "; u1.setColor(15);
			Sleep(3000);
			u1.clearScreen();
			continue;
		}

		cout << "\n Address:  "; cin >> address;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.RegisterMenu();
		}

		u1.cinClear();

		for (unsigned int i = 0; i != suppliersVec.size(); i++) {
			if (suppliersVec.at(i).getAddress() == address) {
				u1.setColor(12); cerr << "  ERROR: The address you selected was already found in our system. Probably you already have an account. "; u1.setColor(15);
				Sleep(3000);
				u1.clearScreen();
				continue;
			}
		}
	}

	suppliersVec.push_back(Supplier(user, password, stoi(nif), address));
	u1.clearScreen();
	return;
}

//Orders Suppliers
void Corporation::orderSuppliersVec()
{
	int i, j;
	for (i = 0; i < (suppliersVec.size() - 1); i++) {
		for (j = 0; j < suppliersVec.size() - 1; j++)
		{
			if (suppliersVec[j].getName() > suppliersVec[j + 1].getName())
			{
				string before, after;
				after = suppliersVec[j].getName();
				before = suppliersVec[j + 1].getName();
				suppliersVec[j + 1].setName(after);
				suppliersVec[j].setName(before);
			}
		}
	}

}

void Corporation::orderRentsVec()
{
	int i;
	if (rentsVec.size() == 1)
		return;
	for (int k = 0; k < (rentsVec.size() - 1); k++) {
		for (i = 0; i < (rentsVec.size() - 1); i++) {
			if (rentsVec[i].getPrice() > rentsVec[i + 1].getPrice())
			{
				Rent before, after;
				after = rentsVec[i];
				before = rentsVec[i + 1];
				rentsVec[i + 1] = after;
				rentsVec[i] = before;
			}
		}
		i = 0;
	}
}

//Adds rent to logged-in supplier
void Corporation::makeRent() {

	bool isIn = true;
	Date d1, d2;
	string cinNumIter, cinChoice;
	int numIteration, choice;
	vector<Rent> confirmRents;
	int counter = 1;

	while (isIn) {

		u1.setColor(14); cout << "\n  ::| CREATE RENT |::\n"; u1.setColor(15);

		cout << "\nHow many rents do you wish to be made available:  ";
		cin >> cinNumIter;
		cout << endl;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.SuppliersMenu();
		}

		for (size_t i = 0; i < cinNumIter.size(); i++) {
			if (!isdigit(cinNumIter.at(i))) {
				u1.setColor(12); cerr << endl << "  ERROR: Input can only contain digits. "; u1.setColor(15);
				Sleep(1500);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.cinClear();
				u1.clearScreen();
				continue;
			}
		}

		numIteration = stoi(cinNumIter);
		cin.clear();
		break;
	}

	long nif;

	for (int i = 0; i < suppliersVec.size(); i++)
		if (suppliersVec[i].getName() == Corporation::instance()->supplierName) {
			nif = suppliersVec[i].getNif();
		}


	for (int i = 0; i < numIteration; i++) {
		u1.setColor(11); cout << "What is the type of rent?\n\n"; u1.setColor(15);
		cout << "1 - Hotel\n2 - Bed'n'Breakfast\n3 - Apartment\n4 - Flat\n5 - Shared House\n\n";
		u1.setColor(14); cout << "Select the number corresponding to the option you wish to select: "; u1.setColor(15);
		cin >> cinChoice;

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.SuppliersMenu();
		}

		if (stoi(cinChoice) < 1 || stoi(cinChoice) > 5) {
			u1.setColor(12); cerr << endl << "  ERROR: Input can only range from 1 to 5. "; u1.setColor(15);
			Sleep(1500);
			u1.cinClear();
			corpMenu.SuppliersMenu();
		}

		for (size_t i = 0; i < cinChoice.size(); i++) {
			if (!isdigit(cinChoice.at(i))) {
				u1.setColor(12); cerr << endl << "  ERROR: Input can only contain digits. "; u1.setColor(15);
				Sleep(1500);
				u1.cinClear();
				corpMenu.SuppliersMenu();
			}
		}

		choice = stoi(cinChoice);

		if (choice == 1) {
			u1.clearScreen();
			Hotel h;
			rentsVec.push_back(h.buildRent(nif));
			confirmRents.push_back(rentsVec.back());
			continue;
		}
		if (choice == 2) {
			u1.clearScreen();
			bedNbreakfast bnb;
			rentsVec.push_back(bnb.buildRent(nif));
			confirmRents.push_back(rentsVec.back());
			continue;
		}
		if (choice == 3) {
			u1.clearScreen();
			apartment ap;
			rentsVec.push_back(ap.buildRent(nif));
			confirmRents.push_back(rentsVec.back());
			continue;
		}
		if (choice == 4) {
			u1.clearScreen();
			flat fl;
			rentsVec.push_back(fl.buildRent(nif));
			confirmRents.push_back(rentsVec.back());
			continue;
		}
		if (choice == 5) {
			u1.clearScreen();
			sharedHouse sh;
			rentsVec.push_back(sh.buildRent(nif));
			confirmRents.push_back(rentsVec.back());
			continue;
		}
	}

	u1.setColor(14); cout << "Rents: \n\n"; u1.setColor(15);
	for (size_t i = 0; i < confirmRents.size(); i++) {
		if (confirmRents.at(i).getTypeRent() == "Hotel") {
			cout << "Type of accommodation: " << confirmRents.at(i).getTypeRent() << endl;
			cout << "Name: " << confirmRents.at(i).getName() << endl;
			cout << "Available from: " << confirmRents.at(i).getDataInicio();
			cout << "  To: " << confirmRents.at(i).getDataFim() << endl;
			cout << "Room type: " << confirmRents.at(i).getType() << endl;
			cout << "Price per night: " << confirmRents.at(i).getPrice() << endl;
			cout << "Room's capacity: " << confirmRents.at(i).getNumPeople() << endl << endl;
		}
		else if (confirmRents.at(i).getTypeRent() == "Apartment") {
			cout << "Type of accommodation: " << confirmRents.at(i).getTypeRent() << endl;
			cout << "Name: " << confirmRents.at(i).getName() << endl;
			cout << "Available from: " << confirmRents.at(i).getDataInicio();
			cout << "  To: " << confirmRents.at(i).getDataFim() << endl;
			cout << "Has Kitchen: " << confirmRents.at(i).getKitchen() << endl;
			cout << "Has Living Room: " << confirmRents.at(i).getLivingRoom() << endl;
			cout << "Has Suite: " << confirmRents.at(i).getSuite() << endl;
			cout << "Price per night: " << confirmRents.at(i).getPrice() << endl;
			cout << "Room's capacity: " << confirmRents.at(i).getNumPeople() << endl << endl;

		}
		else {
			cout << "Type of accommodation: " << confirmRents.at(i).getTypeRent() << endl;
			cout << "Name: " << confirmRents.at(i).getName() << endl;
			cout << "Available from: " << confirmRents.at(i).getDataInicio();
			cout << "  To: " << confirmRents.at(i).getDataFim() << endl;
			cout << "Price per night: " << confirmRents.at(i).getPrice() << endl;
			cout << "Room's capacity: " << confirmRents.at(i).getNumPeople() << endl << endl;

		}
	}

	u1.successMessage();
	return;

}

void Corporation::makeReservation() // o unico erro � como dar display das rents e ainda vai haver modificacoes na estrutura da funcao
{
	string city, nameRent, typeRent, type;
	unsigned int n_people, n, counter = 1, option;
	bool isIn = true;
	float xPrice;
	vector<int> v;

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);

	vector<Rent> tmpRentsVec;
	tmpRentsVec = rentsVec;
	tmpRentsVec = setDiscounts(tmpRentsVec);

	city = Corporation::instance()->cities();
	u1.clearScreen();

	string dateB, dateE;

	while (isIn) {
		cout << "Date of check-in: "; cin >> dateB;

		Date date1 = Date(dateB);

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.UsersMenu();
		}

		if (!date1.isValid() || (real_date > date1)) {
			u1.setColor(12); cerr << endl << " ERROR: The date you inserted is not valid."; u1.setColor(15); Sleep(500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
			u1.clearScreen();
			continue;
		}
		else {
			u1.cinClear();
			isIn = false;
		}

		cout << "\nDate of check-out : "; cin >> dateE; cout << endl;

		Date date2 = Date(dateE);

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.UsersMenu();
		}

		if (!date2.isValid() || (real_date > date2)) {
			u1.setColor(12); cerr << "  ERROR: The date you inserted is not valid. Please use the format dd/mm/yyyy"; u1.setColor(15);
			Sleep(2000);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
			u1.clearScreen();
			continue;
		}
		else {
			u1.cinClear();
			isIn = false;
		}

		Rent * c = nullptr;

		u1.setColor(11); cout << "Rooms available between " << date1 << " and " << date2 << " in " << city << ": \n\n"; u1.setColor(15);

		for (int i = 0; i < tmpRentsVec.size(); i++) {
			if (tmpRentsVec[i].isValid(date1, date2) && (tmpRentsVec[i].getCity() == city)) {
				if (tmpRentsVec.at(i).getTypeRent() == "Hotel") {
					u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
					cout << "Type of accommodation: " << tmpRentsVec.at(i).getTypeRent() << endl;
					cout << "Name: " << tmpRentsVec.at(i).getName() << endl;
					cout << "Available from: " << tmpRentsVec.at(i).getDataInicio();
					cout << "  To: " << tmpRentsVec.at(i).getDataFim() << endl;
					cout << "Room type: " << tmpRentsVec.at(i).getType() << endl;
					cout << "Price per night: " << tmpRentsVec.at(i).getPrice() << endl;
					cout << "Capacity: " << tmpRentsVec.at(i).getNumPeople() << endl << endl;
					counter++;
					v.push_back(i);
				}
				else if (tmpRentsVec.at(i).getTypeRent() == "Apartment") {
					u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
					cout << "Type of accommodation: " << tmpRentsVec.at(i).getTypeRent() << endl;
					cout << "Name: " << tmpRentsVec.at(i).getName() << endl;
					cout << "Available from: " << tmpRentsVec.at(i).getDataInicio();
					cout << "  To: " << tmpRentsVec.at(i).getDataFim() << endl;
					cout << "Has Kitchen: " << tmpRentsVec.at(i).getKitchen() << endl;
					cout << "Has Living Room: " << tmpRentsVec.at(i).getLivingRoom() << endl;
					cout << "Has Suite: " << tmpRentsVec.at(i).getSuite() << endl;
					cout << "Price per night: " << tmpRentsVec.at(i).getPrice() << endl;
					cout << "Capacity: " << tmpRentsVec.at(i).getNumPeople() << endl << endl;
					counter++;
					v.push_back(i);

				}
				else {
					u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
					cout << "Type of accommodation: " << tmpRentsVec.at(i).getTypeRent() << endl;
					cout << "Name: " << tmpRentsVec.at(i).getName() << endl;
					cout << "Available from: " << tmpRentsVec.at(i).getDataInicio();
					cout << "  To: " << tmpRentsVec.at(i).getDataFim() << endl;
					cout << "Price per night: " << tmpRentsVec.at(i).getPrice() << endl;
					cout << "Capacity: " << tmpRentsVec.at(i).getNumPeople() << endl << endl;
					counter++;
					v.push_back(i);

				}
			}
		}

		if (counter == 1) {
			u1.setColor(12); cerr << "  There are no rents available between the dates specified.\n  Returning to the menu."; u1.setColor(15);
			Sleep(2000);
			return;

		}

		cout << "Insert the option's number: ";
		cin >> option;

		xPrice = tmpRentsVec[v[option - 1]].getPrice();

		if (cin.eof()) {
			u1.cancelMessage();
			corpMenu.UsersMenu();
		}

		if (cin.fail()) {
			u1.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u1.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.cinClear();
			u1.clearScreen();
			continue;
		}
		else {
			u1.cinClear();
			isIn = false;
		}
	}

	isIn = true;

	while (isIn) {

		Date date1 = Date(dateB);
		Date date2 = Date(dateE);


		if (!(rentsVec[v[option - 1]].getTypeRent() == "Hotel")) {
			cout << "\nNumber of people: ";
			cin >> n_people;

			if (cin.eof()) {
				u1.cancelMessage();
				corpMenu.UsersMenu();
			}

			if (cin.fail()) {
				u1.setColor(12); cerr << endl << "  ERROR: Input is not an integer."; u1.setColor(15);
				Sleep(1500);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.cinClear();
				u1.clearScreen();
				continue;
			}

			for (int index = 0; index < tmpRentsVec.size(); index++) {
				if (n_people > rentsVec.at(index).getNumPeople()) {
					u1.setColor(12); cerr << endl << "  ERROR: The value you inserted exceeds the room's maximum capacity."; u1.setColor(15);
					Sleep(1500);
					cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
					Sleep(1500);
					u1.cinClear();
					continue;
				}
				else {
					cin.clear();
					isIn = false;
				}
			}
		}

		isIn = false;
	}
	Date date1 = Date(dateB);
	Date date2 = Date(dateE);
	int nif;
	isIn = true;

	float totalPrice = xPrice*(date2.minus(date1));
	u1.setColor(14); cout << "/nThis reservation will be a total of " << totalPrice << "�."; u1.setColor(15);
	Sleep(2000);

	while (isIn) {
		if (Corporation::instance()->username == "")
		{
			cout << "\nNIF: ";
			cin >> nif;

			if (cin.eof()) {
				u1.cancelMessage();
				corpMenu.UsersMenu();
			}
			if (cin.fail())
			{
				cout << "\nInvalid input. Retrying last step.\n";
				continue;
			}
		}
		else
		{
			for (int l = 0; l < usersVec.size(); l++)
			{
				if (usersVec[l].getUsername() == Corporation::instance()->username)
					nif = usersVec[l].getNif();
			}

		}
		isIn = false;

	}

	//ALTERAR O CONSTRUTOR DE RENTS
	rentsVec[v[option - 1]].setReservation(Reservation(nif, totalPrice, date1, date2));
	createPriorityQueueFromRents();
	createHashUsersInactive();
	u1.successMessage();
	return;
}

void Corporation::cancelReservation()
{
	long nif_user;
	int counter = 1, option;
	vector<int> v;

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);

	if (Corporation::instance()->username == "")
	{
		u1.setColor(14); cout << "Only registered users can access this feature. Sign in to take full advantage of our service!";  u1.setColor(15);
		Sleep(2000);
		return;
	}

	for (size_t i = 0; i < usersVec.size(); i++)
	{
		if (usersVec[i].getUsername() == Corporation::instance()->username)
			nif_user = usersVec.at(i).getNif();
	}

	bool found = false;

	for (int j = 0; j < rentsVec.size(); j++) {
		for (int k = 0; k < rentsVec.at(j).getReservations().size(); k++) {
			if (rentsVec[j].getReservations()[k].getnif() == nif_user) {
				found = true;
			}
		}
	}

	if (found)
	{
		cout << "List of your reservations: " << endl << endl;
		for (int j = 0; j < rentsVec.size(); j++) {
			for (int k = 0; k < rentsVec.at(j).getReservations().size(); k++) {
				if (rentsVec.at(j).getReservations().at(k).getnif() == nif_user) {
					if (rentsVec.at(j).getTypeRent() == "Hotel") {
						u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
						cout << "Type of accommodation: " << rentsVec.at(j).getTypeRent() << endl;
						cout << "Name: " << rentsVec.at(j).getName() << endl;
						cout << "Available from: " << rentsVec.at(j).getDataInicio();
						cout << "  To: " << rentsVec.at(j).getDataFim() << endl;
						cout << "Room type: " << rentsVec.at(j).getType() << endl;
						cout << "Price per night: " << rentsVec.at(j).getPrice() << endl;
						cout << "Capacity: " << rentsVec.at(j).getNumPeople() << endl << endl;
						counter++;
						v.push_back(j);
					}
					else if (rentsVec.at(j).getTypeRent() == "Apartment") {
						u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
						cout << "Type of accommodation: " << rentsVec.at(j).getTypeRent() << endl;
						cout << "Name: " << rentsVec.at(j).getName() << endl;
						cout << "Available from: " << rentsVec.at(j).getDataInicio();
						cout << "  To: " << rentsVec.at(j).getDataFim() << endl;
						cout << "Has Kitchen: " << rentsVec.at(j).getKitchen() << endl;
						cout << "Has Living Room: " << rentsVec.at(j).getLivingRoom() << endl;
						cout << "Has Suite: " << rentsVec.at(j).getSuite() << endl;
						cout << "Price per night: " << rentsVec.at(j).getPrice() << endl;
						cout << "Capacity: " << rentsVec.at(j).getNumPeople() << endl << endl;
						counter++;
						v.push_back(j);

					}
					else {
						u1.setColor(14); cout << "Option " << counter << endl; u1.setColor(15);
						cout << "Type of accommodation: " << rentsVec.at(j).getTypeRent() << endl;
						cout << "Name: " << rentsVec.at(j).getName() << endl;
						cout << "Available from: " << rentsVec.at(j).getDataInicio();
						cout << "  To: " << rentsVec.at(j).getDataFim() << endl;
						cout << "Price per night: " << rentsVec.at(j).getPrice() << endl;
						cout << "Capacity: " << rentsVec.at(j).getNumPeople() << endl << endl;
						counter++;
						v.push_back(j);

					}
				}
			}
		}
	}
	else
	{
		cout << "\n  You havent made any reservations yet!" << endl;
		Sleep(2000);
		return;
	}

	u1.setColor(14); cout << "Insert the option's number: "; u1.setColor(15);
	cin >> option;


	vector<Reservation>x_vec;

	string answer;
	cout << "Do you want to confirm ? (yes|No)";
	getline(cin, answer);

	if (cin.eof()) {
		u1.cancelMessage();
		corpMenu.UsersMenu();
	}

	if (answer == "Yes" || answer == "yes")
	{


		Date x = rentsVec.at(v.at(option - 1)).getReservations().at(v.at(option - 1)).getDate1() - real_date;
		u1.setColor(14);
		if (x.getYear() != 0 || x.getMonth() > 0)
			cout << " You will receive " << rentsVec.at(v.at(option - 1)).getReservations().at(v.at(option - 1)).getPrice() << "�." << endl;
		else if (x.getDay() >= 15)
			cout << "You will receive " << rentsVec.at(v.at(option - 1)).getReservations().at(v.at(option - 1)).getPrice() / 2 << "�." << endl;
		else
			cout << "Unfortunately, we cannot refund your reservation since its beginning date is less than 15 days from now." << endl; u1.setColor(15);


		x_vec = rentsVec.at(v.at(option - 1)).getReservations();
		x_vec.erase(x_vec.begin() + v.at(option - 1));
		rentsVec.at(v.at(option - 1)).setReservationVector(x_vec);
		createPriorityQueueFromRents();

		Sleep(2000);
	}
	else
	{
		cout << "You canceled the operation." << endl;
		Sleep(2000);
		return;
	}
}

void Corporation::printUsersReservations()
{
	int counter = 1;

	u1.setColor(14); cout << "Your active reservations: \n"; u1.setColor(15);

	
	u1.setColor(11); cout << endl << left << "  " << setw(20) << "Check-in" << setw(20) << "Check-out" << setw(20) << "Price" << endl;
	cout << "  ----------------------------------------------"; u1.setColor(15);

	for (int i = 0; i < rentsVec.size(); i++) {
		for (int j = 0; j < rentsVec.at(i).getReservations().size(); j++) {
			if (nif == rentsVec.at(i).getReservations().at(j).getnif()) {
				cout << endl << left << "  "  << rentsVec.at(i).getReservations().at(j).getDate1() 
					 << "          " << rentsVec.at(i).getReservations().at(j).getDate2() 
					 << "          " << rentsVec.at(i).getReservations().at(j).getPrice();
				counter++;
			}
		}
	}

	if (counter == 1) {
		u1.setColor(14);
		cout << "\n  You do not have any active reservations at the moment.\n";
		u1.setColor(15);
	}

	u1.pressToContinueMessage();


}

bool Corporation::foundRentsFile(string rentsFile)
{
	fstream f;

	f.open(rentsFile);

	if (f.fail()) {
		f.close();
		u1.setColor(12); cerr << "\n  ERROR: " << rentsFile << " (suppliers file) could not be found!\n         Verify the directory!\n\n"; u1.setColor(15);
		return false;
	}

	f.close();

	this->rentsFile = rentsFile;
	return true;
}

string Corporation::cities() {

	string *item = new string[18];
	int counter = 1, option;
	string cinOption;
	bool run = true;

	item[0] = "Aveiro";
	item[1] = "Beja";
	item[2] = "Braga";
	item[3] = "Braganca";
	item[4] = "Castelo Branco";
	item[5] = "Coimbra";
	item[6] = "Evora";
	item[7] = "Faro";
	item[8] = "Guarda";
	item[9] = "Leiria";
	item[10] = "Lisboa";
	item[11] = "Portalegre";
	item[12] = "Porto";
	item[13] = "Santarem";
	item[14] = "Setubal";
	item[15] = "Viana do Castelo";
	item[16] = "Vila Real";
	item[17] = "Viseu";

	while (run) {
		counter = 1;
		u1.setColor(11); cout << "Cities available: \n\n"; u1.setColor(15);
		for (size_t i = 0; i < 18; i++) {
			cout << counter << " - " << item[i] << endl;
			counter++;
		}

		u1.setColor(14); cout << "\nInsert the number corresponding to the city\nin which you wish to make your rent available:  "; u1.setColor(15);
		cin >> cinOption;

		if (cin.eof()) {
			u1.cancelMessage();
			u1.clearScreen();
			corpMenu.SuppliersMenu();
		}

		if (stoi(cinOption) < 1 || stoi(cinOption) > 18) {
			u1.setColor(12); cerr << endl << "  ERROR: Input can only range from 1 to 18. "; u1.setColor(15);
			Sleep(1500);
			cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
			Sleep(1500);
			u1.clearScreen();
			continue;
		}

		for (size_t i = 0; i < cinOption.size(); i++) {
			if (!isdigit(cinOption.at(i))) {
				u1.setColor(12); cerr << endl << "  ERROR: Input can only contain digits. "; u1.setColor(15);
				Sleep(1500);
				cout << endl << "  Please try again. If you wish to cancel the operation press CTRL + Z.";
				Sleep(1500);
				u1.clearScreen();
				u1.cinClear();
				continue;
			}
		}

		option = stoi(cinOption);

		switch (option) {

		case 1:
			return item[0];
		case 2:
			return item[1];
		case 3:
			return item[2];
		case 4:
			return item[3];
		case 5:
			return item[4];
		case 6:
			return item[5];
		case 7:
			return item[6];
		case 8:
			return item[7];
		case 9:
			return item[8];
		case 10:
			return item[9];
		case 11:
			return item[10];
		case 12:
			return item[11];
		case 13:
			return item[12];
		case 14:
			return item[13];
		case 15:
			return item[14];
		case 16:
			return item[15];
		case 17:
			return item[16];
		case 18:
			return item[17];
		default:
			continue;
		}
	}
}


void Corporation::createHashUsersInactive() {

	unordered_set<Users, hstr, eqstr>temp;

#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	Date real_date = Date(day, month, year);

	for (int k = 0; k < usersVec.size(); k++) {

		int num_days = 0;
		bool have_reservations = false;

		for (int i = 0; i < rentsVec.size(); i++) {

			vector<Reservation> x = rentsVec[i].getReservations();

			for (int j = 0; j < x.size(); j++)
			{
				if (usersVec.at(k).getNif() == x.at(j).getnif()) {

					have_reservations = true;

					if (num_days != 0 && real_date.minus(x.at(j).getDate2()) > num_days)
						num_days = real_date.minus(x.at(j).getDate1());

					if (num_days == 0)
						num_days = real_date.minus(x.at(j).getDate1());
				}
			}
		}

		if (num_days > 60 || !have_reservations)
			temp.insert(usersVec.at(k));
	}

	usersInactives = temp;
}

void Corporation::displayUsersInactive() {

	Ash_Users_inactive::iterator it = usersInactives.begin();

	u1.setColor(14); cout << "The following users have been inactive for 60 days: \n\n"; u1.setColor(15);

	u1.setColor(11); cout << endl << left << "  " << setw(20) << "Username" << setw(20) << "NIF" << endl;
	cout << "  ------------------------------" << endl; u1.setColor(15);
	while (it != usersInactives.end()) {
		if (!((*it).getUsername() == "_NON REG")) {
			cout << left << "  " << setw(20) << (*it).getUsername() << setw(20) << (*it).getNif() << endl;
		}
		it++;
	}
	u1.pressToContinueMessage();
}
