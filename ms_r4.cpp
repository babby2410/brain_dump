/*
 * Given a (n, k), largest k digit number using the digits from n (order needs to be intact)
 */

#include <iostream>
#include <vector>

using namespace std;

void maxKDigitUtil(int idx, vector<int> &currentDigits, vector<int> &digits, int &maximumValue, const int &k) {
    if (currentDigits.size() == k) {
        int multiplier = 1;
        int currentValue = 0;
        for (int i = currentDigits.size() - 1; i >= 0; i--) {
            currentValue += (multiplier * currentDigits[i]);
            multiplier *= 10;
        }

        maximumValue = max(maximumValue, currentValue);
        return ;
    }

    if (idx >= digits.size()) {
        return ;
    }

    currentDigits.push_back(digits[idx]);
    maxKDigitUtil(idx + 1, currentDigits, digits, maximumValue, k);
    currentDigits.pop_back();

    maxKDigitUtil(idx + 1, currentDigits, digits, maximumValue, k);
}

int maxKDigitNumber(vector<int> &digits, int k) {
    int maximumValue = INT_MIN;
    vector<int> currentDigits;
    maxKDigitUtil(0, currentDigits, digits, maximumValue, k);
    return maximumValue;
}

int main() {
    vector<int> temp{6,3,8,1,7,3,9,8};
    int k = 3;
    int answer = maxKDigitNumber(temp, k);
    cout << "Answer: " << answer << endl;
    return 0;
}
