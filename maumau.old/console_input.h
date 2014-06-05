#ifndef CONSOLEINPUT_H_
#define CONSOLEINPUT_H_

#include <string>
#include <vector>



long read_long(int min, int max);
long read_long();
double read_double();
double read_double(double min, double max);
int read_int(int min, int max);
int read_int();
void read_string(string& input);
void press_any_key();
int request_menu(const vector<string> entries, int menu_size, string request);

#endif /* CONSOLEINPUT_H_ */
