#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "expression_evaluator.h"

using namespace std;
using namespace calc;

int main(int argc, const char** argv)
{

  // opt --test
  bool test = false;

  if (argc == 2)
  {
    if (string(argv[1]) == "--test")
    {
      test = true;
    }
  }

  if (!test){
    std::cout << "Expression Evaluator" << std::endl;
    std::cout << "Enter an expression to evaluate or --test to run tests" << std::endl;
    std::cout << "Press Ctrl+D to exit" << std::endl;
    std::cout << std::endl;
    std::cout << "For test, do something like:" << std::endl;
    std::cout << "    $ ./calc.run --test < test_data.txt" << std::endl;

    std::cout << std::endl;
    std::cout << "For example, try these expressions:" << std::endl;
    std::cout << "    1 + 2" << std::endl;
    std::cout << "    3 * (4 + 5)" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
  }

  if (test) {
      int total = 0;
      int passed = 0;

      std::string expr;
      std::string expected;
      const double EPS = 1e-9;
      while (std::cin.eof() == false) {
          if(!(std::cin >> expr)) break;
          if(!(std::cin >> expected)) break;

          if (expr == "") continue;
          if (expr[0] == '#') continue;

          total++;

          double actual;

          bool ok = evaluateExpression(expr, actual);

          if (!ok && expected == "-"){
            std::cout << "[\033[32mPASS\033[0m]" << " ";
            std::cout << expr << " => ILLEGAL: Expected ILLEGAL" << std::endl;
            passed++;
            continue;
          }
          if (!ok) {
            std::cout << "[\033[31mFAIL\033[0m]" << " ";
            std::cout << expr << " => \033[31mILLEGAL\033[0m: Expected " 
                      << expected << std::endl;
            continue;
          }

          if (expected == "-") {
            std::cout << "[\033[31mFAIL\033[0m]" << " ";
            std::cout << expr << " => " << actual << ": Expected ILLEGAL" << std::endl;
            continue;
          }

          if (std::fabs(actual - stod(expected)) < EPS) {
            std::cout << "[\033[32mPASS\033[0m]" << " ";
            std::cout << expr << " => " << actual << ": Expected " 
                      << expected << std::endl;
            passed++;
          } else {
            std::cout << "[\033[31mFAIL\033[0m]" << " ";
            std::cout << expr << " => " << actual << ": Expected " 
                      << expected << std::endl;
          }
      }

      std::cout << "Passed " << passed << " Failed " << total - passed << " Total " << total << std::endl;

  } else {

    string expr;
    std::cout << "\033[33m$\033[0m ";
    while (!getline(cin, expr).eof())
    {
      double result;
      if (evaluateExpression(expr, result))
        cout << result << endl;
      else
        cout << "ILLEGAL" << endl;
      std::cout << "\033[33m$\033[0m ";
    }
    
    return 0;

  }
}
