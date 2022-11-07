#include <stdio.h>
#include <Windows.h>
#pragma warning(disable : 4996)
void main()
{
	int filenum = 1;
	char file_root[100] = "\0";
	while (filenum < 7)
	{
		FILE* fp;
		char       buf[1024];
		int i = 0;
		sprintf(file_root, "data\\%d.dat", filenum);
		fp = fopen(file_root, "r");

		if (fp == NULL) printf("파일열기 실패\n");
		else printf("파일열기 성공\n");

		double data[1024][4] = { '\0', };
		char tmp[20] = { '\0' };
		float read_data = 0;
		int mode = 0;
		int line = 0;
		int dat = 0;
		int count = 0;
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			for (int i = 0; i < sizeof(buf); i++)
			{
				if (line > 2) tmp[dat] = buf[i];
				dat++;
				if (buf[i] == ' ')
				{
					data[line][mode] = atof(tmp);
					mode++;
					dat = 0;
				}


				if (buf[i] == NULL)
				{
					data[line][mode] = atof(tmp);
					if (line == 1)
					{
						tmp[0] = buf[i - 4];
						tmp[1] = buf[i - 3];
						tmp[2] = buf[i - 2];
						count = atoi(tmp);
					}
					line++;
					mode = 0;
					dat = 0;
					break;
				}

			}

			read_data = atoi(buf);
		}
		fclose(fp);
		/*
		for (int i = 3; i < 500; i++)
		{
			printf("%lf ", data[i][0]);
			printf("%lf ", data[i][1]);
			printf("%lf\n", data[i][2]);
			//if (buf[i] == 0x20) mode++;
			//if (buf[i] == NULL) break;

		}
		*/
		
		sprintf(file_root, "data\\extract %d.dat",filenum);
		FILE* fop;
		fop = fopen(file_root, "wt");
		fprintf(fop, "count : %d\n", count);
		for (int i = 3; i < count + 3; i++)
		{
			if (((data[i][0] > 347) || (data[i][0] < 13)) && (data[i][1] > 2300 && data[i][1] < 3200))
				fprintf(fop, "%lf %lf\n", data[i][0], data[i][1]);
			//fprintf(fop, "%lf\n", data[i][2]);
		}

		filenum++;
	}
	
}