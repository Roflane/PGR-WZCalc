#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>

#define LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define CIN(x) (std::cin >> (x))
#define c32(_v) static_cast<uint32_t>(_v)

enum class EScale : uint32_t {
    First = 50,
    Second = 25,
    Mixed = 100,
};

enum class EOption : uint32_t {
    First = 1,
    Second = 2,
    Mixed = 3
};

namespace table {
     std::vector<uint32_t> scale = {
         c32(EScale::First),
         c32(EScale::Second),
         c32(EScale::Mixed),
     };
}

typedef struct {
    uint32_t totalDamage;
    uint32_t waveCount;
    uint32_t score;
} WarzoneData;


template <EScale scale>
uint32_t calcScore(WarzoneData wzData) {
    return (wzData.totalDamage / c32(scale)) + (wzData.waveCount * 50'000) + 20000;
}


void data_io(uint32_t &option, WarzoneData &wzData) {
    LOG("Enter zone placement: \n"
    "1 - First\n"
    "2 - Second\n"
    "3 - Mixed\n~ ");
    CIN(option);
    if (option < c32(EOption::First) || option > c32(EOption::Mixed)) return;

    LOG("Enter total damage: ");
    CIN(wzData.totalDamage);

    LOG("Enter wave count: ");
    CIN(wzData.waveCount);
}


[[noreturn]] void runScoreCalculator() {
    while (true) {
        system("cls");

        WarzoneData wzData;
        uint32_t option;

        data_io(option, wzData);
        switch (static_cast<EOption>(option)) {
            case EOption::First:
                wzData.score = calcScore<EScale::First>(wzData);
                break;
            case EOption::Second:
                wzData.score = calcScore<EScale::Second>(wzData);
                break;
            case EOption::Mixed:
                wzData.score = calcScore<EScale::Mixed>(wzData);
                break;
        }

        LOG("Approximate score: %d\n", wzData.score);
        LOG("Press enter to proceed\n");
        std::cin.ignore();
        std::cin.get();
    }
}

int main() { runScoreCalculator(); }