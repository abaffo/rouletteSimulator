#include "roulette.hpp"
#include "player.hpp"

#define ROULETTE_MAX_NUMBER 37
#define ROULETTE_MINMAX_LIMIT 19

Roulette::Roulette()
{
    srand((unsigned int)time(NULL));
    resetBetResult();
}

Roulette::~Roulette()
{

}

void Roulette::spin(){
       
    int spinResult = std::rand() % ROULETTE_MAX_NUMBER;
    setBetResult(spinResult);

    // TEST: show result
    std::cout<<std::endl<<spinResult<<") ";
    for(auto a: betResult){
        std::cout<<getBetTypeName(a.first)<<": "<<a.second<<", ";
    }
    std::cout<<std::endl;

}

void getName();

void Roulette::setBetResult(int spinResult){

    resetBetResult();

    if(spinResult==0){
        return;
    }
    
    if(spinResult<19){
        betResult[LOW] = true;
    } else { 
        betResult[HIGH] = true;
    }

    if(spinResult%2){
        betResult[ODD] = true;

        if (spinResult <= 10 || (spinResult > 18 && spinResult <= 28)){
            betResult[RED] = true;
        } else { 
            betResult[BLACK] = true;
        }

    } else {
        betResult[EVEN] = true;

        if (spinResult <= 10 || (spinResult > 18 && spinResult <= 28)){
            betResult[BLACK] = true;
        } else { 
            betResult[RED] = true;
        }
    }

}

void Roulette::resetBetResult(){
   betResult = {{RED, false}, 
                {BLACK, false}, 
                {EVEN, false}, 
                {ODD, false}, 
                {LOW, false}, 
                {HIGH, false}};
}


void Roulette::setBet(int playID, BetsTypes betType, float money) const{
    if(money<=0){
        return;
    }
    betTable[playID] = bet{betType,money};
}

Roulette::BetTable Roulette::getBetTable() const{
    return betTable;
}

float Roulette::payPlayer(int playerID){
    float ret = 0;
    
    if (!(betTable.find(playerID) == betTable.end())) {
        std::cout<<"bet="<<getBetTypeName(betTable.at(playerID).betType);
        std::cout<<", restult = "<< betResult[betTable.at(playerID).betType] <<std::endl;   
    } else {
        std::cout<<"[Warning] Player "<< playerID <<" asked about a bet not found"<<std::endl;
    }

    return ret;

}

std::string Roulette::getBetTypeName(BetsTypes bet){
    std::string ret;
    switch (bet)
    {
    case RED:
        ret = "red";
        break;
    case BLACK:
        ret = "black";
        break;
    case EVEN:
        ret = "even";
        break;
    case ODD:
        ret = "odd";
        break;
    case LOW:
        ret = "low";
        break;
    case HIGH:
        ret = "high";
        break;
    default:
        ret = "unknown";
        break;
    }

    return ret;
}
