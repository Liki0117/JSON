#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*CJSON TYPES:  */
#define JSON_FALSE 0
#define JSON_TRUE  1
#define JSON_NULL  2
#define JSON_NUMBER 3
#define JSON_STRING 4
#define JSON_ARRAY 5
#define JSON_OBJECT 6

/*THE CJSON STRUCTURE*/
typedef struct JSON{
	int type;                                        /*the type of the item,as above */
	char *valuestring;                            	 /*the item's string,if type==JSON_STRING  */
	int  valueint;                                   /*the item's number,if type==JSON_TRUE||JSON_FALSE */
	double valuedouble;                              /*the item's number,if type==JSON_NUMBER */

	unsigned int   which;                            /* The item's index, if type == JSON_ARRAY */
    char           *key;                             /* The item's key, if type == JSON_OBJECT */
    struct JSON    *phead;
    struct JSON    *pend;
    struct JSON    *pnext;
    unsigned int   length;
}JSON;


/***************************************************    Create   ***********************************************************/
JSON *CreateNumber(double num)  
{
	JSON *ja=(struct JSON *)malloc(sizeof(JSON));
	ja->type = 3;
	ja->valuestring=NULL;
	ja->valueint=-1;
	ja->valuedouble=num;
	ja->which=0;
	ja->key=NULL;
	ja->phead=NULL;
	ja->pend=NULL;
	ja->pnext=NULL;
	ja->length=0;
	return ja;
}

JSON *CreateString(const char *string)
{
	JSON *ja=(struct JSON *)malloc(sizeof(JSON));
	ja->type = 4;
	ja->valuestring=(char*)string;
	ja->valueint=-1;
	ja->valuedouble=0;
	ja->which=0;
	ja->key=NULL;
	ja->phead=NULL;
	ja->pend=NULL;
	ja->pnext=NULL;
	ja->length=0;
	return ja;
}

JSON *CreateBool(int b)
{
	JSON *ja=(struct JSON *)malloc(sizeof(JSON));
	ja->type = 3;
	ja->valuestring=NULL;
	ja->valuedouble=0;
	ja->which=0;
	ja->key=NULL;
	ja->phead=NULL;
	ja->pend=NULL;
	ja->pnext=NULL;
	ja->length=0;
	if (b == 0)
		ja->valueint = false;
	else
		ja->valueint = true;
	return ja;
}

JSON *CreateNULL(void)
{
	JSON *ja=(struct JSON *)malloc(sizeof(JSON));
	ja->type = 2;
	ja->valuestring=NULL;
	ja->valueint=-1;
	ja->valuedouble=0;
	ja->which=0;
	ja->key=NULL;
	ja->phead=NULL;
	ja->pend=NULL;
	ja->pnext=NULL;
	ja->length=0;
	return ja;
}

JSON *CreateTrue(void)
{
	JSON *ja=(struct JSON *)malloc(sizeof(JSON));
	ja->type = 1;
	ja->valuestring=NULL;
	ja->valueint=true;
	ja->valuedouble=0;
	ja->which=0;
	ja->key=NULL;
	ja->phead=NULL;
	ja->pend=NULL;
	ja->pnext=NULL;
	ja->length=0;
	return ja;
}

JSON *CreateFalse(void)
{
	JSON *ja=(struct JSON *)malloc(sizeof(JSON));
	ja->type = 0;
	ja->valuestring=NULL;
	ja->valueint=false;
	ja->valuedouble=0;
	ja->which=0;
	ja->key=NULL;
	ja->phead=NULL;
	ja->pend=NULL;
	ja->pnext=NULL;
	ja->length=0;
	return ja;
}

JSON *CreateArray(void) 
{
	JSON *ja=(struct JSON *)malloc(sizeof(JSON));
	ja->type = 5;
	ja->valuestring=NULL;
	ja->valueint=-1;
	ja->valuedouble=0;
	ja->which=-1;
	ja->key=NULL;
	ja->phead=NULL;
	ja->pend=NULL;
	ja->pnext=NULL;
	ja->length=0;
	return ja;
}

