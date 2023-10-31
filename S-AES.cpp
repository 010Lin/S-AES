#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

// TODO 实现x^nfx的函数
void x_de_n_fang_cheng_fx(int xfx[4], int a[4]) //* xfx是结果，a是上一步的结果
{
    //! 注意要取模
    //! 既约多项式是 x^4 + x + 1
    //* 保存四次乘法的系数
    if (a[0] == 0)
    {
        for (int i = 0; i < 3; i++)
            xfx[i] = a[i + 1];
    }
    else
    {
        //! 如果乘数首项不为1就需要将 b1x^2+b0x 与 x+1 进行异或
        xfx[1] = a[2];
        xfx[2] = a[3] == 1 ? 0 : 1;
        xfx[3] = 1;
    }
}
// TODO 乘法
int *chengfa(int a[4], int b[4])
{
    //* 储存结果的系数
    int *result = new int[4];
    for (int i = 0; i < 4; i++)
        result[i] = 0;

    //* 记录下x^nfx
    int xfx[4] = {0};
    x_de_n_fang_cheng_fx(xfx, a);
    int x2fx[4] = {0};
    x_de_n_fang_cheng_fx(x2fx, xfx);
    int x3fx[4] = {0};
    x_de_n_fang_cheng_fx(x3fx, x2fx);

    //* 现在需要根据多项式a和b开始异或
    if (b[0] == 1)
        for (int i = 0; i < 4; i++)
            result[i] ^= x3fx[i];
    if (b[1] == 1)
        for (int i = 0; i < 4; i++)
            result[i] ^= x2fx[i];
    if (b[2] == 1)
        for (int i = 0; i < 4; i++)
            result[i] ^= xfx[i];
    if (b[3] == 1)
        for (int i = 0; i < 4; i++)
            result[i] ^= a[i];
    return result;
}


// 逆多项式乘法
int *ni_chengfa(int a[4], int b[4]) {
    int *result = new int[4];
    for (int i = 0; i < 4; i++)
        result[i] = 0;

    // 计算 x^3fx
    int x3fx[4];
    for (int i = 0; i < 4; i++) {
        x3fx[i] = a[i];
    }

    // 计算 x^2fx
    int x2fx[4];
    x_de_n_fang_cheng_fx(x2fx, x3fx);

    // 计算 xfx
    int xfx[4];
    x_de_n_fang_cheng_fx(xfx, x2fx);

    // 根据多项式 b 开始异或操作
    if (b[0] == 1) {
        for (int i = 0; i < 4; i++) {
            result[i] ^= x3fx[i];
        }
    }
    if (b[1] == 1) {
        for (int i = 0; i < 4; i++) {
            result[i] ^= x2fx[i];
        }
    }
    if (b[2] == 1) {
        for (int i = 0; i < 4; i++) {
            result[i] ^= xfx[i];
        }
    }
    if (b[3] == 1) {
        for (int i = 0; i < 4; i++) {
            result[i] ^= a[i];
        }
    }

    return result;
}


const int s[4][4] = {
    {9, 4, 10, 11},
    {13, 1, 8, 5},
    {6, 2, 0, 3},
    {12, 14, 15, 7}};
    
const int s_ni[4][4]= {
	{10,5,9,11},
	{1,7,8,15},
	{6,0,2,3},
	{12,4,13,14}};

const int tihuanwei[16][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 1},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 1, 0, 0},
    {0, 1, 0, 1},
    {0, 1, 1, 0},
    {0, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 0, 1},
    {1, 0, 1, 0},
    {1, 0, 1, 1},
    {1, 1, 0, 0},
    {1, 1, 0, 1},
    {1, 1, 1, 0},
    {1, 1, 1, 1}};
// const int tihuanwei[4][4][4] = {
//     {{1, 0, 0, 1},{0, 1, 0, 0},{1, 0, 1, 0},{1, 0, 1, 1}},
//     {{1, 1, 0, 1},{0, 0, 0, 1},{1,0,0,0},{0,1,0,1}},
//     {{0,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,1,1}},
//     {{1,1,0,0},{1,1,1,0},{1,1,1,1},{0,1,1,1}}};


//* 定义轮常数
int rcon1[8] = {1, 0, 0, 0, 0, 0, 0, 0};
int rcon2[8] = {0, 0, 1, 1, 0, 0, 0, 0};

int *yihuo8(int *a, int *b)//8位的异或
{
    int *t = new int[8];
    for (int i = 0; i < 8; i++)
        t[i] = a[i] ^ b[i];
    return t;
}

