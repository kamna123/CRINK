#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include "cuda_y.h"
#include "AffineTest.h"
 
void Affine_NonAffine_Test(struct StatementNode* write_var,struct StatementNode* read_var)
{
    struct StatementNode *writeTemp,*readTemp;
    struct StringNode *writeString,*readString;
    struct SizeNode *writeSize,*readSize;
    int sizeCount=0;
    writeTemp=write_var;
    while(writeTemp&&sizeCount==0)
    {
        writeSize=writeTemp->stringNode->size;
        while(writeSize)
        {
            writeString=writeSize->sizeString;
            while(writeString)
            {
                if(writeString->size!=NULL)
                {
                    sizeCount=1;
                    break;
                    }
                writeString=writeString->next;
            }
            writeSize=writeSize->next;
        }
        writeTemp=writeTemp->next;
    }
    if(sizeCount==1)
        AffineKernel='n';
    readTemp=read_var;
    while(readTemp&&sizeCount==0)
    {
        readSize=readTemp->stringNode->size;
        while(readSize)
        {
            readString=readSize->sizeString;
            while(readString)
            {
                if(readString->size!=NULL)
                {
                    sizeCount=1;
                    break;
                    }
                readString=readString->next;
            }
            readSize=readSize->next;
        }
        readTemp=readTemp->next;
    }
    if(sizeCount==1)
        AffineKernel='n';
}
