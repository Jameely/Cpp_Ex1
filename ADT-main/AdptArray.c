#include "AdptArray.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray , *PAdptArray;



PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printfunc_){
    if(copyFunc_== NULL || printfunc_ == NULL || delFunc_ == NULL){
        return NULL;
    }
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printfunc_ ;
	return pArr;
}


Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	if (pArr == NULL || pNewElem == NULL || idx < 0){
		return FAIL;
    }

	if (idx >= pArr->ArrSize)
	{
		
	PElement* newpElemArr;

		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL){
			return FAIL;
        }
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        if(!newpElemArr){
            return FAIL;
        }
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
    if(((pArr->pElemArr)[idx])!= NULL)
    {
	pArr->delFunc((pArr->pElemArr)[idx]);
    }
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}


PElement GetAdptArrayAt(PAdptArray parr, int idx){
    if(!parr || !(parr->copyFunc)){
        return NULL;
    }
    if((parr->pElemArr)[idx]==NULL)
    {
        return NULL;
    }
    return parr->copyFunc((parr->pElemArr)[idx]);
}

int GetAdptArraySize(PAdptArray pArr){
    if(!pArr){
        return -1;
    }
    return pArr->ArrSize;
}



void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL || pArr->delFunc==NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
        if(pArr->pElemArr[i]!=NULL){
		pArr->delFunc((pArr->pElemArr)[i]);
	}
    }
	free(pArr->pElemArr);
	free(pArr);
}

void PrintDB(PAdptArray pArr){
    for (size_t i = 0; i < pArr->ArrSize; i++)
    {
        if((pArr->pElemArr)[i] != NULL)
        {
        pArr->printFunc((pArr->pElemArr)[i]);
        }
    }       
}