int *yihuo4(int *a, int *b)//4位的异或
{
    int *t = new int[4];
    for (int i = 0; i < 4; i++)
        t[i] = a[i] ^ b[i];
    return t;
}

void s_he_tihuan(int *temp) //使用s盒替换的函数，8位换
{
    int t1 = 2 * temp[0] + temp[1];
    int t2 = 2 * temp[2] + temp[3];
    int t3 = 2 * temp[4] + temp[5];
    int t4 = 2 * temp[6] + temp[7];
    int tihuan1 = s[t1][t2]; //记录替换后的数字
    int tihuan2 = s[t3][t4];
    //* 四位四位进行替换
    for (int i = 0; i < 4; i++)
        temp[i] = tihuanwei[tihuan1][i];
    for (int i = 0; i < 4; i++)
        temp[i + 4] = tihuanwei[tihuan2][i];
}

void s_ni_tihuan(int *temp) //使用逆s盒替换的函数，8位换
{
    int t1 = 2 * temp[0] + temp[1];
    int t2 = 2 * temp[2] + temp[3];
    int t3 = 2 * temp[4] + temp[5];
    int t4 = 2 * temp[6] + temp[7];
    int tihuan1 = s_ni[t1][t2]; //记录替换后的数字
    int tihuan2 = s_ni[t3][t4];
    //* 四位四位进行替换
    for (int i = 0; i < 4; i++)
        temp[i] = tihuanwei[tihuan1][i];
    for (int i = 0; i < 4; i++)
        temp[i + 4] = tihuanwei[tihuan2][i];
}

void zuoyi(int **temp) //循环左移
{
    for(int i = 4;i < 8;i ++)
    {
        int t = temp[0][i];
        temp[0][i] = temp[1][i];
        temp[1][i] = t;
    }
}

void ni_zuoyi(int **state) {
    for (int i = 4; i < 8; i++) {
        int t = state[1][i];
        state[1][i] = state[0][i];
        state[0][i] = t;
    }
}


int *g(int *temp, int *rcon) // temp是一个八位的数组,rcon是轮常数
{
    //! 注意这个temp是密钥，不能改动，要复制一个新的进行计算
    int *t = new int[8];
    for (int i = 0; i < 8; i++)
        t[i] = temp[i];
    //* 循环左移
    for (int i = 0; i < 4; i++)
    {
        int tt = t[i + 4];
        t[i + 4] = t[i];
        t[i] = tt;
    }

    //* 进行s盒替换
    s_he_tihuan(t);

    //* 进行轮常数异或
    return yihuo8(t, rcon);
}

void liehunxiao(int **mingwen)
{
    int si_de2jinzhi[4] = {0, 1, 0, 0};
    int *m00 = new int[4];
    int *m10 = new int[4];
    int *m01 = new int[4];
    int *m11 = new int[4];
    for (int i = 0; i < 4; i++)
    {
        m00[i] = mingwen[0][i];
        m10[i] = mingwen[0][i + 4];
        m01[i] = mingwen[1][i];
        m11[i] = mingwen[1][i + 4];
    }
    int *n00 = new int[4];
    int *n10 = new int[4];
    int *n01 = new int[4];
    int *n11 = new int[4];
    n00 = yihuo4(m00, chengfa(si_de2jinzhi, m10));//乘法结果是1011
    n10 = yihuo4(chengfa(si_de2jinzhi, m00), m10);//0101
    n01 = yihuo4(m01, chengfa(si_de2jinzhi, m11));//0100
    n11 = yihuo4(chengfa(si_de2jinzhi, m01), m11);//0010
    for (int i = 0; i < 4; i++)
    {
        mingwen[0][i] = n00[i];
        mingwen[0][i + 4] = n10[i];
        mingwen[1][i] = n01[i];
        mingwen[1][i + 4] = n11[i];
    }
}


void Invliehunxiao(int** miwen)
{
    int two_2jinzhi[4] = { 0,0,1,0 };
    int nine_2jinzhi[4] = { 1,0,0,1 };
    int* m00 = new int[4];
    int* m10 = new int[4];
    int* m01 = new int[4];
    int* m11 = new int[4];
    for (int i = 0; i < 4; i++)
    {
        m00[i] = miwen[0][i];
        m10[i] = miwen[0][i + 4];
        m01[i] = miwen[1][i];
        m11[i] = miwen[1][i + 4];
    }
    int* n00 = new int[4];
    int* n10 = new int[4];
    int* n01 = new int[4];
    int* n11 = new int[4];
    n00 = yihuo4(chengfa(nine_2jinzhi,m00), chengfa(two_2jinzhi, m10));
    n10 = yihuo4(chengfa(two_2jinzhi, m00), chengfa(nine_2jinzhi,m10));
    n01 = yihuo4(chengfa(nine_2jinzhi,m01), chengfa(two_2jinzhi, m11));
    n11 = yihuo4(chengfa(two_2jinzhi, m01), chengfa(nine_2jinzhi,m11));
    for (int i = 0; i < 4; i++)
    {
        miwen[0][i] = n00[i];
        miwen[0][i + 4] = n10[i];
        miwen[1][i] = n01[i];
        miwen[1][i + 4] = n11[i];
    }
}

