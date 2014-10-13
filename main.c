 //ŒÆËãÆ÷£¬²»ÍêÈ«°æ£¬ŽýžÄœø¡£ÁœÎ»ÊýŒÆËãÕý³££¬µ«ÊÇÈýÎ»Êý»áŽæÔÚÒ»Ð©bug,ŽýœâŸö
//ŒüÅÌË³ÐòÎª AC£¬1,2,3,4,5,6,7,8,9,0£¬/,*,+,-,=;
//»¶Ó­ÓïÎªhello friend
//¿ÉÒÔÏÔÊŸÎÂ¶È£¬°ŽÒ»ŽÎACŒüžüÐÂÒ»ŽÎ




#include<reg51.h>
#include<intrins.h>

#define uint unsigned int 
#define uchar unsigned char


#define LCDIO P0
#define KEYBOARD P1

sbit RS=P2^0;
sbit RW=P2^1;	
sbit E=P2^2;
sbit BF=P0^7;
long int key=16;
uchar flag,tltemp,i,j;
long int key1,xian,count1,count2,shi,count=0;//×îºóÏÔÊŸœá¹ûÊÇÐèÒªµÄÒ»Ð©±äÁ¿

	long int result;
unsigned char code key_code[]={
              0xee,0xde,0xbe,0x7e,0xed,0xdd,0xbd,0x7d, 
              0xeb,0xdb,0xbb,0x7b,0xe7,0xd7,0xb7,0x77};
code uchar mayuan[]={'0','1','2','3','4','5','6','7','8','9','0','/','*','-','+','='};
uchar code Error[]={"E"};
unsigned char code digit[11]={"0123456789-"};     //¶šÒå×Ö·ûÊý×éÏÔÊŸÊý×Ö
unsigned char code User[]={0x10,0x06,0x09,0x08,0x08,0x09,0x06,0x00};//×Ô¶šÒå×Ö·û¡æ */ 
//ÑÓÊ±º¯Êý
void delay1ms()
{
   		unsigned char i,j;	
	 	for(i=0;i<10;i++)
	  	for(j=0;j<33;j++)
	   ;		 
 }
void delay(unsigned int n)
 {
   	unsigned int i;
	for(i=0;i<n;i++)
	delay1ms();
 }

