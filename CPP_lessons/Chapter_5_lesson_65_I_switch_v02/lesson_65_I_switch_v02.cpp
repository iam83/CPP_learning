/*
 Напишите функцию calculate(), которая принимает две переменные типа int и одну переменную типа char
 которая, в свою очередь, представляет одну из следующих математических операций: +, -, *, / или % (остаток от числа).
 Используйте switch для выполнения соответствующей математической операции над целыми числами,
 а результат возвращайте обратно в main(). Если в функцию передается недействительный математический оператор,
 то функция должна выводить ошибку. С оператором деления выполняйте целочисленное деление.
 */

#include <iostream>
 
struct Condition
{
    int a;
    char operation;
    int b;
};
 
struct Result
{
    int result;
    int error;
};
 
Condition getArgs()
{
    Condition x;
    std::cout << "Enter args (examle: 2 - 4): ";
    std::cin >> x.a;
    std::cin >> x.operation;
    std::cin >> x.b;
    return x;
}
 
Result calculate(int a, char operation, int b)
{
    Result res;
    res.error = 0;
    res.result = 0;
    switch (operation)
    {
    case '-':
        res.result = a - b;
        break;
    case '+':
        res.result = a + b;
        break;
    case '*':
        res.result = a * b;
        break;
    case '/':
        res.result = a / b;
        break;
    case '%':
        res.result = a % b;
        break;
    default:
        std::cout << "Unknown operation";
        res.error = -1;
        break;
    }
    return res;
}
 
int main()
{
    Condition cond = getArgs();
    Result res = calculate(cond.a, cond.operation, cond.b);
    if (!res.error)
    {
        std::cout << res.result << std::endl;
    }
    return res.error;
}