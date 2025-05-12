#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      // Add your code here
      HASH_INDEX_T w[5] ={0};
      int len = static_cast<int>(k.length());
      int group = 0;
      int power = 0;

      for (int i = len - 1; i >= 0 && group < 5; --i) {
        HASH_INDEX_T val = letterDigitToNumber(k[i]);
        w[4-group] += val * static_cast<HASH_INDEX_T>(pow(36, power));
        ++power;

        if (power == 6) {
          ++group;
          power = 0;
        }
      }

      HASH_INDEX_T hash = 0;
      for (int i = 0; i < 5; ++i) {
        hash += w[i] * rValues[i];
      }
      return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      if (letter >= 'A' && letter <= 'Z') {letter = letter - 'A' + 'a';} // convert lower case
      if (letter >= 'a' && letter <= 'z') {return letter - 'a';} // alphabet to value
      else if (letter >= '0' && letter <= '9') {return 26 + (letter - '0');} // numeric to value
      return 0; // invalid character
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
