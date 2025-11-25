import nimib

nbInit
nbDoc.title = "RPN 逆波兰计算器使用手册"

nbText: """
RPN 逆波兰计算器使用说明

安装与编译
g++ -std=c++17 rpn_calc.cpp -o rpn_calc
./rpn_calc

基本用法
1 2 + 3 + -> 6
5 1 2 + 4 * + 3 - -> 14

支持运算
"+", "-", "*", "/", "^", "?"

栈操作与命令
"c", "s", "q"

错误处理
除零错误
栈空错误
操作数不足
无效输入
负数平方根
"""

nbSave()
