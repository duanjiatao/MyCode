#pragma once
#include<iostream>
#include<cassert>
#include<string>
#include "HuffmanTree.h"

typedef long LongType;
struct FileInfo
{
	unsigned char _ch;  // 字符
	LongType _count;    // 字符出现次数
	string _code;	    // 字符的Huffman编码

	FileInfo(const unsigned char ch = 0)
		:_ch(ch)
		, _count(0)
	{}

	bool operator<(const FileInfo& info) const
	{
		return this->_count < info._count;
	}

	bool operator!=(const FileInfo& info) const
	{
		return this->_count != info._count;
	}

	FileInfo operator+(const FileInfo& info)
	{
		FileInfo tmp;
		tmp._count = this->_count + info._count;
		return tmp;
	}

};

class FileCompress
{
public:
	FileCompress()
	{
		for (int i = 0; i < 256; ++i)
		{
			_info[i]._ch = i;
		}
	}

	//压缩
	bool Compress(const char* fileName)  //压缩
	{
		//打开文件，统计文件中各字符出现的次数
		assert(fileName);
		FILE* fOutCompress = fopen(fileName, "rb");
		assert(fOutCompress);
		
		int ch = fgetc(fOutCompress);
		while (ch != EOF)
		{
			++_info[ch]._count;  //ch直接做下标
			ch = fgetc(fOutCompress);
		}

		/**********************************************/

		//创建Huffman树
		HuffmanTree<FileInfo> fileHT;
		FileInfo invalid;  //count为0
		fileHT.CreateTree(_info, 256, invalid);

		/**********************************************/

		//生成Huffman编码
		_GenerateHuffmanCode(fileHT.GetRoot());

		/**********************************************/

		//将压缩文件的后缀改为 ".compress"
		const string CompressFileName = GetFileName(fileName, ".compress");
		FILE* fInCompress = fopen(CompressFileName.c_str(), "wb");
		assert(fInCompress);

		/**********************************************/

		//开始压缩文件
		fseek(fOutCompress, 0, SEEK_SET);	 //定位到文件开始位置
		int readChar = fgetc(fOutCompress);  //先读取一个字符
		unsigned char charWirte = 0; //待写入文件的字符
		int index = 0;				 //统计二进制的位数
		while (readChar != EOF)
		{
			string HfCode = _info[readChar]._code;  //用来保存读取的Huffman编码
			for (size_t i = 0; i < HfCode.size(); ++i)
			{
				charWirte <<= 1;
				if (HfCode[i] == '1')  //为1再或，为0不用或
				{
					charWirte |= 1;
				}
				if (++index == 8)
				{
					fputc(charWirte, fInCompress);
					charWirte = 0;
					index = 0;
				}
			}

			readChar = fgetc(fOutCompress);  //继续读文件
		}
		if (index > 0 && index < 8)  //最后几位不够8位的情况
		{
			charWirte <<= (8 - index);  //相当于补 8-index 个0
			fputc(charWirte, fInCompress);  //补最后一个字符
		}
		fclose(fOutCompress);  //关闭文件

		/**********************************************/

		//创建一个配置文件（后缀为 .configure）
		const string ConfigureFile = GetFileName(fileName, ".configure");
		FILE* FileConfig = fopen(ConfigureFile.c_str(), "wb");  //打开文件
		assert(FileConfig);

		/**********************************************/

		//开始写配置文件

		//统计文件中字符的总个数
		unsigned long long chCount = 0;
		for (size_t i = 0; i < 256; ++i)
		{
			chCount += _info[i]._count;
		}

		//将chCount的高位写入配置文件
		string strChCount;
		char chCountArr1[12];
		_itoa_s((chCount >> 32), chCountArr1, 10);
		strChCount += chCountArr1;
		strChCount += '\n';
		fputs(strChCount.c_str(), FileConfig);

		//将chCount的低位写入配置文件
		strChCount.clear();
		char chCountArr2[12];
		_itoa_s(chCount, chCountArr2, 10);
		strChCount += chCountArr2;
		strChCount += '\n';
		fputs(strChCount.c_str(), FileConfig);

		//写字符的值及出现的次数
		for (size_t i = 0; i < 256; ++i)
		{
			string chInfo;
			if (_info[i]._count > 0)
			{
				//对应的字符
				chInfo += _info[i]._ch;
				chInfo += ',';
				//字符对应的出现次数
				char strNum[12];
				_itoa_s(_info[i]._count, strNum, 10);
				chInfo += strNum;
				//加个换行
				chInfo += '\n';
				//写入文件
				fputs(chInfo.c_str(), FileConfig);
			}
		}
		fclose(FileConfig);  //关闭文件

		/**********************************************/

		return true;
	}

