# sample_opencv_mingw
用VScode加g++来弄OpenCV真的是日了狗了，真的服了自己，为什么要搞这么麻烦。可能就只是爱折腾而已吧  

## 搭建步骤
首先你要有opencv的mingw的库。因为我下的本来就是winpack，使用VS2015也就是VC14来弄的，所以根本没有mingw的库，怎么办呢，你可以自己下source然后用mingw编译出你自己的mingw库，当然你也可以下别人编译好的。而我就选择了自己编译。天啊！我真的服了我自己。  
下好source之后用cmake，添加你的gcc,g++路径然后编译，如果不出意外的话你会有错误，第一次的时候我用的不是posix的mingw而是win32的mingw所以就会出现std:thread这个问题，哇真的日了狗了！也是在一个偶然的机会在一个偶然的blog里面看到的，然后重装回posix。然后继续mingw32-make，到68%的时候出来一个dnn的问题，天啊，然后回到cmake中把这个选项off掉就好了，最后编译到99%又出个python的错误，因为Anaconda里有个python什么的，然后回cmake中将所有python的都off掉，最后终于编译通过了！感动中国有木有！！！！！然后install然后添加环境变量然后g++写好命令编译运行就好了！！！  
然后要想头文件没有绿线的话就要在c_cpp_properties.json中添加你的路径  
最后的话你的gcc命令要把你的test.h文件I进来然后就可以啦  

## 此外  
我使用的是mingw8.1，posix的Threads，如果不是这个的话会很多坑的，真是日了狗了  
你可以使用gcc -v -E -x c++ -来看你的MinGW的全部安装目录  
可能用到的链接，非常感谢两位大佬的博客  
[MinGW.md](https://github.com/Microsoft/vscode-cpptools/blob/8979a6e6b348efd23b97037151d8968915f9fea0/Documentation/LanguageServer/MinGW.md)  
[G++常用命令1](https://blog.csdn.net/lcuwb/article/details/80626870)  
[G++常见命令2](https://blog.csdn.net/qq_24283329/article/details/72595386) 
