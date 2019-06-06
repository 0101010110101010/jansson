#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <jansson.h>

#include <assert.h>

int main() {

    char *text = "{ \"name\":\"�»�\", \"age\":30, \"children\":[ \"����\", \"èè\" ] }";

    json_error_t error;

    // json_t���������κ�JSON�ڵ�

    json_t *root = json_loads( text, 0, &error );

    // �����ȡʧ�ܣ��Զ���Ϊ��ָ��

    if ( !root ) {

        printf( "error: on line %d: %s\n", error.line, error.text );

        return 1;

    } else {

        // json_is_*�������ж���������

        // ����JSON����

        assert( json_is_object( root ));

        json_t *name, *age, *children;

        name = json_object_get( root, "name" );

        age = json_object_get( root, "age" );

        printf(  "NAME: %s, AGE: %d\n", json_string_value( name ), json_integer_value( age ));

        children = json_object_get( root, "children" );

        // ����JSON����

        assert( json_is_array( children ));

        int sof = json_array_size( children );

        for ( int i = 0; i != sof; i++ ) {

            json_t *child = json_array_get( children, i );

            fprintf( stdout, "CHILDREN: %s\n", json_string_value( child ));

        }

        // ��С���ü�����������Դ����

        json_decref( root );

    }

    return 0;

}

�������Ǵ�������е����飺

 fileflist = json_object_get(sessionJSON, "flt");//��{����}�л�ȡ��key��Ӧ��ֵ
     iSize = json_array_size(fileflist); 
     if(iSize == 0)
        printf("json file is fail-->iSize = %d\n",iSize);
    jArrayGet = json_array_get(fileflist,0);
   if (json_is_object(jArrayGet))
    {
        valuenew = json_object_get(jArrayGet, "pth");    //[hegs]����KEY���һ��value
        if (json_string_value(valuenew) != NULL)
        {
            strcpy(file_value, json_string_value(valuenew));
        }
    }
