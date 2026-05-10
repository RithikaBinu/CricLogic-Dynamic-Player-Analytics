#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ANSI COLOR PALETTE ---
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD    "\x1b[1m"

// --- DATA STRUCTURE ---
struct PlayerNode {
    char name[50];
    int runs;
    int innings;
    int wickets;
    struct PlayerNode* next;
}; // <-- CRITICAL: Semicolon here, and nothing else before the next function.

// --- HELPER FUNCTIONS ---
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

// 1. ADD PLAYER
void addPlayer(struct PlayerNode** head_ref, char* name, int runs, int innings, int wickets) {
    struct PlayerNode* newNode = createNode(name, runs, innings, wickets);

    if (*head_ref == NULL) {
        *head_ref = newNode;
    } else {
        struct PlayerNode* temp = *head_ref;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf(GREEN "\n>> [SUCCESS] Player '%s' added to the database.\n" RESET, name);
}

// 2. DISPLAY SCOREBOARD
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
        // Calculate average safely to avoid division by zero
        double avg = (temp->innings > 0) ? (double)temp->runs / temp->innings : 0.0;

        printf("| %-20s | %-8d | %-8d | %-8.2f | %-8d |\n",
               temp->name, temp->runs, temp->innings, avg, temp->wickets);
        temp = temp->next;
    }
    printf(BLUE "+----------------------+----------+----------+----------+----------+\n" RESET);
}

// 3. COMPREHENSIVE UPDATE
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

    if (!found) {
        printf(RED "\n>> [ERROR] Player '%s' not found.\n" RESET, searchName);
    }
}

// 4. DELETE PLAYER
void deletePlayer(struct PlayerNode** head_ref, char* key) {
    struct PlayerNode *temp = *head_ref, *prev = NULL;

    // If head node itself holds the key
    if (temp != NULL && strcmp(temp->name, key) == 0) {
        *head_ref = temp->next;
        free(temp);
        printf(RED "\n>> [REMOVED] Player '%s' deleted.\n" RESET, key);
        return;
    }

    // Search for the key to be deleted
    while (temp != NULL && strcmp(temp->name, key) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) {
        printf(YELLOW "\n>> [ERROR] Player '%s' not found.\n" RESET, key);
        return;
    }

    // Unlink the node from linked list
    prev->next = temp->next;
    free(temp);
    printf(RED "\n>> [REMOVED] Player '%s' deleted.\n" RESET, key);
}

// --- MAIN INTERFACE ---
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

        // Input validation for menu choice
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf(RED "\n>> Invalid input! Please enter a number.\n" RESET);
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                printf(BOLD "\n--- ADD PLAYER ---\n" RESET);
                printf("Enter Full Name: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline

                printf("Enter Total Runs: ");
                scanf("%d", &runs);
                printf("Enter Total Innings: ");
                scanf("%d", &innings);
                printf("Enter Total Wickets: ");
                scanf("%d", &wickets);
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
                printf(CYAN "\nCleaning up memory... See you at the next match!\n" RESET);
                break;

            default:
                printf(RED "\n>> Invalid choice! Please select 1-5.\n" RESET);
        }
    } while (choice != 5);

    // --- MEMORY CLEANUP BEFORE EXIT ---
    struct PlayerNode* current = head;
    while (current != NULL) {
        struct PlayerNode* nextNode = current->next;
        free(current);
        current = nextNode;
    }

    return 0;
}
