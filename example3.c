int analysis_json_rstr(char * pcJsonInfo)
{
    int i = 0;
    int j = 0;
     
    json_t * pJsonTaskArray = NULL;
    json_t * pJsonArrayNode = NULL;
    json_t * pJsonArray = NULL;
    json_t * pJsonValue;
    json_error_t error;

    uint32 ulArrayNum;

    syslog( "json info [%s]\n",pcJsonInfo);

    pJsonTaskArray = json_loads(pcJsonInfo,0,&error);/* 加载json信息 */
    if(!json_is_array(pJsonTaskArray))
    {
        syslog("json info  is not array \n");
        return -1;
    }

    ulArrayNum = json_array_size(pJsonTaskArray); /* 获取json信息的数量 */

    /* 依次处理每个json信息 */
    for(i = 0; i < ulArrayNum ;i++)
    {
        int arrayNum;

        pJsonArrayNode = json_array_get(pJsonTaskArray,i); /* 获取一个具体的过滤信息 */
        if(!json_is_object(pJsonArrayNode))
        {
            syslog("json info is not object \n");
            return -2;
        }

        pJsonValue= json_object_get(pJsonArrayNode,"id"); /* 解析每个json的Id字段 */

        strcmp((const char *)(JsonId) , sizeof(JsonId), 
                 (const char *)json_string_value(pJsonValue), & indicator);
        json_decref(pJsonValue);

        /* 给 key1 赋值 */
        pJsonValue= json_object_get(pJsonArrayNode,"key1");
        key1 = atoi((char *)json_string_value(pJsonValue));
        json_decref(pJsonValue);

        /* 解析json数组 */
        pJsonArray= json_object_get(pJsonArrayNode,"array");
        arrayNum = json_array_size(pJsonArray);
        for(j = 0 ; j < arrayNum ; j++)
        {
            array[j] = strtoll(json_string_value(json_array_get(pJsonArray,j)),NULL,16); 
        }
        json_decref(pJsonArray);


        /* 解析key2 */
        pJsonValue= json_object_get(pJsonArrayNode,"key2");
        key2 = json_integer_value(pJsonValue) ;
        json_decref(pJsonValue);

        json_decref(pJsonArrayNode);
    }

    json_decref(pJsonTaskArray);

    return 0;
}

