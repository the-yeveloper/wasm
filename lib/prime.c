//
// Created by Evgeniy Vinogradov on 8/10/22.
//
int isPrime(int num) {
    for (int i = 2; i * i <= num; i++){
        if (num % i == 0)
            return 0;
    }

    return num > 1 ? 1 : 0;
}

