#include <iostream>
#include<string>

using namespace std;

int main(int argc, char** argv) {
	int p1, p2, p3;
	cin >> p1 >> p2 >> p3;
	string s1, s2;
	int s1Idx = 0;
	int s2Idx = 0;
	cin >> s1;

	for (s1Idx = 0; s1Idx < s1.length(); s1Idx++)
	{
		if (s1[s1Idx] != '-')
		{
			s2 = s2 + s1[s1Idx];
		}
		else
		{
			if (s1Idx - 1 < 0||s1Idx+1>=s1.length())
			{
				s2 = s2 + s1[s1Idx];
				continue;
			}
			char c1 = s1[s1Idx - 1];
			char c2 = s1[s1Idx + 1];
			if ((c1 + 1) == c2)
			{
				continue;
			}
			else if (c1 >= c2 && (((c1 >= 'a' && c1 <= 'z') && (c2 >= 'a' && c2 <= 'z'))
				|| ((c1 >= '0' && c1 <= '9') && (c2 >= '0' && c2 <= '9'))))
			{
				s2 = s2 + s1[s1Idx];
			}
			else if (c1 < c2 && (((c1 >= 'a' && c1 <= 'z') && (c2 >= 'a' && c2 <= 'z'))
				|| ((c1 >= '0' && c1 <= '9') && (c2 >= '0' && c2 <= '9'))))
			{
				if (p1 == 1)//a
				{
					if (p3 == 1)
					{
						char input = c1 + 1;
						while (input < c2)
						{
							for (int i = 0; i < p2; i++)
							{
								s2 = s2 + input;
							}
							input = input + 1;
						}

					}
					else//ÄæÐò 
					{
						char input = c2 - 1;
						while (input > c1)
						{
							for (int i = 0; i < p2; i++)
							{
								s2 = s2 + input;
							}
							input = input - 1;
						}
					}
				}
				else if (p1 == 2)//A
				{
					if (p3 == 1)
					{
						char input = c1 + 1;
						while (input < c2)
						{
							for (int i = 0; i < p2; i++)
							{
								if ((c1 >= '0' && c1 <= '9') && (c2 >= '0' && c2 <= '9'))
								{
									s2 = s2 + input;
								}
								else
								{
									char Input = input - 32;
									s2 = s2 + Input;
								}
							}
							input = input + 1;
						}
					}
					else
					{
						char input = c2 - 1;
						while (input > c1)
						{
							for (int i = 0; i < p2; i++)
							{
								if ((c1 >= '0' && c1 <= '9') && (c2 >= '0' && c2 <= '9'))
								{
									s2 = s2 + input;
								}
								else
								{
									char Input = input - 32;
									s2 = s2 + Input;
								}
								
							}
							input = input - 1;
						}
					}
				}
				else//*
				{
					char input = c1 + 1;
					while (input < c2)
					{
						for (int i = 0; i < p2; i++)
						{
							s2 = s2 + '*';
						}
						input = input + 1;
					}
				}
			}
			else
			{
				s2 = s2 + s1[s1Idx];
			}

		}
	}

	cout << s2;

	return 0;
}