#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


void intro();
void lobby();
void poisonedCocktail();
void scorpionAttempt();
void rooftopConfrontation();
void ending();

void main() {
    intro();
}

void intro() {
    char choice[10];
    clrscr();

    cout << "[HOTEL REVERIE]\n";
    cout << "Cairo, 1940s.\n";
    cout << "Your name is Alex Palmer, a doctor passing through a city which never truly sleeps.\n";
    cout << "You have taken a room at the Hotel Reverie, unaware that before your stay is over,\n";
    cout << "the strings of fate will intertwine yours with that of an heiress named Clara Ryce-Lechere.\n\n";
    cout << "Do you wish to begin? [Y/N]: ";
    cin >> choice;

    if (strcmp(choice, "Y") == 0) {
        lobby();
    }
    else {
        cout << "You turn away from the hotel.\n";
        cout << "Some stories are never lived. Goodbye.\n";
        exit(0);
    }
}

void lobby() {
    char choice[10];

    clrscr();
    cout << "\nThe lobby is half-shadow and half-smoke. A forgotten piano stands in the corner.\n";
    cout << "You nurse a glass of whiskey, listening to the distant sounds of the city at night.\n";
    cout << "Clara Ryce-Lechere enters your peripheral vision, akin to an apparition, her elegance worn like armor.\n";
    cout << "Her eyes betray exhaustion and sorrow.\n";
    cout << "You invite her to sit. She does.\n";
    cout << "She murmurs, almost to herself: 'The piano hasn't been touched in years.'\n\n";
    cout << "Do you...\n";
    cout << "[1] Rise and play 'Clair de Lune' for her.\n";
    cout << "[2] Remain seated, sharing the silence.\n";
    cout << "Your choice... ";
    cin >> choice;

    if (strcmp(choice, "1") == 0) {
        cout << "\nYour fingers find the keys. The melody drifts through the airspace.\n";
        cout << "Clara closes her eyes. When the final note fades, she rises abruptly.\n";
        cout << "Having had her emotions stirred, she leaves without a word.\n";
        poisonedCocktail();
    }
    else if (strcmp(choice, "2") == 0) {
        cout << "\nYou sit together in silence.\n";
        cout << "Eventually, Clara stands.\n";
        cout << "Goodbye, Doctor Palmer.\n";

        exit(0);
    }
    else {
        cout << "Invalid choice. Try again...\n";
        lobby();
    }
}

void poisonedCocktail() {
    char choice[10];

    clrscr();
    cout << "\nA little later, you order a Black Rose cocktail, intending it for Clara.\n";
    cout << "The glass gleams beneath the dim lights. When you return, Clara is gone.\n";
    cout << "You hand the drink over to the nearest person to you. Madame Roban accepts the drink.\n";
    cout << "Minutes later, she lies dead.\n";
    cout << "The lobby fills with uniforms, with questions and suspicion.\n\n";
    cout << "Do you...\n";
    cout << "[1] Assist Inspector Lavigne with the investigation.\n";
    cout << "[2] Slip away before the net tightens.\n";
    cout << "Your choice...";
    cin >> choice;

    if (strcmp(choice, "1") == 0) {
        cout << "\nYou speak of the derails you have noticed, details others miss. The faint scent of perfume, the itch in your throat.\n";
        cout << "Inspector Lavigne listens closely. Another thread is pulled.\n";
        scorpionAttempt();
    }
    else if (strcmp(choice, "2") == 0) {
        cout << "\nYou leave the hotel, and your fate, behind.\n";
        cout << "It seems that, after all... Some doors, once closed, can never open again. Don't you think?\n";
        exit(0);
    }
    else {
        cout << "Invalid choice. Try again...\n";
        poisonedCocktail();
    }
}

void scorpionAttempt() {
    char choice[10];

    clrscr();
    cout << "\nThe following evening, you arrive at Clara's room with a glass of champagne in hand.\n";
    cout << "As you step inside, you notice movement nearby the curtains.\n";
    cout << "A scorpion... You cannot help it but think that it has been placed there with intent.\n\n";
    cout << "Do you...\n";
    cout << "[1] Trap the scorpion beneath a glass.\n";
    cout << "[2] Retreat, and leave Clara to face it alone.\n";
    cout << "Your choice... ";
    cin >> choice;

    if (strcmp(choice, "1") == 0) {
        cout << "\nYour reflexes are swift. The scorpion thrashes beneath the glass.\n";
        cout << "Clara trembles, then steps into your arms, a soft kind of urgency in her kiss.\n";
        rooftopConfrontation();
    }
    else if (strcmp(choice, "2") == 0) {
        cout << "\nYou withdraw, the sound of the door echoing behind you.\n";
        cout << "Cowardice has a long memory.\n";
        cout << "You won't come back, will you?\n";
        exit(0);
    }
    else {
        cout << "Invalid choice. Try again...\n";
        scorpionAttempt();
    }
}

void rooftopConfrontation() {
    char choice[10];

    clrscr();
    cout << "\nNear midnight, a voice carries through the stairwell.\n";
    cout << "Claude Ryce-Lechere, and his accomplice, Otto. Murder, spoken about with an air of nonchalance.\n";
    cout << "You follow them to the rooftop, wind whipping at your gray coat.\n";
    cout << "Claude lunges for Clara, forcing her toward the broken railing.\n";
    cout << "Do you...\n";
    cout << "[1] Confront Claude.\n";
    cout << "[2] Shout a healf-hearted warning, and flee.\n";
    cout << "Your choice...";
    cin >> choice;

    if (strcmp(choice, "1") == 0) {
        cout << "\nBlows are exchanged. Claude stumbles backwards as the sound of sirens permeates the air.\n";
        cout << "Inspector Lavigne appears, his pistol drawn.\n";
        ending();
    }
    else if (strcmp(choice, "2") == 0) {
        cout << "\nYour warning comes too late. Clara falls into the darkness below.\n";
        exit(0);
    }
    else {
        cout << "Invalid choice. Try again...\n";
        rooftopConfrontation();
    }
}

void ending() {
    clrscr();
    cout << "\nClaude is taken away, wringing his hands helplessly in their handcuffs. Dawn approaches.\n";
    cout << "On the rooftop, Cairo stretches endlessly beneath you.\n";
    cout << "Clara turns to you. She is shaken, but free.\n\n";
    cout << "You hold her close. The two of you now have all the time in the world.\n";
    cout << "Below, Cairo goes on as it always has.\n";
    cout << "[THANK YOU FOR PLAYING.]\n";
    cout << "[WE HOPE THAT YOU HAVE ENJOYED YOUR STAY.]\n";
    exit(0);
}