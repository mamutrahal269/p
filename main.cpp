#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
ostream &n(ostream &stream){
	stream << "\n";
	return stream;
}
void reader(ifstream &f){
	char ch;
	int size = 0;
	cout << n;
	while(f.get(ch)){
		if(ch == '\\' && f.peek() == 'n'){
			cout << "\n";
			f.get(ch);
			continue;
		}
		if(ch == '\\' && f.peek() == 't'){
			cout << '\t';
			f.get(ch);
			continue;
		}
		cout << ch;
		size++;
	}
	cout << n << n << "Всего символов(включая невидимые) : " << size << n ;
	f.close();
}
void writer(string s,ofstream &f){
	int i = 0;
	while(s[i]) f.put(s[i++]);
	f.close();
}
void copier(ofstream &to,ifstream &from){
	char ch;
	while(from.get(ch)) to.put(ch);
	from.close();
	to.close();
}
void menu(){
	cout << n << "Использование : \n \n./programm file.name чтение(1)/добавление(2)/перезапись(3)/\n  копирование(4)/изменение байта(5)" 
	<< n << n;
}
int main(int argc,char *argv[]){
	if(argc < 3 || argc >= 4){
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
		reader(file);
	}
	if(atoi(argv[2]) == 2){
		ofstream file(argv[1],ios::out | ios::app | ios::binary);
		string str;
		getline(cin,str);
		writer(str,file);
	}
	if(atoi(argv[2]) == 3){
		ofstream file(argv[1],ios::out | ios::trunc);
		string s;
		getline(cin,s);
		writer(s,file);
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
		ofstream where(s,ios::out | ios::trunc);
		copier(where,what);
	}
}