//ÒÔÏÂÊÇLCDÏÔÊŸËùÐèÒªµÄÒ»Ð©º¯Êý£¬°üÀš³õÊŒ»¯ÐŽÖžÁîºÍÊýŸÝ
 bit BusyTest(void)
  {
    	bit result;
		RS=0;       //žùŸÝ¹æ¶š£¬RSÎªµÍµçÆœ£¬RWÎªžßµçÆœÊ±£¬¿ÉÒÔ¶Á×ŽÌ¬
    	RW=1;
    	E=1;        //E=1£¬²ÅÔÊÐí¶ÁÐŽ
    	_nop_();   //¿Õ²Ù×÷
    	_nop_();
    	_nop_(); 
   		_nop_();   //¿Õ²Ù×÷ËÄžö»úÆ÷ÖÜÆÚ£¬žøÓ²Œþ·ŽÓŠÊ±Œä	
    	result=BF;  //œ«ÃŠÂµ±êÖŸµçÆœž³žøresult
		E=0;
    	return result;
  }
 void Write_com (unsigned char dictate)
{   
    while(BusyTest()==1); //Èç¹ûÃŠŸÍµÈŽý
	 RS=0;                  //žùŸÝ¹æ¶š£¬RSºÍR/WÍ¬Ê±ÎªµÍµçÆœÊ±£¬¿ÉÒÔÐŽÈëÖžÁî
	 RW=0;   
	 E=0;                   //EÖÃµÍµçÆœ(ÐŽÖžÁîÊ±£¬
                             // ŸÍÊÇÈÃEŽÓ0µœ1·¢ÉúÕýÌø±ä£¬ËùÒÔÓŠÏÈÖÃ"0"
	 _nop_();
	 _nop_();             //¿Õ²Ù×÷Áœžö»úÆ÷ÖÜÆÚ£¬žøÓ²Œþ·ŽÓŠÊ±Œä
	 P0=dictate;            //œ«ÊýŸÝËÍÈëP0¿Ú£¬ŒŽÐŽÈëÖžÁî»òµØÖ·
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();               //¿Õ²Ù×÷ËÄžö»úÆ÷ÖÜÆÚ£¬žøÓ²Œþ·ŽÓŠÊ±Œä
	 E=1;                   //EÖÃžßµçÆœ
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();               //¿Õ²Ù×÷ËÄžö»úÆ÷ÖÜÆÚ£¬žøÓ²Œþ·ŽÓŠÊ±Œä
	  E=0;                  //µ±EÓÉžßµçÆœÌø±ä³ÉµÍµçÆœÊ±£¬ÒºŸ§Ä£¿é¿ªÊŒÖŽÐÐÃüÁî
 }
 void WriteAddress(unsigned char x)
 {
     Write_com(x|0x80); //ÏÔÊŸÎ»ÖÃµÄÈ·¶š·œ·š¹æ¶šÎª"80H+µØÖ·Âëx"	
 }
  void WriteData(unsigned char y)
 {
    while(BusyTest()==1);  
	  RS=1;           //RSÎªžßµçÆœ£¬RWÎªµÍµçÆœÊ±£¬¿ÉÒÔÐŽÈëÊýŸÝ
	  RW=0;
	  E=0;            //EÖÃµÍµçÆœ(ÐŽÖžÁîÊ±£¬£¬
                       // ŸÍÊÇÈÃEŽÓ0µœ1·¢ÉúÕýÌø±ä£¬ËùÒÔÓŠÏÈÖÃ"0"
	  P0=y;           //œ«ÊýŸÝËÍÈëP0¿Ú£¬ŒŽœ«ÊýŸÝÐŽÈëÒºŸ§Ä£¿é
	  _nop_();
	  _nop_();
 	  _nop_();
    	  _nop_();       //¿Õ²Ù×÷ËÄžö»úÆ÷ÖÜÆÚ£¬žøÓ²Œþ·ŽÓŠÊ±Œä
	  E=1;          //EÖÃžßµçÆœ
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();        //¿Õ²Ù×÷ËÄžö»úÆ÷ÖÜÆÚ£¬žøÓ²Œþ·ŽÓŠÊ±Œä
	  E=0;            //µ±EÓÉžßµçÆœÌø±ä³ÉµÍµçÆœÊ±£¬ÒºŸ§Ä£¿é¿ªÊŒÖŽÐÐÃüÁî
 }
//*****************************************************
void LcdInt(void)
{
   	delay(15);             //ÑÓÊ±15ms£¬Ê×ŽÎÐŽÖžÁîÊ±ÓŠžøLCDÒ»¶ÎœÏ³€µÄ·ŽÓŠÊ±Œä
   	Write_com(0x38);  //ÏÔÊŸÄ£ÊœÉèÖÃ£º16¡Á2ÏÔÊŸ£¬5¡Á7µãÕó£¬8Î»ÊýŸÝœÓ¿Ú
	delay(5);   //ÑÓÊ±5ms¡¡
	Write_com(0x38);
	delay(5);
	Write_com(0x38); //3ŽÎÐŽ ÉèÖÃÄ£Êœ
	delay(5);
	Write_com(0x0F);  //ÏÔÊŸÄ£ÊœÉèÖÃ£ºÏÔÊŸ¿ª£¬ÓÐ¹â±ê£¬¹â±êÉÁËž
	delay(5);
	Write_com(0x06);  //ÏÔÊŸÄ£ÊœÉèÖÃ£º¹â±êÓÒÒÆ£¬×Ö·û²»ÒÆ
	delay(5);											  
	Write_com(0x01);  //ÇåÆÁÄ»ÖžÁî£¬œ«ÒÔÇ°µÄÏÔÊŸÄÚÈÝÇå³ý
	delay(5);
 }

