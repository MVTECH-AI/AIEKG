#ifndef SCRAWREADER_H
#define SCRAWREADER_H
#ifdef __cplusplus  
extern "C" {  
#endif 
#ifdef SCRAWREADER_EXPORTS
#define SCRAWREADER_API __declspec(dllexport)
#else
#define SCRAWREADER_API __declspec(dllimport)
#endif

// Read the all lead data from raw file.
// The data was layout like the following order: (5000 I data) (5000 II data) (5000 III data) AVL AVF AVR V1~V6  
// sFilePath the absolute path for raw data..
// sLeadData should have enough memory(5000*12*short).
//strMsg declare for char strMsg[255];receive the error message. if null,will not set.
// ret: 0 succeed
//		-1 file error
//		-2 memory error
//		-100 unknown error
#define RAWDATALEN 5000
SCRAWREADER_API int readRawLeadData(const char* sFilePath,short* iLeadData,char* strMsg);
typedef int (*fReadRawLeadData)(const char* sFilePath,short* iLeadData,char* strMsg);
#ifdef __cplusplus  
} 
#endif 
#endif

