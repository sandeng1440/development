#include <iostream>
#include <cmath>
#include <complex>
using namespace std;

class quadratic{
private:
  float a, b, c;
  double x1,x2;
public:
void getRoots(){
  cout<<"Enter the values of in the form: ax2 + bx + c"<<endl;
  cout<<"a: ";
  cin>>a;
  cout<<endl<<"b: ";
  cin>>b;
  cout<<endl<<"c: ";
  cin>>c;
  cout<<endl;
  
  float det = ((b*b) - 4*(a * c));
  if (det < 0){
    cout<<"The roots are not real"<<endl;
    return;
  }

  x1 = (-b + sqrt(det)) / (2*a);
  x2 = (-b - sqrt(det)) / (2*a);
  cout<<"Roots: "<<x1<<" and "<<x2<<endl;

}


};
int main(){
  int ch;
  quadratic quad;
  do {
    cout<<"Choose:"<<endl<<"1) enter a new quadratic function"<<endl<<"2) quit"<<endl;
    cin>>ch;
    if(ch == 1){
      quad.getRoots();
    }
  } while (ch != 2);
  return 0;
}
