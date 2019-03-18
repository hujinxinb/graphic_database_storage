# graphic_database_storage
实现图形数据库的存储。也即在关系型数据库中存取二进制结构化数据。在Visual Studio提供的标准MFC多文档应用界面程序进行开发。

<br><br>
所需实现的具体功能包括：
<br><br>
（1）.在界面中可任意绘制如矩形，文字，折线等基本图元。
<br><br>
（2）.设计属性窗口，可通过属性窗口得到或修改已绘制图元的属性数据，诸如形状，颜色，起始点坐标，字体大小，折线粗细等。
<br><br>
（3）.通过IP远程连接外部服务器上的SQL Server数据库
<br><br>
（4）.将界面上绘制的图形转换成结构化数据存储到远程的SQL Server数据库中。
<br><br>
（5）.将组合图形对象，也即图形间的组合关系，同样存储到远程SQL Server数据库中。
<br><br>

总体的设计思想在于：将图形用适当的规则，离散成数据信息，即属性数据和几何数据。属性数据是指图形的诸如颜色，大小，粗细，厚度等的固有属性。
<br>
几何数据是指图形的位置坐标数据，比如各个端点的坐标数据。然后一次绘制的多个图形，对应于在关系型数据库中两张表。
<br>
一张表用来存储各个图元的属性数据和几何数据，每个图元作为表中的一行。另一张表用来存储图形间的组合嵌套关系。
<br><br>
在文档界面绘制图形信息：
<br><br>
![Image text](https://github.com/hujinxinb/graphic_database_storage/blob/master/img/2a.jpg)
<br><br>
框选图元即在属性窗口得到其可编辑的属性信息：
<br><br>
![Image text](https://github.com/hujinxinb/graphic_database_storage/blob/master/img/4.jpg)
<br><br>
连接到远程服务器的SQL Server数据库并编辑表：
<br><br>
![Image text](https://github.com/hujinxinb/graphic_database_storage/blob/master/img/10.jpg)
<br><br>
成功写入远程数据库：
<br><br>
![Image text](https://github.com/hujinxinb/graphic_database_storage/blob/master/img/11.jpg)

