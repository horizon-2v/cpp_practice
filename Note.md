## 目录

[1.输入输出流](#输入输出流)<br>
[2.bit和byte](#bit-和-byte)<br>
[3.初始化](#初始化)<br> 
[4.指针和引用](#指针和引用)<br>
[5.const关键字](#const关键字)<br>
[6.typedef关键字](#typedef-关键字)<br>
[7.auto关键字](#auto-关键字)<br>
[8.decltype关键字](#decltype关键字)<br>
[9.C++版本头文件](#c版本的头文件)<br>
[10.标准库string](#标准库string)<br>
[11.标准库vector](#标准库vector)<br>
[12.迭代器](#迭代器)<br>
[13.数组](#数组)<br>
[14.sizeof运算符](#sizeof运算符)<br>
[15.逗号运算](#逗号运算符)<br>
[16.强制类型转换](#强制类型转换)<br>
[17.try-catch异常处理](#try-catch异常处理)<br>
[18.函数](#函数)<br>
[19.内联函数](#内联函数)<br>
[20.constexpr函数](#constexpr函数)<br>
[21.assert和NDEBUG](#assert和ndebug)<br>
[22.函数指针](#函数指针)<br>


## 输入输出流
### 输入流的结束标志
```
while(cin >> num1)
```
对于输入流，当输入流的类型非法（如输入char，被输入的变量为int），或者遇到文件结束符时，`cin >> num1`返回`false`, 每次回车将会把当前行的内容传给流，遇到空格结束，因此若输入 `1 2 3 y` 在回车时，因为有非法字符，将结束循环。而输入 `1 2 3 4` 则不会，输入回车后会开启新的一行，等待输入。文件结束符在Windows下为Ctrl+Z，在Linux下则为Ctrl+D，文件结束符在一行内有别的内容用空格隔开时不会生效，例如: `1 2 3 Ctrl+D` Ctrl+D将无效。但是单独一行输入`Ctrl+D`将直接结束流的输入(不需要回车)

### 输入输出流的级联
```C++
cin >> num1 >> num2
cout << num1 << num2
```
输入输出流级联时，表达式从左向右进行运算，每次将内容写入流（或从流写入变量）时后，其返回流本身，因此上述表达式实际上等效于：
```C++
cin >> num1
cin >> num2
cout << num1
cout << num2
```
当输入一行以空格隔开时，直到按下回车为止，程序处于一个等待输入的状态。按下回车后，会将这一行输入全部通过cin写入变量，但是遇到第一个空格之后，第一个cin >> var的语句就结束了，此时会返回cin，之后空格之后的内容还在cin里，所以再一次遇到cin >> var2的时候，又会将剩下的内容写入变量，直到遇到空格或结束为止，以此类推。`cin >> var1 >> var2`的本质也是上述过程，只不过写在一行了而已。

## bit 和 Byte
### bit 
计算机中01序列的每一位就是一个bit，比如0010是4个bit 

### Byte
计算机可寻址的最小内存块为Byte，存储的基本单元被称为"字"（word），一个word一般由多个Byte构成，大多数机器的Byte由8个bit构成，而word则由4个或8个Byte构成

## 初始化
### 初始化和赋值的区别
初始化和赋值在C++中并不是一个概念，在一些其他语言中这二者可能是同一回事，在C++中二者的区别在大多数情况下也几乎可以忽略，但本质上在C++中二者有很大区别，因为初始化是在创建变量时为其赋予一个初始值，而赋值则把对象的当前值擦除再赋予一个新值。在初始化时常用 `=` 因此看起来像是在赋值一样，但实际上初始化不能等同于赋值

### 初始化的四种基本形式：
``` C++
int value = 0;
int value = {0}；
int value{0};
int value(0);
```
用花括号初始化是C++11引入的新特性，这种初始化形式被称为列表初始化，在初始化时，如果有丢失信息的可能（比如用一个double的字面值对int进行初始化），编译器会报错

### 默认初始化
如果**变量定义于任何函数体之外**，在未显式初始化时，变量被默认初始化为0,如果**存在于函数体之内**，则**不被初始化**,未初始化的内置类型变量的值是未定义的，如果试图访问或拷贝则会引发错误。类的初始化形式则由自己定义。

## 指针和引用
### 引用
通过将声明符写成&d的形式来定义引用类型，其中d是变量名：
```C++
int val = 123;
int &refval = val;
```
引用必须被初始化，一般在初始化变量时，初始值会被拷贝到新建的对象上去，但引用在定义时，则是将引用和初始值绑定在一起，对引用的所有操作都相当于直接操作初始值对象。<br>
引用只能绑定在对象上，而不能与字面值或者某个表达式的计算结果绑定在一起。

### 指针
指针和引用类似，都实现了对对象的间接访问。但和引用又有些许不同：
1. 指针本是是一个对象，允许对指针进行赋值和拷贝，而且指针在其生命周期内可以先后指向不同的对象。
2. 指针无需在初始化的时候赋值，和其他内置类型一样，在块定义域内没有初始化的指针将会拥有一个不确定的值。
定义指针类型的方法将声明符写成*d的形式，其中d是变量名：
```C++
int *ip1, *ip2;
double *dp2;
```

### 空指针
空指针不指向任何对象，生成空指针有三种方法：
```C++
int *p1 = nullptr;
int *p2 = 0;

//需要先#include <cstdlib>
int *p3 = NULL;
```
指针对象被用于条件语句时，如果指针的值为0（即为空指针）则返回false，否则返回true。

### void* 指针
void* 是一种特殊的指针，可用于存放任意对象的地址。void* 本质上还是指针，不同的点在于我们对该地址中存放的是什么类型的对象并不了解。不能直接操作void* 指针，因为我们并不知道其指向的对象是什么类型，但是可以将其和别的指针进行比较操作，也可以作为函数的输入和输出，还可以赋值给其他void* 指针。

### 多个指针变量的定义
将*写在靠近类型的位置容易引起误导，例如：
```C++
int* p1, p2;
```
看起来容易被误解为定义了两个int的指针p1，p2。但实际上是定义了一个int的指针p1和int类型的变量p2。因此为了避免误解建议将*写在靠近变量名的位置：
```C++
int *p1, p2;
```
### 指向指针的引用
引用本身不是对象，因此不能定义指向引用的指针。但指针是对象，所以可以定义指向指针的引用。
```C++
int val = 42;
int *p = nullptr;
int *&r = p;

r = &val;
*r = 0;
```
值得注意的是指向指针的引用的写法是*&，在判断一个复杂的复合类型声明时，可以从右向左阅读变量，以上文为例，与变量r最近的修饰符是&，因此是一个引用，其余部分都是用于确定r引用的类型是什么，上文中是int *，因此引用的类型是int类型的指针。

## const关键字
### const的作用
const限定符用于定义值不能被改变的变量，用关键字`const`对其进行限定：
```C++
const int bufSize = 512;
```
被const修饰的变量必须初始化，一旦初始化之后值就不再能改变，任何试图向const对象写值的操作均会报错。const对象只在文件内部有效，当多个文件包含同名的const对象时，他们被视为每个文件内不同的变量。但若想在多个文件内共享const对象，则需要在声明和定义时对const对象添加extern关键字。也就是说，如果是非const变量，可以直接被其他文件共享，在需要共享的文件中声明extern就可以了，而被共享的变量则不需要添加extern关键字，但是如果是const变量，则被共享的变量也需要添加extern关键字。

### const引用
const引用不仅仅是对const对象的引用这么简单，例如：
```C++
int val = 1;
const int &r1 = val;
```
以上是合法的行为，`const int&`表明对常量的引用，它对引用能够做的行为进行了限制，不能通过引用来改变被引用对象的值，但是被引用对象本身是非常量的，所以被引用对象本身依然可以修改，只是不能通过常量引用r1来修改。但是，反过来：
```C++
const int val = 1;
int &r = val;
```
以上行为则是非法的，不能用非常量引用来引用常量。

### const指针
指向const的指针和指向const的引用类似，同样对指针能够做的行为进行了限制，不能通过指针来修改其指向对象的值，但被指向的对象本身可以是非常量，本身依然可以修改。并且，指向常量的指针自身也并非常量，因此可以被修改，可以指向其他对象：
```C++
int val = 1;
const int c = 2;
const int *p = &val;
p = &c;
*p = 2; 
//非法操作，不能通过指向常量的指针修改其指向对象的值，
//但指针本身并非常量，可以指向其他变量
```
常量指针则表面指针本身是一个常量，在声明时将*放到const前面：
```C++
int *const cp1 = &val;
const int *const cp2 = &c;
```
常量指针不能被修改，其指向的对象在初始化后就不能再改变了，但是被指向的对象本身可以是常量也可以是非常量，如果是非常量则依然可以用解引用通过指针去修改指向对象的值

## constexpr常量表达式
常量表达式是指值不会改变并且在编译过程就能得到计算结果的表达式。C++11的新标准允许将变量声明为`constexpr`类型以便由编译器来验证变量的值是否是一个常量表达式
```C++
constexpr int mf = 20;
constexpr int limit = mf + 1;
constexpr int sz = size();//仅当size是constexpr函数时才正确
```
constexpr的作用更像是提醒编译器帮我们来检查一个变量是否为常量表达式，一般来说如果我们认为变量是一个常量表达式，那就把它声明为constexpr类型，这样如果实际上在我们的程序中他不是一个常量表达式，编译器则会报错来提示我们。

### constexpr指针
constexpr指针中，constexpr限定符仅对指针有效，而与指针指向的对象无关，也就是说constexpr只能是顶层const：
```C++
const int *p = nullptr;
constexpr int *q = nullptr;
```
p是底层const，而q检查的是顶层const。<br>
由于常数表达式的定义是在编译过程就能知道计算结果，所以constexpr指针和引用的初始值会被严格限制，一般来说，只能用在函数体之外的变量的地址来初始化他们，因为函数体内的变量的地址不是固定不变的，无法在编译过程就得到其固定的值。

## typedef 关键字
typedef是类型别名，为类型起一个同义词，typedef对类型定义别名的语法为：
```C++
typedef double wages;
typedef wages base, *p;
```
typedef在用于数组时形式有一点不同，类型别名写在数组维度之前，数组元素类型之后：
```C++
typedef int int_arr[4];//int_arr是int[4]的别名
```
C++11还规定了一种新方法：别名声明，来定义类型的别名：
```C++
using SI = Sales_item;
```
将等式左边的名字规定成等式右边的别名。

### const+类型别名
以下面这段代码为例：
```C++
typedef char *pstring;
const pstring ctr = 0;
``` 
const修饰的是整个pstring，也就是说pstring是常量，所以ctr是一个指向char类型的常量指针（顶层const）
容易误导的是，如果将pstring代入到代码中，`const char *pstring`看起来像是底层const，因此不能习惯于将别名代入回代码来研究其含义。

## auto 关键字
auto关键字可以让编译器替我们去分析表达式所属的类型，auto变量的定义必须有初始值。使用auto在一条语句中声明多个变量的时候，所有变量的初始基本数据类型必须一样。

### auto和引用
用auto做类型时，如果用引用来初始化，则编译器会根据引用的对象来推断auto的类型：
```C++
int i = 0, &r = i;
auto a = r;
```
上述代码中a的属性为int，而不是int&。因为引用不是对象，而只是别名，因此此处相当于用i的值来推断a的类型，因此是int。

### const和auto
auto关键字会忽略初始值的顶层const属性，但是会保留其底层const，比如当初始值是一个指向常量的指针时：
```C++
const int ci = i, &cr = ci;
auto b = ci; //b是int类型，忽略了顶层const
auto d = &i; //i是int，用i的地址来推d的类型，所以是int*
auto e = &ci; //ci是const int, 用ci的地址来推e，保留底层const属性，因此是const int*
```
如果希望推断出的auto类型是顶层const，则需要手动添加const关键字：
```C++
const auto f = ci;//f的类型是const int
```
对于忽略顶层const这个点，在用auto声明指针和引用时值得注意，用于初始化的对象的顶层const属性仍然被保留：
```C++
const int ci = 1;
auto a = ci; //auto为int，忽略了顶层const属性
auto &r = ci, *p = &ci; 
//此时给auto&和auto*推断属性，所以ci的const的顶层const属性得以保留
```

## decltype关键字
decltype同样可以通过表达式来推断类型，但不会用该表达式的值来初始化变量。decltype和auto在使用上有些许不同，decltype使用的表达式是否是一个变量会产生不同的结果：
1. 当表达式是变量时<br>
decltype将返回该变量的类型，顶层const也会保留，引用也会直接返回引用类型本身（而不是返回被引用的类型）
    ```C++
    const int ci = 0, &cj = ci;
    decltype(ci) x = 0;//x的类型是const int，保留了顶层属性
    decltype(cj) y = x;//y的类型是const int&，返回的是引用类型本身而不是被引用的对象 
    ```
    引用大部分时候都是作为别名存在，即实际上相当于操作被引用的对象，只有在decltype里是例外，其返回的是引用自身。
2. 当表达式不是变量时<br>
decltype会返回该表达式的结果类型。值得注意的是*p这种解引用操作是一个表达式，其返回值是对对象的引用。
    ```C++
    int i = 42, *p = &i, &r = i;
    decltype(r + 1) b;//r本身是变量，但是r+1是表达式，因此返回r+1的结果类型int
    decltype(*p) c;//错误，因为*p是表达式而不是变量，所以返回*p的结果类型int*
    ```
    另外特别值得注意的点是，如果变量名被加了括号，编译器就会把他当做是一个表达式而非变量来处理，该类表达式的结果引用类型：
    ```C++
    decltype((i)) d;//(i)被看成是表达式，返回值类型是int&
    decltype(i) e;//i是变量，所以返回int类型
    ```
    牢记decltype((variable))的结果永远是引用，但decltype(variable)只有在variable自身是引用的时候结果才是引用类型。


## C++版本的头文件
C++标准库兼容了C语言的标准库，C语言的标准库一般都是name.h的形式，C++则将这些文件命名为cname，去掉.h后缀后在名字前添加字母c，表明这是一个属于C标准库的头文件。因此cname和name.h两个文件是等价，从功能上讲用哪个都可以，但是一般建议在C++中使用C++版本的头文件。并且在cname的头文件中定义的名字从属于namespace std，而定义在name.h中的则不然。这样的好处是标准库中的名字总能在std中被找到，如果使用.h的话开发者就不得不时刻牢记哪些是从C语言继承来的，哪些又是C++所独有的。

## 标准库string
标准库类型string表示可变长的字符序列，使用string类型必须首先包含string头文件，作为标准库的一部分，string定义在命名空间std中，因此在使用前必须先包含：
```C++
#include <string>
using std::string;
```
### 初始化方式
可以用一个字面值或者string对象来对string进行初始化，也可以使用一个数字和一个字符来进行初始化，得到到结果是多个该字符构成的字符串：
```C++
string s1;
string s2 = s1;
string s2(s1);
string s3 = "abcd";
string s3("abcd");
string s4(10, 'c'); //s4的值为ccccccccccc
```

### 对string的操作
```C++
cin >> s;
cout << s;
```
输入输出流和其他基本类型一样，可以从输入流写入或者输出到输出流。
```C++
getline(cin, s);
```
getline函数可以一次读取一行的数据写入字符串，包括空格，这样就可以将空格写入到string当中去，但最后的回车符没有写进string，因此输出时如果要换行还是需要手动加上换行符。getline的返回值就是参数中的cin，因此可以将getline函数直接作为while的判断条件，就像while(cin >> s)一样。
```C++
s.empty();
s.size();
```
empty和size函数用来判断字符串是否为空以及返回字符串的长度。

### string::size_type类型
s.size()的返回值并不是unsigned或者int，而是string::size_type，这个类型是一个无符号的数，按理说用于存放s.size()函数的返回值的变量都应该是string::size_type类型。在C++11引入auto和decltype之后，可以更加方便的使用这种类型，如：
```C++
auto len = s.size();
decltype(s.size()) len;
```
由于size_type是无符号数，因此如果在表达式中混用了带符号数与无符号数则可能发生错误，因此如果要用size_type进行计算的话要特别注意参与运算的变量类型。

### string的比较
在两个string对象进行比较时：
1. 如果两个string对象在某些位置上的字符不相同，则第一对不相同的字符的比较结果将作为两个string对象的比较结果，两个字符的比较依据大小写敏感的字典顺序。
2. 如果两个string对象长度不同，但是一个string是另一个的子串，则短的那个小于长的string，如果长度也相同则认为两个string相等。

### 给string的赋值
允许把一个string赋值给另一个string，也允许把一个字面值赋值给string。但需要注意的是，出于一些历史原因以及为了和C兼容，**C++中的字符串字面值和string并不是同一种类型**，因此无论是用字符串字面值给string赋值还是通过加法运算来拼接字符串，本质上在其中都隐含了从字符串字面值到string的类型转换。在进行字符串拼接时，必须保证加号两侧至少要有一个string对线，这样才能将字面值转化为string类型后进行加法运算。如果加号两侧都是字符串字面值则会发生错误，因为字符串字面值这种类型不能进行加法运算。举例说明：
```C++
string s4 = s1 + ", ";//正确，","被转化成了string后进行加法操作
string s5 = "hello" + ", ";//错误，字符串字面值不能进行加法操作
string s6 = s1 + ", " + "world";//正确，s1和","运算后返回string继续和"world"运算
string s7 = "hello" + ", " + s2;//错误，"hello" + ", "已经出现错误
```

### 遍历string中的字符
可以使用范围for（for each）语句来便利string中的每一个字符：
```C++
string str("some string");
for(auto c : str)
    cout << c << endl;
```
如果想要通过遍历的方式改变string中的字符，可以在范围for中加入引用类型：
```C++
string str("some string");
for(auto &c : str)
    c = toupper(c);
cout << str << endl;
```

### 访问string中的某一个字符
可以使用下表运算符[]来访问某一个字符，下表运算符接受的输入参数的类型是string::size_type。下标的取值范围必须大于0而小于str.size()，否则可能会出现不可预料的后果。下标运算符返回的是下标对应的字符的引用。

## 标准库vector
标准库vector表示对象的集合，存放相同类型的对象，每一个对象都有一个与之对应的索引，因为集合存放着其他对象，因此也被称之为容器。使用vector之前，必须包含相应的头文件，并且要使用using语句：
```C++
#include <vector>
using std::vector;
```
vector本身是一个类模板，类模板本身并不是类，编译器会根据模板创建类或者函数，给类模板提供信息的方式是在模板后面跟一个<>，在<>内放上信息。vector需要提供的额外信息是存放对象的类型：
```C++
vector<int> ivec;
vector<Sales_Item> Sales_vec;
vector<vector<string>> file;
```
注意，引用因为不是对象，因此不能放在vector内。

### vector的定义和初始化
可以用一个已有的vector对象来对一个新的vector进行初始化，也可以用一个数字和存放类型的变量进行初始化，结果是复数个该变量值的vector，也可以只用一个数字来初始化，结果是复合个默认初始化的变量，也可以用花括号直接初始化，用花括号内的结果作为vector的初始化值。
```C++
vector<T> v1;
vector<T> v2 = v1;//通过已有vector进行初始化
vector<T> v2 = v1；
vector<T> v3(n, val);//结果是n个val的vector
vector<T> v4(n);//结果是n个默认初始化的vector
vector<T> v5{a, b, c};//结果是存放了a, b, c的vector
vector<T> v6 = {a, b, c};
```
注意，列表初始化还有两种特殊情况，但不建议使用：
```C++
vector<string> v7{10};
vector<string> v8{10, "hi"};
```
以上两种情况，编译器不会报错。在这种情况下，因为是用花括号包着的列表，编译器首先尝试进行列表初始化，但由于int类型的10不能初始化成string对象，因此编译器会尝试普通的初始化，因此这两行代码会等效于圆括号包着的10和10，“hi”，所以初始化的结果是v7是10个默认初始化的值，v8是10个“hi”。

### 向vector中添加元素
使用vector的push_back方法可以在vector的末尾添加元素：
```C++
vector<int> v2;
for(i = 0; i < 100; i++){
    v2.push_back(i);
}
```

### vector的其他操作
vector的操作与string的基本相同：
```C++
v.empty();
v.size();
v.push_back(t);
v[n];
v1 = v2;
v1 = {a, b, c};
v1 == v2;
v1 != v2;
<, <=, >, >=
```
v.size的返回值类型同样是vector<T>::size_type，注意不能省去尖括号和里面的内容。比较运算符和string一样，比较第一个不相同的元素，如果完全相同就比较长度。vector的下标运算符也和string一样，返回的该位置元素的引用，但值得注意的是，不能通过下标运算符来访问不存在的位置的元素，因此也不能通过下标运算符来添加元素，必须使用push_back方法。

## 迭代器
迭代器和指针类似，也可以间接的访问对象，使用迭代器可以访问容器或string中的某个元素，也能从一个元素移动到另一个元素，一个有效的迭代器指向某一个元素，或者指向容器中尾元素的下一位置。值得注意的是，string本质上不是容器，但是它的很多操作和容器类似，其中就包括迭代器。

### 获得迭代器对象
迭代器对象并不是通过取地址运算符赋值的，凡是拥有迭代器的容器都有返回迭代器成员的方法begin()和end()：
```C++
auto b = v.begin(), e = v.end;()
```
begin方法返回的是指向容器中第一个对象的迭代器，end方法则是返回指向容器中尾元素的下一位置的迭代器。如果容器为空，那么begin和end返回的是同一个迭代器，都是尾后迭代器。迭代器使用的时候和指针几乎相同：
```C++
*item;
item -> mem;
++item;
--item;
item1 == item2;
item2 != item2; 
```
可以通过解引用操作访问迭代器指向的元素，也可以用->操作访问指向对象的成员。迭代器的++和--操作会使迭代器指向下一个或者上一个元素，在迭代器指向同一个对象的时候判定为两个迭代器相等。

### 迭代器的类型
迭代器的类型是iterator，如果是只读的迭代器，则是const_iterator：
```C++
vector<int>::iterator it;
string:iterator it2;
vector<int>::const_iterator it3;
string::const_iterator it4;
```
const_iterator是一个类似底层const的指针的类型，即不能通过迭代器来改变指向对象的值，但迭代器本身可以自由移动。如果容器或者string对象是常量，则只能使用常量迭代器，如果容器或者string不是常量，则既可以使用普通迭代器也可以使用常量迭代器。实际使用时也可以用auto来获取迭代器的类型<br>
如果一个容器或string本身是常量，那么begin和end返回的迭代器类型是const_iterator，该容器本身也只能使用const_iterator，但是如果是非常量的容器和string，begin和end返回的是iterator，如果我们想使用一个常量迭代器，可以使用`cbegin()`和`cend()`。

### 迭代器失效
任何使得容器的容量发生变化的操作均会使迭代器失效，最典型的例子是`push_back()`操作，因此但凡使用了迭代器的循环体，都不要像容器中添加元素。

### 迭代器的运算
迭代器可以进行算术运算：
```C++
iter + n
iter - n
iter += n;
iter -= n;
iter1 - iter2;
>, <, >=, <=
```
迭代器的加减分别指的是迭代器向前和向后的操作，这一点和item++和item--相对应，iter + n表示迭代器向前移动n个位置，同样iter - n表示向后移动n个位置。两个迭代器相减则定义为，运算符右侧的迭代器需要向前移动多少位置才能到达运算符左侧的迭代器的位置，差值结果的类型为`difference_type`该类型是一个带符号的整数，一般使用时可以直接用auto获取他的类型。

## 数组
数组和vector很类似，但是灵活性不如vector强。数组的大小固定不变，不能实时扩容，对于某些特殊的应用来说程序的运行时性能较好。

### 定义和初始化
数组的声明形如a[d]，其中a是数组的名字，d是数组的维度，数组的维度必须是一个常量表达式：
```C++
unsigned cnt = 42;
constexpr unsigned sz = 42;
int arr[10];
int *parr[sz];
string bad[cnt];//错误，cnt不是常量表达式
```
数组定义的时候必须指定数组的类型，不能使用auto来推断数组的类型，另外和vector一样，引用因为不是对象，所以不存在引用的数组。<br>
数组的初始化可以采用列表初始化的形式，此时可以忽略数组的维度，编译器会根据初始值的数量推算数组维度。如果指定了数组的维度，那么列表初始化时初始值的数量不应该超过数组的维度，如果初始值的数量少于数组的维度，后面不够的部分会用默认初始值。
```C++
int ial[3] = {1, 2, 3};
int a2[] = {0, 1, 2};
```
特别的，字符数组可以用字符串字面值来初始化，但注意字符串字面值最后会有一个看不见的空字符'\0'，该字符也要作为字符数组的一个元素。
```C++
char a1[] = "hello";
char a2[5] = "apple";//错误，"apple"有六个字符，超出数组维度
```
数组不能用于对另一个数组的初始化和赋值：
```C++
int a[] = {0, 1, 2};
int a2[] = a;//错误，不能用数组初始化另一个数组
a2 = a;//错误，不能用数组给另一个数组赋值
```
数组本身是一个对象，因此可以定义指向数组的指针和对数组的引用，但要注意声明写法，容易与对指针的数组混淆：
```C++
int *ptrs[10];//存放int*的数组
int (*Parray)[10] = &arr;//指向存放10个int的数组的指针
int (&arrRef)[10] = arr;//对存放10个int的数组的引用
int *(*arry)[10] = &ptrs;//指向存放10个int*的数组的指针
```

### 访问数组元素
数组访问元素的方法和vector基本相同，也可以使用范围for循环和下标运算来访问元素，数字下标的的类型通常定义为`size_t`类型，该类型是一种机器相关的无符号类型，被设计的足够大以便能表示内存中任意对象的大小，该类型被定义在cstddef头文件中，也就是C标准库stddef.h头文件的C++版本。数组下标同样不能越界。但是数组的下标运算可以取负值，编译器不会报错，这是因为数组下标运算的本质是取当前指针的地址，然后移动下标数个单位，因此：
```C++
int ia[] = {0, 2, 4, 6, 8};
int *p = &ia[2];//p指向了ia[2]
int j = p[1];//等效于 int j = *(p + 1);也就是ia[3]
int k = p[-2];//等效于 int k = *(p - 2);也就是ia[0]
```
但一般来说不建议使用这种方式，因为容易越界发生不可预料的问题

### 数组名与指针
很多用到数组名字的地方，编译器都会自动转换为指向数组第一个元素的指针。用auto推断数组类型时，实际上会得到一个指针类型，但是如果使用decltype，得到的是数组类型本身：
```C++
int ia[10];
int *p = &ia[0];
auto ia2(ia);//ia2的类型是int*，其值是ia中第一个元素的地址
decltype(ia) ia3;//ia3是一个维度为10的int数组
ia3 = p;//错误，此时ia3是数组，不是指针，因此不能用指针对象来赋值
```
指针也可以当做迭代器，因此迭代器的操作指针都支持：
```C++
int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int *p = arr;
p++;
```
获取数组首元素的指针很简单，但是获取指向尾元素下一位置的指针则需要：
```C++
int *e = &arr[10];
```
这里我们使用下标运算符访问了一个超出数组范围的元素，因此该指针类似于尾后迭代器，不指向任何元素，不能对尾后指针执行解引用或者递增操作。使用下标来获取尾后指针极易出错，因此在C++11中引入了begin和end函数，但由于指针不是类，因此和vector的begin和end函数的使用方法有些不同，这两个函数定义在iterator头文件中, 属于std命名空间：
```C++
#include <iterator>
using namespace std;

int ia[] = {1, 2, 3, 4};
int *beg = begin(ia);
int *last = end(ia);
```
指向数组的指针支持所有迭代器的操作，比如加减一个常数，或是两个指针相减，两个指针相减结果的返回值类型是`ptrdiff_t`,该类型和`size_t`一样定义在cstddef头文件中，因为差值可能为负，因此该类型是一个带符号的类型。

### 数组和vector的兼容
可以用数组来初始化vector对象：
```C++
int int_arr[] = {0, 1, 2, 3, 4, 5};
vector<int> = ivec(begin(int_arr), end(int_arr));
//也可以只使用数组的一部分进行初始化
vector<int> = subVec(int_arr + 1, int_arr + 4);
```

### C风格字符串本质是数组
C语言中的字符串本质是一个以空字符'\0'结尾的字符数组，我使用的字符串字面值实际上也是C风格字符串。C风格的字符串使用起来和C++中的string有很大不同：
```C++
#include <string>
#include <cstring>

using namespace std;
string s1 = "abc";
string s2 = "def";
if(s1 < s2)//正确，C++的string直接用比较运算符比较

const char ca1[] = "abc";
const char ca2[] = "def";
if(ca1 < ca2)
//错误，ca1和ca2本质上是字符数组，因此用于比较时会
//转化为指向第一个元素的指针，不能比较两个无关的指针

if(strcmp(ca1, ca2) > 0)//正确用法
```
对于C风格字符串，常用的函数：
```C++
strlen(s);//返回字符串s的长度，不包括空字符'\0'
strcmp(s1, s2);//s1 > s2时大于0，s1 < s2时小于0，相等返回0 
strcat(s1, s2);//拼接s1和s2，返回s1，要注意s1的维度避免越界
strcpy(s1, s2);//将s2的值拷贝给s1，返回s1
```
以上函数都包含在cstring头文件下。在C++中尽量不要使用C风格字符串，有很多安全隐患。<br>
string可以部分兼容C风格字符串，可以用一个字符串字面值来初始化string，但不能用string来初始化C风格字符串，如果需要将string转化为C风格字符串则需要使用`c_str()`函数:
```C++
string s = "hello";
const char *str = s.c_str();
```
但值得注意的是，如果后续操作改变了s的值就可能让之前返回的数组失去效用，所以如果执行完`c_str()`后想一直使用其返回的数组，最好将该数组重新拷贝一份。

### 多维数组
多维数组可以通过多个下标运算符去访问具体的元素，一般可以用for循环的嵌套来遍历一个多维数组，但是值得注意的是范围for循环在多维数组中的使用：
```C++
constexpr size_t rowCnt = 3, colCnt = 4;
int ia[rowCnt][colCnt];
for (auto &row ：ia)
    for(auto col : row)
        std::cout << col << std::endl;
```
在用范围for循环遍历多维数组时，除了最内层的循环外，其他所有循环都应该是引用类型，这是因为如果不用引用类型，外层循环在遍历时，将每一个数组传值给row的时候，本质上传的是指针，指针是无法进行后续内层的遍历的，因此外层循环需要加上引用，确保内层循环遍历的是一个数组而不是指针。<br>
对于二维数组，用for循环遍历时要格外注意类型：
```C++
int ai[3][4];
for(auto p = ai; p != ai + 3; p++)
    for(auto q = *p; q != *p + 4; q++)
        cout << *q << endl;
```
p的类型分析：ai是3维数组，里面存放的元素类型是4维数组，因此ai赋值给p时，传递的是指向3维数组中第一个元素的指针，即一个指向元素为int的4维数组 `int (*p)[4]`<br>
q的类型分析：内层循环遍历的是每个元素本身，因此首先给q赋值的应该是一个数组，所以应该是\*p，\*p的类型是元素类型为int的4维数组，当该数组给q赋值时，传递的是指向第一个int的指针，所以q的类型是`int*`，那么在输出内层循环结果时需要解引用`*q`。

## sizeof运算符
sizeof运算符返回一条表达式或一个类型名字所占的字节数，返回值是`size_t`类型：
```C++
int a = 0;
auto n = sizeof(int);
n = sizeof n;
```
值得注意的是，sizeof运算符在作用于一个表达式的时候，并不会实际计算该表达式的结果，所以如果对一个非法指针进行sizeof操作并不会有安全问题。还有几点值得注意：
1. 对引用进行sizeof时返回被引用对象的大小，因为引用本身不是对象
2. 对指针进行sizeof时返回的是指针自身所占空间的大小
3. 对数组进行sizeof时返回的是数组所有元素所占空间的总和，应用于sizeof时数组名不会被转化为指针
4. 对string和vector对象执行sizeof只返回该类型固定部分的大小，不会计算对象中的元素占了多少空间，本质上是计算这个类所占的空间
5. sizeof的返回值是常量表达式，因此可以用来声明数组维度
6. C++11允许使用`Sale_data::revenue`这样的形式在sizeof中获取类成员的大小，因为获取类成员的大小无需实例化对象，sizeof也不会去运算表达式的结果

## 逗号运算符
逗号运算符有两个运算对象，按照从左往右的顺序依次求值。首先对左侧表达式求值，然后将求值结果丢弃掉，逗号运算符真正的结果是右侧的表达式。逗号运算符主要用于for循环中：
```C++
vector<int>::size_type cnt = ivec.size();
for(vector<int>::size_type ix = 0; ix != ivec.size(); ++ix, --cnt)
    ivec[ix] = cnt;
```

## 强制类型转换
C++中的强制类型转换有4种：`static_cast, dynamic_cast, const_cast, reinterpret_cast`，格式是cast-name<type>(expression)<br>
其中最常用的是static_cast<br>
const_cast用于改变对象的const属性，去掉const属性之后，如果对象本身不是常量，可以使用强制类型转换后的对象修改对象的值，但如果对象本身是常量则会产生未定义的后果,const_cast常常用于函数重载的上下文：
```C++
const char *cp;
char *q = static_cast<char*>(cp);
```
reinterpret_cast通常为运算对象的位模式提供较低层次上的重新解释。每太看懂，感觉大概意思就是可以强行改变类型，但类型的本质没有改变，只是让编译器认为改变了属性，因此对改变类型后的对象按照新类型进行运算可能会出现问题，因此尽量不要使用这种方式<br>
C语言中的强制类型转换的语法是：
```C++
int (var);
(int) var;
```
使用C风格的强制类型转换时，如果转换合法，将会执行和static_cast和const_cast相同的操作，如果转换不合法，将会执行reinterpret_cast操作。C风格的强制类型转换和C++版本的在效果上没有什么区别，但C风格的强制类型转换从表现形式上说不是很清晰明了。

## try-catch异常处理
### throw 关键字
程序检测异常部分使用throw关键字，throw之后紧跟一个表达式，该表达式就是抛出的异常类型：
```C++
if(item1_isbn() != item2_isbn())
    throw runtime_error("Data must refer to same ISBN");
cout << item1 + item2 << endl;
```
### try-catch关键字
try关键字之后紧跟一个块，在try语句块之后是多个catch语句块，catch用于捕获异常，根据抛出异常的类型来决定执行哪一个catch语句块：
```C++
#include <iostream>
#include <stdexcept>
using namespace std;

while(cin >> item1 >> item2){
    try {
        if(item1_isbn() != item2_isbn())
            throw runtime_error("Data must refer to same ISBN");
        cout << item1 + item2 << endl;
    } catch(runtime_error err){
        cout << err.what() << "\nTry Again? Enter y or n" << endl;
        char c;
        cin << c；
        if(!cin || c == 'n')
            break;
    }
}
```
异常被抛出的时候，如果在该函数内没有找到相应的catch语句，异常会继续向上抛出，在调用该函数的函数内继续寻找能catch该异常的语句。如果到最终都没有找到能处理该异常的函数，程序将转到名为terminate的标准库函数，一般情况下执行该函数会导致程序非正常退出。如果没有try语句，那也就意味着没有与之搭配的catch语句，那么如果抛出了异常也会被terminate函数终止。

### 标准异常
C++标准库定义了一组异常类：
1. exception类，定义在exception头文件中，这个类只报告异常发生，没有任何额外信息，是最基本的异常类
2. stdexcept头文件定义的几种常用类:
    | Exception Name  | 描述                             |
    | --------------- | -------------------------------- |
    | exception       | 最普通的问题                      |
    | runtime_error   | 只有在运行时才能检测出来的问题      | 
    | range_error     | 结果超出了有意义的范围             |
    | overflow_error  | 运行错误：计算上溢                 |
    | underflow_error | 运行错误：计算下溢                 |
    | logic_error     | 程序逻辑错误                      |
    | domain_error    | 逻辑错误：参数对应结果不存在        |
    | invalid_argument| 逻辑错误：无效参数                 |
    | length_error    | 逻辑错误：创建超出类型最大长度的对象 |
    | out_of_range    | 逻辑错误：使用一个超出有效范围的值   |
    exception类只能默认初始化，其他类应该使用string或者C风格字符串来初始化，不允许使用默认初始化，创建类使用的字符串初始值应是报错信息
3.  new头文件定义了bad_alloc异常类型<br>
    bad_alloc异常类也只能使用默认初始化
4.  type_info头文件定义了bad_cast异常类型
    bad_cast异常类也只能使用默认初始化
    
    异常类只有名为what的成员函数，该函数没有参数，返回值是一个指向C风格字符串的const char*，该字符串提供关于异常的文本信息，也就是创建异常类所用的初始值，对于无初始值的异常类，what函数返回的内容由编译器决定

## 函数
### 静态变量
在函数内部定义的变量一般在函数调用结束后生命周期就结束了，但如果我们需要令一个函数内定义的变量在函数调用结束后依然存在，可以用static关键字将其定义为静态变量，静态变量在第一次被初始化时创建，在程序结束之后才会销毁：
```C++
size_t count_calls(){
    static size_t ctr = 0;
    return ++ctr;
}
int main(){
    for(size_t i = 0; i != 10; i++){
        cout << count_call() << endl;
    }
    return 0;
}
```
### 函数声明
函数的声明和定义十分类似，唯一的区别是声明时不需要函数体，直接以分号结尾。而且因为没有函数体，理论上形参的名字也可以省略，但是一般在声明时还是会带上形参名便于理解。函数的声明一般放在头文件中，在声明的时候不开辟内存，仅仅告诉编译器，有这样的函数在，要预留一部分内存，因此属于预编译阶段可以完成的任务，建议放在头文件内。如果不进行函数声明，直接定义函数，如果函数定义在调用之前，可以正常使用不会报错，但如果定义在调用之后则会编译报错。变量的声明和定义与函数同理。
    
### 值传递和引用传递
函数的形参是非引用类型时，实参对形参进行值传递，将实参的值拷贝给形参，在函数内对形参做的任何操作不会影响实参原本的值。函数的形参是引用类型时，实参对形参进行引用传递，此时形参是对实参的引用，因此在函数内对形参的操作会改变实参的值。<br>
值得注意的是指针作为参数时的情况：
```C++
void reset(int *ip){
    *ip = 0; //实参和形参指向同一个对象，该值被改变了
    ip = 0;//形参本身指向的地址被改变了，但实参没有变
}
```
指针进行值传递时，指针对象本身的不会改变，即在函数内改变指针的指向，不影响实参指针的指向对象，但是在函数内改变指向对象的值，实参指向的对象的值也会改变。实参指针本身的值，也就是指向的地址没有变，但是该地址内存的对象的值被改变了。<br>

有以下几种情况适合使用引用传递：
1. 被传递的对象很大时<br>
    如果被传递的对象是很大的类或者很长的容器，此时如果使用值传递，因为本质上会进行拷贝操作，此时对大对象的拷贝将会产生很大的开销
2. 被传递的对象不支持拷贝操作<br>
    一些不支持拷贝操作的类只能进行引用传递，因为本身无法被拷贝
3. 需要返回多个参数时<br>
    非定义新的数据类型，函数一般只能有一个返回值，那么如果想返回多个值就可以借助引用传递，可以把想要额外返回的对象作为引用传递的实参，在函数内通过操作形参来返回值。
    
### const形参
在实参向形参传递时，会忽略掉形参的顶层const属性，这一点和初始化const对象时是一致的，可以用一个非const的实参给const形参传参。值得注意的是，因为会忽略形参的顶层const属性，因此在函数重载时，不能仅通过加const来实现重载：
```C++
void fcn(const int i){}
void fcn(int i){}//错误，fun重复定义
```
表面看起来两个fcn函数参数不同，但实际上因为会忽略顶层const属性所以两个函数在传参时没有什么区别，因此不能重载。<br>
除非在需要改变形参值的场景下，其他情况下尽量使用常量引用作为形参。因为如果形参是非const的类型，则不能用const对象的实参传参，这样如果在函数嵌套时，错误的使用了非const的引用，则可能会出现编译错误：
```C++
bool is_sentence(const string &s){
    string::size_type ctr = 0;
    return find_char(s, '.', ctr) == s.size() - 1 && ctr == 1;
}
```
如果find_char函数的第一个参数定义成非const的引用，则会发生编译错误，因为不能用一个const的实参对非const的形参传参。

### 数组形参
数组的两个特殊性质在传参的时候同样适用：1.不允许拷贝数组。2.在使用数组名时实际上传递的是指向第一个元素的指针。
```C++
void print(const int*);
void print(const int[]);
void print(const int[10]);
```
以上三种写法实际上是等价的，第二种写法会自动的把数组名转化为元素指针类型，而第三种写法虽然标明了数组的容量，但这只是我们的一个期望值，并不具有实际意义。<br>
因为在传数组时实际上传递的是指针，所以对数组越界的控制就尤为重要，一般的方法是给函数传参时传入首元素的指针和尾后指针，或者显示的传入数组的容量。<br>
数组的引用传参和其他类型对象的引用传参没有什么区别：
```C++
void print(int (&arr)[10]){
    for(auto elem : arr){
        std::cout << elem << std::endl;
    }
}
```
对二维数组传参时也是一样，但是要注意对象元素的类型：
```C++
void print(int (*matrix)[10], int rowSize);
void print(int matrix[][10], int rowSize);
```
二维数组中存的数据类型应该是一维的数组，实际上每一个元素里存放的是指向一维数组的指针，所以第一种写法中第一个参数的类型是指向int[10]的指针，第二种写法看起来会更容易让人理解一些，但因为实际上传的是指针而非数组，因此两种写法各有利弊。

### 可变形参
如果不能确定函数传入参数的数量，可以使用可变形参来传递数量可变的参数，传递可变形参有两种方法：initializer_list和省略符
#### initializer_list形参
initializer_list是一种类似于vector的容器，是一种模板类型，在定义initializer_list对象时必须说明表中所含元素的类型，与vector不同的地方在于，initializer_list内所有的元素都是常量，不能修改其元素的值。initializer_list初始化方法为：
```C++
initializer_list<T> lst;
initializet_list<T> lst{a, b, c...};
```
用一个initializer_list对象对另一个进行赋值或者拷贝时，并不会赋值容器中的元素，而是原始列表和副本共享元素。
```C++
lst2(lst1);
lst2 = lst1;//不赋值元素，lst1和lst2共享元素
```
initializer_list和vector一样，有迭代器也有`begin()`和`end()`方法：
```C++
void error_msg(initializer_list<string> il){
    for(auto it = il.begin(); it != il.end(); ++il){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```
如果想要对initializer_list形参传递一个值的序列，则需要把这些序列放在一个花括号内：
```C++
//excepted和actual都是string类型
if(excepted != actual){
    error_msg({"functionX", expected, actual});
}
else{
    error_msg({"functionX","okay"});
}
```
含有initializer_list形参的函数依然可以有其他的参数：
```C++
using namespace std;
void err_msg(ErrCode e, initializer_list<string> il){
    cout << e.msg() << ": ";
    for(const auto &elem : il){
        cout << elem << " ";
    }
    cout << endl;
}
```
调用时也需要额外传入Errcode参数：
```C++
if(excepted != actual){
    err_msg(ErrCode(42), {"functionX", excepted, actual});
}
else{
    err_msg(ErrCode(0), {"functionX", "okay"});
}
```
 #### 省略符形参
省略符形参时为了便于C++程序访问某些特殊的C代码而设置的，其形式为：
```C++
void foo(int par, ...);
void foo(int par...);
void foo(...);
```
前两种形式是等价的，也就是说逗号可以省略，前面是确定的参数，省略号代表的是不确定数量的参数，获取可变参数列表需要借助头文件stdarg.h中的几个宏：
```C++
#include "stdarg.h"
void function(int count, ...){
    va_list args;
    va_start(args, count);
    for(auto i = 0; i != count; ++i){
        auto val = va_arg(args, int);
        std::cout << val << std::endl;
    }
    va_end(args);
}
```
va_list用于初始化可变参数列表对象。va_start的第一个参数是列表本身，第二个参数是...之前的参数。va_arg用于获取参数，并将指针指向下一个参数，第一个参数是列表对象本身，第二个参数是获取的参数的类型。va_end用于清空列表对象。值得注意的是，大多数类类型的对象在用省略符形参进行参数传递时都会发生错误，因此只供C++代码访问C代码的时候用。

### 函数的返回值
函数返回时，进行值传递还是引用传递取决于函数返回值的类型，如果返回值是非引用类型，那么即使return的对象是引用，在调用函数时传递的也是被引用对象值的拷贝，如果返回值是引用类型，则在调用函数时传递的是对象的引用，特别需要注意的时，不能返回局部变量的引用或者指针，因为在函数执行完之后局部变量将被销毁，如果返回局部对象的引用将会返回一个非法的地址。

### 函数返回数组指针
数组不能被拷贝，因此不能直接返回数组，但可以返回数组的指针，但是想要定义一个返回数组的指针和引用一般会比较繁琐，想要定义个返回数组指针或引用的函数，应该如下定义：
```C++
int (*function(char c))[10];
int (&function(char c))[10];
```
函数名和形参作为一个整体，从内向外分析，首先表明返回的是一个指针或引用，之后最前面是数组内元素的类型，最后面是数组的维度。为了避免这种复杂的写法，可以使用类型别名来简化：
```C++
typedef int arr[10];
using arr = int[10];
arr* = func(int i);
```
C++11中还引入了一种新的声明形式：尾置返回类型，允许把返回值的类型放在形参列表之后：
```C++
auto func(int i) -> int(*)[10];
```
尾置返回类型也能更清楚的定义返回数组指针或引用的函数。<br>
另外，如果已知返回的是哪一个数组类型，也可以借助decltype关键字：
```C++
int odd[] = {1, 3, 5, 7, 9};
int even[] = {2, 4, 6, 8, 0};
decltype(odd) *func(int i){
    return (i % 2) ? &odd : &even;
}
```
### 函数的默认实参
在函数声明时可以添加函数的默认实参，有默认实参的函数，如果在调用时省略了实参，将会用默认实参来进行赋值。在某一个形参被设置了默认实参之后，他后面所有的实参都必须设置默认实参。调用时，如果要省略实参，则只能省略尾部的实参。默认实参可以多次被声明，但是不能通过重复声明的方式来修改某一个实参的默认值，可以在重复声明时对没有添加默认实参的实参添加默认值。<br>
值得注意的是，局部变量不能作为默认实参。用作默认实参的名字在函数声明所在的作用域内解析，而这些名字的求值过程发生在函数调用时：
```C++
int wd = 80;
char def = ' ';
int ht();
string screen(int = ht(), int = wd, char = def);
string window = screen();//调用screen(ht(), 80, ' ');

void f2(){
    def = '*';
    int wd = 100;
    window = screen();//调用screen(ht(), 80, '*');
}
```
上述代码可以看出，函数内修改默认实参的对象的值后，在默认调用时也会修改该值，因为对名字求值过程发生在函数调用的时候。但wd的值没有改变，这是因为局部变量不能作为默认实参，尽管在函数内屏蔽了外部的wd，但这并不影响默认实参的传值，因为用作默认实参的名字在声明的时候已经解析完了，此时的wd和默认实参中的wd没有任何关系。

## 内联函数
内联函数可以允许函数在调用点上内联的展开，从而避免函数调用的开销，因此一般将一些很短小，且经常被调用的函数声明为内联函数，声明和定义内联函数只需要在函数前面加上inline关键字：
```C++
inline const string &function();
```
不过内联说明只是向编译器发起的一个请求，编译器可以选择忽略这个请求，而且大部分编译器都不支持内联内联递归函数。

## constexpr函数
constexpr函数表示能用于常量表达式的函数，constexpr函数的所有形参和返回值必须是字面值，而且函数体内必须有且只有一条return语句：
```C++
constexpr int new_sz(){return 42;}
constexpr int foo = new_sz();//正确，new_sz()是常量表达式
```
为了能在编译的时候随时展开，constexpr函数被隐式的指定为内联函数。constexpr函数中可以有空语句、类型别名以及using声明。值得注意的是，constexpr函数返回的不一定是常量表达式，比如：
```C++
constexpr size_t scale(size_t cnt){return new_sz() * cnt;}
```
上述函数在其形参是常量表达式时返回的是常量表达式，否则就不是。<br>
内联函数和constexpr函数的定义都应该放在头文件中，因为对于某个给定的内联函数或者constexpr函数来说，他的多个定义必须完全一致。

## assert和NDEBUG
assert通常用来调试程序，包含在cassert头文件中，输入参数是一个表达式，当结果为true时不做任何处理，为false时终止程序运行并输出报错信息。assert只在没有定义NDEBUG变量时有效，如果手动定义了NDEBUG：`#define NDEBUG`则assert不会有任何作用，在编译时也可以通过指令添加定义：`g++ -D NDEBUG main.cc`该指令等效于在程序最前面添加了NDEBUG的定义。<br>
编译器还提供了一些用于输出调试信息的变量：
| 变量名        | 描述   |
| ------------ | ------ |
| \_\_FILE\_\_ | 文件名 |
| \_\_LINE\_\_ | 行号   |
| \_\_TIME\_\_ | 时间   |
| \_\_DATA\_\_ | 日期   |

## 函数指针
函数指针是指向函数的指针，函数的类型与他的返回值和形参类型有关，想要声明一个函数的指针，只需要用指针替换函数名即可：
```C++
bool func(int val1, int val2);
bool (*pf)(int, int);
```
使用函数指针时，可以不解引用直接调用指针：
```C++
bool flag = pf(1, 2);
```
与数组类似，当直接把函数名用于赋值时，传递的实际是指向该函数的指针：
```C++
pf = func;
pf = &func;
```
以上两种写法是等价的，也可以给函数指针赋nullptr或者0，在用重载的函数给指针赋值时，必须保证指针类型和其中一个重载函数完全匹配。<br>
和数组类似，函数不能直接作为形参，但是可以传递函数指针，在形参中可以直接写成函数的形式，但是实际上传递的是函数指针：
```C++
void func(int val1, int val2, bool pf(int, int));
void func(int val1, int val2, bool (*pf)(int, int));
```
以上两种定义时等价的，传参时也可以直接传入函数名，但实际上传递的是函数的指针。和数组一样，同样可以通过typedef或者using来命名别名来简化函数的形参。<br>
定义函数类型的返回值时，和数组一样，不能直接返回函数，只能返回函数指针，最简单的方法是使用别名：
```C++
using F = int(int, int);
using PF = int(*)(int, int);
```
别名F是一个函数类型，PF才是函数指针：
```C++
PF f1(int);//正确，返回函数指针
F f1(int);//错误，不能返回函数类型
F *f1(int);//正确，显示返回函数指针
```
也可以不使用别名，但会很繁琐：
```C++
int(*f1(int))(int, int);
```
和数组一样，也可以使用尾置返回类型：
```C++
auto f1(int) -> int (*)(int, int);
```
使用decltype获取返回值也可以，但是要记得decltype返回的是函数类型，需要手动加上\*:
```C++
decltype(func) *getFcn(int);
```
## 类
### 类中的const成员函数
在类中可以定义const成员函数，其定义语法如下：
```C++
std::string isbn() const {return bookNo;}
```
const成员函数的实质意义是将类成员函数中的隐式的this形参声明为指向常量对象的指针。通常来说，this是一个指向类本身的常量指针，其本身为常量指针（顶层const），但其指向的类本身不是一个常量对象，声明为常量成员函数后，this指针指向常量对象（即具有底层const），将成员函数命名为常量成员函数有助于提高灵活性，因为不论是否是const对象都可以调用成员函数，但是代价是由于将指针变成了指向常量的指针，因此常量成员函数不能改变类内部成员的值，也就是对类内的所有成员只能读不能写。同时，常量对象，包括常量对象的指针和引用，都只能调用常量成员函数，否则本质上在将一个指向常量对象的指针指向了一个非常量。
### 构造函数
构造函数在没有自定义任何一个构造函数时才会自动生成默认构造函数，为了安全起见，建议在类内定义了每一个成员变量的前提下使用默认构造函数，如果编译器不支持在类内设置成员变量的初始化，则应该使用初始化列表的方式：
```C++
struct  Sales_data{
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p):
            bookNo(s), units_sold(n), revenue(p*n){}
    Sales_data(std::istream &is);
}
```
当我们有自定义的构造函数，又希望可以使用默认构造函数的时候，可以在构造函数后面加上`= default`，代表希望执行默认构造函数，该关键字既可以和声明一起出现在类的内部，也可以作为定义出现在类的外部，和其他函数一样，如果出现在类内部则默认构造函数是内联的，在外部则不是内联的。在类外部定义构造函数的时候需要显示的表明属于哪一个类：
```C++
Sales_data::Sales_data(std::istream &is){
    read(is, *this);
}
```
### class和struct
class和struct关键字在定义类的时候几乎没有区别，用哪一个都可以，唯一的区别在于默认访问权限。如果在第一个访问说明符之前定义成员，在struct中他们是public的，而在class中是private的，除此之外没有其他区别。
### 友元
类可以允许其他类或者函数访问他的非公有成员，方法是令其他类或者函数成为他的友元，友元用`friend`关键字定义：
```C++
class Sales_data{
friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::istream &read(std::istream&, Sales_data&);
friend std::ostream &print(std::ostream&, const Sales_data&);
}
//外部函数，在类内定义友元
Sales_data add(const Sales_data&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
```
友元只能在类的内部定义，且位置不限，友元并不是类的成员，也不受类的作用域的限制，但一般来讲建议在类定义的开始和结束之前集中声明友元。另外，友元的声明仅仅指定了访问权限，而并非一个真正的声明，因此如果我们希望类的用户能够调用某个友元函数，还需要在友元声明之外专门对函数进行一次声明。同时，为了使友元对类的用户可见，通常把友元的声明和类本身放置在同一个头文件中。
