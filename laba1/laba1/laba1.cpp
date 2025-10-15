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

string perevodv2_int(int num) { // перевод в двоичную систему
    string str = ""; // строка для двоичной записи
    int nuli, save_num = num; // доп нули, сохранение числа для бита знака
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
    if (save_num < 0) str = '1' + str;
    else str = '0' + str;
    str.insert(1, " "); str.insert(9, " "); str.insert(18, " "); str.insert(27, " "); // пробелы для визуала
    cout << "\x1b[36m" << str << "\x1b[0m" << endl;
    cout << "^ ЗНАК\n";
    return "";
}

string perevodv2_float(float num) {
    float save_all_num = num; // сохраняем полностью число чтобы в конце дописать бит знака
    if (num < 0) num = -num; // если число отрицательное
    long long int_part = static_cast<long long>(num); // целая часть числа
    long long save_int_part = int_part; // сохраняем целую часть для дальнейших действий
    float drob_part = num - int_part; // дробная часть
    int nuli = 0; // для дополнительных нулей если нужно
    string str = "", str2 = ""; // строчки для целой (str) и дробной части (str2) 

    if (int_part == 0) str = '0'; // если целая часть равна 0 

    while (int_part != 0) { // процесс перевода целой части
        if (int_part % 2 == 1) str = '1' + str;
        else str = '0' + str;
        int_part = int_part >> 1;
    }

    while (drob_part > 0) { // процесс перевода дробной части
        drob_part = drob_part * 2;
        if (drob_part >= 1) {
            str2 += '1';
            drob_part--;
        }
        else {
            str2 += '0';
        }
    }

    string res = str + '.' + str2; // соединяем две части
    int point = res.find('.'), exponenta = 0, odin = res.find('1'), trash_after_point;
    /*первая точка в строке, экспонента, первая единица в строке,
    переменная для удаления ненужных нулей если целая часть равна нулю*/

    if (save_int_part != 0) {
        exponenta = point - odin - 1; // нахождение экспоненты если целая часть не ноль
        res.erase(point, 1); // удаление прошлой точки
        odin++;
        res.insert(odin, "."); // по индексу + 1 где находится единица ставим новую точку
    }
    if (save_int_part == 0) {
        exponenta = point - odin; // экспонента
        trash_after_point = -exponenta; // в данном случае экспонента нужна положительной, т.к. она изначально отрицательная ведь точку смещаем вправо.
        res.erase(point, 1); // удалили точку
        res.insert(odin, "."); // как в прошлом if
        res.erase(0, trash_after_point); // удаление ненужных нулей перед точкой, чтобы потом вставить переведённую в дв.з. экспоненту

    }

    exponenta = exponenta + 127; // экспонента
    string strex = ""; // строка для экспоненты

    while (exponenta > 0) { // перевод экспоненты в двоичную запись
        if (exponenta % 2 == 1) strex = '1' + strex;
        else strex = '0' + strex;
        exponenta /= 2;
    }

    if (strex.length() < 8) { //дополнительные нули для экспоненты
        nuli = 8 - strex.length();
        while (nuli != 0) {
            strex = '0' + strex;
            nuli--;
        }
    }

    res.erase(0, 1); // убираем единицу перед точкой т.к. единица осталась
    res = strex + res; // соединяем экспоненту с мантиссой

    if (res.length() < 32) { //дополнительные нули для дробной части
        nuli = 32 - res.length();
        while (nuli != 0) {
            res += '0';
            nuli--;
        }
    }

    if (save_all_num < 0) res = '1' + res; // добавляем бит знака
    else res = '0' + res;

    // пробелы для визуала
    res.insert(1, " "); res.insert(18, " "); res.insert(27, " ");
    cout << "Результат: " << "\x1b[32m" << res << "\x1b[0m" << endl;
    cout << setw(13) << "(S)" << "(---E--)" << " " << "(" << setfill('-') << setw(12) << "M" << setw(12) << ")" << setfill(' ') << endl;
    return "";
}

