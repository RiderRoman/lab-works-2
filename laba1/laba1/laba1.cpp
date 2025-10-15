#include <iostream>
#include <string>
#include <limits>
#include <thread>
#include <chrono>
#include <iomanip>
#include <windows.h>
#include <sstream>
#undef max
using namespace std;

int menu52forall();
void problem();
string perevodv2_int(int num) {
    string str = "";
    int nuli, save = num;
    if (num < 0) {
        num = -2147483648 - num;
        num = -num;
    }
    while (num != 0) {
        if (num % 2 == 1) str = '1' + str;
        else str = '0' + str;
        num = num >> 1;
    }
    if (str.length() < (sizeof(int) * 8) - 1) {
        nuli = (sizeof(int) * 8 - 1) - str.length();
        while (nuli != 0) {
            str = '0' + str;
            nuli--;
        }
    }
    if (save < 0) str = '1' + str;
    else str = '0' + str;
    str.insert(1, " "); str.insert(9, " "); str.insert(18, " "); str.insert(27, " ");
    cout << "\x1b[36m" << str << "\x1b[0m" << endl;
    cout << "^ ЗНАК\n";
    return "";
}

string perevodv2_float(float num) {
    float save2 = num;
    if (num < 0) num = -num; // если число отрицательное
    long long a = static_cast<long long>(num); // целая часть числа
    long long save = a;
    float b = num - a; // дробная часть
    int nuli = 0, nuli2 = 0, max_bit = 23, count_bit = 0;
    string str = "", str2 = ""; // строчки для целой и дробной части
    if (a == 0) str = '0'; // если целая часть равна 0
     
    while (a != 0) { // процесс перевода целой части
        if (a % 2 == 1) str = '1' + str;
        else str = '0' + str;
        a = a >> 1;
    }

    while (b > 0 && count_bit < max_bit) { // процесс перевода дробной части
        b = b * 2;
        if (b >= 1) {
            str2 += '1';
            b--; 
        }
        else {
            str2 += '0';
        }
        count_bit++;
    }
    if (str2.length() < 23) { //дополнительные нули для дробной части
        nuli = 23 - str2.length();
        while (nuli != 0) {
            str2 += '0';
            nuli--;
        }
    }

    string res = str + '.' + str2; // соединяем две части
    int point = res.find('.'), exponenta = 0, odin = res.find('1'), count = 0, count2 = 0;

    if (save != 0) {
        while (res[1] != '.') { // алгоритм для нахождения экспоненты. Пока 1 индекс дв. записи не будет точкой, двигаем точку влево (при условии что целая часть не равна 0)
            swap(res[point], res[point - 1]);
            point = res.find('.');
            exponenta++;
            count2++;
        }
        while (count2 != 0) { // удаляем лишние нули
            res.pop_back();
            count2--;
        }
    }
    if (save == 0) { // если целая часть равна 0, то точку двигаем вправо до первой единицы.
        while (res[odin] != '.') {
            swap(res[point], res[point + 1]);
            point = res.find('.');
            exponenta--;
            count++;
        }
        res.erase(0, count);
        while (count != 0) {
            res = res + '0';
            count--;
        }
    }
    exponenta = exponenta + 127; // экспонента
    string strex = ""; // строка для экспоненты
    while (exponenta > 0) { // перевод экспоненты в двоичную запись
        if (exponenta % 2 == 1) strex = '1' + strex;
        else strex = '0' + strex;
        exponenta /= 2;
    }

    res.erase(0, 1); // убираем цифру перед точкой
    res = strex + res; // соединяем экспоненту с мантиссой
    point = res.find('.');
    if (point < 8) { // доп нули для экспоненты
        while (point != 8) {
            res = '0' + res;
            point = res.find('.');
        }
    }
    if (save2 < 0) res = '1' + res;  // добавляем бит знака
    else res = '0' + res;

    if (res.length() > 33) {
        while (res.length() != 33) {
            res.pop_back();
        }
    }
    res.insert(1, " "); res.insert(18, " "); res.insert(27, " ");
    cout << "Результат: " << "\x1b[32m" << res << "\x1b[0m" << endl;
    cout << setw(13) << "(S)" << "(---E--)" << " " << "(" << setfill('-') << setw(12) << "M" << setw(12) << ")" << setfill(' ') << endl;
    return "";
}