void lunmiyaojia(int **mingwen, int **key)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            mingwen[i][j] ^= key[i][j];
}

//用于输出
void shuchu(int **a)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cout << a[i][j] << ' ';
    cout << endl;
}

// 将ASCII字符串转换为二进制字符串
void asciiToBinaryString(const char *ascii, char *binary) {
    for (int i = 0; i < 8; i++) {
        char c = ascii[i];
        for (int j = 0; j < 8; j++) {
            binary[i * 8 + j] = ((c >> (7 - j)) & 1) ? '1' : '0';
        }
    }
}

// 将二进制字符串转换为ASCII字符串
void binaryStringToAscii(const char *binary, char *ascii) {
    for (int i = 0; i < 8; i++) {
        char c = 0;
        for (int j = 0; j < 8; j++) {
            c = (c << 1) | (binary[i * 8 + j] - '0');
        }
        ascii[i] = c;
    }
}

//异或
void XORBlocks(int* a, int* b) {
    for (int i = 0; i < 8; i++) {
        a[i] ^= b[i];
    }
}

//16转二进制数组存放iv
void toBinaryArray(uint16_t value, int numBits, int binaryArray[]) {
    for (int i = numBits - 1; i >= 0; i--) {
        binaryArray[i] = (value & (1 << i)) ? 1 : 0;
    }
}

