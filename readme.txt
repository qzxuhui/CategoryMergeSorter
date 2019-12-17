文件夹说明：
bin      文件夹中存放了可以用于各个操作系统的可执行文件。
code     文件夹中存放了源代码
template 文件夹中存放了输入文件的模板
test     文件夹中存放了下述示范用法

程序用法：
(1) 确认自己的操作系统，常见的操作系统有 Ubuntu, Win7, Win10 系统
(2) 在bin文件夹下找到自己操作系统对应的可执行文件
    Ubuntu      : sorter_Ubuntu
    Win7/Win10  : sorter_Windows.exe

(3) 拷贝可执行文件到某个目录中
    例如，目前的操作系统是win10，新建一个test文件夹，拷贝sorter_Windows.exe到该文件夹中

(4) 准备输入文件
    输入文件需要和可执行文件在同一个目录下。
    假设A院有6人参与排序,B院有4人参与排序，那么在test文件夹中新建一个input.txt文件，并输入以下内容
    
    A  6
    B  4

    这一步操作完毕后，test文件夹下应该有可执行文件"sorter_Windows.exe"和输入文件"input.txt".

(5) 执行程序
    直接双击sorter_Windows.exe

(6) 查看结果
    可以看到 test文件夹中出现了一个输出文件 "output.txt",内容如下:

    A_1    
    B_1       
    A_2       
    B_2       
    A_3       
    A_4       
    B_3       
    A_5       
    B_4       
    A_6

测试：
    在Ubuntu 18.04, Windows 10, Windows 7 操作系统上运行正常。

其他：
    txt格式文件建议使用软件 notepad++ 来进行编辑。

    如果出现某些动态库缺失，例如报错
    "无法启动此程序，因为计算机中丢失MSVCP110.dll"。尝试重新安装该程序以解决此问题。
    提供两种解决方法:
    (1) 在windows下安装集成开发环境Visual Studio，重新编译。
    (2) 下载360安全卫士,修复*.dll缺失的问题。具体执行步骤见下方参考链接。
        https://zhidao.baidu.com/question/499904449112049524.html
    
