#include <stdio.h>
#include <inttypes.h>

uint64_t countNum(uint64_t num);

void fillingArr(uint64_t num, uint64_t size, uint8_t *arr);

uint64_t transformArrayToNum(uint8_t array[], uint64_t size);

uint64_t descendingOrder(uint64_t n);

void bubleSort(uint8_t * array, uint64_t size);

int main() {

    uint64_t num1 = 473928;
    uint64_t num2 = 42145;
    uint64_t num3 = 145263;
    uint64_t num4 = 123456789;
    uint64_t num5 = 0;
    uint64_t num6 = 1;
    uint64_t num7 = 1021;
    uint64_t num8 = 1469594179;

    uint64_t newNumber;

    newNumber = descendingOrder(num2);
    printf("%" PRId64 "\n", newNumber);

    newNumber = descendingOrder(num3);
    printf("%" PRId64 "\n", newNumber);

    newNumber = descendingOrder(num4);
    printf("%" PRId64 "\n", newNumber);

    newNumber = descendingOrder(num5);
    printf("%" PRId64 "\n", newNumber);

    newNumber = descendingOrder(num6);
    printf("%" PRId64 "\n", newNumber);

    newNumber = descendingOrder(num8);
    printf("%" PRId64 "\n", newNumber);


    return 0;
}

uint64_t descendingOrder(uint64_t n) {
    if (n < 10) { return n;}
    uint64_t size = countNum(n);
    uint8_t arr[size];
    fillingArr(n,size, arr);
    bubleSort(arr, size);
    uint64_t result = transformArrayToNum(arr, size);
    return result;
}

uint64_t countNum(uint64_t num) {
    uint64_t count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

void fillingArr(uint64_t num, uint64_t size, uint8_t *array) {
    for (uint64_t i = 0; i < size; ++i) {
        array[i] = (uint8_t) (num % 10);
        num /= 10;
    }
}

uint64_t transformArrayToNum(uint8_t *array, uint64_t size) {
    uint64_t result = 0;
    uint64_t multiplier = 1;
    for (uint64_t i = 0; i < size; ++i) {
        result += array[i] * multiplier;
        multiplier *= 10;
    }
    return result;
}

void bubleSort(uint8_t * array, uint64_t size){
    for (uint64_t i = 0; i < size - 1; i++) {
        for (uint64_t j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                uint8_t tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}
