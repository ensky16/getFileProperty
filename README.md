# getFileProperty
MFC工具，获取文件名字和时间属性，并且将值放到粘贴板上，然后直接使用Ctrl+V即可粘贴了。

例如：
有一个文件：123.txt,  修改时间：2020年6月26日 14:33:11

将这个文件拖动到本软件中，直接Ctrl+V即可获取到上述信息

# 格式修改
如果需要更改显示时间的格式，比如更改为 月-日-年 等，请查看函数  CgetFilePropertyMFCDlg::SetFileNameAndProToClip()


