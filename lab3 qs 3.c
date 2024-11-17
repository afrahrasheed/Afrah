//QUESTION 3 LAB 3//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Constants
#define NUM_TEAMS 10        // Maximum number of teams//
#define SQUAD_SIZE 23       // Maximum players per team//

// Struct Definitions
typedef struct {
    int day, month, year;  // Date of birth of player//
} date_t;

typedef struct {
    char name[26];         // Full name (max 25 characters)//
    int kit_number;        // Kit number (1–99)//
    char club[51];         // Club name//
    date_t dob;            // Date of birth//
    char position[31];     // Position (e.g., midfielder)//
} player_t;

typedef struct {
    char name[21];         // Team name (max 20 characters)//
    player_t players[SQUAD_SIZE]; // Array of players//
    int active_size;       // Number of players in the team//
} team_t;

// Function Prototypes//
void display_menu();
void enroll_club(team_t teams[], int *num_teams);
void add_player(team_t teams[], int num_teams);
void search_update(team_t teams[], int num_teams);
void display_club_statistics(team_t teams[], int num_teams);
void handle_error(const char *message);
int calculate_age(date_t dob);


int main() {
    team_t teams[NUM_TEAMS]; // Array to hold the teams//
    int num_teams = 0;       // Number of teams currently there//
    int choice;

    while (1) {
        display_menu(); // Display the menu to the user//
        printf("Enter your choice: ");
        scanf("%d", &choice);

        
        switch (choice) {
            case 1: 
                enroll_club(teams, &num_teams);//enroll new team if user selects the option//
                break;
            case 2:
                add_player(teams, num_teams); //add players if user selects the option//
                break;
            case 3:
                search_update(teams, num_teams); //update the details if the user selects the option//
                break;
            case 4:
                display_club_statistics(teams, num_teams); //show the club statistics if the user selects the option//
                break;
            default:
                printf("Exiting program. Thank you!\n");
                return 0;
        }
    }
}


void display_menu() { // Display Menu//
    printf("\n===== Sports League Management Menu =====\n");
    printf("1. Enroll a new club\n");
    printf("2. Add a player to a club\n");
    printf("3. Search and update player details\n");
    printf("4. Display club statistics\n");
    printf("Any other key to exit\n");
}

void enroll_club(team_t teams[], int *num_teams) {  // Enroll a New Club//
    if (*num_teams >= NUM_TEAMS) {
        handle_error("Maximum number of clubs reached.");
        return;
    }

    printf("Enter the name of the club: ");
    getchar(); // Clear the buffer//
    fgets(teams[*num_teams].name, sizeof(teams[*num_teams].name), stdin);
    teams[*num_teams].name[strcspn(teams[*num_teams].name, "\n")] = '\0';

    
    for (int i = 0; i < *num_teams; i++) { // Check for duplicate club name//
        if (strcmp(teams[i].name, teams[*num_teams].name) == 0) {
            handle_error("Club name already exists.");
            return;
        }
    }

    teams[*num_teams].active_size = 0;
    (*num_teams)++;
    printf("Club '%s' enrolled successfully.\n", teams[*num_teams - 1].name);
}

void add_player(team_t teams[], int num_teams) { // Add a Player to a Club//
    if (num_teams == 0) {
        handle_error("No clubs enrolled yet. Please enroll a club first.");
        return;
    }

  
    printf("Select a club:\n");   // Display club list//
    for (int i = 0; i < num_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }

    int club_choice;       // Select a club//
    printf("Enter your choice: ");
    scanf("%d", &club_choice);
    club_choice--;

    if (club_choice < 0 || club_choice >= num_teams) {
        handle_error("Invalid club selection.");
        return;
    }

    if (teams[club_choice].active_size >= SQUAD_SIZE) {
        handle_error("Squad size limit reached for this club.");
        return;
    }

    player_t *player = &teams[club_choice].players[teams[club_choice].active_size];     // Add player details//
    printf("Enter player name: ");
    getchar(); // Clear buffer
    fgets(player->name, sizeof(player->name), stdin);
    player->name[strcspn(player->name, "\n")] = '\0';

    for (int i = 0; i < teams[club_choice].active_size; i++) {     // Check for duplicate player name or kit number//
        if (strcmp(teams[club_choice].players[i].name, player->name) == 0) {
            handle_error("Player name already exists in the squad.");
            return;
        }
    }

    printf("Enter kit number (1-99): ");
    scanf("%d", &player->kit_number);

    for (int i = 0; i < teams[club_choice].active_size; i++) {
        if (teams[club_choice].players[i].kit_number == player->kit_number) {
            handle_error("Kit number already exists in the squad.");
            return;
        }
    }

    printf("Enter date of birth (DD MM YYYY): ");
    scanf("%d %d %d", &player->dob.day, &player->dob.month, &player->dob.year);

    printf("Enter position: ");
    getchar();
    fgets(player->position, sizeof(player->position), stdin);
    player->position[strcspn(player->position, "\n")] = '\0';

    teams[club_choice].active_size++;
    printf("Player '%s' added successfully to club '%s'.\n", player->name, teams[club_choice].name);
}

void search_update(team_t teams[], int num_teams) { // Search and Update Player Details//
    char search_name[26];
    int search_kit_number, found = 0;

    printf("Enter player name or kit number to search: ");
    getchar(); // Clear buffer//
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = '\0';

    for (int i = 0; i < num_teams; i++) {     // Search for the player//
        for (int j = 0; j < teams[i].active_size; j++) {
            if (strcasecmp(teams[i].players[j].name, search_name) == 0 || 
                (sscanf(search_name, "%d", &search_kit_number) && teams[i].players[j].kit_number == search_kit_number)) {
                player_t *player = &teams[i].players[j];
                found = 1;

                printf("Player found in club '%s':\n", teams[i].name);
                printf("Name: %s, Kit: %d, DOB: %d/%d/%d, Position: %s\n",
                       player->name, player->kit_number, player->dob.day, player->dob.month, player->dob.year, player->position);

                printf("Do you want to update this player? (yes=1 / no=0): ");
                int update_choice;
                scanf("%d", &update_choice);
                if (update_choice == 1) {
                    printf("Enter new position: ");
                    getchar();
                    fgets(player->position, sizeof(player->position), stdin);
                    player->position[strcspn(player->position, "\n")] = '\0';
                    printf("Player position updated successfully.\n");
                }
                return;
            }
        }
    }

    if (!found) {
        printf("Player not found.\n");
    }
}

void display_club_statistics(team_t teams[], int num_teams) { // Display Club Statistics//
    for (int i = 0; i < num_teams; i++) {
        printf("\nClub: %s\n", teams[i].name);
        printf("Number of players: %d\n", teams[i].active_size);

        int total_age = 0;
        for (int j = 0; j < teams[i].active_size; j++) {
            player_t *player = &teams[i].players[j];
            int age = calculate_age(player->dob);
            total_age += age;

            printf("Name: %s, Kit: %d, Age: %d, Position: %s\n",
                   player->name, player->kit_number, age, player->position);
        }
        printf("Average age: %.2f\n", teams[i].active_size ? (float)total_age / teams[i].active_size : 0.0);
    }
}

void handle_error(const char *message) { // To handle Errors//
    printf("Error: %s\n", message);
}

int calculate_age(date_t dob) { // Calculate the Age//
    int current_year = 2024, current_month = 11, current_day = 16;
    int age = current_year - dob.year;
    if (dob.month > current_month || (dob.month == current_month && dob.day > current_day)) {
        age--;
    }
    return age;
}
