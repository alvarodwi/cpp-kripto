#pragma once

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

void refreshUi(bool wait = false) {
  if (wait) {
    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::cin.get();
  }
  std::cout << "\033[2J\033[1;1H";
}

void ignoreLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void errorMessage(std::string s) {
  std::cout << "\n//ERROR\n";
  std::cout << s.c_str() << '\n';
  refreshUi();
}