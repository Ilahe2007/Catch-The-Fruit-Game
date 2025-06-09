#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<unistd.h>
int flag = 0;

void menu();

void moving_basket(int *key, int *x){
    //This function moves the basket using coordinate x and arrow keys
    *key = getch();
    if(*key == KEY_RIGHT){
        (*x)++;
        if((*x) > 10){
            *x = 1;
        }
    }else if(*key == KEY_LEFT){
        (*x)--;
        if((*x) < 1){
            (*x) = 10;
        }
    }
}

int falling(int *heart){
    //this function chooses random food or a bomb to go down
    int random_coordinate = rand() % 10 + 1 ;
    int index_of_choosen_food = rand() % 6;
    while(index_of_choosen_food == 5){
        if(*heart == 3){
            index_of_choosen_food = rand() % 6;
        }else{
            break;
        }
    }
    return random_coordinate * 10 + index_of_choosen_food; //I am taking it as a three or two digit number, example if coorinate is taken as 10 and random choice is 1, then 101 will be mmy number so to use the coordinate i will take number/10, for the choosen index i will use number % 10
}

void hearts(int *heart){
    for(int i = 0; i < *heart; i++)    printw("❤️ ");
    printw("\n");
}

void info(){
    clear();
    printw("The game rules are simple. \nThere's foods falling and specific food you need to catch. you have 3 lives.\n if you dont catch the food you supposed to catch you lose one point,\n if you catch a fruit you're not supposed to catch then you lose one live as well. if you catch a bomb you lose 2 lives.\n But theres sometimes hears falling if you catch it you gain one live. after every 3 score food falls faster. Have fun!");
    refresh();
    int key = 1;
    while(key){
        if(key == ' '){
            break;
        }
        key = getch();
    }
    clear();
    menu();
}

void frame(){
    for(int i = 0 ; i < 10; i++){
        move(i, 0);
        printw("#");
        move(i, 12);
        printw("#");
        refresh();
    }
}

void game(){

    int key, y = 0, x = 10, score = 1, speed = 150000;
    char* food_chosen[6] = {"🍓", "💣", "🍌", "🍎", "🍍","❤️"};
    frame();
    move(10,5);
    printw("🧺");
    refresh();
    int heart = 3, to_catch = falling(&heart) % 10;
    if(to_catch == 1 || to_catch == 5){
        to_catch--; //if it's bomb then we change it
    }

    while(key != '0'){ 
        //food moves down
        frame();
        int choice = falling(&heart);
        int coordinate = choice / 10, index = choice %10;
        while(y < 10){
            frame();
            usleep(speed);

            clear(); 
            move(15,0);
            printw("Your lives:");
            hearts(&heart);
            printw("Score: %d\n", score - 1);
            printw("The fruit you need to catch is: %s\n", food_chosen[to_catch]);
            refresh();
            move(y, coordinate);
            printw("%s", food_chosen[index]);
            refresh();

            //Moving the basket
            moving_basket(&key, &x);
            move(10,x);
            printw("🧺");
            refresh();
            y++;
        }y = 0;
        

        //checks if the basket catched the food
        if(coordinate == x){
            //if it did we increase the score
            if(food_chosen[to_catch] == food_chosen[index]){
                score++;
                if(score % 3 == 0){
                    speed -= 50000;
                }
            }else{
                //if it catch the fruit but it wasnt the one we needed or bomb we decrease the lives
                if(food_chosen[index] == "💣")       heart-=2;
                else if(food_chosen[index] == "❤️")  heart++;
                else                                 heart--;
            }
        }else{
            if(food_chosen[index] == food_chosen[to_catch])     heart--;
        }

        //if 3 lives are lost you lose
        if(heart < 0){
            clear();
            move(10,10);
            printw("SKILL ISSUE!\n");
            move(11,10);
            printw("FINAL SCORE: %d", score);
            refresh();
            sleep(2);
            clear();
            menu();
        }

        if(heart > 3)       heart = 3;
    }

    getch();
    endwin();
}

void menu(){
    clear();
    if(flag == 0){
        move(10,10);
        printw(">Start<\n");
        move(11,10);
        printw(" Rules");
        move(12,10);
        printw(" Exit");
        refresh();
    }else if(flag == 1){
        refresh();move(10,10);
        printw(" Start\n");
        move(11,10);
        printw(">Rules<");
        move(12,10);
        printw(" Exit");
        refresh();
    }else{
        move(10,10);
        printw(" Start\n");
        move(11,10);
        printw(" Rules");
        move(12,10);
        printw(">Exit<");
    }

    while(true){

        switch (getch()){
            case ' ':
                if(flag == 1){
                    info();
                }else if(flag == 0){
                    game();
                }else{
                    endwin();
                    break;
                }
            case KEY_DOWN:
                if(flag == 0){
                    flag = 1;
                }else if (flag == 1){
                    flag = 2;
                }else{
                    flag = 0;
                }
            menu();
            case KEY_UP:
                if(flag == 0){
                    flag = 2;
                }else if(flag == 1){
                    flag = 0;
                }else{
                    flag = 1;
                }
            menu();
        }
    }
}

int main(){
    setlocale(LC_ALL, "");  //I used it so I can use emojis
    srand(time(0));
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);  //so the fruits move even if no key is pressed
    noecho();  //so the key we pressed is not shown on the screen
    clear(); 
    curs_set(0); //not to show the cursor
    menu();
    return 0;
}