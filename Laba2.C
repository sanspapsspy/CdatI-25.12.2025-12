#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <locale.h>

// Вспомогательные функции

// Функция для проверки, содержит ли массив элемент
bool contains(const int* arr, int size, int value) {
    int i;
    
    for (i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

// Функция для подсчета количества вхождений элемента в массив
int count_occurrences(const int* arr, int size, int value) {
    int count = 0;
    int i;
    
    for (i = 0; i < size; i++) {
        if (arr[i] == value) {
            count++;
        }
    }
    return count;
}

// Функция для поиска минимального элемента в массиве
int find_min(const int* arr, int size) {
    int min;
    int i;
    
    if (size == 0) return 0;
    min = arr[0];
    
    for (i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Функция для поиска максимального элемента в массиве
int find_max(const int* arr, int size) {
    int max;
    int i;
    
    if (size == 0) return 0;
    max = arr[0];
    
    for (i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Функция для поиска ближайшего по модулю элемента в массиве B
int find_closest_by_abs(const int* B, int sizeB, int value) {
    int closest;
    int min_diff;
    int diff;
    int i;
    
    if (sizeB == 0) return 0;

    closest = B[0];
    min_diff = abs(value - B[0]);

    for (i = 1; i < sizeB; i++) {
        diff = abs(value - B[i]);
        if (diff < min_diff) {
            min_diff = diff;
            closest = B[i];
        }
    }

    return closest;
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

// ЗАДАНИЕ 1: Массив C, где к каждому четному элементу А добавлено сколько раз этот элемент встречается в массиве В
// Интерпретация: Для каждого элемента массива A, если он четный, то в массив C добавляем этот элемент плюс количество его вхождений в B
// Если элемент A нечетный, то просто добавляем его в C без изменений
int* task1(const int* A, int sizeA, const int* B, int sizeB, int* resultSize) {
    int* C = NULL;
    int i;
    int count_in_B;
    
    // Результирующий массив будет такого же размера, как A
    C = (int*)malloc(sizeA * sizeof(int));
    *resultSize = sizeA;

    for (i = 0; i < sizeA; i++) {
        if (A[i] % 2 == 0) {
            // Четный элемент: добавляем элемент + количество его вхождений в B
            count_in_B = count_occurrences(B, sizeB, A[i]);
            C[i] = A[i] + count_in_B;
        }
        else {
            // Нечетный элемент: добавляем без изменений
            C[i] = A[i];
        }
    }

    return C;
}

// ЗАДАНИЕ 2: Массив C, где после каждого элемента А вставлен ближайший по модулю элемент из массива В
// Интерпретация: Создаем массив C, чередуя элементы A и их ближайшие по модулю элементы из B
int* task2(const int* A, int sizeA, const int* B, int sizeB, int* resultSize) {
    int* C = NULL;
    int newSize;
    int index;
    int i;
    int closest;
    
    // Результирующий массив будет в два раза больше A (если sizeA > 0)
    newSize = (sizeA > 0) ? sizeA * 2 : 0;
    C = (int*)malloc(newSize * sizeof(int));
    *resultSize = newSize;

    index = 0;
    for (i = 0; i < sizeA; i++) {
        // Добавляем элемент из A
        C[index++] = A[i];

        // Добавляем ближайший по модулю элемент из B
        closest = find_closest_by_abs(B, sizeB, A[i]);
        C[index++] = closest;
    }

    return C;
}

// ЗАДАНИЕ 3: Массив C, где к каждому четному элементу А добавить минимальный элемент из B, а к нечетному - максимальный из B
// Интерпретация: Для каждого элемента A создаем новый элемент в C как сумму:
// - если элемент A четный: A[i] + min(B)
// - если элемент A нечетный: A[i] + max(B)
int* task3(const int* A, int sizeA, const int* B, int sizeB, int* resultSize) {
    int* C = NULL;
    int min_B;
    int max_B;
    int i;
    
    // Предварительно находим min и max в массиве B
    min_B = (sizeB > 0) ? find_min(B, sizeB) : 0;
    max_B = (sizeB > 0) ? find_max(B, sizeB) : 0;

    // Результирующий массив будет такого же размера, как A
    C = (int*)malloc(sizeA * sizeof(int));
    *resultSize = sizeA;

    for (i = 0; i < sizeA; i++) {
        if (A[i] % 2 == 0) {
            // Четный элемент: добавляем минимальный элемент из B
            C[i] = A[i] + min_B;
        }
        else {
            // Нечетный элемент: добавляем максимальный элемент из B
            C[i] = A[i] + max_B;
        }
    }

    return C;
}

// Основная функция для демонстрации работы
int main() {
    // Тестовые данные (общие для всех задач)
    int A[] = { 2, 3, 5, 7, 8, 10, 4, 6, 12, 15 };
    int B[] = { 3, 5, 8, 10, 3, 5, 7, 12, 15, 20 };
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
    
    // Для дополнительных тестов
    int A2[] = { 1, 2, 3 };
    int B2[] = {};
    int sizeA2;
    int sizeB2;
    int sizeC1b;
    int* C1b = NULL;
    int sizeC2b;
    int* C2b = NULL;
    int sizeC3b;
    int* C3b = NULL;
    
    // Для теста с отрицательными числами
    int A3[] = { -2, -3, -4, -5 };
    int B3[] = { -1, -2, -3, 0, 1, 2 };
    int sizeA3;
    int sizeB3;
    int sizeC1c;
    int* C1c = NULL;
    int sizeC2c;
    int* C2c = NULL;
    int sizeC3c;
    int* C3c = NULL;

    setlocale(LC_ALL, ("Rus"));

    // Вычисляем размеры массивов
    sizeA = sizeof(A) / sizeof(A[0]);
    sizeB = sizeof(B) / sizeof(B[0]);
    sizeA2 = sizeof(A2) / sizeof(A2[0]);
    sizeB2 = 0;
    sizeA3 = sizeof(A3) / sizeof(A3[0]);
    sizeB3 = sizeof(B3) / sizeof(B3[0]);

    printf("Исходные массивы:\n");
    print_array("A", A, sizeA);
    print_array("B", B, sizeB);
    printf("\n");

    // Задание 1
    printf("ЗАДАНИЕ 1:\n");
    printf("Массив C, где к каждому четному элементу А добавлено сколько раз этот элемент встречается в массиве В\n");
    printf("Интерпретация: Для четных элементов A[i] -> A[i] + count(A[i] in B)\n");
    printf("Для нечетных элементов A[i] -> A[i] (без изменений)\n");
    printf("Анализ:\n");
    printf("- Четные элементы A: 2, 8, 10, 4, 6, 12\n");
    printf("  count(2 in B) = 0 → 2 + 0 = 2\n");
    printf("  count(8 in B) = 1 → 8 + 1 = 9\n");
    printf("  count(10 in B) = 1 → 10 + 1 = 11\n");
    printf("  count(4 in B) = 0 → 4 + 0 = 4\n");
    printf("  count(6 in B) = 0 → 6 + 0 = 6\n");
    printf("  count(12 in B) = 1 → 12 + 1 = 13\n");
    printf("- Нечетные элементы A: 3, 5, 7, 15 (остаются без изменений)\n");
    printf("Ожидаемый результат C: [2, 3, 5, 7, 9, 11, 4, 6, 13, 15]\n");
    printf("Результат: ");
    C1 = task1(A, sizeA, B, sizeB, &sizeC1);
    print_array("C", C1, sizeC1);
    free(C1);
    printf("\n");

    // Задание 2
    printf("ЗАДАНИЕ 2:\n");
    printf("Массив C, где после каждого элемента А вставлен ближайший по модулю элемент из массива В\n");
    printf("Интерпретация: C = [A[0], ближайший_к_A[0], A[1], ближайший_к_A[1], ...]\n");
    printf("Анализ (ближайший по модулю элемент из B для каждого элемента A):\n");
    printf("A[0]=2 → ближайшие в B: |2-3|=1, |2-5|=3, |2-8|=6 → выбираем 3\n");
    printf("A[1]=3 → ближайшие в B: есть сам 3 → выбираем 3\n");
    printf("A[2]=5 → ближайшие в B: есть сам 5 → выбираем 5\n");
    printf("A[3]=7 → ближайшие в B: |7-7|=0, |7-8|=1 → выбираем 7\n");
    printf("A[4]=8 → ближайшие в B: есть сам 8 → выбираем 8\n");
    printf("A[5]=10 → ближайшие в B: есть сам 10 → выбираем 10\n");
    printf("A[6]=4 → ближайшие в B: |4-3|=1, |4-5|=1 → выбираем 3 (первый)\n");
    printf("A[7]=6 → ближайшие в B: |6-5|=1, |6-7|=1 → выбираем 5 (первый)\n");
    printf("A[8]=12 → ближайшие в B: есть сам 12 → выбираем 12\n");
    printf("A[9]=15 → ближайшие в B: есть сам 15 → выбираем 15\n");
    printf("Ожидаемый результат C: [2, 3, 3, 3, 5, 5, 7, 7, 8, 8, 10, 10, 4, 3, 6, 5, 12, 12, 15, 15]\n");
    printf("Результат: ");
    C2 = task2(A, sizeA, B, sizeB, &sizeC2);
    print_array("C", C2, sizeC2);
    free(C2);
    printf("\n");

    // Задание 3
    printf("ЗАДАНИЕ 3:\n");
    printf("Массив C, где к каждому четному элементу А добавить минимальный элемент из B, а к нечетному - максимальный из B\n");
    printf("Интерпретация: Для четных A[i]: C[i] = A[i] + min(B)\n");
    printf("               Для нечетных A[i]: C[i] = A[i] + max(B)\n");
    printf("Анализ:\n");
    printf("min(B) = 3, max(B) = 20\n");
    printf("- Четные элементы A: 2, 8, 10, 4, 6, 12\n");
    printf("  2 + 3 = 5\n");
    printf("  8 + 3 = 11\n");
    printf("  10 + 3 = 13\n");
    printf("  4 + 3 = 7\n");
    printf("  6 + 3 = 9\n");
    printf("  12 + 3 = 15\n");
    printf("- Нечетные элементы A: 3, 5, 7, 15\n");
    printf("  3 + 20 = 23\n");
    printf("  5 + 20 = 25\n");
    printf("  7 + 20 = 27\n");
    printf("  15 + 20 = 35\n");
    printf("Ожидаемый результат C: [5, 23, 25, 27, 11, 13, 7, 9, 15, 35]\n");
    printf("Результат: ");
    C3 = task3(A, sizeA, B, sizeB, &sizeC3);
    print_array("C", C3, sizeC3);
    free(C3);
    printf("\n");

    // Дополнительные тесты с пограничными случаями
    printf("\nДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ:\n");

    // Тест 1: Пустой массив B
    printf("\n1. Тест с пустым массивом B:\n");
    print_array("A", A2, sizeA2);
    print_array("B", B2, sizeB2);

    // Задание 1 с пустым B
    printf("Задание 1 (пустой B): ");
    C1b = task1(A2, sizeA2, B2, sizeB2, &sizeC1b);
    print_array("C", C1b, sizeC1b);
    free(C1b);

    // Задание 2 с пустым B
    printf("Задание 2 (пустой B): ближайший элемент будет 0 (по умолчанию)\n");
    printf("Результат: ");
    C2b = task2(A2, sizeA2, B2, sizeB2, &sizeC2b);
    print_array("C", C2b, sizeC2b);
    free(C2b);

    // Задание 3 с пустым B
    printf("Задание 3 (пустой B): min(B)=0, max(B)=0\n");
    printf("Результат: ");
    C3b = task3(A2, sizeA2, B2, sizeB2, &sizeC3b);
    print_array("C", C3b, sizeC3b);
    free(C3b);

    // Тест 2: Отрицательные числа
    printf("\n2. Тест с отрицательными числами:\n");
    print_array("A", A3, sizeA3);
    print_array("B", B3, sizeB3);

    // Задание 1 с отрицательными числами
    printf("Задание 1 (отрицательные): ");
    C1c = task1(A3, sizeA3, B3, sizeB3, &sizeC1c);
    print_array("C", C1c, sizeC1c);
    free(C1c);

    // Задание 2 с отрицательными числами (проверка модуля)
    printf("Задание 2 (отрицательные):\n");
    printf("Анализ ближайших по модулю:\n");
    printf("A[0]=-2 → ближайшие: |-2-(-2)|=0, |-2-(-1)|=1 → выбираем -2\n");
    printf("A[1]=-3 → ближайшие: |-3-(-3)|=0, |-3-(-2)|=1 → выбираем -3\n");
    printf("A[2]=-4 → ближайшие: |-4-(-3)|=1, |-4-(-2)|=2 → выбираем -3\n");
    printf("A[3]=-5 → ближайшие: |-5-(-3)|=2, |-5-(-2)|=3 → выбираем -3\n");
    printf("Результат: ");
    C2c = task2(A3, sizeA3, B3, sizeB3, &sizeC2c);
    print_array("C", C2c, sizeC2c);
    free(C2c);

    // Задание 3 с отрицательными числами
    printf("Задание 3 (отрицательные): min(B)=-3, max(B)=2\n");
    printf("Результат: ");
    C3c = task3(A3, sizeA3, B3, sizeB3, &sizeC3c);
    print_array("C", C3c, sizeC3c);
    free(C3c);

    return 0;
}
