#include <iostream> 
#include <sstream> 
using namespace std; 
int main()   
{ 
	istringstream istr;
    string s="1 \n 56.7";
	istr.str(s); 
    //�����������̿��Լ�д�� istringstream istr("1 56.7"); 
    cout << istr.str()<<endl; 
    int a; 
    float b; 
	istr>>a; 
    cout<<a<<endl; 
	istr>>b; 
    cout<<b<<endl; 
    s="23 \n 56.7";
    
    istr>>a; 
    cout<<a<<endl; 
	istr>>b; 
    cout<<b<<endl; 
	system("pause"); 
	ostringstream ostr; 
    ostr.str("abc");//��������ʱ���������ַ�������,��ô����������ʱ�򲻻�ӽ�        β��ʼ����,�����޸�ԭ������,�����Ĳ������� 
    ostr.put('d'); 
    ostr.put('e'); 
    ostr<<"fg"; 

    string gstr = ostr.str(); 
    cout<<gstr; 
    system("pause"); 
stringstream sstr("ccc"); 
sstr.put('d'); 
sstr.put('e'); 
sstr<<"fg"; 
 gstr = sstr.str(); 
cout<<gstr<<endl; 
system("pause"); 
char ch;
sstr>>ch; 
cout<<ch<<endl;
cout<<sstr.str()<<endl;
sstr<<"hij";
cout<<sstr.str()<<endl;
sstr>>ch; 
cout<<ch<<endl;

system("pause"); 
}

