@echo off
set DebugDir=E:\Users\zhoujie\Documents\百度云\我的工程\魔塔\Dungeoned\Resources\
set ToolPath==D:\DataMaker\

@echo 生成Avatar
set TileXlsx=%DebugDir%Tile转义表.xlsx

@echo/
@echo 生成游戏数据配置档：
%ToolPath%DataMaker.exe TileList %TileXlsx% %DebugDir%

pause