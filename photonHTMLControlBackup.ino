//PUT YOUR VARIABLES HERE

void setup(){
    Particle.function("my-main", myMain);  
    
    //PUT YOUR SETUP CODE HERE. Note: Only three more functions allowed!
    // test everything using the return int from a function!
    
    //RGB.control(true);
    //RGB.color(0, 255, 255);  //cyan
    RGB.brightness(255);    // 1=very low light, 255 = max
}

void loop(){
    //PUT YOUR LOOP CODE HERE
}

int myMain(String myCode) {
    myCode.toUpperCase();   // set argument to uppercase--remove for better security
    // used send instead of write since I needed it to be 4 characters long.
    // d7-send-1 or d7-send-high or d7-send-on to turn on D7
    // d5-read      read D5
    // a0-send-0    turn A0 off
    // a0-send-255  turn A0 maximum
    // a1-read      read A1
     
    // Block sets pinNumber for digital 0-7 or analog 10-17 from the number
    int mySetWrite = 0;
    int pinNumber = myCode.charAt(1) - '0';
    if(myCode=="RESET"){                //Checks for RESET code for resetting all outputs
        for(int i=0; i<=7; i++){        //loops through D0-D7, setting all outputs to 0
            int v = i + 10;             //allows for looping A0-A5
            pinMode(i, OUTPUT);         //Sets pin to OUT
            pinMode(v, OUTPUT);
            digitalWrite(i, 0);         //Write 0 to pin
            analogWrite(v, 0);
        }
        return 4048404;                 //Return numerical value/code for "reset"
    }
    else if (pinNumber< 0 || pinNumber >7) return -1; 
    if (myCode.startsWith("A")){pinNumber = pinNumber+10;}  //+10 is for analog numbers
    
    String myActivity = myCode.substring(4,8);     //take the 4 characters
     
    //Following sets the characters after the last dash to integers
    String myOptional = myCode.substring(9);
    if(myOptional == "HIGH") {mySetWrite = 1;}
        else if(myOptional == "LOW") {mySetWrite = 0; }
            else if(myOptional == "ON") {mySetWrite = 1;}
                else if(myOptional == "OFF") {mySetWrite = 0; }
                   else {mySetWrite = myOptional.toInt();  }  // sets  write value
    // myCode parsing complete d0-dsend-1
    
    //-------------------------------------------------Dakaro Code----------------------------------------
    char mode = myCode.charAt(3);   //get char just before send/read
    if(mode == 68){ //is D
        if(myActivity == "READ"){
            pinMode(pinNumber, INPUT_PULLDOWN);
            return digitalRead(pinNumber);
        }
        else if(myActivity == "SEND"){
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            return mySetWrite;
        }
    }
    if(mode == 65){ //is A
        if(myActivity == "READ"){
            return analogRead(pinNumber);
        }
        else if(myActivity == "SEND"){
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);
            return mySetWrite;
        }
    }
    //----------------------------------------------------------------------------------------------------
}
