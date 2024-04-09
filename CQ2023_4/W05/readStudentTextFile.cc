// #include"test.hpp"
#include<iostream>
#include<fstream>

using namespace std;

struct Student {
    char Name[50];
    char ID[9];
};

// Overloading << operator to output a Student struct
ostream& operator<<(ostream& out, const Student& s) {
    out << s.ID << " " << s.Name;
    return out;
}

// A simpler approach, equivalent to above approach.
void printStudent(const Student& s) {
    cout << s.ID << " " << s.Name;
}

// Read a student from fileName
Student* readStudentListFromTextFile(const char* fileName, 
                                     int& studentListSize) {
    ifstream inputFile(fileName, ios::in);

    studentListSize = 1;

    // Using C++ "new" keyword
    // Student* studentList = new Student[studentListSize];

    // Using C malloc function
    Student* studentList = (Student*)malloc(sizeof(Student));

    while (!inputFile.eof()) {
        Student studentBuffer;
        inputFile.getline(studentBuffer.Name, 50);
        inputFile.getline(studentBuffer.ID, 9);

        studentList[studentListSize - 1] = studentBuffer;

        // Skip immediately if reached EOF, to avoid reallocating a spare slot.
        if (inputFile.eof()) {
            break;
        }

        studentListSize++;

        // Using C++
        // Student* newStudentList = new Student[studentListSize];
        // for (int i = 0; i < studentListSize; ++i) {
        //     newStudentList[i] = studentList[i];
        // }

        // delete[] studentList;
        // studentList = newStudentList;

        // Using C-way realloc
        studentList = (Student*)realloc(studentList, sizeof(Student) * studentListSize);
    }

    inputFile.close();

    return studentList;
}

int main() {
    int studentListSize;
    Student* studentList = readStudentListFromTextFile(
        "input.txt", 
        studentListSize
    );

    for (int i = 0; i < studentListSize; ++i) {
        cout << studentList[i] << "\n";
    }

    // Use delete, if you use C++ allocation
    // delete[] studentList;

    // Use free, if you use C allocation
    free(studentList);
    return 0;
}