string perevodv2_double(double num) {
    double save2 = num;
    if (num < 0) num = -num; // если число отрицательное
    long long a = static_cast<long long>(num); // целая часть числа
    long long save = a;
    double b = num - a; // дробная часть
    int nuli = 0, nuli2 = 0, max_bit = 52, bit_count = 0;;
    string str = "", str2 = ""; // строчки для целой и дробной части
    if (a == 0) str = '0'; // если целая часть равна 0 
    while (a != 0) { // процесс перевода целой части
        if (a % 2 == 1) str = '1' + str;
        else str = '0' + str;
        a = a >> 1;
    }

    while (b > 0 && bit_count < max_bit) { // процесс перевода дробной части
        b = b * 2;
        if (b >= 1) {
            str2 += '1';
            b--;
        }
        else {
            str2 += '0';
        }
        bit_count++;
    }
    if (str2.length() < 52) { //дополнительные нули для дробной части
        nuli = 52 - str2.length();
        while (nuli != 0) {
            str2 += '0';
            nuli--;
        }
    }
    
    string res = str + '.' + str2; // соединяем две части
    int point = res.find('.'), exponenta = 0, odin = res.find('1'), count = 0, count2 = 0;

    if (save != 0) {
        while (res[1] != '.') { // алгоритм для нахождения экспоненты. Пока 1 индекс дв. записи не будет точкой, двигаем точку влево (при условии что целая часть не равна 0)
            swap(res[point], res[point - 1]);
            point = res.find('.');
            exponenta++;
            count2++;
        }
        while (count2 != 0) { // удаляем лишние нули
            res.pop_back();
            count2--;
        }
    }
    if (save == 0) { // если целая часть равна 0, то точку двигаем вправо до первой единицы.
        while (res[odin] != '.') {
            swap(res[point], res[point + 1]);
            point = res.find('.');
            exponenta--;
            count++;
        }
        res.erase(0, count);
        while (count != 0) {
            res = res + '0';
            count--;
        }
    }
    exponenta = exponenta + 1023; // экспонента
    string strex = ""; // строка для экспоненты
    while (exponenta > 0) { // перевод экспоненты в двоичную запись
        if (exponenta % 2 == 1) strex = '1' + strex;
        else strex = '0' + strex;
        exponenta /= 2;
    }


    res.erase(0, 1); // убираем цифру перед точкой
    res = strex + res; // соединяем экспоненту с мантиссой
    point = res.find('.');
    if (point < 11) { // доп нули для экспоненты
        while (point != 11) {
            res = '0' + res;
            point = res.find('.');
        }
    }
    if (save2 < 0) { // добавляем бит знака
        res = '1' + res;
    }
    else {
        res = '0' + res;
    }
    if (res.length() > 65) {
        while (res.length() != 65) {
            res.pop_back();
        }
    }
    res.insert(1, " "); res.insert(5, " "); res.insert(19, " "); res.insert(28, " "); res.insert(37, " "); res.insert(46, " "); res.insert(55, " "); res.insert(64, " ");

    cout << "Результат: " << "\x1b[32m" << res << "\x1b[0m" << endl;
    cout << setw(13) << "(S)" << "(-----E----)" << " " << "(" << setfill('-') << setw(29) << "M" << setw(28) << ")" << setfill(' ') << endl;
    return "";
}

//=======================================================================================================================================================
void perevod_bit_double(double num) {
    uint64_t bits = *reinterpret_cast<uint64_t*>(&num); // double становится интом, но все биты от double сохранены. Нужно чтобы потом делать замену бита
    perevodv2_double(num);
    if (menu52forall() == 1) {
        int pos;
        bool bit_val;
        cout << "Введите позицию бита (0-63): ";
        cin >> pos;
        cout << "Введите значение бита (0-1): ";
        cin >> bit_val;

        // замена бита
        if (bit_val) bits |= (uint64_t(1) << pos);
        else bits &= ~(uint64_t(1) << pos);

        string otvet;
        double new_num = *reinterpret_cast<double*>(&bits); // снова double
        cout << "Новое число: " << new_num << endl;
        perevodv2_double(new_num);
        return;
    }  
}

