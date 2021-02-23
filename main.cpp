//
// Created by xylx on 2021/2/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <unistd.h>
#include "tools.h"


//-------------------------- 王道计算机机试指南题目 -----------------------------//

//******************************* 穷举 *********************************

/*
 * 例题 2.1、【题目】abc
 * 设a,b,c均是0到9之间的数字，abc, bcc是两个三位数，且有abc + bcc = 532。
 * 求满足条件的所有a, b, c的值。
 * 提示：代数化简 abc+bcc = a*100+b*10+c + b*100+c*10+c = a*100+b*110+c*12 = 532
 */
/**
 * 求解a,b,c：设a,b,c均是0到9之间的数字，abc, bcc是两个三位数，且有abc + bcc = 532
 */
void findABC() {
    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            for (int k = 0; k <= 9; ++k) {
                if (i * 100 + j * 110 + k * 12 == 532) {   //判断
                    printf("%d %d %d\n", i, j, k);
                }
            }
        }
    }
}

/*
 * 例题 2.2、【题目】反序数
 * 设N是一个4位数，它的9倍恰好是其反序数(如1234的反序数是4321), 求N的值。
 * 提示：求余法求反序数
 */
/**
 * 求一个数字的反序数
 * @param x 待求数字
 * @return 反序数
 */
int reverseNumber(int x) {
    int temp = 0;
    while (x) {
        temp = temp * 10 + x % 10;
        x /= 10;
    }
    return temp;
}

/**
 * 求解4位数N，它的9倍恰好是其反序数
 */
void inverseNumber() {
    for (int i = 1000; i <= 1111; ++i) {
        if (i * 9 == reverseNumber(i)) {
            printf("%d\n", i);
        }
    }
}

/*
 * 例题 2.3、【题目】对称平方数
 * 打印所有不超过256,其平方具有对称性质的数。如2和11就是这样的数，因为2x2=4,11x11= 121。
 */
/**
 * 判断是否为回文数
 * @param x 待判断数字
 * @return 是否为回文数
 */
bool isPalindrome(int x) {
    if (x % 10 == 0 && x != 0) {    //能被十整除的非零数皆不是回文数
        return false;
    }
    int temp = 0;
    while (x > temp) {  //计算数值的后一半的对称值即可
        temp = temp * 10 + x % 10;
        x /= 10;
    }
    return x == temp || x == temp / 10; //比较前一半与后一半对称值是否相等
}

/**
 * 打印所有不超过256的对称平方数
 */
void symmetricSquare() {

    for (int i = 0; i <= 256; ++i) {
        if (i * i == reverseNumber(i * i)) {    //方法一
            printf("%d\n", i);
        }
        //if (isPalindrome(i * i)) {    //方法二
        //    printf("%d\n", i);
        //}
    }
}

/*
 * 习题 2.1、【题目】与7无关的数
 * 一个正整数，如果它能被7整除，或者它的十进制表示法中某个位数上的数字为7,那么称其为与7相关的数。
 * 现求所有小于等于n (n< 100)的与7无关的正整数的平方和。
 */
/**
 * 查找与7无关的数
 * @param n 范围上限
 */
void findIrrelevantSeven(int n) {
    if (n <= 0 || n >= 100) {
        return;
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i % 7 != 0 && i % 10 != 7 && i / 10 % 10 != 7) {
            sum += i * i;
        }
    }
    printf("%d\n", sum);
}

/*
 * 习题 2.2、【题目】百鸡问题
 * 用小于等于n元去买100只鸡，大鸡5元/只，小鸡3元/只，还有1/3 元每只的一种小鸡，分别记为x只、y只和z只。
 * 编程求解x, y,z所有可能的解。
 */
/**
 * 百鸡问题
 * @param n 上限钱数
 */
void calcChicken(int n) {
    for (int i = 0; i <= 100 && i <= n / 5; ++i) {
        for (int j = 0; j <= 100 && j <= n / 3; ++j) {
            int k = 100 - i - j;
            if (k >= 0 && 5 * i + 3 * j + 1.0 / 3 * k <= n) {
                printf("x=%d,y=%d,z=%d\n", i, j, k);
            }

        }
    }
}