string perevodv2_double(double num) {
    double save_all_num = num; // сохраняем полностью число чтобы в конце дописать бит знака
    if (num < 0) num = -num; // если число отрицательное
    long long int_part = static_cast<long long>(num); // целая часть числа
    long long save_int_part = int_part; // сохраняем целую часть для дальнейших действий
    double drob_part = num - int_part; // дробная часть
    int nuli = 0; // для дополнительных нулей если нужно
    string str = "", str2 = ""; // строчки для целой (str) и дробной части (str2) 

    if (int_part == 0) str = '0'; // если целая часть равна 0 

    while (int_part != 0) { // процесс перевода целой части
        if (int_part % 2 == 1) str = '1' + str;
        else str = '0' + str;
        int_part = int_part >> 1;
    }

    while (drob_part > 0 ) { // процесс перевода дробной части
        drob_part = drob_part * 2;
        if (drob_part >= 1) {
            str2 += '1';
            drob_part--;
        }
        else {
            str2 += '0';
        }
    }

    string res = str + '.' + str2; // соединяем две части. | res (result) |
    int point = res.find('.'), exponenta = 0, odin = res.find('1'), trash_after_point; 
    /*первая точка в строке, экспонента, первая единица в строке, 
    переменная для удаления ненужных нулей если целая часть равна нулю*/ 

    if (save_int_part != 0) {
        exponenta = point - odin - 1; // нахождение экспоненты если целая часть не ноль
        res.erase(point, 1); // удаление прошлой точки
        odin++;
        res.insert(odin, "."); // по индексу + 1 где находится единица ставим новую точку
    }
    if (save_int_part == 0) {
        exponenta = point - odin; // экспонента
        trash_after_point = -exponenta; // в данном случае экспонента нужна положительной, т.к. она изначально отрицательная ведь точку смещаем вправо.
        res.erase(point, 1); // удалили точку
        res.insert(odin, "."); // как в прошлом if
        res.erase(0, trash_after_point); // удаление ненужных нулей перед точкой, чтобы потом вставить переведённую в дв.з. экспоненту
        
    }
    
    exponenta = exponenta + 1023; // экспонента
    string strex = ""; // строка для экспоненты

    while (exponenta > 0) { // перевод экспоненты в двоичную запись
        if (exponenta % 2 == 1) strex = '1' + strex;
        else strex = '0' + strex;
        exponenta /= 2;
    }

    if (strex.length() < 11) { //дополнительные нули для экспоненты
        nuli = 11 - strex.length();
        while (nuli != 0) {
            strex = '0' + strex;
            nuli--;
        }
    }

    res.erase(0, 1); // убираем единицу перед точкой т.к. единица осталась
    res = strex + res; // соединяем экспоненту с мантиссой
    
    if (res.length() < 64) { //дополнительные нули для дробной части
        nuli = 64 - res.length();
        while (nuli != 0) {
            res += '0';
            nuli--;
        }
    }

    if (save_all_num < 0) res = '1' + res; // добавляем бит знака
    else res = '0' + res; 

    res.insert(1, " "); res.insert(5, " "); res.insert(19, " "); res.insert(28, " "); res.insert(37, " "); res.insert(46, " "); res.insert(55, " "); res.insert(64, " ");
    // пробелы для визуала
    cout << "Результат: " << "\x1b[32m" << res << "\x1b[0m" << endl;
    cout << setw(13) << "(S)" << "(-----E----)" << " " << "(" << setfill('-') << setw(29) << "M" << setw(28) << ")" << setfill(' ') << endl;
    return "";
}

void perevod_bit_double(double num) { // замена бита для double
    uint64_t bits = *reinterpret_cast<uint64_t*>(&num); // double становится интом, но все биты от double сохранены. Нужно чтобы потом делать замену бита
    perevodv2_double(num);
    if (menu52forall() == 1) {
        int pos;
        bool bit;
        cout << "Введите позицию бита (0-63): ";
        cin >> pos;
        cout << "Введите значение бита (0-1): ";
        cin >> bit;

        // замена бита
        if (bit) bits |= (uint64_t(1) << pos);
        else bits &= ~(uint64_t(1) << pos);

        string otvet;
        double new_num = *reinterpret_cast<double*>(&bits); // снова double
        cout << "Новое число: " << fixed << setprecision(64) << new_num << endl;
        perevodv2_double(new_num);
        return;
    }  
}

void perevod_bit_float(float num) { // замена бита для float
    uint32_t bits = *reinterpret_cast<uint32_t*>(&num);
    perevodv2_float(num);
    if (menu52forall() == 1) {
        int pos; 
        bool bit;
        cout << "Введите позицию бита (0-31): ";
        cin >> pos;
        cout << "Введите значение бита (0-1): ";
        cin >> bit;
        // замена бита
        if (bit) bits |= (uint32_t(1) << pos);
        else bits &= ~(uint32_t(1) << pos);

        string otvet;
        float new_num = *reinterpret_cast<float*>(&bits);

        cout << "Новое число: " << fixed << setprecision(64) << new_num << endl;
        perevodv2_float(new_num);
        return;
    }
}

int perevod_bit_int(int num) { // замена бита для int
    perevodv2_int(num);
    int new_num, pos; // новое число, позиция бита
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
    while (select != 4) {
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
    int select = 0;
    while (select != 10) {
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
        cin >> select;
        switch (select) {
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