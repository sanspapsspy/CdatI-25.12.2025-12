#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>

// Вспомогательные функции

// Функция для проверки, является ли число простым
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Функция для проверки, содержит ли массив элемент
bool contains(const int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

// Функция для подсчета количества вхождений элемента в массив
int count_occurrences(const int* arr, int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            count++;
        }
    }
    return count;
}

// Функция для проверки, встречается ли элемент в массиве более одного раза
bool occurs_more_than_once(const int* arr, int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            count++;
            if (count > 1) {
                return true;
            }
        }
    }
    return false;
}

// Функция для вывода массива
void print_array(const char* label, const int* arr, int size) {
    int i;
    
    printf("%s: ", label);
    if (size == 0) {
        printf("пустой массив\n");
        return;
    }

    printf("[");
    for (i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// ЗАДАНИЕ 1: Массив C содержит нечетные элементы А, которых нет в В
int* task1(const int* A, int sizeA, const int* B, int sizeB, int* resultSize) {
    int maxSize = 0;
    int* C = NULL;
    int i;
    
    // Определяем максимально возможный размер результата
    for (i = 0; i < sizeA; i++) {
        if (A[i] % 2 != 0) { // нечетный
            if (!contains(B, sizeB, A[i])) { // не содержится в B
                maxSize++;
            }
        }
    }

    // Выделяем память для результата
    C = (int*)malloc(maxSize * sizeof(int));
    *resultSize = 0;

    // Заполняем массив C
    for (i = 0; i < sizeA; i++) {
        if (A[i] % 2 != 0) { // нечетный элемент A
            if (!contains(B, sizeB, A[i])) { // которого нет в B
                C[*resultSize] = A[i];
                (*resultSize)++;
            }
        }
    }

    return C;
}

// ЗАДАНИЕ 2: Массив C содержит элементы А, которые есть в В более, чем в одном экземпляре
int* task2(const int* A, int sizeA, const int* B, int sizeB, int* resultSize) {
    bool* added = NULL;
    int maxSize = 0;
    int* C = NULL;
    int i, j;
    
    // Временный массив для отслеживания уже добавленных элементов
    added = (bool*)calloc(sizeA, sizeof(bool));

    // Определяем максимально возможный размер результата
    for (i = 0; i < sizeA; i++) {
        if (!added[i]) {
            if (contains(B, sizeB, A[i]) && occurs_more_than_once(B, sizeB, A[i])) {
                maxSize++;
                // Помечаем все одинаковые элементы как добавленные
                for (j = i; j < sizeA; j++) {
                    if (A[j] == A[i]) {
                        added[j] = true;
                    }
                }
            }
        }
    }

    // Выделяем память для результата
    C = (int*)malloc(maxSize * sizeof(int));
    *resultSize = 0;

    // Сбрасываем массив added
    for (i = 0; i < sizeA; i++) {
        added[i] = false;
    }

    // Заполняем массив C
    for (i = 0; i < sizeA; i++) {
        if (!added[i]) {
            if (contains(B, sizeB, A[i]) && occurs_more_than_once(B, sizeB, A[i])) {
                C[*resultSize] = A[i];
                (*resultSize)++;
                // Помечаем все одинаковые элементы как добавленные
                for (j = i; j < sizeA; j++) {
                    if (A[j] == A[i]) {
                        added[j] = true;
                    }
                }
            }
        }
    }

    free(added);
    return C;
}

// ЗАДАНИЕ 3: Массив C содержит неповторяющиеся элементы А, которых нет в В
int* task3(const int* A, int sizeA, const int* B, int sizeB, int* resultSize) {
    bool* added = NULL;
    int maxSize = 0;
    int* C = NULL;
    int i, j;
    bool is_unique;
    
    // Временный массив для отслеживания уже добавленных элементов
    added = (bool*)calloc(sizeA, sizeof(bool));

    // Определяем максимально возможный размер результата
    for (i = 0; i < sizeA; i++) {
        if (!added[i]) {
            // Проверяем, что элемент уникален в A и не содержится в B
            if (!contains(B, sizeB, A[i])) {
                is_unique = true;
                // Проверяем уникальность в A
                for (j = 0; j < sizeA; j++) {
                    if (i != j && A[i] == A[j]) {
                        is_unique = false;
                        break;
                    }
                }
                if (is_unique) {
                    maxSize++;
                }
            }
            // Помечаем все одинаковые элементы
            for (j = i; j < sizeA; j++) {
                if (A[j] == A[i]) {
                    added[j] = true;
                }
            }
        }
    }

    // Выделяем память для результат
    C = (int*)malloc(maxSize * sizeof(int));
    *resultSize = 0;

    // Сбрасываем массив added
    for (i = 0; i < sizeA; i++) {
        added[i] = false;
    }

    // Заполняем массив C
    for (i = 0; i < sizeA; i++) {
        if (!added[i]) {
            // Проверяем, что элемент уникален в A и не содержится в B
            if (!contains(B, sizeB, A[i])) {
                is_unique = true;
                // Проверяем уникальность в A
                for (j = 0; j < sizeA; j++) {
                    if (i != j && A[i] == A[j]) {
                        is_unique = false;
                        break;
                    }
                }
                if (is_unique) {
                    C[*resultSize] = A[i];
                    (*resultSize)++;
                }
            }
            // Помечаем все одинаковые элементы
            for (j = i; j < sizeA; j++) {
                if (A[j] == A[i]) {
                    added[j] = true;
                }
            }
        }
    }

    free(added);
    return C;
}

// ЗАДАНИЕ 4: Массив C содержит четные элементы А, которые есть в В
int* task4(const int* A, int sizeA, const int* B, int sizeB, int* resultSize) {
    bool* added = NULL;
    int maxSize = 0;
    int* C = NULL;
    int i, j;
    
    // Временный массив для отслеживания уже добавленных элементов
    added = (bool*)calloc(sizeA, sizeof(bool));

    // Определяем максимально возможный размер результата
    for (i = 0; i < sizeA; i++) {
        if (!added[i]) {
            if (A[i] % 2 == 0 && contains(B, sizeB, A[i])) {
                maxSize++;
                // Помечаем все одинаковые элементы как добавленные
                for (j = i; j < sizeA; j++) {
                    if (A[j] == A[i]) {
                        added[j] = true;
                    }
                }
            }
        }
    }

    // Выделяем память для результата
    C = (int*)malloc(maxSize * sizeof(int));
    *resultSize = 0;

    // Сбрасываем массив added
    for (i = 0; i < sizeA; i++) {
        added[i] = false;
    }

    // Заполняем массив C
    for (i = 0; i < sizeA; i++) {
        if (!added[i]) {
            if (A[i] % 2 == 0 && contains(B, sizeB, A[i])) {
                C[*resultSize] = A[i];
                (*resultSize)++;
                // Помечаем все одинаковые элементы как добавленные
                for (j = i; j < sizeA; j++) {
                    if (A[j] == A[i]) {
                        added[j] = true;
                    }
                }
            }
        }
    }

    free(added);
    return C;
}

// ЗАДАНИЕ 5: Массив C содержит элементы А по модулю равные некоторым элементам В
int* task5(const int* A, int sizeA, const int* B, int sizeB, int* resultSize) {
    bool* added = NULL;
    int maxSize = 0;
    int* C = NULL;
    int i, j;
    bool found;
    
    // Временный массив для отслеживания уже добавленных элементов
    added = (bool*)calloc(sizeA, sizeof(bool));

    // Определяем максимально возможный размер результата
    for (i = 0; i < sizeA; i++) {
        if (!added[i]) {
            found = false;
            // Проверяем, есть ли в B элемент с таким же модулем
            for (j = 0; j < sizeB; j++) {
                if (abs(A[i]) == abs(B[j])) {
                    found = true;
                    break;
                }
            }
            if (found) {
                maxSize++;
                // Помечаем все одинаковые элементы как добавленные
                for (j = i; j < sizeA; j++) {
                    if (A[j] == A[i]) {
                        added[j] = true;
                    }
                }
            }
        }
    }

    // Выделяем память для результата
    C = (int*)malloc(maxSize * sizeof(int));
    *resultSize = 0;

    // Сбрасываем массив added
    for (i = 0; i < sizeA; i++) {
        added[i] = false;
    }

    // Заполняем массив C
    for (i = 0; i < sizeA; i++) {
        if (!added[i]) {
            found = false;
            // Проверяем, есть ли в B элемент с таким же модулем
            for (j = 0; j < sizeB; j++) {
                if (abs(A[i]) == abs(B[j])) {
                    found = true;
                    break;
                }
            }
            if (found) {
                C[*resultSize] = A[i];
                (*resultSize)++;
                // Помечаем все одинаковые элементы как добавленные
                for (j = i; j < sizeA; j++) {
                    if (A[j] == A[i]) {
                        added[j] = true;
                    }
                }
            }
        }
    }

    free(added);
    return C;
}

// ЗАДАНИЕ 6: Найти последний по порядку элемент, являющийся простым числом
int task6(const int* A, int sizeA) {
    int i;
    
    for (i = sizeA - 1; i >= 0; i--) {
        if (is_prime(A[i])) {
            return A[i];
        }
    }
    return -1; // Если простых чисел нет
}

// Основная функция для демонстрации работы
int main() {
    // Тестовые данные
    int A[] = { 2, 3, 5, 7, 3, 8, 10, 5, 13, 17, 19, 4, 6, 8, -5, -3 };
    int B[] = { 3, 5, 8, 10, 12, 14, 16, 3, 5, 7, -3, -5 };
    int sizeA = sizeof(A) / sizeof(A[0]);
    int sizeB = sizeof(B) / sizeof(B[0]);
    
    // Для задания 1
    int sizeC1;
    int* C1 = NULL;
    
    // Для задания 2
    int sizeC2;
    int* C2 = NULL;
    
    // Для задания 3
    int sizeC3;
    int* C3 = NULL;
    
    // Для задания 4
    int sizeC4;
    int* C4 = NULL;
    
    // Для задания 5
    int sizeC5;
    int* C5 = NULL;
    
    // Для задания 6
    int last_prime;
    
    // Для дополнительного примера
    int testArray[] = { 4, 6, 8, 9, 10, 12, 14, 15 };
    int testSize = sizeof(testArray) / sizeof(testArray[0]);
    int result;

    setlocale(LC_ALL, ("Rus"));

    printf("Исходные массивы:\n");
    print_array("A", A, sizeA);
    print_array("B", B, sizeB);
    printf("\n");

    // Задание 1
    printf("ЗАДАНИЕ 1:\n");
    printf("Найти нечетные элементы А, которых нет в В\n");
    printf("Ожидаемый результат:\n");
    printf("Из массива A берём нечётные элементы: 3, 5, 7, 3, 5, 13, 17, 19, -5, -3\n");
    printf("Исключаем те, что есть в B (3, 5, 7, -3, -5)\n");
    printf("Остаются: 13, 17, 19\n");
    printf("Результат: ");
    C1 = task1(A, sizeA, B, sizeB, &sizeC1);
    print_array("C", C1, sizeC1);
    free(C1);
    printf("\n");

    // Задание 2
    printf("ЗАДАНИЕ 2:\n");
    printf("Найти элементы А, которые есть в В более, чем в одном экземпляре\n");
    printf("Ожидаемый результат:\n");
    printf("В массиве B элементы, встречающиеся более 1 раза: 3 (два раза), 5 (два раза)\n");
    printf("В массиве A эти элементы: 3, 5, 3, 5\n");
    printf("Уникальные значения: 3, 5\n");
    printf("Результат: ");
    C2 = task2(A, sizeA, B, sizeB, &sizeC2);
    print_array("C", C2, sizeC2);
    free(C2);
    printf("\n");

    // Задание 3
    printf("ЗАДАНИЕ 3:\n");
    printf("Найти неповторяющиеся элементы А, которых нет в В\n");
    printf("Ожидаемый результат:\n");
    printf("Неповторяющиеся в A: 2, 7, 8, 10, 13, 17, 19, 4, 6, -5, -3\n");
    printf("Исключаем те, что есть в B (8, 10, -3, -5)\n");
    printf("Остаются: 2, 7, 13, 17, 19, 4, 6\n");
    printf("Результат: ");
    C3 = task3(A, sizeA, B, sizeB, &sizeC3);
    print_array("C", C3, sizeC3);
    free(C3);
    printf("\n");

    // Задание 4
    printf("ЗАДАНИЕ 4:\n");
    printf("Найти четные элементы А, которые есть в В\n");
    printf("Ожидаемый результат:\n");
    printf("Чётные элементы A: 2, 8, 10, 4, 6, 8\n");
    printf("Из них есть в B: 8, 10\n");
    printf("Уникальные значения: 8, 10\n");
    printf("Результат: ");
    C4 = task4(A, sizeA, B, sizeB, &sizeC4);
    print_array("C", C4, sizeC4);
    free(C4);
    printf("\n");

    // Задание 5
    printf("ЗАДАНИЕ 5:\n");
    printf("Найти элементы А по модулю равные некоторым элементам В\n");
    printf("Ожидаемый результат:\n");
    printf("В B есть элементы с модулями: 3, 5, 8, 10, 12, 14, 16, 7, 3, 5\n");
    printf("В A ищем элементы с такими же модулями:\n");
    printf("|3| и |-3| → 3, -3 (но 3 и -3 есть в B)\n");
    printf("|5| и |-5| → 5, -5 (но 5 и -5 есть в B)\n");
    printf("|8| → 8 (есть в B)\n");
    printf("|10| → 10 (есть в B)\n");
    printf("|7| → 7 (есть в B)\n");
    printf("|13| → нет в B\n");
    printf("|17| → нет в B\n");
    printf("|19| → нет в B\n");
    printf("|4| → нет в B\n");
    printf("|6| → нет в B\n");
    printf("Уникальные значения из A: 3, 5, 7, 8, 10, -3, -5\n");
    printf("Результат: ");
    C5 = task5(A, sizeA, B, sizeB, &sizeC5);
    print_array("C", C5, sizeC5);
    free(C5);
    printf("\n");

    // Задание 6
    printf("ЗАДАНИЕ 6:\n");
    printf("Найти последний по порядку элемент, являющийся простым числом\n");
    printf("Ожидаемый результат:\n");
    printf("Простые числа в A: 2, 3, 5, 7, 3, 5, 13, 17, 19\n");
    printf("Последний по порядку (с конца): 19\n");
    last_prime = task6(A, sizeA);
    if (last_prime != -1) {
        printf("Результат: %d\n", last_prime);
    }
    else {
        printf("В массиве A нет простых чисел\n");
    }

    // Дополнительный пример для задачи 6
    printf("\nДополнительный пример для задачи 6:\n");
    print_array("Массив", testArray, testSize);
    printf("Ожидаемый результат: нет простых чисел\n");
    result = task6(testArray, testSize);
    if (result != -1) {
        printf("Последний простой элемент: %d\n", result);
    }
    else {
        printf("В массиве нет простых чисел (ожидаемо для этого массива)\n");
    }

    return 0;
}