void perevod_bit_float(float num) {
    uint32_t bits = *reinterpret_cast<uint32_t*>(&num);
    perevodv2_float(num);
    if (menu52forall() == 1) {
        int pos;
        bool bit_val;
        cout << "Введите позицию бита (0-31): ";
        cin >> pos;
        cout << "Введите значение бита (0-1): ";
        cin >> bit_val;
        // замена бита
        if (bit_val) bits |= (uint64_t(1) << pos);
        else bits &= ~(uint64_t(1) << pos);

        string otvet;
        float new_num = *reinterpret_cast<float*>(&bits);

        cout << "Новое число: " << new_num << endl;
        perevodv2_float(new_num);
        return;
    }
}

int perevod_bit_int(int num) {
    perevodv2_int(num);
    int new_num, pos;
    bool bit;
    if (menu52forall() == 1) {
        cout << "Введите позицию бита (0-31) ";
        cin >> pos;
        cout << "Введите значение бита (0-1) ";
        cin >> bit;
        if (bit) {
            int mask = 1 << pos;
            new_num = num | mask;
            perevodv2_int(new_num);
            return num | mask;
        }
        else {
            int mask = ~(1 << pos);
            new_num = num & mask;
            perevodv2_int(new_num);
            return num & mask;
        }
    }
    else {
        return 0;
    }
}

void problem() {
    cout << "что-то пошло не так\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    this_thread::sleep_for(chrono::milliseconds(600)); // пауза перед чисткой экрана
    system("cls");
    return;
}
int menu52forall() {
    int select = 0;
    cout << "Выберите действие" << endl
        << "1. Изменить двоичное представление" << endl
        << "2." << "\x1b[32m" << " Готово" << "\x1b[0m" << endl;
    if (!(cin >> select)) {
        problem();
        return 0;
    }
    while (select != 2) {
        switch (select) {
        case 1:
            return 1;
            break;
        case 2:
            system("cls");
            return 0;
        default:
            problem();
            return 0;
        }
    }
}

void menu51() { //case 5
    int select = 0, res;
    long double select_num_double;
    float select_num_float;
    long long select_num_int;    
    while (select != 9) {
        cout << setw(12) << "\x1b[35m" << "Вы выбрали пункт 5" << "\x1b[0m" << endl;
        cout << setw(20) << "Типы данных" << endl;
        cout << "1. int " << endl                        
            << "2. float " << endl
            << "3. double " << endl
            << "4." << "\x1b[31m" << " Назад " << "\x1b[0m" << endl;
        cout << "Выберите тип данных: ";
        cin >> select;
        switch (select) {
        case 1:
            system("cls");
            cout << "Введите целое число: ";
            cin >> select_num_int;
            if (select_num_int <= 2147483647 && select_num_int >= -2147483647) res = perevod_bit_int(select_num_int);
            else problem();
            cout << "Новое число: " << res << endl;
            break;
        case 2:
            system("cls");
            cout << "Введите число: ";
            if (!(cin >> select_num_float)) problem();
            perevod_bit_float(select_num_float);
            break;
        case 3:
            system("cls");   
            cout << "Введите число: ";
            if (!(cin >> select_num_double)) problem();
            perevod_bit_double(select_num_double);            
            break;     
        case 4:
            system("cls");
            return;
        default:
            problem();
        }
    }
}

