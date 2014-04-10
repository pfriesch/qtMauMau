#include "console_input.h"
#include <cfloat>
#include <climits>
#include <iostream>
#include <string>

/**
 * Returns the read long value form the standard input. If the read value is not
 * between the given barriers the user is asked to repeat his input.
 * @param min the minimal long value the user can enter.
 * @param max the maximal long value the user can enter.
 * @return the read long value form the standard input.
 */
long read_long(long min, long max) {
	if (max < min) {
		long temp = max;
		max = min;
		min = temp;
	}
	long input = 0;
	bool correct_input = false;
	cin.clear();
	cin.unsetf(cin.skipws);
	do {
		cin >> input;
		correct_input = cin.good() && min <= input && input <= max;
		cin.clear();
		cin.ignore(static_cast<streamsize>(LONG_MAX), '\n');
		if (!correct_input) {
			cout << "Bitte geben sie eine Zahl zwischen " << min << " und "
					<< max << " ein." << endl;
		}
	} while (!correct_input);
	cin.setf(cin.skipws);
	return input;
}

/**
 * Returns the read long value form the standard input.
 * @param min the minimal long value the user can enter.
 * @param max the maximal long value the user can enter.
 * @return the read long value form the standard input.
 */
long read_long() {
	return read_long(LONG_MIN, LONG_MAX);
}

/**
 * Returns the read double value form the standard input.
 * @param min the minimal double value the user can enter.
 * @param max the maximal double value the user can enter.
 * @return the read double value form the standard input.
 */
double read_double() {
	return static_cast<double>(read_long(static_cast<long>(DBL_MIN),
			static_cast<long>(DBL_MAX)));
}

/**
 * Returns the read double value form the standard input. If the read value is not
 * between the given barriers the user is asked to repeat his input.
 * @param min the minimal double value the user can enter.
 * @param max the maximal double value the user can enter.
 * @return the read double value form the standard input.
 */
double read_double(double min, double max) {
	return static_cast<double>(read_long(static_cast<long>(min),
			static_cast<long>(max)));
}

/**
 * Returns the read integer value form the standard input. If the read value is not
 * between the given barriers the user is asked to repeat his input.
 * @param min the minimal integer value the user can enter.
 * @param max the maximal integer value the user can enter.
 * @return the read integer value form the standard input.
 */
int read_int(int min, int max) {
	return static_cast<int>(read_long(static_cast<long>(min),
			static_cast<long>(max)));
}

/**
 * Returns the read integer value form the standard input.
 * @param min the minimal integer value the user can enter.
 * @param max the maximal integer value the user can enter.
 * @return the read integer value form the standard input.
 */
int read_int() {
	return static_cast<int>(read_long(static_cast<long>(INT_MIN),
			static_cast<long>(INT_MAX)));
}

/**
 * Writes the read string form the standard input to the given string.
 * @param input the string the read sting is written to.
 */
void read_string(string& input) {
	bool correct_input = false;
	cin.clear();
	cin.unsetf(cin.skipws);
	do {
		cin >> input;
		correct_input = cin.good();
		cin.clear();
		cin.ignore(static_cast<streamsize>(LONG_MAX), '\n');
		if (correct_input != true) {
			cout << "Die Eingabe war ungueltig!" << endl;
		}
	} while (correct_input != 1);
	cin.setf(cin.skipws);
}

/**
 * Asks the user to press any key.
 */
void press_any_key() {
	cout << "Press any key to continue...";
	cin.ignore();
	cin.get();
}

/**
 * Writes a menu of the given entries and asks the user with the given request to choose one.
 * @param entries a vector of entries, used to build the menu from.
 * @param menu_size the size of the menu.
 * @param request the request string.
 * @return the number of the chosen menu entry.
 */
int request_menu(const vector<string> entries, int menu_size, string request) {
	cout <<  request << endl;
	for (int i = 0; i < menu_size; ++i) {
		cout << "[" << i << "]\t" << entries[i] << endl;
	}
	cout << endl;
	return read_int(0, menu_size - 1);
}

