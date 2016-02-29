#include<iostream>

long long int fact(long long int x)
{
   long long int out=1;
   while(x>1)
   {
      out*=x;
      x--;
   }
   return out;
}

int main()
{
   int y=20;
   long long int z;
   while(1)
   {
      z=fact(y);
      std::cout<<z<<std::endl;
   }

}
