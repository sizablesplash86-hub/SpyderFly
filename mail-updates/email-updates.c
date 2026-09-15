#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBSCRIBER_FILE "/var/lib/mysite/subscribers.txt"

// Function to save a new subscriber email
int save_subscriber(const char *email) {
    // Basic validation check
    if (strchr(email, '@') == NULL || strlen(email) > 254) {
        return -1;
    }

    // Check for duplicates
    FILE *file = fopen(SUBSCRIBER_FILE, "r");
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = 0;
            if (strcmp(line, email) == 0) {
                fclose(file);
                return 0; // Already subscribed
            }
        }
        fclose(file);
    }

    // Append new email
    file = fopen(SUBSCRIBER_FILE, "a");
    if (!file) return -1;
    
    fprintf(file, "%s\n", email);
    fclose(file);
    return 1;
}

// Function to broadcast repository updates to all subscribers
void send_notifications(const char *repo_name, const char *commit_msg) {
    FILE *file = fopen(SUBSCRIBER_FILE, "r");
    if (!file) return;

    char email[256];
    char command[1024];

    while (fgets(email, sizeof(email), file)) {
        email[strcspn(email, "\r\n")] = 0;
        if (strlen(email) == 0) continue;

        // Construct headers including From, To, and Subject
        snprintf(command, sizeof(command), 
                 "echo -e \"From: noreply@sizablesplash.com\\n"
                 "To: %s\\n"
                 "Subject: Update on %s\\n"
                 "Content-Type: text/plain; charset=UTF-8\\n\\n"
                 "A new commit was pushed to %s:\\n\\n%s\" | sendmail %s", 
                 email, repo_name, repo_name, commit_msg, email);
        
        int ret = system(command);
        if (ret != 0) {
            fprintf(stderr, "Failed to send email to %s\n", email);
        }
    }
    fclose(file);
}
int main() {
    // Example simulation of handling a subscription request
    // In your actual server loop, you'd parse the HTTP POST body for JSON: {"email":"user@example.com"}
    const char *new_user = "testuser@example.com";
    int res = save_subscriber(new_user);
    if (res == 1) {
        printf("Added new subscriber: %s\n", new_user);
    }

    // Example simulation of handling a GitHub Webhook payload
    // GitHub sends a JSON payload on push; your C parser extracts the repo name and commit message.
    send_notifications("sizablesplash/repo", "Fix memory leak in socket handler");

    return 0;
}
