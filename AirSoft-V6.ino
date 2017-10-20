//Alarme Air Soft pour Stephane
//On/Off, appuie bouton déclenche alarme au bout de x seconde
//Parametrage tempo 10 ou 30 s par un appuie bouton

#define Buzzer 3       //patte relai / buzzer
#define BtTempo 12   //bouton poussoir tempo 10 ou 30s
#define BtStart 11   //bouton poussoir start
#define LedStart 10 //led tempo declenché
#define LedTempo10 9//led tempo sur 10s
#define LedTempo30 8//led tempo sur 30s


//Tempo
int Tempo = 10000; // Tempo de base 10s (en ms)
int TempoMin = 10000;
int TempoMax = 30000;
int TempsBuzzer = 5000;

long Debut_Tempo; //calcul duréé
byte Flag_Debut_Tempo = 0;


//Bouton
int valBtTempo = 0;        //sauve etat bouton dans val
int old_valBtTempo = 0;    //sauve valeur précedente de val
int stateBtTempo = 0;       //0 = del eteint, 1 = del allumée

int valStart = 0;        //sauve etat bouton dans val
int FlagvalStart = 1; //flag debut
int old_valStart = 0;    //sauve valeur précedente de val
int stateStart = 0;       //0 = del eteint, 1 = del allumée


//Alarm
int AlarmGo= 0;

void setup() {
             Serial.begin(9600); //Moniteur série en 9600 Baud
             Serial.println("Alarme Air Soft Domochris.fr");
             pinMode(Buzzer, OUTPUT);   //patte sortie buzzer
             pinMode(BtTempo, INPUT); //patte bouton tempo
             pinMode(BtStart, INPUT); //patte bouton Start
             pinMode(LedStart, OUTPUT);   //patte del LedStart
             pinMode(LedTempo10, OUTPUT);   //patte del LedTempo10
             pinMode(LedTempo30, OUTPUT);   //patte del LedTempo30
             }

void loop() {
  
            Parametrage();
            Led();
            TempoGo();
            Alarm();

            }



void Parametrage(){
  
                  //Tempo
                  valBtTempo = digitalRead(BtTempo);   //lit etat du bouton
                  //Test si changement etat
                  if ((valBtTempo==HIGH) && (old_valBtTempo==LOW)){
                                                                  stateBtTempo=1-stateBtTempo;
                                                                  delay(10);
                                                                  }
                  old_valBtTempo = valBtTempo;    //sauve ancienne val
                  
                  if (stateBtTempo == 1){
                                          Tempo = TempoMax;
                                           // digitalWrite(Buzzer, HIGH); //allume led
                                        }  
                                        else  {
                                                  Tempo = TempoMin;
                                              }
                  
                 //Start
                 if (FlagvalStart==1){
                                      valStart = digitalRead(BtStart);   //lit etat du bouton
                                      if (valStart == 1){ 
                                                          FlagvalStart =0;
                                                          Flag_Debut_Tempo = 1;
                                                         }
                                      }
                  
                 }
  
   void Led(){ //affichage par led tempo et start
   
               if (AlarmGo == 2){ digitalWrite(LedStart, HIGH); //allume led LedStart
                               } 
                                else {digitalWrite(LedStart, LOW); //eteind led LedStart
                                      }
               if (Tempo == TempoMin){ digitalWrite(LedTempo10, HIGH); //allume led LedTempo10
                                     } 
                                      else {digitalWrite(LedTempo10, LOW); //eteind led LedTempo10
                                            }
               if (Tempo == TempoMax ){ digitalWrite(LedTempo30, HIGH); //allume led LedTempo30
                                       } 
                                      else {digitalWrite(LedTempo30, LOW); //eteind led LedTempo30
                                            }                       
  
              } 
  
  
  
  void TempoGo(){
 // Serial.println(Flag_Debut_Tempo);
                if (Flag_Debut_Tempo == 1){
                  
                                          AlarmGo =1;
                                          Flag_Debut_Tempo =0;
                                          }
                              
                }  


  
  void Alarm(){
 //  Serial.println(Debut_Tempo);
               if (AlarmGo == 1){  
                                 Debut_Tempo = millis();
                                 AlarmGo = 2;
                                 digitalWrite(Buzzer, HIGH); //allume buzzer deux bip 1/2 seconde au démarrage du compteur
                                 delay(500);
                                 digitalWrite(Buzzer, LOW); //allume buzzer
                                 delay(500);
                                 digitalWrite(Buzzer, HIGH); //allume buzzer 
                                 delay(500);
                                 digitalWrite(Buzzer, LOW); //allume buzzer
                                 }

               if (AlarmGo == 2){   
                                   //Debut_Tempo
                                  if ((millis() - Debut_Tempo)> Tempo){ //Temp + grand que Tempo declenchement buzzer
                      
                                                                       if (((millis() - Debut_Tempo)-Tempo)< TempsBuzzer){ //Temps - grand que TempsBuzzer apres la Tempo
                                                       
                                                                                                                          digitalWrite(Buzzer, HIGH); //allume buzzer
                                                                                                                          }
                                                        
                                                                       else {
                                                                              AlarmGo = 0;
                                                                              FlagvalStart =1;  
                                                                              digitalWrite(Buzzer, LOW); //eteins buzzer
                                                                              } //on sort de la boucle, plus de buzzer  
                                                               
                                                                       }
        
                  
  
                                }
              }