/*
 * 习题 2.3、【题目】Old Bill
 * N只火鸡的价格为$_XYZ_，火鸡的总数N在1到99之间。
 * 价格由五位数组成，两边的数字由于褪色而看不清，所以只能看到中间的三位数。
 * 假设第一一个数字非零，每只火鸡的价格是整数，并且所有火鸡的价格相同。
 * 给定N,X,Y和Z,编写一个程序来猜测两边褪色的数字和火鸡的原始价格。
 * 如果有多个价格符合题意，那么输出最昂贵的那个。
 * 如果没有价格符合题意，那么输出0。
 * 提示：首位非零，求最贵的需要从大到小枚举；总价格=i * 10000 + x * 1000 + y * 100 + z * 10 + j
 */
/**
 * 推测火鸡价总价，并计算单价
 * @param n 火鸡个数
 * @param x 千位数字
 * @param y 百位数字
 * @param z 十位数字
 */
void guessBillPrice(int n, int x, int y, int z) {
    int flag = true;
    for (int i = 9; i >= 1; --i) {
        for (int j = 9; j >= 0; --j) {
            int price = i * 10000 + x * 1000 + y * 100 + z * 10 + j;
            if (price % n == 0) {
                printf("%d %d %d\n", i, j, price / n);
                flag = false;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }
    if (flag) {
        printf("0\n");
    }
}


//******************************* 模拟 *********************************

/*
 * 例题 2.4、【题目】输出梯形
 * 输入一个高度h(1<=h<=1000),输出一个高度为h、上底边长度为h的梯形。
 */
/**
 * 输出梯形
 * @param h 上底和高长度
 */
void trapezoidPrint(int h) {
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= h * 2 - 2 * i; ++j) {
            printf(" ");
        }
        for (int j = 1; j <= h + 2 * (i - 1); ++j) {
            printf("*");
        }
        printf("\n");
    }
}

/*
 * 例题 2.5、【题目】叠筐
 * 把一个个大小差-一圈的管叠上去，使得从上往下看时，边筐花色交错。
 * 输入是一个个三元组，分别是:外筐尺寸n (n为满足0<n<80的奇整数)，中心花色字符，外筐花色字符，后二者都为ASCII可见字符。
 * 输出叠在一起的筐图案，中心花色与外筐花色字符从内层起交错相叠，多筐相叠时，最外管的角总是被打磨掉。
 * 叠筐与叠筐之间应有行间隔。
 */
/**
 * 递归处理叠筐
 * @param str 保存上一次的叠筐状态的字符串数组（初始n个全为内部字符）
 * @param n 行数（奇数）
 * @param i 当前行（初始0）
 * @param in 内部字符
 * @param out 外部字符
 */
void stackingBasketsRecursion(const char str[], int n, int i, char in, char out) {

    //复制数组并翻转中间几位
    char temp[100] = {0};
    int len = strlen(str);
    for (int j = 0; j <= len; ++j) {
        if (j >= i && j <= len - 1 - i) {   //一定需要翻转的区间
            if (str[j] == out) {
                temp[j] = in;
            } else {      //翻转
                temp[j] = out;
            }
        } else {                            //可能不需要翻转的区间
            if (str[j] == ' ') {               //空字符翻转为外筐字符（首尾行去角后产生）
                temp[j] = out;
            } else {                         //其他字符直接复制
                temp[j] = str[j];
            }
        }
    }

    if (i == 0 && n > 1) {  //多行的首尾行去角
        temp[0] = temp[n - 1] = ' ';
    }

    //上下对称输出
    puts(temp);
    if (i == n / 2) {   //到达中间，结束递归深入
        return;
    } else {        //未到达中间，继续深入递归
        stackingBasketsRecursion(temp, n, i + 1, in, out);
        puts(temp);
    }
}

/**
 * 输出叠筐图形
 * @param n 行数
 * @param in 内部字符
 * @param out 外部字符
 */
