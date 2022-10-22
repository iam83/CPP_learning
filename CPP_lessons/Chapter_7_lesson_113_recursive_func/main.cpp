#include <iostream>

int g_count = 0;

void countOut(int count)
    {
    std::cout << "push " << count << '\n';
    ++g_count;
    std::cout << g_count <<std::endl;
    countOut(count-1); //stack overflow
    
    
}

int main()
{
    countOut(4);
    return 0;
}