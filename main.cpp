#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include "funcs.h"

using namespace std;

void add_doctor(doctor *&all_doctors, int &n, int &size) {
    if (n + 1 > size) {
        doctor *temp = new doctor[(n * 3) / 2 + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = all_doctors[i];
        }
        delete[] all_doctors;
        all_doctors = temp;
        size = n * 3 / 2 + 1;
    }

    cin >> all_doctors[n];

    doctor::count_up();
    n++;
    cout << "Доктор добавлен\n";
}

void print_doctors(doctor *all_doctors, int n) {
    if (n == 0) {
        cout << "Нет записей о докторах в базе\n";
        return;
    }
    cout << left << setw(30) << "Фамилия" << setw(30) << "Имя" << setw(30) << "Специальность" << setw(30)
         << "Квалификация" << endl << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(30) << all_doctors[i].get_fam() << setw(30) << all_doctors[i].get_name() << setw(30)
             << all_doctors[i].get_spec() << setw(30) << all_doctors[i].get_qual() << endl;
    }
}

void bubbleSort(doctor *&all_doctors, int &n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(all_doctors[j].get_fam(), all_doctors[j + 1].get_fam()) > 0) {
                doctor temp = all_doctors[j];
                all_doctors[j] = all_doctors[j + 1];
                all_doctors[j + 1] = temp;
            }
        }
    }
}

doctor *find_doctor(doctor *all_doctors, int n) {
    man initials;
    cin >> initials;

    for (int i = 0; i < n; i++) {
        if (all_doctors[i] == initials) {
            return &all_doctors[i];
        }
    }
    return nullptr;
}

doctor *find_spec(doctor *all_doctors, int n, int &num_founded) {
    char spec_buff[256];
    bool condition = true;

    doctor *found_doctors = new doctor[n];

    while (condition) {
        cout << "Введите специальность доктора\n"
                "специальность - цифра 1, 2 или 3\n"
                "1 - терапевт\n"
                "2 - кардиолог\n"
                "3 - стоматолог\n";
        cin >> spec_buff;
        long spec = check_int(spec_buff);
        if (spec == -1) {
            cout << "Специальность - целое число!\n\n";
            continue;
        }
        cout << "\n";

        switch (spec) {
            case 1:
            case 2:
            case 3:
                for (int i = 0; i < n; i++) {
                    if (spec == all_doctors[i].get_enum_spec()) {
                        found_doctors[num_founded] = all_doctors[i];
                        num_founded += 1;
                    }
                }
                condition = false;
                break;
            default:
                cout << "Нет такой специальности\n\n";
                break;
        }
    }
    return found_doctors;
}

doctor *find_qual(doctor *all_doctors, int n, int &num_founded) {
    char qual_buff[256];
    bool condition = true;

    doctor *found_doctors = new doctor[n];

    while (condition) {
        cout << "Введите квалификацию доктора\n"
                "квалификация - цифра 0, 1 или 2\n"
                "0 - высшая\n"
                "1 - первая\n"
                "2 - вторая\n";
        cin >> qual_buff;
        long qual = check_int(qual_buff);
        if (qual == -1) {
            cout << "Квалификация - целое число!\n\n";
            continue;
        }
        cout << "\n";

        switch (qual) {
            case 0:
            case 1:
            case 2:
                for (int i = 0; i < n; i++) {
                    if (qual == all_doctors[i].get_enum_qual()) {
                        found_doctors[num_founded] = all_doctors[i];
                        num_founded += 1;
                    }
                }
                condition = false;
                break;
            default:
                cout << "Нет такой квалификации\n\n";
                break;
        }
    }
    return found_doctors;
}

