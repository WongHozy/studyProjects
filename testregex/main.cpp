#include <regex>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
	string emailStr = "boo@gmail.com  hozy@qq.com  huanghongjie@icould.com";
	regex reg_email("([[:w:]]+)@([[:w:]]+)\\.com");

	cout << regex_replace(emailStr, reg_email, "$1 is on $2\n", regex_constants::format_no_copy);

	string ipStr = "127.0.0.1  192.168.0.1";
	regex reg_ip("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");

	cout << regex_replace(ipStr, reg_ip, "$1 $2 $3 $4\n", regex_constants::format_no_copy);

	return 0;
}

