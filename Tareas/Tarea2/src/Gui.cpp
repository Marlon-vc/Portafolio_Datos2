#include <iostream>

class Person {
    public:
        Person(char *name, int age);
        char *name;
        int age;
};

Person::Person(char *name, int age) {
    this->name = name;
    this->age = age;
}

class Student: public Person {
    public:
        Student(char *name, int age, int id, int courses);
        int id;
        int courses;
};

Student::Student(char *name, int age, int id, int courses):Person(name, age) {
    this->name = name;
    this->age = age;
    this->id = id;
    this->courses = courses;
}

void checkPolimorfism(Person *p1) {
    std::cout << p1->name << std::endl;
    std::cout << p1->age << std::endl;
}

int main() {
    Person *p = new Person("Paola", 21);
    Student *s = new Student("Marlon", 20, 2017217080, 5);

    checkPolimorfism(p);
    checkPolimorfism(s);
}