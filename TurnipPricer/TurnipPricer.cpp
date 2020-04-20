#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class TurnipPrices {
  
  int basePrice;
  int sellPrices[12];
  int whatPattern;
  std::mt19937 mt;
  uint_fast32_t seed_mt;

public:
  
  TurnipPrices(){}
  int get_sellPrices(int i){return sellPrices[i];}
  void calculate(int base = 0, int pattern = 4);
  int randint(int min, int max)
  {
    std::uniform_int_distribution<> dist(min, max);
    return dist(mt);
  }
  float randfloat(float a, float b)
  {
    std::uniform_real_distribution<> dist(a, b);
    return dist(mt);
  }
  int intceil(float val)
  {
    return (int)(val + 0.99999f);
  }
  void showSellPrices();
  
};

void TurnipPrices::calculate(int base, int pattern)
{
  //+++ set basePrice +++
  if ( 90 <= base and base <= 110 ){
    basePrice = base;
  }else{
    basePrice = randint(90, 110);
  }

  //+++ set whatPattern +++
  if ( 0 <= pattern and pattern <= 3 ){
    whatPattern = pattern;
  }else{
    whatPattern = 0; // It has to be randomly chosen
  }

  int chance = randint(0, 99);

  //+++ selext the next pattern +++
  int nextPattern = 0;
  switch (whatPattern)
    {
    case 0:
      if (chance >= 20) nextPattern++;
      if (chance >= 50) nextPattern++;
      if (chance >= 65) nextPattern++;
      break;
    case 1:
      if (chance >= 50) nextPattern++;
      if (chance >= 55) nextPattern++;
      if (chance >= 75) nextPattern++;
      break;
    case 2:
      if (chance >= 25) nextPattern++;
      if (chance >= 70) nextPattern++;
      if (chance >= 75) nextPattern++;
      break;
    case 3:
      if (chance >= 45) nextPattern++;
      if (chance >= 70) nextPattern++;
      if (chance >= 85) nextPattern++;
      break;
    }

  whatPattern = nextPattern;

  //+++ calculate sellPrices +++
  switch (whatPattern)
    {
    case 0:
      {
	// PATTERN 0: high, decreasing, high, decreasing, high
	int work = 0;
	int decPhaseLen1 = randint(2, 3);
	int decPhaseLen2 = 5 - decPhaseLen1;
      
	int hiPhaseLen1 = randint(0, 6);
	int hiPhaseLen2 = randint(1, 7 - hiPhaseLen1);
	int hiPhaseLen3 = 7 - hiPhaseLen1 - hiPhaseLen2;
      
	// high phase 1
	for (int i=0; i<hiPhaseLen1; i++)
	  {
	    sellPrices[work++]
	      = intceil(randfloat(0.9, 1.4) * basePrice);
	  }
      
	// decreasing phase 1
	float rate = randfloat(0.8, 0.6);
	for (int i=0; i<decPhaseLen1; i++)
	  {
	    sellPrices[work++] = intceil(rate * basePrice);
	    rate -= 0.04;
	    rate -= randfloat(0, 0.06);
	  }
      
	// high Phase 2
	for (int i=0; i<hiPhaseLen2; i++)
	  {
	    sellPrices[work++]
	      = intceil(randfloat(0.9, 1.4) * basePrice);
	  }
      
	// decreasing phase 2
	rate = randfloat(0.8, 0.6);
	for (int i=0; i<decPhaseLen2; i++)
	  {
	    sellPrices[work++] = intceil(rate * basePrice);
	    rate -= 0.04;
	    rate -= randfloat(0, 0.06);
	  }
      
	// high phase 3
	for (int i=0; i<hiPhaseLen3; i++)
	  {
	    sellPrices[work++]
	      = intceil(randfloat(0.9, 1.4) * basePrice);
	  }
      }
      break;
    case 1:
      {
	// PATTERN 1: decreasing middle, high spike, random low
	int peakStart = randint(1, 7);
	float rate = randfloat(0.85, 0.90);
	int work = 0;
	for (; work<peakStart; work++)
	  {
	    sellPrices[work] = intceil(rate * basePrice);
	    rate -= 0.03;
	    rate -= randfloat(0, 0.02);
	  }
	sellPrices[work++]
	  = intceil(randfloat(0.9, 1.4) * basePrice);
	sellPrices[work++]
	  = intceil(randfloat(1.4, 2.0) * basePrice);
	sellPrices[work++]
	  = intceil(randfloat(2.0, 6.0) * basePrice);
	sellPrices[work++]
	  = intceil(randfloat(1.4, 2.0) * basePrice);
	sellPrices[work++]
	  = intceil(randfloat(0.9, 1.4) * basePrice);
	for (; work < 12; work++)
	  {
	    sellPrices[work]
	      = intceil(randfloat(0.4, 0.9) * basePrice);
	  }
      }
      break;
    case 2:
      {
	// PATTERN 2: consistently decreasing
	float rate = randfloat(0.85, 0.90);
	for (int work = 0; work < 12; work++)
	  {
	    sellPrices[work] = intceil(rate * basePrice);
	    rate -= 0.03;
	    rate -= randfloat(0, 0.02);
	  }
      }
      break;
    case 3:
      {
	// PATTERN 3: decreasing, spike, decreasing
	int peakStart = randint(0, 7);

	// decreasing phase before the peak
	float rate = randfloat(0.4, 0.9);
	int work = 0;
	for (; work < peakStart; work++)
	  {
	    sellPrices[work] = intceil(rate * basePrice);
	    rate -= 0.03;
	    rate -= randfloat(0, 0.02);
	  }

	sellPrices[work++] = intceil(randfloat(0.9, 1.4) * basePrice);
	sellPrices[work++] = intceil(randfloat(0.9, 1.4) * basePrice);
	rate = randfloat(1.4, 2.0);
	sellPrices[work++]
	  = intceil(randfloat(1.4, rate) * basePrice) - 1;
	sellPrices[work++]
	  = intceil(rate * basePrice);
	sellPrices[work++]
	  = intceil(randfloat(1.4, rate) * basePrice) - 1;

	// decreasing phase after the peak
	if (work < 12)
	  {
	    rate = randfloat(0.4, 0.9);
	    for (; work < 12; work++)
	      {
		sellPrices[work] = intceil(rate * basePrice);
		rate -= 0.03;
		rate -= randfloat(0, 0.02);
	      }
	  }
      }
      break;
    }
}

void TurnipPrices::showSellPrices()
{
  printf("Pattern %d:\n", whatPattern);
  printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
  printf("%3d  %3d  %3d  %3d  %3d  %3d  %3d\n",
	 basePrice,
	 sellPrices[0], sellPrices[2],
	 sellPrices[4], sellPrices[6],
	 sellPrices[8], sellPrices[10]);
  printf("     %3d  %3d  %3d  %3d  %3d  %3d\n",
	 sellPrices[1], sellPrices[3],
	 sellPrices[5], sellPrices[7],
	 sellPrices[9], sellPrices[11]); 
}


int main(int argc, char ** argv){

  TurnipPrices pricer;

  int base = 108;
  int pattern = 0;

  int statNum = 0;
  int upward = 0;

  while (statNum < 10000)
    {
      pricer.calculate(base, pattern);
      if (pricer.get_sellPrices(0) == 144)
	{
	  // pricer.showSellPrices();
	  int max = 0;
	  for (int i=0; i<12; i++){
	    max = std::max(max, pricer.get_sellPrices(i));
	  }
	  // std::cout << "MAX:" << max << std::endl;
	  statNum++;
	  if (max > 146) upward++;
	}
    }

  std::cout << (float)upward / (float)statNum << std::endl;
  
}
