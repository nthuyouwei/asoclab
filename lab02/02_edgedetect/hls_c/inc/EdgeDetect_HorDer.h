/**************************************************************************
 *                                                                        *
 *  Edge Detect Design Walkthrough for HLS                                *
 *                                                                        *
 *  Software Version: 1.0                                                 *
 *                                                                        *
 *  Release Date    : Tue Jan 14 15:40:43 PST 2020                        *
 *  Release Type    : Production Release                                  *
 *  Release Build   : 1.0.0                                               *
 *                                                                        *
 *  Copyright 2020, Siemens                                               *
 *                                                                        *
 **************************************************************************
 *  Licensed under the Apache License, Version 2.0 (the "License");       *
 *  you may not use this file except in compliance with the License.      *
 *  You may obtain a copy of the License at                               *
 *                                                                        *
 *      http://www.apache.org/licenses/LICENSE-2.0                        *
 *                                                                        *
 *  Unless required by applicable law or agreed to in writing, software   *
 *  distributed under the License is distributed on an "AS IS" BASIS,     *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or       *
 *  implied.                                                              *
 *  See the License for the specific language governing permissions and   *
 *  limitations under the License.                                        *
 **************************************************************************
 *                                                                        *
 *  The most recent version of this package is available at github.       *
 *                                                                        *
 *************************************************************************/
#pragma once

#include "EdgeDetect_defs.h"
#include <mc_scverify.h>



  class EdgeDetect_HorDer
  {
  public:
    EdgeDetect_HorDer() {}
  
    #pragma hls_design interface
    void CCS_BLOCK(run)(ac_channel<pixelType4x> &dat_in,
                        maxWType                &widthIn,
                        maxHType                &heightIn,
                        ac_channel<gradType4x>    &dx,
                        ac_channel<pixelType4x> &dat_out)
    {

  
      pixelType p[9];
      pixelType4x pix;
      gradType4x  grad;

      
      HROW: for (maxHType y = 0; ; y++) {
        #pragma hls_pipeline_init_interval 1
        HCOL: for (maxWType x = 0; ; x+=4) { // HCOL has one extra iteration to ramp-up window

          if (x <= (widthIn- 4))
            pix = dat_in.read();


            #pragma hls_unroll yes
            for (int i=0; i < 5; i++)
              p[i] = p[i+4];
                        
            #pragma hls_unroll yes
            for (int i=0; i < 4; i++)
              p[i+5] = pix.slc<8>(i*8);
              
            if (x==4){
             p[0]=p[2];
            }
            if (x==widthIn){
             p[5]=p[3];
            }  

          // Calculate derivative
          #pragma hls_unroll yes
          for(int i=0; i < 4; i++)
          {
            gradType grad_tmp;
            grad_tmp = p[i]*kernel1[0] + p[i+1]*kernel1[1] + p[i+2]*kernel1[2];
            grad.set_slc(i*9, grad_tmp);
          }
  
          if (x != 0) { // Write streaming interface
            pixelType4x p_tmp; 
            for (int i=0;i<4;i++){
            
            p_tmp.set_slc(8*i,p[i+1]);
            }

            dat_out.write(p_tmp);
            dx.write(grad); // derivative out
          }

          // programmable width exit condition
          if ( x == widthIn) {
            break;
          }
        }
        // programmable height exit condition
        if (y == maxHType(heightIn-1)) { // cast to maxHType for RTL code coverage
          break;
        }
      }
    }
  };