	//解压缩
	bool Uncompress(const char* fileName)  //解压缩
	{
		//1.读取配置文件，重建Huffman树
		//2.读压缩文件，根据Huffman树进行解压
		//3.关闭打开的文件

		assert(fileName);

		//打开配置文件（后缀为“.configure”）
		const string ConfigureFile = GetFileName(fileName, ".configure");
		FILE* fOutConfigure = fopen(ConfigureFile.c_str(), "rb");
		assert(fOutConfigure);

		string line;
		unsigned long long chCount = 0;  //文件中字符的总个数

		if (ReadLine(fOutConfigure, line))  //读高位
		{
			chCount |= atoi(line.c_str());
			chCount <<= 32;
			line.clear();
		}
		if (ReadLine(fOutConfigure, line))  //读低位
		{
			chCount |= atoi(line.c_str());
			line.clear();
		}
		
		//开始读字符与其对应的个数
		while (ReadLine(fOutConfigure, line))
		{
			unsigned char ch = line[0];
			if (line.empty())  //遇到换行符
			{
				line += '\n';
				if (ReadLine(fOutConfigure, line))  //再读一行
				{
					_info[10]._count = atoi(line.substr(2).c_str());  //下标从1开始
				}
			}
			else
			{
				_info[ch]._count = atoi(line.substr(2).c_str());
			}
		
			line.clear();
		}
		fclose(fOutConfigure);  //关闭配置文件

		/**********************************************/

		//重建Huffman树
		HuffmanTree<FileInfo> fileHT;
		FileInfo invalid;  //count为0
		fileHT.CreateTree(_info, 256, invalid);

		/**********************************************/

		//打开压缩文件（后缀为“.compress”）
		const string CompressFile = GetFileName(fileName, ".compress");
		FILE* fOutCompress = fopen(CompressFile.c_str(), "rb");
		assert(fOutCompress);

		//新建解压缩后的文件（后缀为“.uncompress”）
		const string UncompressFile = GetFileName(fileName, ".uncompress");
		FILE* fInUncompress = fopen(UncompressFile.c_str(), "wb");
		assert(fInUncompress);

		//开始读压缩文件进行解压
		unsigned char ch = fgetc(fOutCompress);
		unsigned char compare = 1;  //用来判断字符的每一位
		HuffmanTreeNode<FileInfo>* root = fileHT.GetRoot();
		HuffmanTreeNode<FileInfo>* cur = root;

		int mov = 7;
		while (1)
		{
			if ((ch & (compare << mov)))
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}

			//叶子节点对应的字符
			if (cur && cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fInUncompress);
				
				if (--chCount == 0)
				{
					break;
				}

				cur = root;
			}

			if (--mov < 0)
			{
				ch = fgetc(fOutCompress);  //读下一个字符
				mov = 7;
			}

		}

		fclose(fInUncompress);
		fclose(fOutCompress);
		
		/**********************************************/

		return true;
	}

	void PrintHuffmanCode() const
	{
		for (int i = 0; i < 256; ++i)
		{
			if (_info[i]._count > 0)
			{
				cout << _info[i]._ch << " : " << _info[i]._code << endl;
			}
		}
	}


protected:
	void _GenerateHuffmanCode(HuffmanTreeNode<FileInfo>* root)
	{
		if (NULL == root)
			return;

		//后序遍历Huffman树
		_GenerateHuffmanCode(root->_left);
		_GenerateHuffmanCode(root->_right);

		//找到叶子节点，生成对应的Huffman编码
		if (NULL == root->_left && NULL == root->_right)
		{
			HuffmanTreeNode<FileInfo>* cur = root;
			HuffmanTreeNode<FileInfo>* parent = cur->_parent;
			string& code = _info[cur->_weight._ch]._code;
			
			while (parent) //生成Huffman编码
			{
				if (cur->_parent->_left == cur)  //左孩子
				{
					code += '0';
				}
				else  //右孩子
				{
					code += '1';
				}
				cur = parent;
				parent = cur->_parent;
			}

			//逆置Huffman编码
			code.assign(code.rbegin(), code.rend());
		}
	}

	//获取一个新文件的文件名
	const string GetFileName(const char* fileName, const char* sub)
	{
		string NewFile(fileName);
		string NewSub(sub);
		size_t flag = NewFile.find('.');  //找到‘.’字符的下标
		NewFile.replace(flag, NewSub.size(), sub);

		return NewFile;
	}

	bool ReadLine(FILE* file, string& line)  //读取文件中的一行字符串
	{
		assert(file);

		int ch = fgetc(file);
		if (ch == EOF)
			return false;

		while (ch != EOF && ch != '\n')
		{
			line += ch;
			ch = fgetc(file);
		}
		return true;
	}


protected:
	FileInfo _info[256];
};


void TestCompress()
{
	FileCompress file;
	file.Compress("files.txt");
	//file.PrintHuffmanCode();
}

void TestUncompress()
{
	FileCompress file;
	file.Uncompress("files.txt");
	//file.PrintHuffmanCode();
}