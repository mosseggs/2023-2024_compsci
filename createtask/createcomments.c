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
// Let the major arcana be first 0-21 and starting from 22
// Then ace - king the fourteen cards of each color are entered going red blue yellow green
bool cardPlayed[78];
int pot[4];
float score = 0;
int royalsLeft = 16;

void printData()
{
   // iterate through each suit and find the highest royal
   int royals = royalsLeft;
   for (int i = 0; i < 4; i++)
   {
       for (int j = 0; j < 4; j++)
       {
           if (cardPlayed[(78 - (i * cardsPerSuit)) - j - 1] == false)
           {
               switch (j)
               {
                   // king
                   case 0:
                       printf("The %s King", color[3 - i]);
                       break;
                   // queen
                   case 1:
                       printf("The %s Queen", color[3 - i]);
                       break;
                   // knight
                   case 2:
                       printf("The %s Knight", color[3 - i]);
                       break;
                   // jack
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
   // print remaining trumps
   printf("Remaining trumps: \n");
   for (int i = 0; i < 22; i++)
   {
       if (!cardPlayed[i])
       {
           printf("%i is remaining\n", i);
       }
   }
}


// returns the score of each card
float findScore(int id)
{
   switch (id)
   {
       // counts the three oudlers
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
   // removes the major arcana
   // sets red ace to the first card
   id = id - 22;
   // if its a non oudler trump half a point
   if (id < 0)
   {
       return .5;
   }
   // removes the suit
   id = id % cardsPerSuit;
   // jack should be 10 knight 11 queen 12 king 13
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
   // if normal card return half a point
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
   // Contingency for if the suit is invalid or the card is above the allowed values(22 for tarots and 15 for colors)
   if (suit == -1 || (suit == 0 && cardNum > 21) || (suit > 0 && cardNum > cardsPerSuit) ||
       strlen(players[currentPlayerNum].cardsPlayed) < 2 || strlen(players[currentPlayerNum].cardsPlayed) > 3)
   {
       printf("Invalid card\n");
       lockOff(currentPlayerNum);
   }
   // contingency for if the card has already been played previously
   else if (cardPlayed[cardNum + suit] == true)
   {
       printf("Card has already been played\n");
       lockOff(currentPlayerNum);
   }
   // otherwise proceed as planned
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
   // Note to grader. In tarot the player who won the last round goes first instead of the first player.
   // Therefore this section of code is to iterate through a turn in the correct game order
   int currentPlayerNum = 0;
   for (int i = 0; i < 4; i++)
   {
       // Starting from the player who last one rotate in order through each player
       currentPlayerNum = i + playerWhoLastWon;
       if (currentPlayerNum > 3)
       {
           // just ensures the loop continues as first player goes after fourth player
           currentPlayerNum = currentPlayerNum - 4;
       }
       // lock off cards
       lockOff(currentPlayerNum);
   }
   // Section: Calculating the winner of the round
   // If they play a tarot and the other card is a color, tarot always wins. If both play the same color, the higher number wins.
   // If they play different colors, Previous winner wins.
   for (int i = 0; i < 4; i++)
   {
       // Checks if the card is higher then the other atoi( + 1) starts from second char
       if (((atoi(players[i].cardsPlayed + 1) > (atoi(players[playerWhoLastWon].cardsPlayed + 1)))
            // same suit
            && (players[i].cardsPlayed[0] == players[playerWhoLastWon].cardsPlayed[0]))
           // Checks for trumps and the fool
           ||
           (players[i].cardsPlayed[0] == 't' && players[playerWhoLastWon].cardsPlayed[0] != 't' && players[i].cardsPlayed[1] != 0))
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
