#define pinUp    15
#define pinLeft  18
#define pinRight 16
#define pinDown  17
#define pinBite  19
#define pinDance 22

void print_values();
int refUp, refLeft, refRight, refDown, refBite, refDance;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(38400);
  refUp = touchRead(pinUp) + 100;
  refLeft = touchRead(pinLeft) + 100;
  refRight = touchRead(pinRight) + 100;
  refDown = touchRead(pinDown) + 100;
  refBite = touchRead(pinBite) + 100;
  refDance = touchRead(pinDance) + 100;

  Serial.println("Reference values");
  print_values();

  
}

void loop() {
  
  //Serial.println("RUNTIME VALUE");
  // print_values();

  if (touchRead(pinUp) > refUp)
    Serial.println("Up");
  if (touchRead(pinLeft) > refLeft)
    Serial.println("Left");
  if (touchRead(pinRight) > refRight)
    Serial.println("Right");
  if (touchRead(pinDown) > refDown)
    Serial.println("Down");
  if (touchRead(pinBite) > refBite)
    Serial.println("Bite!!!!!!");
  if (touchRead(pinDance) > refDance)
    Serial.println("PARTY TIEM!!!111!");

  delay(200);
}

void print_values() {
  Serial.print("Up: ");
  Serial.println(touchRead(pinUp));
  Serial.print("Left: ");
  Serial.println(touchRead(pinLeft));
  Serial.print("Right: ");
  Serial.println(touchRead(pinRight));
  Serial.print("Down: ");
  Serial.println(touchRead(pinDown));
  Serial.print("Bite: ");
  Serial.println(touchRead(pinBite));
  Serial.print("Dance: ");
  Serial.println(touchRead(pinDance));
  Serial.println("  ");
}


