#include "computermove.h"

ComputerMove::ComputerMove()
{

}


QPair <int, int> ComputerMove::getMove(const QVector< QVector<Square *> > &grid)
{
    int nimXor = 0;

    for(int i = 0; i < grid.size(); i++){
        nimXor ^= grid[i].size();
    }

    int pile = 0, amount = 1;

    if(nimXor){ // winning position
        for(int i = 0; i < grid.size(); i++){
            if(grid[i].size() > (grid[i].size() ^ nimXor)){
                pile = i;
                amount = grid[i].size() - (grid[i].size() ^ nimXor);
                break;
            }
        }
    }
    else{ // losing position
        // random move

        for(int i = 0; i < grid.size(); i++){
            if(grid[i].size() > 0){
                pile = i;
                amount = (qrand() % grid[i].size()) + 1;
                break;
            }
        }
    }

    return qMakePair(pile, amount);
}
