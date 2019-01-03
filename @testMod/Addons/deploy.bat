taskkill /f /im DayZServer_x64.exe
taskkill /f /im DZSALModServer.exe
taskkill /f /im DayZ_x64.exe

timeout /t 2

"C:\Program Files\PBO Manager v.1.4 beta\PBOConsole.exe" -pack ./testMod ./testMod.pbo
"C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\DsUtils\DSSignFile.exe" "C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\DsUtils\Bulot.biprivatekey" "C:\Program Files (x86)\Steam\steamapps\common\DayZServer\@testMod\Addons\testMod.pbo"
rmdir /S /Q "C:\Program Files (x86)\Steam\steamapps\common\DayZ\@testMod"
echo D | xcopy /E "C:\Program Files (x86)\Steam\steamapps\common\DayZServer\@testMod" "C:\Program Files (x86)\Steam\steamapps\common\DayZ\@testMod"
"C:\Program Files (x86)\Steam\steamapps\common\DayZServer\StartServer.bat"