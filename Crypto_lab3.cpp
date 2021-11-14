#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <string.h>
#include <cmath>
#include <vector>
#include <sstream>
using namespace std;

//S盒
unsigned char S[16][16] = 
  { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

//逆S盒
unsigned char S_ni[16][16] = 
  { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

static const int colM[4][4] = 
{ 2, 3, 1, 1,
  1, 2, 3, 1,
  1, 1, 2, 3,
  3, 1, 1, 2 };

static const int decolM[4][4] = 
{ 0x0E, 0x0B, 0x0D, 0x09,
  0x09, 0x0E, 0x0B, 0x0D,
  0x0D, 0x09, 0x0E, 0x0B,
  0x0B, 0x0D, 0x09, 0x0E };

unsigned char Rcon[4][10] = 
{
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};   //轮常数

struct key
{
    unsigned char key[4][4];
}Roundkey[11];  //存放轮密钥

string strToHex(string str);		//string 转换为十六进制
void convertTo44Array(string str, unsigned char a[4][4]);   //字符串转化为4*4矩阵
string Array44Tostr(unsigned char a[4][4]);                 //4*4矩阵转化为字符串
int getLeft4bit(unsigned char a);                           //取字节左四位
int getRight4bit(unsigned char a);                          //取字节右四位
unsigned char Schange(unsigned char a);                     //按照索引取S盒中的元素
void subBytes(unsigned char a[4][4]);                       //S盒替换
unsigned char Schange_ni(unsigned char a);                  //按照索引取逆S盒中的元素
void subBytes_ni(unsigned char a[4][4]);                    //S盒逆替换
void AddKey(unsigned char a[4][4],unsigned char b[4][4]);   //轮密钥加
void RowShift(unsigned char state[4][4]);                   //行变换，按字节循环左移
void RowShift_ni(unsigned char state[4][4]);                //行移位逆变换
void ColMix(unsigned char state[4][4]);                     //列混合
unsigned char AES_MUL(int n,unsigned char a);               //AES字乘法
unsigned char XMUL(unsigned char s);                        //X乘
void extendKey(string s);                                   //轮密钥生成，n表示第几轮，从0开始
void DeColMix(unsigned char state[4][4]);                   //列混合逆变换
void encrypt(unsigned char plain[4][4]);                    //加密函数
void decrypt1(unsigned char cipher[4][4]);                  //直接逆变换的解密函数
void decrypt2(unsigned char cipher[4][4]);                  //调整结构后的解密函数

int main()
{
    unsigned char plain[4][4];
    string str;
    string key;
    for(int i=0;i<10;i++)
    {
        ofstream outfile;
        char ch = i + '0';
        string s(1,ch);
        string t=".txt";
        string filename="D://testcase" + s + t;
        outfile.open(filename);
        cout<<"输入第"<<i<<"组测试用例的明文串：";
        cin>>str;
        convertTo44Array(str,plain);
        cout<<"输入第"<<i<<"组测试用例的密钥串：";
        cin>>key;
        convertTo44Array(key,Roundkey[0].key);
        encrypt(plain);
        string result = Array44Tostr(plain);
        decrypt2(plain);
        string mingwen = Array44Tostr(plain);
        cout<<"解密后的明文为："<<mingwen<<endl;
        cout<<"转化为16进制输出生成第"<<i<<"组测试文件"<<endl;
        outfile<<strToHex(str)<<endl;
        outfile<<strToHex(key)<<endl;
        outfile<<strToHex(result);
        cout<<"---------------------------------"<<endl;
        outfile.close();
    }
    system("pause");
    return 0;
}

string strToHex(string str)		//string 转换为十六进制
{
	const std::string hex = "0123456789ABCDEF";
	stringstream ss;
	for (std::string::size_type i = 0; i < str.size(); ++i)
		ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xf] << "";
	return ss.str();
}

int getLeft4bit(unsigned char a) //取字节左四位
{
    int result = a & 0b11110000;
    return result >> 4;
}

int getRight4bit(unsigned char a)  //取字节右四位
{
    int result = a & 0b00001111;
    return result;
}

unsigned char Schange(unsigned char a)  //取S盒中的值
{
    int row = getLeft4bit(a);
    int col = getRight4bit(a);
    return S[row][col];
}

void subBytes(unsigned char a[4][4])  //S盒变换
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            a[i][j]=Schange(a[i][j]);
}

unsigned char Schange_ni(unsigned char a)  //取S逆盒中的值
{
    int row = getLeft4bit(a);
    int col = getRight4bit(a);
    return S_ni[row][col];
}

void subBytes_ni(unsigned char a[4][4])  //S盒逆变换
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            a[i][j]=Schange_ni(a[i][j]);
}

void convertTo44Array(string str, unsigned char a[4][4]) 
{
	int k = 0;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++) 
			a[j][i] = str[k++];
}

string Array44Tostr(unsigned char a[4][4])
{
    string str="";
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            str+=a[j][i];
    return str;
}

void AddKey(unsigned char a[4][4],unsigned char b[4][4]) //a是状态，b是key
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
           a[i][j]=a[i][j]^b[i][j];
    return ;
}

void RowShift(unsigned char state[4][4])  //按字节循环左移
{
    unsigned char temp[4][4];  //复制状态数组
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            temp[i][j]=state[i][j];
    for(int i=0;i<4;i++)
    {
        state[1][i]=temp[1][(i-1+4)%4];
        state[2][i]=temp[2][(i-2+4)%4];
        state[3][i]=temp[3][(i-3+4)%4];
    }
    return ;
}

