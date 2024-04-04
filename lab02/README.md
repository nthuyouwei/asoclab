report 連結:

02_edgedetect 是我們利用catapult hls 設計出edgedetect的硬體加速ip。

03_fsic_prj 是我們利用02中產生出的ip 合到FSIC，這裡我們提供兩種模擬方法:

1. vivado_xsim
```
cd 03_fsic_prj_xsim/rtl/user/testbench/tc
./run_xsim
source run_clean
```
