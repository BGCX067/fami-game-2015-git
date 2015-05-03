#include "general_types.h"

/*КОманды от GUI*/
CommandFromGUI::CommandFromGUI(){
  _playerNumber = 0;
  _guiCommand = GUICommand();
}
CommandFromGUI::~CommandFromGUI(){

}

void CommandFromGUI::setPlayerNumber(t_player_number s_player_number){
  _playerNumber = s_player_number;
}
void CommandFromGUI::setFromGUICommand(GUICommand s_gui_command){
  _guiCommand = s_gui_command;
}

t_player_number CommandFromGUI::getPlayerNumber(){
  return _playerNumber;
}
GUICommand CommandFromGUI::getGUICommand(){
  return _guiCommand;
}