JSON *CreateObject(void)
{
	JSON *ja=(struct JSON *)malloc(sizeof(JSON));
	ja->type = 6;
	ja->valuestring=NULL;
	ja->valueint=-1;
	ja->valuedouble=0;
	ja->which=0;
	ja->key=NULL;
	ja->phead=NULL;
	ja->pend=NULL;
	ja->pnext=NULL;
	ja->length=0;
	return ja;
}

/**********************************************************  Parse & Print *******************************************************************/

JSON *ParseJSON(const char *value)
{
	switch(value[0]) {
    case '-':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
        return CreateNumber(atol(value));
        break;
	case '\"':
        return CreateString(value);
        break;
	case 'n':
        return CreateNULL();
		break;
    case 't':
        return CreateTrue();
        break;
    case 'f':
        return CreateFalse();
        break;
    }
}


void PrintJSON(JSON *item)
{
	JSON *current=item;
	switch (item->type)
	{
	case 0:
		printf("false");
		break;
	case 1:
		printf("true");
		break;
	case 2:
		printf("null");
		break;
	case 3:
		printf("%d", item->valuedouble);
		break;
	case 4:
		printf("\"%s\"", item->valuestring);
		break;
	case 5:
		printf("[");
		while(current!=NULL)
		{
			PrintJSON(current);
			current=current->pnext;
		}
		printf("]");
		break;
	case 6:
		printf("{");
		while(current!=NULL)
		{
			PrintJSON(current);
			current=current->pnext;
		}
		printf("}");
		break;
	}
}

void PrintJSONToFile(JSON *item,const char *file_name)
{
	FILE* pfile=fopen(file_name,"w");
	JSON *current=item;
	switch (item->type)
	{
	case 0:
		fprintf(pfile,"false");
		break;
	case 1:
		fprintf(pfile,"true");
		break;
	case 2:
		fprintf(pfile,"null");
		break;
	case 3:
		fprintf(pfile,"%d", item->valuedouble);
		break;
	case 4:
		fprintf(pfile,"\"%s\"", item->valuestring);
		break;
	case 5:
		fprintf(pfile,"[");
		while(current!=NULL)
		{
			PrintJSON(current);
			current=current->pnext;
		}
		fprintf(pfile,"]");
		break;
	case 6:
		fprintf(pfile,"{");
		while(current!=NULL)
		{
			PrintJSON(current);
			current=current->pnext;
		}
		fprintf(pfile,"}");
		break;
	}
}*/

/*************************************        Append         *************************************************************************/

void AddItemToArray(JSON *array, JSON *item)
{   
	array->length++;
	array->pend=item;
	while(array->pnext)
		array = array->pnext;
	array->pnext = item;
	item->which=array->which+1;
}

void AddItemToObject(JSON *object, const char *key, JSON *value)
{
	object->length++;
	object->pend=value;
	while (object->pnext)
		object = object->pnext;
	object->pnext=value;
	value->key=(char*)key;
}

/******************************************************************    Remove/Delete     *******************************************************/

void DeleteJSON(JSON *item)
{
	if (item == NULL)
        return;
    if (item->type == JSON_STRING) {
        free(item->valuestring);
        item->valuestring = NULL;
    }
    if (item->key != NULL) {
        free(item->key);
        item->key = NULL;
    }
    if (item->length != 0) {
		JSON* nextitem;
		int i,j=item->length;
		for(i=0;i<j;i++)
		{
			nextitem=item->pnext;
			DeleteJSON(item);
			item=nextitem;
		}
    }
    free(item);
    return;
}

