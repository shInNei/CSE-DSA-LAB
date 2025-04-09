#include "main.h"
#include "restaurant.cpp"

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    string fileName = "test.txt";
    simulate(fileName);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
     std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}
