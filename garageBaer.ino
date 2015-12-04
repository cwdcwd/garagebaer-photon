
int openDoor(String command);
int closeDoor(String command);
int setState(String state);
int controlPin=D0;
int relayPower=A0; //CWD-- for testing

int iGarageState=0;
int iLastState;

void setup() {
    Serial.begin(9600);
    iGarageState=iLastState=0;
//CWD-- register funcs & vars
    Spark.function("openDoor",openDoor);
    Spark.function("closeDoor",closeDoor);
    Spark.function("setState",setState);
    Spark.variable("state", &iGarageState, INT);
//CWD-- set up pins
    pinMode(controlPin, OUTPUT);
    pinMode(relayPower, OUTPUT);

    digitalWrite(controlPin, LOW);
    digitalWrite(relayPower, HIGH);
}

void loop() {
    String s=getState();

    if(iLastState!=iGarageState){
        Spark.publish("state",s);
        Serial.println(s);
    }

    iLastState=iGarageState;
    delay(1000);
}

int openDoor(String command){
    //CWD-- execute open
    setState("OPENED");
    return operateDoor();
}

int closeDoor(String command){
    //CWD-- execute close
    setState("CLOSED");
    return operateDoor();
}

int operateDoor(){
  digitalWrite(controlPin,HIGH); //CWD-- open relay
  delay(1000); //CWD-- let it go for a sec
  digitalWrite(controlPin,LOW); //CWD-- close relay
  return iGarageState;
}

int setState(String s){
  int p=iGarageState;

  if(s=="OPENED"){
    iGarageState=1;
  } else if(s=="CLOSED"){
    iGarageState=-1;
  } else {
    iGarageState=0;
  }

  return p;
}

String getState(){
  if(iGarageState==1){
    return "OPENED";
  } else if(iGarageState==-1){
    return "CLOSED";
  }

  return "UNKOWN";
}
