#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;
ostream &n(ostream &stream){
	stream << "\n";
	return stream;
}
void read(ifstream &f){
	char ch;
	int size = 0;
	cout << n;
	while(f.get(ch)){
		if(ch == '\\' && f.peek() == 'n'){
			cout << n ;
			f.get(ch);
			size += 2;
			continue;
		}
		if(ch == '\\' && f.peek() == 't'){
			cout << '\t';
			f.get(ch);
			size += 2;
			continue;
		}
		cout << ch;
		size++;
	}
	cout << n << n << "Всего символов(включая невидимые) : " << size << n ;
	f.close();
}
void write(string s,ofstream &f){
	int i = 0;
	while(s[i]) f.put(s[i++]);
	f.close();
}
void copy(ofstream &to,ifstream &from){
	char ch;
	while(from.get(ch)) to.put(ch);
	from.close();
	to.close();
}
void paste(int byte,string str,string file){
	ofstream w;
	ifstream r;
	r.open(file);
	string temp_beg;
	string temp_end;
	char ch;
	
	for(int i = 0;i<byte && r.get(ch);i++) temp_beg += ch;
	
	while(r.get(ch)) temp_end += ch;
	r.close();
	temp_beg += str + temp_end;
	w.open(file,ios::out | ios::trunc | ios::binary);
	w<<temp_beg;
	w.close();
}
void erase(int from,int to,ofstream &f){}
void menu(){
	cout << n << "Использование : \n \n./programm file.name чтение(1)/добавление(2)/перезапись(3)/\n  копирование(4)/произвольная вставка(5)" 
	<< n << n;
}
int main(int argc,char *argv[]){
	if(argc < 3 || argc > 3){
		menu();
		return 1;
	}
	if(atoi(argv[2]) == 1){
		ifstream file(argv[1],ios::in);
		if(!file)
		{
			cout << "Не удалось открыть файл " << "\'" << argv[1] << "\'" << n;
			return 1;
		}
		read(file);
	}
	if(atoi(argv[2]) == 2){
		ofstream file(argv[1],ios::out | ios::app | ios::binary);
		string str;
		getline(cin,str);
		write(str,file);
	}
	if(atoi(argv[2]) == 3){
		ofstream file(argv[1],ios::out | ios::trunc);
		string s;
		getline(cin,s);
		write(s,file);
	}
	if(atoi(argv[2]) == 4){
		ifstream what(argv[1],ios::in | ios::binary);
		if(!what)
		{
			cout << "Не удалось открыть файл " << "\'" << argv[1] << "\'" << n;
			return 1;
		}
		string s;
		cin >> s;
		ofstream where(s,ios::out | ios::trunc | ios::binary);
		copy(where,what);
	}
	if(atoi(argv[2]) == 5){
		cout << n << "Введите байт и строку" << n;
		string s;
		int b;
		cin >> b;
		getline(cin,s);
		paste(b,s,argv[1]);
	}
}
