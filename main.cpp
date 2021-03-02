//
// Created by xylx on 2021/2/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

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
/**
 * 计算给定的日期是周几(蔡勒公式)
 * @param year 年
 * @param month 月
 * @param day 日
 */
void calcDayOfWeek(int year, const char *month, int day) {

    //月份映射
    const char *months[15] = {
            [3]="March", "April", "May", "June", "July", "August",
                         "September", "October", "November", "December", "January", "February"
    };
    //星期映射
    const char *week[7] = {
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
/**
 * 按xxxx-xx-xx的格式输出日期，实现加一天的操作。
 * @param year 年
 * @param month 月
 * @param day 日
 */
void dateClass(int year, int month, int day) {
    //c99
    int monthDays[13] = { //每月天数
            [1]=31, [3]=31, [5]=31, [7]=31, [8]=31, [10]=31, [12]=31,
            [4]=30, [6]=30, [9]=30, [11]=30,
            [2]=28
    };
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        monthDays[2] += 1;
    }

    if (day + 1 > monthDays[month]) {    //跨月
        month += 1;
        day = 1;
        if (month > 12) {              //跨年
            year += 1;
            month = 1;
        }
    } else {                         //不跨月
        day += 1;
    }

    printf("%04d-%02d-%02d\n", year, month, day);
}


//******************************* 其他模拟 *********************************
/*
 * 例题 2.9、【题目】略
 */

/*
 * 例题 2.10、【题目】手机键盘
 * 按照手机键盘输入字母的方式，计算所花费的时间
 * 如：a,b,c都在“1”键上，输入a只需要按一次，输入c需要连续按三次。
 * 如果连续两个字符不在同一个按键上，则可直接按，如：ad需要按两下，kz需要按6下。
 * 如果连续两字符在同一个按键上，则两个按键之间需要等一段时间，如ac，在按了a之后，需要等一会儿才能按c。
 * 现在假设每按一次需要花费一个时间段，等待时间需要花费两个时间段。
 * 现在给出一串字符，需要计算出它所需要花费的时间。
 */
/**
 * 按照手机键盘输入字母的方式，计算所花费的时间
 * @param str 待输入的字符串
 */
void calcInputTime(const char *str) {
    if (!str || str[0] == '\0') {
        return;
    }
    //映射每个字母键入需要的时间
    int times[26] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4};

    int len = strlen(str);
    int t = times[str[0] - 'a'];    //累计时间，初始化为第一个字符键入时间
    for (int i = 1; i < len; ++i) { //累计后续所有字符需要的键入时间
        t += times[str[i] - 'a'];   //第i个字符键入所需时间
        // 前后字符在同一按键上需要加时间间隔
        if (str[i] - str[i - 1] == times[str[i] - 'a'] - times[str[i - 1] - 'a']) {    //前后字符同键
            t += 2;
        }
    }
    printf("%d\n", t);
}

/*
 * 例题 2.11、【题目】xxx定律(卡拉兹猜想)
 * 对于一个数n，如果是偶数，就把n砍掉一半；如果是奇数，把n变成 3*n+1后砍掉一半，直到该数变为1为止。
 * 请计算需要经过几步才能将n变到1，
 */
void calcCallatz(int n) {
    int t = 0;
    while (n != 1) {
        if (n % 2) {
            n = (3 * n + 1) / 2;
        } else {
            n /= 2;
        }
        t++;
    }
    printf("%d\n", t);
}

/*
 * 习题 2.9、【题目】
*/

/*
 * 习题 2.10、【题目】
*/

/*
 * 习题 2.11、【题目】
*/



//******************************* 排序 *********************************

/*
 * 例题 3.1、【题目】排序
 * 对输入的n个数排序并输出。
*/
/**
 * 用于排序的比较函数
 * @param a 值
 * @param b 值
 * @return 升序：a>b返回正数，a==b返回0,a<b返回负数；降序反之
 */
