/*
 * CFunctions.cpp
 * 14. Определить класс CVector для работы с вектором вещественных
 * чисел. Длина вектора задается в конструкторе класса. В классе
 * должны быть определены необходимые конструкторы, деструктор, операторы сло-
 * жения, вычитания, скалярного умножения.
 * Написать функцию и конструктор сохранения переменной данного
 * типа в файл и загрузки из файла.
 * В отдельном файле должен быть написан тест на данный класс.
 *     
 */
 
 
#include<iostream>
#include<fstream>
#include <sstream>
#include"CVektor.h"
//size_t glob_n;
//////////////////CLASS METHODS///////////////////////////
//////CVektor
void CVektor::CopyOnly(const CVektor &v)
    {
     if(this!=&v)
     {memcpy(ptrArr=new float[n=v.n], v.ptrArr, v.n*sizeof(float)); }
    }
void CVektor::GetVektor()        //Задать вектор
    {
        //cout << "Введите размерность вектора: "; cin >> n;
        for (size_t i=0; i < n; i++ )
        {
            cout << "Введите элемент вектора № " << i << ": ";
            cin >> ptrArr[i];
        }
    }
void CVektor::ShowVektor()       //Показать вектор
    {
        cout << "Вектор {";
        for (size_t i=0; i < n; i++)
        {  
         if(i<n-1)
            cout << ptrArr[i] << ", ";
         else
            cout << ptrArr[i];
        }    
        cout << "}\n";
    }
 
CVektor& CVektor::operator=(const CVektor& v)
    {
        if(this!=&v) 
        {if(ptrArr!=NULL)delete [] ptrArr;
         CopyOnly(v);}
        return *this;
    }
/*CVektor& CVektor::operator=( CVektor0 &b)
{ 
if(this!=&b )
{memcpy(ptrArr,b.getPtrArr(),b.getN()*sizeof(float)); n=b.getN();} 
return *this;
}*/
/*static */
CVektor** CVektor::Input(const char *fn)
{

CVektor **v=new CVektor*[11]; 
memset(v,0,sizeof(CVektor*)*11);
//CVektor **v=NULL;
std::ifstream finput; 
//char mystring[100];
   finput.open(fn, ios::in);
   if (!finput) {
    cout << "File error - can't open to read data!";
    cin.sync(); cin.get(); throw -1;
   }
   
       bool b; unsigned short int k=0; int n=0;
       char s[15]; string str;
     //for(int i=0;!(finput.eof());i++)
     //if ((fgets(mystring[i], 100, f) != NULL) ) // считать символы из файла
      size_t i=0;
      //LC:
      while(getline(finput,str))
      {stringstream ss(str);
      //finput.getline(mystring, 100);
       //вырезать имя файла и присвоить его
      ss >> b;
      //if(b==1) {goto lk;}
      ss >> s;
      //cout<<"\ns="<<s<<endl;
      ss >> n;
      //cout<<"n="<<n<<endl;
      if(b==0) { v[i]=new CVektor0(n); //maybe need to kill vec
                 v[i]->setText(s);
                 }
      else if(b==1) {v[i]=new CVektor1(n); //maybe need to kill vec
                     v[i]->setText(s);
                    }
      //cout<<"xxx";
      for(int j=0;(ss>>k)&&(j<n);j++)
      {
       if(k>9) {cout<<"WRONG DATA! Цифра принимает значение от 0 до 9.\n"; finput.close();delete[]v;throw -1;}
       (*v[i]).setPos(j,k);
      }
      //cout<<endl;
      //if(finput.eof()){break;}
      i++;
       }   
       //REMEMBER IT!
       glob_n=i;
   
     //  lk:
    finput.close();
     //fclose (f);

return v;
}
//////CVektor0    
int CVektor0::output(const char *FileName)
{
   
   if(FileName){
   std::ofstream foutput;
   if (!foutput) {
    cout << "File error - can't open to write data!";
    cin.sync(); cin.get(); throw -1;
   }
   foutput.open(OutFile, ios::out | ios::app);
       for(size_t i=0;i<n;i++){foutput<<ptrArr[i]<<" ";} 
       foutput<<endl;
       //cout<<*this;
          
     //  lk:
    foutput.close();
  }
     return 0;

}
    
