#include <stdio.h>

struct Date {
    unsigned int year : 12;   // 0 ~ 4095
    unsigned int month : 4;   // 1 ~ 12
    unsigned int day : 5;     // 1 ~ 31
};

// 判断闰年
int is_leap(unsigned int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 计算当年第几天
int day_of_year(struct Date d) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap(d.year))
        days_in_month[1] = 29;

    int total = 0;
    for (int i = 0; i < d.month - 1; i++)
        total += days_in_month[i];
    total += d.day;
    return total;
}

int main() {
    struct Date today = {2026, 7, 23};
    printf("今天是 %u 年的第 %d 天\n", today.year, day_of_year(today));
    return 0;
}
