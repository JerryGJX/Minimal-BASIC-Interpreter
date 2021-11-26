# BASIC Interpreter - 2021

**ddl：第12周周一23:00**

BASIC是一门解释性编程语言，本次大作业要求你用c++实现这个语言中的一些功能，来完成一个 Minimal 版本的 BASIC 解释器。

这个解释器既可以立即解释某些语句并运行，又可以编写一个按照行数升序依次运行的大程序，还有一些控制语句。

我们进行基本的鲁棒性检测，但是不进行性能检测和内存泄漏检测，你只需要通过下发的数据点即可。



## 前置工作

首先，为了score.cpp能测评你的程序：

如果你用的是wsl或linux，请删除Basic-Demo-64bit_for_mac_to_be_rename

如果你用的是mac，请删除Basic-Demo-64bit，**并将Basic-Demo-64bit_for_mac_to_be_rename改名为Basic-Demo-64bit**

之后的步骤中我们认为你完成了此操作。



**Basic-Demo-64bit是标程的可执行文件**，你可以用命令行输入`./Basic-Demo-64bit`来运行它，看看BASIC解释器是如何工作的。

如果你用的不是wsl，而是mac或linux，在运行`./Basic-Demo-64bit`的时候，可能会出现 Permission denied 错误。这时候运行`chmod +x Basic-Demo-64bit`应当可以解决此问题



## 下发代码内容描述

提供了CMakeLists.txt，因此你可以直接用CLion打开下发的文件夹，直接就可以编译运行了。

你在写程序的时候只需要完成Basic文件中的内容。默认什么都不写就已经完成了一个可定义变量的计算器（如：输入x=1+1，回车，输出2，再输入x+x，输出4），你需要自行阅读代码来判断你需要编写或增添哪些文件中的哪些部分。你也可以自行添加文件，更改类或文件的结构，不必拘泥于提供的框架，只需要在code review时向助教说明你的架构即可。

本作业会引用下发的库 StanfordCPPLib。要用到的库中的文件已经被include到各头文件中了，当然你愿意的话也可以自己使用该库的其它文件。你**不应修改**这个库中的任何内容。关于该库的使用，可以查阅官方文档[The StanfordCPPLib package](https://cs.stanford.edu/people/eroberts/StanfordCPPLib/doc/index.html)

由于StanfordCPPLib是自带内存泄漏的（用valgrind跑一遍原始下发代码就可以检测出来），**本次大作业不检测内存泄露**。

关于具体的BASIC解释器的语法要求与其它说明，请见**Minimal BASIC Interpreter - 2021.pdf**



代码框架简述：

- Basic.cpp是主程序，读入一行一行。

现在只完成了一个可以定义变量的计算器，计算步骤为

1. 用针对Expression的parser（定义在parser文件中）去把读入的行解释成一颗Expression语法树。

2. 计算这个Expression语法树并输出答案（Expression的定义与计算部分都在exp文件中）。

   而程序运行过程的变量与值都保存在evalstate文件中。



对完整版：

- 你需要另一种针对Statement的parser（和parser文件没有关系，因为parser文件里只有针对Expression的parser）去把输入字符串解释成Statement语法树。记录与parse的字符串的工作在program文件中。

- Statement的定义与计算部分都在statement文件中。



## 本地测评方法

**score.cpp是测评文件**，会寻找你的可执行文件与Basic-Demo-64bit进行对拍（对拍，指进行相同输入看输出是否相同）。

测评文件内容默认是Test文件夹下提供的文件。这些文件和oj中测评的数据点是相同的。在这些测试点下，你的程序需要输出与标程相同的结果。

你的可执行文件路径与名字默认为`cmake-build-debug/code`,也就是CLion默认的产生可执行文件的位置。

如果路径有问题或你有独特的需求，你可以自行修改score.cpp中的路径或者测评代码来满足你的需求。



score.cpp使用方法：编译score.cpp，然后运行编译产生的文件，即可。

样例：

```
g++ -o score score.cpp
./score -f
```

使用 ./score -h 来查看帮助。



## oj提交方法

本次大作业**使用github进行测评**。提交时，你的github仓库下需要有一个Basic文件夹，一个提供的StanfordCPPLib文件夹，与一个提供的CMakeLists.txt。



在oj的提交栏提交你的github仓库的地址，如 `https://github.com/your_user_name/your_repo_name`



如果**Compile Error**并且报错类似下面的样子，

`Cloning into 'your_repo_name'... fatal: unable to access 'https://github.com/your_user_name/your_repo_name/': Failed to connect to github.com port 443: Connection timed out  `

或

`Cloning into 'your_repo_name'... fatal: unable to access 'https://github.com/your_user_name/your_repo_name/': GnuTLS recv error (-110): The TLS connection was non-properly terminated.  `

可能是因为github访问速度较慢。你只需要将**提交的地址改为**`https://github.com.cnpmjs.org/your_user_name/your_repo_name`形式的地址就可以进行镜像加速从而解决这个问题了。针对这个功能，推荐浏览器插件“GitHub加速”。



测评文件内容默认是Test文件夹下提供的文件。这些文件和oj中测评的数据点是相同的。在这些测试点下，你的程序需要输出与标程相同的结果。



