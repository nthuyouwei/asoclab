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
#include "EdgeDetect_VerDer.h"
#include "EdgeDetect_HorDer.h"
#include "EdgeDetect_MagAng.h"
#include <mc_scverify.h>

//namespace EdgeDetect_IP {

  #pragma hls_design top
  class EdgeDetect_Top
  {
    //instances
    EdgeDetect_VerDer VerDer_inst;
    EdgeDetect_HorDer HorDer_inst;
    EdgeDetect_MagAng MagAng_inst;
  
    // Static interconnect channels (FIFOs) between blocks
    ac_channel<gradType4x>       dy;
    ac_channel<gradType4x>       dx;
    ac_channel<pixelType4x>      dat_in_hor; // channel for passing input pixels to horizontalDerivative
    ac_channel<pixelType4x>      dat_in_mag;
  
  public:
    EdgeDetect_Top() {}
  
    //--------------------------------------------------------------------------
    // Function: run
    //   Top interface for data in/out of class. Combines vertical and
    //   horizontal derivative and magnitude/angle computation.
    #pragma hls_design interface
    void CCS_BLOCK(run)(maxWType              &widthIn,
                        maxHType              &heightIn,
                        bool                  &sw_in,
                        uint32                &crc32_hw_pix_in,
                        uint32                &crc32_hw_pix_out,
                        ac_channel<Stream_t>  &din_chn,
                        ac_channel<Stream_t>  &dout_chn)
    {  
      VerDer_inst.run(din_chn, widthIn, heightIn, dat_in_hor, dy);
      HorDer_inst.run(dat_in_hor, widthIn, heightIn, dx, dat_in_mag);
      MagAng_inst.run(dx, dy, widthIn, heightIn,dat_in_mag,sw_in,crc32_hw_pix_in ,crc32_hw_pix_out,dout_chn);
    }
  };

//}


