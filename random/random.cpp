#include <iostream>
#include <random>

int main()
{

  std::random_device rd; /* genuine random number */
  std::cout << rd() << std::endl;

  std::mt19937 mt1; /* pseudo-random number */
  std::cout << mt1() << std::endl;
  
  std::mt19937 mt2(rd()); /*pseudo-random number with random seed */
  std::cout << mt2() << std::endl;

  // Uniform Distribution<int>
  std::uniform_int_distribution<int> dist(-10, 10);
  for (int i=0; i<10; ++i)
    std::cout << dist(mt2) << ' ';
  std::cout << std::endl;

  // Uniform Distribution<float>
  std::uniform_real_distribution<float> dist_f(0, 1);
  for (int i=0; i<5; ++i)
    std::cout << dist_f(mt2) << ' ';
  std::cout << std::endl;
  
  return 0;
}
