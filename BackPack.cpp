#include <iostream>

using namespace std;

void zeroArr(int* arr, int len);
bool getBit(unsigned char code, int pointer);
int GCD(int c, int N, int& d, int& y);

int main()
{
	int p[8],
		pSumm = 0,
		pk[8],
		pkSumm = 0,
		pkD[8],
		N = 0,
		c = 0,
		cMI = 0;
	int inputMsg = 0;
	unsigned char msg = 0;
	int msgEnc = 0, //always 2 byte length because of piSumm < N < 65536(2byte)
		msgDec = 0;
	//zero p & pk & pkD
	zeroArr(p, 8);
	zeroArr(pk, 8);
	zeroArr(pkD, 8);
	//Input
	cout << "Please enter Pi:\n";
	for (int i = 0; i < 8; i++)
	{
		cout << "p" << i << " ";
		cin >> p[i];
	}
	cout << endl;
	while (true)
	{
		cout << "Please enter N not greater then 65536: ";
		cin >> N;
		//check N
		if (N < 65536)
			break;
		else
			cout << endl;
	}
	cout << endl;
	cout << "Please enter c: ";
	cin >> c;
	cout << endl;
	cout << "Please enter message: ";
	cin >> inputMsg;
	msg = (unsigned char)inputMsg;
	//pi Summ
	for (int i = 0; i < 8; i++)
		pSumm += p[i] * getBit(msg, i)?1:0; //if bit(msg) == 1 then multiply by 1 else by 0
	cout << "Pi Summ done.\nSumm = " << pSumm << endl;
	//Pk generating
	for (int i = 0; i < 8; i++)
		pk[i] = (p[i] * c) % N; //pi * c mod N
	cout << "Pk generating done." << endl;
	//encrypting
	for (int i = 0; i < 8; i++)
		msgEnc += getBit(msg, i) ? pk[7-i] : 0; //if bit(msg) == 1 then +pk[i] else +0
	cout << "Encrypting done.\nEncrypted msg: " << msgEnc << endl;
	//show PK{N, c, pk[]}
	cout << "Your public key is:\n" <<
		"*****[ PK ]*****" <<
		"\nN = " << N <<
		"\nc = " << c <<
		"\n\t{Pk}\n";
	for (int i = 0; i < 8; i++)
		cout << i << ".Pk" << i << " = " << pk[i] << endl;
	cout << "****************" << endl;
	//show SK{p[]}
	cout << "Your private key is:\n" <<
		"*****[ SK ]*****" <<
		"\n\t{P}\n";
	for (int i = 0; i < 8; i++)
		cout << i << ". P" << i << " = " << p[i] << endl;
	cout << "****************" << endl;
	//Decrypt 1. getting cMI
	int d = 0, y = 0;
	GCD(c, N, d, y);
	cMI = N + d;
	cout << "d = " << d << " y = " << y << endl;
	cout << "Multiplication inverse c mod N is " << cMI << endl;
	//Decrpt 2. getting new msgE
	msgEnc = (msgEnc * cMI) % N; //Summ * c^-1 mod N
	//Decrypt 3. getting weigths
	for (int i = 7; i >= 0; i--)
	{
		msgDec <<= 1;
		if (msgEnc >= p[i])
		{
			msgDec++; // write 1
			msgEnc -= p[i];
		}
	}
	cout << "Decrypted msg is " << msgDec << endl;
	system("pause");
	return 0;
}

bool getBit(unsigned char code, int pointer) //pointer [0 - 7]
{
	//int length = 0;
	//length = binaryLen(code) - 1;
	unsigned char pointerBit = 0, temp = 0;
	pointerBit = pow(2, 7 - pointer);
	temp = code ^ pointerBit;
	if (temp < code)
		return true;
	else
		return false;
}

void zeroArr(int* arr, int len)
{
	for (int i = 0; i < len; i++)
		arr[i] = 0;
}

int GCD(int c, int N, int& d, int& y) 
{
	if (c == 0) {
		d = 0; y = 1;
		return N;
	}
	int x1, y1;
	int gcd = GCD(N % c, c, x1, y1);
	d = y1 - (N / c) * x1;
	y = x1;
	return gcd;
}