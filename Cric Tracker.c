#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ANSI Color Codes for a professional look
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD    "\x1b[1m"

struct PlayerNode {
    char name[50];
    int runs;
    int innings;
    int wickets;
    struct PlayerNode* next;
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

struct PlayerNode* createNode(char* name, int runs, int innings, int wickets) {
    struct PlayerNode* newNode = (struct PlayerNode*)malloc(sizeof(struct PlayerNode));
    if (!newNode) return NULL;
    strcpy(newNode->name, name);
    newNode->runs = runs;
    newNode->innings = innings;
    newNode->wickets = wickets;
    newNode->next = NULL;
    return newNode;
}

void addPlayer(struct PlayerNode** head_ref, char* name, int runs, int innings, int wickets) {
    struct PlayerNode* newNode = createNode(name, runs, innings, wickets);
    if (*head_ref == NULL) {
        *head_ref = newNode;
    } else {
        struct PlayerNode* temp = *head_ref;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    printf(GREEN "\n>> [SUCCESS] Player '%s' added to the database.\n" RESET, name);
}

// --- UPDATED DISPLAY WITH REFINED PADDING ---
void displayAll(struct PlayerNode* head) {
    if (head == NULL) {
        printf(YELLOW "\n>> [EMPTY] No players found in the tracker.\n" RESET);
        return;
    }

    printf(CYAN "\n" BOLD "  LIVE SCOREBOARD SUMMARY" RESET);
    printf(BLUE "\n+----------------------+----------+----------+----------+----------+\n");
    printf("| %-20s | %-8s | %-8s | %-8s | %-8s |\n", "PLAYER NAME", "RUNS", "INNINGS", "AVG", "WICKETS");
    printf("+----------------------+----------+----------+----------+----------+\n" RESET);

    struct PlayerNode* temp = head;
    while (temp != NULL) {
        double avg = (temp->innings > 0) ? (double)temp->runs / temp->innings : 0.0;
        printf("| %-20s | %-8d | %-8d | %-8.2f | %-8d |\n",
               temp->name, temp->runs, temp->innings, avg, temp->wickets);
        temp = temp->next;
    }
    printf(BLUE "+----------------------+----------+----------+----------+----------+\n" RESET);
}

// --- UPDATED COMPREHENSIVE UPDATE FUNCTION ---
void updateStats(struct PlayerNode* head, char* searchName) {
    struct PlayerNode* temp = head;
    int found = 0;

    while (temp != NULL) {
        if (strcmp(temp->name, searchName) == 0) {
            int r, i, w;
            printf(CYAN "\n>> Found: " BOLD "%s" RESET "\n", searchName);
            printf(YELLOW "Current Stats -> Runs: %d | Innings: %d | Wickets: %d\n" RESET,
                   temp->runs, temp->innings, temp->wickets);

            printf("\n Enter runs to ADD: ");
            scanf("%d", &r);
            printf(" Enter innings to ADD: ");
            scanf("%d", &i);
            printf(" Enter wickets to ADD: ");
            scanf("%d", &w);
            clearInputBuffer();

            temp->runs += r;
            temp->innings += i;
            temp->wickets += w;

            printf(GREEN ">> [UPDATED] Stats for %s updated successfully!\n" RESET, searchName);
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (!found) printf(RED "\n>> [ERROR] Player '%s' not found.\n" RESET, searchName);
}

void deletePlayer(struct PlayerNode** head_ref, char* key) {
    struct PlayerNode *temp = *head_ref, *prev = NULL;

    if (temp != NULL && strcmp(temp->name, key) == 0) {
        *head_ref = temp->next;
        free(temp);
        printf(RED "\n>> [REMOVED] Player '%s' deleted.\n" RESET, key);
        return;
    }

    while (temp != NULL && strcmp(temp->name, key) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf(YELLOW "\n>> [ERROR] Player '%s' not found.\n" RESET, key);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf(RED "\n>> [REMOVED] Player '%s' deleted.\n" RESET, key);
}

int main() {
    struct PlayerNode* head = NULL;
    int choice;
    char name[50];
    int runs, innings, wickets;

    do {
        printf(CYAN "\n" BOLD "============================================\n");
        printf("       CRICKET PLAYER TRACKER PRO           \n");
        printf("============================================\n" RESET);
        printf(YELLOW " 1." RESET " Add New Player\n");
        printf(YELLOW " 2." RESET " Display Scoreboard\n");
        printf(YELLOW " 3." RESET " Update Player Stats (Runs/Inn/Wkt)\n");
        printf(YELLOW " 4." RESET " Delete Player\n");
        printf(YELLOW " 5." RESET " Exit\n");
        printf(CYAN "--------------------------------------------\n" RESET);
        printf(" Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                printf(BOLD "\n--- ADD PLAYER ---\n" RESET);
                printf("Enter Full Name: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter Runs: "); scanf("%d", &runs);
                printf("Enter Innings: "); scanf("%d", &innings);
                printf("Enter Wickets: "); scanf("%d", &wickets);
                clearInputBuffer();
                addPlayer(&head, name, runs, innings, wickets);
                break;
            case 2:
                displayAll(head);
                break;
            case 3:
                printf(BOLD "\n--- UPDATE STATS ---\n" RESET);
                printf("Enter Player Name: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0;
                updateStats(head, name);
                break;
            case 4:
                printf(BOLD "\n--- DELETE PLAYER ---\n" RESET);
                printf("Enter Player Name: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0;
                deletePlayer(&head, name);
                break;
            case 5:
                printf(CYAN "\nCleaning memory and exiting... Goodbye!\n" RESET);
                break;
            default:
                printf(RED "\n>> Invalid choice!\n" RESET);
        }
    } while (choice != 5);

    return 0;
}
