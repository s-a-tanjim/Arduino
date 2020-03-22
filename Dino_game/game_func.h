// To check val is within "start" and "End"
boolean inRange(int val, int start, int End)
{
  if(End>start){
    if(val<=End && val>=start)
      return true;
  }
  else if(End==start)
  {
    if(start==val)
      return true;
  }
  else
  {
    if(val>=End && val<=start)
      return true;
  }
  return false;
}

// To check if dino is on the tree or not
boolean is_gameover(int treeX, int treeY, int dinoX, int dinoY)
{
  if(inRange(treeX,dinoX,dinoX+35) && inRange(treeY,dinoY,dinoY+46))
    return true;
  return false;
}

// This should check dino more precisely (But it has some bug :P )
boolean is_gameover___(int treeX, int treeY, int dinoX, int dinoY){
  //Serial.print(treeX);
  //Serial.print("   |   ");
  //Serial.println(dinoY);
  if(inRange(dinoY,DINO_BASE_POINT_Y-10,DINO_BASE_POINT_Y+5)) //Dino is in ground
  {
    //Serial.print("Ground      |   ");
    if(inRange(treeX,dinoX+42,dinoX+44))     //Head bari khaise kina
    {
      Serial.println("Head out");
      return true;
    }
    if(inRange(treeX,dinoX-1,dinoX+1))     //Tail bari khaise kina
    {
      Serial.println("Tail out");
      return true;
    }
  }
  else if(inRange(dinoY,DINO_BASE_POINT_Y-11,DINO_BASE_POINT_Y-40))   //Dino is jumping
  {
    //Serial.print("Jumping     |   ");
    if(dinoX+20<treeX)    //First half(head) of dino
    {
      Serial.println("Head Side     |   ");
      if(dinoX+35==treeX)
      {
        Serial.println("OUT!");
        return true;
      }
    }
    else                  //Last half(tail) of dino
    {
      Serial.println("Tail Side     |   ");
      if(dinoX+5==treeX+30 || dinoY+46==treeY)
      {
        Serial.println("OUT!");
        return true; 
      }
      //else if(inRange(treeY,dinoY+45,dinoY+100))
    }
  }
  else if(inRange(dinoY,DINO_BASE_POINT_Y-46,DINO_BASE_POINT_Y-100))  //Dino is up
  {
    Serial.println("Up      |   ");
    if(inRange(dinoX,treeX,treeX+30) && dinoY>=treeY)
    {
      Serial.println("OUT!");
      return true;
    }
  }
  //inRange(treeY,dinoY+45,dinoY+100)
  // && inRange(dinoX,treeX,treeX+30)
  //Serial.println("Not Out!");
  return false;
}

// Moves tree and check if dino is on it or not
void moveTree()
{
  if(tree_x_pos<=0){  // If tree reaches edge of the screen, it will start from beginning
    tree_x_pos=480;   // 480 is the width of the screen
  }
  clear_tree(tree_prev_pos_x,TREE_BASE_POINT_Y);  // Clear the previous tree
  tree(tree_x_pos,TREE_BASE_POINT_Y);             // Print the tree
  // Check game is over or not
  if(is_gameover(tree_x_pos,TREE_BASE_POINT_Y,DINO_BASE_POINT_X,dino_y_pos))
  {
    start_buzzer();
    playState=false;
    if(score>highScore)
      highScore=score;
    dino_y_pos = DINO_BASE_POINT_Y;
    tree_x_pos = 480; //width of screen
    gameOverMsgFlag=true;
    //Serial.println("Game Over!!!");
  }
  tree_prev_pos_x=tree_x_pos;
  tree_x_pos -= (gameSpeed+2);
  score++;
}

void jumpDino()
{
  // dino Jumping upward and tree is moving
  for( dino_y_pos=DINO_BASE_POINT_Y ; dino_y_pos >= (DINO_BASE_POINT_Y-70) && playState ; dino_y_pos-=(gameSpeed+2) )
  {
    clear_t_rex(DINO_BASE_POINT_X,trex_prev_pos_y);
    t_rex(DINO_BASE_POINT_X,dino_y_pos);
    trex_prev_pos_y=dino_y_pos;
    moveTree();
    delay(6);
    stop_buzzer();
  }

  // Dino is at the top and tree is moving
  for(int i=0;i<5 && playState;i++)
  {
    moveTree();
    delay(20);
  }

  // dino Jumping downward and tree is moving
  for(dino_y_pos=(DINO_BASE_POINT_Y-70);dino_y_pos<=DINO_BASE_POINT_Y && playState;dino_y_pos+=(gameSpeed+2))
  {
    clear_t_rex(DINO_BASE_POINT_X,trex_prev_pos_y);
    t_rex(DINO_BASE_POINT_X,dino_y_pos);
    trex_prev_pos_y=dino_y_pos;
    moveTree();
    delay(6);
  }
}

void startGame()
{
  if (mapX > 300)
  {
    start_buzzer();
    jumpDino();
  }
  else
  {
    moveTree();
  }

  scorePrint(); // Print the score on top right corner of screen
  // increase gameSpeed when score will increase 500*gameSpeed
  if(score>500*gameSpeed)
    gameSpeed++;
}
