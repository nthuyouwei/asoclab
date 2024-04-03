//  Catapult Ultra Synthesis 2023.2/1059873 (Production Release) Mon Aug  7 10:54:31 PDT 2023
//  
//          Copyright (c) Siemens EDA, 1996-2023, All Rights Reserved.
//                        UNPUBLISHED, LICENSED SOFTWARE.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                   PROPERTY OF SIEMENS EDA OR ITS LICENSORS.
//  
//  Running on Linux mentor@RHEL74 3.10.0-1160.95.1.el7.x86_64 x86_64 aol
//  
//  Package information: SIFLIBS v26.2_0.0, HLS_PKGS v26.2_0.0, 
//                       SIF_TOOLKITS v26.2_0.0, SIF_XILINX v26.2_0.0, 
//                       SIF_ALTERA v26.2_0.0, CCS_LIBS v26.2_0.0, 
//                       CDS_PPRO v2023.1, CDS_DesignChecker v2023.2, 
//                       CDS_OASYS v21.1_3.1, CDS_PSR v23.1_1.18, 
//                       DesignPad v2.78_1.0
//  

solution new -state initial
solution options defaults
solution options set /Input/CppStandard c++11
solution options set /Input/TargetPlatform x86_64
solution options set /Input/SearchPath {../bmpUtil/inc ../cmodel/inc ../hls_c/inc}
solution options set /Output/OutputVHDL false
solution options set /Output/GenerateCycleNetlist false
solution options set /Output/Basename {extract {${ENTITY}}}
solution options set /Flows/SCVerify/INVOKE_ARGS {./image/people640x360_rgb.bmp 1 out_algorithm.bmp out_hw.bmp}
solution file add ../hls_c/inc/EdgeDetect.h -type CHEADER
solution file add ../hls_c/src/EdgeDetect_tb.cpp -type C++ -exclude true
solution file add ../bmpUtil/src/bmp_io.cpp -type C++ -exclude true
directive set -REGISTER_THRESHOLD 65536
go new
go analyze
go compile
solution library add nangate-45nm_beh -- -rtlsyntool DesignCompiler -vendor Nangate -technology 045nm
solution library add ccs_sample_mem
solution library add amba
go libraries
directive set -CLOCKS {clk {-CLOCK_PERIOD 10.0 -CLOCK_EDGE rising -CLOCK_UNCERTAINTY 0.0 -CLOCK_HIGH_TIME 5.0 -RESET_SYNC_NAME rst -RESET_ASYNC_NAME arst_n -RESET_KIND both -RESET_SYNC_ACTIVE high -RESET_ASYNC_ACTIVE low -ENABLE_ACTIVE high}}
go assembly
directive set /EdgeDetect_Top/widthIn:rsc -MAP_TO_MODULE {[DirectInput]}
directive set /EdgeDetect_Top/heightIn:rsc -MAP_TO_MODULE {[DirectInput]}
directive set /EdgeDetect_Top/sw_in:rsc -MAP_TO_MODULE {[DirectInput]}
#directive set /EdgeDetect_Top/dat_in:rsc -MAP_TO_MODULE amba.ccs_axi4stream_in
#directive set /EdgeDetect_Top/dat_out:rsc -MAP_TO_MODULE amba.ccs_axi4stream_out
directive set /EdgeDetect_Top/din_chn:rsc -MAP_TO_MODULE ccs_ioport.ccs_in_wait
directive set /EdgeDetect_Top/dout_chn:rsc -MAP_TO_MODULE ccs_ioport.ccs_out_wait
directive set /EdgeDetect_Top/EdgeDetect_VerDer/run/VROW -PIPELINE_INIT_INTERVAL 1
directive set /EdgeDetect_Top/EdgeDetect_HorDer/run/HROW -PIPELINE_INIT_INTERVAL 1
directive set /EdgeDetect_Top/EdgeDetect_MagAng/run/MROW -PIPELINE_INIT_INTERVAL 1
directive set /EdgeDetect_Top/dat_in_hor:cns -FIFO_DEPTH 0
directive set /EdgeDetect_Top/dy:cns -FIFO_DEPTH 2
directive set /EdgeDetect_Top/dat_in_mag:cns -FIFO_DEPTH 0
directive set /EdgeDetect_Top/dx:cns -FIFO_DEPTH 0
directive set /EdgeDetect_Top/EdgeDetect_VerDer/run/line_buf0:rsc -MAP_TO_MODULE ccs_sample_mem.ccs_ram_sync_singleport
directive set /EdgeDetect_Top/EdgeDetect_VerDer/run/line_buf0:rsc -GEN_EXTERNAL_ENABLE true
directive set /EdgeDetect_Top/EdgeDetect_VerDer/run/line_buf0:rsc -EXTERNAL_MEMORY true
directive set /EdgeDetect_Top/EdgeDetect_VerDer/run/line_buf1:rsc -MAP_TO_MODULE ccs_sample_mem.ccs_ram_sync_singleport
directive set /EdgeDetect_Top/EdgeDetect_VerDer/run/line_buf1:rsc -EXTERNAL_MEMORY true
directive set /EdgeDetect_Top/EdgeDetect_VerDer/run/line_buf1:rsc -GEN_EXTERNAL_ENABLE true
directive set /EdgeDetect_Top/EdgeDetect_HorDer/dat_in:rsc -MAP_TO_MODULE ccs_ioport.ccs_in_wait_coupled
directive set /EdgeDetect_Top/EdgeDetect_MagAng/dx_in:rsc -MAP_TO_MODULE ccs_ioport.ccs_in_wait_coupled
directive set /EdgeDetect_Top/EdgeDetect_MagAng/dy_in:rsc -MAP_TO_MODULE ccs_ioport.ccs_in_wait_coupled
go architect
go extract

# Show the memory map dump
#view file [solution get /SOLUTION_DIR]/rtl_csr_map.txt
