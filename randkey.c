#include <stdio.h>
#include <stdlib.h>
#include <time.h>
main()
{
      int length=0, if_=1;
      char webname[20],account[20];
      puts("enter the web:");
      scanf("%s",webname);
      puts("enter the account:");
      scanf("%s",account);
      puts("enter your keyword's length:");
      scanf("%d", &length);
      puts("if !@#$%&*(0:without):");
      scanf("%d", &if_);
      char *key;
      srand(time(NULL));
      key=(char*)malloc(sizeof(char)*(length+1));
      
      int if_A=0, if_a=0, if_1=0, if_i=0;
      while(!(if_A && if_a && if_1 && if_i))
      {
          if_A=0; if_a=0; if_1=0; if_i=0;
          int i=0;
          for(i=0;i<length;i++)
            {
             int temp=rand()%128;
             if((temp<58&&temp>47)|| (temp<='Z'&&temp>='A')|| (temp<='z'&&temp>='a') )
               key[i]=(char)temp;
             else if( if_ && (temp==21||(temp<=38&&temp>=35)||temp==64))/*!#$%&@*/
               key[i]=(char)temp;
             else
               i--;
            }
          key[i]='\0';
          printf("%s\n",key);
          
          for(i=0;i<length;i++)
            {
             char temp=key[i];
             if((temp<58&&temp>47)) if_1=1;
             else if((temp<='Z'&&temp>='A')) if_A=1;
             else if((temp<='z'&&temp>='a')) if_a=1;
             if(!if_) if_i=1;
             else if((temp==21||(temp<=38&&temp>=35)||temp==64)) if_i=1;
            }
          
      }
      puts("-----------------------------------------------");
      printf("your keyword of\n Account: %s \n     for: %s\n      is: %s\n",account,webname,key);
      puts("-----------------------------------------------");
      system("pause");
}