int main()
{
	int choose;
    cout<<"Enter 1 for 二进制加密，2 for 二进制解密，3 for ASCII 加密，4 for ACSII 解密"<<endl;
	cout<<"5 for 双重加密， 6 for 双重解密， 7 for 三重加密， 8 for 三重解密, 9 for 中间相遇攻击, 10 for CBC"<<endl;
    cin>>choose;
    //* 输入明文和密钥
    int **mingwen = new int *[2];
    for (int i = 0; i < 2; i++)
        mingwen[i] = new int[8];
    
    int **miwen = new int *[2];
    for (int i = 0; i < 2; i++)
     miwen[i] = new int[8];
     
       int **mingwen_test = new int *[2];
    for (int i = 0; i < 2; i++)
        mingwen_test[i] = new int[8];
     
      int **miwen_test = new int *[2];
    for (int i = 0; i < 2; i++)
     miwen_test[i] = new int[8];
        
    int **key = new int *[2];
    int **keyA = new int *[2];
    int **keyB = new int *[2];
    int **keyC = new int *[2];
    int **keyD = new int *[2];
    int **key1 = new int *[2];
    int **key2 = new int *[2];
    int **keyA1 = new int *[2];
    int **keyA2 = new int *[2];
    int **keyB1 = new int *[2];
    int **keyB2 = new int *[2];
    int **keyC1 = new int *[2];
    int **keyC2 = new int *[2];
    int **keyD1 = new int *[2];
    int **keyD2 = new int *[2];
    
    int k=0;
    int flag=0;
    
    string mm; //利用字符串特性输入统计输入的字符个数  明/密文 
    

    
    
    if(choose==9)//密钥全遍历 
    
    {
    	bool get = false; //确认是否找到了密钥 
    	
    	cout<<"请输入明文+密文"<<endl;
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        cin >> mingwen[i][j]; 
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        cin >> miwen[i][j]; 
    	for (int i = 0; i < 2; i++)
        keyD[i] = new int[8];
        for (int i = 0; i < 2; i++)
        key[i] = new int[8];
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        {
		key[i][j]=0; //初始化密钥
        keyD[i][j]=0;
		}

		int sum=0;
		int sumz=0;
		
	  
		while(sumz!=17) //keyD的所有可能和key1的所有可能组合 
		{	
		//初始化实验数组
		for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        mingwen_test[i][j] = mingwen[i][j]; 
		 
     
        bool shouldbreak = false;
	 	for(int i=0;i<2 && !shouldbreak; i++)
		for(int j=0;j<8;j++)
            {
            	if(keyD[i][j]==0){
            	keyD[i][j]=1;
            	shouldbreak = true;
            	break;
	            }
        	    if(keyD[i][j]==1){
        		keyD[i][j]=0;
		    	}
	        
            } //keyD二进制数组全排列
            
	        sumz=0;
		    for(int i=0;i<2;i++)
            for(int j=0;j<8;j++)
	    	if(keyD[i][j]==1)sumz++;//统计1的个数
	    //		cout<<"----------------------------------kerD中1的个数为："<<sumz<<endl;
	    		
		//开始尝试，首先生成密钥keyD1,keyD2,给加密使用 
			  for (int i = 0; i < 2; i++)
              keyD1[i] = new int[8];
              for (int i = 0; i < 2; i++)
              keyD2[i] = new int[8];

    keyD1[0] = yihuo8(keyD[0], g(keyD[1], rcon1));
    keyD1[1] = yihuo8(keyD1[0], keyD[1]);
    keyD2[0] = yihuo8(keyD1[0], g(keyD1[1], rcon2));
    keyD2[1] = yihuo8(keyD2[0], keyD1[1]); 
		
	 //对于明文
	//* 第0轮的轮密钥加
    lunmiyaojia(mingwen_test, keyD);

    //*第一轮
    //* 明文半字节代替
    s_he_tihuan(mingwen_test[0]);
    s_he_tihuan(mingwen_test[1]);
    //* 明文的行移位
    zuoyi(mingwen_test);
    liehunxiao(mingwen_test);
    lunmiyaojia(mingwen_test,keyD1);
        //* 明文半字节代替
    s_he_tihuan(mingwen_test[0]);
    s_he_tihuan(mingwen_test[1]);
    //* 明文的行移位
    zuoyi(mingwen_test);
    lunmiyaojia(mingwen_test,keyD2);
	 
	 
		sum=0;
		while(sum!=17) 
		{
			//初始化实验数组
		for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        miwen_test[i][j] = miwen[i][j]; 	
         
              bool shouldbreak2 = false;
            	for(int i=0;i<2 && !shouldbreak2 ;i++)
				for(int j=0;j<8;j++)
            {
            	if(key[i][j]==0){
            	key[i][j]=1;
            	shouldbreak2 = true;
            	break;
	            }
        	    if(key[i][j]==1){
        		key[i][j]=0;
		    	}
	        
            } //二进制数组全排列
            sum=0;
            for(int i=0;i<2;i++)
            for(int j=0;j<8;j++)
	    	{
                if(key[i][j]==1)sum++;
	    	}//统计1的个数
	    	
			//开始尝试，首先生成密钥key1,key2
			  for (int i = 0; i < 2; i++)
              key1[i] = new int[8];
              for (int i = 0; i < 2; i++)
              key2[i] = new int[8];

    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]); 
   
	  
    //对于密文
    //* 第0轮的轮密钥加
    lunmiyaojia(miwen_test, key2);

    //*第一轮
    //* 密文的行移位
    ni_zuoyi(miwen_test);
    
	//* 密文半字节代替
    s_ni_tihuan(miwen_test[0]);
    s_ni_tihuan(miwen_test[1]);
    
	//* 密文的轮密钥加
    lunmiyaojia(miwen_test, key1);
    
	//* 密文的列混淆
    Invliehunxiao(miwen_test);
    
    ni_zuoyi(miwen_test);
    
    s_ni_tihuan(miwen_test[0]);
    s_ni_tihuan(miwen_test[1]);
    
    lunmiyaojia(miwen_test,key);
    

    
    //进行明密文对比
    int count=0;

	 for (int i = 0; i < 2; i++)
     for (int j = 0; j < 8; j++)
        {
        	if(mingwen_test[i][j]==miwen_test[i][j])count+=1;
		}
		
		if(count==16)
		{
			get= true;
			cout<<"破译成功!"<<endl<<"密钥K1为：";
		for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        cout<<keyD[i][j];
        cout<<endl;
			cout<<"密钥K2为：";
		for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        cout<<key[i][j];
        cout<<endl; 
            
  /*  cout<<"明文中间结果为：";
     for (int i = 0; i < 2; i++)
     for (int j = 0; j < 8; j++)
     cout<<mingwen_test[i][j];
	 cout<<endl;  
		     cout<<"密文中间结果为：";
     for (int i = 0; i < 2; i++)
     for (int j = 0; j < 8; j++)
     cout<<miwen_test[i][j];
	 cout<<endl;  */  
		}

	   // cout<<sum<<endl;
		if(sum==16)sum=17; //全排列结束条件 
	 
		}

	if(sumz==16)sumz=17; //全排列结束条件
    	 
	}
	