void stackingBaskets(int n, char in, char out) {
    char str[100] = {0};                    //当前行字符数组
    if (n < 1 || n % 2 != 1 || n > 80) {    //非法数值
        return;
    } else {                                //合法行数
        for (int i = 0; i < n; ++i) {      //初始化当前行字符数组
            str[i] = in;                    //因为递归先翻转，后输出，所以要全部初始化为筐的内部字符
        }
        str[n] = '\0';                      //存为字符串，方便puts输出
        stackingBasketsRecursion(str, n, 0, in, out);
    }
}

/*
 * 习题 2.4、【题目】Repeater
 * 以图构图。
 * 第一行包含一个正整数N，代表模板的大小为N * N（N只能是3、4或5）。
 * 接下来的N行描述了模板。
 * 下一行包含一个正整数Q，它是图片的比例级别。
 * 输入以N = 0结束。
 * 保证一张图片的大小不会超过3000 * 3000。
 */


/*
 * 习题 2.5、【题目】Hello World for U
 */


//******************************* 日期 *********************************

/*
 * 例题 2.6、【题目】今年的第几天？
 * 输入年、月、日，计算该天是本年的第几天。
 */
/**
 * 计算该天是本年的第几天
 * @param year 年份
 * @param month 月份
 * @param day 日
 */
void calcDaysOfYear(int year, int month, int day) {
    //c99
    int monthDays[13] = { //每月天数
            [1]=31, [3]=31, [5]=31, [7]=31, [8]=31, [10]=31, [12]=31,
            [4]=30, [6]=30, [9]=30, [11]=30,
            [2]=28
    };

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) { //判断闰年
        monthDays[2] += 1;
    }

    int sum = 0;  //累计天数
    for (int i = 1; i < month; ++i) {   //前几个月天数和
        sum += monthDays[i];
    }
    sum += day;   //当月天数

    printf("%d\n", sum);
}

/*
 * 例题 2.7、【题目】打印日期
 * 给出年份和此年中的第几天，算出这天是几月几号。
 */
/**
 * 给出年份和此年中的第几天，算出这天是几月几号
 * @param year 年份
 * @param n 第几天
 */
void calcDateOfYear(int year, int n) {
    //c99
    int monthDays[13] = { //每月天数
            [1]=31, [3]=31, [5]=31, [7]=31, [8]=31, [10]=31, [12]=31,
            [4]=30, [6]=30, [9]=30, [11]=30,
            [2]=28
    };

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {  //闰年判断
        monthDays[2] += 1;
    }

    int sum = 0;  //累计天数
    for (int i = 1; i <= 12; ++i) {  //月
        for (int j = 1; j <= monthDays[i]; ++j) { //日
            sum++;
            if (sum == n) {    //到达指定天数，输出对应日期
                printf("%d-%02d-%02d\n", year, i, j);
                return;
            }
        }
    }
}

/*
 * 例题 2.8、【题目】日期累加
 * 计算一个日期加上若干天后的日期。
 * 注意：考虑跨年！！！
 */
/**
 * 计算一个日期加上若干天后的日期
 * @param year 年份
 * @param month 月份
 * @param day 日
 * @param interval 间隔天数
 */
void calcDateAfterDate(int year, int month, int day, int interval) {
    //c99
    int monthDays[13] = { //每月天数
            [1]=31, [3]=31, [5]=31, [7]=31, [8]=31, [10]=31, [12]=31,
            [4]=30, [6]=30, [9]=30, [11]=30,
            [2]=28
    };

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {  //闰年判断
        monthDays[2] += 1;
    }

    int sum = 0;
    for (int i = month; i <= 12; ++i) {
        for (int j = 1; j <= monthDays[i]; ++j) {
            sum++;
            if (sum - day == interval) {
                printf("%d-%02d-%02d\n", year, i, j);
                return;
            }
        }
    }
    //考虑跨年
    calcDateAfterDate(year + 1, 1, 1, interval - (sum - day) - 1);
}

/*
 * 习题 2.6、【题目】日期差值
 * 有两个日期，求两个日期之间的天数，如果两个日期是连续的，则规定它们之间的天数为两天。
 */
/**
 * 求两个日期之间的天数（正数）
 * @param date1 日期一
 * @param date2 日期二
 */
