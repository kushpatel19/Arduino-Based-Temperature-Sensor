// Without Controller
// For the Analog and digital temperature sensor module (NTC Thermistor Temperature Sensor)
// Temprature Control using Arduino
// ES311 - Heat and Mass Transfer 
// Group-A3

#define LED_PIN 13                                   // defining pin 13 as the led input pin
#define DIGITAL_INPUT 3                              // defining digital input at pin 3
#define ANALOG_INPUT A0                              // defining analog input at A0

// initializing the variables

int    digital_output ;                              // This will read the digital value
int    analog_output ;                               // This will read the analog value
int    revised_output;                               // variable to store the corrected value
float  temp_C ;                                      // Variable for storing the temperature
float  temp_f ;                                      // Variable for storing the fahrenheit

void setup ( )                                       // Anything written I it will run once.
{
  pinMode ( LED_PIN, OUTPUT ) ;                      // declaring pin 13 as output
  pinMode ( DIGITAL_INPUT, INPUT ) ;                 // declaring pin 3 as input
  pinMode ( ANALOG_INPUT, INPUT )  ;                 // declaring A0 as input pin
  Serial.begin ( 9600 ) ;                            // selecting the baud rate at 9600
  Serial.println (" HMT Group-A3 : The data is " ) ;
}

void loop ( )                                              // Anything written in it will run continuously
{
  analog_output = analogRead ( ANALOG_INPUT ) ;            // Reading the analog value and storing in analog_output
  Serial.print ( " Analog value of the NTC Thermistor is =  " ) ;                                       
  Serial.print ( analog_output ) ,  DEC ;                  // This will display the analog value
  Serial.println( );

  // The module has thermistor connection reversed
  revised_output= map ( analog_output, 0, 1023, 1023, 0 ) ;
  temp_C = Thermistor ( revised_output ) ;
  temp_f = ( temp_C * 9.0 ) / 5.0 + 32.0 ;

  // Reading the digital data
  digital_output = digitalRead ( DIGITAL_INPUT ) ;
  Serial.print ( "   Digital value of the NTC Thermistor is =  " ) ;
  Serial.println ( digital_output ) , DEC ;                // This will display the digital value on the display 
  Serial.println( );
  Serial.print ( " LED is = " ) ;
  // We can change the setpoint by giving the diffrent orientation of the screw on the potentiaometer
  if ( digital_output == HIGH )                            // The LED will turn on When the sensor value will exceed the set point
  {
    digitalWrite ( LED_PIN, HIGH ) ;
    Serial.print ( "ON " ) ;
  }
  else
  {
    digitalWrite ( LED_PIN, LOW ) ;
    Serial.print ( "OFF " ) ;   
  }
  
  // This will print the temperature
  Serial.println ( ); 
  Serial.print ( " Measured Temperature = " ) ;
  Serial.print ( temp_f, 1 ) ;                              // This will display the temperature in Fahrenheit
  Serial.print (" F  " ) ;
  Serial.print("- ");
  Serial.print  (temp_C, 1 ) ;                              // This will display the temperature in Celcius
  Serial.println (" C " ) ; 
  Serial.println ( ) ;                                      // Leaving a blank line
  Delay ( 1000 ) ;                                          // Wait for 1 second
}

double Thermistor ( int RawADC )
{
double Temp ;
  Temp = log ( ( ( 10240000 / RawADC ) – 10000 ) ) ;
  Temp = 1 / ( 0.001129148 + ( 0.000234125 * Temp ) + ( 0.0000000876741 * Temp * Temp * Temp ) ) ;
  Temp = Temp - 273.15 ;            // This will Convert Kelvin to Celcius
  return Temp ;
}
