/* Authors:
 * Pedro Almeida
 * Renato Valente
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xaxidma.h"
#include "xtmrctr_l.h"
#include "xil_printf.h"

/****************************** Definitions **********************************/

typedef int bool;

#define N				4095

#define DMA_DEVICE_ID	XPAR_AXI_DMA_0_DEVICE_ID

#define SEED_VALUE      50

/*********************** DMA Configuration Function **************************/

int DMAConfig(u16 dmaDeviceId, XAxiDma* pDMAInstDefs)
{
	XAxiDma_Config* pDMAConfig;
	int status;

	// Initialize the XAxiDma device
	pDMAConfig = XAxiDma_LookupConfig(dmaDeviceId);
	if (!pDMAConfig)
	{
		xil_printf("No DMA configuration found for %d.\r\n", dmaDeviceId);
		return XST_FAILURE;
	}

	status = XAxiDma_CfgInitialize(pDMAInstDefs, pDMAConfig);
	if (status != XST_SUCCESS)
	{
		xil_printf("DMA Initialization failed %d.\r\n", status);
		return XST_FAILURE;
	}

	if (XAxiDma_HasSg(pDMAInstDefs))
	{
		xil_printf("Device configured as SG mode.\r\n");
		return XST_FAILURE;
	}

	// Disable interrupts, we use polling mode
	XAxiDma_IntrDisable(pDMAInstDefs, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(pDMAInstDefs, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

	return XST_SUCCESS;
}

/************************ Auxiliar Functions *********************/
bool primesCheck(int n){

    if(n <= 1){
        return FALSE;
    }

    if(n == 2){
        return TRUE;
    }

    int flag = 0;
    int i;
    for(i = 2; i <= n/2; i++){
        if(n % i == 0){
            flag = 1;
            break;
        }
    }
    if (flag == 0){
        return TRUE;
    }
    return FALSE;
}

/*********************** Prime Functions *************************/

void PrimesSw(int* dst, int* src, unsigned int size)
{
	int* p;
	for (p = src; p < src + size; p++, dst++) {

		bool temp = primesCheck(*p);
		if (temp){      // primo -> escreve o numero
			*dst = *p;
		}
		else{           // nao e primo -> escreve zero
			*dst = 0;
		}
	}
}

// dst -> result of the software/hardware
// src -> original values
bool CheckPrimes(int* dst, int* src, unsigned int size)
{
	int* p;
	for (p = src; p < src + size; p++, dst++) {
		int res;
		bool temp = primesCheck(*p);
		if (temp){
			res = *p;
		}
		else{
			res = 0;
		}

		if(res != *dst){
			return FALSE;
		}
	}

	return TRUE;
}

bool CheckPrimesHw(int* dst, int* src, unsigned int size)
{
	int* p;
	dst++;
	for (p = src; p < src + size; p++, dst++) {
		int res;
		bool temp = primesCheck(*p);
		if (temp){
			res = *p;
		}
		else{
			res = 0;
		}

		if(res != *dst){
			return FALSE;
		}
	}

	return TRUE;
}

/*****************************  Helper Functions *****************************/
int min(int a, int b){
	return ((a < b) ? a : b);
}

void PrintDataArray(int* pData, unsigned int size)
{
	int* p;
	for(p = pData; p < pData + size; p++){
		xil_printf("%d    ", *p);
	}
}

int countValuesNotZero(int* pData, unsigned int size){
	int* p;
	int count = 0;
	for(p = pData; p < pData + size; p++){
		if(*p != 0){
			count++;
		}
	}
	return count;
}

void ResetPerformanceTimer()
{
	XTmrCtr_Disable(XPAR_TMRCTR_0_BASEADDR, 0);
	XTmrCtr_SetLoadReg(XPAR_TMRCTR_0_BASEADDR, 0, 0x00000001);
	XTmrCtr_LoadTimerCounterReg(XPAR_TMRCTR_0_BASEADDR, 0);
	XTmrCtr_SetControlStatusReg(XPAR_TMRCTR_0_BASEADDR, 0, 0x00000000);
}

void RestartPerformanceTimer()
{
	ResetPerformanceTimer();
	XTmrCtr_Enable(XPAR_TMRCTR_0_BASEADDR, 0);
}

unsigned int GetPerformanceTimer()
{
	return XTmrCtr_GetTimerCounterReg(XPAR_TMRCTR_0_BASEADDR, 0);
}

unsigned int StopAndGetPerformanceTimer()
{
	XTmrCtr_Disable(XPAR_TMRCTR_0_BASEADDR, 0);
	return GetPerformanceTimer();
}


/******************************  Main Functions ******************************/

int main()
{
	int status;

	XAxiDma dmaInstDefs;

	int srcData[N];
	int dstData[N];
	int nPrimesFound;

	init_platform();

	unsigned int timeElapsed;


	xil_printf("\r\n------Primes Program------\n");

	xil_printf("\nFilling memory with pseudo-random data. Seed is %d.\n", SEED_VALUE);
	RestartPerformanceTimer();

	xil_printf("\r\nPrimes Program\n");

	srand(SEED_VALUE);
	for (int i = 0; i < N; i++)
	{
		srcData[i] = rand() % 256; // limitar numero gerado
	}

	timeElapsed = StopAndGetPerformanceTimer();
	xil_printf("\n\rMemory initialization time: %d microseconds\n\n",
			   timeElapsed / (XPAR_CPU_M_AXI_DP_FREQ_HZ / 1000000));
	PrintDataArray(srcData, min(20, N));
	xil_printf("\n");

	// Software only
	xil_printf("\n----------------------------------------------------------------------\n\rSoftware only\n");
	RestartPerformanceTimer();
	PrimesSw(dstData, srcData, N);
	timeElapsed = StopAndGetPerformanceTimer();
	xil_printf("\nExecution time: %d microseconds\n",
			   timeElapsed / (XPAR_CPU_M_AXI_DP_FREQ_HZ / 1000000));
//	PrintDataArray(dstData, min(20, 400));

	nPrimesFound = countValuesNotZero(dstData, N);
	xil_printf("\n Number of primes found Sw:  %d\n", nPrimesFound);

	int newDst[nPrimesFound];
	int j = 0;
	for(int i = 0; i < N; i++){
		if(dstData[i] != 0){
			newDst[j] = dstData[i];
			j++;
		}
	}

	xil_printf("\n");
	PrintDataArray(newDst, min(20, 400));

	xil_printf("\n\rChecking Sw result: %s\n",
			   CheckPrimes(dstData, srcData, N) ? "OK" : "Error");



	xil_printf("\n----------------------------------------------------------------------\n\rHardware assisted\n\rConfiguring DMA...");
	status = DMAConfig(XPAR_AXI_DMA_0_DEVICE_ID, &dmaInstDefs);
	if (status != XST_SUCCESS)
	{
		xil_printf("\r\nConfiguration failed.");
		return XST_FAILURE;
	}
	xil_printf("\nDMA running...\n");

	// DMA and Hardware assisted
	RestartPerformanceTimer();
	status = XAxiDma_SimpleTransfer(&dmaInstDefs,(UINTPTR) dstData, N * sizeof(int),
									XAXIDMA_DEVICE_TO_DMA);
	status = XAxiDma_SimpleTransfer(&dmaInstDefs,(UINTPTR) srcData, N * sizeof(int),
									XAXIDMA_DMA_TO_DEVICE);
	if (status != XST_SUCCESS)
	{
		xil_printf("\r\nDMA transfer failed.");
		return XST_FAILURE;
	}
	while ((XAxiDma_Busy(&dmaInstDefs, XAXIDMA_DEVICE_TO_DMA)) ||
		   (XAxiDma_Busy(&dmaInstDefs, XAXIDMA_DMA_TO_DEVICE)))
	{
		/* Wait */
	}

	timeElapsed = StopAndGetPerformanceTimer();
	xil_printf("\nExecution time: %d microseconds\n",
			   timeElapsed / (XPAR_CPU_M_AXI_DP_FREQ_HZ / 1000000));
//	PrintDataArray(dstData, min(20, N));

	nPrimesFound = countValuesNotZero(dstData, N);
	xil_printf("\n Number of primes found Hw:  %d\n", nPrimesFound);

	int newDst2[nPrimesFound];
	j = 0;
	for(int i = 0; i < N; i++){
		if(dstData[i] != 0){
			newDst2[j] = dstData[i];
			j++;
		}
	}
	xil_printf("\n");
	PrintDataArray(newDst2, min(20, 400));

	xil_printf("\n\n\rChecking Hw result: %s\n\r",
			   CheckPrimes(newDst2, newDst, nPrimesFound) ? "OK" : "Error");

//	xil_printf("\n\n\rChecking Hw result: %s\n\r",
//			   CheckPrimesHw(dstData, srcData, 4095) ? "OK" : "Error");

	cleanup_platform();
//	return XST_SUCCESS;
	return 0;
}