int compare(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

/**
 * 对输入的n个数排序并输出
 * @param arr 待排序数组
 * @param n 元素个数
 */
void sortN(int arr[], int n) {

    //qsort(arr,n, sizeof(int),compare);        //c排序函数

    std::sort(arr, arr + n);               //c++排序函数（更方便）

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
}

/*
 * 例题 3.2、【题目】成绩排序
 * 用一维数组存储学号和成绩，然后按成绩排序输出。
*/
typedef struct student1 {
    int no;
    int score;
} STU1;

/**
 * 用于排序的比较函数（true：a,b; false:b,a）
 * @param a
 * @param b
 * @return
 */
bool compareByScoreAndNo(STU1 a, STU1 b) {
    if (a.score == b.score) {
        return a.no < b.no;
    } else {
        return a.score < b.score;
    }
}

/**
 * 按照成绩排序
 * @param students
 * @param n
 */
void sortScore1(STU1 students[], int n) {
    std::sort(students, students + n, compareByScoreAndNo);
    for (int i = 0; i < n; ++i) {
        printf("%d %d\n", students[i].no, students[i].score);
    }
}

/*
 * 例题 3.3、【题目】成绩排序
 * 输入任意(用户，成绩)序列，可以获得成绩从高到低或从低到高的排列，相同成绩都按先录入者排列在前的规则处理。
 * 输入多行，首先输入要排序的人的个数，然后输入排序方法0 (降序)或1 (升序),再分别输入他们的名字和成绩，以一个空格隔开。
*/
typedef struct student2 {
    char name[100];
    int no;
    int score;
} STU2;

/**
 * 用于升序排序的比较函数（true：a,b; false:b,a）
 * @param a
 * @param b
 * @return
 */
bool compareByScoreAndNoAscending(STU2 a, STU2 b) {
    if (a.score == b.score) {
        return a.no < b.no;
    } else {
        return a.score < b.score;
    }
}

/**
 * 用于降序排序的比较函数（true：a,b; false:b,a）
 * @param a
 * @param b
 * @return
 */
bool compareByScoreAndNoDescending(STU2 a, STU2 b) {
    if (a.score == b.score) {
        return a.no < b.no;
    } else {
        return a.score > b.score;
    }
}

/**
 * 按成绩排序
 * @param students
 * @param n
 * @param type 排序类型
 */
void sortScore2(STU2 students[], int n, int type) {
    if (type) {
        std::sort(students, students + n, compareByScoreAndNoAscending);
    } else {
        std::sort(students, students + n, compareByScoreAndNoDescending);
    }

    for (int i = 0; i < n; ++i) {
        printf("%s %d %d\n", students[i].name, students[i].no, students[i].score);
    }
}

/*
 * 习题 3.1、【题目】特殊排序
 * 输入一系列整数，将其中最大的数挑出输出(有多个最大数时，挑出一个即可)，并对剩下的数排序，如果无剩下的数，那么输出-1。
*/
/**
 * 输入一系列整数,将其中最大的数挑出输出(有多个最大数时，挑出一个即可)，并对剩下的数排序输出,如果无剩下的数，那么输出-1。
 * @param a
 * @param n 元素个数
 */
void sortAndDeleteMax(int a[], int n) {
    if (n == 1) {
        printf("%d\n-1\n", a[0]);
    } else {
        std::sort(a, a + n);
        printf("%d\n", a[n - 1]);
        for (int i = 0; i < n - 1; ++i) {
            printf("%d ", a[i]);
        }
    }
}

/*
 * 习题 3.2、【题目】整数奇偶排序
 * 输入10个整数，彼此以空格分隔。重新排序以后输出(也按空格分隔)，要求:
 * 1.先输出其中的奇数,并按从大到小排列；
 * 2.然后输出其中的偶数,并按从小到大排列。
*/
void sortEvenOdd(int a[], int n) {
    std::sort(a, a + n);
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] % 2) {
            printf("%d ", a[i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] % 2 == 0) {
            printf("%d ", a[i]);
        }
    }
}

/*
 * 习题 3.3、【题目】小白鼠排队
 * N只小白鼠(1 <= N <= 100)，每只鼠头上戴着一顶有颜色的帽子。
 * 现在称出每只白鼠的重量，要求按照白鼠重量从大到小的顺序输出它们头上帽子的颜色。
 * 帽子的颜色用“red”，“blue”等字符串来表示。不同的小白鼠可以戴相同颜色的帽子。
 * 白鼠的重量用整数表示。
*/
typedef struct mouse {
    int weight;
    char color[20];
} Mouse;

bool compareMouse(Mouse a, Mouse b) {
    return a.weight > b.weight;
}

void mouseQueue(Mouse m[], int n) {
    std::sort(m, m + n, compareMouse);
    for (int i = 0; i < n; ++i) {
        printf("%s\n", m[i].color);
    }
}