void Menu12() { //case1 
    int select2 = 0;
    while (select2 != 10) {
        cout << setfill(' ') << setw(20) << "Типы данных" << endl;
        cout << "1. int " << endl
            << "2. short int " << endl
            << "3. long int " << endl
            << "4. float " << endl
            << "5. double " << endl
            << "6. long double " << endl
            << "7. char " << endl
            << "8. bool " << endl
            << "9. Все сразу " << endl
            << "10." << "\x1b[31m" << " Назад " << "\x1b[0m" << endl << endl;
        cout << "Выберите тип данных.\nПрограмма выведет сколько байтов в памяти занимает тот или иной тип.";
        cin >> select2;
        switch (select2) {
        case 1:
            system("cls");
            cout << "\x1b[31m" << "int: " << sizeof(int) << " байта" << "\x1b[0m" << endl << endl;
            break;
        case 2:
            system("cls");
            cout << "\x1b[32m" << "short int: " << sizeof(short int) << " байта" << "\x1b[0m" << endl << endl;
            break;
        case 3:
            system("cls");
            cout << "\x1b[33m" << "long int: " << sizeof(long int) << " байта" << "\x1b[0m" << endl << endl;
            break;
        case 4:
            system("cls");
            cout << "\x1b[34m" << "float: " << sizeof(float) << " байта" << "\x1b[0m" << endl << endl;
            break;
        case 5:
            system("cls");
            cout << "\x1b[35m" << "double: " << sizeof(double) << " байт" << "\x1b[0m" << endl << endl;
            break;
        case 6:
            system("cls");
            cout << "\x1b[36m" << "long double: " << sizeof(long double) << " байт" << "\x1b[0m" << endl << endl;
            break;
        case 7:
            system("cls");
            cout << "\x1b[37m" << "char: " << sizeof(char) << " байт" << "\x1b[0m" << endl << endl;
            break;
        case 8:
            system("cls");
            cout << "\x1b[31m" << "bool: " << sizeof(bool) << " байт" << "\x1b[0m" << endl << endl;
            break;
        case 9:
            system("cls");
            cout << "\x1b[32m" << "int: " << sizeof(int) << " байта\n"
                << "short int: " << sizeof(short int) << " байта\n"
                << "long int: " << sizeof(long int) << " байта\n"
                << "float: " << sizeof(float) << " байта\n"
                << "double: " << sizeof(double) << " байт\n"
                << "long double: " << sizeof(long double) << " байт\n"
                << "char: " << sizeof(char) << " байт\n"
                << "bool: " << sizeof(bool) << " байт\n" << "\x1b[0m" << endl;
            break;
        case 10:
            system("cls");
            return;
        default:
            problem();
        }
    }
}

int main() { // main menu
    setlocale(LC_ALL, "RU");
    int select = 0;
    while (true) {
        cout << "1. Типы данных" << endl
            << "2. Двоичное представление типа int " << endl
            << "3. Двоичное представление типа float " << endl
            << "4. Двоичное представление типа double " << endl
            << "5. Двоичное представление для всех типов данных с произвольным изменением бита " << endl
            << "6." << "\x1b[31m" << " Выход " << "\x1b[0m" << endl;
        cout << "Выберите операцию: ";
        cin >> select;
        long double num_double;
        float num_float;
        long long num_int;
        string result_double, result_int, result_float;
        switch (select) {
        case 1:
            system("cls");
            Menu12();
            break;
        case 2: // двоичное представление инта
            system("cls");
            cout << "Введите целое число: ";
            if (!(cin >> num_int)) problem();
            if ((num_int <= 2147483647) && (num_int >= -2147483647)) {
                result_int = perevodv2_int(num_int);
                cout << result_int << endl;
            }       
            break;
        case 3: // float
            system("cls");
            cout << "Введите число: ";
            if (!(cin >> num_float)) problem();
            result_float = perevodv2_float(num_float);
            cout << result_float << endl;
            break;
        case 4: // double
            system("cls");
            cout << "Введите число: ";
            if (!(cin >> num_double)) problem();
            result_double = perevodv2_double(num_double);
            cout << result_double << endl;
            break;
        case 5:
            system("cls");
            menu51();
            break;
        case 6:
            cout << "До свидания!" << endl;
            return false;
        default:
            problem();
        }
    }
    return 0;
}