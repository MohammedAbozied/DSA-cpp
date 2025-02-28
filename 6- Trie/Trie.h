#pragma once
#include<iostream>	
#include<cstring>	
#include<vector>

using namespace std;

class Trie
{
	static const int MAX_CHAR = 26;
	Trie* Child[MAX_CHAR];  // each node has an array of pointers with Trie type.
	bool is_leaf{}; // each node has a flag.

public:

	Trie()
	{
		memset(Child, 0, sizeof(Child));
	}

	~Trie()
	{
		for (int i = 0; i < MAX_CHAR; i++)
		{
			if(Child[i] != nullptr)
				delete Child[i];
		}
		
	}

	// using recursion
	void insert(string str, int idx = 0)
	{
		if (idx == (int)str.size())
			is_leaf = true;
		else
		{
			int cur = str[idx] - 'a';
			if (Child[cur] == 0)
				Child[cur] = new Trie();
			Child[cur]->insert(str, idx + 1);
		}
	}
	// using iteration (faster than recursion with a lot of queries)
	void insert2(string str)
	{
		Trie* cur = this;

		for (int i = 0; i < str.size(); i++)
		{
			int ch = str[i] - 'a';
			if (!cur->Child[ch])
				cur->Child[ch] = new Trie();
			cur = cur->Child[ch];
		}
		cur->is_leaf = true;
	}

	void insert_in_reverse(string str)
	{
		reverse(str.begin(), str.end());
		Trie* cur = this;

		for (int i = 0; i < str.size(); i++)
		{
			int ch = str[i] - 'a';
			if (!cur->Child[ch])
				cur->Child[ch] = new Trie();
			cur = cur->Child[ch];
		}
		cur->is_leaf = true;
	}

	bool suffix_exist(string str)
	{
		reverse(str.begin(), str.end());
		Trie* cur = this;

		for (int i = 0; i < str.size(); i++)
		{
			int ch = str[i] - 'a';

			if (!cur->Child[ch])
				return false;

			if (cur->Child[ch]->is_leaf)
				return true;
			cur = cur->Child[ch];

		}

		return true;

	}

	void print()
	{
		if (is_leaf)
		{
			cout << "\n";
			return;
		}

		for (int i = 0; i < 26; i++)
		{

			if (Child[i])
			{
				cout << char('a' + i);
				Child[i]->print();
			}
		}
	}

	// using recursion
	bool word_exist(string str, int idx = 0)
	{
		if (idx == str.size())
			return is_leaf;

		int cur = str[idx] - 'a';
		if (!Child[cur])
			return false;

		return Child[cur]->word_exist(str, idx + 1);
	}
	// using iteration (faster than recursion with a lot of queries)
	bool word_exist2(string str)
	{
		Trie* cur = this;

		for (int i = 0; i < str.size(); i++)
		{
			int ch = str[i] - 'a';
			if (!cur->Child[ch])
				return false;
			
			cur = cur->Child[ch];
		}
		return cur->is_leaf;
	}



	bool prefix_exist(string str, int idx = 0)
	{
		if (idx == str.size())
			return true;

		int cur = str[idx] - 'a';
		if (!Child[cur])
			return false;

		return Child[cur]->prefix_exist(str, idx + 1);
	}

	string first_prefix(string str) // help method
	{
		Trie* cur = this;

		for (int i = 0; i < str.size(); i++)
		{
			int ch = str[i] - 'a';
			if (!cur->Child[ch])
				break;

			if (cur->Child[ch]->is_leaf)
				return str.substr(0, i + 1);
			cur = cur->Child[ch];
		}
		/// return str if there are not any prefix match str , or str is taller than tallest prefix in trie.
		return str;
	}



	static string replaceWords(vector<string>& dictionary, string sentence)
	{
		Trie trie;
		for (string w : dictionary)
			trie.insert2(w);

		string curWord = "";
		string Result = "";

		for (int i = 0; i < sentence.size(); i++)
		{
			if (sentence[i] != ' ')
			{
				curWord += sentence[i];
			}
			else
			{
				Result += trie.first_prefix(curWord)+" ";
				curWord = "";
			}
		}
		Result += trie.first_prefix(curWord);// last word
		return Result;
	}












};

