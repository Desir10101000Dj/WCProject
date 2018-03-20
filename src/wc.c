#include <stdio.h>
#include <unistd.h>
#include <string.h>


int l = 0;
int w = 0;
int c = 0;
int o = 0;
int lineCnt = 0;  //行数
int wordCnt = 0;  //单词数
int charCnt = 0;   //字符数

int countFile(char *filename){
    FILE *fp;  // 指向文件的指针
    char buffer[1003];  //缓冲区，存储读取到的每行的内容
    int bufferLen;  // 缓冲区中实际存储的内容的长度
    int i;  // 当前读到缓冲区的第i个字符
    char c;  // 读取到的字符
    int isLastBlank = 0;  // 上个字符是否是空格
    int charNum = 0;  // 当前行的字符数
    int wordNum = 0; // 当前行的单词数
    if( (fp=fopen(filename, "rb")) == NULL ){
        perror(filename);
        return -1;
    }
    //printf("line   words  chars\n");
    // 每次读取一行数据，保存到buffer，每行最多只能有1000个字符
    while(fgets(buffer, 1003, fp) != NULL){
        bufferLen = strlen(buffer);
        // 遍历缓冲区的内容
        for(i=0; i<bufferLen; i++){
            c = buffer[i];
            if( c==' ' || c=='\t'){  // 遇到空格
                !isLastBlank && wordNum++;  // 如果上个字符不是空格，那么单词数加1
                isLastBlank = 1;
            }else if(c!='\n'&&c!='\r'){  // 忽略换行符
                charNum++;  // 如果既不是换行符也不是空格，字符数加1
                isLastBlank = 0;
            }
        }
        !isLastBlank && wordNum++;  // 如果最后一个字符不是空格，那么单词数加1
        isLastBlank = 1;  // 每次换行重置为1
        // 一行结束，计算总字符数、总单词数、总行数
        lineCnt++;  // 总行数
        charCnt += charNum;  // 总字符数
        wordCnt += wordNum;  // 总单词数
        // 置零，重新统计下一行
        charNum = 0;
        wordNum = 0;
    }
    fclose(fp);
    return 1;
}

int writeOutput(char *filename)
{
    FILE *fpWrite = fopen(filename,"w");
    if (fpWrite == NULL)
        return -1;
    if (l)
    {
        fprintf(fpWrite, "Lines: %d\n", lineCnt);
    }
    if (w)
    {
        fprintf(fpWrite, "Words: %d\n", wordCnt);
    }
    if (c)
    {
        fprintf(fpWrite, "Chars: %d\n", charCnt);
    }
    fclose(fpWrite);
}


int main(int argc,char *argv[])
{

    //opterr = 0;  //使getopt不行stderr输出错误信息  
    int opt=0;
    char inputFileName[50];
    char outputFileName[50];


    while((opt=getopt(argc,argv,"a:l:w:c:o:")) != -1)
    {
        switch(opt)
        {
            case 'a':
                l = w = c = 1;
                strcpy(inputFileName,optarg);
                break;
            case 'l': 
                l = 1;
                strcpy(inputFileName,optarg);
                break;  
            case 'w': 
                w = 1;
                strcpy(inputFileName,optarg); 
                break;  
            case 'c': 
                c = 1;
                strcpy(inputFileName,optarg);
                break;
            case 'o':
                o = 1;
                strcpy(outputFileName,optarg);  
        }
    }
    countFile(inputFileName);
    if (o)
        writeOutput(outputFileName);
    else
    {
        if (l)
        {
            printf("Lines: %d\n", lineCnt);
        }
        if (w)
        {
            printf("Words: %d\n", wordCnt);
        }
        if (c)
        {
            printf("Chars: %d\n", charCnt);
        }   
    }
    return 0;
}