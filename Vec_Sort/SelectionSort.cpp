#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    
    const int size =5;
    int min;


    std::vector<int> vec(size);

    for (int i = 0; i < size; i++) {
        vec[i] = std::rand() %100;
    }
    
    for (int value: vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
     
    for (int i = 0; i < size; i++)
    {
        std::cout << vec[i] << " ";
        min= vec[i];
        for (int n= i+1; n < size; n++)
        {
            std::cout << " r: ";
            if (vec[n] < min)
            {
                min= vec[n];
            }
            std::cout << vec[n] << " ";
            
        }
        std::cout << " min: " << min << " ";
        
        std::cout << std::endl;
    }
    
        return 0;
}