/*
 * 习题 3.4、【题目】奥运排序问题
*/


//******************************* 查找 *********************************

/*
 * 例题 3.4、【题目】找x
 * 输入一个数n，然后输入n个数值各不相同，再输入一个值x，输出这个值在这个数组中的下标（从0开始，若不在数组中则输出-1）。
*/
void findX(int a[], int n, int x) {
    for (int i = 0; i < n; ++i) {
        if (a[i] == x) {
            printf("%d\n", i);
            return;
        }
    }
    printf("-1\n");
}

/*
 * 例题 3.4、【题目】查找
 * 输入数组长度 n 输入数组 a[1...n] 输入查找个数 m 输入查找数字 b[1...m] ，输出 YES or NO ，查找有则YES 否则NO 。
*/
void findMany(int a[], int n, int b[], int m) {

    for (int i = 0; i < m; ++i) {
        int l = 0, h = n - 1, mid;
        while (l <= h) {
            mid = (l + h) / 2;
            if (a[mid] == b[i]) {
                printf("YES\n");
                break;
            } else if (a[mid] < b[i]) {
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        }
        if (l > h) {
            printf("NO\n");
        }
    }
}

/*
 * 习题 3.5、【题目】找最小数
 * 第一行输入一个数n，1 <= n <= 1000，下面输入n行数据，每一行有两个数，分别是x y。
 * 输出一组x y，该组数据是所有数据中x最小，且在x相等的情况下y最小的。
*/
typedef struct twoNum {
    int x;
    int y;
} TwoNum;

/**
 * 比较函数，优先x最小，再取y最小
 * @param a
 * @param b
 * @return
 */
bool compareXY(TwoNum a, TwoNum b) {
    if (a.x == b.x) {
        return a.y < b.y;
    } else {
        return a.x < b.x;
    }
}

/**
 * 查找最小数对
 * @param a
 * @param n
 */
void findMin1(TwoNum a[], int n) {

    std::sort(a, a + n, compareXY);
    printf("%d %d\n", a[0].x, a[0].y);
}

/**
 * 查找最小数对（在线处理）
 */
void findMin2() {
    int n;
    while (scanf("%d", &n) == 1) {
        int x, y;
        int minx = INT32_MAX, miny = INT32_MAX;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &x, &y);
            //在线处理
            if (x < minx) {
                minx = x;
                miny = y;
            } else if (x == minx && y < miny) {
                miny = y;
            }
        }
        printf("%d %d\n", minx, miny);
    }
}

/*
 * 习题 3.6、【题目】打印极值点下标
 * 在一个整数数组上，对于下标为i的整数，如果它大于所有它相邻的整数，或者小于所有它相邻的整数，
 * 则称为该整数为一个极值点，极值点的下标就是i。
*/
/**
 * 打印极值点下标
 * @param a
 * @param n
 */
void findExtremePoint(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        if ((i == 0 && a[1] != a[0]) || (i == n - 1 && a[n - 2] != a[n - 1]) || (a[i - 1] < a[i] && a[i] > a[i + 1]) ||
            (a[i - 1] > a[i] && a[i] < a[i + 1])) {
            printf("%d ", i);
        }
    }
    printf("\n");
}


/*
 * 习题 3.7、【题目】找位置
 * 对给定的一个字符串，找出有重复的字符，并给出其位置。
*/
typedef struct nodeStr {
    int no;     //下标
    int order;  //出现的次序
    char c;     //字符
} NodeStr;

bool compareCharNode(NodeStr a, NodeStr b) {
    if (a.c == b.c) {   //同一字符，按照下标排序
        return a.no < b.no;
    } else {            //不同字符，按照出现的次序排序
        return a.order < b.order;
    }
}

/**
 * 对给定的一个字符串，找出有重复的字符，并给出其位置
 * @param str
 */
