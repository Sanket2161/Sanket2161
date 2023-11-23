//Macro Definitions
#define LM35 A0
#define LED  13

//Global Variable declaration
bool Toggle1 = 0, Toggle2=0;
float Tempr = 0.0;
unsigned int Timer1=0, Timer2=0;
const float Vref = 5.0;
const int Max_Adc_Counts = 1023, Conversion_Factor = 100, Event1_time = 500, Event2_time = 250;


//Timer0 Interrupt triggers every 1ms
ISR(TIMER0_COMPA_vect){//ISR started
  if (Tempr > 30) //Blink every 500ms
  {
    Timer1++;Timer2=0;
    if(Timer1 == Event1_time)
    {
      digitalWrite(LED,~Toggle1);
      Timer1=0;
    }
  }
  else// //Blink every 250ms
  {
    Timer2++;Timer1=0;
    if(Timer2 == Event2_time)
    {
      digitalWrite(LED,~Toggle2);
      Timer2=0;
    }
  }

}//End of ISR

//Start of Setuop()
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  cli();//stop interrupt

//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 1khz increments
  OCR0A = 249;// = (16*10^6) / (1000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  sei();//allow interrupts

}//End of Setup()

//Start of Loop()
void loop() {
  // put your main code here, to run repeatedly:

    float Lmvalue = analogRead(LM35);//Read sensor data from LM35, 10Deg Cel. = 0.100 V
    float Vsense = (Lmvalue*Vref)/Max_Adc_Counts;//Convert ADC Counts into voltage   Voltage= (ADC counts * 5.0)/1023
    Tempr = Lmvalue * Conversion_Factor;//Convert voltage into Temp into Deg Cel.
  
}//End of Loop()

/*--------------FILE REVISION HISTORY-------------------------*
*------------DATE 23-11-2023----------------------------------*
*------------AUTHOR  SANKET S DARADE--------------------------*
*------------Initial LM35 and Timer Implementation------------*/