//ÒÔÏÂÎªŒüÅÌÉšÃèº¯Êý
 uchar  keyscan()
{
   uchar  scan1,scan2,keycode,j;

   P1=0xf0;
   scan1=P1;
   if((scan1&0xf0)!=0xf0)           //ÅÐŒüÊÇ·ñ°ŽÏÂ
   {
     delay(100);                   //ÑÓÊ±20ms
     scan1=P1;
     if((scan1&0xf0)!=0xf0)         //¶þŽÎÅÐŒüÊÇ·ñ°ŽÏÂ
     {
        P1=0x0f;  //Ïß·Ž×ª·šµÄºËÐÄ
        scan2=P1;
        keycode=scan1|scan2;         //×éºÏ³ÉŒü±àÂë

        for(j=0;j<=15;j++)
        {
           if(keycode== key_code[j])  //²é±íµÃŒüÖµ
           {
              key=j;
              return(key);
           }
        } 
     }
   }
   else  
   P1=0xff; //P1¿ÚÐŽ1 ÊäÈë×ŽÌ¬
   return (16);//"-"
}



//18B20ÎÂ¶È¿ØÖÆº¯Êý
sbit DQ=P3^3;
uchar time;
bit Init_DS18B20(void)	
{
 bit flag;         //Ž¢ŽæDS18B20ÊÇ·ñŽæÔÚµÄ±êÖŸ£¬flag=0£¬±íÊŸŽæÔÚ£»flag=1£¬±íÊŸ²»ŽæÔÚ
 DQ = 1;           //ÏÈœ«ÊýŸÝÏßÀ­žß
 for(time=0;time<2;time++) //ÂÔÎ¢ÑÓÊ±ÔŒ6Î¢Ãë
     ;
 DQ = 0;           //ÔÙœ«ÊýŸÝÏßŽÓžßÀ­µÍ£¬ÒªÇó±£³Ö480~960us
 for(time=0;time<200;time++)  //ÂÔÎ¢ÑÓÊ±ÔŒ600Î¢Ãë
     ;         //ÒÔÏòDS18B20·¢³öÒ»³ÖÐø480~960usµÄµÍµçÆœžŽÎ»Âö³å 
 DQ = 1;           //ÊÍ·ÅÊýŸÝÏß£šœ«ÊýŸÝÏßÀ­žß£© 
  for(time=0;time<10;time++)
     ;  //ÑÓÊ±ÔŒ30us£šÊÍ·Å×ÜÏßºóÐèµÈŽý15~60usÈÃDS18B20Êä³öŽæÔÚÂö³å£©
 flag=DQ;          //ÈÃµ¥Æ¬»úŒì²âÊÇ·ñÊä³öÁËŽæÔÚÂö³å£šDQ=0±íÊŸŽæÔÚ£©      
 for(time=0;time<200;time++)  //ÑÓÊ±×ã¹»³€Ê±Œä£¬µÈŽýŽæÔÚÂö³åÊä³öÍê±Ï
      ;
 return (flag);    //·µ»ØŒì²â³É¹Š±êÖŸ
}


