#include "tcpip/tcpip.h"
 tWFScanResult bssDesc;
    typedef struct
        {
            uint8_t      bssidn[WF_BSSID_LENGTH]; // Network BSSID value
            uint8_t      ssidn[WF_MAX_SSID_LENGTH]; // Network SSID value
            uint8_t      rssin; // Signal strength of received frame beacon or probe response
            uint8_t      channeln; // Channel number

        } tWFScanResultneeded;
 tWFScanResultneeded bssDescn[];
 uint8_t *tempbssid[];
 uint8_t *tempssid[];
 uint8_t *temprssi[];
 uint8_t *tempchannel[];

void scanfor24hper5s()
{
    static uint32_t t = 0;// counting for 5s
    static uint8_t i = 0;// for the scanning result in time sequence
    int x;
    if (TickGet()-t >= 5*TICK_SECOND)
    {
        LED1_ON();
        WFInitScan();
        if (WFStartScan() == WF_SUCCESS) 
        {
            SCAN_SET_DISPLAY(SCANCXT.scanState);
            SCANCXT.displayIdx = 0;
        }
        for(x=0; x < SCANCXT.numScanResults; x++)
        {
            if (WFRetrieveScanResult(x, &bssDesc)== WF_SUCCESS)
            {
              Getneededresult(bssDescn[x]);
            };
            
        }
        //tWFScanResultneeded temp;
              //if (x)
        i++;
        tempbssid[i] = bssDescn->bssidn;
        tempssid[i] = bssDescn->ssidn;
        temprssi[i] = bssDescn->rssin;
        tempchannel[i] = bssDescn->channeln;
        LED2_ON();
        //DelayMs(250);
        LED1_OFF();
        LED2_OFF();
        t = TickGet();
        i++;
    
}
void Getneededresult (tWFScanResultneeded  p_scanResult)
     {
        p_scanResult.bssidn = bssDesc->bssid;
        p_scanResult.ssidn = bssDesc->ssid;
        p_scanResult.rssin = bssDesc->rssi;
        p_scanResult.channeln = bssDesc->channel;
        return;   
     }
