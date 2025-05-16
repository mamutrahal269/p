#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
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
	cout << n << n << "Размер файла: " << size << " байт" << n ;
	f.close();
}
void write(string s,fstream &f){
	int i = 0;
	while(s[i]) f.put(s[i++]);
	f.close();
}
void copy(fstream &f,string fname){
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
	try{
		temp.insert(byte,str);
	}catch(out_of_range& err){
		cerr << "Выход за границы файла! \n";
		exit(1);
	}
	r.close();
	w.open(file,ios::out | ios::trunc);
	w<<temp;
	w.close();
}
void erase(int start,int count,string fname){
	fstream f(fname,ios::in);
	string temp;
	char ch;
	while(f.get(ch)) temp += ch;
	try{
		temp.erase(start,count);
	}catch(out_of_range& err){
		cerr << "Выход за границы файла!\n";
		exit(1);
	}
	f.close();
	f.open(fname,ios::out | ios::trunc);
	f << temp;
}
void search(string str,fstream &file){
	string temp;
	char ch;
	while(file.get(ch)) temp += ch;
	int index = temp.find(str);
	if(index == -1){
		cout << n << "Строка не найдена" << n;
		return;
	}
	int size = index + str.size();
	cout << n << "Байт начала строки: " << index << n;
	cout << n << "Байт конца строки: " << size << n;
	file.close();
}
void menu(){
	cout << n << "Использование : \n \n./programm file-name чтение(-rd)/добавление(-a)/перезапись(-rw)/";
	cout << "\n  копирование(-cp)/произвольная вставка(-p)/стереть(-e)/поиск строки(-f)"
	<< n << n;
}
int main(int argc,char* argv[]){
	vector<string> args(argv, argv + argc);
	if(args.size() < 3 || args[1] == "--help"){
		menu();
		return 1;
	}
	if(args[2] == "-rd"){
		fstream file(args[1],ios::in);
		if(!file){
			cerr << "Не удалось открыть файл \'" << args[1] << "\'" << n;
			return 1;
		}
		read(file);
		return 0;
	}
	if(args[2] == "-a"){
		if(args.size() < 4){
			string str;
			cout << "Введите текст: " << n;
			getline(cin,str);
			args.push_back(str);
		}
		fstream file(args[1],ios::out | ios::app);
		if(!file){
			cerr << "Не удалось открыть файл \'" << args[1] << "\'" << n;
			return 1;
		}
		write(args[3],file);
		return 0;
	}
	if(args[2] == "-rw"){
		if(args.size() < 4){
			string str;
			cout << "Введите текст: " << n;
			getline(cin,str);
			args.push_back(str);
		}
		fstream file(args[1],ios::out | ios::trunc);
		if(!file){
			cerr << "Не удалось открыть файл \'" << args[1] << "\'" << n;
			return 1;
		}
		write(args[3],file);
		return 0;
	}
	if(args[2] == "-cp"){
		if(args.size() < 4){
			string str;
			cout << "Введите имя файла: " << n;
			getline(cin,str);
			args.push_back(str);
		}
		if(args[1] == args[3]){
			cerr << "Такое копирование запрещено" << n;
			return 1;
		}
		fstream file(args[1],ios::in);
		if(!file){
			cerr << "Не удалось открыть файл \'" << args[1] << "\'" << n;
			return 1;
		}
		copy(file,args[3]);
	}
	if(args[2] == "-p"){
		if(args.size() <= 4){
			if(args.size() == 4) args.pop_back();
			string byte;
			string str;
			cout << "Введите байт: " << n;
			cin >> byte;
			args.push_back(byte);
			cout << "Введите текст: " << n;
			cin >> str;
			args.push_back(str);
		}
		int byte;
		try{
			byte = stoi(args[3]);
		} catch (const std::invalid_argument& err) {
			cerr << "Некорректный числовой аргумент: " + args[3] << n;
			return 1;
		} catch (const std::out_of_range& err) {
			cerr << "Число вне диапазона: " + args[3] << n;
			return 1;
		}
		paste(byte,args[4],args[1]);
		return 0;
	}
	if(args[2] == "-e"){
		if(args.size() <= 3){
			string bt;
			string cnt;
			cout << "Введите начальный байт: " << n;
			cin >> bt;
			args.push_back(string(bt));
			cout << "Введите количество байт: " << n;
			cin >> cnt;
			args.push_back(string(cnt));
		}
		int start;
		int count;
		try{
			start = stoi(args[3]);
		} catch (invalid_argument& err) {
			cerr << "Некорректный числовой аргумент: " << args[3] << n;
			return 1;
		} catch (out_of_range& err) {
			cerr << "Число вне диапазона: " << args[3] << n;
			return 1;
		}
		try{
			count = stoi(args[4]);
		} catch (invalid_argument& err) {
			cerr << "Некорректный числовой аргумент: " << args[4] << n;
			return 1;
		} catch (out_of_range& err) {
			cerr << "Число вне диапазона: " << args[4] << n;
			return 1;
		}
		erase(start,count,args[1]);
		return 0;
	}
	if(args[2] == "-f"){
		if(args.size() < 4){
			string str;
			cout << "Введите текст: " << n;
			cin >> str;
			args.push_back(str);
		}
		fstream file(args[1],ios::in);
		if(!file){
			cerr << "Не удалось открыть файл \'" << args[1] << "\'" << n;
			return 1;
		}
		search(args[3],file);
		return 0;
	}
}