if(get==false) cout<<"无对应密钥";
//else cout<<"破译成功"; 
return 0;
}
    
  
  
  
    
    if(choose==1||choose==2||choose==3||choose==4||choose==10) 
    {
    for (int i = 0; i < 2; i++)
    key[i] = new int[8];
    }
    if(choose==5||choose==6) 
    {
    for (int i = 0; i < 4; i++)
    key[i] = new int[8];
    for (int i = 0; i < 2; i++)
    keyA[i] = new int[8];
    for (int i = 0; i < 2; i++)
    keyB[i] = new int[8];
    }
    if(choose==7||choose==8) 
    {
    for (int i = 0; i < 6; i++)
    key[i] = new int[8];
    for (int i = 0; i < 2; i++)
    keyA[i] = new int[8];
    for (int i = 0; i < 2; i++)
    keyB[i] = new int[8];
    for (int i = 0; i < 2; i++)
    keyC[i] = new int[8];
    }
    
    if(choose==1||choose==2)
    {
    cout<<"请输入明/密文+密钥"<<endl;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        cin >> mingwen[i][j];     
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        cin >> key[i][j];
    }
    
    
    if(choose==5||choose==6)
    {
    	cout<<"请输入明/密文+密钥"<<endl;
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> mingwen[i][j];
       for (int i = 0; i < 4; i++)
       for (int j = 0; j < 8; j++)
            cin >> key[i][j];
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            keyA[i][j]=key[i][j];
            
              for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cout<<keyA[i][j];
            cout<<endl;
            
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            keyB[i][j]=key[i+2][j];
          for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cout<<keyB[i][j];
            cout<<endl;
	}
	
	    if(choose==7||choose==8)
    {
    	cout<<"请输入明/密文+密钥"<<endl;
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> mingwen[i][j];
       for (int i = 0; i < 6; i++)
       for (int j = 0; j < 8; j++)
            cin >> key[i][j];
            
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            keyC[i][j]=key[i+4][j];
            
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cout<<keyC[i][j];
            cout<<endl;

            
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            keyA[i][j]=key[i][j];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cout<<keyA[i][j];
             cout<<endl;
             
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        keyB[i][j]=key[i+2][j];
        for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        cout<<keyB[i][j];
        cout<<endl;

	}

    if(choose==1||choose==2) 
    {

    for (int i = 0; i < 2; i++)
        key1[i] = new int[8];
    for (int i = 0; i < 2; i++)
        key2[i] = new int[8];

    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]);
    }
    
    if(choose==5||choose==6)
    {
    for (int i = 0; i < 2; i++)
        keyA1[i] = new int[8];
    for (int i = 0; i < 2; i++)
        keyA2[i] = new int[8];

    keyA1[0] = yihuo8(keyA[0], g(keyA[1], rcon1));
    keyA1[1] = yihuo8(keyA1[0], keyA[1]);
    keyA2[0] = yihuo8(keyA1[0], g(keyA1[1], rcon2));
    keyA2[1] = yihuo8(keyA2[0], keyA1[1]);
    for (int i = 0; i < 2; i++)
        keyB1[i] = new int[8];
    for (int i = 0; i < 2; i++)
        keyB2[i] = new int[8];

    keyB1[0] = yihuo8(keyB[0], g(keyB[1], rcon1));
    keyB1[1] = yihuo8(keyB1[0], keyB[1]);
    keyB2[0] = yihuo8(keyB1[0], g(keyB1[1], rcon2));
    keyB2[1] = yihuo8(keyB2[0], keyB1[1]);
    }
    
    if(choose==7||choose==8)
    {
    for (int i = 0; i < 2; i++)
        keyA1[i] = new int[8];
    for (int i = 0; i < 2; i++)
        keyA2[i] = new int[8];
    keyA1[0] = yihuo8(keyA[0], g(keyA[1], rcon1));
    keyA1[1] = yihuo8(keyA1[0], keyA[1]);
    keyA2[0] = yihuo8(keyA1[0], g(keyA1[1], rcon2));
    keyA2[1] = yihuo8(keyA2[0], keyA1[1]);
    for (int i = 0; i < 2; i++)
        keyB1[i] = new int[8];
    for (int i = 0; i < 2; i++)
        keyB2[i] = new int[8];

    keyB1[0] = yihuo8(keyB[0], g(keyB[1], rcon1));
    keyB1[1] = yihuo8(keyB1[0], keyB[1]);
    keyB2[0] = yihuo8(keyB1[0], g(keyB1[1], rcon2));
    keyB2[1] = yihuo8(keyB2[0], keyB1[1]);
    
    for (int i = 0; i < 2; i++)
        keyC1[i] = new int[8];
    for (int i = 0; i < 2; i++)
        keyC2[i] = new int[8];

    keyC1[0] = yihuo8(keyC[0], g(keyC[1], rcon1));
    keyC1[1] = yihuo8(keyC1[0], keyC[1]);
    keyC2[0] = yihuo8(keyC1[0], g(keyC1[1], rcon2));
    keyC2[1] = yihuo8(keyC2[0], keyC1[1]);
    }
    
