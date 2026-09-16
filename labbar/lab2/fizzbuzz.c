#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
void print_number(int num) {
     if(num % 5 == 0 && num % 3 == 0) {
        puts("FizzBuzzzzzz");
    }
    else if (num % 3 == 0){
        puts("Fizz");
    }
    else if(num % 5 == 0) {
        puts("Buzz");
    }

   
    else {
        printf("%d\n", num);
    }

}

int main(int argc, char *argv[]) {
    int T = atoi(argv[1]);
    for( int i = 1; i<= T; i++ ){
        print_number(i);
    }
    return 0;
}