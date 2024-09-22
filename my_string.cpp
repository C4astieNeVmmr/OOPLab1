#include <iostream>
#include <cstring>
#include <time.h>
#pragma warning(disable : 4996)

class Cstr {
public:
    char* str;
    int length;
    char* randomString(int length) {
        if (length <= 0) {
            return nullptr;
        }
        const char setOfChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char* newString = new char[length + 1];
        for (int i = 0; i < length; i++) {
            newString[i] = setOfChars[rand() % ((sizeof(setOfChars) - 1))];
        }
        newString[length] = '\0';
        return newString;
    }
public:
    Cstr() {
        srand(time(NULL));
        int length = rand() % 21;
        this->length = length;
        this->str = randomString(length);
    }
    Cstr(const char* strAsChar) {
        this->length = strlen(strAsChar);
        this->str = new char[this->length + 1];
        strcpy(this->str, strAsChar);
    }
    Cstr(int length) {
        this->length = length;
        this->str = randomString(length);
    }
    Cstr(const Cstr& strToCopy) {//if by value(not reference), then new object in func will call copy constructor again, and copy contructors goes recursivly
        this->length = strToCopy.length;
        this->str = new char[strToCopy.length + 1];
        strcpy(this->str, strToCopy.str);
    }
    ~Cstr() {
        delete[] this->str;
    }

    Cstr operator=(Cstr strBuffer) {
        if (&strBuffer != this) {
            this->length = strBuffer.length;
            delete[] this->str;
            this->str = new char[this->length + 1];
            strcpy(this->str, strBuffer.str);
        }
        return *this;//* to dereference, and return actual object.
    }
    /*Cstr operator=(const char* strBuffer){
        if(this->str!=strBuffer){
            this->length=strlen(strBuffer);
            delete[] this->str;
            this->str = new char[this->length+1];
            strcpy(this->str,strBuffer);
        }
        return *this;//* to dereference, and return actual object.
    }*/
    char& operator[](int index) {
        return this->str[index % this->length];
    }

    Cstr operator+(Cstr strB) {
        int newLength = this->length + strB.length;
        char* newStr = new char[newLength + 1];
        strcpy(newStr, this->str);
        strcat(newStr, strB.str);
        Cstr res(newStr);
        delete[] newStr;
        return res;
    }
    Cstr operator+=(Cstr strB) {
        *this = *this + strB;
        return *this;
    }

    bool operator==(Cstr strB) const {
        if (this->length != strB.length) {
            return false;
        }
        for (int i = 0; i < length; i++) {
            if (this->str[i] != strB.str[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator>(Cstr strB) {
        int i = 0;
        for (; i < this->length, i < strB.length; i++) {
            if (this->str[i] > strB.str[i]) {
                return 1;
            }
        }
        return i == (this->length - 1);
    }
    bool operator<(Cstr strB) {
        return strB > *this;
    }

    friend std::ostream& operator<< (std::ostream& os, Cstr cstr) {
        os << cstr.str;
        return os;
    }
    friend std::istream& operator>> (std::istream& is, Cstr& cstr) {
        char buffer[100];
        is >> buffer;
        cstr = buffer;
        return is;
    }
    /*friend std::istream& operator>> (std::istream& is, Cstr& cstr){
        int k=1;
        char* buffer1=new char[8];
        char* buffer2=new char[8];
        is >> buffer1;
        is >> buffer2;
        std::cout << buffer1 << "\t\t" << buffer2;
        return is;
    }*/

    int getLength() {
        return this->length;
    }
};

int main() {
    srand(time(NULL));
    const char* toConstructor2 = "some_text_for_test123";
    Cstr str1;
    Cstr str2(toConstructor2);
    Cstr str3(10);
    Cstr str4(str2);
    std::cout << str1 << "\t" << str1.getLength() << "\n";
    std::cout << str2 << "\t" << str2.getLength() << "\n";
    std::cout << str3 << "\t" << str3.getLength() << "\n";
    std::cout << str4 << "\t" << str4.getLength() << "\n\n\n";

    Cstr temp("stringAtext"), stringA, stringB;
    stringA = temp;
    stringB = "stringBtext";
    std::cout << stringA << "\t" << stringB << "\n";

    stringA[5] = 'M';
    stringB[5] = 'N';
    std::cout << stringA << "\t" << stringB << "\n\n\n";

    temp = "stringC";
    stringA = temp + "A";
    stringB = temp + "B";
    std::cout << stringA << "\t" << stringB << "\n";
    stringA += "W";
    stringB += "W";
    std::cout << stringA << "\t" << stringB << "\n\n\n";

    stringA = "qweasd";
    stringB = "qweasd";
    std::cout << "stringA == stringB = " << (stringA == stringB) << "\n" << "stringA > stringB = " << (stringA > stringB) << "\nstringA < stringB = " << (stringA < stringB) << "\n\n";
    stringA += "A";
    std::cout << "stringA == stringB = " << (stringA == stringB) << "\n" << "stringA > stringB = " << (stringA > stringB) << "\nstringA < stringB = " << (stringA < stringB) << "\n\n";
    stringB = stringB + "B";
    std::cout << "stringA == stringB = " << (stringA == stringB) << "\n" << "stringA > stringB = " << (stringA > stringB) << "\nstringA < stringB = " << (stringA < stringB) << "\n\n\n";

    std::cin >> temp;
    std::cout << temp << "\t" << temp.getLength() << "\n";
    return 0;
}
