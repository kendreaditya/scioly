/*****************************************************************************
 * Res_Test.c
 *****************************************************************************/

#include <sys/platform.h>
#include "Res_Test.h"

int main(int argc, char *argv[])
{
	
	/*
	 * - Start by setting ADC in idle mode with AdcGo().
	 * - Set up ADC with AdcRng(), AdcFlt(), AdcMski() and AdcPin().
	 * - Optionally use AdcBuf() AdcDiag() and AdcBias().
	 * - Start conversion with AdcGo().
	 * - Check with AdcSta() that result is available.
	 * - Read result with AdcRd()
	 */
	volatile long ulADC1DAT = 0;
	AdcGo(pADI_ADC1,ADCMDE_ADCMD_IDLE);
	AdcFlt(pADI_ADC1,40,1,3 | ADCFLT_NOTCH2 | ADCFLT_CHOP | ADCFLT_RAVG2);
	AdcRng(pADI_ADC1,ADCCON_ADCREF_INTREF,ADCMDE_PGA_G32,ADCCON_ADCCODE_INT);
	//AdcBuf(pADI_ADC1,ADCCFG_EXTBUF_VREFPN,ADC_BUF_ON);
	AdcPin(pADI_ADC1,ADCCON_ADCCN_AIN1,ADCCON_ADCCP_AIN0);
	AdcMski(pADI_ADC1,ADCMSKI_RDY,1);
	AdcGo(pADI_ADC1,ADCMDE_ADCMD_CONT);
	ulADC1DAT = AdcRd(pADI_ADC1);

	return 0;
}


void Printf(const char *fmt, ...)
{
   //char buff[256];

   //va_list args;
   //va_start (args, fmt);

   //vsprintf (buff, fmt, args);
   //va_end (args);

   //UART_WriteString(buff);
}
