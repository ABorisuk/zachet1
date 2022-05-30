#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SHIFT 48
#define CARRY 10

int my_sum(int *total, int *next, int n_total, int n_next, int next_sign,
           int *total_sign);
void reverse(int *array, int N);
int main(void)
{
    char a;
    int *total = malloc(1 * sizeof(int));
    total[0] = 0;
    int max_count = 1;
    int total_sign = 0;
    int *next = malloc(1 * sizeof(int));
    while (1) {
        int flag = 0;
        int count = 0;
        int next_sign = 0;
        while (1) {
            if (scanf("%c", &a) != 1) {
                flag = 1;
                break;
            }
            if (a == ' ' || a == '\n' || a == '\t') {
                break;
            }
            if (a == '-') {
                next_sign = 1;
                scanf("%c", &a);
            }
            next = realloc(next, (count + 1) * sizeof(int));
            next[count] = a - SHIFT;
            count++;
        }
        reverse(next, count);
        max_count =
            my_sum(total, next, max_count, count, next_sign, &total_sign);

        if (flag == 1) {
            break;
        }
    }
    printf("|");
    for (int i = 0; i < max_count; i++) {
        printf("%d", total[i]);
    }
    printf("|");
    printf("%d\n", total_sign);
    free(total);
    free(next);
}

int my_sum(int *total, int *next, int n_total, int n_next, int next_sign,
           int *total_sign)
{
    int N = 0;
    int ltotal_sign = *total_sign;
    if (ltotal_sign == 1 && next_sign == 1) {
        next_sign = 0;
    }
    if (ltotal_sign == 1 && next_sign == 0) {
        next_sign = 1;
    }
    if (n_total > n_next) {
        next = realloc(next, n_total * sizeof(int));
        N = n_total;
        for (int i = n_next; i < n_total; i++) {
            next[i] = 0;
        }
    } else if (n_next > n_total) {
        total = realloc(total, n_next * sizeof(int));
        N = n_next;
        for (int i = n_total; i < n_next; i++) {
            total[i] = 0;
        }
    } else {
        N = n_total;
    }
    if (next_sign) {
        int carry = 0;
        int which = 0;
        for (int i = 0; i < N; i++) {
            if (next[N - 1 - i] > total[N - 1 - i]) {
                which = 1;
                break;
            }
        }
        if (which == 1) {
            for (int i = 0; i < N; i++) {
                int tmp = next[i];
                next[i] = total[i];
                total[i] = tmp;
                *total_sign = 1;
                if (ltotal_sign == 1) {
                    *total_sign = 0;
                }
            }
        }
        for (int i = 0; i < N; i++) {
            total[i] -= carry;
            if (total[i] < next[i]) {
                carry++;
                total[i] += CARRY;
            }
            total[i] -= next[i];
        }
        return N;
    }
    int carry = 0;
    for (int i = 0; i < N; i++) {
        int tmp = total[i] + next[i] + carry;
        carry = (tmp - tmp % CARRY) / CARRY;
        total[i] = tmp - carry * CARRY;
    }
    int ttmp = carry;
    int count = 0;
    while (ttmp != 0) {
        count++;
        ttmp /= CARRY;
    }
    total = realloc(total, (N + count) * sizeof(int));
    for (int i = N; i < N + count; i++) {
        total[i] = carry % CARRY;
        carry /= CARRY;
    }
    return N + count;
}

void reverse(int *array, int N)
{
    for (int i = 0; i < N / 2; i++) {
        int tmp = array[N - i - 1];
        array[N - i - 1] = array[i];
        array[i] = tmp;
    }
}
