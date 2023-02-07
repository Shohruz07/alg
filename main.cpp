#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<queue>
#include <assert.h>
#include <locale.h>
#include <windows.h>
#include<fstream>
using namespace std;

class Arif_alg{
public:
    long long head = 1000000000;
    long long second = 100000000;
    void encode();
    int whole = 256;//A total of possible characters
	double bottom = -1;
	double zero = 0;//Underflow bits
	//Initialize Low High
	long long int l = 0;
	long long int h = 9999999999;

    void decode();

    double Letter_table(string a) {
        double high = 0;
        double low = 1;
        for (int i = a.length() - 1; i >= 0; i--) {
            high += (a[i] - '0')*low;
            low *= 10;
	}
	return high;
}
};




//coding
void Arif_alg::encode() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
	string text = "";//original
	string code = "";//coding
	vector<int> freq;
	//Read the original text
	ifstream in("input.txt");
	string tmp;
	while (getline(in, tmp)) {
		if (text == "") text = tmp;
		else {
			text += '\n' + tmp;
		}
	}
	text += "#"; cout<<"Text in input.txt: \n"<<text<<endl;
	//Initialize the probability table
	for (int i = 0; i <= 255; i++) {
		freq.push_back(1);
	}
	//Start processing the original text
	for (int i = 0; i < text.length(); i++) {
		int pos = int(text[i]);
		double range = (h - l) + 1;
		double num = 0;
		for (int j = 0; j < pos; j++) {
			num += freq[j];
		}
		h = l + range * (num + freq[pos]) / (whole + 1) - 1;
		l = l + range * num / (whole + 1);
		whole++;
		freq[pos]++;
		//Start shifting next
		//Start shift
		while ((l / head) == (h / head)) {
			double d = l / head;
			code = code + char(l / head + '0');
			l = (l  % head) * 10;
			h = (h   % head) * 10 + 9;
			//cout<<"  l:"<<l<<"  h:"<<h<<endl;
			char add = '0';
			if (d == bottom) {///////Long type is required! ! ! ! ! !
				add = '9';
			}
			while (zero) {
				zero--;
				code = code + add;
			}
			bottom = -1;
		}
		//Handle underflow
		while (h - l < second) {
			if (bottom == -1)bottom = l / head;
			zero++;
			int tmp = l / head;
			l = tmp * head + (l%second) * 10;
			tmp = h / head;
			h = tmp * head + (h%second) * 10 + 9;
		}
	}
	ifstream infile;
    ofstream outfile;
    infile.open("input.txt");
    outfile.open("original_text.txt");
    char buffer[1000];
    while(!infile.eof())
    {infile.getline(buffer,sizeof(buffer));
     outfile<<buffer<<endl;}
    infile.close();
    outfile.close();
	//All traversal completed
	double m = (l + h) / 2;
	string magic = to_string(m);
	while (magic.length() < 10) {
		magic = magic + "0";
	}
	code = code + magic;

	ofstream out("output.txt");
	out << code;
	cout<<"Code: "<<code<<endl;

}

//decoding
void Arif_alg::decode() {
    setlocale(LC_ALL, "");
     SetConsoleCP(1251); SetConsoleOutputCP(1251);
	string original = "";//original
	string code = "";//coding
	vector<int> freq;
	int whole = 256;//A total of possible characters
	double underflow = -1;
	double undernum = 0;
	//Initialize Low High
	long long int l = 0;
	long long int h = 9999999999;
	//Read into the code
	ifstream in("output.txt");
	in >> code; cout<<code<<endl;

	//Initialize the probability table
	for (int i = 0; i <= 255; i++) {
		freq.push_back(1);
	}
	long long int curcode = Letter_table(code.substr(0, 10));
	int pos = 10;//Currently running to which code
	int cur = 257;
	//Start decoding
	while (cur != int('#')) {
		double tmp = l;
		double range = (h - l) + 1;
		double num = 0;
		for (int j = 0; j < freq.size(); j++) {
			double th = tmp + range * (num + freq[j]) / (whole + 1) - 1;
			double tl = tmp + range * (num) / (whole + 1);
			num += freq[j];
			if (curcode >= tl && curcode < th) {
				cur = j;
				l = tl;
				h = th;
				whole++;
				freq[cur]++;
				break;
			}
		}
		if (cur != int('#')) {
			original = original + char(cur);
		}
		//Start shift
		while ((l / head) == (h / head)) {
			code = code + char(l / head + '0');
			l = (l  % head) * 10;
			h = (h   % head) * 10 + 9;
			curcode = (curcode%head) * 10 + code[pos] - '0';
			pos++;
		}
		//Handle underflow
		while (h - l < second) {
			double tmp = curcode / head;
			curcode = tmp * head + (curcode%second) * 10 + code[pos] - '0';
			pos++;
			tmp = l / head;
			l = tmp * head + (l%second) * 10;
			tmp = h / head;
			h = tmp * head + (h%second) * 10 + 9;
		}

	}
	ofstream out("original_text.txt");
	out << original;
cout<<original<<endl;


}


int main() {
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "");
    Arif_alg obj;
	obj.encode();
	system("pause");



	return 0;
}