void RowShift_ni(unsigned char state[4][4])
{
    unsigned char temp[4][4];  //复制状态数组
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            temp[i][j]=state[i][j];
    for(int i=0;i<4;i++)
    {
        state[1][i]=temp[1][(i+1)%4];
        state[2][i]=temp[2][(i+2)%4];
        state[3][i]=temp[3][(i+3)%4];
    }
    return;
}

void ColMix(unsigned char state[4][4])  //列混合
{
    unsigned char temp[4][4];  //复制状态数组
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            temp[i][j]=state[i][j];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            state[i][j] = AES_MUL(colM[i][0],temp[0][j]) ^ AES_MUL(colM[i][1],temp[1][j]) ^ AES_MUL(colM[i][2],temp[2][j]) ^ AES_MUL(colM[i][3], temp[3][j]);

}

void DeColMix(unsigned char state[4][4])  //列混合逆变换
{
    unsigned char temp[4][4];  //复制状态数组
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            temp[i][j]=state[i][j];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            state[i][j] = AES_MUL(decolM[i][0],temp[0][j]) ^ AES_MUL(decolM[i][1],temp[1][j]) ^ AES_MUL(decolM[i][2],temp[2][j]) ^ AES_MUL(decolM[i][3], temp[3][j]);

}

unsigned char AES_MUL(int n,unsigned char a)  //AES要用的字乘法
{
    unsigned char result;
    if(n==1)
        result=a;
    else if(n==2)
        result=XMUL(a);
    else if(n==3)
        result=XMUL(a)^a;
    else if(n==0x09)
        result=XMUL(XMUL(XMUL(a)))^a;  //8^1
    else if(n==0x0B) //11
        result=XMUL(XMUL(XMUL(a)))^XMUL(a)^a;     //8^2^1
    else if(n==0x0D)  //13
        result=XMUL(XMUL(XMUL(a)))^XMUL(XMUL(a))^a;    //12^1=8^4^1
    else if(n==0x0E)
        result=XMUL(XMUL(XMUL(a)))^XMUL(XMUL(a))^XMUL(a);    //12^2=8^4^2
    return  result;
}

unsigned char XMUL(unsigned char s)    //x乘
{
	unsigned char result = s << 1;
	int b7 = result & 0b10000000;
	if(b7 != 0) {
		result = result & 0x000000ff;
		result = result ^ 0x1b;
	}
	return result;
}

void extendKey(string s)  //轮密钥生成，n表示第几轮，从0开始
{
    convertTo44Array(s,Roundkey[0].key);
    for(int n=1;n<11;n++)
    {
        //第四列移位
        Roundkey[n].key[0][0]=Roundkey[n-1].key[1][3];
        Roundkey[n].key[1][0]=Roundkey[n-1].key[2][3];
        Roundkey[n].key[2][0]=Roundkey[n-1].key[3][3];
        Roundkey[n].key[3][0]=Roundkey[n-1].key[0][3];
        //第四列字节替换
        for(int i=0;i<4;i++)
            Roundkey[n].key[i][0]=Schange(Roundkey[n].key[i][0]);
        //第四列异或轮常数
        for(int i=0;i<4;i++)
            Roundkey[n].key[i][0]=Roundkey[n].key[i][0]^Rcon[i][n-1]^Roundkey[n-1].key[i][0];
        //按列异或生成新的密钥存入key
        for(int i=1;i<4;i++)
        {
            Roundkey[n].key[0][i]=Roundkey[n-1].key[0][i]^Roundkey[n].key[0][i-1];
            Roundkey[n].key[1][i]=Roundkey[n-1].key[1][i]^Roundkey[n].key[1][i-1];
            Roundkey[n].key[2][i]=Roundkey[n-1].key[2][i]^Roundkey[n].key[2][i-1];
            Roundkey[n].key[3][i]=Roundkey[n-1].key[3][i]^Roundkey[n].key[3][i-1];
        }
    }
}

void encrypt(unsigned char plain[4][4])
{
    //先进行第一轮的密钥加
    AddKey(plain,Roundkey[0].key);
    //重复9轮标准轮变换
    for(int i=1;i<=9;i++)
    {
        subBytes(plain);//S盒转化
        RowShift(plain);//行移位
        ColMix(plain);//列混合
        AddKey(plain,Roundkey[i].key);//密钥加
    }
    //最后一轮非标准轮变换
    subBytes(plain);//S盒转化
    RowShift(plain);//行移位
    AddKey(plain,Roundkey[10].key);//密钥加
}

void decrypt1(unsigned char cipher[4][4])
{
    //先跟第十轮密钥加
    AddKey(cipher,Roundkey[10].key);
    //重复9轮标准轮变换
    for(int i=9;i>=1;i--)
    {
        RowShift_ni(cipher);//行移位逆变换
        subBytes_ni(cipher);//S盒逆转化
        AddKey(cipher,Roundkey[i].key);//密钥加
        DeColMix(cipher);//列混合
    }
    //最后一轮非标准轮变换
    RowShift_ni(cipher);//行移位
    subBytes_ni(cipher);//S盒转化
    AddKey(cipher,Roundkey[0].key);//密钥加
}

void decrypt2(unsigned char cipher[4][4])
{
    //先跟第十轮密钥加
    AddKey(cipher,Roundkey[10].key);
    //重复9轮标准轮变换
    for(int i=9;i>=1;i--)
    {
        subBytes_ni(cipher);//S盒逆转化
        RowShift_ni(cipher);//行移位逆变换
        DeColMix(cipher);//列混合
        RowShift_ni(Roundkey[i].key);
        AddKey(cipher,Roundkey[i].key);//密钥加
    }
    //最后一轮非标准轮变换
    subBytes_ni(cipher);//S盒转化
    RowShift_ni(cipher);//行移位
    AddKey(cipher,Roundkey[0].key);//密钥加
}