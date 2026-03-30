#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct player
{
   string name;
   string cardsPlayed;
};


#define cardsPerSuit 14
struct player players[4];
int offensePlayerNum;
int suit = 0;
string color[4] = {"Red", "Blue", "Yellow", "Green"};
bool cardPlayed[78];
int pot[4];
float score = 0;
int royalsLeft = 16;

void printData()
{
   int royals = royalsLeft;
   for (int i = 0; i < 4; i++)
   {
       for (int j = 0; j < 4; j++)
       {
           if (cardPlayed[(78 - (i * cardsPerSuit)) - j - 1] == false)
           {
               switch (j)
               {
                   case 0:
                       printf("The %s King", color[3 - i]);
                       break;
                   case 1:
                       printf("The %s Queen", color[3 - i]);
                       break;
                   case 2:
                       printf("The %s Knight", color[3 - i]);
                       break;
                   case 3:
                       printf("The %s Jack", color[3 - i]);
                       break;
               }
               if (royals > 1)
               {
                   printf(", ");
               }
               royals--;
           }
           if (royals == 1)
           {
               printf("and ");
           }
       }
   }
   if (royalsLeft != 0)
   {
       printf(" are still in the game\n");
   }
   printf("Remaining trumps: \n");
   for (int i = 0; i < 22; i++)
   {
       if (!cardPlayed[i])
       {
           printf("%i is remaining\n", i);
       }
   }
}


float findScore(int id)
{
   switch (id)
   {
       case 0:
           return 0.5;
           break;
       case 1:
       case 21:
           return 9.5;
           break;
       default:
           break;
   }
   id = id - 22;
   if (id < 0)
   {
       return .5;
   }
   id = id % cardsPerSuit;
   switch (id)
   {
       case 10:
           return 1.5;
           break;
       case 11:
           return 2.5;
           break;
       case 12:
           return 3.5;
           break;
       case 13:
           return 4.5;
           break;
       default:
           break;
   }
   return .5;
}


void lockOff(int currentPlayerNum)
{
   players[currentPlayerNum].cardsPlayed =
       get_string("What did %s play? (Mark suit letter then number ex r6 or t17) ", players[currentPlayerNum].name);


   switch (players[currentPlayerNum].cardsPlayed[0])
   {
       case 't':
           suit = 0;
           break;
       case 'r':
           suit = 21;
           break;
       case 'b':
           suit = 35;
           break;
       case 'y':
           suit = 49;
           break;
       case 'g':
           suit = 63;
           break;
       default:
           suit = -1;
   }
   int cardNum = atoi(players[currentPlayerNum].cardsPlayed + 1);
   if (suit == -1 || (suit == 0 && cardNum > 21) || (suit > 0 && cardNum > cardsPerSuit) ||
       strlen(players[currentPlayerNum].cardsPlayed) < 2 || strlen(players[currentPlayerNum].cardsPlayed) > 3)
   {
       printf("Invalid card\n");
       lockOff(currentPlayerNum);
   }
   else if (cardPlayed[cardNum + suit] == true)
   {
       printf("Card has already been played\n");
       lockOff(currentPlayerNum);
   }
   else
   {
       cardPlayed[cardNum + suit] = true;
       pot[currentPlayerNum] = cardNum + suit;
       if (suit > 0 && (cardNum > 10) && (cardNum < 15))
       {
           royalsLeft--;
       }
   }
   return;
}


int gameTurn(int playerWhoLastWon)
{
   int currentPlayerNum = 0;
   for (int i = 0; i < 4; i++)
   {
       currentPlayerNum = i + playerWhoLastWon;
       if (currentPlayerNum > 3)
       {
           currentPlayerNum = currentPlayerNum - 4;
       }
       lockOff(currentPlayerNum);
   }
   for (int i = 0; i < 4; i++)
   {
       if (((atoi(players[i].cardsPlayed + 1) >
           (atoi(players[playerWhoLastWon].cardsPlayed + 1)))
           && (players[i].cardsPlayed[0] == players[playerWhoLastWon].cardsPlayed[0]))
           ||(players[i].cardsPlayed[0] == 't'
           && players[playerWhoLastWon].cardsPlayed[0] != 't'
           && players[i].cardsPlayed[1] != 0))
       {
           playerWhoLastWon = i;
       }
   }


   if (playerWhoLastWon == offensePlayerNum)
   {
       for (int i = 0; i < 4; i++)
       {
           score += findScore(pot[i]);


       }
   }
   for (int i = 0; i < 4; i++)
   {
       if (pot[i] == 0 && i == offensePlayerNum)
       {
           score += 9;
       }
   }
   if (score > 51)
   {
       printf("The Offense is winning by %i points\n", (int)score - 51);
   }
   else
   {
       printf("The Offense currently needs %i points to win\n", 51 - (int) score);
   }
   printData();
   return playerWhoLastWon;
}


int main(void)
{
   for (int i = 0; i < 4; i++)
   {
       players[i].name = get_string("Starting from right of the dealer, Who is player %i? ", i + 1);
   }
   offensePlayerNum = get_int("Which player is offense?(Player number) ") - 1;
   int playerWhoLastWon = 0;
   for (int i = 0; i < 18; i++)
   {
       printf("Turn %i\n", i + 1);
       playerWhoLastWon = gameTurn(playerWhoLastWon);
   }
   for (int i = 0; i < 79; i++)
   {
       if (!cardPlayed[i])
       {
           score += findScore(i);
       }
   }
   if (score >= 51)
   {
       printf("%s wins by %i points.", players[offensePlayerNum].name, (int) score - 51);
   }
   else
   {
       printf("%s loses by %i points.", players[offensePlayerNum].name, 51 - (int)score);
   }
}
