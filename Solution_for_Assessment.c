#include<stdio.h>
void size_file(char *file_name);
void count_lines(char *file_name);
void split_base_size(char *file_name, int max);
void split_base_lines(char *file_name, size_t max_lines);

int main(int argc,char *argv[])
{
    size_file(argv[1]);
    count_lines(argv[1]);
    split_base_lines(argv[1],100);
    
    printf("\n Enter 1 To Split File Based on Size   ");
    printf("\n Enter 2 To Split File Based on Lines : ");
    int a=0;scanf("%d",&a);
    if(a==1)
    {
	    printf("\n How Much kilobytes Each Files must be splitted based on ? \n ");
	    printf("Example : Enter 2kB as 2  \n Enter Now :");
	    float b=0.0;scanf("%f",&b);
	    split_base_size(argv[1],b);
    }
    else if(a==2)
    {
        printf("\n How Much Lines must Each file consist of to Split a File  :  ");
        int max=0;scanf("%d",&max);
        split_base_lines(argv[1],max+8);
    }
    printf("\nNow You can use ls command to view the text files in terminal\n");
}

void size_file(char *file_name)
{
	FILE *fp=fopen(file_name,"r");
	fseek(fp,0L,SEEK_END);
	long double result=ftell(fp);
	//printf("Size of Bytes %Lf",result);
	float a=result/1024;
	printf(" \n Size of File in  Kilo Bytes : %.2fkB \n",a);
	fclose(fp);
}
void count_lines(char *file_name)
{
	FILE *fp;int count=0;char c;
	fp=fopen(file_name,"r");
	for(c=getc(fp);c!=EOF;c=getc(fp))
	{
		if(c=='\n')
		{
			count++;
		}
	}
	printf("\nThe Number of Lines in the File is %d\n",count);
	fclose(fp);
}
void split_base_size(char *file_name, int max)
{
	FILE *file_input,*file_output;max=max*1024;
	char buffer[(1024*16)];size_t size,read,written;
	file_input=fopen(file_name,"rb");
	int result=0;
	while(!feof(file_input))
	{
		sprintf(buffer,"%04d-%s",result,file_name);
		file_output=fopen(buffer,"wb");
		size=0;

		read=sizeof(buffer);
		if((size+read)>max)
		{
			read=max-size;
		}
		read=fread(buffer,1,read,file_input);
		written=fwrite(buffer,1,read,file_output);
		size +=written;

		if(size>=max)
		{
			fclose(file_output);
			file_output=NULL;
			result++;
		}
	}
	fclose(file_input);
}
void split_base_lines(char *file_name, size_t max_lines)
{
 FILE *fp;int count=0;char c;
        fp=fopen(file_name,"r");
        for(c=getc(fp);c!=EOF;c=getc(fp))
        {
                if(c=='\n')
                {
			if(count==max_lines)
			{
			    fseek(fp,0,count);
		           // printf("\n Line Number is %d \n",count);
			    long int result=ftell(fp);
			    long int a=result/1024;
			    //printf("\n Line in Kilo Bytes %ld \n",a);
			    split_base_size(file_name,a);
			    break; 
		            	    
			}
                        count++;
                }
        }
        //printf("\nThe Number of Lines in the File is %d\n",count);
        fclose(fp);
}

