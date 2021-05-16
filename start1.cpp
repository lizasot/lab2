#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;


// ДИНАМИЧЕСКИЙ ОДНОМЕРНЫЙ ЦЕЛОЧИСЛЕННЫЙ МАССИВ 
// == Прочие действия ==
// Вывод массива
void outputArr(int*& arr, int size)
{
    if (size <= 0) { cout << "Ошибка!\n"; return; }
    for (int i = 0; i < size; i++) { cout << arr[i] << ' '; }
    cout << '\n';
}

// Создание массива размера N. Данные - случайные числа от 0 до 99
int* createArr(int N)
{
    if (N <= 0) { cout << "Ошибка!\n"; return NULL; }
    int* arr = new int[N]();
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100; //заполнение случайным числом от 0 до 99
    }
    return arr;
}

// == ФУНКЦИИ ПО ПУНКТАМ ==
//пункт 1.a по массивам: N случайных чисел
int taskArr1a(int*& arr, bool time, int repeat)
{
    clock_t start, end; //таймер
    int n;
    cout << "Введите количество элементов нового массива: ";
    while (!(cin >> n) || (n <= 0)) //проверка на корректность ввода
    {
        cout << "Ошибка! Новый массив не был создан!\n";
        cin.clear();
        cin.sync();
        while (cin.get() != '\n');
        cout << "Введите количество элементов нового массива: ";
    }
    
    if (time) { start = clock(); } //начало таймера 
    for (int r = 0; r < repeat; r++){ if (arr) { delete[] arr; } arr = createArr(n); }
    if (time) { end = clock(); } //конец таймера
    cout << "Создан новый массив: ";
    outputArr(arr, n);
    if (time) { cout << "Время выполнения (только создание): " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
    return n;
}

//пункт 1.b по массивам: произвольный размер
int taskArr1b(int*& arr, bool time)
{
    clock_t start, end;
    int x, size = 1;
    cout << "Введите элементы нового массива: ";
    cin >> x;
    if (!cin) { cout << "Ошибка! Новый массив не был создан\n"; }
    else
    {
        if (time) { start = clock(); } //начало таймера
        if (arr) { delete[] arr; }
        arr = createArr(1);
        arr[0] = x;
        while (cin && cin.get() != '\n') //считываются все значения, пока не встречен мусор
        {
            int* tmp;
            cin >> x;
            if (cin)
            {
                size++;
                tmp = (int*)realloc(arr, size * sizeof(int));
                if (tmp != NULL) { arr = tmp; arr[size - 1] = x; }
            }
        }
        if (time) { end = clock(); } //конец таймера
        cout << "Создан новый массив: ";
        outputArr(arr, size);
        cout << "Длина массива — " << size << " элементов.\n";
        if (time) { cout << "Время выполнения (только создание): " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
        return size;
    }
    return 0;
}

//пункт 1.с по массивам: произвольный размер с файла
int taskArr1с(int*& arr, bool time, int repeat)
{
    clock_t start, end;
    int x, size = 1;
    ifstream fin("numbers.txt");
    if (!fin.is_open()) { cout << "Файл не был найден.\n"; } // если файл не открыт, сообщить об этом
    else
    {
        
        fin >> x;
        if (!fin) { cout << "Ошибка! Новый массив не был создан\n"; }
        else
        {
            if (time) { start = clock(); } //начало таймера
            if (arr) { delete[] arr; }
            arr = createArr(1);
            arr[0] = x;
            while (fin && fin.get() != '\n') //считываются все значения, пока не встречен мусор
            {
                int* tmp;
                fin >> x;
                if (fin)
                {
                    size++;
                    tmp = (int*)realloc(arr, size * sizeof(int));
                    if (tmp != NULL) { arr = tmp; arr[size - 1] = x; }
                }
            }
            if (time) { end = clock(); } //конец таймера
            cout << "Создан новый массив: ";
            outputArr(arr, size);
            cout << "Длина массива — " << size << " элементов.\n";
            if (time) { cout << "Время выполнения (только создание): " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
            return size;
        }
    }
    return 0;
}

//3.a - вставка нового элемента 
void taskArr3a(int*& arr, bool time, int& size, int repeat)
{
    clock_t start, end;
    if (repeat < 1) { cout << "Ошибка! Массив не был изменён!\n"; return; }
    if (size < 1) { cout << "Ошибка! Массив не был найден!\n"; return; }
    int x;
    cout << "Введите значение нового элемента: ";
    cin >> x;
    if (!cin) { cout << "Ошибка! Массив не был изменён!\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        if (time) { start = clock(); } //начало таймера

        for (int i = 0; i < repeat; i++)
        {
            int* tmp;
            size++;
            tmp = (int*)realloc(arr, size * sizeof(int));
            if (tmp != NULL) { arr = tmp; arr[size - 1] = x; }
        }

        if (time) { end = clock(); } //конец таймера
        cout << "Создан новый массив: ";
        outputArr(arr, size);
        cout << "Длина массива — " << size << " элементов.\n";
        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
        return;
    }
    return;
}

//3ItemInd - получить элемент по индексу
void taskArr3ItemInd(int*& arr, bool time, int& size, int repeat)
{
    clock_t start, end;
    if (repeat < 1) { cout << "Ошибка! Количество повторений не может быть меньше 1!\n"; return; }
    if (size < 1) { cout << "Ошибка! Массив не был найден!\n"; return; }
    int x;
    cout << "Введите индекс элемента, который хотите получить (нумерация элементов с нуля): ";
    cin >> x;
    if (!cin || x >= size || x < 0) { cout << "Ошибка! Элемент не был найден.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        if (time) { start = clock(); } //начало таймера

        int* item = nullptr;
        for (int i = 0; i < repeat; i++) { item = &arr[x]; }

        if (time) { end = clock(); } //конец таймера
        if (item != nullptr) { cout << "Получен элемент " << *item << " с адресом " << item << '\n'; }
        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
        return;
    }
    return;
}

//3Item - получить элемент по значению
void taskArr3Item(int*& arr, bool time, int& size, int repeat)
{
    clock_t start, end;
    if (repeat < 1) { cout << "Ошибка! Количество повторений не может быть меньше 1!\n"; return; }
    if (size < 1) { cout << "Ошибка! Массив не был найден!\n"; return; }
    int x;
    cout << "Введите значение элемента, который хотите получить: ";
    cin >> x;
    if (!cin) { cout << "Ошибка! Некорректный ввод.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        if (time) { start = clock(); } //начало таймера

        int* item = nullptr;
        for (int r = 0; r < repeat; r++)
        {
            for (int i = 0; i < size; i++)
            {
                if (arr[i] == x) { item = &arr[i]; break; }
            }
            if (item == nullptr) { cout << "Не найдено\n"; break; }
        }

        if (time) { end = clock(); } //конец таймера
        if (item != nullptr) { cout << "Получен элемент " << *item << " с адресом " << item << '\n'; }
        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
    }
    return;
}

//3DelInd - удаление элемента по индексу
void taskArr3DelInd(int*& arr, bool time, int& size, int repeat)
{
    clock_t start, end;
    if (repeat < 1) { cout << "Ошибка! Количество повторений не может быть меньше 1!\n"; return; }
    if (size < 1) { cout << "Ошибка! Массив не был найден!\n"; return; }
    int x;
    cout << "Введите индекс, элемент которого хотите удалить (нумерация элементов с нуля): ";
    cin >> x;
    if (!cin || x >= size || x < 0) { cout << "Ошибка! Элемент не был найден.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        if (time) { start = clock(); } //начало таймера

        for (int r = 0; r < repeat; r++)
        {
            if (!cin || x >= size || x < 0) { cout << "Ошибка! Повторение не удалось, так как такой элемент не был найден.\n"; r = repeat; break; }
            for (int j = x; j < size; j++) { arr[j] = arr[j + 1]; } //сдвиг влево на место удаляемого элемента
            int* tmp;
            size--;
            tmp = (int*)realloc(arr, size * sizeof(int));
            if (tmp != NULL) { arr = tmp; }
        }
        if (time) { end = clock(); } //конец таймера

        cout << "Новый массив: ";
        if (size) { outputArr(arr, size); }
        else { cout << "Массив пуст.\n"; }
        cout << "Длина массива — " << size << " элементов.\n";

        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
        return;
    }
    return;
}

//3Del - удаление элемента по значению
//Удаляется только 1 элемент, так как доступна функция повтора
void taskArr3Del(int*& arr, bool time, int& size, int repeat)
{
    clock_t start, end;
    if (repeat < 1) { cout << "Ошибка! Количество повторений не может быть меньше 1!\n"; return; }
    if (size < 1) { cout << "Ошибка! Массив не был найден!\n"; return; }
    int x;
    cout << "Введите значение элемента, который хотите удалить: ";
    cin >> x;
    if (!cin) { cout << "Ошибка! Некорректный ввод.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        bool check; //найден ли элемент?
        if (time) { start = clock(); } //начало таймера

        for (int r = 0; r < repeat; r++)
        {
            check = false;
            for (int i = 0; i < size; i++)
            {
                if (arr[i] == x)
                {
                    for (int j = i; j < size; j++) { arr[j] = arr[j + 1]; } //сдвиг влево на место удаляемого элемента
                    int* tmp;
                    size--;
                    tmp = (int*)realloc(arr, size * sizeof(int));
                    if (tmp != NULL) { arr = tmp; }
                    check = true;
                    break;
                }
            }
            if (!check) { cout << "Элемент не найден\n"; r = repeat; break; }
        }
        if (time) { end = clock(); } //конец таймера
        if (check)
        {
            cout << "Элемент удалён\n";
            cout << "Новый массив: ";
            if (size) { outputArr(arr, size); }
            else { cout << "Массив пуст.\n"; }
            cout << "Длина массива — " << size << " элементов.\n\n";
        }

        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
        return;
    }
    return;
}

// ДВУСВЯЗНЫЙ СПИСОК
struct list
{
    int data;
    list* tail;
    list* head;
};

// == Прочие действия ==
// Вывод списка, начиная с введённого узла 
void outputList(list* beg)
{
    if (!beg) { cout << "Список не найден!"; return; }
    list* curr = beg;
    while (curr)
    {
        cout << curr->data << ' ';
        curr = curr->tail;
    }
    cout << '\n';
}

// Очищение списка, начиная с введённого узла 
void deleteList(list*& beg)
{
    list* Next;
    while (beg)
    {
        Next = beg->tail;
        delete beg;
        beg = Next;
    }
}

// Длина списка
int lenList(list* roster)
{
    size_t len = 0;
    while (roster)
    {
        len++;
        roster = roster->tail;
    }
    return len;
}

// == Создание списка размера N. Данные - случайные числа от 0 до 99 ==
list* createList(int N)
{
    if (N <= 0) { cout << "Ошибка!\n"; return NULL; }
    list* Curr = 0, //текущий элемент
        * Next = 0; //следующий
    for (int i = 0; i < N; i++) //заполнение списка с конца
    {
        Curr = new list; //новый элемент

        Curr->data = rand() % 100; //заполнение случайным числом от 0 до 99

        Curr->tail = Next; //в адресной части - следующий элемент
        if (Next) //если существует следующий элемент
        {
            Next->head = Curr;
        } //закрепляем прошлый узел с текущим
        Next = Curr; //переходим к следующему элементу
    }

    Curr->head = 0; //его предыдущий адрес должен отсылаться на NULL
    return Curr; //адрес последнего элемента возвращается как адрес первого
}

// == Заполнение списка данными. N определяется автоматически ==
//Добавление нового элемента к списку после указанного узла. Не добавляет элемент в начало списка
list* addItem(list* roster, int a)
{
    list* temp;
    temp = new list; //создание добавляемого узла
    temp->data = a; //заполняем значение

    temp->tail = roster->tail;
    temp->head = roster;
    if (roster->tail) { (roster->tail)->head = temp; }
    roster->tail = temp;

    return temp;  //адрес добавленного узла
}

//доступ к заданному элементу списка (по индексу) для манипуляций с его информационной частью
list* itemList(list* beg, int index)
{
    //index--; //если индексация не с нуля
    while (beg && (index--))
    {
        beg = beg->tail;
        if (!beg) { return 0; } //элемент не существует
    }
    return beg;
}

//удаление узла из списка;
list* deleteItem(list* delItem, list* beg)
{
    list* prev, * next;
    prev = delItem->head; //элемент, предшедствующий удаляемому узлу
    next = delItem->tail; //следующий элемент после удаляемого

    //если НЕ первый
    if (prev) { prev->tail = delItem->tail; }
    else //если в начале
    {
        delete delItem;
        if (next) { next->head = prev; return next; } //если следующий элемент существует - вернуть его как начало
        else { return NULL; } //если нет - список будет удалён
    }
    //если НЕ последний
    if (next) { next->head = delItem->head; }

    delete delItem;
    return beg;
}

// == ФУНКЦИИ ПО ПУНКТАМ ==
//пункт 1.a по спискам: N случайных чисел
void taskList1a(list*& beg, bool time, int repeat)
{
    clock_t start, end;
    int n;
    cout << "Введите длину нового списка: ";
    while (!(cin >> n) || (n <= 0))
    {
        cout << "Ошибка! Новый список не был создан!\n";
        cin.clear();
        cin.sync();
        while (cin.get() != '\n');
        cout << "Введите длину нового списка: ";
    }
    if (beg) { deleteList(beg); }
    if (time) { start = clock(); }
    for (int r = 0; r < repeat; r++){ beg = createList(n); }
    if (time) { end = clock(); }
    cout << "Создан новый список: ";
    outputList(beg);
    if (time) { cout << "Время выполнения (только создание): " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
}

//пункт 1.b по спискам: произвольный размер
void taskList1b(list*& beg, bool time)
{
    clock_t start, end;
    int x;
    cout << "Введите элементы нового списка: ";
    cin >> x;
    if (!cin) { cout << "Ошибка! Некорректный ввод.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        if (time) { start = clock(); }
        if (beg) { deleteList(beg); }
        beg = createList(1);
        beg->data = x;
        while (cin && cin.get() != '\n') //считываются все значения, пока не встречен мусор
        {
            cin >> x;
            if (cin)
            {
                addItem(beg, x);
                beg = beg->tail;
            }
        }
        if (time) { end = clock(); }
        while (beg->head) { beg = beg->head; }
        cout << "Создан новый список: ";
        outputList(beg);
        cout << "Длина списка — " << lenList(beg) << " элементов.\n";
        if (time) { cout << "Время выполнения (только создание): " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
    }
}

//пункт 1.c по спискам: произвольный размер, считывание с файла
void taskList1c(list*& beg, bool time)
{
    clock_t start, end;
    int x;
    ifstream fin("numbers.txt");
    if (!fin.is_open()) { cout << "Файл не был найден.\n"; }// если файл не открыт, сообщить об этом
    else
    {
        fin >> x;
        if (!fin) { cout << "Ошибка! Некорректный ввод.\n"; cin.clear(); while (cin.get() != '\n'); }
        else
        {
            if (time) { start = clock(); }
            if (beg) { deleteList(beg); }
            beg = createList(1);
            beg->data = x;
            while (fin && fin.get() != '\n') //считываются все значения, пока не встречен мусор
            {
                fin >> x;
                if (fin)
                {
                    addItem(beg, x);
                    beg = beg->tail;
                }
            }
            if (time) { end = clock(); }
            while (beg->head) { beg = beg->head; }
            cout << "Создан новый список: ";
            outputList(beg);
            cout << "Длина списка — " << lenList(beg) << " элементов.\n";
            if (time) { cout << "Время выполнения (только создание): " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
            fin.close();
        }
    }

    
}

//3.a - вставка нового элемента !!после первого элемента
void taskList3a(list*& beg, bool time, int repeat)
{
    clock_t start, end;
    if (repeat < 1) { cout << "Ошибка! Список не был изменён!\n"; return; }
    if (!beg) { cout << "Ошибка! Список не был найден!\n"; return; }
    int x;
    cout << "Введите значение нового элемента: ";
    cin >> x;
    if (!cin) { cout << "Ошибка! Некорректный ввод.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        if (time) { start = clock(); } //начало таймера

        for (int i = 0; i < repeat; i++)
        {
            addItem(beg, x);
        }

        if (time) { end = clock(); } //конец таймера
        cout << "Создан новый список: ";
        outputList(beg);
        cout << "Длина списка — " << lenList(beg) << " элементов.\n";
        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
    }
    return;
}

//3ItemInd - получить элемент по индексу
void taskList3ItemInd(list*& beg, bool time, int repeat)
{
    clock_t start, end;
    if (repeat < 1) { cout << "Ошибка! Количество повторений не может быть меньше 1!\n"; return; }
    if (!beg) { cout << "Ошибка! Список не был найден!\n"; return; }
    int x;
    cout << "Введите индекс элемента, который хотите получить (нумерация элементов с нуля): ";
    cin >> x;
    if (!cin || x >= lenList(beg) || x < 0) { cout << "Ошибка! Элемент не был найден.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        if (time) { start = clock(); } //начало таймера

        list* item = nullptr;
        for (int i = 0; i < repeat; i++) { item = itemList(beg, x); }

        if (time) { end = clock(); } //конец таймера
        if (item != nullptr) { cout << "Получен элемент " << item->data << " с адресом " << item << '\n'; }
        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
    }
    return;
}

//3Item - получить элемент по значению
void taskList3Item(list*& beg, bool time, int repeat)
{
    clock_t start, end;
    if (repeat < 1) { cout << "Ошибка! Количество повторений не может быть меньше 1!\n"; return; }
    if (!beg) { cout << "Ошибка! Список не был найден!\n"; return; }
    int x;
    cout << "Введите значение элемента, который хотите получить: ";
    cin >> x;
    if (!cin || x >= lenList(beg) || x < 0) { cout << "Ошибка! Элемент не был найден.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        bool check = false; //найден ли элемент?
        if (time) { start = clock(); } //начало таймера

        list* tmp;
        list* item = nullptr;
        for (int r = 0; r < repeat; r++)
        {
            tmp = beg;
            size_t i = 0;
            do
            {
                if (tmp->data == x) { item = tmp; break; }
                tmp = tmp->tail;
                i++;
            } while (tmp);
            if (item == nullptr) { cout << "Не найдено\n"; break; }
        }

        if (time) { end = clock(); } //конец таймера
        if (item != nullptr) { cout << "Получен элемент " << item->data << " с адресом " << item << '\n'; }
        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
    }
    return;
}

//3DelInd - удаление элемента по индексу
void taskList3DelInd(list*& beg, bool time, int repeat)
{
    clock_t start, end;
    if (repeat < 1) { cout << "Ошибка! Количество повторений не может быть меньше 1!\n"; return; }
    if (!beg) { cout << "Ошибка! Список не был найден!\n"; return; }
    int x;
    cout << "Введите индекс элемента, который хотите удалить (нумерация элементов с нуля): ";
    cin >> x;
    if (!cin || x >= lenList(beg) || x < 0) { cout << "Ошибка! Элемент не был найден.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        if (time) { start = clock(); } //начало таймера

        for (int i = 0; i < repeat; i++)
        {
            if (itemList(beg, x)) { deleteItem(itemList(beg, x), beg); }
            else { cout << "Ошибка! Такой элемент не был найден.\n"; break; }
        }

        if (time) { end = clock(); } //конец таймера
        if (beg)
        {
            cout << "Создан новый список: ";
            outputList(beg);
            cout << "Длина списка — " << lenList(beg) << " элементов.\n";
        }
        else { cout << "Список был удалён\n"; }
        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
    }
    return;
}

//3Del - удаление элемента по значению
void taskList3Del(list*& beg, bool time, int repeat)
{
    clock_t start, end;
    bool check = false; //удалён ли элемент
    if (repeat < 1) { cout << "Ошибка! Количество повторений не может быть меньше 1!\n"; return; }
    if (!beg) { cout << "Ошибка! Список не был найден!\n"; return; }
    int x;
    cout << "Введите значение элемента, который хотите удалить: ";
    cin >> x;
    if (!cin) { cout << "Ошибка! Некорректный ввод.\n"; cin.clear(); while (cin.get() != '\n'); }
    else
    {
        list* delItem;
        if (time) { start = clock(); } //начало таймера

        for (int i = 0; i < repeat; i++)
        {
            delItem = beg;
            do {
                if (delItem->data == x)
                {
                    beg = deleteItem(delItem, beg);
                    check = true;
                    break;
                }
                delItem = delItem->tail;
            } while (delItem);
            if (!check) { break; }
        }

        if (time) { end = clock(); } //конец таймера
        if (beg)
        {
            if (check)
            {
                cout << "Создан новый список: ";
                outputList(beg);
                cout << "Длина списка — " << lenList(beg) << " элементов.\n";
            }
            else { cout << "Элемент не был найден\n"; }
        }
        else { cout << "Список был удалён\n"; }
        if (time) { cout << "Время выполнения: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << '\n'; }
    }
    return;
}

int main()
{
    setlocale(0, "");
    bool time = true;
    int repeat = 1; //количество повторений действия

    // ДИНАМИЧЕСКИЙ МАССИВ
    int size = 0;
    int* arr = new int[size]();

    // ДВУСВЯЗНЫЙ СПИСОК 
    list* beg = NULL;

    bool check = true; //выход из меню
    bool check1 = false; //выход из под меню
    bool outp = false;
    //false - заканчивает цикл, приводя непосредственно к выходу
    do {
        //system("cls");
        char sw = ' '; //переключатель главного меню
        char sw1 = ' '; //переключатель саб-меню
        cout << "\nВыберите нужный раздел: \n";
        cout << "\x1b[32m[1]\x1b[0m Создание целочисленного одномерного массива\n";
        cout << "\x1b[32m[2]\x1b[0m Работа с элементами массива \n";
        cout << "\x1b[32m[3]\x1b[0m Создание двусвязного списка\n";
        cout << "\x1b[32m[4]\x1b[0m Работа с узлами двусвязного списка\n";
        cout << "\x1b[32m[5]\x1b[0m Включить/выключить счётчик времени при выполнении какого-либо действия. Состояние: ";
        if (time) { cout << "\x1b[32mВключено\x1b[0m\n"; }
        else { cout << "\x1b[33mВыключено\x1b[0m\n"; }
        cout << "\x1b[32m[6]\x1b[0m Установить другое число повторов действия. Количество повторений сейчас: " << repeat << '\n';
        cout << "\x1b[32m[7]\x1b[0m Очистить экран консоли\n";
        cout << "\x1b[32m[8]\x1b[0m Включить/выключить отображение списка и массива. Состояние: ";
        if (outp) { cout << "\x1b[32mВключено\x1b[0m\n"; }
        else { cout << "\x1b[33mВыключено\x1b[0m\n"; }
        cout << "\x1b[32m[0]\x1b[0m Закрыть программу\n";
        if (outp)
        {
            cout << "Массив: ";
            if (size) { outputArr(arr, size); }
            else { cout << "Не создан.\n"; }
            cout << "Список: ";
            if (beg) { outputList(beg); }
            else { cout << "Не создан.\n"; }
        }
        cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

        cin >> sw;
        while (cin.get() != '\n') { sw = ' '; }; //если строка содержит более одного символа, возвращается ошибка

        switch (sw)
        {

        case '1': //[1] Создание целочисленного одномерного массива
            do {
                check1 = false;
                sw1 = ' ';
                cout << "\n\x1b[32m[1]\x1b[0m Ввести количество элементов в массиве, чтобы получить массив со случайными числами (от 0 до 99)\n";
                cout << "\x1b[32m[2]\x1b[0m Ввести значение элементов массива. Его размер определяется автоматически\n";
                cout << "\x1b[32m[3]\x1b[0m Считать массив с файла\n";
                cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
                cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

                cin >> sw1;
                while (cin.get() != '\n') { sw1 = ' '; };

                switch (sw1)
                {
                case '1': //[1] Случайные числа
                    size = taskArr1a(arr, time, repeat);
                    break;
                case '2': //[2] Заполнение массива
                    size = taskArr1b(arr, time);
                    break;
                case '3': //[3] Заполнение массива с файла
                    size = taskArr1с(arr, time, repeat);
                    break;
                case '0': //[0] Назад
                    break;
                default:
                    cout << "Ошибка! Пожалуйста, попробуйте снова\n";
                    check1 = true; //цикл пойдёт заново
                    break;
                }
            } while (check1);
            break;

        case '2': //[2] Работа с элементами массива
            do {
                check1 = false;
                sw1 = ' ';
                cout << "\nВыберите, что хотите сделать: \n";
                cout << "\x1b[32m[1]\x1b[0m Вставить новый элемент в массив\n";
                cout << "\x1b[32m[2]\x1b[0m Удалить элемент массива (по индексу)\n";
                cout << "\x1b[32m[3]\x1b[0m Удалить элемент массива (по значению)\n";
                cout << "\x1b[32m[4]\x1b[0m Получить элемент массива по индексу\n";
                cout << "\x1b[32m[5]\x1b[0m Получить элемента массива по значению\n";
                cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
                cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

                cin >> sw1;
                while (cin.get() != '\n') { sw1 = ' '; };

                switch (sw1)
                {
                case '1': //[1] Вставить новый элемент в массив
                    taskArr3a(arr, time, size, repeat);
                    break;
                case '2': //[2] Удалить элемент массива (по индексу)
                    taskArr3DelInd(arr, time, size, repeat);
                    break;
                case '3': //[3] Удалить элемент массива (по значению)
                    taskArr3Del(arr, time, size, repeat);
                    break;
                case '4': //[4] Получить элемент массива по индексу
                    taskArr3ItemInd(arr, time, size, repeat);
                    break;
                case '5': //[5] Получить элемента массива по значению
                    taskArr3Item(arr, true, size, repeat);
                    break;
                case '0': //[0] Назад
                    break;
                default:
                    cout << "Ошибка! Пожалуйста, попробуйте снова\n";
                    check1 = true; //цикл пойдёт заново
                    break;
                }
            } while (check1);
            break;


        case '3': //[3] Создание двусвязного списка
            do {
                check1 = false;
                sw1 = ' ';
                cout << "\nВыберите, что хотите сделать: \n";
                cout << "\x1b[32m[1]\x1b[0m Ввести количество элементов в списке, чтобы получить список со случайными числами (от 0 до 99)\n";
                cout << "\x1b[32m[2]\x1b[0m Ввести значение узлов списка. Его размер определяется автоматически\n";
                cout << "\x1b[32m[3]\x1b[0m Считать список с файла\n";
                cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
                cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

                cin >> sw1;
                while (cin.get() != '\n') { sw1 = ' '; };

                switch (sw1)
                {
                case '1': //[1] Случайные числа
                    taskList1a(beg, time, repeat);
                    break;
                case '2': //[2] Заполнение списка
                    taskList1b(beg, time);
                    break;
                case '3': //[3] Заполнение списка с файла
                    taskList1c(beg, time);
                    break;
                case '0': //[0] Назад
                    break;
                default:
                    cout << "Ошибка! Пожалуйста, попробуйте снова\n";
                    check1 = true; //цикл пойдёт заново
                    break;
                }
            } while (check1);
            break;


        case '4': //[4] Работа с узлами двусвязного списка
            do {
                check1 = false;
                sw1 = ' ';
                cout << "\nВыберите, что хотите сделать: \n";
                cout << "\x1b[32m[1]\x1b[0m Вставить новый элемент в список\n";
                cout << "\x1b[32m[2]\x1b[0m Удалить узел списка (по индексу)\n";
                cout << "\x1b[32m[3]\x1b[0m Удалить узел списка (по значению)\n";
                cout << "\x1b[32m[4]\x1b[0m Получить элемент списка по индексу\n";
                cout << "\x1b[32m[5]\x1b[0m Получить элемент списка по значению\n";
                cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
                cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

                cin >> sw1;
                while (cin.get() != '\n') { sw1 = ' '; };

                switch (sw1)
                {
                case '1': //[1] Вставить новый элемент в массив
                    taskList3a(beg, time, repeat);
                    break;
                case '2': //[2] Удалить элемент массива (по индексу)
                    taskList3DelInd(beg, time, repeat);
                    break;
                case '3': //[3] Удалить элемент массива (по значению)
                    taskList3Del(beg, time, repeat);
                    break;
                case '4': //[4] Получить элемент списка по индексу
                    taskList3ItemInd(beg, time, repeat);
                    break;
                case '5': //[5] Получить элемент списка по значению
                    taskList3Item(beg, time, repeat);
                    break;
                case '0': //[0] Назад
                    break;
                default:
                    cout << "Ошибка! Пожалуйста, попробуйте снова\n";
                    check1 = true; //цикл пойдёт заново
                    break;
                }
            } while (check1);
            break;


        case '5': //[5] Включить/отключить счётчик времени при выполнении какого-либо действия
            time = !time;
            if (time) { cout << "Счётчик времени теперь включён.\n"; }
            else { cout << "Счётчик времени теперь отключён.\n"; }
            break;

        case '6': //[6] Установить другое число повторов действия. По умолчанию равен 1
            do
            {
                int x = 0;
                check1 = false;
                cout << "Введите число повторений (выше нуля): ";

                cin >> x;
                while (cin.get() != '\n');

                if (!cin || x <= 0) { cout << "Ошибка! Количество повторений не может быть меньше 1. Значение не было изменено.\n";
                check1 = true; }
                else { repeat = x; }
            } while (check1);
            break;

        case '7': //[7] Очистить экран
            system("cls");
            break;

        case '8': //[5] Включить/отключить счётчик времени при выполнении какого-либо действия
            outp = !outp;
            if (outp) { cout << "Отображение списка и массива включено.\n"; }
            else { cout << "Отображение списка и массива отключено.\n"; }
            break;

        case '0': //[0] Закрыть программу
            cout << "Выход из программы...\n";
            check = false; //выход из цикла
            break;
        default: //в случае, если введено что-то иное
            cout << "Ошибка! Пожалуйста, попробуйте снова\n";
            break;
        }

    } while (check);


    if (size) { delete[] arr; }
    deleteList(beg);
    system("Pause");
    return 0;
}