void findRepeatCharLocation(const char *str) {

    int hash[256] = {0};    //保存每个字符首次出现的次序
    int len = strlen(str);
    int count = 0;          //计数是第几个不同字符
    NodeStr ns[len];
    for (int i = 0; i < len; ++i) {     //映射
        if (hash[str[i]]) {             //出现一个重复字符，使用首次出现的次序
            ns[i].order = hash[str[i]];
        } else {                        //出现一个新字符，更新该字符的首次次序记录，并使用当前次序
            count++;
            ns[i].order = hash[str[i]] = count;
        }
        ns[i].no = i;
        ns[i].c = str[i];
    }
    std::sort(ns, ns + len, compareCharNode);   //排序
    for (int i = 0; i < len; ++i) {                 //输出
        //临近字符相同则是重复字符需要输出，否则跳过
        bool flag = i < len - 1 && ns[i].c == ns[i + 1].c;
        if ((i > 0 && ns[i - 1].c == ns[i].c) || flag) {
            printf("%c:%d", ns[i].c, ns[i].no);
            if (flag) {                     //下一个字符相同，输出逗号分隔
                printf(",");
            } else {                        //下一个字符不同，输出换行分隔
                printf("\n");
            }
        }
    }
}


//******************************* 字符串 *********************************

/*
 * 例题 4.1、【题目】特殊乘法
 * 写个算法，对2个小于1000000000的输入，求结果。
 * 特殊乘法举例：123 * 45 = 1*4 +1*5 +2*4 +2*5 +3*4+3*5
*/
void specialMultiplication(const char *a, const char *b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int sum = 0;
    for (int i = 0; i < lenA; ++i) {
        for (int j = 0; j < lenB; ++j) {
            sum += (a[i] - '0') * (b[j] - '0');
        }
    }
    printf("%d\n", sum);
}

/*
 * 例题 4.2、【题目】密码翻译
 * 我们给出一种最简的的加密方法，对给定的一个字符串，
 * 把其中从a-y,A-Y的字母用其后继字母替代，把z和Z用a和A替代，则可得到一个简单的加密字符串。
*/
void encodeStr(const char *str) {
    char result[100];
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        if (('a' <= str[i] && str[i] <= 'y') || ('A' <= str[i] && str[i] <= 'Y')) {
            result[i] = str[i] + 1;
        } else if ('z' == str[i] || 'Z' == str[i]) {
            result[i] = str[i] - 25;
        } else {
            result[i] = str[i];
        }
    }
    result[len] = '\0';
    puts(result);
}

/*
 * 例题 4.3、【题目】简单密码
 * Julius Caesar曾经使用过一种很简单的密码。
 * 对于明文中的每个字符，将它用它字母表中后5位对应的字符来代替，这样就得到了密文。
 * 比如字符A用F来代替。如下是密文和明文中字符的对应关系。
 * 密文 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
 * 明文 V W X Y Z A B C D E F G H I J K L M N O P Q R S T U
 * 你的任务是对给定的密文进行解密得到明文。
 * 你需要注意的是，密文中出现的字母都是大写字母。
 * 密文中也包括非字母的字符，对这些字符不用进行解码。
*/
/**
 * 凯撒密码，解密
 * @param str
 */
void caesarDecode(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        //方法一：循环移位，统一处理
        if ('A' <= str[i] && str[i] <= 'Z') {
            putchar((str[i] - 'A' - 5 + 26) % 26 + 'A');
        } else {
            putchar(str[i]);
        }

        //方法二：判断区间，分类处理
        // if ('A' <= str[i] && str[i] <= 'E') {
        //     putchar(str[i] + 21);
        // } else if ('F' <= str[i] && str[i] <= 'Z') {
        //     putchar(str[i] - 5);
        // } else {
        //     putchar(str[i]);
        // }
    }
    putchar('\n');
}

/**
 * 凯撒密码，加密
 * @param str
 */
void caesarEncode(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        //方法一：循环移位，统一处理
        if ('A' <= str[i] && str[i] <= 'Z') {
            putchar((str[i] - 'A' + 5) % 26 + 'A');
        } else {
            putchar(str[i]);
        }

        //方法二：判断区间，分类处理
        // if ('V' <= str[i] && str[i] <= 'Z') {
        //     putchar(str[i] - 21);
        // } else if ('A' <= str[i] && str[i] <= 'U') {
        //     putchar(str[i] + 5);
        // } else {
        //     putchar(str[i]);
        // }
    }
    putchar('\n');
}

