#include <random>

class RandomNumberGenerator{

private:

    std::random_device m_randomDevice{};
    std::mt19937 m_engine{m_randomDevice()};    // seed 

public:

    RandomNumberGenerator() = default;
    
    int generate(int low, int high){
        return std::uniform_int_distribution<int>{low, high}(m_engine);
    }

};