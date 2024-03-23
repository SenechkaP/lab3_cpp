#define _CRT_SECURE_NO_WARNINGS

#include "man.h"
#include "funcs.h"

man::man() {
    this->fam = nullptr;
    this->name = nullptr;
}

man::man(char *fam, char *name) {
    this->fam = new char[strlen(fam) + 1];
    this->name = new char[strlen(name) + 1];
    strcpy(this->fam, fam);
    strcpy(this->name, name);
}

man::man(man &other_fio) {
    this->fam = other_fio.get_fam();
    this->name = other_fio.get_name();
}

man::~man() {
    delete[]fam;
    delete[]name;
//    std::cout << "deleted";
}

man &man::operator=(man &other_fio) {
    if (&other_fio != this) {
        this->set_fam(other_fio.get_fam());
        this->set_name(other_fio.get_name());
    }
    return *this;
}

std::istream &operator>>(std::istream &is, man &fio) {
    char fam_buff[256];
    char name_buff[256];

    std::cout << "Введите фамилию, имя:\n";
    std::cin >> fam_buff >> name_buff;

    while (!(check_str(fam_buff), check_str(name_buff))) {
        std::cout <<"Введите фамилию и имя корректно\n\n";
        std::cin >> fam_buff >> name_buff;
    }

    fio.set_fam(fam_buff);
    fio.set_name(name_buff);

    return is;
}

char *man::get_fam() {
    char *fam_return = new char[strlen(this->fam) + 1];
    strcpy(fam_return, this->fam);
    return fam_return;
}

void man::set_fam(char *fam) {
    if (this->fam) {
        delete[]this->fam;
    }
    this->fam = new char[strlen(fam) + 1];
    strcpy(this->fam, fam);
}

char *man::get_name() {
    char *name_return = new char[strlen(this->name) + 1];
    strcpy(name_return, this->name);
    return name_return;
}

void man::set_name(char *name) {
    if (this->name) {
        delete[]this->name;
    }
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}