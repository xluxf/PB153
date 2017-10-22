// FI MUNI - PB153
// Filip Lux
// implementing hash function

#include "hashTables.h"

#define TESTED_TYPE float



template <typename T, typename INPUT_TYPE>
void manualTest () {

	T table;

	std::string cmd;
	INPUT_TYPE number;

	while (true) {

		std::cout << ">> ";

		std::cin >> cmd;

		if (cmd == "insert" || cmd == "i") {
			std::cin >> number;
			table.insert(number);
			table.print();
		}

		else if (cmd == "erase" || cmd == "e") {
			std::cin >> number;
			table.erase(number);
			table.print();
		}

		else if ( cmd == "find" || cmd == "f") {
			std::cin >> number;
			if (table.find(number))
				std::cout << number << " is in table.\n";
			else
				std::cout << number << " is not there.\n";
		}

		else if ( cmd == "print" || cmd == "p") {
			table.print();
		}

		else if (cmd == "exit") {
			break;
		}
		else {
			std::cout << "Wrong argument. Type insert | erase | find | print | exit \n";
		}
	}
}

template <typename T, typename I>
void automaticTest () {

	T table;

	table.printName();

	srand ( time(NULL) );

	long long i;
	clock_t t;
	t = clock();

	for (i = 0; i < TEST_INSERT_ITER; ++i) {
		I number = rand();
		table.insert(number);
	}
	t = clock() - t;


	std::cout << float(t)/CLOCKS_PER_SEC << " s \n";

}

void benchmark () {

	std::cout << "Benchmark of hash tables\n\n";

	std::cout << "tested type: " << "float" << "\n";
	std::cout << "number of inserted objects: " << TEST_INSERT_ITER << "\n\n";


	automaticTest < HashTableS<TESTED_TYPE> , TESTED_TYPE > ();
	automaticTest < HashTableUS<TESTED_TYPE> , TESTED_TYPE > ();
	automaticTest < HashTableLL<TESTED_TYPE> , TESTED_TYPE > ();
	automaticTest < HashTableLPR<TESTED_TYPE> , TESTED_TYPE > ();


}

int main () {

	//benchmark();
	manualTest < HashTableUS<TESTED_TYPE> , TESTED_TYPE>();
	//manualTest < HashTableLPR<TESTED_TYPE> , TESTED_TYPE>();

	return 0;
}