#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;
ostream &n(ostream &stream){
	cout << "\n";
	return stream;
}
void menu(){
	cout << n << "Использование : \n \n./programm file.name чтение(1)/добавление(2)/перезапись(3)/\n  копирование(4)/произвольная вставка(5)" 
	<< n << n;
}

class DATA{
	fstream file;
	public:
	DATA(string filename,ios::openmode mode) {
		file.open(filename,mode);
		if(!file){
			cerr << "\nНе удалось окрыть файл '" << filename << "'" << "\n\nЭкстренное завершение программы \n";
			abort();
		}
	}
	DATA(){}
	~DATA(){
		if(file.is_open())file.close();
	}
	friend ostream& operator<<(ostream &stream,DATA &f){
		string temp;
		char ch;
		while(f.file.get(ch)) temp += ch;
		stream << temp;
		return stream;
	}
	friend istream& operator>>(istream &stream,DATA &f){
		string str;
		getline(stream,str);
		f.file << str;
		return stream;
	}
	
	void setfile(string filename,ios::openmode mode){
		file.open(filename,mode);
		if(!file){
			cerr << "\nНе удалось окрыть файл '" << filename << "'" << "\n\nЭкстренное завершение программы \n";
			abort();
		}
	}
	void read(){
		char ch;
		cout << n;
		int sz = 0;
		while(file.get(ch)){
			cout << ch;
			sz++;
		}
		cout << n << "Общий размер файла : " << sz << " байт";
		file.close();
	}
	void readesc(){
		char ch;
		int sz = 0;
		cout << n;
		while(file.get(ch)){
			if(ch == '\\' && file.peek() == 'n'){
				sz += 2;
				cout << n;
				file.get(ch);
				continue;
			}
			if(ch == '\\' && file.peek() == 't'){
				sz += 2;
				cout << '\t';
				file.get(ch);
				continue;
			}
			if(ch == '\\' && file.peek() == 'v'){
				sz += 2;
				cout << '\v';
				file.get(ch);
				continue;
			}
			if(ch == '\\' && file.peek() == 'f'){
				sz += 2;
				cout << '\f';
				file.get(ch);
				continue;
			}
			sz++;
			cout << ch;
		}
		cout << n << "Общий размер файла : " << sz << " байт";
	}
	void copy(string fname){
		ofstream f(fname,ios::out | ios::binary);
		char ch;
		while(file.get(ch)) f.put(ch);
		f.close();
	}
	void writef(const char *s){
		file.write(s,strlen(s));
	}
};