unsigned char ReadOneChar(void)
 {
		unsigned char i=0;	
		unsigned char dat;  //Ž¢Žæ¶Á³öµÄÒ»žö×ÖœÚÊýŸÝ
		for (i=0;i<8;i++)
		 {
		   
		   DQ =1;       // ÏÈœ«ÊýŸÝÏßÀ­žß
		   _nop_();	    //µÈŽýÒ»žö»úÆ÷ÖÜÆÚ	 
		   DQ = 0;      //µ¥Æ¬»úŽÓDS18B20¶ÁÊéŸÝÊ±,œ«ÊýŸÝÏßŽÓžßÀ­µÍŒŽÆô¶¯¶ÁÊ±Ðò
		   _nop_();     //µÈŽýÒ»žö»úÆ÷ÖÜÆÚ		   
		   DQ = 1;     //œ«ÊýŸÝÏß"ÈËÎª"À­žß,Îªµ¥Æ¬»úŒì²âDS18B20µÄÊä³öµçÆœ×÷×Œ±ž
		   for(time=0;time<2;time++)
             ;      //ÑÓÊ±ÔŒ6us£¬Ê¹Ö÷»úÔÚ15usÄÚ²ÉÑù
			 	dat>>=1;
		   if(DQ==1)
		      dat|=0x80;  //Èç¹û¶ÁµœµÄÊýŸÝÊÇ1£¬Ôòœ«1ŽæÈëdat
			else
				dat|=0x00;//Èç¹û¶ÁµœµÄÊýŸÝÊÇ0£¬Ôòœ«0ŽæÈëdat
		     //œ«µ¥Æ¬»úŒì²âµœµÄµçÆœÐÅºÅDQŽæÈër[i]	
		   for(time=0;time<8;time++)
		      	;              //ÑÓÊ±3us,Áœžö¶ÁÊ±ÐòÖ®Œä±ØÐëÓÐŽóÓÚ1usµÄ»ÖžŽÆÚ	
	    }	                    
	 return(dat);    //·µ»Ø¶Á³öµÄÊ®ÁùœøÖÆÊýŸÝ
}
/*****************************************************
º¯Êý¹ŠÄÜ£ºÏòDS18B20ÐŽÈëÒ»žö×ÖœÚÊýŸÝ
Èë¿Ú²ÎÊý£ºdat
***************************************************/  
WriteOneChar(unsigned char dat)
{
	unsigned char i=0;
	for (i=0; i<8; i++)
		 {
		  DQ =1;         // ÏÈœ«ÊýŸÝÏßÀ­žß
		  _nop_();	     //µÈŽýÒ»žö»úÆ÷ÖÜÆÚ	 
		  DQ=0;          //œ«ÊýŸÝÏßŽÓžßÀ­µÍÊ±ŒŽÆô¶¯ÐŽÊ±Ðò       
		  DQ=dat&0x01;   //ÀûÓÃÓëÔËËãÈ¡³öÒªÐŽµÄÄ³Î»¶þœøÖÆÊýŸÝ,
                       //²¢œ«ÆäËÍµœÊýŸÝÏßÉÏµÈŽýDS18B20²ÉÑù	
		 for(time=0;time<10;time++)	
		     ;//ÑÓÊ±ÔŒ30us£¬DS18B20ÔÚÀ­µÍºóµÄÔŒ15~60usÆÚŒäŽÓÊýŸÝÏßÉÏ²ÉÑù
		  DQ=1;          //ÊÍ·ÅÊýŸÝÏß		    
		  for(time=0;time<1;time++)
			  ;//ÑÓÊ±3us,ÁœžöÐŽÊ±ÐòŒäÖÁÉÙÐèÒª1usµÄ»ÖžŽÆÚ
		  dat>>=1;       //œ«datÖÐµÄž÷¶þœøÖÆÎ»ÊýŸÝÓÒÒÆ1Î»
		 }
	  for(time=0;time<4;time++)
	              ; //ÉÔ×÷ÑÓÊ±,žøÓ²ŒþÒ»µã·ŽÓŠÊ±Œä
}

/*****************************************************
º¯Êý¹ŠÄÜ£º×öºÃ¶ÁÎÂ¶ÈµÄ×Œ±ž
***************************************************/ 
void ReadyReadTemp(void)
{
      Init_DS18B20();     //œ«DS18B20³õÊŒ»¯
		WriteOneChar(0xCC); // Ìø¹ý¶ÁÐòºÅÁÐºÅµÄ²Ù×÷
		WriteOneChar(0x44); // Æô¶¯ÎÂ¶È×ª»»	  
	      delay(200); //×ª»»Ò»ŽÎÐèÒªÑÓÊ±Ò»¶ÎÊ±Œä 
	
		Init_DS18B20();     //œ«DS18B20³õÊŒ»¯
		WriteOneChar(0xCC); //Ìø¹ý¶ÁÐòºÅÁÐºÅµÄ²Ù×÷
		WriteOneChar(0xBE); //¶ÁÈ¡ÎÂ¶ÈŒÄŽæÆ÷,Ç°Áœžö·Ö±ðÊÇÎÂ¶ÈµÄµÍÎ»ºÍžßÎ»	
		}

