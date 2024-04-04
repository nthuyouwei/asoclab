

report 連結:

有關report所要求的檔案catapult 部分都放在02，fsic放在03_vsim


02_edgedetect 是我們利用catapult hls 設計出edgedetect的硬體加速ip。

03_fsic_prj 是我們利用02中產生出的ip 合到FSIC，這裡我們提供兩種模擬方法:

1. vivado_xsim
```
cd 03_fsic_prj_xsim/rtl/user/testbench/tc
./run_xsim
source run_clean
```
![image](https://github.com/nthuyouwei/asoclab/assets/145022311/aaf15037-c3d3-40a8-a849-8c036ce73a63)

這會產生vcd檔可以利用gtkwave看波型。

2. Questasim_vsim
```
cd 03_fsic_prj_vsim/dsn/testbench/vsim
source run_vsim
```
![image](https://github.com/nthuyouwei/asoclab/assets/145022311/bb51ccee-21d6-4f56-9992-5ef060aa87ca)