void calcDateGap(int date1, int date2) {
    //c99
    int monthDays[13] = { //每月天数
            [1]=31, [3]=31, [5]=31, [7]=31, [8]=31, [10]=31, [12]=31,
            [4]=30, [6]=30, [9]=30, [11]=30,
            [2]=28
    };

    //分解得年月日
    int d1 = date1 % 100;
    int d2 = date2 % 100;
    int m1 = date1 / 100 % 100;
    int m2 = date2 / 100 % 100;
    int y1 = date1 / 10000;
    int y2 = date2 / 10000;

    if (y1 > y2) {         //1存小日期，2存大日期
        int temp = y1;
        y1 = y2;
        y2 = temp;
        temp = m1;
        m1 = m2;
        m2 = temp;
        temp = d1;
        d1 = d2;
        d2 = temp;
    }

    int sum1 = 0;     //累计中间经历几年的天数
    for (int i = y1; i < y2; ++i) {
        sum1 += 365;
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
            sum1 += 1;
        }
    }

    if ((y1 % 4 == 0 && y1 % 100 != 0) || y1 % 400 == 0) {
        monthDays[2] += 1;
    }
    int sum2 = 0;     //累计小日期本年已度过天数
    for (int i = 1; i < m1; ++i) {
        sum2 += monthDays[i];
    }
    sum2 += d1;

    monthDays[2] = 28;    //重置2月天数

    if ((y2 % 4 == 0 && y2 % 100 != 0) || y2 % 400 == 0) {
        monthDays[2] += 1;
    }
    int sum3 = 0;     //累计大日期本年已度过天数
    for (int i = 1; i < m2; ++i) {
        sum3 += monthDays[i];
    }
    sum3 += d2;

    printf("%d\n", sum1 + sum3 - sum2 + 1);
}

/*
 * 习题 2.7、【题目】Day of Week
 * 编写一个程序，计算给定的日期是周几。
 * 提示：蔡勒公式！！！
 */
void calcDayOfWeek(int year, const char *month, int day) {

    //月份映射
    char *months[15] = {
            [3]="March", "April", "May", "June", "July", "August",
            "September", "October", "November", "December", "January", "February"
    };
    //星期映射
    char *week[7] = {
            "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };

    int m = 0;  //月份
    for (int i = 3; i < 15; ++i) {
        if (!strcmp(month, months[i])) {
            m = i;
            break;
        }
    }
    if (m > 12) {   //本年1，2月需要视为去年13，14月
        year--;
    }

    int c = year / 100, y = year % 100; //上个世纪，本年后两位
    int w = (y + y / 4 + c / 4 - 2 * c + (26 * (m + 1) / 10) + day - 1) % 7;    //蔡勒公式
    printf("%s\n", week[w]);
}

/*
 * 习题 2.8、【题目】日期类
 * 编写一个日期类，要求按xxxx-xx-xx的格式输出日期，实现加一天的操作。
 */
void dateClass(){
    //c99
    int monthDays[13] = { //每月天数
            [1]=31, [3]=31, [5]=31, [7]=31, [8]=31, [10]=31, [12]=31,
            [4]=30, [6]=30, [9]=30, [11]=30,
            [2]=28
    };

}



int main() {

    double start, end;
    start = getTime();

    //findABC();
    //inverseNumber();
    //symmetricSquare();
    //findIrrelevantSeven(10);
    //calcChicken(40);
    //guessBillPrice(84, 6, 7, 5);
    //trapezoidPrint(4);
    //stackingBaskets(1,'B','A');
    //stackingBaskets(5,'B','A');
    //stackingBaskets(11,'$','*');
    //calcDaysOfYear(1990,9,20);
    //calcDaysOfYear(2000,5,1);
    //calcDateOfYear(2000,3);
    //calcDateOfYear(2000,31);
    //calcDateOfYear(2000,40);
    //calcDateOfYear(2000,60);
    //calcDateOfYear(2000,61);
    //calcDateOfYear(2001,60);
    //calcDateAfterDate(2008, 2, 3, 100);
    //calcDateAfterDate(2008, 2, 3, 1000);
    //calcDateGap(20110412,20110422);
    calcDayOfWeek(2001, "October", 14);
    //calcDayOfWeek(2021, "February", 23);


    end = getTime();
    printf("\ntime spend:%f ms\n", (end - start));

    return 0;
}
