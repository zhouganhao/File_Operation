#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "config.h"
#define LINE_SIZE 1024


/*
功能： 从指定配置文件中读取关键字所对应的值 格式 key = value ;

path: 配置文件目录位置及文件名 key：关键字  value: 关键字对应的值
*/
int Read_Config_Value(char* path, char *key, char *value)
{
	char buf[LINE_SIZE];
	int success = 0;
	//打开文件	
	FILE *file_fd = fopen(path,"r");
	if(file_fd ==NULL)
	{
		printf("open file error\n");
		return -1;
	}
	//读取文件 搜索关键字 
	while(1)
	{
		char *temp = fgets(buf,LINE_SIZE,file_fd);
		if(temp == NULL)
		{
			//perror("fgets:");
		}

		if(feof(file_fd)) //文件结束：返回非0值，文件未结束，返回0值
		{
			break;
		}

		char name[LINE_SIZE] = "hello";
		char name_value[LINE_SIZE] = {0};

		sscanf(buf,"%[^=]=%[^;]",name,name_value);

		int ret = sscanf(name,"%s",name);
		if(ret != 1) 
		{
			continue;
		}

		ret = sscanf(name_value,"%s",name_value);	
		if(ret != 1)
			continue;
		

		if(strcmp(key,name) == 0)
		{
			//printf("%s ",buf);
			sscanf(name_value,"%s",value);
			success = 1;
		}
	}

	fclose(file_fd);

	return (success == 0)? -1 : 0;
}

int Write_Config_Value(char* path, char *key, char *value)
{
	char buf[LINE_SIZE];
	//int write_position = 0;

	//打开文件	
	FILE *file_fd = fopen(path,"r");
	FILE *copy_fd = fopen("./copy_config.ini","w+"); //新修改的配置文件
	if( (file_fd ==NULL) || (copy_fd == NULL) )
	{
		printf("open file error\n");
		return -1;
	}
	//读取文件 搜索关键字 
	while(1)
	{
		char *temp = fgets(buf,LINE_SIZE,file_fd);	//获取一行
		if(temp == NULL)
		{
			//perror("fgets:");
		}

		if(feof(file_fd)) //文件结束：返回非0值，文件未结束，返回0值
		{
			break;
		}
		//write_position = ftell(file_fd);
		//printf("%s %s",key,buf);
		char name[LINE_SIZE] = {0};
		char name_value[LINE_SIZE] = {0};

		sscanf(buf,"%[^=]=%s",name,name_value);
		sscanf(name,"%s",name);


		if(strcmp(key,name) == 0)
		{
			memset(buf,0,LINE_SIZE);
		//	rewind(file_fd);
		//	fseek(file_fd,write_position,SEEK_CUR);
			sprintf(buf,"%s = %s ;\n",key, value);
		}

		fputs(buf,copy_fd);
	}

	fclose(file_fd);
	fclose(copy_fd);

	char cmd[100]={0};
	sprintf(cmd,"cp %s %s","./copy_config.ini",path);
	system(cmd);
	return 0;
}


/*
配置初始化
从对应目录的配置文件读取配置并且相应赋值
若配置文件中没有找到对应的关键字，则使用默认值
*/
void config_ini(char *path)
{
	char value[LINE_SIZE] = {0};

	if(Read_Config_Value(path, "name", value) < 0)
	{
		printf("name not found ori = %s\n",name);
	}else
	{
		name = strdup(value);	//字符串赋值 strdup调用了malloc，用完需要调用free;
		printf("name = %s\n",name);
	}

	if(Read_Config_Value(path, "age", value) < 0)
	{
		printf("age not found ori=%d\n",age);
	}else
	{
		age = atoi(value);	//字符串转整形
		printf("age = %d\n",age);
	}


	if(Read_Config_Value(path, "hight", value) < 0)
	{
		printf("hight not found ori=%.2f\n",hight);
	}else
	{
		hight = atof(value);	//字符串转浮点型
		printf("higt = %.2f\n",hight);
	}
	//printf("config.ini\n");
}

