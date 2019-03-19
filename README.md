# VScode_sample
其中main.cpp中的东西很简单，include了位于桌面的test文件夹中的test.h  
然后要想头文件没有绿线的话就要在c_cpp_properties.json中添加你的路径  
最后的话你的gcc命令要把你的test.h文件I进来然后就可以啦  

## 此外  
使用gcc -v -E -x c++ -来看你的MinGW的全部安装目录  
可能用到的链接  
 [MinGW](https://github.com/Microsoft/vscode-cpptools/blob/8979a6e6b348efd23b97037151d8968915f9fea0/Documentation/LanguageServer/MinGW.md)  
https://blog.csdn.net/lcuwb/article/details/80626870  
