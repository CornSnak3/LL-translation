#include <algorithm>
#include <array>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <string>


const std::array<char, 7> terminalSymbols = { '5', '6', '7', '8', '+', '/', '#' };
std::string inputString;
int currentPosition;

bool isTerminalSymbol(const char &);
char yylex();
void parse();

double S();
double E();
double T();
double F();

double Z(double);


int main() {
  do {
    inputString = "";
    currentPosition = 0;
    std::cout << ">> ";
    std::getline(std::cin, inputString);
    if (inputString[0] == 'q' || inputString[0] == 'Q')
      break;
    parse();
  } while (true);

  return 0;
}

bool isTerminalSymbol(const char &symbol) {
  return (std::find(terminalSymbols.begin(), 
             terminalSymbols.end(), symbol) != terminalSymbols.end());
}

char yylex() {
  if (isTerminalSymbol(inputString[++currentPosition]))
    return inputString[currentPosition];

  throw new std::invalid_argument(
    "Illegal symbol \'" + std::to_string(inputString[currentPosition]) +
    '\'' + " at " + std::to_string(--currentPosition));
}

void parse() {
  try {
    std::cout << inputString << " = ";
    inputString.erase(remove(inputString.begin(), inputString.end(), ' '), inputString.end());
    inputString += "#"; 
    std::cout << S() << std::endl;
  } catch (std::invalid_argument exc) {
    std::cout << exc.what() << std::endl;
    return;
  }
}

double S() {
  try {
    if (isdigit(inputString[currentPosition]))
      return E();
    throw new std::invalid_argument("S()");
  } catch (std::invalid_argument exc) {
    throw new std::invalid_argument(exc);
  }
}

double E() {
  try {
    return Z(T());
    throw new std::invalid_argument("E()");
  } catch (std::invalid_argument exc) {
    throw new std::invalid_argument(exc);
  }
}

double T() {
  try {
    if (isdigit(inputString[currentPosition])) {
      double a = F();
      if (yylex() == '/' && isdigit(yylex()))
        return (a / F());
    }
    throw new std::invalid_argument("T()");
  } catch (std::invalid_argument exc) {
    throw new std::invalid_argument(exc);
  }
}

double F() {
  switch (inputString[currentPosition]) {
  case '5': return 5; 
  case '6': return 6;
  case '7': return 7;
  case '8': return 8;
  default: throw new std::invalid_argument("F()");
  }
}

double Z(double Ts) {
  try {
    if (inputString[++currentPosition] == '+') {
      if (isdigit(yylex())) {
        double Zi = T();
        double Z1i = Zi + Ts;
        return Z(Z1i);
      }
      else {
        throw new std::invalid_argument("Z()");
      }
    }
    else if (inputString[currentPosition] == '#')
      return Ts;
  } catch (std::invalid_argument exc) {
    throw new std::invalid_argument(exc);
  }
}