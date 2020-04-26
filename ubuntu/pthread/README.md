# sample_pthread
很简单的一个小多线程代码。只要你g++的shell命令没错然后-I了你的头文件然后也括进了你的各个cpp那你就可以成功编译运行并调试了  
此外如果你不在c_cpp_properties.json中添加你的头文件的路径呢你会看到烦人的绿色波浪线，所以我老老实实就加了    
这个真的是要posix的mingw才可以成功的！！！！如果你不是posix而是win32的话呢你可以去掉dll的位置然后把pthreadVC2改成pthread。同样效果  

## 此外  
我使用的是mingw8.1，posix的Threads，如果不是这个的话会很多坑的，真是日了狗了  
你可以使用gcc -v -E -x c++ -来看你的MinGW的全部安装目录  
可能用到的链接，非常感谢两位大佬的博客  
[MinGW.md](https://github.com/Microsoft/vscode-cpptools/blob/8979a6e6b348efd23b97037151d8968915f9fea0/Documentation/LanguageServer/MinGW.md)  
[G++常用命令1](https://blog.csdn.net/lcuwb/article/details/80626870)  
[G++常见命令2](https://blog.csdn.net/qq_24283329/article/details/72595386) 
