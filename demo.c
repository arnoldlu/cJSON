/*
  Copyright (c) 2009 Dave Gamble

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

void printJson(cJSON *root)
{
	if(!root)
	{
		printf("NULL JSON root.\n");
		return;
	}

	printf("Type=0x%02x, %s=%s\n", root->type, root->string, cJSON_Print(root));
}

static char * makeJson(void)
{
	cJSON *pJsonRoot = NULL;
	cJSON *pSubJson = NULL;
	char *p = NULL;

	pJsonRoot = cJSON_CreateObject();
	if(NULL == pJsonRoot)
	{
		printf("%s line=%d NULL\n", __func__, __LINE__);
		return NULL;
	}
	cJSON_AddStringToObject(pJsonRoot, "hello", "hello world");
	cJSON_AddNumberToObject(pJsonRoot, "number", 10010);
	cJSON_AddBoolToObject(pJsonRoot, "bool", 1);
	pSubJson = cJSON_CreateObject();
	if(NULL == pSubJson)
	{
		printf("%s line=%d NULL\n", __func__, __LINE__);
		cJSON_Delete(pJsonRoot);
		return NULL;
	}
	cJSON_AddStringToObject(pSubJson, "subjsonobj", "a sub json string");
	cJSON_AddItemToObject(pJsonRoot, "subobj", pSubJson);

	p = cJSON_Print(pJsonRoot);
	if(NULL == p)
	{
		printf("%s line=%d NULL\n", __func__, __LINE__);
		cJSON_Delete(pJsonRoot);
		return NULL;
	}

	cJSON_Delete(pJsonRoot);

	return p;
}


static void parseJson(char * pMsg)
{
	cJSON *pJson;
	cJSON *pSub;
	cJSON * pSubSub;

	if(NULL == pMsg)
	{
	return;
	}

	pJson = cJSON_Parse(pMsg);
	if(NULL == pJson)
	{
		return ;
	}

	pSub = cJSON_GetObjectItem(pJson, "hello");
	printJson(pSub);

	pSub = cJSON_GetObjectItem(pJson, "number");
	printJson(pSub);

	pSub = cJSON_GetObjectItem(pJson, "bool");
	printJson(pSub);

	pSub = cJSON_GetObjectItem(pJson, "subobj");
	printJson(pSub);

	pSubSub = cJSON_GetObjectItem(pSub, "subjsonobj");
	printJson(pSubSub);

	cJSON_Delete(pJson);
}

int main(void)
{
	char *p;

	/* print the version */
	printf("Version: %s\n", cJSON_Version());

	p = makeJson();
	if(NULL == p)
	{
		return 0;
	}
	printf("p = \n%s\n\n", p);
	parseJson(p);
	free(p);
	return 0;
}
