#include "dice.h"

#include <stdlib.h>

namespace JupThrData {

Dice::Dice(int max, int bonus) {
    this->addedBonuses = bonus;
    this->maximumValue = max;
}

RollResult Dice::roll(int modifiers) {
    int result = (std::rand() % this->maximumValue) + 1;
    result += this->addedBonuses;
    result += modifiers;

    return JupThrData::RollResult(result);
}

RollResult Dice::roll() {
    return this->roll(0);
}

RollResult::RollResult(int number) {
    this->result = number;

    if (number >= 8) {
        this->rollStatus = RollStatus::Raise;
    } else if (number >= 4) {
        this->rollStatus = RollStatus::Success;
    } else {
        this->rollStatus = RollStatus::Fail;
    }
}

} // namespace JupThrData
