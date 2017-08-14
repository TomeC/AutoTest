AutoTest --- 基于MFC的批量TCP接口测试应用
======================================

### 安装
1. x86: [下载](Release/AutoTest.exe)
2. x64: [下载](x64/Release/AutoTest.exe) <br />

同时下载/x64/Release/server.conf到应用的目录下，配置服务器ip和端口后，直接双击即可运行

### 使用介绍
1. server.conf里的ip和port会自动加载到界面的输入框，可以随意修改
2. 点击“加载配置”，会弹出选择文件框（txt和dat后缀的文件），文件ansi编码；<br />
	加载的文件格式：#开头的表示注释，不会作为测试数据发送，其他的一条数据一行
3. 双击列表中的某一条会把其中的内容发送到指定端口并弹出返回值；
4. 点击“开始”会把加载的内容全部发送到指定端口并接受返回值；

### 编译
推荐使用visual studio community 2015版，这个是微软的免费版，不需要购买。<br />
直接F7编译即可。
