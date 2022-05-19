#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fp;char b[50]="Line :";
	fp=fopen("test-file.txt","w");
	for(int i=1;i<=1001;i++)
	{
		fprintf(fp,"%s : %d\n","File Number is ",i);
	}
	fclose(fp);
}