/* 扩展：【题目】文本替换加密
 * 加密规则：明文中小写字母用其后面的第a个字母替换（a<26），大写字母用其后面的第b个字母替换（b<26），
 * 可将字母表看成是首尾相接的。例如a=3，字母‘c’替换成‘f’，字母‘y’替换成‘b’。
 * 解密规则：输入密钥（加密用到的数字a和b），将密文中小写字母用其前面的第a个字母替换，大写字母用其前面的第b个字母替换，
 * 可将字母表看成是首尾相接的。
 * 解密过程是加密过程的逆过程，请编程实现这个过程，其中加密和解密过程分别用函数encode()和decode()实现。
 * （要求函数参数采用指针变量实现，main()函数中键盘输入明文和2个密钥，
 * 然后调用encode()和decode()函数分别输出加密后的密文及再将其解密后的文本。）
 */
char *encode(const char *str, int a, int b) {
    int len = strlen(str);
    char *result = (char *) malloc(sizeof(char) * len);
    for (int i = 0; i < len; ++i) {
        if ('a' <= str[i] && str[i] <= 'z') {
            result[i] = (str[i] - 'a' + a) % 26 + 'a';
        } else if ('A' <= str[i] && str[i] <= 'Z') {
            result[i] = (str[i] - 'A' + b) % 26 + 'A';
        } else {
            result[i] = str[i];
        }
    }
    return result;
}

char *decode(const char *str, int a, int b) {
    int len = strlen(str);
    char *result = (char *) malloc(sizeof(char) * len);
    for (int i = 0; i < len; ++i) {
        if ('a' <= str[i] && str[i] <= 'z') {
            result[i] = (str[i] - 'a' - a + 26) % 26 + 'a';
        } else if ('A' <= str[i] && str[i] <= 'Z') {
            result[i] = (str[i] - 'A' - b + 26) % 26 + 'A';
        } else {
            result[i] = str[i];
        }
    }
    return result;
}


//*******************************  *********************************

/*
 * 例题 5.1、【题目】
 *
*/



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
    //calcDayOfWeek(2001, "October", 14);
    //calcDayOfWeek(2021, "February", 23);
    //dateClass(1999,10,20);
    //dateClass(1999,12,31);
    //dateClass(2000,2,28);
    //dateClass(2000,2,29);
    //calcInputTime("bob");
    //calcInputTime("www");
    //calcCallatz(3);
    //calcCallatz(1);
    // int a[] = {9, 7, 3, 5, 1};
    // sortN(a, 5);
    // STU1 s[] = {{1, 10},
    //            {2, 5},
    //            {3, 20},
    //            {4, 15},
    //            {5, 10}};
    // sortScore1(s, 5);
    // STU2 s[] = {{"asd1",1, 10},
    //             {"asd2",2, 5},
    //             {"asd3",3, 20},
    //             {"asd4",4, 15},
    //             {"asd5",5, 10}};
    // sortScore2(s, 5,0);
    // sortScore2(s, 5,1);
    // int a[] = {9, 7, 3, 5, 1};
    // sortAndDeleteMax(a,5);
    // int a[10]={47,13,11,7,3,0 ,4, 12 ,34, 98};
    // sortEvenOdd(a,10);
    // Mouse m[]={{20,"red"},
    //            {12,"blue"},
    //            {35,"green"}};
    // mouseQueue(m,3);
    // int a[]={1,2,3,4,5};
    // findX(a,5,6);
    // int a[] = {1, 5, 2, 4, 3};
    // int b[] = {2, 5, 6};
    // std::sort(a,a+5);
    // findMany(a, 5, b, 3);
    // TwoNum a[] = {{3, 3},
    //               {2, 2},
    //               {5, 5},
    //               {2, 1},
    //               {3, 6}};
    // findMin1(a,5);
    // int a[]={12 ,12, 122 ,112 ,222 ,211 ,222, 221 ,76 ,36, 31 ,234, 256, 76 ,76};
    // findExtremePoint(a,15);
    // findRepeatCharLocation("kygexrrwunuwxalgcbxistydvrxmfyhbzgfpjwtrsaszqkxqjrgchhybxuzlmccafsljlfdse");
    // specialMultiplication("123","45");
    // encodeStr("Hello! How are you!");
    // caesarDecode("NS BFW, JAJSYX TK NRUTWYFSHJ FWJ YMJ WJXZQY TK YWNANFQ HFZXJX");
    // caesarEncode("IN WAR, EVENTS OF IMPORTANCE ARE THE RESULT OF TRIVIAL CAUSES");
    puts(encode("abcxyzABCXYZ", 3, 4));
    puts(decode("defabcEFGBCD", 3, 4));

    end = getTime();
    printf("\ntime spend:%f ms\n", (end - start));

    return 0;
}
