/**
************************************************************************
This C++ sample is developed using the C++ API of Dynamsoft Barcode Reader.
The sample demonstrates how to read barcode from the Linux Command Line.
*************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "../../../include/DynamsoftBarcodeReader.h"

int DecodeFile(CBarcodeReader& reader,const char* pszImageFile,float& fCostTime)
{
	struct timeval ullTimeBegin, ullTimeEnd;
	int iResult = 0;
    gettimeofday(&ullTimeBegin, NULL);
    iResult = reader.DecodeFile(pszImageFile);
    gettimeofday(&ullTimeEnd, NULL);
    fCostTime = (float)((ullTimeEnd.tv_sec * 1000 * 1000 +  ullTimeEnd.tv_usec) - (ullTimeBegin.tv_sec * 1000 * 1000 + ullTimeBegin.tv_usec))/(1000 * 1000);
    return iResult;
}

void ToHexString(unsigned char* pSrc, int iLen, char* pDest)
{
	const char HEXCHARS[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	int i;
	char* ptr = pDest;
	for(i = 0; i < iLen; ++i)
	{
		snprintf(ptr, 4, "%c%c ", HEXCHARS[ ( pSrc[i] & 0xF0 ) >> 4 ], HEXCHARS[ ( pSrc[i] & 0x0F ) >> 0 ]);
		ptr += 3;
	}
}

void OutputResult(CBarcodeReader& reader,int errorcode,float time)
{
	char* pszTemp = NULL;
	char* pszTemp1 = NULL;
	char* pszTemp2 = NULL;
	int iRet = errorcode;
	pszTemp = (char*)malloc(4096);

	if (iRet != DBR_OK && iRet != DBRERR_MAXICODE_LICENSE_INVALID && iRet != DBRERR_GS1_COMPOSITE_LICENSE_INVALID && iRet != DBRERR_LICENSE_EXPIRED && iRet != DBRERR_QR_LICENSE_INVALID &&
		iRet != DBRERR_1D_LICENSE_INVALID && iRet != DBRERR_PDF417_LICENSE_INVALID && iRet != DBRERR_DATAMATRIX_LICENSE_INVALID && iRet !=DBRERR_AZTEC_LICENSE_INVALID && 
		iRet != DBRERR_GS1_DATABAR_LICENSE_INVALID && iRet != DBRERR_PATCHCODE_LICENSE_INVALID && iRet != DBRERR_POSTALCODE_LICENSE_INVALID && iRet != DBRERR_DOTCODE_LICENSE_INVALID && 
		iRet != DBRERR_DOTCODE_LICENSE_INVALID && iRet != DBRERR_DPM_LICENSE_INVALID && iRet != DBRERR_IRT_LICENSE_INVALID)
	{
		snprintf(pszTemp, 4096, "Failed to read barcode: %s\r\n", CBarcodeReader::GetErrorString(iRet));
		printf("%s",pszTemp);
		free(pszTemp);
		return;
	}

	TextResultArray *paryResult = NULL;
	reader.GetAllTextResults(&paryResult);

	if (paryResult->resultsCount == 0)
	{
		snprintf(pszTemp, 4096, "No barcode found. Total time spent: %.3f seconds.\r\n", time);
		printf("%s",pszTemp);
		free(pszTemp);
		CBarcodeReader::FreeTextResults(&paryResult);
		return;
	}

	snprintf(pszTemp, 4096, "Total barcode(s) found: %d. Total time spent: %.3f seconds\r\n\r\n", paryResult->resultsCount, time);
	printf("%s",pszTemp);
	for (int iIndex = 0; iIndex < paryResult->resultsCount; iIndex++)
	{
		snprintf(pszTemp, 4096, "Barcode %d:\r\n", iIndex + 1);
		printf("%s",pszTemp);
		snprintf(pszTemp, 4096, "    Type: %s\r\n", paryResult->results[iIndex]->barcodeFormatString);
		printf("%s",pszTemp);
		snprintf(pszTemp, 4096, "    Value: %s\r\n", paryResult->results[iIndex]->barcodeText);
		printf("%s",pszTemp);
		pszTemp1 = (char*)malloc(paryResult->results[iIndex]->barcodeBytesLength*3 + 1);
		pszTemp2 = (char*)malloc(paryResult->results[iIndex]->barcodeBytesLength*3 + 100);
		ToHexString(paryResult->results[iIndex]->barcodeBytes, paryResult->results[iIndex]->barcodeBytesLength, pszTemp1);
		snprintf(pszTemp2, paryResult->results[iIndex]->barcodeBytesLength*3 + 100, "    Hex Data: %s\r\n", pszTemp1);
		printf("%s",pszTemp2);
		free(pszTemp1);
		free(pszTemp2);
	}
	free(pszTemp);
	CBarcodeReader::FreeTextResults(&paryResult);
	return;
}

int main(int argc, const char* argv[])
{
	int iRet = -1;
	float fCostTime = 0;


	CBarcodeReader reader;
	reader.InitLicense("LICENSE-KEY");


    // read barcode.
	char pszImageFile[512] = { 0 };
	if(argc<=1)
	{
		printf("Usage: ReadBarcode [ImageFilePath]\n");
		return 1; 
	}
	int iLen;
	iLen = strlen(argv[1]);
	if (argv[1][0] == '\'')
	{
		if(argv[1][iLen - 3] == '\'')
			memcpy(pszImageFile, argv[1] + 1, iLen - 4);
		else if(argv[1][iLen - 2] == '\'')
			memcpy(pszImageFile, argv[1] + 1, iLen - 3);
	}
	else
		memcpy(pszImageFile, argv[1], iLen);

    iRet = DecodeFile(reader,pszImageFile,fCostTime);
	const char* errorString  = CBarcodeReader::GetErrorString(iRet);
    if(iRet !=DBR_OK)
    {
        printf("Error code: %d. Error message: %s\n", iRet, errorString);
    }
    // output barcode result.
    OutputResult(reader,iRet,fCostTime);
	return 0;
}
