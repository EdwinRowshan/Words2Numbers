#include <iostream>
#include <sstream>

using namespace std;


int numDigits(int n) {

    return n >= 10 ? numDigits(n / 10) + 1 : 1;
}

int firstDigit(int n) {
    while (n >= 10)
        n /= 10;
    return n;
}


int lastDigit(int n) {
    return (n % 10);
}

int getCommaDigs(int dig, int n) {
    int numTrailingUnnecessaryDigits = numDigits(n) - dig;
    for (int i = 0; i < numTrailingUnnecessaryDigits; ++i) {
        n /= 10;
    }
    return n;
}


int removeFirst(int x) {
    if (x < 10) return 0;
    return x % 10 + 10 * removeFirst(x / 10);
}


string intToString(int n) {
    stringstream convert;
    convert << n;
    return convert.str();
}


int StringToInt(string s) {
    stringstream ss(s);
    int x;
    ss >> x;
    return x;
}


string extract(string num) {
    return {num[num.length() - 3], num[num.length() - 2], num[num.length() - 1]};
}


string convert(int number) {
    if (number < 0) cout << "Number not permitted" << endl;

    string ones[] = {"null", "eins", "zwei", "drei", "vier", "fünf", "sechs", "sieben", "acht", "neun",
                     "zehn", "elf", "zwölf", "dreizehn", "vierzehn", "fünfzehn", "sechzehn", "siebzehn", "achtzehn",
                     "neunzehn"};

    string tens[] = {"", "", "zwanzig", "dreißig", "vierzig", "fünfzig", "sechzig", "siebzig", "achtzig", "neunzig"};

    string hundreds[] = {"", "einhundert", "zweihundert", "dreihundert", "vierhundert", "fünfhundert", "sechshundert",
                         "siebenhundert",
                         "achthundert", "neunhundert"};

    string num = intToString(number);

    if (numDigits(number) == 1) {
        return ones[number];
    }

    if (numDigits(number) == 2) {
        if (getCommaDigs(2, number) <= 19 && getCommaDigs(2, number) >= 10) {
            return ones[getCommaDigs(2, number)];
        }
        if (number % 10 == 1) {
            return "einund" + tens[(number / 10) % 10];
        }
        if (lastDigit(number) == 0 && firstDigit(number) != 0) {
            return tens[firstDigit(number)];
        }
        return ones[number % 10] + "und" + tens[(number / 10) % 10];
    }

    if (numDigits(number) == 3) {
        if (number % 100 == 00) {
            return hundreds[firstDigit(number)];
        }
        if (number % 100 == 11 || number % 100 == 12) {
            return hundreds[firstDigit(number)] + ones[number % 100];
        }
        if (lastDigit(number) == 1 && (number / 10) % 10 == 0) {
            return hundreds[((number / 10) / 10) % 10] + "eins";
        }
        if (lastDigit(number) == 1 && (number / 10) % 10 != 1) {
            return hundreds[firstDigit(number)] + "einund" + tens[(number / 10) % 10];
        }
        if (lastDigit(number) == 0 && (number / 10) % 10 != 0) {
            return hundreds[firstDigit(number)] + tens[(number / 10) % 10];
        }
        if ((number / 10) % 10 == 0) {
            return hundreds[firstDigit(number)] + ones[lastDigit(number)];
        }
        if ((number / 10) % 10 != 1) {
            return hundreds[firstDigit(number)] + ones[lastDigit(number)] + "und" + tens[(number / 10) % 10];
        } else {
            return hundreds[firstDigit(number)] + ones[number % 100];
        }
    }
    return "Error in conversion";
}


string solution(int number) {
    string num = intToString(number);
    string uncut = intToString(number);
    string ret = "";
    string numberWords[] = {"", "tausend", " Millionen ", " Milliarden "};
    string OnesWord[] = {"eins", "ein", "eine", "eine", "eine"};
    int counter = 0;
    if (num == "0") {
        return "null";
    }
    while (num.length() >= 3) {

        string currentGroup;
        if (extract(num) == "000") {
            currentGroup = "";
        }
        else if (extract(num) == "001") {
            currentGroup = OnesWord[counter] + numberWords[counter];
        } else {
            currentGroup = convert(StringToInt(extract(num))) + numberWords[counter];
        }
        num.resize(num.length() - 3);
        ret = currentGroup + ret;
        ++counter;
    }
    if (num == "1") {
        ret = OnesWord[counter] + numberWords[counter] + ret;
    } else if (num.length() > 0) {
        ret = convert(StringToInt(num)) + numberWords[counter] + ret;
    }
    return ret;
}

int main() {

    do {
        int input;
        cout << "ENTER NUMBER TO CONVERT : " << endl;
        cin >> input;
        cout << solution(input) << endl;

    } while (true);
    return 0;
}