#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int receive_digital();//�ݴ�����û����������

void receive_fraction(int* numerator,int* denominator);//�ݴ��û�����ķ���

double topic_general(int *numerator,int *denominator,int *answerType);//����˫��������������Ŀ

double topic_proper_fraction(int *numerator,int *denominator,int *answerType);//�������������������Ŀ

int gcd( int x, int y );//�������������Լ��

int judeg_answer(double answer);//����Ϊ����ʱ�ж��û�����Ĵ��Ƿ���ȷ

int judeg_fraction_answer(double answer,int numerator,int denominator);//����Ϊ����ʱ�ж��û�����Ĵ��Ƿ���ȷ


void main()
{
    int sum,score,choose,i,result;//sumΪ��Ŀ������scoreΪ�ɼ���chooseΪ�û��Ĺ���ѡ��resultΪ�𰸵ĶԴ�
    double answer;//��Ŀ��ȷ��
    int numerator,denominator,answerType;//numerator Ϊ����, denominator Ϊ��ĸ, answerType Ϊ������
    int *pNumerator,*pDenominator,*pAnswerType;//*pNumerator Ϊ���ӵ�ָ��,*pDenominator Ϊ��ĸ��ָ��,*pAnswerType Ϊ�����͵�ָ��

    pNumerator = &numerator;
    pDenominator = &denominator;
    pAnswerType = &answerType;

    do
    {
        printf("\t\tСѧ��������ѵ�����\n");
        printf("\t\t0.�˳�ϵͳ\n\t\t1.˫������������\n\t\t2.�������������\n\n");
        printf("��ͨ���������ѡ���ܣ�");

        choose = receive_digital();

        if(choose == 1)
        {
            do
            {
                printf("\n\t\t˫������������\n");
                printf("��������Ŀ������(����0���˳�)��");

                sum = receive_digital();
                if(sum == 0)
                {
                    break;
                }
                score = sum;

                printf("��Ŀ����Ϊ%d\n\n",sum);
                printf("��ʾ����Ϊ���������\n���������������»س��޷�Ӧʱ����Ӧ�����������\n�������������ʾ����ʱ����Ӧ������������\n\n");
                for(i = 0;i < sum;i++)
                {
                    printf("��%d�⣺\n",i+1);
                    answer = topic_general(pNumerator,pDenominator,pAnswerType);

                    if(answerType == 1)//��Ϊ����
                    {
                        result = judeg_answer(answer);
                    }
                    else//��Ϊ����
                    {
                        result = judeg_fraction_answer(answer,numerator,denominator);
                    }
                    if(result == 0)//�û��𰸴���
                    {
                        score--;
                    }
                }
                printf("����Ϊ��%d��\n���ĳɼ�Ϊ:%d��;��ȷ��Ϊ��%.0lf%%\n\n",sum,score,((double)score / (double)sum) * 100);
            }while(sum != 0);
        }
        else if(choose == 2)
        {
            do
            {
                printf("\n\t\t�������������\n");
                printf("��������Ŀ������(����0���˳�)��");

                sum = receive_digital();
                if(sum == 0)
                {
                    break;
                }
                score = sum;

                printf("��Ŀ����Ϊ%d\n\n",sum);
                printf("��ʾ����Ϊ���������\n���������������»س��޷�Ӧʱ����Ӧ�����������\n�������������ʾ����ʱ����Ӧ������������\n\n");
                for(i = 0;i < sum;i++)
                {
                    printf("��%d�⣺\n",i+1);

                    answer = topic_proper_fraction(pNumerator,pDenominator,pAnswerType);

                    if(answerType == 1)//��Ϊ����
                    {
                        result = judeg_answer(answer);
                    }
                    else//��Ϊ����
                    {
                        result = judeg_fraction_answer(answer,numerator,denominator);
                    }

                    if(result == 0)//�û��𰸴���
                    {
                        score--;
                    }
                }
                printf("����Ϊ��%d��\n���ĳɼ�Ϊ:%d��;��ȷ��Ϊ��%.0lf%%\n\n",sum,score,((double)score / (double)sum) * 100);
            }while(sum != 0);
        }
        else if(choose == 0)
        {
            break;
        }
        else
        {
            printf("�������,���������룡\n");
        }
    }while(choose != 0);

    printf("��л����ʹ�á�\n");

    return ;
}
/*
*
    �ݴ�����û����������
    ����ֵ��Ϊ�û����������
*
*/
int receive_digital()
{
    int number,resultValue;

    do{
        resultValue = scanf("%d",&number);
        if(resultValue != 1)//�жϵ�һ���ַ��Ƿ񰴹涨��ʽ����
        {
            printf("�����������������������������:");
            while(getchar() != '\n');
        }
        else if(number < 0)//�ж������Ƿ���ڵ���0
        {
            printf("����������ݲ���Ϊ����������������:");
            while(getchar() != '\n');
        }
        else if(getchar() != '\n')//�жϵ�һ���ַ����Ƿ�Ϊ�س�
        {
            printf("����������ݸ�ʽ��������������:");
            while(getchar() != '\n');
            number = receive_digital();
        }
    }while(resultValue != 1 || number < 0);

    return number;
}
/*
*
     �ݴ��û�����ķ���
     ��һ������Ϊ���ӵ�ָ�룬�ڶ�������Ϊ��ĸ��ָ��
*
*/
void receive_fraction(int* numerator,int* denominator)
{
    int resultValue;
    char ch;

    do{
        resultValue = scanf("%d%c%d",numerator,&ch,denominator);
        if(resultValue != 3)//�жϵ�һ,��,�����ַ��Ƿ񰴹涨��ʽ����
        {
            printf("�����������������������������:");
            while(getchar() != '\n');
        }
        else if(*numerator < 0|| *denominator < 0)//�жϷ��ӷ�ĸ�Ƿ����0
        {
            printf("����������ݲ���Ϊ�������㣬����������:");
            while(getchar() != '\n');
        }
        else if(ch != '/')//�жϷ����Ƿ���ȷ
        {
            printf("������ķ����������������룺");
            while(getchar()!='\n');
        }
        else if(getchar() != '\n')//�жϵ������ַ����Ƿ�Ϊ�س�
        {
            printf("����������ݸ�ʽ��������������:");
            while(getchar() != '\n');
            receive_fraction(numerator,denominator);
        }
    }while(resultValue != 3 || *numerator < 0 || *denominator < 0 || ch!='/');

    return ;
}
/*
*
       ����˫��������������Ŀ
       ��һ������Ϊ���ӵ�ָ�룬�ڶ�������Ϊ��ĸ��ָ�룬����������Ϊ�����͵�ָ��(0����������Ƿ�����1���������������)
       ����ֵΪ��Ŀ�Ĵ�
*
*/

