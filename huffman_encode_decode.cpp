// C++ program to encode and decode a string using
// Huffman Coding.
#include <bits/stdc++.h>
#include<iostream>
#include <cstdio>
#include <stdio.h>
#include <stdio_ext.h>
#define MAX_TREE_HT 256
using namespace std;

// to map each character its huffman value
map<char, string> codes;

// to store the frequency of character of the input data
map<char, int> freq;

// A Huffman tree node
struct min_heap
{
	char data;			 // One of the input characters
	int freq;			 // Frequency of the character
	min_heap *left, *right; // Left and right child

	min_heap(char data, int freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

// utility function for the priority queue
struct compare
{
	bool operator()(min_heap* l, min_heap* r)
	{
		return (l->freq > r->freq);
	}
};

// utility function to print characters along with there huffman value
void print_codes(struct min_heap* root, string str)
{
	if (!root)
		return;
	if (root->data != '$')
		cout << root->data << ": " << str << "\n";
	print_codes(root->left, str + "0");
	print_codes(root->right, str + "1");
}

// utility function to store characters along with there huffman value in a hash table.
void store_codes(struct min_heap* root, string str)
{
	if (root==NULL)
		return;
	if (root->data != '$')
		codes[root->data]=str;
	store_codes(root->left, str + "0");
	store_codes(root->right, str + "1");
}

// STL priority queue to store heap tree
priority_queue<min_heap*, vector<min_heap*>, compare> min_heap_object;

void clear_queue()
{
    while (!min_heap_object.empty()) {
        min_heap_object.pop();
    }
}

void clear_all()
{
	codes.clear();
	freq.clear();
	clear_queue();
}

// function to build the Huffman tree and store it in min_heap_object
void huffman_encoding(int size)
{
	struct min_heap *left, *right, *top;
	for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++)
		min_heap_object.push(new min_heap(v->first, v->second));
	while (min_heap_object.size() != 1)
	{
		left = min_heap_object.top();
		min_heap_object.pop();
		right = min_heap_object.top();
		min_heap_object.pop();
		top = new min_heap('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		min_heap_object.push(top);
	}
	store_codes(min_heap_object.top(), "");
}

// utility function to store map each character with its frequency in input string
void calculate_frequency(string str, int n)
{
	for (int i=0; i<str.size(); i++)
		freq[str[i]]++;
}

void display_frequency()
{
	cout << endl << "Printing frequency of each letter in the message" << endl;
	for(auto it = freq.cbegin(); it != freq.cend(); ++it)
	{
		cout << it->first << " " << it->second << "\n";
	}
	cout<<endl;
}

/* function iterates through the encoded string s
   if s[i]=='1' then move to node->right
   if s[i]=='0' then move to node->left
   if leaf node append the node->data to our output string
*/
string huffman_decoding(struct min_heap* root, string s)
{
	string result = "";
	struct min_heap* curr = root;
	for (int i=0;i<s.size();i++)
	{
		if (s[i] == '0')
		curr = curr->left;
		else
		curr = curr->right;

		// reached leaf node
		if (curr->left==NULL and curr->right==NULL)
		{
			result += curr->data;
			curr = root;
		}
	}
	// cout<<result<<endl;
	return result+'\0';
}

// Driver program to test above functions
int main()
{
	string str, char_str;
	char char_arr[100] = {0};
	int is_encode;
	while(1) {
		cout << endl<<"Enter 1 to encode and 0 to decode"<<endl;
		cin >> is_encode;
		if ((is_encode != 0) && (is_encode != 1)) {
			cout << "Invalid input. Please enter 1 to Encode and 0 to Decode"<<endl;
			continue;
		}
		string encoded_str, decoded_str, es;

		if (is_encode == 1) {
			cout << "Enter a long word"<<endl;
			cin >> str;
			calculate_frequency(str, str.length());
			display_frequency();
			huffman_encoding(str.length());
			cout << "Character With there Codes:\n";
			for (auto v=codes.begin(); v!=codes.end(); v++)
				cout << v->first <<' ' << v->second << endl;
			cout<<endl;

			for (auto i: str)
				encoded_str+=codes[i];

			cout << "\nEncoded Huffman data:\n" << encoded_str << endl;
			//Clear All once encoding is done.
			clear_all();
		} else if (is_encode == 0) {
			char c;
			int f, sum_of_freq=0;
			char star[10] = "\n";

			//Clear All before starting decoding.
			clear_all();
			cout << endl<<"Enter encoded string"<<endl;
			cin >> es;
			cout << endl <<"Enter input character and its frequency. Enter NEWLINE as character once you are done"<<endl;
			while (1) {
				cout << endl << "Enter the character  ";
				__fpurge(stdin);
				fgets(char_arr, sizeof (char_arr), stdin);
				if (char_arr[0] == '\n')
					break;
				char_arr[strcspn(char_arr, "\n")] = 0;
				c = char_arr[0];
				cout <<  "Enter frequency of '" << c << "' ";
				cin >> f;
				cout << endl;
				freq.insert({ c, f });
				sum_of_freq = sum_of_freq + f;
			}
			huffman_encoding(sum_of_freq);
			decoded_str = huffman_decoding(min_heap_object.top(), es);
			cout << "\nDecoded Huffman Data:\n" << decoded_str << endl;
		}
	}
	return 0;
}