//加密过程
    if(choose == 1){
	
    //* 第0轮的轮密钥加
    lunmiyaojia(mingwen, key);

    //*第一轮
    //* 明文半字节代替
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    //* 明文的行移位
    zuoyi(mingwen);
    //* 明文的列混淆
    liehunxiao(mingwen);
    //* 明文的轮密钥加
    lunmiyaojia(mingwen, key1);

    //*第二轮
    //* 明文半字节代替
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    
    //* 明文的行移位
    zuoyi(mingwen);
    //* 明文的轮密钥加
    lunmiyaojia(mingwen, key2);

    //* 现在的明文其实是密文了
    shuchu(mingwen);
    }
    
     if(choose == 3){
    cout<<"请输入明/密文+密钥"<<endl;
    cin>>mm;
    int length =mm.length(); //输入的字符个数 
    cout<<"长度为："<<length<<endl;
    char m[length]; //字符串转字符数组 
    strcpy(m, mm.c_str());
    //将ASCII明文转换为二进制字符串
    char binaryM[length*8];
    asciiToBinaryString(m, binaryM); //现在总明文存在binaryM数组里，在之后需要切割成2个一组 
    cout<<"转换后的二进制数组为："<<endl;
     for(int i=0;i<length*8;i++)
	 cout<<binaryM[i];
	 cout<<endl;   
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        cin >> key[i][j];
    
    for (int i = 0; i < 2; i++)
        key1[i] = new int[8];
    for (int i = 0; i < 2; i++)
        key2[i] = new int[8];

    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]);
     	
    while(flag<length*8) 
    {
	for(int i=0;i<2;i++)
	for(int j=0;j<8;j++)
	{
		int temp=0;
		if(binaryM[k]=='0')temp=0;
		else temp=1;
		
		 mingwen[i][j]=temp;
	
		 k++;	
	} //切割数组存放16位 
	//输出来看一下 
	for(int i=0;i<2;i++)
	for(int j=0;j<8;j++)
	cout<<mingwen[i][j];
	cout<<endl; 
	
    //* 第0轮的轮密钥加
    lunmiyaojia(mingwen, key);

    //*第一轮
    //* 明文半字节代替
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    //* 明文的行移位
    zuoyi(mingwen);
    //* 明文的列混淆
    liehunxiao(mingwen);
    //* 明文的轮密钥加
    lunmiyaojia(mingwen, key1);

    //*第二轮
    //* 明文半字节代替
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    
    //* 明文的行移位
    zuoyi(mingwen);
    //* 明文的轮密钥加
    lunmiyaojia(mingwen, key2);
    cout<<"加密后的二进制为："; 
    shuchu(mingwen);
     //将16位二进制密文转为两个对应的字符 直接计算 
     int sum1=0;
     int sum2=0;
	for(int i=0;i<8;i++)	
	{
	sum1+=mingwen[0][i]*(pow(2,7-i));
	sum2+=mingwen[1][i]*(pow(2,7-i));
    }
	cout<<sum1<<"字符为:"<<char(sum1)<<endl;
    cout<<sum2<<"字符为:"<<char(sum2)<<endl;
    flag+=16;
    }
    }
    
    if(choose == 5){
	
    //第一重加密 
    lunmiyaojia(mingwen, keyA);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    liehunxiao(mingwen);
    lunmiyaojia(mingwen, keyA1);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    lunmiyaojia(mingwen, keyA2);
    shuchu(mingwen);
    //第二重加密
    lunmiyaojia(mingwen, keyB);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    liehunxiao(mingwen);
    lunmiyaojia(mingwen, keyB1);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    lunmiyaojia(mingwen, keyB2); 
    //* 现在的明文其实是密文了
    shuchu(mingwen); 
    }
    if(choose == 7){
	
    //第一重加密 
    lunmiyaojia(mingwen, keyA);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    liehunxiao(mingwen);
    lunmiyaojia(mingwen, keyA1);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    lunmiyaojia(mingwen, keyA2);
     shuchu(mingwen); 
    //第二重加密
    lunmiyaojia(mingwen, keyB);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    liehunxiao(mingwen);
    lunmiyaojia(mingwen, keyB1);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    lunmiyaojia(mingwen, keyB2); 
     shuchu(mingwen); 
    //第三重加密
    lunmiyaojia(mingwen, keyC);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    liehunxiao(mingwen);
    lunmiyaojia(mingwen, keyC1);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    lunmiyaojia(mingwen, keyC2); 
    //* 现在的明文其实是密文了
    shuchu(mingwen); 
    }
