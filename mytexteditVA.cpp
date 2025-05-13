#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;
ostream &n(ostream &stream){
	stream << "\n";
	return stream;
}
void read(fstream &f){
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
	cout << n << n << "Размер файла : " << size << " байт" << n ;
	f.close();
}
void write(char* s,fstream &f){
	int i = 0;
	while(s[i]) f.put(s[i++]);
	f.close();
}
void copy(fstream &f,char* fname){
	fstream file(fname,ios::out | ios::trunc);
	char ch;
	while(f.get(ch)) file.put(ch);
	file.close();
	f.close();
}
void paste(int byte,string str,string file){
	ofstream w;
	ifstream r;
	r.open(file);
	string temp;
	char ch;
	while(r.get(ch)) temp += ch;
	temp.insert(byte,str);
	r.close();
	w.open(file,ios::out | ios::trunc);
	w<<temp;
	w.close();
}
void erase(int start,int count,char* fname){
	fstream f(fname,ios::in);
	if(start>0) start--;
	string temp;
	char ch;
	while(f.get(ch)) temp += ch;
	temp.erase(start,count);
	f.close();
	f.open(fname,ios::out | ios::trunc);
	f << temp;
}
void search(string str,fstream &file){
	string temp;
	char ch;
	while(file.get(ch)) temp += ch;
	int index = temp.find(str);
	if(index == string::npos){
		cout << n << "Строка не найдена" << n;
		return;
	}
	int size = index + str.size();
	cout << n << "Байт начала строки : " << index << n;
	cout << n << "Байт конца строки : " << size << n;
	file.close();
}
void menu(){
	cout << n << "Использование : \n \n./programm file-name чтение(-rd)/добавление(-a)/перезапись(-rw)/";
	cout << "\n  копирование(-cp)/произвольная вставка(-p)/стереть(-e)/поиск строки(-f)"
	<< n << n;
}
int main(int argc,char *argv[]){
	if(argc<3){
		menu();
		return 1;
	}
	if(strcmp(argv[2],"-rd") && strcmp(argv[2],"-a") && strcmp(argv[2],"-rw") && strcmp(argv[2],"-cp") && strcmp(argv[2],"-p") && strcmp(argv[2],"-e") && strcmp(argv[2],"-f")){
		menu();
		return 1;
	}
	if(!strcmp(argv[2],"-rd")){
		if(argc>3){
			cout << "Использование функции чтение(-rd) : " << n
			<< "./programm file-name -rd" << n;
			return 1;
		}
		fstream file(argv[1],ios::in);
		if(!file){
			cout << "Не удалось открыть файл '" << argv[1] << "'" << n;
			return 1;
		}
		read(file);
	}
	if(!strcmp(argv[2],"-a")){
		if(argc<4){
			cout << "Использование функции добавление(-a) : " << n
			<< "./programm file-name -a ваша_строка" << n;
			return 1;
		}
		fstream file(argv[1],ios::out | ios::app);
		if(!file){
			cout << "Не удалось открыть файл '" << argv[1] << "'" << n;
			return 1;
		}
		write(argv[3],file);
	}
	if(!strcmp(argv[2],"-rw")){
		if(argc<4){
			cout << "Использование функции перезапись(-rw) : " << n
			<< "./programm file-name -rw ваша_строка" << n;
			return 1;
		}
		fstream file(argv[1],ios::out | ios::trunc);
		if(!file){
			cout << "Не удалось открыть файл '" << argv[1] << "'" << n;
			return 1;
		}
		write(argv[3],file);
	}
	if(!strcmp(argv[2],"-cp")){
		if(argc<4){
			cout << "Использование функции копирование(-cp) : " << n
			<< "./programm file-name -cp to-file-name" << n;
			return 1;
		}
		fstream file(argv[1],ios::in);
		if(!file){
			cout << "Не удалось открыть файл '" << argv[1] << "'" << n;
			return 1;
		}
		if(!strcmp(argv[1],argv[3])){
			system("echo \"\e[31mНеверный ввод\e[0m\"");
			return 1;
		}
		copy(file,argv[3]);
	}
	if(!strcmp(argv[2],"-p")){
		if(argc<5){
			cout << "Использование функции произвольная вставка(-p) : " << n
			<< "./programm file-name -p байт ваша_строка" << n;
			return 1;
		}
		paste(atoi(argv[3]),argv[4],argv[1]);
	}
	if(!strcmp(argv[2],"-e")){
		if(argc != 5){
			cout << "Использование функции стереть(-e) : " << n
			<< "./programm file-name -e байт-начало байт-количество" << n;
			return 1;
		}
		erase(atoi(argv[3]),atoi(argv[4]),argv[1]);
	}
	if(!strcmp(argv[2],"-f")){
		if(argc != 4){
			cout << "Использование функции поиск строки(-f) : " << n
			<< "./programm file-name -f ваша_строка" << n;
			return 1;
		}
		fstream file(argv[1],ios::in);
		if(!file){
			cout << "Не удалось открыть файл '" << argv[1] << "'" << n;
			return 1;
		}
		search(argv[3],file);
	}
}