void processFile(char *file_name, doctor *&all_doctors, int &total_doctors, int &size) {
    ifstream file(file_name);

    if (!file.is_open()) {
        cout << "Невозможно открыть файл" << endl;
        return;
    }

    int temp_total = 0;
    char line[256];
    char fam_buff[256];
    char name_buff[256];
    int spec_buff;
    int qual_buff;

    if (file.getline(line, sizeof(line))) {
        stringstream ss(line);
        ss >> temp_total;
    } else {
        cout << "Файл пустой" << endl;
        return;
    }

    doctor *temp_doctors = new doctor[temp_total];

    int index = 0;
    while (file.getline(line, sizeof(line)) && index < temp_total) {
        stringstream ss(line);
        ss >> fam_buff >> name_buff >> spec_buff >> qual_buff;

        SpecType new_spec = static_cast<SpecType>(spec_buff);
        QualType new_qual = static_cast<QualType>(qual_buff);

        temp_doctors[index].set_fam(fam_buff);
        temp_doctors[index].set_name(name_buff);
        temp_doctors[index].set_spec(new_spec);
        temp_doctors[index].set_qual(new_qual);
        doctor::count_up();

        index++;
    }

    file.close();

    all_doctors = temp_doctors;
    total_doctors = temp_total;
    size = temp_total;
}

void save(char *file_name, doctor *all_doctors, int n) {
    ofstream file(file_name);

    if (!file.is_open()) {
        cout << "Невозможно открыть файл" << endl;
        return;
    }

    file << n << endl;

    for (int i = 0; i < n; i++) {
        file << all_doctors[i].get_fam() << " " << all_doctors[i].get_name() << " " << all_doctors[i].get_enum_spec()
             << " " << all_doctors[i].get_enum_qual() << endl;
    }

    file.close();
    cout << "Данные сохранены" << endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    doctor *all_doctors = nullptr;

    int total_doctors = 0;
    int total_size = 0;
    char file_name[256] = "doctors.txt";

    processFile(file_name, all_doctors, total_doctors, total_size);
    cout << "Кол-во записей в базе: ";
    cout << doctor::get_count() << endl << endl;

    bool condition = true;
    while (condition) {
        cout << "Добавить нового доктора................1\n"
                "Вывести информацию о всех докторах.....2\n"
                "Отсортировать докторов по фамилии......3\n"
                "Найти доктора по фамилии и имени.......4\n"
                "Найти доктора по специальности.........5\n"
                "Найти доктора по квалификации..........6\n"
                "Завершить программу....................7\n\n"
                "Введите номер функции: ";
        char input[256];
        long command;

        cin >> input;
        command = check_int(input);

        if (command == -1) {
            cout << "Ошибка. Введите целое число.\n\n";
            continue;
        }
        cout << endl;

        switch (command) {
            case 1:
                add_doctor(all_doctors, total_doctors, total_size);
                cout << endl;
                break;
            case 2:
                print_doctors(all_doctors, total_doctors);
                cout << endl;
                break;
            case 3:
                bubbleSort(all_doctors, total_doctors);
                cout << "Данные отсортированы\n\n";
                break;
            case 4: {
                doctor *founded_doc = find_doctor(all_doctors, total_doctors);
                if (!founded_doc) {
                    cout << "Доктор не найден\n\n";
                } else {
                    cout << "Доктор найден:\n\n";
                    cout << founded_doc->get_fam() << " " << founded_doc->get_name() << ", " << founded_doc->get_spec()
                         << ", " << founded_doc->get_qual() << " квалификация" << endl << endl;
                }
                break;
            }
            case 5: {
                int num_founded = 0;
                doctor *founded = find_spec(all_doctors, total_doctors, num_founded);
                print_doctors(founded, num_founded);
                cout << endl;
                break;
            }
            case 6: {
                int num_founded = 0;
                doctor *founded = find_qual(all_doctors, total_doctors, num_founded);
                print_doctors(founded, num_founded);
                cout << endl;
                break;
            }
            case 7:
                condition = false;
                save(file_name, all_doctors, total_doctors);
                break;
            default:
                cout << "Нет такой команды, введите команду от 1 до 7\n\n";
                break;
        }
    }

    delete[] all_doctors;

    return 0;
}