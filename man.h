#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

class man {
private:
    char* fam;
    char* name;
public:
    man();

    man(char*, char*);

    man(man&);

    ~man();

    man& operator=(man&);

    friend std::istream &operator>>(std::istream &, man &);

    char* get_fam();

    void set_fam(char*);

    char* get_name();

    void set_name(char*);
};
