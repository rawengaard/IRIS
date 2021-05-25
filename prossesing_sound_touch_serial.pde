// This code is being run on a computer, while listening to input from an Arduino over the Serial port.


import processing.serial.*;
import ddf.minim.*;

// create a player for each sound
AudioPlayer player1;
AudioPlayer player2;
AudioPlayer player3;
AudioPlayer player4;
AudioPlayer player5;
AudioPlayer player6;
AudioPlayer player7;
AudioPlayer player8;
AudioPlayer player9;
AudioPlayer player10;
AudioPlayer player11;

Minim minim; // To read and use mp3 files

Serial port;
int val;
String inBuffer;
int lf = 10; // ASCII linefeed



void setup() {
   size(400, 400);                          // Sets the size on the processing window.
   printArray(Serial.list());
   // print a list of all available ports

   minim = new Minim(this);

   //Loading files to players.
   player1 = minim.loadFile("k1_klokke3_2 sek.mp3");
   player2 = minim.loadFile("takt tre_4 sek.mp3");
   player3 = minim.loadFile("k3_beat2_8 sek.mp3");
   player4 = minim.loadFile("k2_hamster_3 sek.mp3");
   player5 = minim.loadFile("k4_babbel_3 sek.mp3");
   player6 = minim.loadFile("k5_fiolin2_4,2 sek.mp3");
   player7 = minim.loadFile("k7_piano2_3 sek.mp3");
   player8 = minim.loadFile("k8_hund_2 sek.mp3");
   player9 = minim.loadFile("Latter_4,2 sek.mp3");
   player10 = minim.loadFile("Nannanana_3,1 sek.mp3");
   player11 = minim.loadFile("k10_pizzicato_3,5 sek.mp3");

   // Sets up Serial-conection, chooses the port to which the Arduino is connected
   port = new Serial(this, Serial.list()[0], 9600);

   // Buffer until Linefeed.
   port.bufferUntil(lf);

}
void draw() {
  //inBuffer = "........";
  background(100);
   text("received: " + inBuffer , 10,50);                   // 

     if (inBuffer!= null && inBuffer.equals("1")){          // if the input equals this number
       player1.play();                                      // Starts playback from the current position. If this was previously set to loop, looping will be disabled.
           if (player1.position() == player1.length()){     // if the position of the player is at the end of the file
              player1.rewind();}                            // rewind back to start
            redraw();                                       // update display window
     }
     if (inBuffer!= null && inBuffer.equals("2")){
       player2.play();
           if (player2.position() == player2.length() ){
              player2.rewind();}
              redraw();
     }
     if (inBuffer!= null && inBuffer.equals("3")){ //equals
       player3.play();
           if (player3.position()== player3.length() ){
              player3.rewind();}
              redraw();
     }
     if (inBuffer!= null && inBuffer.equals("4")){ //equals
       player4.play();
           if (player4.position() == player4.length() ){
              player4.rewind();}
              redraw();
     }
     if (inBuffer!= null && inBuffer.equals("5")){ //equals
       player5.play();
           if (player5.position() == player5.length() ){
              player5.rewind();}
              redraw();
     }
     if (inBuffer!= null && inBuffer.equals("6")){ //equals
       player6.play();
           if (player6.position() == player6.length() ){
              player6.rewind();}
              redraw();
     }
     if (inBuffer!= null && inBuffer.equals("7")){ //equals
       player7.play();
           if (player7.position() == player7.length() ){
              player7.rewind();}
              redraw();
     }
     if (inBuffer!= null && inBuffer.equals("8")){ //equals
       player8.play();
           if (player8.position() == player8.length() ){
              player8.rewind();}
              redraw();
     }
     if (inBuffer!= null && inBuffer.equals("9")){ //equals
       player9.play();
           if (player9.position()== player9.length() ){
              player9.rewind();}
              redraw();
     }
     if (inBuffer!= null && inBuffer.equals("10")){ //equals
       player10.play();
           if (player10.position() == player10.length() ){
              player10.rewind();}
              redraw();
     }
     if (inBuffer!= null && inBuffer.equals("11")){
       player11.play();
           if (player11.position() == player11.length() ){
              player11.rewind();}
              redraw();
     }
}

// Controls the input from Serial.
void serialEvent(Serial p) {                            // when there is information input from Serial
  inBuffer = p.readString();                            // read input
  inBuffer = inBuffer.trim().replace("\n","");          // trim and remove newline

}


void stop(){
   // always close Minim audio classes when you are done with them
   player1.close();
   player3.close();
   player4.close();
   player5.close();
   player6.close();
   player7.close();
   player8.close();
   player9.close();
   player10.close();
   player11.close();
   minim.stop();
   super.stop();
}
