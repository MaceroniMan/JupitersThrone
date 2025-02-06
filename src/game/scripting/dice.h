#ifndef DICE_H
#define DICE_H

namespace JupThrData {

enum RollStatus {
    Fail,
    Success,
    Raise
};

class RollResult {
public:
    RollResult(int number);

    int res();

    bool is(RollStatus compareStatus);

private:
    RollStatus rollStatus;
    int result;
};

class Dice
{
public:
    Dice(int max, int bonus);

    RollResult roll();
    RollResult roll(int modifier);

    int max() {return this->maximumValue;}
    int bonus() {return this->addedBonuses;}

    static Dice D4() {return Dice(4, 0);}

    static Dice D6() {return Dice(6, 0);}

    static Dice D8() {return Dice(8, 0);}

    static Dice D10() {return Dice(10, 0);}

    static Dice D12() {return Dice(12, 0);}

    static Dice D12(int bonus) {return Dice(12, bonus);}

private:
    int maximumValue;
    int addedBonuses;
};

} // namespace JupThrData

#endif // DICE_H
