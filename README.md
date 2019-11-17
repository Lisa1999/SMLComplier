# SMLComplier
to write a SML Complier in C++ using LLVM

#整理
说明：本文件用于记录整个开发过程，包括参考资料、目前进度、疑点和解决方案等；编辑请按照现有格式，最好只增加，即如果需要在成员已写的文案上做修改，请添加备注。
参考
SML语法介绍（详细）：
http://homepages.inf.ed.ac.uk/stg/NOTES/
维基百科SML：
https://en.wikipedia.org/wiki/Standard_ML
LLVM项目例子目录（包括万花筒项目）：
http://www.llvm.org/docs/tutorial/index.html?tdsourcetag=s_pctim_aiomsg
LLVM程序员手册：
http://llvm.org/docs/ProgrammersManual.html?tdsourcetag=s_pctim_aiomsg
SML语法简介：CSDN博客
https://blog.csdn.net/hgkjbm/article/details/100611587
SML语法：产生式形式
http://people.mpi-sws.org/~rossberg/sml.html?tdsourcetag=s_pctim_aiomsg
Clang介绍：
http://clang.llvm.org/docs/
目前进度
项目已经上传到GitHub，可能有点混乱，下载后，添加到LLVM解决方案中，应该可以比较直观。
GitHub地址：
https://github.com/Deerxl/SMLComplier.git

词法分析：
输入：源文件
输出：vector的结构体word，即<word1, word2, ..., wordn>，word 为 {row, value, token}

语法分析：
群文件：语法分析-语法树；
参考：http://people.mpi-sws.org/~rossberg/sml.html?tdsourcetag=s_pctim_aiomsg
备注：可能不全，可能有错，做语法分析可能会在此基础上进行删改

疑难解答
项目引用配置：
项目在现有的520个项目的工程里添加，方便引用llvm的一些文件；引用llvm的文件，需参考项目万花筒9的引用，右键 项目名 -> 添加 -> 引用，对照项目万花筒9的引用，依次添加引用到项目中。然后，右键 项目名 -> 属性 -> C/C++ -> 常规，附加包含目录里的路径参照下图修改，注意根据自己的下载路径进行修改。

最后，SDL检查 -> 否。


