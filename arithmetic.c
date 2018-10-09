#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int receive_digital();//容错接收用户输入的数字

void receive_fraction(int* numerator,int* denominator);//容错用户输入的分数

double topic_general(int *numerator,int *denominator,int *answerType);//生成双符号四则运算题目

double topic_proper_fraction(int *numerator,int *denominator,int *answerType);//生成真分数四则运算题目

int gcd( int x, int y );//求两个数的最大公约数

int judeg_answer(double answer);//当答案为整数时判断用户输入的答案是否正确

int judeg_fraction_answer(double answer,int numerator,int denominator);//当答案为分数时判断用户输入的答案是否正确


void main()
{
    int sum,score,choose,i,result;//sum为题目总数，score为成绩，choose为用户的功能选择，result为答案的对错
    double answer;//题目正确答案
    int numerator,denominator,answerType;//numerator 为分子, denominator 为分母, answerType 为答案类型
    int *pNumerator,*pDenominator,*pAnswerType;//*pNumerator 为分子的指针,*pDenominator 为分母的指针,*pAnswerType 为答案类型的指针

    pNumerator = &numerator;
    pDenominator = &denominator;
    pAnswerType = &answerType;

    do
    {
        printf("\t\t小学四则运算训练软件\n");
        printf("\t\t0.退出系统\n\t\t1.双符号四则运算\n\t\t2.真分数四则运算\n\n");
        printf("请通过输入序号选择功能：");

        choose = receive_digital();

        if(choose == 1)
        {
            do
            {
                printf("\n\t\t双符号四则运算\n");
                printf("请输入题目的总数(输入0将退出)：");

                sum = receive_digital();
                if(sum == 0)
                {
                    break;
                }
                score = sum;

                printf("题目总数为%d\n\n",sum);
                printf("提示：答案为整数或分数\n当输入整数，按下回车无反应时，即应该输入分数！\n当输入分数，提示错误时，即应该输入整数！\n\n");
                for(i = 0;i < sum;i++)
                {
                    printf("第%d题：\n",i+1);
                    answer = topic_general(pNumerator,pDenominator,pAnswerType);

                    if(answerType == 1)//答案为整数
                    {
                        result = judeg_answer(answer);
                    }
                    else//答案为分数
                    {
                        result = judeg_fraction_answer(answer,numerator,denominator);
                    }
                    if(result == 0)//用户答案错误
                    {
                        score--;
                    }
                }
                printf("满分为：%d分\n您的成绩为:%d分;正确率为：%.0lf%%\n\n",sum,score,((double)score / (double)sum) * 100);
            }while(sum != 0);
        }
        else if(choose == 2)
        {
            do
            {
                printf("\n\t\t真分数四则运算\n");
                printf("请输入题目的总数(输入0将退出)：");

                sum = receive_digital();
                if(sum == 0)
                {
                    break;
                }
                score = sum;

                printf("题目总数为%d\n\n",sum);
                printf("提示：答案为整数或分数\n当输入整数，按下回车无反应时，即应该输入分数！\n当输入分数，提示错误时，即应该输入整数！\n\n");
                for(i = 0;i < sum;i++)
                {
                    printf("第%d题：\n",i+1);

                    answer = topic_proper_fraction(pNumerator,pDenominator,pAnswerType);

                    if(answerType == 1)//答案为整数
                    {
                        result = judeg_answer(answer);
                    }
                    else//答案为分数
                    {
                        result = judeg_fraction_answer(answer,numerator,denominator);
                    }

                    if(result == 0)//用户答案错误
                    {
                        score--;
                    }
                }
                printf("满分为：%d分\n您的成绩为:%d分;正确率为：%.0lf%%\n\n",sum,score,((double)score / (double)sum) * 100);
            }while(sum != 0);
        }
        else if(choose == 0)
        {
            break;
        }
        else
        {
            printf("输入错误,请重新输入！\n");
        }
    }while(choose != 0);

    printf("感谢您的使用。\n");

    return ;
}
/*
*
    容错接收用户输入的数字
    返回值即为用户输入的数字
*
*/
int receive_digital()
{
    int number,resultValue;

    do{
        resultValue = scanf("%d",&number);
        if(resultValue != 1)//判断第一个字符是否按规定格式输入
        {
            printf("您输入的数据类型有误，请重新输入:");
            while(getchar() != '\n');
        }
        else if(number < 0)//判断数字是否大于等于0
        {
            printf("您输入的数据不能为负数，请重新输入:");
            while(getchar() != '\n');
        }
        else if(getchar() != '\n')//判断第一个字符后是否为回车
        {
            printf("您输入的数据格式有误，请重新输入:");
            while(getchar() != '\n');
            number = receive_digital();
        }
    }while(resultValue != 1 || number < 0);

    return number;
}
/*
*
     容错用户输入的分数
     第一个参数为分子的指针，第二个参数为分母的指针
*
*/
void receive_fraction(int* numerator,int* denominator)
{
    int resultValue;
    char ch;

    do{
        resultValue = scanf("%d%c%d",numerator,&ch,denominator);
        if(resultValue != 3)//判断第一,二,三个字符是否按规定格式输入
        {
            printf("您输入的数据类型有误，请重新输入:");
            while(getchar() != '\n');
        }
        else if(*numerator < 0|| *denominator < 0)//判断分子分母是否大于0
        {
            printf("您输入的数据不能为负数或零，请重新输入:");
            while(getchar() != '\n');
        }
        else if(ch != '/')//判断符号是否正确
        {
            printf("您输入的符号有误，请重新输入：");
            while(getchar()!='\n');
        }
        else if(getchar() != '\n')//判断第三个字符后是否为回车
        {
            printf("您输入的数据格式有误，请重新输入:");
            while(getchar() != '\n');
            receive_fraction(numerator,denominator);
        }
    }while(resultValue != 3 || *numerator < 0 || *denominator < 0 || ch!='/');

    return ;
}
/*
*
       生成双符号四则运算题目
       第一个参数为分子的指针，第二个参数为分母的指针，第三个参数为答案类型的指针(0代表答案类型是分数，1代表答案类型是整数)
       返回值为题目的答案
*
*/

