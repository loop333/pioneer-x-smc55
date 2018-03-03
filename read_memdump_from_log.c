#include <stdio.h>
#include <string.h>

int main(void)
{
  FILE *fin;
  FILE *fout;
  char buf[1024];
  char oldbuf[1024];
  int print;
  int begin = 0x60000000;
  int end =   0x61effff0;
  int cur;
  char begin_str[20];
  char end_str[20];
  char cur_str[20];
  char outbuf[16];
  char fname[256];

  sprintf(begin_str, "0x%8x", begin);
  sprintf(end_str, "0x%8x", end);
  printf("%s - %s\n", begin_str, end_str);

  fin = fopen("0x60000000.txt", "rt");
  if (fin == NULL)
   {
     printf("Can't open input file\n");
     return 1;
   }

  sprintf(fname, "%s.bin", begin_str);
  fout = fopen(fname, "wb+");
  if (fout == NULL)
    {
      printf("Can't open output file\n");
      return 1;
    }

  print = 0;
  cur = begin;
  while (1)
   {
     if (fgets(buf, sizeof(buf)-1, fin) == NULL)
       break;

     if (strchr(buf, '\n'))
       *strchr(buf, '\n') = 0;
     if (strchr(buf, '\r'))
       *strchr(buf, '\r') = 0;

     if (strncmp(buf, begin_str, 10) == 0)
       print = 1;
     if (print)
      {
        sprintf(cur_str, "0x%8x", cur);
        if ((strncmp(buf, cur_str, 10) != 0) || (strlen(buf) != 48))
          {
            printf("error %s != %s, %s\n", cur_str, buf, oldbuf);
            printf("strlen=%ld\n", strlen(buf));
            break;
          }
        for (int i=0;i<4;i++)
          for (int j=0;j<4;j++)
            {
              int c;
              sscanf(buf+12+i*9+j*2, "%2x", &c);
              outbuf[i*4+3-j] = c;
            }
        fwrite(outbuf, 16, 1, fout);
        cur += 16;
      }
     if (strncmp(buf, end_str, 10) == 0)
       {
         cur = begin;
         print = 0;
       }

     strcpy(oldbuf, buf);
   }

  fclose(fin);
  fclose(fout);
  return 0;
}
