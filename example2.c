#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <jansson.h>

#include <assert.h>

int main() {

    char *text = "{ \"name\":\"德华\", \"age\":30, \"children\":[ \"狗狗\", \"猫猫\" ] }";

    json_error_t error;

    // json_t用于引用任何JSON节点

    json_t *root = json_loads( text, 0, &error );

    // 如果读取失败，自动置为空指针

    if ( !root ) {

        printf( "error: on line %d: %s\n", error.line, error.text );

        return 1;

    } else {

        // json_is_*宏用于判断数据类型

        // 处理JSON对象

        assert( json_is_object( root ));

        json_t *name, *age, *children;

        name = json_object_get( root, "name" );

        age = json_object_get( root, "age" );

        printf(  "NAME: %s, AGE: %d\n", json_string_value( name ), json_integer_value( age ));

        children = json_object_get( root, "children" );

        // 处理JSON数组

        assert( json_is_array( children ));

        int sof = json_array_size( children );

        for ( int i = 0; i != sof; i++ ) {

            json_t *child = json_array_get( children, i );

            fprintf( stdout, "CHILDREN: %s\n", json_string_value( child ));

        }

        // 减小引用计数，导致资源回收

        json_decref( root );

    }

    return 0;

}

另外这是处理对象中的数组：

 fileflist = json_object_get(sessionJSON, "flt");//从{对象}中获取与key对应的值
     iSize = json_array_size(fileflist); 
     if(iSize == 0)
        printf("json file is fail-->iSize = %d\n",iSize);
    jArrayGet = json_array_get(fileflist,0);
   if (json_is_object(jArrayGet))
    {
        valuenew = json_object_get(jArrayGet, "pth");    //[hegs]根据KEY获得一个value
        if (json_string_value(valuenew) != NULL)
        {
            strcpy(file_value, json_string_value(valuenew));
        }
    }
