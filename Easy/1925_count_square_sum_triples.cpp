#include<cmath>
#include<numeric>
using std::sqrt;
/*
    Whoever thought this was an easy problem has serious mental health issues. Clearly a troll who vibe
    codes.
*/
class Solution1 {
public:
//This is an O(n^2) time complexity solution. It's efficient given the constraints, but it's hard for me 
//to be happy with a solution with such slow runtime
    int countTriples(const int& n) {
        int a{3}, b{4}, count{};
        for(int c2{a*a+b*b}; c2<=n*n; c2=a*a+b*b)
        {
            //this just checks if c2 has an integer square root. If it does, no data is lost when casting
            //sqrt() to int; casting causes loss of data otherwise
            if(int root{static_cast<int>(sqrt(c2))}; root*root==c2)
                count+=2;
            if(a==b-1 || (a+1)*(a+1)+b*b>n*n)
            {
                a=3;
                ++b;
            }else
                ++a;    
        }
        return count;
    }
};
class Solution2 {
public:
//This is an O(n*log(n)) time complexity solution, which uses Euclid's formula for pythagorean triples
    int countTriples(const int& n) {
        int i{2}, j{1}, count{};
        while(i*i+j*j<=n)
        {
            if(std::gcd(i,j)==1)
            {
                int c{i*i+j*j};
                count+=(n/c)*2;
            }
            if(j==i-1 || i*i+(j+2)*(j+2)>n)
            {
                ++i;
                j=(i % 2 == 0) ? 1 : 2;
            }else
                j+=2;
        }
        return count;
    }
};
