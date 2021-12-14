sbit LCD_RS at LATA3_bit;
sbit LCD_EN at LATB1_bit;
sbit LCD_D4 at LATB2_bit;
sbit LCD_D5 at LATB3_bit;
sbit LCD_D6 at LATB4_bit;
sbit LCD_D7 at LATB5_bit;

sbit LCD_RS_Direction at TRISA3_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;
 // LCD setup and module connections              declare the LCD prior to int

//create variable and save them either as integers or variables with specified lengths along with setting higher limit(hlim) to 70 and lower limit(llim) to 20
int pk;
char temp_string[10];
char highlim[5];
char lowlim[5];
int hlim=70;
int llim= 20;
char keypadPort at PORTD;   //declaring keypad at port D
int adctemp;
char temp_in_celsius[5];

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
Lcd_Cmd(_LCD_CURSOR_OFF) ;    // removes cursor on LCD
       //displays good afternoon assignment 2  leaving it for 1 sec then clearing the screen
Lcd_Out(1,1, "Good Afternoon") ;
Lcd_Out(2,1, "Assignment 2") ;
Delay_ms(1000) ;
Lcd_Cmd(_LCD_CLEAR) ;


Lcd_Out(1, 1, "Temp: ") ; //dsiplays temp next to temperature output
Lcd_Out(2, 1, "HL:");   // displays HL as higher limit  next to the upper limit
Lcd_Out(2, 10, "LL:");  // displays HL as higher limit  next to the upper limit

// Initialize LCD
// Clear LCD display
// Turn cursor off
// Clear LCD display
// Prepare and output static text on LCD
// Prepare and output static text on LCD
// Prepare and output static text on LCD





//Setup Adc

ANSELA=0x00000010;
TRISA=0x00000010;
//RA2_bit=1;
ADC_Init();






//Setup keypad()

ANSELB=0;
TRISB=0;
//TRISC=0xff;
Keypad_Init();

while(1){
int adctemp = ADC_Read(1);
float temp_in_celsius = 5*adctemp/10.24;   // equation changes signal from sensor to temperature in degrees
WordToStr(temp_in_celsius,temp_string);   //needed as lCD only accepts string and wont accept it as a float to display
Lcd_Out(1,8,temp_string);
//takes the created variable adctemp and saves the signal taken from the sensor to it, multiplying this signal to obtain a temperature in degrees then converting the float into string so that its compatible to the LCD then displaying it on the LCD



   // converts the variables hlim and llim which was an int into a string to allow compatibility with LCD  and displays the limit along with their symbolic representation
WordToStr(hlim,highlim);
WordToStr(llim,lowlim);
Lcd_Out(2,1,highlim);
Lcd_Out(2,10,lowlim);
Lcd_Out(2, 1, "HL:");
Lcd_Out(2, 10, "LL:");



if (Keypad_Key_Click() == 16 ) // this section allows user input using the keypad when the user pressed D on the keypad the higher limit is altered  when key 1 is pressed higher limit increases by 1 when key 2 is pressed the higher limit is decreased by 1 when * key is pressed the higher limit is  added by 10 in each scenario the variable is overwritten
{
pk = 0;
while (pk==0);
{
pk = Keypad_Key_Click();
if (pk == 1)
{
 hlim = hlim +1;break;
}
else if (pk == 2)
{
 hlim = hlim - 2;break;

}
 else if (pk == 13)
 {
 hlim = hlim + 10;break;
 }
}


}

 // this section allows user input using the keypad when the user pressed  on C the keypad the lower limit is altered  when key 1 is pressed lower limit increases by 1 when key 2 is pressed the lower limit is decreased by 1 when * key is pressed the lower limit is  added by 10 in each scenario the variable is overwritten
if (Keypad_Key_Click() == 12 ) //
{
int pk = 0;
while (pk==0);
{
pk = Keypad_Key_Click();
if (pk == 1)
{
 llim = llim +1;break;
}
else if (pk == 2)
{
 llim = llim - 1;break;

}
 else if (pk == 13)
 {
 llim = llim + 10;break;
 }
}


}

 if ((temp_in_celsius >= hlim) || (temp_in_celsius <= llim)) // if the actual temperature exceeds the limits in any direction the buzzer turns on
    {
    PORTE=0xff;
    }

    else
    {
    PORTE=0;
    }


}

}