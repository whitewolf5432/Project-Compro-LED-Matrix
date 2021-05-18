int x=0;
int index;
String msg = "I LOVE COMPUTER PROGRAMMING SO MUCH."; //Create word.

//Count character
int length = msg.length();

//Columns
int clockPin1 = 2; //Arduino pin connected to Clock Pin 11 of 74HC595
int latchPin1 = 3; //Arduino pin connected to Latch Pin 12 of 74HC595
int dataPin1 = 4;  //Arduino pin connected to Data Pin 14 of 74HC595

//Rows
int clockPin2 = 5; //Arduino pin connected to Clock Pin 11 of 74HC595
int latchPin2 = 6; //Arduino pin connected to Latch Pin 12 of 74HC595
int dataPin2 = 7;  //Arduino pin connected to Data Pin 14 of 74HC595

//FONT DEFENITION
byte alphabets[][9] = {
 {0, 0,     0, 0,     0, 0,     0, 0}, //SPACE
 {0, 30,   50, 72,   72, 50,   30, 0}, //A
 {0, 126, 126, 66,   74, 74,   52, 0}, //B
 {0, 60,   66, 66,   66, 66,  100, 0}, //C
 {0, 126,  66, 66,   66, 36,   24, 0}, //D
 {0, 126,  82, 74,   82, 74,   82, 0}, //E
 {0, 126,  72, 72,   72, 72,  104, 0}, //F
 {0, 60,   66, 66,   90, 82,   76, 0}, //G
 {0, 126, 126, 24,   24, 126, 126, 0}, //H
 {0, 102, 102, 126, 126, 102, 102, 0}, //I
 {0, 12,   14, 102, 126, 124,  96, 0}, //J
 {0, 126, 126, 24,   36, 66,   66, 0}, //K
 {0, 126, 126, 6,     6, 6,    14, 0}, //L
 {0, 126,  32, 24,   24, 32,  126, 0}, //M
 {0, 126,  32, 16,    8, 4,   126, 0}, //N
 {0, 60,   66, 66,   66, 66,   60, 0}, //O
 {0, 66,  126, 126,  74, 72,   48, 0}, //P
 {0, 56,   68, 68,   76, 68,   58, 0}, //Q
 {0, 126, 126, 72,   76, 74,   50, 0}, //R
 {0, 36,   82, 82,   74, 74,   36, 0}, //S
 {0, 96,   98, 126, 126, 98,   96, 0}, //T
 {0, 120, 124, 6,     6, 124, 120, 0}, //U
 {0, 112,  28, 6,     6, 28,  112, 0}, //V
 {0, 126,   4, 24,   24, 4,   126, 0}, //W
 {0, 66,   36, 24,   24, 36,   66, 0}, //X
 {0, 96,   50, 30,   30, 50,   96, 0}, //Y
 {0, 98,   70, 74,   82, 98,   70, 0}, //Z
};

// Function setup program.
void setup()
{
 pinMode(latchPin1, OUTPUT);
 pinMode(clockPin1, OUTPUT);
 pinMode(dataPin1, OUTPUT);

 pinMode(latchPin2, OUTPUT);
 pinMode(clockPin2, OUTPUT);
 pinMode(dataPin2, OUTPUT);
}

// Function output program.
void Display(int alpha)
{
  for (int row = 0; row < 8; row++) {
    int rowbit = 1 << row;
    digitalWrite(latchPin2, LOW); //Hold latchPin LOW for transmitting data
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowbit); //Transmit data

    //Start sending column bytes
    digitalWrite(latchPin1, LOW); //Hold latchPin LOW for transmitting data
   
    //Shift out to each matrix
    shiftOut(dataPin1, clockPin1, LSBFIRST, ~alphabets[alpha][row]);

    //flip both latches at once to eliminate flicker
    digitalWrite(latchPin1, HIGH); //Return the latch pin 1 high to signal chip
    digitalWrite(latchPin2, HIGH); //Return the latch pin 2 high to signal chip

    //Wait
    delay(50);
  }
}

// Function loop
void loop()
{
  index = msg[(x++)%length]-'@';
  index = index < 0?0:index;
  for (int blink = 0; blink <= (index?5:2); blink++)
  {
    Display(index);
  }
}
