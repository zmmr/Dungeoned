@echo off
set DebugDir=E:\Users\zhoujie\Documents\�ٶ���\�ҵĹ���\ħ��\Dungeoned\Resources\
set ToolPath==D:\DataMaker\

@echo ����Avatar
set TileXlsx=%DebugDir%Tileת���.xlsx

@echo/
@echo ������Ϸ�������õ���
%ToolPath%DataMaker.exe TileList %TileXlsx% %DebugDir%

pause