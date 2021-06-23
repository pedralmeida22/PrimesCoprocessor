#include <stdio.h>
#include <stdbool.h> 


bool primesCheck(int n){
    
    if(n <= 1){
        return false;
    }

    if(n == 2){
        return true;
    }

    int flag = 0;
    int i;
    for(i = 2; i <= n/2; i++){
        if(n % i == 0){
            flag = 1;
            break;
        }
    }
    if (flag == 0){
        return true;
    }
    return false;
}

void printArray(int* array, int size){
    int* p;
    for(p = array; p < array + size; p++){
        printf("%d\n", *p);
    }
}

void PrimesSw(int* dst, int* src, unsigned int size)
{
    int* p;
    for (p = src; p < src + size; p++, dst++) {
        
        bool temp = primesCheck(*p);
        if (temp){      // primo -> escreve o numero
            *dst = *p;
        }
        else{           // nao e primo -> escreve zero
            *dst = 0;
        }
    }
}

bool CheckPrimes(int* dst, int* src, unsigned int size){
    int* p;
    for (p = src; p < src + size; p++, dst++) {
        int res;
        bool temp = primesCheck(*p);
        if (temp){
            res = *p;
        }
        else{
            res = 0;
        }

        if(res != *dst){
            return false;
        }
    }

    return true;
}

int main() {
    printf("Hello World!\n");
    int src[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int dst[10];
    
    PrimesSw(dst, src, 10);
    
    printf("result:\n");
    printArray(dst, 10);

    printf("Checking result... %s\n", CheckPrimes(dst, src, 10) ? "Ok" : "Error");

    return 0;
}