JSON *DetachItemFromArray(JSON *array, int which)
{
	JSON* current=array;
	JSON* del=current;
	/*找出第which-1个JSON，执行解挂*/
	if (which<0 || which>array->length){
		printf("Sorry!Nothing to return");
		exit(1);
	}
	else
	{
		for (int j = -1; j<which-1; j++)
			current = current->pnext;
		del=current->pnext;
		current->pnext=del->pnext;
		if(del->type==5||del->type==6)
			del->pend=NULL;
		else
			del->pnext=NULL;
		array->length--;
		return del;
	}
}
JSON *DetachItemFromObject(JSON *object, const char *key)
{
	JSON *del=object;
	/*依次比对object里每个JSON的"key"与要求的"key"*/
	int val_notfound=1;
	JSON* current=del;
	del=del->pnext;
	while(del)
	{
		if(strcmp(del->key,key)||!(del->key))
		{
			current=current->pnext;
			del=del->pnext;
		}
		else{
			val_notfound=0;
			break;}
	}
	/*执行解挂操作*/
	if(val_notfound)
		printf("JSON not found!");
	else{
		current->pnext=del->pnext;
		if(del->type==5||del->type==6)
			del->pend=NULL;
		else
			del->pnext=NULL;
		object->length--;
		return del;
	}
}

void *DeleteItemFromArray(JSON *array, int which)
{
	JSON* current=array;
	JSON* del=current;
	/*找出第which-1个JSON，执行删除*/
	if (which<0 || which>array->length){
		printf("Sorry!Nothing to return");
		exit(1);
	}
	else
	{
		for (int j = -1; j<which-1; j++)
			current = current->pnext;
		del=current->pnext;
		current->pnext=del->pnext;
		if(del->type==5||del->type==6)
			del->pend=NULL;
		else
			del->pnext=NULL;
		array->length--;
		DeleteJSON(del);
	}
	return NULL;
}

void DeleteItemFromObject(JSON *object, const char *key)
{
	JSON *del=object;
	/*依次比对object里每个JSON的"key"与要求的"key"*/
	int val_notfound=1;
	JSON* current=del;
	del=del->pnext;
	while(del)
	{
		if(strcmp(del->key,key)||!(del->key))
		{
			current=current->pnext;
			del=del->pnext;
		}
		else{
			val_notfound=0;
			break;}
	}
	/*执行删除操作*/
	if(val_notfound)
		printf("JSON not found!");
	else{
		current->pnext=del->pnext;
		if(del->type==5||del->type==6)
			del->pend=NULL;
		else
			del->pnext=NULL;
		object->length--;
		DeleteJSON(del);
	}
}


/*****************************************************      Update     ************************************************************************/

void ReplaceItemInArray(JSON *array, int which, JSON *new_item)
{
	JSON* current=array;
	JSON* del=current;
	/*找出第which-1个JSON，执行替换*/
	if (which<0 || which>=array->length)
		printf("Sorry!Nothing to return");
	else
	{
		current=array;
		for (int j = -1; j<which-1; j++)
			current = current->pnext;
		del=current->pnext;
		if(!(del->pnext))		
			array->pend=new_item;
		current->pnext=new_item;
		new_item->which=del->which;
		new_item->pnext=del->pnext;
		del->pnext=NULL;
		DeleteJSON(del);
	}
}

void ReplaceItemInObject(JSON *object, const char *key, JSON *new_value)
{
	JSON* phead=object;
	/*依次比对object里每个JSON的"key"与要求的"key"*/
	int val_notfound=1;
	JSON* preobject=object;
	object=object->pnext;
	while(object)
	{
		if(strcmp(object->key,key)||!(object->key))
		{
			preobject=preobject->pnext;
			object=object->pnext;
		}
		else{
			val_notfound=0;
			break;}
	}
	/*执行替换操作*/
	if(val_notfound)
		printf("JSON not found!");
	else{
		if(!(object->pnext))
			phead->pend=new_value;
		new_value->key=(char*)key;	
		preobject->pnext=new_value;
		new_value->pnext=object->pnext;
		object->pnext=NULL;
		DeleteJSON(object);
	}
}



/********************************************************           READ       *************************************************/

JSON *GetItemInArray(JSON *array, int which)
{
	JSON* current=array;
	/*找出第which个JSON*/
	if (which<0 || which>array->length){
		printf("Sorry!Nothing to return");
		exit(1);
	}
	else
	{
		for (int j = -1; j<which; j++)
			current = current->pnext;
	}
	return current;
}

