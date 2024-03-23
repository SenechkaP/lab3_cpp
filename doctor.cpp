#define _CRT_SECURE_NO_WARNINGS

#include "doctor.h"
#include "funcs.h"

doctor::doctor() {
}

doctor::doctor(char *fam, char *name, SpecType spec, QualType qual) {
    this->person.set_fam(fam);
    this->person.set_name(name);
    this->spec = spec;
    this->qual = qual;
}

doctor::doctor(doctor &doc) {
    this->person.set_fam(doc.person.get_fam());
    this->person.set_name(doc.person.get_name());
    this->spec = doc.spec;
    this->qual = doc.qual;
}

doctor::~doctor() {
}

bool doctor::operator==(man &other_fio) {
    if ((strcmp(this->get_fam(), other_fio.get_fam()) == 0) && (strcmp(this->get_name(), other_fio.get_name()) == 0)) {
        return true;
    } else {
        return false;
    }
}

doctor &doctor::operator=(doctor &doc) {
    if (&doc != this) {
        this->person.set_fam(doc.person.get_fam());
        this->person.set_name(doc.person.get_name());
        this->spec = doc.spec;
        this->qual = doc.qual;
    }
    return *this;
}

std::istream &operator>>(std::istream &is, doctor &doc) {
    char fam_buff[256];
    char name_buff[256];
    char spec_buff[256];
    char qual_buff[256];

    bool condition = true;

    while (condition) {
        std::cout << "Введите фамилию, имя, специальность, квалификацию нового доктора\n"
                     "специальность - цифра 1, 2 или 3\n"
                     "1 - терапевт\n"
                     "2 - кардиолог\n"
                     "3 - стоматолог\n\n"
                     "квалификация - цифра 0, 1 или 2\n"
                     "0 - высшая\n"
                     "1 - первая\n"
                     "2 - вторая\n";
        is >> fam_buff >> name_buff >> spec_buff >> qual_buff;

        long spec = check_int(spec_buff);
        long qual = check_int(qual_buff);

        std::cout << std::endl;

        if (!(check_str(fam_buff) && check_str(name_buff) && spec >= 1 && spec <= 3 && qual >= 0 && qual <= 2)) {
            std::cout << "Введите данные корректно\n\n";
        } else {
            SpecType new_spec = static_cast<SpecType>(spec);
            QualType new_qual = static_cast<QualType>(qual);

            doc.set_fam(fam_buff);
            doc.set_name(name_buff);
            doc.set_spec(new_spec);
            doc.set_qual(new_qual);
            condition = false;
        }
    }
    return is;
}

char *doctor::get_fam() {
    return this->person.get_fam();
}

void doctor::set_fam(char *fam) {
    this->person.set_fam(fam);
}

char *doctor::get_name() {
    return this->person.get_name();
}

void doctor::set_name(char *name) {
    this->person.set_name(name);
}

SpecType doctor::get_enum_spec() {
    return this->spec;
}

const char *doctor::get_spec() {
    return specs[this->spec - 1];
}

void doctor::set_spec(SpecType spec) {
    this->spec = spec;
}

QualType doctor::get_enum_qual() {
    return this->qual;
}

const char *doctor::get_qual() {
    return quals[this->qual];
}

void doctor::set_qual(QualType qual) {
    this->qual = qual;
}

int doctor::get_count() {
    return count;
}

void doctor::count_up() {
    count += 1;
}

int doctor::count = 0;