void display_temp1(unsigned char x)
{
 unsigned char j,k,l;     //j,k,l·Ö±ðŽ¢ŽæÎÂ¶ÈµÄ°ÙÎ»¡¢Ê®Î»ºÍžöÎ»
	j=x/100;              //È¡°ÙÎ»
	k=(x%100)/10;    //È¡Ê®Î»
	l=x%10;             //È¡žöÎ»  
	WriteAddress(0x40);    //ÐŽÏÔÊŸµØÖ·,œ«ÔÚµÚ2ÐÐµÚ7ÁÐ¿ªÊŒÏÔÊŸ
	if(flag==1)				//žºÎÂ¶ÈÊ± ÏÔÊŸ¡°¡ª¡±
	{
	WriteData(digit[10]);    //œ«°ÙÎ»Êý×ÖµÄ×Ö·û³£Á¿ÐŽÈëLCD
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              	}
	else{
	WriteData(digit[j]);    //œ«Ê®Î»Êý×ÖµÄ×Ö·û³£Á¿ÐŽÈëLCD
	}
	WriteData(digit[k]);    //œ«Ê®Î»Êý×ÖµÄ×Ö·û³£Á¿ÐŽÈëLCD
	WriteData(digit[l]);    //œ«žöÎ»Êý×ÖµÄ×Ö·û³£Á¿ÐŽÈëLCD
	delay(50);         //ÑÓÊ±1msžøÓ²ŒþÒ»µã·ŽÓŠÊ±Œä     
	
	}

void wendu(){
unsigned char TL;     //Ž¢ŽæÔÝŽæÆ÷µÄÎÂ¶ÈµÍÎ»
     unsigned char TH;    //Ž¢ŽæÔÝŽæÆ÷µÄÎÂ¶ÈžßÎ»
     unsigned char TN;      //Ž¢ŽæÎÂ¶ÈµÄÕûÊý²¿·Ö
	 flag=0;
		ReadyReadTemp();     //¶ÁÎÂ¶È×Œ±ž

	    TL=ReadOneChar();    //ÏÈ¶ÁµÄÊÇÎÂ¶ÈÖµµÍÎ»
		TH=ReadOneChar();    //œÓ×Å¶ÁµÄÊÇÎÂ¶ÈÖµžßÎ»
		
		if((TH&0xf8)!=0x00)//ÅÐ¶ÏžßÎåÎ» µÃµœÎÂ¶ÈÕýžº±êÖŸ
		{
		flag=1;
		TL=~TL;	 //È¡·Ž
		TH=~TH;	  //È¡·Ž
		tltemp=TL+1; //µÍÎ»ŒÓ1
		TL=tltemp;
		if(tltemp>255) TH++;  //Èç¹ûµÍ8Î»ŽóÓÚ255£¬Ïòžß8Î»œø1
	   TN=TH*16+TL/16;      //ÊµŒÊÎÂ¶ÈÖµ=(TH*256+TL)/16,ŒŽ£ºTH*16+TL/16
				                  //ÕâÑùµÃ³öµÄÊÇÎÂ¶ÈµÄÕûÊý²¿·Ö,Ð¡Êý²¿·Ö±»¶ªÆúÁË
	       //ŒÆËãÎÂ¶ÈµÄÐ¡Êý²¿·Ö,œ«ÓàÊý³ËÒÔ10ÔÙ³ýÒÔ16È¡Õû£¬
		}
		TN=TH*16+TL/16;      //ÊµŒÊÎÂ¶ÈÖµ=(TH*256+TL)/16,ŒŽ£ºTH*16+TL/16
				                  //ÕâÑùµÃ³öµÄÊÇÎÂ¶ÈµÄÕûÊý²¿·Ö,Ð¡Êý²¿·Ö±»¶ªÆúÁË
	       //ŒÆËãÎÂ¶ÈµÄÐ¡Êý²¿·Ö,œ«ÓàÊý³ËÒÔ10ÔÙ³ýÒÔ16È¡Õû£¬
		display_temp1(TN);	                  //ÕâÑùµÃµœµÄÊÇÎÂ¶ÈÐ¡Êý²¿·ÖµÄµÚÒ»Î»Êý×Ö(±£Áô1Î»Ð¡Êý
	    //ÏÔÊŸÎÂ¶ÈµÄÐ¡Êý²¿·Ö
      delay(10);               
    }	








