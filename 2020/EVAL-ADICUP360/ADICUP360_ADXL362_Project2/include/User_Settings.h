/*!
 *****************************************************************************
 * @file:    User_Settings.h
 * @brief:   Local WiFi Network and Cloud Instance Settings
 * @version: $Revision$
 * @date:    $Date$
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2015-2017 Analog Devices, Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  - Modified versions of the software must be conspicuously marked as such.
  - This software is licensed solely and exclusively for use with processors
    manufactured by or for Analog Devices, Inc.
  - This software may not be combined or merged with other code in any manner
    that would cause the software to become subject to terms and conditions
    which differ from those listed here.
  - Neither the name of Analog Devices, Inc. nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.
  - The use of this software may or may not infringe the patent rights of one
    or more patent holders.  This license does not release you from the
    requirement that you obtain separate licenses from these patent holders
    to use this software.

THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
TITLE, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
NO EVENT SHALL ANALOG DEVICES, INC. OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, PUNITIVE OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, DAMAGES ARISING OUT OF CLAIMS OF INTELLECTUAL
PROPERTY RIGHTS INFRINGEMENT; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

#ifndef USER_SETTINGS_H_
#define USER_SETTINGS_H_


/********************************** Enter information ****************************************************************/

/* Enter Local WiFi Network Information */
char ssid[] = "";                                                         // Enter SSID of WiFi Network
char password[] = "";                                                     // Enter Password of WiFi Network
char security_type[] = "";                                                // Enter security type
                                                                          // (0=Open, 1=WEP, 2=WPA, 3=WPA2, 4=WPA+WPA2, 5=WPA2 TKIP)
/* Enter Cloud Instance Information */
char instance_url[] = "";                                                 // Enter Cloud Instance URL
char app_key[] = "";                                                      // Enter Application Key

char Thing_Name[] = "ADICUP360_ADXL362_Thing";                            // Enter Thing Name
char Thing_Description[] = "Thing created by Device";                     // Enter Thing Description

/* Enter Location of Device here*/
float latitude  =  42.1944;                                               // Enter latitude
float longitude =  -71.1990;                                              // Enter longitude
float elevation =  0;                                                     // Enter elevation

/***********************************************************************************************************************/
char ThingTemplate_Name[] = "ADICUP360_ADXL362_ThingTemplate";
char Property1_Name[] = "X";
char Property2_Name[] = "Y";
char Property3_Name[] = "Z";

#endif /* USER_SETTINGS_H_ */

/*********************************************************************************************************************************************************************/
