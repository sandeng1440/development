#include <iostream>
using namespace std;

class Marks{
private:
	int cw;
	int exam;
public:
	void Get(){
		cout<<"Enter the coursework:"<<endl;
		cin>>cw;
		cout<<"Enter the exam marks: "<<endl;
		cin>>exam;
		cout<<"Grade: "<<Grade(Add(cw, exam))<<endl;
	}
	int Add(int c, int e){
		return c + e;
	}
  char * val;
	char Grade(int t){
		switch(t){
			case (t >= 0 && t < 40):
        val = "E";
				return val;
				break;
			case (t > 39 && t < 50):
        const char val = "D";
				return val;
				break;
			case (t > 49 && t < 60):
        const char val = "C";
				return val;
				break;
			case (t > 59 && t < 70):
        const char val = "B";
				return val;
				break;
			default:
        const char val = "A";
				return val;
			
		}
	}
};

int main (){
  Marks m;
  m.Get();
  return 0;
}
