set path=%path%;%cd%\..\bin

cd html

call utf82gbk.bat index.hhp
call utf82gbk.bat index.hhc
call utf82gbk.bat index.hhk
call utf82gbk.bat *.html
call html-utf82gbk *.html

"C:\Program Files\HTML Help Workshop\hhc.exe" index.hhp

if exist index.chm copy index.chm ..\����Ա�ֲ�.chm

cd ..