#ifndef UTILS
#define UTILS

#include "num.h"

namespace Prime
{
    template <typename T>
    bool IsPerfectPower(const Num<T>& value)
    {
        Num<T> upperBound = value;
        Num<T> lowerBound = Num<T>(1);
        const auto log2 = value.BitsNum();
        for (std::uint64_t i = 1; i < log2; i++)
        {
            while (upperBound >= lowerBound)
            {
                const Num<T> candidateBase = (lowerBound + upperBound) >> 1; // Shifting is to divide by two
                const Num<T> candidate = Num<T>::Pow(candidateBase, i + 1);
                if (value == candidate)
                    return true;

                if (candidate > value)
                    upperBound = candidateBase - 1;
                else
                    lowerBound = candidateBase + 1;
            }
        }

        return false;
    }

    template <typename T>
    std::uint64_t FindR(const Num<T>& value)
    {
        std::uint64_t log2Pow2 = value.BitsNum();
        log2Pow2 *= log2Pow2;

        std::uint64_t r = log2Pow2 + 1;
        while(true)
        {
            bool foundR = true;
            for (std::uint64_t j = 1; j <= log2Pow2; j++)
            {
                if (PowerMod(value, Num<T>(j), Num<T>(r)) == 1)
                {
                    foundR = false;
                    break;
                }
            }

            if (foundR)
                return r;

            r++;
        }
    }

    // This method uses GCD binary method to tell if the values have gcd greater than 1
    template <typename T>
    bool HaveGCD(Num<T> first, Num<T> second)
    {
        if (first == 1 || second == 1)
            return false;

        while (!first.IsNull() && !second.IsNull() && first != second)
        {
            bool firstEven = !(first.Bit(0));
            bool secondEven = !(second.Bit(0));

            if (firstEven && secondEven)
                return true;
            else if (firstEven && !secondEven)
                first >>= 1;
            else if (!firstEven && secondEven)
                second >>= 1;
            else if (first >= second)
                first = (first - second) >> 1;
            else
            {
                Num<T> temp = first;
                first = (second - first) >> 1;
                second = temp;
            }
        }

        return first.IsNull() ? second > 1 : first > 1;
    }
}

#endif // UTILS