/////CVektor1
int CVektor1::output(const char *FileName)
{
  // char mystring[100];
 
   //if (f == NULL) perror("Ошибка открытия файла");
   //else
   if(FileName){
  std::ofstream foutput;
   if (!foutput) {
    cout << "File error - can't open to write data!";
    cin.sync(); cin.get(); throw -1;
   }
  
   foutput.open(OutFile, ios::out | ios::app);
   {
       foutput<<"{\n";
       for(size_t i=0;i<n;i++){foutput<<ptrArr[i]<<endl;} 
       foutput<<"}\n";
        // cout<<*this;
         //foutput<<this;
  
          
    foutput.close();
  }
}
return 0;
}
    
    
    
/////////OPERATORS///////////////
CVektor& operator+(const CVektor &lhs, const CVektor &rhs)
{
 if(lhs.getN()==rhs.getN())
     {
     //const CVektor& w=rhs; const CVektor& u=lhs; 
     const CVektor& tmpl=lhs; const CVektor& tmpr=rhs;
     CVektor& l=const_cast<CVektor&>(tmpl);//=const_cast<CVektor&>(w);
     CVektor& r=const_cast<CVektor&>(tmpr);
     CVektor& res=r;
     for (size_t i=0; i < lhs.getN(); i++ ) {
        (res)[i]= (l).getPtrArr()[i]+(r).getPtrArr()[i];
        //r[i]=lhs[i]+rhs[i];
        }
     return (res);
     }
    else 
    {
     cout << "Вектора должны быть одинаковой длины!\n"; 
     throw -1;
    }
}
//поменять? это не похоже на правду... мняются исходники либо отбрасывается квалификатор...
CVektor& operator-(const CVektor &lhs, const CVektor &rhs) 
{
 if(lhs.getN()==rhs.getN())
     {
     const CVektor& tmpl=lhs; const CVektor& tmpr=rhs;
     CVektor& l=const_cast<CVektor&>(tmpl);//=const_cast<CVektor&>(w);
     CVektor& r=const_cast<CVektor&>(tmpr);
     CVektor& res=r;
     for (size_t i=0; i < lhs.getN(); i++ ) {
        (res)[i]= (l).getPtrArr()[i]+(r).getPtrArr()[i];
        }
     return (res);
     }
    else 
    {
     cout << "Вектора должны быть одинаковой длины!\n"; 
     throw -1;
    }
} 
/*CVektor0& operator+(const CVektor0 &lhs, const CVektor0 &rhs)
{
 if(lhs.getN()==rhs.getN())
     {
     //const CVektor& w=rhs; const CVektor& u=lhs; 
     const CVektor0& tmpl=lhs; const CVektor0& tmpr=rhs;
     CVektor0& l=const_cast<CVektor0&>(tmpl);//=const_cast<CVektor&>(w);
     CVektor0& r=const_cast<CVektor0&>(tmpr);
     CVektor0& res=r;
     for (size_t i=0; i < lhs.getN(); i++ ) {
        (res)[i]= (l).getPtrArr()[i]+(r).getPtrArr()[i];
        //r[i]=lhs[i]+rhs[i];
        }
     return (res);
     }
    else 
    {
     cout << "Вектора должны быть одинаковой длины!\n"; 
     throw -1;
    }
}
//поменять
CVektor0& operator-(const CVektor0 &lhs, const CVektor0 &rhs) 
{
 if(lhs.getN()==rhs.getN())
     {
     const CVektor0& tmpl=lhs; const CVektor0& tmpr=rhs;
     CVektor0& l=const_cast<CVektor0&>(tmpl);//=const_cast<CVektor&>(w);
     CVektor0& r=const_cast<CVektor0&>(tmpr);
     CVektor0& res=r;
     for (size_t i=0; i < lhs.getN(); i++ ) {
        (res)[i]= (l).getPtrArr()[i]+(r).getPtrArr()[i];
        }
     return (res);
     }
    else 
    {
     cout << "Вектора должны быть одинаковой длины!\n"; 
     throw -1;
    }
} */
CVektor1& operator+(const CVektor1 &lhs, const CVektor1 &rhs)
{
 if(lhs.getN()==rhs.getN())
     {
      const CVektor1& tmpl=lhs; const CVektor1& tmpr=rhs;
     CVektor1& l=const_cast<CVektor1&>(tmpl);//=const_cast<CVektor&>(w);
     CVektor1& r=const_cast<CVektor1&>(tmpr);
     CVektor1& res=r;
     for (size_t i=0; i < lhs.getN(); i++ ) {
        (res)[i]= (l).getPtrArr()[i]+(r).getPtrArr()[i];
        }
     return (res);
     /*const CVektor1& res=rhs;
     for (size_t i=0; i < lhs.getN(); i++ ) {
        const_cast<CVektor1&>(res)[i]= const_cast<CVektor1&>(lhs).getPtrArr()[i]+const_cast<CVektor1&>(rhs).getPtrArr()[i];
        //r[i]=lhs[i]+rhs[i];
        }
     return const_cast<CVektor1&>(res);*/
     }
    else 
    {
     cout << "Вектора должны быть одинаковой длины!\n"; 
     throw -1;
    }
}
CVektor1& operator-(const CVektor1 &lhs, const CVektor1 &rhs)
{
 if(lhs.getN()==rhs.getN())
     {
      const CVektor1& tmpl=lhs; const CVektor1& tmpr=rhs;
     CVektor1& l=const_cast<CVektor1&>(tmpl);//=const_cast<CVektor&>(w);
     CVektor1& r=const_cast<CVektor1&>(tmpr);
     CVektor1& res=l;
     for (size_t i=0; i < lhs.getN(); i++ ) {
        (res)[i]= (l).getPtrArr()[i]-(r).getPtrArr()[i];
        }
     return (res);
     }
    else 
    {
     cout << "Вектора должны быть одинаковой длины!\n"; 
     throw -1;
    }
}
/*CVektor& CVektor::operator=(const CVektor&& v)
    {
        if(this!=&&v) 
        {Clean(); CopyOnly(v);}
        return *this;
    }*/
