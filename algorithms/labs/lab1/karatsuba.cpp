/******************************************************************************

                              Lab Assignment 1
    Divide and Conquer, Sorting and Searching, and Randomized Algorithms
                                Coursera
September 28, 2020
Hauk Gu
*******************************************************************************/

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

//auxiliary function
//compute sum of two unsigned numbers
string findsum(string str1, string str2) {
    
    //remove leading zeros
    str1.erase(0, min(str1.find_first_not_of('0'), str1.size()-1));
    str2.erase(0, min(str2.find_first_not_of('0'), str2.size()-1));
    
    //padding
    int i = 0;
    if (str1.length() < str2.length()) {
        swap(str1, str2);
    } 
    int diff = str1.length() - str2.length();
    for (i = 0; i < diff; i++) {
        str2 = '0' + str2;
    }
    
    //calculate sum and carry of each digit    
    i = str1.length() - 1;
    int subsum = 0;
    int carry = 0;
    string sum = "";
    
    while (i >= 0) {
        
        subsum = ((str1.at(i) - '0') + (str2.at(i) - '0') + carry) % 10;
        carry = ((str1.at(i) - '0') + (str2.at(i) - '0') + carry) / 10;
        sum = to_string(subsum) + sum;
        i--;
    }
        
    if (carry > 0) 
        sum = "1" + sum;   
        
    return sum;
}

//auxiliary function
//compute difference of two unsigned numbers
string findsubtract(string str1, string str2) {
    
    //remove leading zeros
    str1.erase(0, min(str1.find_first_not_of('0'), str1.size()-1));
    str2.erase(0, min(str2.find_first_not_of('0'), str2.size()-1));
    
    //padding
    int i = 0;
    int diff = str1.length() - str2.length();
    for (i = 0; i < diff; i++) {
        str2 = '0' + str2;
    }
    
    //calculate difference and borrow of each digit
    i = str1.length() - 1;
    int subdiff = 0;
    int borrow = 0;
    string result = "";
    
    while (i >= 0) {
        
        if ((str1.at(i) - '0') - borrow < (str2.at(i) - '0')) {
            
            //borrow required 
            subdiff = (10 + (str1.at(i) - '0') - (str2.at(i) - '0') - borrow);
            borrow = 1;
        } else {
            
            subdiff = (str1.at(i) - '0') - (str2.at(i) - '0') - borrow;
            //reset borrow
            borrow = 0;
        }
        result = to_string(subdiff) + result;
        i--;
    }
    return result;
}

/**********************************************************
karatsuma implementation
x = a * 10^n + b
y = c * 10^n + d
x * y = 10^n * ac + 10^(n/2) * ((a+b)(c+d) - ac - bd) + bd
**********************************************************/
string karatsuma(string str1, string str2) {
    
    //base case
    if (str1.length() < 2 || str2.length() < 2) {
        
        int num1 = stoi(str1);
        int num2 = stoi(str2);
        
        return to_string(num1 * num2);
    }
    
    //padding
    int diff = 0; 
    int i = 0;
    if (str1.length() < str2.length()) {
        
        diff = str2.length() - str1.length();
        for (i = 0; i < diff; i++) {
            str1 = '0' + str1;
        }
    }
    else if (str1.length() > str2.length()) {
        
        diff = str1.length() - str2.length();
        for (i = 0; i < diff; i++) {
            str2 = '0' + str2;
        }
    }

    //divide and conquer
    double n = min(str1.length(), str2.length());
    int n_half = floor(n / 2);
        
    string a = str1.substr(0, ceil(n/2));
    string b = str1.substr(ceil(n/2));
    
    string c = str2.substr(0, ceil(n/2));
    string d = str2.substr(ceil(n/2));
    
    //calculate ac
    string p1 = karatsuma(a, c);
    
    //calculate bd
    string p2 = karatsuma(b, d);
    
    //calculate (a+b)(c+d)
    string sum1 = findsum(a, b);
    string sum2 = findsum(c, d);
    
    //for small values
    //string sum1 = to_string(stoi(a) + stoi(b)); 
    //string sum2 = to_string(stoi(c) + stoi(d)); 
    
    //remove leading zeros
    sum1.erase(0, min(sum1.find_first_not_of('0'), sum1.size()-1));
    sum2.erase(0, min(sum2.find_first_not_of('0'), sum2.size()-1));
    
    string p3 = karatsuma(sum1, sum2);
     
    //calculate pow
    string m1 = p1;
    for (i=0; i<n_half*2; i++) {
        m1 += "0";
    }
    
    string m2 = findsubtract(p3, findsum(p1, p2));
    m2.erase(0, min(m2.find_first_not_of('0'), m2.size()-1));
    
    //calculate pow
    for (i=0; i<n_half; i++) {
        m2 += "0";
    }
    
    //sum of results
    string result = findsum(findsum(m1, m2), p2);

    //for small values
    //string result = to_string(stoi(p1) * pow(10, n_half*2) + pow(10, n_half) * (stoi(p3) - stoi(p1) - stoi(p2)) + stoi(p2));

    return result; 
}

int main()
{
    
    string result = karatsuma("3141592653589793238462643383279502884197169399375105820974944592", "2718281828459045235360287471352662497757247093699959574966967627");
    cout<<result<<endl;
    //answer 
    //8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184
    
    return 0;
}

//end of file