void main(){
uchar num1=0;
uchar num2=0;
   LcdInt();
   delay(10);
   Write_com(0x01);
   delay(5);
   WriteAddress(0x01);//ÏÂÃæÊÇ»¶Ó­Óï
   WriteData('L');WriteData('i');
   WriteData('R');
   WriteData('o');
   WriteData('n');
    WriteData('g'); WriteData(' '); delay(10);WriteData('H'); WriteData('e');
	 WriteData('n');delay(50);
	  WriteData('S');
	   WriteData('h');
	  WriteData('a');delay(50);
   WriteAddress(0x43);
	  WriteData('C');WriteData('a');WriteData('l');WriteData('c');WriteData('u');WriteData('l');WriteData('a');
	  WriteData('t');WriteData('o');WriteData('r');
   delay(100);
   //ŽËŽŠ¿ªÊŒÑ­»·º¯Êý
  A: while(1)
   {num1=0;num2=0;count=0;shi=1;
   Write_com(0x01);
   delay(5);wendu();//ÎÂ¶ÈÏÔÊŸ¿ØÖÆº¯Êý
   	Write_com(0x40);       //Éè¶šCGRAMµØÖ·
			delay(5);
			for(j=0;j<8;j++ )
			{
				WriteData(User[j]);//ÐŽÈë×Ô¶šÒåÍŒÐÎ ¡æ 
			}
	   		WriteAddress(0x43);//Éè¶šÆÁÄ»ÉÏµÄÏÔÊŸÎ»ÖÃ
			 delay(5);
	   		WriteData(0x00);	  //ŽÓCGRAMÀïÈ¡³ö×Ô¶šÒåÍŒÐÎÏÔÊŸ

   WriteAddress(0x00);
   WriteData('I');
   WriteData('n');
   WriteData('p');
   WriteData('u');
   WriteData('t');
   WriteData(':');
   
  
   key=16;
   while(1){ 
   while(key==16){
   keyscan();}
   if(key==0)
   goto A;
     if(key>=11)
	 	  break;
      else
     {WriteData(mayuan[key]); num1=key+num1*10;}
	 key=16; }
  
  
  
   	 i=key;
     WriteData(mayuan[key]);
	 key=16;
 
	
	while(1){
	while(key==16){
   keyscan();}
   if(key==0)
   goto A;
     if(key>=11&&key<=14)
	 WriteData(Error[0]);
	 if(key==15)
	 break;
      else
     {WriteData(mayuan[key]); num2=key+num2*10;}
	 key=16;}
   switch(i){
   case 11:result=num1/num2;break;
   case 12:result=num1*num2;break;
   case 13:result=num1-num2;break;
   case 14:result=num1+num2;break;
    } 



	
  	
	key=result;WriteData('=');
	WriteAddress(0x40);WriteData('R');WriteData('e');WriteData('s');WriteData('u');WriteData('l');WriteData('t');WriteData(':');
	while(key!=0){count++;key=key/10;}
	count1=count;
	count2=count;
	key1=result;
	while(count!=0){
	while(count1!=1){key1=key1/10;count1--;}
	WriteData(mayuan[key1]);
	while(count2!=1){shi=shi*10;count2--;}
	result=result-key1*shi;shi=1;
	key1=result;
	count--;
	count1=count;count2=count;
	}

    key=16;
	for(;key!=0;)
	{keyscan();}
	} }