double topic_general(int *numerator,int *denominator,int *answerType)
{
    int x,y,z;//三个随机数
    int symbol1,symbol2;//两个运算符号
    double answer;

    srand(time(NULL));//随机数种子
    x = rand()%100+1;
    y = rand()%100+1;
    z = rand()%100+1;
    symbol1 = rand()%4+1;//运算符号：1代表+，2代表-，3代表*，4代表/
    symbol2 = rand()%4+1;

    switch(symbol1)
    {
    case 1:
        switch(symbol2)
        {
        case 1:
            printf("%d + %d + %d=",x,y,z);
            answer = (double)(x + y + z);
            *answerType = 1;
           break;
        case 2:
            if(x + y > z)//保证答案不为负数
            {
                printf("%d + %d - %d=",x,y,z);
                answer = (double)(x + y - z);
                *answerType = 1;
            }
            else
            {
                printf("%d + %d - %d=",x,z,y);
                answer = (double)(x + z - y);
                *answerType = 1;
            }
           break;
        case 3:
            printf("%d + %d * %d=",x,y,z);
            answer = (double)(x + y * z);
            *answerType = 1;
           break;
        case 4:
            printf("%d + %d / %d=",x,y,z);
            *denominator = z;
            *numerator = x * z + y;
            answer = (double)*numerator / (double)*denominator;
            if((double)*numerator / (double)*denominator == 0)//判断答案是整数还是分数
            {
                *answerType = 1;
            }
            else
            {
                *answerType = 0;
            }
           break;
        }
        break;

    case 2:
        switch(symbol2)
        {
        case 1:
            if(x - y >= -z)//保证答案不为负数
            {
                printf("%d - %d + %d=",x,y,z);
                answer = (double)(x - y + z);
                *answerType = 1;
            }
            else
            {
                printf("%d - %d + %d=",y,x,z);
                answer = (double)(y - x + z);
                *answerType = 1;
            }
            break;
        case 2:
            if(x >= y + z)//保证答案不为负数
            {
                printf("%d - %d - %d=",x,y,z);
                answer = (double)(x - y - z);
                *answerType = 1;
            }
            else if(x > z)
            {
                x = x + y;
                printf("%d - %d - %d=",x,y,z);
                answer = (double)(x - y - z);
                *answerType = 1;
            }
            else
            {
                z = z + y;
                printf("%d - %d - %d=",z,y,x);
                answer = (double)(z - y - x);
                *answerType = 1;
            }
            break;
        case 3:
            if(x > y * z)//保证答案不为负数
            {
                printf("%d - %d * %d=",x,y,z);
                answer = (double)(x - y * z);
                *answerType = 1;
                break;
            }
        case 4:
            if(x > y / z)//保证答案不为负数
            {
                printf("%d - %d / %d=",x,y,z);
                *numerator = x * z - y;
                *denominator = z;
                answer = (double)*numerator / (double)*denominator;
                if((double)*numerator / (double)*denominator == 0)//判断答案是整数还是分数
                {
                    *answerType = 1;
                }
                else
                {
                    *answerType = 0;
                }
            }
            else
            {
                printf("%d - %d / %d=",x,z,y);
                *numerator = x * y - z;
                *denominator = y;
                answer = (double)*numerator / (double)*denominator;
                if((double)*numerator / (double)*denominator == 0)//判断答案是整数还是分数
                {
                    *answerType = 1;
                }
                else
                {
                    *answerType = 0;
                }
            }
            break;
        }
        break;

    case 3:
        switch(symbol2)
        {
        case 1:
            printf("%d * %d + %d=",x,y,z);
            answer = (double)(x * y + z);
            *answerType = 1;
           break;
        case 2:
            if(x * y >= z)//保证答案不为负数
            {
                printf("%d * %d - %d=",x,y,z);
                answer = (double)(x * y - z);
                *answerType = 1;
            }
            else
            {
                printf("%d * %d - %d=",x,z,y);
                answer = (double)(x * z - y);
                *answerType = 1;
            }
            break;
        case 3:
            printf("%d * %d * %d=",x,y,z);
            answer = (double)(x * y * z);
            *answerType = 1;
           break;
        case 4:
            printf("%d * %d / %d=",x,y,z);
            *numerator = x * y;
            *denominator = z;
            answer = (double)*numerator / (double)*denominator;
            if((double)*numerator / (double)*denominator == 0)//判断答案是整数还是分数
            {
                *answerType = 1;
            }
            else
            {
                *answerType = 0;
            }
           break;
        }
        break;

    case 4:
        switch(symbol2)
        {
        case 1:
            printf("%d / %d + %d=",x,y,z);
            *numerator = z * y + x;
            *denominator = y;
            answer = (double)*numerator / (double)*denominator;
            if((double)*numerator / (double)*denominator == 0)//判断答案是整数还是分数
            {
                *answerType = 1;
            }
            else
            {
                *answerType = 0;
            }
           break;
        case 2:
            if(x / y >= z)//保证答案不为负数
            {
                printf("%d / %d - %d=",x,y,z);
                *numerator = x - (y * z);
                *denominator = y;
                answer = (double)*numerator / (double)*denominator;
                if((double)*numerator / (double)*denominator == 0)//判断答案是整数还是分数
                {
                    *answerType = 1;
                }
                else
                {
                    *answerType = 0;
                }
                break;
            }
        case 3:
            printf("%d / %d * %d=",x,y,z);
            *numerator = x * z;
            *denominator = y;
            answer = (double)*numerator / (double)*denominator;
            if((double)*numerator / (double)*denominator == 0)//判断答案是整数还是分数
            {
                *answerType = 1;
            }
            else
            {
                *answerType = 0;
            }
            break;
        case 4:
            printf("%d / %d / %d=",x,y,z);
            *numerator = x;
            *denominator = y * z;
            answer = (double)*numerator / (double)*denominator;
            if((double)*numerator / (double)*denominator == 0)//判断答案是整数还是分数
            {
                *answerType = 1;
            }
            else
            {
                *answerType = 0;
            }
            break;
        }
        break;
    }

    return answer;
}
/*
*
       生成真分数四则运算题目
       第一个参数为分子的指针，第二个参数为分母的指针，第三个参数为答案类型的指针(0代表答案类型是分数，1代表答案类型是整数)
       返回值为题目答案
*
*/
double topic_proper_fraction(int *numerator,int *denominator,int *answerType)
{
    int numertor1,numertor2,denominator1,denominator2;//两个分子，两个分母
    int temp,symbol;//temp为中间值，用于分子分母值得交换，symbol为运算符号
    double answer;//答案

    srand(time(NULL));//随机数种子
    denominator1 = rand()%100+2;//分母为2-100之间的数
    denominator2 = rand()%100+2;
    numertor1 = rand()%100+1;//分子为1-100之间的数
    numertor2 = rand()%100+1;
    symbol = rand()%4+1;//运算符号：1代表+，2代表-，3代表*，4代表/

    if(numertor1 > denominator1)//保证分子不大于等于分母
    {
        temp = numertor1;
        numertor1 = denominator1;
        denominator1 = temp;
    }
    else if(numertor1 == denominator1)
    {
        numertor1 = numertor1 / 3 + 1;
    }

    if(numertor2 > denominator2)//保证分子不大于等于分母
    {
        temp = numertor2;
        numertor2 = denominator2;
        denominator2 = temp;
    }
    else if(numertor2 == denominator2)
    {
        numertor2 = numertor1 / 3 + 1;
    }

    switch(symbol)
    {
    case 1:
        printf("%d/%d + %d/%d=",numertor1,denominator1,numertor2,denominator2);

        *numerator = numertor1 * denominator2 + numertor2 * denominator1;
        *denominator = denominator1 * denominator2;

        answer = (double)*numerator / (double)*denominator;
        if((double)*numerator / (double)*denominator == 0)//判断答案为分数还是整数
        {
            *answerType = 1;
        }
        else
        {
            *answerType = 0;
        }
        break;
    case 2:
        if((double)numertor1 / (double)denominator1 - (double)numertor2 / (double)denominator2 > 0)//保证答案不为负数
        {
            printf("%d/%d - %d/%d=",numertor1,denominator1,numertor2,denominator2);

            *numerator = numertor1 * denominator2 - numertor2 * denominator1;
            *denominator = denominator1 * denominator2;

            answer = (double)*numerator / (double)*denominator;
            if((double)*numerator / (double)*denominator == 0)//判断答案为分数还是整数
            {
                *answerType = 1;
            }
            else
            {
                *answerType = 0;
            }
        }
        else
        {
            printf("%d/%d - %d/%d=",numertor2,denominator2,numertor1,denominator1);

            *numerator = numertor2 * denominator1 - numertor1 * denominator2;
            *denominator = denominator1 * denominator2;

            answer = (double)*numerator / (double)*denominator;
            if((double)*numerator / (double)*denominator == 0)//判断答案为分数还是整数
            {
                *answerType = 1;
            }
            else
            {
                *answerType = 0;
            }
        }
        break;
    case 3:
        printf("%d/%d * %d/%d=",numertor1,denominator1,numertor2,denominator2);

        *numerator = numertor1 * numertor2;
        *denominator = denominator1 * denominator2;

        answer = (double)*numerator / (double)*denominator;
        if((double)*numerator / (double)*denominator == 0)//判断答案为分数还是整数
        {
            *answerType = 1;
        }
        else
        {
            *answerType = 0;
        }
        break;
    case 4:
        printf("%d/%d / %d/%d=",numertor1,denominator1,numertor2,denominator2);

        *numerator = numertor1 * denominator2;
        *denominator = denominator1 * numertor2;

        answer = (double)*numerator / (double)*denominator;
        if((double)*numerator / (double)*denominator == 0)//判断答案为分数还是整数
        {
            *answerType = 1;
        }
        else
        {
            *answerType = 0;
        }
        break;
    }

    return answer;
}
/*
*
       求两个数的最大公约数
       返回值即为最大公约数
*
*/
int gcd(int x,int y)
{
	int i;
	for(i = x;i >= 1;i--)
    {
		if(x % i == 0 && y % i == 0)
		{
		    break;
		}
	}
	return i;
}
/*
*
       当答案为整数时判断用户输入的答案是否正确
       参数为答案
       正确返回1，错误返回0
*
*/
int judeg_answer(double answer)
{
    double userAnswer;//用户答案
    int resultValue;//接收用户输入

    resultValue = receive_digital();
    userAnswer = (double)resultValue;
    if(userAnswer == answer)
    {
        printf("正确！！\n\n");
        return 1;
    }
    else
    {
        printf("错误！！答案为%d。\n\n",(int)answer);
        return 0;
    }
}
/*
*
       当答案为分数时判断用户输入的答案是否正确
       第一个参数为答案，第二个参数为分子，第三个参数为分母
       正确返回1，错误返回0
*
*/
int judeg_fraction_answer(double answer,int numerator,int denominator)
{
    int GCD;
    double userAnswer;
    int aswerNumerator,aswerDenominator;
    int *pAswerNumerator,*pAswerDenominator;

    pAswerNumerator = &aswerNumerator;
    pAswerDenominator = &aswerDenominator;
    GCD = gcd(numerator,denominator);

    receive_fraction(pAswerNumerator,pAswerDenominator);
    userAnswer = (double)aswerNumerator / (double)aswerDenominator;

    if(userAnswer == answer)
    {
        printf("正确！！\n\n");
        return 1;
    }
    else
    {
        printf("错误！！答案为%d/%d。\n\n",numerator/GCD,denominator/GCD);
        return 0;
    }
}