JSON *GetItemInObject(JSON *object, const char *key)
{
	/*依次比对object里每个JSON的"key"与要求的"key"*/
	int val_notfound=1;
	object=object->pnext;
	while(object)
	{
		if(strcmp(object->key,key)||!(object->key))
			object=object->pnext;
		else{
			val_notfound=0;
			break;}
	}
	/*执行删除操作*/
	if(val_notfound)
		printf("JSON not found!");
	else return object;
}

JSON *Duplicate(JSON *item, int recurse)
{
	/*分配一个JSON大小的空间并复制*/
	JSON *ja=(struct JSON *)malloc(sizeof(JSON));
	ja->type = item->type;
	ja->valuestring=item->valuestring;
	ja->valueint=item->valueint;
	ja->valuedouble=item->valuedouble;
	ja->which=item->which;
	ja->key=item->key;
	ja->phead=item->phead;
	ja->pend=item->pend;
	ja->pnext=item->pnext;
	ja->length=item->length;
	/*如果要求深层复制*/
	if(recurse&&(item->type==5||item->type==6)&&item->length)
	{
		JSON* jb=ja;
		int n=item->length;
		for(int i=0;i<n;i++)
		{
			jb->pnext=Duplicate(item,1);
			item=item->pnext;			
			jb=jb->pnext;		
		}
	}
	return ja;
}

JSON *GetItemInJSON(JSON *json, const char *path)   
{
	if (path[0] != '/') {
        printf("Exception: Invalid path format.\n");
        return NULL;
    }
    if (strcmp("/", path) == 0) {
        return json;
    }
	JSON *rtn;
	int site[10]={0}, //保存'/'在path中的位置
		times=0, //'/'出现的次数
		i=0,
		len=strlen(path);
	char *target;
	for(i=0;i++;i<len)
	{	
		if(path[i]=='/')
			site[times++]=i;
	}
	if(times==1){
		strcpy(target,path+1);
		switch (json->type) {
   //         case JSON_ARRAY:  rtn=GetItemInArray(json, atoi(target)); break;
            case JSON_OBJECT: rtn=GetItemInObject(json, target); break;  
        }
	}else{
		char* path2;
		strncpy(target,path+1,(site[i+1]-site[i]-1));
		switch (json->type) {
            case JSON_ARRAY:  rtn=GetItemInArray(json, atoi(target)); break;
            case JSON_OBJECT: rtn=GetItemInObject(json, target); break;  
        }
		strcpy(path2,path+(site[i+1]-site[i]));
		rtn=GetItemInJSON(rtn,path2);
	}
}

int TestSomeFuncs() {
	
	int score = 10;
	
	JSON *root = CreateObject();

	if (root->type != JSON_OBJECT) { 
		score -= 2;
	}
	
	AddItemToObject(root, "name", CreateString("Hello World"));
	JSON *value = GetItemInObject(root, "name");
	if (value->type != JSON_STRING || strcmp(value->valuestring, "Hello World")) {
		score -= 2;
	}
	
	JSON *array = CreateArray();
	AddItemToArray(array, CreateBool(0));
	AddItemToArray(array, CreateNumber(2.3));
	JSON *item = GetItemInArray(array, 1);
	if (item->type != JSON_NUMBER || item->valuedouble != 2.3) {
		score -= 2;
	}
	
	AddItemToObject(root, "array", array);
	/*	
	{
		"name": "Hello Wrold",
		"array": [
			false,
			2.3
		]
	}*/
		
	item = GetItemInJSON(root, "/array/0");
	if (item->type != JSON_FALSE) {
		score -= 2;
	}
/*	
	PrintJSONToFile(root, "test.json");
	if (!IsSame("test.json", "test.json.ans")) {
		score -= 2;
	}	
*/
	return score;
}

int main() {
	printf("Score: %d\n", TestSomeFuncs());
	return 0;
}
