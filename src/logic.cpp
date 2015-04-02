#include"interface.h"

using namespace logic;
using namespace player;
using namespace map;

Logic::Logic(){
  _gameStatus = "gameStatus";
  _commandsFromGUI = queue<CommandFromGUI>();
}

Logic::~Logic(){
  _gameStatus = "";
  _commandsFromGUI.empty();
}

string Logic::getStatusForGUI(){
  return _gameStatus;
}


void Logic::setCommandForPlayer(){
  //необходимы set-функции у класса PLAYER для установления новых параметров игрока и в последствии пули
}
void Logic::getNextCommandFromGUI(CommandFromGUI g_commandFromGUI){
  _commandsFromGUI.push(g_commandFromGUI);
}

void Logic::run(){
  if(getStatusForGUI() == "play"){
    while(true){
      getNextCommandFromGUI(_commandsFromGUI.back());
      setCommandForPlayer();
      updateMap();
    }
  }
}