double topic_general(int *numerator,int *denominator,int *answerType)
{
    int x,y,z;//���������
    int symbol1,symbol2;//�����������
    double answer;

    srand(time(NULL));//���������
    x = rand()%100+1;
    y = rand()%100+1;
    z = rand()%100+1;
    symbol1 = rand()%4+1;//������ţ�1����+��2����-��3����*��4����/
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
            if(x + y > z)//��֤�𰸲�Ϊ����
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
            if((double)*numerator / (double)*denominator == 0)//�жϴ����������Ƿ���
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
            if(x - y >= -z)//��֤�𰸲�Ϊ����
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
            if(x >= y + z)//��֤�𰸲�Ϊ����
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
            if(x > y * z)//��֤�𰸲�Ϊ����
            {
                printf("%d - %d * %d=",x,y,z);
                answer = (double)(x - y * z);
                *answerType = 1;
                break;
            }
        case 4:
            if(x > y / z)//��֤�𰸲�Ϊ����
            {
                printf("%d - %d / %d=",x,y,z);
                *numerator = x * z - y;
                *denominator = z;
                answer = (double)*numerator / (double)*denominator;
                if((double)*numerator / (double)*denominator == 0)//�жϴ����������Ƿ���
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
                if((double)*numerator / (double)*denominator == 0)//�жϴ����������Ƿ���
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
            if(x * y >= z)//��֤�𰸲�Ϊ����
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
            if((double)*numerator / (double)*denominator == 0)//�жϴ����������Ƿ���
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
            if((double)*numerator / (double)*denominator == 0)//�жϴ����������Ƿ���
            {
                *answerType = 1;
            }
            else
            {
                *answerType = 0;
            }
           break;
        case 2:
            if(x / y >= z)//��֤�𰸲�Ϊ����
            {
                printf("%d / %d - %d=",x,y,z);
                *numerator = x - (y * z);
                *denominator = y;
                answer = (double)*numerator / (double)*denominator;
                if((double)*numerator / (double)*denominator == 0)//�жϴ����������Ƿ���
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
            if((double)*numerator / (double)*denominator == 0)//�жϴ����������Ƿ���
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
            if((double)*numerator / (double)*denominator == 0)//�жϴ����������Ƿ���
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
       �������������������Ŀ
       ��һ������Ϊ���ӵ�ָ�룬�ڶ�������Ϊ��ĸ��ָ�룬����������Ϊ�����͵�ָ��(0����������Ƿ�����1���������������)
       ����ֵΪ��Ŀ��
*
*/
double topic_proper_fraction(int *numerator,int *denominator,int *answerType)
{
    int numertor1,numertor2,denominator1,denominator2;//�������ӣ�������ĸ
    int temp,symbol;//tempΪ�м�ֵ�����ڷ��ӷ�ĸֵ�ý�����symbolΪ�������
    double answer;//��

    srand(time(NULL));//���������
    denominator1 = rand()%100+2;//��ĸΪ2-100֮�����
    denominator2 = rand()%100+2;
    numertor1 = rand()%100+1;//����Ϊ1-100֮�����
    numertor2 = rand()%100+1;
    symbol = rand()%4+1;//������ţ�1����+��2����-��3����*��4����/

    if(numertor1 > denominator1)//��֤���Ӳ����ڵ��ڷ�ĸ
    {
        temp = numertor1;
        numertor1 = denominator1;
        denominator1 = temp;
    }
    else if(numertor1 == denominator1)
    {
        numertor1 = numertor1 / 3 + 1;
    }

    if(numertor2 > denominator2)//��֤���Ӳ����ڵ��ڷ�ĸ
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
        if((double)*numerator / (double)*denominator == 0)//�жϴ�Ϊ������������
        {
            *answerType = 1;
        }
        else
        {
            *answerType = 0;
        }
        break;
    case 2:
        if((double)numertor1 / (double)denominator1 - (double)numertor2 / (double)denominator2 > 0)//��֤�𰸲�Ϊ����
        {
            printf("%d/%d - %d/%d=",numertor1,denominator1,numertor2,denominator2);

            *numerator = numertor1 * denominator2 - numertor2 * denominator1;
            *denominator = denominator1 * denominator2;

            answer = (double)*numerator / (double)*denominator;
            if((double)*numerator / (double)*denominator == 0)//�жϴ�Ϊ������������
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
            if((double)*numerator / (double)*denominator == 0)//�жϴ�Ϊ������������
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
        if((double)*numerator / (double)*denominator == 0)//�жϴ�Ϊ������������
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
        if((double)*numerator / (double)*denominator == 0)//�жϴ�Ϊ������������
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
       �������������Լ��
       ����ֵ��Ϊ���Լ��
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
       ����Ϊ����ʱ�ж��û�����Ĵ��Ƿ���ȷ
       ����Ϊ��
       ��ȷ����1�����󷵻�0
*
*/
int judeg_answer(double answer)
{
    double userAnswer;//�û���
    int resultValue;//�����û�����

    resultValue = receive_digital();
    userAnswer = (double)resultValue;
    if(userAnswer == answer)
    {
        printf("��ȷ����\n\n");
        return 1;
    }
    else
    {
        printf("���󣡣���Ϊ%d��\n\n",(int)answer);
        return 0;
    }
}
/*
*
       ����Ϊ����ʱ�ж��û�����Ĵ��Ƿ���ȷ
       ��һ������Ϊ�𰸣��ڶ�������Ϊ���ӣ�����������Ϊ��ĸ
       ��ȷ����1�����󷵻�0
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
        printf("��ȷ����\n\n");
        return 1;
    }
    else
    {
        printf("���󣡣���Ϊ%d/%d��\n\n",numerator/GCD,denominator/GCD);
        return 0;
    }
}
