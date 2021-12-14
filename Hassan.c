sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D0 at RD0_bit;
sbit LCD_D1 at RD1_bit;
sbit LCD_D2 at RD2_bit;
sbit LCD_D3 at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;


sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit ICD_D0_Direction at TRISD0_bit;
sbit LCD_D1_Direction at TRISD1_bit;
sbit ICD_D2_Direction at TRISD2_bit;
sbit LCD_D3_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
 // LCD setup and module connections                              declare the LCD prior to int

//create variable and save them either as integers or variables with specified lengths along with setting higher limit(hlim) to 70 and lower limit(llim) to 20
int pk;               // create variable pk as integer for pressed key
char temp_string[10]; // create variable as character with length of 10
char highlim[5];     // create variable as character with length of 5
char lowlim[5];      // create variable as character with length of 5
int hlim=70;          // create variable as integer and has a set value of 70 for higher limit
int llim= 20;         // create variable as integer and has a set value of 20 for lower limit
char keypadPort at PORTD;   //declaring keypad at port D
int adctemp;
char temp_in_celsius[5];

void tempout()    //this function takes the created variable adctemp and saves the signal taken from the sensor to it, multiplying this signal to obtain a temperature in degrees then converting the float into string so that its compatible to the LCD then displaying it on the LCD
{
int adctemp = ADC_Read(2);
float temp_in_celsius = 5*adctemp/10.24;
WordToStr(temp_in_celsius,temp_string);
Lcd_Out(1,7,temp_string);
 }


void higherlimout()  //this function contains conditions for setting the higher limit by stating that when a specific button is pressed the value of the limit either increases or decreases depending on the button overwriting the same variable hlim the value in this variable is then converted to string and outputed to the LCD along with "HL" that represents higher limit
{
if (RB2_bit ==1)
{
hlim = hlim+1;
}
if (RB1_bit ==1)
{
hlim = hlim-1;
}

shortToStr(hlim,highlim);
Lcd_Out(2,2,highlim);
Lcd_Out(2, 1, "HL:");

 }
 
 void lowerlimout() // mirroring the previous function this function contains conditions for setting the lower limit by stating that when a specific button is pressed the value of the limit either increases or decreases depending on the button overwriting the same variable llim the value in this variable is then converted to string and outputed to the LCD along with "LL" that represents lower limit
 {
 if (RB3_bit ==1)
{
llim = llim+1;
}
if (RB4_bit ==1)
{
llim = llim-1;
}
 
 shortToStr(llim,lowlim);
 Lcd_Out(2,10,lowlim);
 Lcd_Out(2, 8, "LL:");

 
 }


void main(){

//LCD Setup
 //ANSEL represents wther its analog or digital 0 representing digital TRIS represents whether its an input or output 0 represents output
ANSELD=0;
TRISD=0;
PORTD=0;
TRISE=0;
PORTE=0;
ANSELE=0xff;
Lcd_Init() ;
Lcd_Cmd(_LCD_CLEAR) ;   //clears LCD screen
Lcd_Cmd(_LCD_CURSOR_OFF) ;   // removes cursor on LCD
    //displays good afternoon assignment 2  leaving it for 1 sec then clearing the screen
Lcd_Out(1,1, "Good Afternoon") ;
Lcd_Out(2,1, "Assignment 2") ;
Delay_ms(1000) ;
Lcd_Cmd(_LCD_CLEAR) ;


Lcd_Out(1, 1, "Temp: ") ;        //displays temp next to temperature output











//Setup Adc input

ANSELA=0xff;
TRISA=0xff;
//RA2_bit=1;
ADC_Init();

//setup button input for limits

ANSELB=0;
TRISB=0xff;




//Setup Heater

ANSELC=0;
TRISC = 0;
RC5_bit=1;     // turn heater on






lowerlimout();   // call function


   while(1)    // this conditions allow the buzzer to go off when temperature read is higher than the upper limit or lower than the lower limit in each case turning the buzzer on other than that its located bit will equal 0 meaning its off
   {

 if (((char)temp_in_celsius >= hlim))
    {
    RC1_bit=1;

    }
 else if (((char)temp_in_celsius <= llim))
    {
    RC1_bit=1;
    }
 


    else
    {
    RC1_bit=0;
    }
    tempout();           // call function for temperature calculation and display
    higherlimout();     // call function for higher limit input and display
    lowerlimout();     // call function for lower limit and display


    }
}





