#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

//screen configuration
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET    4  // Reset pin # (or -1 if sharing reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
 
// keyboard configuration
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

//Change the following pins your yours keypad pinout!
byte rowPins[ROWS] = {7, 2, 3, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 8, 4};    //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


String token;
unsigned long debugToken = 0;
uint8_t id = 120;

const int confPin = 9;
const int resPin = 10;
void setup()
{
  pinMode(confPin,INPUT_PULLUP);
  pinMode(resPin, INPUT_PULLUP);
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 allocation failed");
    while(1); //Don't proceed, loop forever
  }
  //display.display();
  //delay(100);
  //display.clearDisplay(); 

  debugToken = encodeData(5000,id,2);
  displayMenu("");
}
 
void loop()
{
//Read if button is pressed	
  char key = keypad.getKey();
  //Print this button to serial monitor
  if (key != NO_KEY && key != '*' && key != '#'){
    	token += String(key);
	displayMenu(token);
  }

  if(digitalRead(resPin) == HIGH)
  {
	clearToken();
  }

  if(digitalRead(confPin) == HIGH)
  {
    confirmToken();
  }

}

void clearToken()
{
   token = "";
   displayMenu("clr....");
   delay(1000);
   displayMenu(token);
   
}

void confirmToken()
{
   displayMenu("Checking......");
   uint32_t duration, curTime;
   uint8_t idd;

   decodeData(debugToken,duration,idd,curTime);
   delay(1000);
   displayMenu(String(idd));
   delay(1000);
   if(idd==id)
	{	
 		displayMenu("token accepted");
	
	}else{
	     displayMenu("try again");
	}

   //displayMenu(token);
   
}
void displayMenu(String msg)
{

	display.clearDisplay();
  display.setTextColor(WHITE);  
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.print(msg);
  display.setCursor(0,20);
  display.print("token: " + String(debugToken));
  display.display();

}

unsigned long encodeData(uint32_t duration, uint8_t id, uint32_t currentTime) {
  // Use bitwise operations to pack the data into a 32-bit integer
  unsigned long token = 0;
  token |= (duration & 0xFFFFF) << 12; // Using 20 bits for duration (up to ~1048575 seconds)
  token |= (id & 0xF) << 8; // Using 4 bits for id (up to 15 different ids)
  token |= (currentTime & 0xFFFFFFFF); // Using 32 bits for currentTime (up to ~136 years)

  return token;
}

// Function to decode the numerical token and extract duration and time
void decodeData(unsigned long token, uint32_t& duration, uint8_t& id, uint32_t& currentTime) {
  // Use bitwise operations to unpack the data from the numerical token
  duration = (token >> 12) & 0xFFFFF;
  id = (token >> 8) & 0xF;
  currentTime = token & 0xFFFFFFFF;
}

int charToInteger(String ch) {
  // Convert the character to a null-terminated string (a string of length 1)

  
  // Use the atoi() function to convert the string to an integer
  int result = atoi(ch.c_str());

  return result;
}