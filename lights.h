#ifndef lights_h
#define lights_h

struct commandDefn {
  String commandName;
  String sequence;
};


const struct commandDefn commands[] = {
  {"On", "ON"},
  {"Off", "OFF"},
  {"All", "SEQ:ALL"},
  {"Reverse", "SEQ:REVERSE"},
  {"Reverse (Flashing)", "SEQ:FREVERSE"},
  {"Hazards" , "SEQ:HAZARDS"},
  {"Hazards (Flashing)", "SEQ:FHAZARDS"},
  {"Breaks", "SEQ:BREAKS"},
  {"Breaks (Flashing)", "SEQ:FBREAKS"},
  {"Breaks (Toggle)" , "SEQ:BREAKSTOGGLE"},
  {"Blink", "SEQ:BLINK"},
  {"Jackpot", "SEQ:JACKPOT"},
  {"Light run", "SEQ:LIGHTRUN"},
  {"Figure of 8", "SEQ:EIGHT EIGHT_R"},
  {"Cylon", "SEQ:CYLON CYLON_R"},
};

#endif
