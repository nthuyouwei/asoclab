# 如果你有我完整的usb，只要執行以下步驟

你需要先利用Mbed Studio寫入程式到mbed板子然後就可以開啟電源等待python。

打開powershell輸入以下指令，車車就會開始跑了

```
cd D:\User\virtualenvs
ee2405\Scripts\activate
cd ..
cd ..
cd '.\Mbed Programs\14_4_QTI_LineFolowing\'
python.exe .\discover_clock_ble.py
``` 

# 如果你沒有我的usb，你需要載入對應的python lib，

```

pip install bleak
pip install numpy
pip install -U matplotlib
```
載入後就可以跑
```
python.exe .\discover_clock_ble.py
```