/*CVektor& CVektor::operator+(const CVektor &v) 
    {
     CVektor& r=const_cast<CVektor&>(v);r.SetZero();
     if(n==v.n)
     {
     for (size_t i=0; i < n; i++ ) {
        r[i]= v.ptrArr[i]+ptrArr[i];
        }
     return r;
     }
    else 
    {
     cout << "Вектора должны быть одинаковой длины!\n"; 
     throw -1;
    }
    }
CVektor1& CVektor1::operator+(const CVektor1 &v) 
    {
     //size_t m=v.n; //CVektor1 const_cast<CVektor1&>(w)=v;
     CVektor1& r=const_cast<CVektor1&>(v);//r.SetZero();
     if(n==v.n)
     {for (size_t i=0; i < n; i++ ) { r[i]= v.ptrArr[i]+ptrArr[i];} return r;}
     else {cout << "n="<<n<<"; v.n="<<v.n<<"; Вектора должны быть одинаковой длины!\n"; throw -1;}
    }*//*
CVektor& CVektor::operator-(const CVektor &v) 
    {
     CVektor& r=const_cast<CVektor&>(v);r.SetZero();
      if(n==v.n)
     {
     for (size_t i=0; i < n; i++ ) {
        r[i]= ptrArr[i]-v.ptrArr[i];
        }
     return r;
     }
    else 
    {
     cout << "Вектора должны быть одинаковой длины!\n"; 
     throw -1;
    }
    }*/
/*CVektor1& CVektor1::operator-(const CVektor1 &v) 
    {
     //size_t m=v.n; //CVektor1 const_cast<CVektor1&>(w)=v;
     const CVektor1 &w=v;
     CVektor1& r=const_cast<CVektor1&>(v);//r.SetZero();
     if(n==v.n)
     {for (size_t i=0; i < n; i++ ) { r.setPos(i, ptrArr[i]-v.ptrArr[i]);} 
     const_cast<CVektor1&>(v)=const_cast<CVektor1&>(w);return r;}
     else {cout << "n="<<n<<"; v.n="<<v.n<<"; Вектора должны быть одинаковой длины!\n"; throw -1;}
    }*/
float CVektor::operator *(const CVektor &v)
    {
      float r=0;
     //n=v.n;
     if(n==v.n)
     {
     for (size_t i=0; i < v.n; i++ ) {
        r += v.ptrArr[i]*ptrArr[i];
        }
     return r;
     }
    else 
    {
     cout << "Вектора должны быть одинаковой длины!\n"; 
     throw -1;
    }
    }

//////////////////FRIEND FUNCTIONS////////////////////////

ostream &operator<<(ostream& cout, CVektor &v) 
{
   cout << "Вектор {";
     for (size_t i=0; i < v.n; i++)
     { 
     if(i<v.getN()-1)
 //        cout << v.getPtrArr()[i]  << ", ";
       cout << v.ptrArr[i]  << ", ";
     else //if(i == v.n-1)
 //        cout << v.getPtrArr()[i]; 
        cout << v.ptrArr[i] ;
     }    
   cout << "}\n";

return cout;
}
istream &operator>>(istream& cin , CVektor &v) 
{
 for (size_t i=0,p; i < v.getN(); i++ )
        {
            cout << "Введите элемент вектора № " << i << ": ";
            cin >> p;      //v.ptrArr[i];
            v.ptrArr[i]=p;
        }
return cin;
}
