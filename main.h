#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <clocale>
#include <cctype>
#include "doctor.h"

void add_doctor(doctor *&, int &, int &);

void print_doctors(doctor *, int);

doctor *find_doctor(doctor *, int);

doctor *find_spec(doctor *, int, int &);

doctor *find_qual(doctor *, int, int &);

void processFile(char *, doctor *&, int &, int &);

void save(char *file_name, doctor *all_doctors, int n);