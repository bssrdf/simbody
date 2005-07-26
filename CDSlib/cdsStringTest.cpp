#include "cdsString.h"

//could do without dependecy on these...
#include <ctype.h>   
#include <string.h>

#include <cdsIostream.h>
#include <cdsIomanip.h>

#include "sthead.h"
#include "cdsList.h"

#include <cdsIomanip.h>
#include <cdsSStream.h>

int
CDSString_test()
{
 int exit=0;
 cout << "testing CDSString...";
 String s("abcdefg");
 char *str = "hijk";
 
 s+= str;
 if (s != "abcdefghijk") {
   cerr << "CDSString: test: " << s << " != abcdefghijk" << endl;
   exit=1;
 }

 s+= 'l';
 if (s != "abcdefghijkl") {
   cerr << "CDSString: test: " << s << " != abcdefghijkl" << endl;
   exit=1;
 }
 
 s = "howdy doody";
 s.upcase();
 if (s != "HOWDY DOODY") {
   cerr << "CDSString: test: " << s << " != HOWDY DOODY" << endl;
   exit=1;
 }

 s.downcase();
 if (s != "howdy doody") {
   cerr << "CDSString: test: " << s << " != howdy doody" << endl;
   exit=1;
 }

 if (s.length() != 11) {
   cerr << "CDSString: test: length of howdy doody != 11" << endl;
   exit=1;
 }

 if ( !s.contains("wdy") ) {
   cerr << "CDSString: test: howdy doody does not contain wdy" << endl;
   exit=1;
 }
 
 int cnt = s.gsub("dy","see");

 if ( cnt != 2 )  {
   cerr << "CDSString: test: gsub count incorrect: " << cnt << endl;
   exit=1;
 }

 if (s != "howsee doosee") {
   cerr << "CDSString: gsub test: " << s << " != howsee doosee" << endl;
   exit=1;
 }

 OStringStream os; os << s << ends;
 if (String(os.str()) != "howsee doosee") {
   cerr << "CDSString: ostream test: " << s << " != howsee doosee" << endl;
   exit=1;
 }

 { 
   IStringStream is("blue red gray orange yellow");
   is >> s;
   if (s != "blue") {
     cerr << "CDSString: istream test: " << s << " != blue" << endl;
     exit=1;
   }
   is.unsetf(ios::skipws);
   is >> s;
   if (s != " red") {
     cerr << "CDSString: istream test: " << s << " != ' red'" << endl;
     exit=1;
   }
   is.setf(ios::skipws);
   is >> s;
   if (s != "gray") {
     cerr << "CDSString: istream test: " << s << " != 'gray'" << endl;
     exit=1;
   }
   is >> s;
   if (s != "orange") {
     cerr << "CDSString: istream test: " << s << " != 'orange'" << endl;
     exit=1;
   }
   is >> s;
   if (s != "yellow") {
     cerr << "CDSString: istream test: " << s << " != 'yellow'" << endl;
     exit=1;
   }
 }
 
 {
   OStringStream os;
   os.setf(ios::right);
   os << setw(10) << "right" << ends;
   if ( String(os.str()) != "     right" ) {
     cerr << "CDSString: right justify: '" << os.str()
	  << "' != '     right'" << endl;
     exit=1;
   }
 }

 {
   OStringStream os;
   os.setf(ios::left);
   os << setw(10) << "left" << ends;
   if ( String(os.str()) != "left      " ) {
     cerr << "CDSString: left justify: '" << os.str()
	  << "' != 'left      '" << endl;
     exit=1;
   }
 }
     

 {
   IStringStream is("doosee n\nbluesey");
   readline(is,s);
   if (s != "doosee n") {
     cerr << "CDSString: readline test: " << s << " != doosee n" << endl;
     exit=1;
   }
 }

 String s1, s2("because"), s3;
 s1 = 'a';  //testing this assignment operator
 s3 = s1+s2;
 if (s3 != "abecause") {
   cerr << "CDSString: operator+: " << s3 << " != abecause" << endl;
   exit=1;
 }

 s3.gsub("a","ba");
 if (s3 != "babecbause") {
   cerr << "gsub failed recursion test: " << s3 << " != babecbause" << endl;
   exit=1;
 }

 {
   CDSString<char> s = "a bc \tdef";
   CDSList< CDSString<char> > list = s.split();
   if ( s.split()[0] != "a" ||
	s.split()[1] != "bc" ||
	s.split()[2] != "def" ) {
     cerr << "split failed on string s. Returned\n\t"
	  << list << endl;
     exit=1;
   }
 }

 { // test glob
   //FIX: test other functionality of glob
   String pattern = "-*-*-*-*-*-*-12-*-*-*-m-*-*-*";
   String text1 = "-adobe-courier-bold-o-normal--12-120-75-75-m-70-iso8859-1";
   String text2 = "-adobe-courier-bold-o-normal--12-120-75-75-X-70-iso8859-1";
   if ( !text1.glob(pattern) || text2.glob(pattern) ) {
     cerr << "glob failed." << endl;
     exit=1;
   }
 }

 { 
   String a = "abcd";
   String b = "lmnop";
   a += b + '\n';
   if ( a != "abcdlmnop\n" ) {
     cerr << "CDSString: multitest failed: " 
	  << a << " != abcdlmnop\\n" << endl;
     exit=1;
   }
 }

 {
   String s = "a longer string";
   String sub = subString(s,9,15);
   if ( s != "a longer string" ||
	sub != "string"          ) {
     cerr << "subString failed: " << sub << " != " << "string" << endl;
     exit=1;
   }
   sub = subString(s,7);
   if ( s != "a longer string" ||
	sub != "r string"          ) {
     cerr << "subString failed: " << sub << " != " << "r string" << endl;
     exit=1;
   }
   sub = subString(s,23);
   if ( s != "a longer string" ||
	sub != ""          ) {
     cerr << "subString failed: " << sub << " != " << "" << endl;
     exit=1;
   }
 }
 
 if ( (String("a temporary ") + "string") != "a temporary string" ) {
   cerr << "tempory string add failed." << endl;
   exit=1;
 }

 {  // inequalilties
   String s1 = "aaaaa";
   String s2 = "aaaaaa";
   const char* c = "bbbb";
   if ( s1 > s2 || !(s1<s2) ||
	s2 < s1 || !(s2>s1) ||
	s1 > c  || !(s1<c)  ||
	c  < s1 || !(c >s1)  ) {
     cerr << "inequality test failed." << endl;
     exit=1;
   }
 }

#ifdef DEBUG_ALLOC
 { // stress tests
   for (int i=0 ; i<20 ; i++) {
     String s;
     for (int j=0 ; j<100000 ; j++)
       s += "a";
     cout << i << ' ';
     cout.flush();
   }
 }
#endif /* DEBUG_ALLOC */


  

 cout << (exit?"failed":"ok") << endl;
 return exit;
} /* test */

