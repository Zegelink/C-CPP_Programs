#include <iostream>
#include <string>
using namespace std;

void transform2(int num, int base, string& s){
    int q;
    int r;
    q= num/base;
    r= num%base;
    char letter[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    
    if(q == 0){
    }
    else{
        transform2(q, base, s);
    }
    s.push_back(letter[r]);
}

int main(){
    
    string s;
    int a;
    int b;
    cout<<"This program converts a decimal(base 10) number into another base recursively"<<endl;
    cout<<"Enter a positive base 10 number you want to convert"<<endl;
    cin>>a;
    cout<<"Enter the base(between 2 ~ 16) you desired"<<endl;
    cin>>b;
    transform2(a, b, s);
    cout<<s<<endl;
    return 0;
    
}
