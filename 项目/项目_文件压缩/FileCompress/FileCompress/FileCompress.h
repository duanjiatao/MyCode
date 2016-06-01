#pragma once
#include<iostream>
#include<cassert>
#include<string>
#include "HuffmanTree.h"

typedef long LongType;
struct FileInfo
{
	unsigned char _ch;  // �ַ�
	LongType _count;    // �ַ����ִ���
	string _code;	    // �ַ���Huffman����

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

	//ѹ��
	bool Compress(const char* fileName)  //ѹ��
	{
		//���ļ���ͳ���ļ��и��ַ����ֵĴ���
		assert(fileName);
		FILE* fOutCompress = fopen(fileName, "rb");
		assert(fOutCompress);
		
		int ch = fgetc(fOutCompress);
		while (ch != EOF)
		{
			++_info[ch]._count;  //chֱ�����±�
			ch = fgetc(fOutCompress);
		}

		/**********************************************/

		//����Huffman��
		HuffmanTree<FileInfo> fileHT;
		FileInfo invalid;  //countΪ0
		fileHT.CreateTree(_info, 256, invalid);

		/**********************************************/

		//����Huffman����
		_GenerateHuffmanCode(fileHT.GetRoot());

		/**********************************************/

		//��ѹ���ļ��ĺ�׺��Ϊ ".compress"
		const string CompressFileName = GetFileName(fileName, ".compress");
		FILE* fInCompress = fopen(CompressFileName.c_str(), "wb");
		assert(fInCompress);

		/**********************************************/

		//��ʼѹ���ļ�
		fseek(fOutCompress, 0, SEEK_SET);	 //��λ���ļ���ʼλ��
		int readChar = fgetc(fOutCompress);  //�ȶ�ȡһ���ַ�
		unsigned char charWirte = 0; //��д���ļ����ַ�
		int index = 0;				 //ͳ�ƶ����Ƶ�λ��
		while (readChar != EOF)
		{
			string HfCode = _info[readChar]._code;  //���������ȡ��Huffman����
			for (size_t i = 0; i < HfCode.size(); ++i)
			{
				charWirte <<= 1;
				if (HfCode[i] == '1')  //Ϊ1�ٻ�Ϊ0���û�
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

			readChar = fgetc(fOutCompress);  //�������ļ�
		}
		if (index > 0 && index < 8)  //���λ����8λ�����
		{
			charWirte <<= (8 - index);  //�൱�ڲ� 8-index ��0
			fputc(charWirte, fInCompress);  //�����һ���ַ�
		}
		fclose(fOutCompress);  //�ر��ļ�

		/**********************************************/

		//����һ�������ļ�����׺Ϊ .configure��
		const string ConfigureFile = GetFileName(fileName, ".configure");
		FILE* FileConfig = fopen(ConfigureFile.c_str(), "wb");  //���ļ�
		assert(FileConfig);

		/**********************************************/

		//��ʼд�����ļ�

		//ͳ���ļ����ַ����ܸ���
		unsigned long long chCount = 0;
		for (size_t i = 0; i < 256; ++i)
		{
			chCount += _info[i]._count;
		}

		//��chCount�ĸ�λд�������ļ�
		string strChCount;
		char chCountArr1[12];
		_itoa_s((chCount >> 32), chCountArr1, 10);
		strChCount += chCountArr1;
		strChCount += '\n';
		fputs(strChCount.c_str(), FileConfig);

		//��chCount�ĵ�λд�������ļ�
		strChCount.clear();
		char chCountArr2[12];
		_itoa_s(chCount, chCountArr2, 10);
		strChCount += chCountArr2;
		strChCount += '\n';
		fputs(strChCount.c_str(), FileConfig);

		//д�ַ���ֵ�����ֵĴ���
		for (size_t i = 0; i < 256; ++i)
		{
			string chInfo;
			if (_info[i]._count > 0)
			{
				//��Ӧ���ַ�
				chInfo += _info[i]._ch;
				chInfo += ',';
				//�ַ���Ӧ�ĳ��ִ���
				char strNum[12];
				_itoa_s(_info[i]._count, strNum, 10);
				chInfo += strNum;
				//�Ӹ�����
				chInfo += '\n';
				//д���ļ�
				fputs(chInfo.c_str(), FileConfig);
			}
		}
		fclose(FileConfig);  //�ر��ļ�

		/**********************************************/

		return true;
	}

	//��ѹ��
	bool Uncompress(const char* fileName)  //��ѹ��
	{
		//1.��ȡ�����ļ����ؽ�Huffman��
		//2.��ѹ���ļ�������Huffman�����н�ѹ
		//3.�رմ򿪵��ļ�

		assert(fileName);

		//�������ļ�����׺Ϊ��.configure����
		const string ConfigureFile = GetFileName(fileName, ".configure");
		FILE* fOutConfigure = fopen(ConfigureFile.c_str(), "rb");
		assert(fOutConfigure);

		string line;
		unsigned long long chCount = 0;  //�ļ����ַ����ܸ���

		if (ReadLine(fOutConfigure, line))  //����λ
		{
			chCount |= atoi(line.c_str());
			chCount <<= 32;
			line.clear();
		}
		if (ReadLine(fOutConfigure, line))  //����λ
		{
			chCount |= atoi(line.c_str());
			line.clear();
		}
		
		//��ʼ���ַ������Ӧ�ĸ���
		while (ReadLine(fOutConfigure, line))
		{
			unsigned char ch = line[0];
			if (line.empty())  //�������з�
			{
				line += '\n';
				if (ReadLine(fOutConfigure, line))  //�ٶ�һ��
				{
					_info[10]._count = atoi(line.substr(2).c_str());  //�±��1��ʼ
				}
			}
			else
			{
				_info[ch]._count = atoi(line.substr(2).c_str());
			}
		
			line.clear();
		}
		fclose(fOutConfigure);  //�ر������ļ�

		/**********************************************/

		//�ؽ�Huffman��
		HuffmanTree<FileInfo> fileHT;
		FileInfo invalid;  //countΪ0
		fileHT.CreateTree(_info, 256, invalid);

		/**********************************************/

		//��ѹ���ļ�����׺Ϊ��.compress����
		const string CompressFile = GetFileName(fileName, ".compress");
		FILE* fOutCompress = fopen(CompressFile.c_str(), "rb");
		assert(fOutCompress);

		//�½���ѹ������ļ�����׺Ϊ��.uncompress����
		const string UncompressFile = GetFileName(fileName, ".uncompress");
		FILE* fInUncompress = fopen(UncompressFile.c_str(), "wb");
		assert(fInUncompress);

		//��ʼ��ѹ���ļ����н�ѹ
		unsigned char ch = fgetc(fOutCompress);
		unsigned char compare = 1;  //�����ж��ַ���ÿһλ
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

			//Ҷ�ӽڵ��Ӧ���ַ�
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
				ch = fgetc(fOutCompress);  //����һ���ַ�
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

		//�������Huffman��
		_GenerateHuffmanCode(root->_left);
		_GenerateHuffmanCode(root->_right);

		//�ҵ�Ҷ�ӽڵ㣬���ɶ�Ӧ��Huffman����
		if (NULL == root->_left && NULL == root->_right)
		{
			HuffmanTreeNode<FileInfo>* cur = root;
			HuffmanTreeNode<FileInfo>* parent = cur->_parent;
			string& code = _info[cur->_weight._ch]._code;
			
			while (parent) //����Huffman����
			{
				if (cur->_parent->_left == cur)  //����
				{
					code += '0';
				}
				else  //�Һ���
				{
					code += '1';
				}
				cur = parent;
				parent = cur->_parent;
			}

			//����Huffman����
			code.assign(code.rbegin(), code.rend());
		}
	}

	//��ȡһ�����ļ����ļ���
	const string GetFileName(const char* fileName, const char* sub)
	{
		string NewFile(fileName);
		string NewSub(sub);
		size_t flag = NewFile.find('.');  //�ҵ���.���ַ����±�
		NewFile.replace(flag, NewSub.size(), sub);

		return NewFile;
	}

	bool ReadLine(FILE* file, string& line)  //��ȡ�ļ��е�һ���ַ���
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