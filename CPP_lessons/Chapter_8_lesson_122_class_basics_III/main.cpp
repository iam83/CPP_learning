#include <iostream> 
#include <cassert> 
 
class Stack { 
private: 
    int m_array[10]; // это будут данные нашего стека 
    int m_next; // это будет индексом следующего свободного элемента стека 
 
public: 
 
    void reset() 
    { 
        m_next = 0; 
        for (int i = 0; i < 10; ++i) 
            m_array[i] = 0; 
    } 
 
    bool push(int value) { 
    // Если стек уже заполнен, то возвращаем false 
        if (m_next == 10) 
            return false; 
    
        m_array[m_next++] = value; // присваиваем следующему свободному элементу значение value, а затем увеличиваем m_next 
        return true; 
    } 
 
    int pop() { 
        // Если элементов в стеке нет, то выводим стейтмент assert 
        assert (m_next > 0); 
    
        // m_next указывает на следующий свободный элемент, поэтому последний элемент со значением - это m_next-1. 
        // Мы хотим сделать следующее: 
        // int val = m_array[m_next-1]; // получаем последний элемент со значением 
        // --
         m_next; // m_next теперь на единицу меньше, так как мы только что вытянули верхний элемент стека 
        // return val; // возвращаем элемент 
        // Весь вышеприведенный код можно заменить следующей (одной) строкой кода 
        return m_array[--m_next];
    } 
    
    void print() { 
        std::cout << "( "; 
        for (int i = 0; i < m_next; ++i) 
            std::cout << m_array[i] << ' '; 
         std::cout << ")\n"; 
    } 

}; 

 
int main() 
{ 
 Stack stack; 
 stack.reset(); 
 
 stack.print(); 
 
 stack.push(3); 
 stack.push(7); 
 stack.push(5); 
 stack.print(); 
 
 stack.pop(); 
 stack.print(); 
 
 stack.pop(); 
 stack.pop(); 
 
 stack.print(); 
 
 return 0; 
}