//解密过程
    if(choose == 2){
	
    //* 第0轮的轮密钥加
    lunmiyaojia(mingwen, key2);

    //*第一轮
    //* 明文的行移位
    ni_zuoyi(mingwen);
    
	//* 明文半字节代替
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    
	//* 明文的轮密钥加
    lunmiyaojia(mingwen, key1);
    
	//* 明文的列混淆
    Invliehunxiao(mingwen);

    //*第二轮
    //* 明文的行移位
    ni_zuoyi(mingwen);
    
	//* 明文半字节代替
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    
	//* 明文的轮密钥加
    lunmiyaojia(mingwen, key);

    //* 现在的明文其实是密文了
    shuchu(mingwen);
    } 
    
         if(choose == 4){
    cout<<"请输入明/密文+密钥"<<endl;
    cin>>mm;
    int length =mm.length(); //输入的字符个数 
    cout<<"长度为："<<length<<endl;
    char m[length]; //字符串转字符数组 
    strcpy(m, mm.c_str());
    //将ASCII明文转换为二进制字符串
    char binaryM[length*8];
    asciiToBinaryString(m, binaryM); //现在总明文存在binaryM数组里，在之后需要切割成2个一组 
    cout<<"转换后的二进制数组为："<<endl;
     for(int i=0;i<length*8;i++)
	 cout<<binaryM[i];
	 cout<<endl;   
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        cin >> key[i][j];
    
    for (int i = 0; i < 2; i++)
        key1[i] = new int[8];
    for (int i = 0; i < 2; i++)
        key2[i] = new int[8];

    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]);
     	
    while(flag<length*8) 
    {
	for(int i=0;i<2;i++)
	for(int j=0;j<8;j++)
	{
		int temp=0;
		if(binaryM[k]=='0')temp=0;
		else temp=1;
		cout<<binaryM[k]<<" ";
		 mingwen[i][j]=temp;
		 cout<<mingwen[i][j]<<endl;
		 k++;	
	} //切割数组存放16位 
	//输出来看一下 
	for(int i=0;i<2;i++)
	for(int j=0;j<8;j++)
	cout<<mingwen[i][j];
	cout<<endl; 
	
    //* 第0轮的轮密钥加
    lunmiyaojia(mingwen, key2);

    //*第一轮
    //* 明文的行移位
    ni_zuoyi(mingwen);
    
	//* 明文半字节代替
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    
	//* 明文的轮密钥加
    lunmiyaojia(mingwen, key1);
    
	//* 明文的列混淆
    Invliehunxiao(mingwen);

    //*第二轮
    //* 明文的行移位
    ni_zuoyi(mingwen);
    
	//* 明文半字节代替
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    
	//* 明文的轮密钥加
    lunmiyaojia(mingwen, key);
    cout<<"解密后的二进制为："; 
    shuchu(mingwen);
     //将16位二进制密文转为两个对应的字符 直接计算 
     int sum1=0;
     int sum2=0;
	for(int i=0;i<8;i++)	
	{
	sum1+=mingwen[0][i]*(pow(2,7-i));
	sum2+=mingwen[1][i]*(pow(2,7-i));
    }
	cout<<sum1<<char(sum1);
    cout<<sum2<<char(sum2);
    flag+=16;
    }
    }
    
     if(choose == 6){
    //第一重解密 
    lunmiyaojia(mingwen, keyB2);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyB1);
    Invliehunxiao(mingwen);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyB);
    
    //第二重加密
    lunmiyaojia(mingwen, keyA2);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyA1);
    Invliehunxiao(mingwen);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyA); 
    //* 现在的明文其实是密文了
    shuchu(mingwen);
    } 
    
     if(choose == 8){
    //第一重解密 
    lunmiyaojia(mingwen, keyC2);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyC1);
    Invliehunxiao(mingwen);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyC);
    //第二重解密 
    lunmiyaojia(mingwen, keyB2);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyB1);
    Invliehunxiao(mingwen);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyB);
    //第三重解密 
    lunmiyaojia(mingwen, keyA2);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyA1);
    Invliehunxiao(mingwen);
    ni_zuoyi(mingwen);
    s_ni_tihuan(mingwen[0]);
    s_ni_tihuan(mingwen[1]);
    lunmiyaojia(mingwen, keyA); 
    //* 现在的明文其实是密文了
    shuchu(mingwen);
    }
	
	
   if(choose == 10)
   {
   	// 输入16位密钥
    cout << "输入16位密钥（两个8位块）：" << endl;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> key[i][j];

    int** key1 = new int* [2];
    for (int i = 0; i < 2; i++)
        key1[i] = new int[8];
    int** key2 = new int* [2];
    for (int i = 0; i < 2; i++)
        key2[i] = new int[8];

    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]);


   	// 随机生成初始向量 IV
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint16_t> dis(0, 0xFFFF);
    uint16_t iv = dis(gen);

    int ivBinary[16];
    toBinaryArray(iv, 16, ivBinary);

    cout << "随机生成的初始向量 (IV): ";
    for (int i = 0; i < 16; i++) {
        cout << ivBinary[i];
    }
    cout << endl;

    int** IV = new int* [2];
    for (int i = 0; i < 2; i++)
        IV[i] = new int[8];

    int** IV_ = new int* [2];
    for (int i = 0; i < 2; i++)
        IV_[i] = new int[8];


    for (int i = 0; i < 16; i++) {
        IV[i / 8][i % 8] = ivBinary[i];
    }

    

    int numBlocks;
    cout << "输入明/密文块的数量：" << endl;
    cin >> numBlocks;

    //解密时输入初始向量IV
    cout << "输入初始向量IV（16bit）：" << endl;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> IV_[i][j];

    for (int blockNum = 0; blockNum < numBlocks; blockNum++) {
        int** mingwen = new int* [2];
        for (int i = 0; i < 2; i++)
            mingwen[i] = new int[8];

       int choose1;
       cout<<"Enter 11 for CBC加密， 12 for CBC解密"<<endl;
        cin>>choose1;
        if (choose1 == 11) {
            
            int** prevCipherBlock = IV;

            cout << "输入第 " << blockNum + 1 << " 个 16 位明文（两个 8 位块）：" << endl;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 8; j++)
                    cin >> mingwen[i][j];

            XORBlocks(mingwen[0], prevCipherBlock[0]);
            XORBlocks(mingwen[1], prevCipherBlock[1]);

            lunmiyaojia(mingwen, key);

            s_he_tihuan(mingwen[0]);
            s_he_tihuan(mingwen[1]);

            zuoyi(mingwen);
            liehunxiao(mingwen);

            lunmiyaojia(mingwen, key1);

            s_he_tihuan(mingwen[0]);
            s_he_tihuan(mingwen[1]);

            zuoyi(mingwen);
            lunmiyaojia(mingwen, key2);

            cout << "第 " << blockNum + 1 << " 个密文是：" << endl;
            shuchu(mingwen);

            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 8; j++)
                    prevCipherBlock[i][j] = mingwen[i][j];
        }
       


        if (choose1 == 12) {
            

            int** prevCipherBlock = IV_;

            if (choose == 4) {
                cout << "输入第 " << blockNum + 1 << " 个密文块：" << endl;
                for (int i = 0; i < 2; i++)
                    for (int j = 0; j < 8; j++)
                        cin >> mingwen[i][j];
            }
            int** currentCipherBlock = new int* [2];
            for (int i = 0; i < 2; i++) {
                currentCipherBlock[i] = new int[8];
                for (int j = 0; j < 8; j++) {
                    currentCipherBlock[i][j] = mingwen[i][j];
                }
            }

            // S-AES解密
            lunmiyaojia(mingwen, key2);

            ni_zuoyi(mingwen);

            s_ni_tihuan(mingwen[0]);
            s_ni_tihuan(mingwen[1]);

            lunmiyaojia(mingwen, key1);

            Invliehunxiao(mingwen);

            ni_zuoyi(mingwen);

            s_ni_tihuan(mingwen[0]);
            s_ni_tihuan(mingwen[1]);

            lunmiyaojia(mingwen, key);

            XORBlocks(mingwen[0], prevCipherBlock[0]);
            XORBlocks(mingwen[1], prevCipherBlock[1]);

            cout << "第 " << blockNum + 1 << " 个明文块是：" << endl;
            shuchu(mingwen);

            // 更新prevCipherBlock为当前解密后的块
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 8; j++)
                    prevCipherBlock[i][j] = currentCipherBlock[i][j];

            // 释放当前密文块的内存
            for (int i = 0; i < 2; i++)
                delete[] currentCipherBlock[i];
            delete[] currentCipherBlock;
        }
   }
}
    
    return 0;
}



