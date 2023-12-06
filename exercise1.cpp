#include <iostream>
#include <vector>


int main()
{
    std::vector<int> g1;
    for (int i = 1; i <= 5; i++){
        int num;
        std::cin >> num;
        g1.push_back(num);
    }

    for (int i=0; i<g1.capacity()-1; i++){
        for (int j=i+1; j<g1.capacity(); j++){
            if (g1[i] > g1[j]){
                int holder = g1[i];
                g1[i] = g1[j];
                g1[j] = g1[i];
            }
        }
    }
        
    
    for (auto i = g1.begin(); i != g1.end(); ++i)
        std::cout << g1[i] << " ";

}
