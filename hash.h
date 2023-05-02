#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;
typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // TODO:
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long wValues[5] = {0};
        int wIndex = 4;
        int multi = 0;
        unsigned long long val = 0;

        for(int i = k.size()-1; i >= 0; --i){
            int ts = 1;
            HASH_INDEX_T a = letterDigitToNumber(k[i]);
            for(int j = 0; j < multi; ++j){
                ts *= 36;
            }
            multi++;
            val += ts*a;
            if(multi == 6){
                multi = 0;
                wValues[wIndex] = val;
                wIndex --;
                val = 0;
            }
            if(wIndex == -1){
                break;
            }
        }
        wValues[wIndex] = val;

        HASH_INDEX_T ans = 0;
        for (int i = 0 ; i < 5 ; ++i) 
        { 
            ans += (wValues[i] * rValues[i]);
        }

        return ans;
    }
    // TODO:
    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(isdigit(letter)){
            
            return letter-22;
        }
        else{
            return tolower(letter) - 97;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
