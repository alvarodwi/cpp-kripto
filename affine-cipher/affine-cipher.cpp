/*
Kelompok 3

140810200041 - Alvaro
140810200045 - Amalia
140810200049 - Rasyid
140810200055 - Wafa
140810200061 - Andyka
*/

#include <iostream>
#include <string>

void menu();
void encryption(std::string, int, int);
void decryption(std::string, int, int);
void refreshUi(bool);
void errorMessage(std::string s);
bool validateCoprime(int n);

int main() {
  char yesNo;

  do {
    yesNo = ' ';
    std::cout << "\n.:: Affine Cipher ::.\n\n";
    menu();

    while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N') {
      std::cout << "\n\nJalankan lagi (Y/N)\t> ";
      std::cin >> yesNo;
      std::cin.ignore();
      refreshUi(false);
    }
  } while (toupper(yesNo) == 'Y');

  return 0;
}

void menu() {
  std::string message;
  int a, b;
  std::cout << "Message\t> ";
  getline(std::cin, message);
  std::cout << "a > ";
  std::cin >> a;
  if (!validateCoprime(a)) {
    a = 1;
  }
  std::cout << "b > ";
  std::cin >> b;
  b = b % 26;

  int op;
  std::cout << "\n";
  std::cout << "1. Enkripsi\n";
  std::cout << "2. Dekripsi\n";
  std::cout << "Pilih operasi\t> ";
  std::cin >> op;

  switch (op) {
  case 1:
    encryption(message, b, a);
    break;
  case 2:
    decryption(message, b, a);
    break;
  default:
    errorMessage("Invalid operation, please try again");
    break;
  }
}

void encryption(std::string message, int b, int a) {
  std::cout << "\n:: Enkripsi >\n";
  std::cout << "message\t: " << message << '\n';
  std::cout << "a\t: " << a << "\n";
  std::cout << "b\t: " << b << "\n\n";

  std::string hasil = "";

  for (int i = 0; i < message.length(); i++) {
    if (message[i] == ' ') {
      hasil += ' ';
      continue;
    }

    /* applying encryption formula ( a x + b ) mod m
    {here x is message[i] and m is 26} and added 'A' to
    bring it in range of ascii alphabet[ 65-90 | A-Z ] */
    // huruf kapital
    if (isupper(message[i]))
      hasil += (char)((((a * (message[i] - 'A')) + b) % 26) + 'A');
    // huruf non kapital
    else
      hasil += (char)((((a * (message[i] - 'a')) + b) % 26) + 'a');
  }

  std::cout << "Enkripsi cipher code >\n" << hasil << '\n';
}
void decryption(std::string message, int b, int a) {
  std::cout << "\n:: Dekripsi >\n";
  std::cout << "message\t: " << message << '\n';
  std::cout << "a\t: " << a << "\n";
  std::cout << "b\t: " << b << "\n\n";

  std::string hasil = "";

  int a_inv = 0;
  int flag = 0;

  // inverse modulo
  for (int i = 0; i < 26; i++) {
    flag = (a * i) % 26;

    // Check if (a*i)%26 == 1,
    // then i will be the multiplicative inverse of a
    if (flag == 1) {
      a_inv = i;
    }
  }

  for (int i = 0; i < message.length(); i++) {
    // deteksi spasi
    if (message[i] == ' ') {
      hasil += ' ';
      continue;
    }

    int offset = islower(message[i]) ? a - 1 : 0;
    // huruf kapital
    if (isupper(message[i]))
      hasil = hasil + (char)(((a_inv * (message[i] + 'A' - b)) % 26) + 'A');
    // huruf non kapital
    else
      hasil = hasil +
              (char)(((a_inv * (message[i] + 'a' - b) - offset) % 26) + 'a');
  }

  std::cout << "Hasil plain text >\n" << hasil << '\n';
}

bool validateCoprime(int n) {
  /*
   Nilai coprime jadi 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23 and 25 (if the
   alphabet is 26 characters long)
  */
  switch (n) {
  case 1:
  case 3:
  case 5:
  case 7:
  case 9:
  case 11:
  case 15:
  case 17:
  case 19:
  case 21:
  case 23:
  case 25:
    return true;
  default:
    return false;
  }
}

void refreshUi(bool wait) {
  if (wait) {
    std::cout << "Press any b to continue...";
    std::cin.ignore();
    std::cin.get();
  }
  std::cout << "\033[2J\033[1;1H";
}

void errorMessage(std::string s) {
  std::cout << "\n//ERROR\n";
  std::cout << s.c_str() << '\n';
  refreshUi(false);
}