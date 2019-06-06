#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <jansson.h>

#include <assert.h>

#define FILE_PATH         "./temp.txt"
#define MAX_NUM            5

typedef struct _JSON_ITEM_INFO
{
    json_t* string;
    json_t* value;
}JSON_ITEM_INFO;

void save_info_to_file()
{
   json_t* root = NULL;
   json_t* item_1 = NULL;
   json_t* item_2 = NULL;
   json_t* item_3 = NULL;
   json_t* array = NULL;
    
   char* s_repon = NULL;
   
   root = json_object();
   item_1 = json_object();
   item_2 = json_object();
   item_3 = json_object(); 
   array = json_array();
  
   json_object_set_new(item_1,"name",json_string("xiaopeng"));
   json_object_set_new(item_1,"age",json_integer(12));
   json_array_append_new(array,item_1);

   json_object_set_new(item_2,"name",json_string("xiaoming"));
   json_object_set_new(item_2,"age",json_integer(8));
   json_array_append_new(array,item_2);

   json_object_set_new(item_3,"name",json_string("xiaohong"));
   json_object_set_new(item_3,"age",json_integer(22));
   json_array_append_new(array,item_3);
   
   json_object_set_new(root,"root",array);

   json_dump_file(root, FILE_PATH,JSON_PRESERVE_ORDER);

   s_repon = json_dumps(root,JSON_INDENT(0));

   printf("s_repon = %s \n",s_repon);
   free(s_repon);

   printf("size = %d \n", (int)json_array_size(array));
   
   if(root)
   {
      json_delete(root);
   }
   if(array)
   {
      json_delete(array);
   }
}

void get_file_info()
{
   int i = 0;
    
   json_t* root = NULL;
   json_t* array = NULL;
   json_error_t error;
   char* s_repon = NULL;
   
   json_t* add_item_1 = NULL;
   char* s_get_add_item = NULL;
   
   json_t* rec_table[MAX_NUM] = {0};
   
   JSON_ITEM_INFO person[MAX_NUM];
   memset(person,0,sizeof(person));
   
   //get the info from file;
   root = json_load_file(FILE_PATH, 0, &error);
   if(!json_is_object(root))
   {
        printf("%s,%d\n",__FILE__,__LINE__);
   }
   s_repon = json_dumps(root,JSON_INDENT(0));
   printf("s_repon = %s \n",s_repon);
   free(s_repon);

   array = json_object_get(root,"root");
   if(!json_is_array(array))
   {
        printf("%s,%d\n",__FILE__,__LINE__);
   }
   
   for(i = 0; i < MAX_NUM ;i++)
   {
       rec_table[i] = json_array_get(array,i);
       if(!json_is_object(rec_table[i]))
       {
            printf("%s,%d\n",__FILE__,__LINE__);
       }
       person[i].string = json_object_get(rec_table[i],"name");
       printf("person[%d].string = %s \n",i,json_string_value(person[i].string));
       person[i].value = json_object_get(rec_table[i],"age");
       printf("person[%d].value = %d \n",i,(int)json_integer_value(person[i].value));
   }
   
    //add the new item;
    add_item_1 = json_object(); 
    json_object_set_new(add_item_1,"name",json_string("zhangsan"));
    json_object_set_new(add_item_1,"age",json_integer(30));
    
   if(json_array_size(array) >= MAX_NUM)
   {
        //remove the top item;
        json_array_remove(array,0);
        
   }    
    json_array_append_new(array,add_item_1);

    //write the new array to the file;
    json_dump_file(root, FILE_PATH,JSON_PRESERVE_ORDER);

    //dump the date and print
    s_get_add_item = json_dumps(root,JSON_INDENT(0));

    printf("s_get_add_item = %s \n",s_get_add_item);
    free(s_get_add_item);

}

int main()
{
    //gcc source.c -ljansson
    save_info_to_file(); //这里将数据保存在文件 FILE_PATH 里；
    get_file_info();     // 这里将文件 FILE_PATH 数据读取出来；

    return 0;
}
