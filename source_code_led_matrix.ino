int x=0;
int index;
String msg = "I LOVE COMPRO";//Create word.

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
byte alphabets[][8] = {
 {0, 0, 0, 0, 0, 0, 0, 0},//SPACE
 {0, 31, 36, 68, 36, 31},//A
 {0, 127, 73, 73, 73, 54},//B
 {0, 62, 65, 65, 65, 34},//C
 {0, 127, 65, 65, 34, 28},//D
 {0, 127, 73, 73, 65, 65},//E
 {0, 127, 72, 72, 72, 64},//F
 {0, 62, 65, 65, 69, 38},//G
 {0, 127, 8, 8, 8, 127},//H
 {0, 0, 65, 127, 65, 0},//I
 {0, 2, 1, 1, 1, 126},//J
 {0, 127, 8, 20, 34, 65},//K
 {0, 127, 1, 1, 1, 1},//L
 {0, 127, 32, 16, 32, 127},//M
 {0, 127, 32, 16, 8, 127},//N
 {0, 62, 65, 65, 65, 62},//O
 {0, 127, 72, 72, 72, 48},//P
 {0, 62, 65, 69, 66, 61},//Q
 {0, 127, 72, 76, 74, 49},//R
 {0, 50, 73, 73, 73, 38},//S
 {0, 64, 64, 127, 64, 64},//T
 {0, 126, 1, 1, 1, 126},//U
 {0, 124, 2, 1, 2, 124},//V
 {0, 126, 1, 6, 1, 126},//W
 {0, 99, 20, 8, 20, 99},//X
 {0, 96, 16, 15, 16, 96},//Y
 {0, 67, 69, 73, 81, 97},//Z
};

void setup()
{
 pinMode(latchPin1, OUTPUT);
 pinMode(clockPin1, OUTPUT);
 pinMode(dataPin1, OUTPUT);

 pinMode(latchPin2, OUTPUT);
 pinMode(clockPin2, OUTPUT);
 pinMode(dataPin2, OUTPUT);
}

//FUNCTIONS
// Displays bitmap array in the matrix
void RefreshDisplay(int alpha)
{
  for (int row = 0; row < 8; row++) {
    int rowbit = 1 << row;
    digitalWrite(latchPin2, LOW);//Hold latchPin LOW for transmitting data
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowbit);   //Transmit data

    //Start sending column bytes
    digitalWrite(latchPin1, LOW);//Hold latchPin LOW for transmitting data
   
    //Shift out to each matrix
    shiftOut(dataPin1, clockPin1, LSBFIRST, ~alphabets[alpha][row]);

    //flip both latches at once to eliminate flicker
    digitalWrite(latchPin1, HIGH);//Return the latch pin 1 high to signal chip
    digitalWrite(latchPin2, HIGH);//Return the latch pin 2 high to signal chip

    //Wait
    delay(100);
  }
}

// Converts row and colum to bitmap bit and turn it off/on
void loop()
{
  index = msg[(x++)%length]-'@';
  index = index < 0?0:index;
  for (int blink = 0; blink <= 5; blink++)
  {
    RefreshDisplay(index);
  }
}
